//! @file     DDSFile.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// DXTColor8888
//----------------------------------------------------------------------------

struct DXTColor8888
{
	_byte b;
	_byte g;
	_byte r;
	_byte a;
};

//----------------------------------------------------------------------------
// DXTColor565
//----------------------------------------------------------------------------

struct DXTColor565
{
	_word b : 5;
	_word g : 6;
	_word r : 5;
};

//----------------------------------------------------------------------------
// DXTColorBlock
//----------------------------------------------------------------------------

struct DXTColorBlock
{
	DXTColor565 mColors565[2];
	_byte		mRow[4];
};

//----------------------------------------------------------------------------
// DXTAlphaBlockExplicit
//----------------------------------------------------------------------------

struct DXTAlphaBlockExplicit 
{
	_word mRow[4];
};

//----------------------------------------------------------------------------
// DXTAlphaBlock3BitLinear
//----------------------------------------------------------------------------

struct DXTAlphaBlock3BitLinear 
{
	_byte mAlpha[2];
	_byte mData[6];
};

//----------------------------------------------------------------------------
// DXT1Block
//----------------------------------------------------------------------------

struct DXT1Block
{
	DXTColorBlock mColor;
};

//----------------------------------------------------------------------------
// DXT3Block ( also used by dxt2 )
//----------------------------------------------------------------------------

struct DXT3Block 
{
	DXTAlphaBlockExplicit	mAlpha;
	DXTColorBlock			mColor;
};

//----------------------------------------------------------------------------
// DXT5Block ( also used by dxt4 )
//----------------------------------------------------------------------------

struct DXT5Block 
{
	DXTAlphaBlock3BitLinear mAlpha;
	DXTColorBlock			mColor;
};

//----------------------------------------------------------------------------
// GetBlockColors Implementation
//----------------------------------------------------------------------------

static _void GetBlockColors( const DXTColorBlock& block, DXTColor8888* colors ) 
{
	// Expand from 565 to 888
	for ( _dword i = 0; i < 2; i ++ )
	{
		colors[i].a = 0xFF;
		colors[i].r = (_byte) ( ( block.mColors565[i].r << 3 ) | ( block.mColors565[i].r >> 2 ) );
		colors[i].g = (_byte) ( ( block.mColors565[i].g << 2 ) | ( block.mColors565[i].g >> 4 ) );
		colors[i].b = (_byte) ( ( block.mColors565[i].b << 3 ) | ( block.mColors565[i].b >> 2 ) );
	}

	_word* blockcolor = (_word*) block.mColors565;
	if ( blockcolor[0] > blockcolor[1] )
	{
		// 4 color block
		for ( _dword i = 0; i < 2; i ++ )
		{
			colors[i + 2].a = 0xFF;
			colors[i + 2].r = (_byte) ( ( _word( colors[0].r ) * ( 2 - i ) + _word( colors[1].r ) * ( 1 + i ) ) / 3 );
			colors[i + 2].g = (_byte) ( ( _word( colors[0].g ) * ( 2 - i ) + _word( colors[1].g ) * ( 1 + i ) ) / 3 );
			colors[i + 2].b = (_byte) ( ( _word( colors[0].b ) * ( 2 - i ) + _word( colors[1].b ) * ( 1 + i ) ) / 3 );
		}
	}
	else 
	{
		// 3 color block, number 4 is transparent
		colors[2].a = 0xFF;
		colors[2].r = (_byte) ( ( _word( colors[0].r ) + _word( colors[1].r ) ) / 2 );
		colors[2].g = (_byte) ( ( _word( colors[0].g ) + _word( colors[1].g ) ) / 2 );
		colors[2].b = (_byte) ( ( _word( colors[0].b ) + _word( colors[1].b ) ) / 2 );

		colors[3].a = 0x00;
		colors[3].g = 0x00;
		colors[3].b = 0x00;
		colors[3].r = 0x00;
	}
}

