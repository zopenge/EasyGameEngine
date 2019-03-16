//! @file     PSDFile.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// PSDFileHelper Implementation
//----------------------------------------------------------------------------

_ubool PSDFileHelper::ReadPascalString( IStreamReader* stream_reader, WString& string, _ENCODING encoding )
{
	// Get the string length
	_byte string_length;
	stream_reader->ReadByte( string_length );

	// Read the string
	if ( string_length != 0 )
	{
		// Read the string 
		MemArrayPtr< _chara > name_buffer( string_length + 1 );
		stream_reader->ReadBuffer( name_buffer, string_length );

		name_buffer[ string_length ] = 0;

		// Convert string to UNICODE
		string.FromString( encoding, (const _chara*) name_buffer );
	}
	else
	{
		string = L"";
	}

	return _true;
}

//----------------------------------------------------------------------------
// PSDFileHeader Implementation
//----------------------------------------------------------------------------

PSDFileHeader::PSDFileHeader( )
{
	mVersion	= 0;
	mChannels	= 0;
	mHeight		= 0;
	mWidth		= 0;
	mDepth		= 0;
	mMode		= 0;
}

PSDFileHeader::~PSDFileHeader( )
{

}

_ubool PSDFileHeader::ReadStream( IStreamReader* stream_reader )
{
	// Read file ID
	_dword fileid = 0;
	stream_reader->ReadDword( fileid );
	
	// Check file ID
	if ( fileid != Math::BSwap32( PSDFile::_FILE_ID ) )
		return _false;

	// Read version
	stream_reader->ReadWord( mVersion );

	// Jump the reserved bytes
	stream_reader->Seek( _SEEK_CURRENT, 6 );

	// Read channels number
	stream_reader->ReadWord( mChannels );

	if ( mChannels == 0 )
		return _false;

	// Read width and height
	stream_reader->ReadDword( mWidth );
	stream_reader->ReadDword( mHeight );

	if ( mWidth == 0 || mHeight == 0 )
		return _false;

	// Read color depth
	stream_reader->ReadWord( mDepth );

	if ( mDepth == 0 )
		return _false;

	// Read color mode
	stream_reader->ReadWord( mMode );

	return _true;
}

//----------------------------------------------------------------------------
// PSDColorMode Implementation
//----------------------------------------------------------------------------

PSDColorMode::PSDColorMode( )
{
	mPaletteSize	= 0;
	mPaletteBuffer	= _null;
}

PSDColorMode::~PSDColorMode( )
{
	EGE_DELETE_ARRAY( mPaletteBuffer );
}

_ubool PSDColorMode::ReadStream( IStreamReader* stream_reader )
{
	// Read the palette size
	stream_reader->ReadDword( mPaletteSize );

	// Read the palette buffer
	if ( mPaletteSize > 0 )
	{
		mPaletteBuffer = new _byte[ mPaletteSize ];
		stream_reader->ReadBuffer( mPaletteBuffer, mPaletteSize );
	}

	return _true;
}

//----------------------------------------------------------------------------
// PSDImageResource Implementation
//----------------------------------------------------------------------------

PSDImageResource::PSDImageResource( )
{
	mResourceID		= 0;
	mReserved		= 0;
	mResourceSize	= 0;
}

PSDImageResource::~PSDImageResource( )
{

}

_ubool PSDImageResource::ReadStream( IStreamReader* stream_reader, _dword& bytes )
{
	// Get the current offset to calculate the resource size
	_dword offset = stream_reader->GetOffset( );

	// Read the resource type 
	_dword resourcetype;
	stream_reader->ReadDword( resourcetype );

	// Check the resource type
	if ( resourcetype != EGE_ID( 'M', 'I', 'B', '8' ) )
		return _false;

	// Read the resource ID
	_word resourceid;
	stream_reader->ReadWord( resourceid );

	// Read the resource name
	if ( PSDFileHelper::ReadPascalString( stream_reader, mResourceName, _ENCODING_UTF8 ) == _false )
		return _false;

	if ( ( mResourceName.GetLength( ) % 2 ) == 0 )
		stream_reader->Seek( _SEEK_CURRENT, 1 );

	// Read the resource size
	stream_reader->ReadDword( mResourceSize );

	if ( mResourceSize % 2 )
		mResourceSize ++;

	// Read resource data
	switch ( mResourceID )
	{
		case _RESOURCE_ID_RESOLUTIONINFO:
		{

		}
		break;

		default:
		{
			stream_reader->Seek( _SEEK_CURRENT, mResourceSize );
		}
		break;
	}

	// Feedback the resource size
	bytes = stream_reader->GetOffset( ) - offset;

	return _true;
}

