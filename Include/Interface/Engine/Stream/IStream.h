//! @file     IStream.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IStream
//----------------------------------------------------------------------------

class IStream : public IObject
{
public:
	//!	Get the stream type.
	//!	@param		none.
	//!	@return		The stream type.
	virtual _STREAM_TYPE GetType( ) const PURE;
	//!	Get the share mode.
	//!	@param		none.
	//!	@return		The share mode.
	virtual _STREAM_SHARE_MODE GetShareMode( ) const PURE;

	//!	Get buffer size in bytes.
	//!	@param		none.
	//!	@return		The buffer size.
	virtual _dword GetSize( ) const PURE;
	//!	Get the offset of current buffer pointer from begin.
	//!	@param		none.
	//!	@return		The offset of current buffer pointer in bytes from begin.
	virtual _dword GetOffset( ) const PURE;

	//!	Seek current buffer pointer to begin.
	//!	@param		flag		The seek flag.
	//! @param		distance	Number of bytes to move.
	//! @return		The current offset of stream from begin.
	virtual _dword Seek( _SEEK flag, _int distance ) PURE;
	//!	Seek dummy data to arrange bounds from begin position.
	//!	@param		value		The value what you want to arrange.
	//! @return		The current offset of stream from begin.
	virtual _dword SeekByArrangedValueFromBegin( _dword value ) PURE;

	//!	Set the stream endian type.
	//!	@param		endian		The endian type.
	//!	@return		none.
	virtual _void SetEndian( _ENDIAN endian ) PURE;
	//!	Get the stream endian type.
	//!	@param		none.
	//!	@return		The endian type.
	virtual _ENDIAN GetEndian( ) const PURE;
};

}