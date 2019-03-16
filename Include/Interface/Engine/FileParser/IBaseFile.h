//! @file     IBaseFile.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IBaseFile
//----------------------------------------------------------------------------

class IBaseFile : public ITFlagsObject< ISerializable >
{
public:
	//!	Get the file type ID.
	//!	@param		none.
	//!	@return		The file type ID.
	virtual _FILE_FORMAT GetFileID( ) const PURE;

	//!	Load from file.
	//!	@param		filename		The file name.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool LoadFromFile( WStringPtr filename ) PURE;
	//!	Load from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool LoadFromStream( IStreamReader* stream_reader ) PURE;
	//!	Unload.
	//!	@param		none.
	//!	@return		none.
	virtual _void Unload( ) PURE;

	//!	Save to stream.
	//!	@param		stream_writer	The stream writer.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SaveToStream( IStreamWriter* stream_writer, _dword flags = 0 ) const PURE;
	//!	Save to file.
	//!	@param		filename		The file name.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SaveToFile( WStringPtr filename, _dword flags = 0 ) const PURE;
};

}