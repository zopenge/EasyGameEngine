//! @file     PSDFile.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// PSDFileHelper
//----------------------------------------------------------------------------

class PSDFileHelper
{
public:
	//!	Read the pascal string.
	static _ubool ReadPascalString( IStreamReader* stream_reader, WString& string, _ENCODING encoding );
};

//----------------------------------------------------------------------------
// PSDFileHeader
//----------------------------------------------------------------------------

class PSDFileHeader
{
private:
	_word	mVersion;  // Version number, always 1
	_word	mChannels; // Number of color channels (1-24) including alpha channels
	_dword	mHeight;   // Height of image in pixels (1-30000)
	_dword	mWidth;    // Width of image in pixels (1-30000)
	_word	mDepth;    // Number of bits per channel (1, 8, and 16)
	_word	mMode;     // Color mode

public:
	PSDFileHeader( );
	~PSDFileHeader( );

public:
	//!	Get the version.
	EGE_GET_ACCESSOR_CONST( _dword, Version )
	//!	Get the width and height.
	EGE_GET_ACCESSOR_CONST( _dword, Width )
	EGE_GET_ACCESSOR_CONST( _dword, Height )
	//!	Get the mode.
	EGE_GET_ACCESSOR_CONST( _dword, Mode )

public:
	//!	Read file header stream.
	//!	@param		stream_reader	The stream reader.
	//! @return		True indicates success, false indicates failure.
	_ubool ReadStream( IStreamReader* stream_reader );
};

//----------------------------------------------------------------------------
// PSDColorMode
//----------------------------------------------------------------------------

class PSDColorMode
{
private:
	_dword	mPaletteSize;
	_byte*	mPaletteBuffer;

public:
	PSDColorMode( );
	~PSDColorMode( );

public:
	//!	Read color mode stream.
	//!	@param		stream_reader	The stream reader.
	//! @return		True indicates success, false indicates failure.
	_ubool ReadStream( IStreamReader* stream_reader );
};

//----------------------------------------------------------------------------
// PSDImageResource
//----------------------------------------------------------------------------

