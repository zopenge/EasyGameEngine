//! @file     EXRFile.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// EXRFile
//----------------------------------------------------------------------------

class EXRFile : public INTERFACE_IMAGEFILE_IMPL( IEXRFile )
{
public:
	//!	The JPG file ID
	enum { _FILE_ID = 0xE0FFD8FF };

private:
	typedef INTERFACE_IMAGEFILE_IMPL( IEXRFile ) BaseClass;

public:
	EXRFile( );
	virtual ~EXRFile( );

// IBaseFile Interface
public:
	virtual _FILE_FORMAT	GetFileID( ) const override;

	virtual _ubool 			LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 			Unload( ) override;

// IImageFile Interface
public:

// IEXRFile Interface
public:
};

}