//----------------------------------------------------------------------------
// PSDImageResources Implementation
//----------------------------------------------------------------------------

PSDImageResources::PSDImageResources( )
{
}

PSDImageResources::~PSDImageResources( )
{

}

_ubool PSDImageResources::ReadStream( IStreamReader* stream_reader )
{
	// Read the image resources size
	_dword imageresourcesize;
	stream_reader->ReadDword( imageresourcesize );

	// Read the image resources
	_dword totalbytes = 0;
	while ( totalbytes < imageresourcesize )
	{
		_dword bytes = 0;

		// Read the image resource
		PSDImageResource imageresource;
		if ( imageresource.ReadStream( stream_reader, bytes ) == _false )
			return _false;

		// Append it into array
		mImageResources.Append( imageresource );

		// Update the total bytes
		totalbytes += bytes;
	}

	return _true;
}

//----------------------------------------------------------------------------
// PSDBlendingRanges Implementation
//----------------------------------------------------------------------------

PSDBlendingRanges::PSDBlendingRanges( )
{
	mBufferSize	= 0;
	mBuffer		= _null;
}

PSDBlendingRanges::~PSDBlendingRanges( )
{
	Memory::GetInstance( ).ReleaseReferencedBuffer( mBuffer );
}

PSDBlendingRanges& PSDBlendingRanges::operator = ( const PSDBlendingRanges& blendingranges )
{
	Memory::GetInstance( ).ReleaseReferencedBuffer( mBuffer );

	mBufferSize = blendingranges.mBufferSize;
	mBuffer		= (_byte*) Memory::GetInstance( ).ReserveReferencedBuffer( blendingranges.mBuffer );

	return *this;
}

_ubool PSDBlendingRanges::ReadStream( IStreamReader* stream_reader )
{
	// Read the buffer size
	stream_reader->ReadDword( mBufferSize );

	// Allocate and read the buffer
	mBuffer = (_byte*) Memory::GetInstance( ).CreateReferencedBuffer( mBufferSize );
	stream_reader->ReadBuffer( mBuffer, mBufferSize );

	return _true;
}

//----------------------------------------------------------------------------
// PSDAdjustmentLayer Implementation
//----------------------------------------------------------------------------

PSDAdjustmentLayer::PSDAdjustmentLayer( )
{
	mKey		= 0;
	mBufferSize	= 0;
	mBuffer		= _null;
}

PSDAdjustmentLayer::~PSDAdjustmentLayer( )
{
	Memory::GetInstance( ).ReleaseReferencedBuffer( mBuffer );
}

PSDAdjustmentLayer& PSDAdjustmentLayer::operator = ( const PSDAdjustmentLayer& adjustmentlayer )
{
	Memory::GetInstance( ).ReleaseReferencedBuffer( mBuffer );

	mKey		= adjustmentlayer.mKey;
	mBufferSize = adjustmentlayer.mBufferSize;
	mBuffer		= (_byte*) Memory::GetInstance( ).ReserveReferencedBuffer( adjustmentlayer.mBuffer );

	return *this;
}

_ubool PSDAdjustmentLayer::ReadStream( IStreamReader* stream_reader )
{
	// Check the signature
	_dword signature;
	stream_reader->ReadDword( signature );
	
	if ( signature != EGE_ID( 'M', 'I', 'B', '8' ) )
		return _false;

	// Read the key
	stream_reader->ReadDword( mKey );

	// Read the buffer size
	stream_reader->ReadDword( mBufferSize );

	// Allocate and read the buffer
	mBuffer = (_byte*) Memory::GetInstance( ).CreateReferencedBuffer( mBufferSize );
	stream_reader->ReadBuffer( mBuffer, mBufferSize );

	return _true;
}

//----------------------------------------------------------------------------
// PSDMask Implementation
//----------------------------------------------------------------------------

