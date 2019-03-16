//! @file     IFileWriter.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IFileWriter
//----------------------------------------------------------------------------

class IFileWriter : public IObject
{
public:
	virtual _ubool LoadFromStream( IStreamReader* stream_reader ) PURE;

	virtual _ubool SaveToStream( IStreamWriter* stream_writer ) const PURE;
	virtual _ubool SaveToFile( WStringPtr file_name ) const PURE;
	virtual IBaseFilePassRef SaveToBaseFile( ) const PURE;
};

}