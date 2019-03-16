//! @file     DDSFile.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// DDSPixelFormat
//----------------------------------------------------------------------------

struct DDSPixelFormat
{
	// DirectDraw PixelFormat Flags
	enum _DDPF
	{
		_DDPF_ALPHAPIXELS	= 0x00000001, // Surface has alpha channel
		_DDPF_ALPHA			= 0x00000002, // Alpha only
		_DDPF_FOURCC		= 0x00000004, // FOURCC available
		_DDPF_RGB			= 0x00000040, // RGB(A) bitmap
	};

	_dword 	mSize;			// Size of this structure (must be 32)
	_dword 	mFlags;			// See _DDPF_*
	_dword 	mFourCC;
	_dword 	mRGBBitCount;	// Total number of bits for RGB formats
	_dword 	mRBitMask;
	_dword 	mGBitMask;
	_dword 	mBBitMask;
	_dword 	mRGBAlphaBitMask;
};

//----------------------------------------------------------------------------
// DDSCaps
//----------------------------------------------------------------------------

struct DDSCaps
{
	// DirectDrawSurface Capability1 Flags
	enum _DDSCAPS1
	{
		_DDSCAPS1_ALPHA				= 0x00000002, // Alpha only surface
		_DDSCAPS1_COMPLEX			= 0x00000008, // Complex surface structure
		_DDSCAPS1_TEXTURE			= 0x00001000, // Used as texture (should always be set)
		_DDSCAPS1_MIPMAP			= 0x00400000, // Mipmap present
	};

	// DirectDrawSurface Capability2 Flags
	enum _DDSCAPS2
	{
		_DDSCAPS2_CUBEMAP			= 0x00000200,
		_DDSCAPS2_CUBEMAP_POSITIVEX	= 0x00000400,
		_DDSCAPS2_CUBEMAP_NEGATIVEX	= 0x00000800,
		_DDSCAPS2_CUBEMAP_POSITIVEY	= 0x00001000,
		_DDSCAPS2_CUBEMAP_NEGATIVEY	= 0x00002000,
		_DDSCAPS2_CUBEMAP_POSITIVEZ	= 0x00004000,
		_DDSCAPS2_CUBEMAP_NEGATIVEZ	= 0x00008000,
		_DDSCAPS2_VOLUME			= 0x00200000,
	};

	_dword 	mCaps1;			// Zero or more of the _DDSCAPS_* members
	_dword 	mCaps2;			// Zero or more of the _DDSCAPS2_* members
	_dword	mReserved[2];
};

//----------------------------------------------------------------------------
// DDSSurfaceDesc
//----------------------------------------------------------------------------

struct DDSSurfaceDesc
{
	// DirectDrawSurface Description Flags
	enum _DDSD
	{
		_DDSD_CAPS			= 0x00000001,
		_DDSD_HEIGHT		= 0x00000002,
		_DDSD_WITH			= 0x00000004,
		_DDSD_PITCH			= 0x00000008,
		_DDSD_ALPHABITDEPTH = 0x00000080,
		_DDSD_PIXELFORMAT	= 0x00001000,
		_DDSD_MIPMAPCOUNT	= 0x00020000,
		_DDSD_LINEARSIZE	= 0x00080000,
		_DDSD_DEPTH			= 0x00800000,
	};

	_dword			mSize;				// Size of this structure (must be 124)
	_dword			mFlags;				// Combination of the _DDSS_* flags
	_dword			mHeight;
	_dword			mWidth;
	_dword			mPitchOrLinearSize;
	_dword			mDepth;				// Depth of a volume texture
	_dword			mMipMapCount;
	_dword			mReserved1[11];
	DDSPixelFormat	mPixelFormat;
	DDSCaps			mCaps;
	_dword			mReserved;
};

//----------------------------------------------------------------------------
// DDSHeader
//----------------------------------------------------------------------------

struct DDSHeader
{
	_dword			mFileID;
	DDSSurfaceDesc	mSurfaceDesc;
};

//----------------------------------------------------------------------------
// DDSFile
//----------------------------------------------------------------------------

class DDSFile : public INTERFACE_COMPRESSEDTEXFILE_IMPL( IDDSFile )
{
public:
	//!	The DDS file ID
	enum { _FILE_ID = EGE_ID( 'D', 'D', 'S', ' ' ) };

private:
	typedef INTERFACE_COMPRESSEDTEXFILE_IMPL( IDDSFile ) BaseClass;

private:
	//!	The compressed image buffer size
	_dword		mCompressedImageSize;
	//!	The compressed image buffer data
	_byte*		mCompressedImageBuffer;

	//!	The *.DDS file header
	DDSHeader	mDDSHeader;

private:
	//!	Load RGB DDS.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	_ubool LoadRGB( );
	//!	Load DXT DDS.
	//!	@param		version		The DXT version.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	template< typename Type, typename BlockType >
	_ubool LoadDXT( );

public:
	DDSFile( );
	virtual ~DDSFile( );
	
// IBaseFile Interface
public:
	virtual _FILE_FORMAT	GetFileID( ) const override;

	virtual _ubool 			LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 			Unload( ) override;

// ICompressedTexFile Interface
public:
	virtual const _byte*	DecodeImagePixel( ) override;

// IDDSFile Interface
public:
	virtual _DXT_VERSION	GetDXTVersion( ) const override;
	virtual _dword			GetMipmapLevel( ) const override;

	virtual const _byte*	GetCompressedImageBuffer( ) const override;
};

}