PSDMask::PSDMask( )
{
	mRegion = RectI::cNull;
}

PSDMask::~PSDMask( )
{
}

_ubool PSDMask::ReadStream( IStreamReader* stream_reader )
{
	// Read the mask size
	_dword size;
	stream_reader->ReadDword( size );

	// Check the mask size
	if ( size == 0 )
		return _true;

	// Read layer's region
	stream_reader->ReadLong( mRegion.t );
	stream_reader->ReadLong( mRegion.l );
	stream_reader->ReadLong( mRegion.b );
	stream_reader->ReadLong( mRegion.r );

	// Skip the reserved bytes
	stream_reader->Seek( _SEEK_CURRENT, size - sizeof( RectI ) );

	return _true;
}

//----------------------------------------------------------------------------
// PSDChannel Implementation
//----------------------------------------------------------------------------

PSDChannel::PSDChannel( )
{
	mID			= 0;
	mReserved	= 0;
	mSize		= 0;
}

PSDChannel::~PSDChannel( )
{
}

_ubool PSDChannel::ReadStream( IStreamReader* stream_reader )
{
	// Read channel ID
	stream_reader->ReadWord( mID );

	// Read channel size
	stream_reader->ReadDword( mSize );

	return _true;
}

//----------------------------------------------------------------------------
// PSDLayer Implementation
//----------------------------------------------------------------------------

PSDLayer::PSDLayer( )
{
	mRegion			= RectI::cNull;

	mPixelBytes		= 0;
	mPixelBuffer	= _null;
}

PSDLayer::~PSDLayer( )
{
	Memory::GetInstance( ).ReleaseReferencedBuffer( mPixelBuffer );
}

PSDLayer& PSDLayer::operator = ( const PSDLayer& layer )
{
	Memory::GetInstance( ).ReleaseReferencedBuffer( mPixelBuffer );

	mRegion			= layer.mRegion;
	mName			= layer.mName;
	mChannels		= layer.mChannels;
	mPixelBytes		= layer.mPixelBytes;
	mPixelBuffer	= (_byte*) Memory::GetInstance( ).ReserveReferencedBuffer( layer.mPixelBuffer );

	return *this;
}

_ubool PSDLayer::ReadLayoutInfo( IStreamReader* stream_reader )
{
	// Read layer's region
	stream_reader->ReadLong( mRegion.t );
	stream_reader->ReadLong( mRegion.l );
	stream_reader->ReadLong( mRegion.b );
	stream_reader->ReadLong( mRegion.r );

	// Read layer's channels number
	_word channelsnumber;
	stream_reader->ReadWord( channelsnumber );
	
	if ( channelsnumber == 0 )
		return _false;

	// Read each channel's id and length of layer
	for ( _dword i = 0; i < channelsnumber; i ++ )
	{
		PSDChannel channel;
		if ( channel.ReadStream( stream_reader ) == _false )
			return _false;

		mChannels.Append( channel );
	}

	// Skip the reserved bytes
	stream_reader->Seek( _SEEK_CURRENT, 12 );

	// Read the extra data size
	_dword extra_size;
	stream_reader->ReadDword( extra_size );

	// Remember the start position for calculation of the AdjustmenLayerInfo size
	_dword extra_offset = stream_reader->GetOffset( );

	// Read the mask stream
	if ( mMask.ReadStream( stream_reader ) == _false )
		return _false;

	// Read the blending ranges
	if ( mBlendingRanges.ReadStream( stream_reader ) == _false )
		return _false;

	// Backup the position for calculate the padding bytes of name
	_dword name_offset = stream_reader->GetOffset( );

	// Read name string
	if ( PSDFileHelper::ReadPascalString( stream_reader, mName, _ENCODING_ANSI ) == _false )
		return _false;

	// Get the name string bytes
	_dword name_bytes = stream_reader->GetOffset( ) - name_offset;

	// Skip padding bytes after name
	_dword paddingbytes = Math::UpperArrange( name_bytes, 4 ) - name_bytes;
	stream_reader->Seek( _SEEK_CURRENT, paddingbytes );

	// Read the adjustment layer stream
	while ( stream_reader->GetOffset( ) < extra_offset + extra_size )
	{
		PSDAdjustmentLayer layer;
		if ( layer.ReadStream( stream_reader ) == _false )
			return _false;

		mAdjustmentLayers.Append( layer );
	}

	return _true;
}

