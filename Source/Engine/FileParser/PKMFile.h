//! @file     PKMFile.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// PKMFile
//----------------------------------------------------------------------------

class PKMFile : public INTERFACE_COMPRESSEDTEXFILE_IMPL( IPKMFile )
{
public:
	//!	The ETC file ID
	enum { _FILE_ID = EGE_ID( 'P', 'K', 'M', ' ' ) };

private:
	typedef INTERFACE_COMPRESSEDTEXFILE_IMPL( IPKMFile ) BaseClass;

private:
	//!	The header info
	PKMHeaderInfo	mHeaderInfo;

// TImageFile Interface
private:
	virtual _ubool					OnSaveToFile( const _byte* pixel_buffer, _dword pitch, _dword width, _dword height, IStreamWriter* stream_writer ) const override;

public:
	PKMFile( );
	virtual ~PKMFile( );

// IBaseFile Interface
public:
	virtual _FILE_FORMAT			GetFileID( ) const override;

	virtual _ubool 					LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 					Unload( ) override;

// IImageFile Interface
public:
	virtual _ubool					Create( _dword width, _dword height, _PIXEL_FORMAT pixelformat, const _byte* pixelbuffer = _null ) override;

// IPKMFile Interface
public:
	virtual const PKMHeaderInfo&	GetPKMHeader( ) const override;
};

}