//! @file     JPGFile.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// JPGFile
//----------------------------------------------------------------------------

class JPGFile : public INTERFACE_IMAGEFILE_IMPL( IJPGFile )
{
private:
	typedef INTERFACE_IMAGEFILE_IMPL( IJPGFile ) BaseClass;

public:
	JPGFile( );
	virtual ~JPGFile( );

// IBaseFile Interface
public:
	virtual _FILE_FORMAT	GetFileID( ) const override;

	virtual _ubool 			LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 			Unload( ) override;

// IImageFile Interface
public:

// IJPGFile Interface
public:
};

}