//----------------------------------------------------------------------------
// DXTBlockCoderBase
//----------------------------------------------------------------------------

template< typename Type > 
class DXTBlockCoderBase
{
protected:
	DXTColor8888	mColors[4];
	const Type*		mBlock;
	_word			mColorRow;

public:
	_void Setup( const _byte* block )
	{
		mBlock = (const Type*) block;

		GetBlockColors( mBlock->mColor, mColors );
	}

	_void SetY( _int y ) 
	{
		mColorRow = mBlock->mColor.mRow[y];
	}

	_void GetColor( _dword x, _dword y, DXTColor8888& color )
	{
		_word bits = ( mColorRow >> ( x * 2 ) ) & 3;

		color = mColors[ bits ];
	}
};

//----------------------------------------------------------------------------
// DXT1BlockCoder
//----------------------------------------------------------------------------

class DXT1BlockCoder : public DXTBlockCoderBase< DXT1Block > 
{
public:
	static _dword GetBytesPerBlock( )
	{
		return sizeof( DXT1Block );
	}
};

//----------------------------------------------------------------------------
// DXT3BlockCoder
//----------------------------------------------------------------------------

class DXT3BlockCoder : public DXTBlockCoderBase< DXT3Block > 
{
protected:
	typedef DXTBlockCoderBase< DXT3Block > BaseClass;

protected:
	_word	mAlphaRow;

public:
	static _dword GetBytesPerBlock( )
	{
		return sizeof( DXT3Block );
	}

	_void SetY( int y )
	{
		BaseClass::SetY( y );

		mAlphaRow = mBlock->mAlpha.mRow[y];
	}

	_void GetColor( _dword x, _dword y, DXTColor8888& color )
	{
		BaseClass::GetColor( x, y, color );

		_word bits = ( mAlphaRow >> ( x * 4 ) ) & 0x0F;
		color.a = (_byte) ( ( bits * 0xFF ) / 0x0F );
	}
};

//----------------------------------------------------------------------------
// DXT5BlockCoder
//----------------------------------------------------------------------------

class DXT5BlockCoder : public DXTBlockCoderBase< DXT5Block > 
{
protected:
	typedef DXTBlockCoderBase< DXT5Block > BaseClass;

protected:
	_word 	mAlphas[8];
	_word 	mAlphaBits;
	_int	mOffset;

public:
	static _dword GetBytesPerBlock( )
	{
		return sizeof( DXT5Block );
	}

	_void Setup( const _byte* block )
	{
		BaseClass::Setup( block );

		const DXTAlphaBlock3BitLinear& alphablock = mBlock->mAlpha;
		mAlphas[0] = alphablock.mAlpha[0];
		mAlphas[1] = alphablock.mAlpha[1];

		if ( mAlphas[0] > mAlphas[1] )
		{
			// 8 alpha block
			for ( _dword i = 0; i <  6; i ++ )
				mAlphas[i + 2] = _word( ( ( 6 - i ) * mAlphas[0] + ( 1 + i ) * mAlphas[1] + 3 ) / 7 );
		}
		else 
		{
			// 6 alpha block
			for ( _dword i = 0; i <  4; i ++ )
				mAlphas[i + 2] = _word( ( ( 4 - i ) * mAlphas[0] + ( 1 + i ) * mAlphas[1] + 2 ) / 5 );

			mAlphas[6] = 0;
			mAlphas[7] = 0xFF;
		}
	}

	_void SetY( int y )
	{
		BaseClass::SetY( y );

		const DXTAlphaBlock3BitLinear &block = mBlock->mAlpha;

		int i = y / 2;

		mAlphaBits	= _word( block.mData[ i * 3 ] ) | ( _word( block.mData[ 1 + i * 3 ] ) << 8 ) | ( _word( block.mData[ 2 + i * 3 ] ) << 16 );
		mOffset		= ( y & 1 ) * 12;
	}