class PSDImageResource
{
public:
	//!	The resource ID
	enum _RESOURCE_ID
	{
		_RESOURCE_ID_UNDEFINED						= 0,
		_RESOURCE_ID_MACPRINTINFO					= 1001,
		_RESOURCE_ID_RESOLUTIONINFO					= 1005,
		_RESOURCE_ID_ALPHACHANNELNAMES				= 1006,
		_RESOURCE_ID_DISPLAYINFO					= 1007,
		_RESOURCE_ID_CAPTION						= 1008,
		_RESOURCE_ID_BORDERINFO						= 1009,
		_RESOURCE_ID_BGCOLOR						= 1010,
		_RESOURCE_ID_PRINTFLAGS						= 1011,
		_RESOURCE_ID_MULTICHANNELHALFTONEINFO		= 1012,
		_RESOURCE_ID_COLORHALFTONEINFO				= 1013,
		_RESOURCE_ID_DUOTONEHALFTONEINFO			= 1014,
		_RESOURCE_ID_MULTICHANNELTRANSFERFUNCTIONS	= 1015,
		_RESOURCE_ID_COLORTRANSFERFUNCTIONS			= 1016,
		_RESOURCE_ID_DUOTONETRANSFERFUNCTIONS		= 1017,
		_RESOURCE_ID_DUOTONEIMAGEINFO				= 1018,
		_RESOURCE_ID_BLACKWHITERANGE				= 1019,
		_RESOURCE_ID_EPSOPTIONS						= 1021,
		_RESOURCE_ID_QUICKMASKINFO					= 1022, //2 bytes containing Quick Mask channel ID, 1 byte boolean indicating whether the mask was initially empty.
		_RESOURCE_ID_LAYERSTATEINFO					= 1024, //2 bytes containing the index of target layer. 0=bottom layer.
		_RESOURCE_ID_WORKINGPATHUNSAVED				= 1025,
		_RESOURCE_ID_LAYERSGROUPINFO				= 1026, //2 bytes per layer containing a group ID for the dragging groups. Layers in a group have the same group ID.
		_RESOURCE_ID_IPTC_NAA						= 1028,
		_RESOURCE_ID_RAWFORMATIMAGEMODE				= 1029,
		_RESOURCE_ID_JPEGQUALITY					= 1030,
		_RESOURCE_ID_GRIDGUIDESINFO					= 1032,
		_RESOURCE_ID_THUMBNAIL1						= 1033,
		_RESOURCE_ID_COPYRIGHTINFO					= 1034,
		_RESOURCE_ID_URL							= 1035,
		_RESOURCE_ID_THUMBNAIL2						= 1036,
		_RESOURCE_ID_GLOBALANGLE					= 1037,
		_RESOURCE_ID_COLORSAMPLERS					= 1038,
		_RESOURCE_ID_ICCPROFILE						= 1039, //The raw bytes of an ICC format profile, see the ICC34.pdf and ICC34.h files from the Internation Color Consortium located in the documentation section
		_RESOURCE_ID_WATERMARK						= 1040,
		_RESOURCE_ID_ICCUNTAGGED					= 1041, //1 byte that disables any assumed profile handling when opening the file. 1 = intentionally untagged.
		_RESOURCE_ID_EFFECTSVISIBLE					= 1042, //1 byte global flag to show/hide all the effects layer. Only present when they are hidden.
		_RESOURCE_ID_SPOTHALFTONE					= 1043, // 4 bytes for version, 4 bytes for length, and the variable length data.
		_RESOURCE_ID_DOCUMENTSPECIFIC				= 1044,
		_RESOURCE_ID_UNICODEALPHANAMES				= 1045, // 4 bytes for length and the string as a UNICODE string
		_RESOURCE_ID_INDEXEDCOLORTABLECOUNT			= 1046, // 2 bytes for the number of colors in table that are actually defined
		_RESOURCE_ID_TRANSPARENTINDEX				= 1047,
		_RESOURCE_ID_GLOBALALTITUDE					= 1049,  // 4 byte entry for altitude
		_RESOURCE_ID_SLICES							= 1050,
		_RESOURCE_ID_WORKFLOWURL					= 1051, //Unicode string, 4 bytes of length followed by UNICODE string
		_RESOURCE_ID_JUMPTOXPEP						= 1052, //2 bytes major version, 2 bytes minor version, //4 bytes count. Following is repeated for count: 4 bytes block size, //4 bytes key, if key = 'jtDd' then next is a Boolean for the dirty flag //otherwise it’s a 4 byte entry for the mod date
		_RESOURCE_ID_ALPHAIDENTIFIERS				= 1053, //4 bytes of length, followed by 4 bytes each for every alpha identifier.
		_RESOURCE_ID_URLLIST						= 1054, //4 byte count of URLs, followed by 4 byte long, 4 byte ID, and UNICODE string for each count.
		_RESOURCE_ID_VERSIONINFO					= 1057, //4 byte version, 1 byte HasRealMergedData, UNICODE string of writer name, UNICODE string of reader name, 4 bytes of file version.
		_RESOURCE_ID_UNKNOWN4						= 1058, //pretty long, 302 bytes in one file. Holds creation date, maybe Photoshop license number
		_RESOURCE_ID_XMLINFO 						= 1060, //some kind of XML definition of file. The xpacket tag seems to hold binary data
		_RESOURCE_ID_UNKNOWN 						= 1061, //seems to be common!
		_RESOURCE_ID_UNKNOWN2 						= 1062, //seems to be common!
		_RESOURCE_ID_UNKNOWN3 						= 1064, //seems to be common!
		_RESOURCE_ID_PATHINFO 						= 2000, //2000-2999 actually I think?
		_RESOURCE_ID_CLIPPINGPATHNAME				= 2999,
		_RESOURCE_ID_PRINTFLAGSINFO					= 10000
	};

private:
	_word	mResourceID;
	_word	mReserved;
	_dword	mResourceSize;
	WString	mResourceName;

public:
	PSDImageResource( );
	~PSDImageResource( );

public:
	//!	Read image resource stream.
	//!	@param		stream_reader	The stream reader.
	//!	@param		bytes			The image resource bytes.
	//! @return		True indicates success, false indicates failure.
	_ubool ReadStream( IStreamReader* stream_reader, _dword& bytes );
};

//----------------------------------------------------------------------------
// PSDImageResources
//----------------------------------------------------------------------------

class PSDImageResources
{
private:
	typedef Array< PSDImageResource > ImageResourceArray;

private:
	ImageResourceArray	mImageResources;

public:
	PSDImageResources( );
	~PSDImageResources( );

public:

public:
	//!	Read image resources stream.
	//!	@param		stream_reader	The stream reader.
	//! @return		True indicates success, false indicates failure.
	_ubool ReadStream( IStreamReader* stream_reader );
};

//----------------------------------------------------------------------------
// PSDBlendingRanges
//----------------------------------------------------------------------------

class PSDBlendingRanges
{
private:
	_dword	mBufferSize;
	_byte*	mBuffer;

public:
	PSDBlendingRanges( );
	~PSDBlendingRanges( );

public:
	//!	Operator functions.
	PSDBlendingRanges& operator = ( const PSDBlendingRanges& blendingranges );

	//!	Read blending ranges stream.
	//!	@param		stream_reader	The stream reader.
	//! @return		True indicates success, false indicates failure.
	_ubool ReadStream( IStreamReader* stream_reader );
};

//----------------------------------------------------------------------------
// PSDAdjustmentLayer
//----------------------------------------------------------------------------