_ubool PSDLayer::ReadLayoutPixel( IStreamReader* stream_reader )
{
	// Get the length of layer, it allows empty layer without any pixels
	_dword length = mRegion.GetWidth( ) * mRegion.GetHeight( );
	if ( length == 0 )
	{
		// We don't have any pixels info, so just jump the layer blocks
		_dword size = 0;
		for ( _dword i = 0; i < mChannels.Number( ); i ++ )
			size += mChannels[i].GetSize( );

		stream_reader->Seek( _SEEK_CURRENT, size );
	}
	else
	{
		// Calculate the pixel buffer bytes
		mPixelBytes = length * sizeof( _dword );
		EGE_ASSERT( mPixelBytes != 0 );

		// Allocate the pixel buffer
		mPixelBuffer = (_byte*) Memory::GetInstance( ).CreateReferencedBuffer( mPixelBytes );
		if ( mPixelBuffer == _null )
			return _false;

		// Fill white color to pixel buffer
		EGE_MEM_SET( mPixelBuffer, 0xFF, mPixelBytes );

		// Each channel of layer
		for ( _dword i = 0; i < mChannels.Number( ); i ++ )
		{
			const PSDChannel& channel = mChannels[i];

			// Get the pixel buffer address by channel format
			_byte* pixelbuffer = _null;
			switch ( channel.GetID( ) )
			{
				case 0xFFFF: pixelbuffer = mPixelBuffer + 3; break; // Alpha
				case 0:      pixelbuffer = mPixelBuffer + 2; break; // Red
				case 1:      pixelbuffer = mPixelBuffer + 1; break; // Green
				case 2:      pixelbuffer = mPixelBuffer; break;		// Blue
				default:
					return _false;
			}

			// Read RLE compression flag
			_word rleflag;
			stream_reader->ReadWord( rleflag );

			// RLE decoding
			if ( rleflag )
			{
				// Jump bytes number of each line
				stream_reader->Seek( _SEEK_CURRENT, mRegion.GetHeight( ) * sizeof( _word ) );

				_dword index = 0; 
				while ( index < length )
				{
					_byte len = 0;
					stream_reader->ReadByte( len );

					if ( len == 128 )
						continue;

					if ( len < 128 )
					{
						for ( len ++ ; len ; len --, index ++, pixelbuffer += sizeof( _dword ) )
							stream_reader->ReadByte( *pixelbuffer );
					}
					else
					{
						_byte code = 0;
						stream_reader->ReadByte( code );

						for ( len = 257 - len; len ; len --, index ++, pixelbuffer += sizeof( _dword ) )
							*pixelbuffer = code;
					}
				}
			}
			// No RLE decoding
			else
			{
				for ( _dword index = 0; index < length; index ++, pixelbuffer += sizeof( _dword ) )
					stream_reader->ReadByte( *pixelbuffer );
			}
		}
	}

	return _true;
}

//----------------------------------------------------------------------------
// PSDLayers Implementation
//----------------------------------------------------------------------------

PSDLayers::PSDLayers( )
{

}

PSDLayers::~PSDLayers( )
{

}

_dword PSDLayers::GetLayerNumber( ) const
{
	return mLayers.Number( );
}

const PSDLayer* PSDLayers::GetLayerByIndex( _dword index ) const
{
	if ( index >= mLayers.Number( ) )
		return _null;

	return &mLayers[ index ];
}

_ubool PSDLayers::ReadStream( IStreamReader* stream_reader )
{
	// Jump the reserved bytes
	stream_reader->Seek( _SEEK_CURRENT, 8 );

	// Load layers number
	_word layersnumber;
	stream_reader->ReadWord( layersnumber );
	
	if ( layersnumber == 0 )
		return _false;

	// Load all layers info
	for ( _int i = 0; i < layersnumber; i ++ )
	{
		PSDLayer layer;
		if ( layer.ReadLayoutInfo( stream_reader ) == _false )
			return _false;

		mLayers.Append( layer );
	}

	// Load all layers pixel buffer info
	for ( _dword i = 0; i < mLayers.Number( ); i ++ )
	{
		if ( mLayers[i].ReadLayoutPixel( stream_reader ) == _false )
			return _false;
	}

	return _true;
}