	_void GetColor( _dword x, _dword y, DXTColor8888& color )
	{
		BaseClass::GetColor( x, y, color );

		_word bits = ( mAlphaBits >> ( x * 3 + mOffset ) ) & 7;
		color.a = (_byte) mAlphas[ bits ];
	}
};

//----------------------------------------------------------------------------
// DecodeDXTBlock Implementation
//----------------------------------------------------------------------------

template< typename Type > 
_void DecodeDXTBlock( _byte* buffer, const _byte* block, _dword pitch, _dword width, _dword height )
{
	Type decoder;
	decoder.Setup( block );

	for ( _dword y = 0; y < height; y ++ )
	{
		decoder.SetY( y );

		_byte* address = buffer + y * pitch;
		for ( _dword x = 0; x < width; x ++, address += 4 )
			decoder.GetColor( x, y, (DXTColor8888&) *address );
	}
}

//----------------------------------------------------------------------------
// DDSFile Implementation
//----------------------------------------------------------------------------

DDSFile::DDSFile( )
{
	mCompressedImageSize	= 0;
	mCompressedImageBuffer	= _null;

	EGE_INIT( mDDSHeader );
}

DDSFile::~DDSFile( )
{
	Unload( );
}

_ubool DDSFile::LoadRGB( )
{
	// We only support the RGBA color mode
	if ( mDDSHeader.mSurfaceDesc.mPixelFormat.mRGBBitCount != 32 )
		return _false;

	// Get the DDS width and height
	_dword width	= mDDSHeader.mSurfaceDesc.mWidth;
	_dword height	= mDDSHeader.mSurfaceDesc.mHeight;
	
	// Create pixel buffer
	mImagePixelBuffer = new _byte[ width * height * 4 ];

	// Get the image pitch
	mImagePitch = mDDSHeader.mSurfaceDesc.mFlags & DDSSurfaceDesc::_DDSD_PITCH ? mDDSHeader.mSurfaceDesc.mPitchOrLinearSize : width * 4;

	// Read the image pixel buffer data
	for ( _dword i = 0; i < height; i ++ )
		EGE_MEM_CPY( mImagePixelBuffer + i * mImagePitch, mCompressedImageBuffer + i * mImagePitch, mImagePitch );

	return _true;
}

template< typename Type, typename BlockType >
_ubool DDSFile::LoadDXT( )
{
	// Get the DDS width and height
	_dword width		= mDDSHeader.mSurfaceDesc.mWidth;
	_dword height		= mDDSHeader.mSurfaceDesc.mHeight;
	// Get the DDS pitch
	_dword pitch		= width * 4;

	// Get the input line bytes
	_dword inputline	= ( width + 3 ) / 4;

	// Get the compressed image buffer address
	_byte* address		= mCompressedImageBuffer;

	// Create the decoder
	BlockType* blocks	= new BlockType[ inputline ];

	// Create the image pixel buffer
	mImagePixelBuffer	= new _byte[ pitch * height ];

	// Start to decode
	for ( _dword y = 0; y < height; y += 4, address += inputline * sizeof( BlockType ) )
	{
		EGE_MEM_CPY( blocks, address, inputline * sizeof( BlockType ) );

		_byte* source = (_byte*) blocks;
		_byte* target = mImagePixelBuffer + y * pitch;

		for ( _dword x = 0; x < width; x += 4 )
		{
			DecodeDXTBlock< Type >( target, source,	pitch, 4, 4 );

			source += Type::GetBytesPerBlock( );
			target += 4 * 4;
		}
	}

	delete[] blocks;

	return _true;
}

_FILE_FORMAT DDSFile::GetFileID( ) const
{
	return _FF_DDS;
}

