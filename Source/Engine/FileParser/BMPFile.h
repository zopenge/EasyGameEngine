//! @file     BMPFile.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// BMPFile
//----------------------------------------------------------------------------

class BMPFile : public INTERFACE_IMAGEFILE_IMPL( IBMPFile )
{
private:
	typedef INTERFACE_IMAGEFILE_IMPL( IBMPFile ) BaseClass;

public:
	BMPFile( );
	virtual ~BMPFile( );
	
// IBaseFile Interface
public:
	virtual _FILE_FORMAT	GetFileID( ) const override;

	virtual _ubool 			LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 			Unload( ) override;

// IImageFile Interface
public:

// IBMPFile Interface
public:
};

}