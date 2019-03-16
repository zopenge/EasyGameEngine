//! @file     KTXFile.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// KTXFile
//----------------------------------------------------------------------------

class KTXFile : public INTERFACE_COMPRESSEDTEXFILE_IMPL( IKTXFile )
{
public:
	//!	The KTX file ID
	enum { _FILE_ID = EGE_ID( 0xAB, 0x4B, 0x54, 0x58 ) };

	//!	The KTX endian referenced value
	enum { KTX_ENDIAN_REF = 0x04030201 };
	enum { KTX_ENDIAN_REF_REV = 0x01020304 };

private:
	typedef INTERFACE_COMPRESSEDTEXFILE_IMPL( IKTXFile ) BaseClass;

private:
	//!	The header info
	KTXHeaderInfo	mHeaderInfo;

private:
	//!	Check KTX header.
	_ubool CheckKTXHeaderInfo( ) const;
	//!	Build texture header.
	_ubool BuildTextureHeader( );

	//!	Read mipmaps compressed buffer data.
	_ubool ReadMipmapsCompressedBufferData( IStreamReader* stream_reader );

// TImageFile Interface
private:
	virtual _ubool					OnSaveToFile( const _byte* pixel_buffer, _dword pitch, _dword width, _dword height, IStreamWriter* stream_writer ) const override;

public:
	KTXFile( );
	virtual ~KTXFile( );

// IBaseFile Interface
public:
	virtual _FILE_FORMAT			GetFileID( ) const override;

	virtual _ubool 					LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 					Unload( ) override;

// IImageFile Interface
public:
	virtual _ubool					Create( _dword width, _dword height, _PIXEL_FORMAT pixelformat, const _byte* pixelbuffer = _null ) override;

// IKTXFile Interface
public:
	virtual const KTXHeaderInfo&	GetKTXHeader( ) const override;
};

}