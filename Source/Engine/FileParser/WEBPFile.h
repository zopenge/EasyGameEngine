//! @file     WEBPFile.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// WEBPFile
//----------------------------------------------------------------------------

class WEBPFile : public INTERFACE_IMAGEFILE_IMPL( IWEBPFile )
{
private:
	typedef INTERFACE_IMAGEFILE_IMPL( IWEBPFile ) BaseClass;

public:
	//!	The WEBP file ID
	enum { _FILE_ID = EGE_ID( 'R', 'I', 'F', 'F' ) };

private:

public:
	WEBPFile( );
	virtual ~WEBPFile( );

// IBaseFile Interface
public:
	virtual _FILE_FORMAT	GetFileID( ) const override;

	virtual _ubool 			LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 			Unload( ) override;

// IWEBPFile Interface
public:
};

}