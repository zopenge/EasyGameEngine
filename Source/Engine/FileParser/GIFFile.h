//! @file     GIFFile.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GIFFile
//----------------------------------------------------------------------------

class GIFFile : public INTERFACE_IMAGEFILE_IMPL( IGIFFile )
{
public:
	//!	The GIF file ID
	enum { _FILE_ID = EGE_ID( 'G', 'I' , 'F', '8' ) };

private:
	typedef INTERFACE_IMAGEFILE_IMPL( IGIFFile ) BaseClass;

private:
	//!	The decode info
	struct DecodeInfo
	{
		GIFFile*			mGifFile;
		IStreamReaderRef	mStreamReader;

		DecodeInfo( )
		{
			mGifFile = _null;
		}
	};

public:
	GIFFile( );
	virtual ~GIFFile( );

private:
	static int OnReadFunction( GifFileType* gif_file, GifByteType* buffer, int size );

private:
	//!	Decode image.
	_ubool DecodeImage( GifFileType* gif_file );

// IBaseFile Interface
public:
	virtual _FILE_FORMAT	GetFileID( ) const override;

	virtual _ubool 			LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 			Unload( ) override;

// IImageFile Interface
public:

// IGIFFile Interface
public:
};

}