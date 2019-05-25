//! @file     PVRTexFile.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// PVRTexFile
//----------------------------------------------------------------------------

class PVRTexFile : public INTERFACE_COMPRESSEDTEXFILE_IMPL( IPVRTCFile )
{
public:
	//!	The KTX file ID
	enum { _FILE_ID = EGE_ID( 'P', 'V', 'R', 3 ) };

private:
	typedef INTERFACE_COMPRESSEDTEXFILE_IMPL( IPVRTCFile ) BaseClass;

private:
	//!	The header info
	PVRTexHeaderInfo	mHeaderInfo;

private:
	//!	Get the GL compressed image type.
	static _dword GetGLCompressedImageType( _qword pixel_format );
	//!	Get the compressed pixel format.
	static _PIXEL_FORMAT GetCompressedPixelFormat( _qword pixel_format );

	//!	Get the bits per pixel.
	static _dword GetBitsPerPixel( _qword pixel_format );

	//!	Get the minimial dmins.
	static _void GetMinDims( _qword pixel_format, _dword& min_x, _dword& min_y, _dword& min_z );

private:
	//!	Read header info.
	_ubool ReadHeaderInfo( IStreamReader* stream_reader );
	
	//!	Jump the meta-data section.
	_void JumpMetaDataSection( IStreamReader* stream_reader );
	
	//!	Build texture info.
	_ubool BuildTextureInfo( );

	//!	Read compressed buffer data.
	_ubool ReadCompressedBufferData( IStreamReader* stream_reader );

// TImageFile Interface
private:
	virtual _ubool					OnSaveToFile( const _byte* pixel_buffer, _dword pitch, _dword width, _dword height, IStreamWriter* stream_writer ) const override;

public:
	PVRTexFile( );
	virtual ~PVRTexFile( );

// IBaseFile Interface
public:
	virtual _FILE_FORMAT			GetFileID( ) const override;

	virtual _ubool 					LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 					Unload( ) override;

// IImageFile Interface
public:
	virtual _ubool					Create( _dword width, _dword height, _PIXEL_FORMAT pixelformat, const _byte* pixelbuffer = _null ) override;

// IPVRTCFile Interface
public:
	virtual const PVRTexHeaderInfo&	GetPVRTexHeader( ) const override;
};

}