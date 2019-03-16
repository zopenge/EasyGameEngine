//! @file     IStreamWriter.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IStreamWriter
//----------------------------------------------------------------------------

class IStreamWriter : public IStream
{
public:
	//!	Remove the buffer data.
	//!	@remark		Only works for none-shared buffer mode.
	//!	@param		size		The remove size in bytes.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword RemoveBuffer( _dword size ) PURE;
	//!	Set the current offset as end position, it will reallocate the memory buffer.
	//!	@param		none.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool SetCurOffsetAsEndPos( ) PURE;

	//!	Get buffer data.
	//!	@param		none.
	//!	@return		The buffer data pointer.
	virtual _byte* GetBuffer( ) PURE;

	//!	Write the buffer data.
	//!	@param		buffer		The buffer data.
	//!	@param		size		The buffer size.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword WriteBuffer( const _void* buffer, _dword size ) PURE;
	//!	Write the 8-bits signed value data.
	//!	@param		data		The value data.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword WriteTiny( _tiny data ) PURE;
	//!	Write the 16-bits signed value data.
	//!	@param		data		The value data.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword WriteShort( _short data ) PURE;
	//!	Write the 32-bits signed value data.
	//!	@param		data		The value data.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword WriteLong( _int data ) PURE;
	//!	Write the 8-bits unsigned value data.
	//!	@param		data		The value data.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword WriteByte( _byte data ) PURE;
	//!	Write the 16-bits unsigned value data.
	//!	@param		data		The value data.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword WriteWord( _word data ) PURE;
	//!	Write the 32-bits unsigned value data.
	//!	@param		data		The value data.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword WriteDword( _dword data ) PURE;
	//!	Write the 64-bits unsigned value data.
	//!	@param		data		The value data.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword WriteQword( _qword data ) PURE;
	//!	Write the 32-bits float value data.
	//!	@param		data		The value data.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword WriteFloat( _float data ) PURE;
	//!	Write the 64-bits double value data.
	//!	@param		data		The value data.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword WriteDouble( _double data ) PURE;

	//!	Write string stream in ANSI.
	//!	@param		string		The string.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword WriteString( AStringPtr string ) PURE;
	//!	Write string stream in UNICODE.
	//!	@param		string		The string.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword WriteString( WStringPtr string ) PURE;
};

}