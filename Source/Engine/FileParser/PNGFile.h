//! @file     PNGFile.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// PNGFile
//----------------------------------------------------------------------------

class PNGFile : public INTERFACE_IMAGEFILE_IMPL( IPNGFile )
{
public:
	//!	The PNG file ID
	enum { _FILE_ID = EGE_ID( 0x89, 'P', 'N', 'G' ) };

private:
	typedef INTERFACE_IMAGEFILE_IMPL( IPNGFile ) BaseClass;

private:
	_int	mBitDepth;
	_int	mColorType;

	Color	mBackgroundColor;

private:
	//!	LibPNG callback functions.
	static _void OnErrorHandler( _handle pngstruct, const char* error );
	static _void OnWarningHandler( _handle pngstruct, const char* warning );
	static _void OnReadProc( _handle pngstruct, unsigned char* buffer, size_t size );
	static _void OnWriteProc( _handle pngstruct, unsigned char* buffer, size_t size );
	static _void OnFlushProc( _handle pngstruct );

private:
	//!	Load PNG image file from stream.
	_ubool LoadImage( _handle pngstruct, _handle pnginfo, IStreamReader* stream_reader );
	//!	Save PNG image file to stream.
	_ubool SaveImage( const _byte* pixel_buffer, _dword pitch, _dword width, _dword height, IStreamWriter* stream_writer ) const;

// TImageFile Interface
private:
	virtual _ubool			OnSaveToFile( const _byte* pixel_buffer, _dword pitch, _dword width, _dword height, IStreamWriter* stream_writer ) const override;

public:
	PNGFile( );
	virtual ~PNGFile( );

// IBaseFile Interface
public:
	virtual _FILE_FORMAT	GetFileID( ) const override;

	virtual _ubool 			LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 			Unload( ) override;

	virtual _ubool 			SaveToStream( IStreamWriter* stream_writer, _dword flags ) const override;

// IImageFile Interface
public:
	virtual _ubool			Create( _dword width, _dword height, _PIXEL_FORMAT pixelformat, const _byte* pixelbuffer = _null ) override;

// IPNGFile Interface
public:
	virtual const Color&	GetBackgroundColor( ) const override;
};

}