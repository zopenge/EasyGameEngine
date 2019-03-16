//! @file     IStreamReader.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IStreamReader
//----------------------------------------------------------------------------

class IStreamReader : public IStream
{
public:
	//!	Get the remain size in bytes.
	//!	@param		none.
	//!	@return		The remain size in bytes.
	virtual _dword GetRemainBytes( ) const PURE;

	//!	Get buffer data.
	//!	@param		none.
	//!	@return		The buffer data pointer.
	virtual const _byte* GetBuffer( ) PURE;

	//!	Check whether the current buffer pointer reach the end position or not.
	//!	@param		none.
	//!	@return		True indicates the reach the end position.
	virtual _ubool ReachEnd( ) const PURE;

	//!	Peek the buffer data.
	//!	@param		buffer		The buffer data.
	//!	@param		size		The buffer size.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword PeekBuffer( _void* buffer, _dword size ) PURE;
	//!	Peek the buffer data with offset.
	//!	@param		buffer		The buffer data.
	//!	@param		size		The buffer size.
	//!	@param		offset		The offset of stream in bytes from begin.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword PeekBuffer( _void* buffer, _dword size, _dword offset ) PURE;

	//!	Read the buffer data.
	//!	@param		buffer		The buffer data.
	//!	@param		size		The buffer size.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword ReadBuffer( _void* buffer, _dword size ) PURE;
	//!	Read the 8-bits signed value data.
	//!	@param		data		The value data.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword ReadTiny( _tiny& data ) PURE;
	//!	Read the 16-bits signed value data.
	//!	@param		data		The value data.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword ReadShort( _short& data ) PURE;
	//!	Read the 32-bits signed value data.
	//!	@param		data		The value data.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword ReadLong( _int& data ) PURE;
	//!	Read the 8-bits unsigned value data.
	//!	@param		data		The value data.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword ReadByte( _byte& data ) PURE;
	//!	Read the 16-bits unsigned value data.
	//!	@param		data		The value data.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword ReadWord( _word& data ) PURE;
	//!	Read the 32-bits unsigned value data.
	//!	@param		data		The value data.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword ReadDword( _dword& data ) PURE;
	//!	Read the 64-bits unsigned value data.
	//!	@param		data		The value data.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword ReadQword( _qword& data ) PURE;
	//!	Read the 32-bits float value data.
	//!	@param		data		The value data.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword ReadFloat( _float& data ) PURE;
	//!	Read the 64-bits double value data.
	//!	@param		data		The value data.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword ReadDouble( _double& data ) PURE;

	//!	Read string stream in ANSI.
	//!	@param		string		The string.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword ReadString( AString& string ) PURE;
	//!	Read string stream in UTF-8.
	//!	@param		string		The string.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword ReadString( UString& string ) PURE;
	//!	Read string stream in UTF-16.
	//!	@param		string		The string.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword ReadString( WString& string ) PURE;

	//!	Read the single line string in ANSI mode.
	//!	@param		string		The string.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword ReadLine( AString& string ) PURE;
	//!	Read the single line string in UTF-8 mode.
	//!	@param		string		The string.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword ReadLine( UString& string ) PURE;
	//!	Read the single line string in UTF-16 mode.
	//!	@param		string		The string.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword ReadLine( WString& string ) PURE;

	//!	Read the single line string in ANSI mode.
	//!	@param		encode_type	The encode type.
	//!	@param		string		The string.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword ReadLine( _ENCODING encode_type, AString& string ) PURE;
	//!	Read the single line string in UTF-8 mode.
	//!	@param		encode_type	The encode type.
	//!	@param		string		The string.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword ReadLine( _ENCODING encode_type, UString& string ) PURE;
	//!	Read the single line string in UTF-16 mode.
	//!	@param		encode_type	The encode type.
	//!	@param		string		The string.
	//! @return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword ReadLine( _ENCODING encode_type, WString& string ) PURE;

	//!	Read encode type.
	//!	@param		encode_type	The encode type.
	//!	@return		The actual processed bytes, 0 indicates nothing to be processed.
	virtual _dword ReadEncodeType( _ENCODING& encode_type ) PURE;
};

}