_ubool DDSFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	// Read the DDS header
	stream_reader->ReadBuffer( &mDDSHeader, sizeof( DDSHeader ) );

	// Check the DDS file ID
	if ( mDDSHeader.mFileID != _FILE_ID )
		return _false;

	// The image size can't be too small
	if ( mDDSHeader.mSurfaceDesc.mWidth < 8 || mDDSHeader.mSurfaceDesc.mHeight < 8 )
		return _false;

	// Set the image info
	mImageWidth			= mDDSHeader.mSurfaceDesc.mWidth;
	mImageHeight		= mDDSHeader.mSurfaceDesc.mHeight;
	mImagePitch			= mImageWidth * 4;
	mImagePixelFormat	= _PF_A8R8G8B8;

	// Get the mip-maps factor
	_dword mipfactor = GetDXTVersion( ) == IDDSFile::_DXT_VERSION_1 ? 8 : 16;

	// The texture width and height
	_dword width	= mImageWidth;
	_dword height	= mImageHeight;

	// Here we manually load each mip map level of the image
	for ( _dword i = 0; i < mDDSHeader.mSurfaceDesc.mMipMapCount; i ++ )   
	{
		_dword mipsize = ( ( width + 3 ) / 4) * ( ( height + 3 ) / 4 ) * mipfactor;   

		// Half the image size for the next mip-map level
		width >>= 1; height >>= 1;

		// Move the offset to the next mip-map
		mCompressedImageSize += mipsize;
	}

	// Create the compressed image buffer
	mCompressedImageBuffer = new _byte[ mCompressedImageSize ];

	// Read the compressed image buffer
	stream_reader->ReadBuffer( mCompressedImageBuffer, mCompressedImageSize );

	return _true;
}

_void DDSFile::Unload( )
{
	EGE_DELETE_ARRAY( mCompressedImageBuffer );

	BaseClass::Unload( );
}

const _byte* DDSFile::DecodeImagePixel( )
{
	// Decode the pixel buffer
	if ( mImagePixelBuffer == _null )
	{
		// Get the pixel format flags
		_dword pixelformatflags = mDDSHeader.mSurfaceDesc.mPixelFormat.mFlags;

		// It's RGB DDS
		if ( pixelformatflags & DDSPixelFormat::_DDPF_RGB )
		{
			if ( LoadRGB( ) == _false )
				return _null;
		}
		// It's DXT DDS
		else if ( pixelformatflags & DDSPixelFormat::_DDPF_FOURCC )
		{
			_ubool result = _false;

			switch ( GetDXTVersion( ) )
			{
				case _DXT_VERSION_1: result = LoadDXT< DXT1BlockCoder, DXT1Block >( ); break;
				case _DXT_VERSION_3: result = LoadDXT< DXT3BlockCoder, DXT3Block >( ); break;
				case _DXT_VERSION_5: result = LoadDXT< DXT5BlockCoder, DXT5Block >( ); break;
                default:
                    break;
			}

			if ( result == _false )
				return _null;
		}

		// Set the image pixel format
		mImagePixelFormat = _PF_A8R8G8B8;
	}

	return mImagePixelBuffer;
}

IDDSFile::_DXT_VERSION DDSFile::GetDXTVersion( ) const
{
	switch ( mDDSHeader.mSurfaceDesc.mPixelFormat.mFourCC )
	{
		case EGE_ID( 'D', 'X', 'T', '1' ): return IDDSFile::_DXT_VERSION_1;
		case EGE_ID( 'D', 'X', 'T', '3' ): return IDDSFile::_DXT_VERSION_3;
		case EGE_ID( 'D', 'X', 'T', '5' ): return IDDSFile::_DXT_VERSION_5;
		default:
			return IDDSFile::_DXT_VERSION_UNKNOWN;
	}
}

_dword DDSFile::GetMipmapLevel( ) const
{
	return mDDSHeader.mSurfaceDesc.mMipMapCount;
}

const _byte* DDSFile::GetCompressedImageBuffer( ) const
{
	return mCompressedImageBuffer;
}