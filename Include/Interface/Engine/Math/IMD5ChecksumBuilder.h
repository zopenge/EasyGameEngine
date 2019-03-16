//! @file     IMD5ChecksumBuilder.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IMD5ChecksumBuilder
//----------------------------------------------------------------------------

class IMD5ChecksumBuilder : public IObject
{
public:
	//!	Calculate the MD5 checksum of stream.
	//!	@param		stream_reader	The stream reader.
	//!	@param		md5_code		The MD5 checksum code.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool BuildFromStream( IStreamReader* stream_reader, MD5Code& md5_code ) const PURE;

	//!	Calculate the MD5 checksum of file.
	//!	@param		filename		The file name.
	//!	@param		md5_code		The MD5 code.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool BuildFromFile( WStringPtr filename, MD5Code& md5_code ) const PURE;
};

}