//----------------------------------------------------------------------------
// PSDFile Implementation
//----------------------------------------------------------------------------

PSDFile::PSDFile( )
{
}

PSDFile::~PSDFile( )
{
	Unload( );
}

_ubool PSDFile::DecodePixelBuffer( )
{
	// Create image pixel buffer ( RGBA mode )
	mImagePixelBuffer = new _byte[ mImageWidth * mImageHeight * sizeof( _dword ) ];
	EGE_MEM_CPY( mImagePixelBuffer, mLayers.GetLayerByIndex( 0 )->GetPixelBuffer( ), mImageWidth * mImageHeight * sizeof( _dword ) );

	// Blend the image pixel by layers
	for ( _dword i = 1; i < mLayers.GetLayerNumber( ); i ++ )
	{
		const PSDLayer* psd_layer = mLayers.GetLayerByIndex( i );
		EGE_ASSERT( psd_layer != _null );

		// Skip for empty layer
		if ( psd_layer->GetPixelBuffer( ) == _null )
			continue;

		// Get the region of PSD layer
		const RectI& psd_region = psd_layer->GetRegion( );

		// Limit the layer region
		RectI region = RectI::Intersect( psd_region, RectI( ).InitWithSize( 0, 0, mImageWidth, mImageHeight ) );

		// Build the target and source image info
		BitmapInfo des_image_info( _PF_A8R8G8B8, 4, mImagePitch, mImageWidth, mImageHeight, mImagePixelBuffer );
		BitmapInfoReadOnly src_image_info( _PF_A8R8G8B8, 4, psd_region.GetWidth( ) * 4, psd_region.GetWidth( ), psd_region.GetHeight( ), (_byte*) psd_layer->GetPixelBuffer( ) );

		// Perform alpha blending by channel
		GetImageProcessor( )->AlphaBlending( des_image_info, src_image_info, region, RectI( ).InitWithSize( 0, 0, psd_region.GetWidth( ), psd_region.GetHeight( ) ), 1.0f );
	}

	return _true;
}

_FILE_FORMAT PSDFile::GetFileID( ) const
{
	return _FF_PSD;
}

_ubool PSDFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	// PSD file stream is encode in big endian mode always
	stream_reader->SetEndian( _ENDIAN_BIG );

	// Read the file header stream
	if ( mFileHeader.ReadStream( stream_reader ) == _false )
		return _false;

	// We only support the RGB color mode
	if ( mFileHeader.GetMode( ) != _MODE_RGB_COLOR ) 
		return _false;

	// Read the color mode stream
	if ( mColorMode.ReadStream( stream_reader ) == _false )
		return _false;

	// Read the image resources stream
	if ( mImageResources.ReadStream( stream_reader ) == _false )
		return _false;

	// Read the layers
	if ( mLayers.ReadStream( stream_reader ) == _false )
		return _false;

	// Set image information
	mImageWidth			= mFileHeader.GetWidth( );
	mImageHeight		= mFileHeader.GetHeight( );
	mImagePitch			= mImageWidth * sizeof( _dword );
	mImagePixelFormat	= _PF_A8R8G8B8;

	// Check whether decode pixel buffer
	if ( HasFlags( _FLAG_HEADER_ONLY ) == _false )
	{
		// Combine all layers into one layer as image pixel buffer info
		if ( DecodePixelBuffer( ) == _false )
			return _false;
	}

	return _true;
}

_void PSDFile::Unload( )
{
	BaseClass::Unload( );
}

IPSDFile::_MODE PSDFile::GetMode( ) const
{
	return (_MODE) mFileHeader.GetMode( );
}

_dword PSDFile::GetLayerNumber( ) const
{
	return mLayers.GetLayerNumber( );
}

_ubool PSDFile::GetLayerByIndex( _dword index, LayerData& layer ) const
{
	const PSDLayer* psd_layer = mLayers.GetLayerByIndex( index );
	if ( psd_layer == _null )
		return _false;

	layer.mRegion		= psd_layer->GetRegion( );
	layer.mName			= psd_layer->GetName( );
	layer.mPixelBuffer	= psd_layer->GetPixelBuffer( );

	return _true;
}