class PSDAdjustmentLayer
{
private:
	_dword	mKey;
	_dword	mBufferSize;
	_byte*	mBuffer;

public:
	PSDAdjustmentLayer( );
	~PSDAdjustmentLayer( );

public:
	//!	Operator functions.
	PSDAdjustmentLayer& operator = ( const PSDAdjustmentLayer& adjustmentlayer );

	//!	Read adjustment layer stream.
	//!	@param		stream_reader	The stream reader.
	//! @return		True indicates success, false indicates failure.
	_ubool ReadStream( IStreamReader* stream_reader );
};

//----------------------------------------------------------------------------
// PSDMask
//----------------------------------------------------------------------------

class PSDMask
{
private:
	RectI	mRegion;

public:
	PSDMask( );
	~PSDMask( );

public:
	//!	Read mask stream.
	//!	@param		stream_reader	The stream reader.
	//! @return		True indicates success, false indicates failure.
	_ubool ReadStream( IStreamReader* stream_reader );
};

//----------------------------------------------------------------------------
// PSDChannel
//----------------------------------------------------------------------------

class PSDChannel
{
private:
	_word	mID;
	_word	mReserved;
	_dword	mSize;

public:
	PSDChannel( );
	~PSDChannel( );

public:
	//!	Get ID and size.
	EGE_GET_ACCESSOR_CONST( _dword, ID )
	EGE_GET_ACCESSOR_CONST( _dword, Size )

public:
	//!	Read channel stream.
	//!	@param		stream_reader	The stream reader.
	//! @return		True indicates success, false indicates failure.
	_ubool ReadStream( IStreamReader* stream_reader );
};

//----------------------------------------------------------------------------
// PSDLayer
//----------------------------------------------------------------------------

class PSDLayer
{
protected:
	RectI						mRegion;
	WString						mName;
	PSDMask						mMask;
	PSDBlendingRanges			mBlendingRanges;
	Array< PSDAdjustmentLayer >	mAdjustmentLayers;
	Array< PSDChannel >			mChannels;

	_dword						mPixelBytes;
	_byte*						mPixelBuffer; // ARGB color buffer

public:
	PSDLayer( );
	~PSDLayer( );

public:
	//!	Get region.
	EGE_GET_ACCESSOR_CONST( RectI, Region )
	//!	Get name.
	EGE_GET_ACCESSOR_CONST( WString, Name )
	//!	Get pixel buffer.
	EGE_GET_ACCESSOR_CONST( const _byte*, PixelBuffer )

public:
	//!	Operator functions.
	PSDLayer& operator = ( const PSDLayer& layer );

public:
	//!	Read layer info.
	//!	@param		stream_reader	The stream reader.
	//! @return		True indicates success, false indicates failure.
	_ubool ReadLayoutInfo( IStreamReader* stream_reader );
	//!	Read layer pixel.
	//!	@param		stream_reader	The stream reader.
	//! @return		True indicates success, false indicates failure.
	_ubool ReadLayoutPixel( IStreamReader* stream_reader );
};

//----------------------------------------------------------------------------
// PSDLayers
//----------------------------------------------------------------------------

class PSDLayers
{
private:
	Array< PSDLayer > mLayers;

public:
	PSDLayers( );
	~PSDLayers( );

public:
	//!	Get the layers number.
	//!	@param		none.
	//!	@return		The number of layers.
	_dword GetLayerNumber( ) const;
	//!	Get the layer by index.
	//!	@param		index		The layer index.
	//!	@return		The layer info.
	const PSDLayer* GetLayerByIndex( _dword index ) const;

	//!	Read layers stream.
	//!	@param		stream_reader	The stream reader.
	//! @return		True indicates success, false indicates failure.
	_ubool ReadStream( IStreamReader* stream_reader );
};

//----------------------------------------------------------------------------
// PSDFile
//----------------------------------------------------------------------------

class PSDFile : public INTERFACE_IMAGEFILE_IMPL( IPSDFile )
{
public:
	//!	The PSD file ID
	enum { _FILE_ID = EGE_ID( '8', 'B', 'P', 'S' ) };

private:
	typedef INTERFACE_IMAGEFILE_IMPL( IPSDFile ) BaseClass;

private:
	PSDFileHeader		mFileHeader;
	PSDColorMode		mColorMode;
	PSDImageResources	mImageResources;
	PSDLayers			mLayers;

private:
	//!	Decode pixel buffer and combine all layers into one pixel buffer.
	_ubool DecodePixelBuffer( );

public:
	PSDFile( );
	virtual ~PSDFile( );

// IBaseFile Interface
public:
	virtual _FILE_FORMAT	GetFileID( ) const override;

	virtual _ubool 			LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 			Unload( ) override;

// IPSDFile Interface
public:
	virtual _MODE			GetMode( ) const override;

	virtual _dword			GetLayerNumber( ) const override;
	virtual _ubool			GetLayerByIndex( _dword index, LayerData& layer ) const override;
};

}