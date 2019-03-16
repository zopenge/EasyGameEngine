//! @file     IDatabaseRecord.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// RecordColumnDesc
//----------------------------------------------------------------------------

struct RecordColumnDesc
{
	enum { _MAX_STRING_LENGTH = 128 };

	enum _COLUMN_TYPE
	{
		_TYPE_UNKNOWN,
		_TYPE_CHAR,
		_TYPE_NUMERIC,
		_TYPE_DECIMAL,
		_TYPE_INTEGER,
		_TYPE_SMALLINT,
		_TYPE_FLOAT,
		_TYPE_REAL,
		_TYPE_DOUBLE,
		_TYPE_DATETIME,
		_TYPE_TIME,
		_TYPE_TIMESTAMP,
		_TYPE_VARCHAR,
		_TYPE_LONGVARCHAR,
		_TYPE_BINARY,
		_TYPE_VARBINARY,
		_TYPE_LONGVARBINARY,
		_TYPE_BIGINT,
		_TYPE_TINYINT,
		_TYPE_BIT,
	};

	_dword	mType;
	_dword	mSize;
	_dword	mDecimalDigits;
	_ubool	mNullable;
	_charw	mName[ _MAX_STRING_LENGTH ];

	RecordColumnDesc( )
	{
		mType			= _TYPE_UNKNOWN;
		mSize			= 0;
		mDecimalDigits	= 0;
		mNullable		= _false;
		mName[0]		= 0;
	}
};

//----------------------------------------------------------------------------
// IDatabaseRecord
//----------------------------------------------------------------------------

class IDatabaseRecord : public IObject
{
public:
	//!	Move to the first element.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool MoveFirst( ) PURE;
	//!	Move to the last element.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool MoveLast( ) PURE;

	//!	Move to the previous element.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool MovePrior( ) PURE;
	//!	Move to the next element.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool MoveNext( ) PURE;

	//!	Get the column number.
	//!	@param		none.
	//! @return		The column number.
	virtual _dword GetColumnNumber( ) const PURE;
	//!	Get the column index.
	//!	@param		name		The column name.
	//! @return		The column index.
	virtual _dword GetColumnIndex( WStringPtr name ) PURE;
	//!	Get the column description.
	//!	@param		index		The column index.
	//! @return		The column description.
	virtual RecordColumnDesc* GetColumnDesc( _dword index ) PURE;

	//!	Get value.
	//!	@param		index		The column index.
	//!	@param		nullvalue	True indicates it's null value.
	//! @return		The value.
	virtual _tiny GetTiny( _dword index, _ubool* nullvalue = _null ) PURE;
	//!	Get value.
	//!	@param		index		The column index.
	//!	@param		nullvalue	True indicates it's null value.
	//! @return		The value.
	virtual _short GetShort( _dword index, _ubool* nullvalue = _null ) PURE;
	//!	Get value.
	//!	@param		index		The column index.
	//!	@param		nullvalue	True indicates it's null value.
	//! @return		The value.
	virtual _int GetLong( _dword index, _ubool* nullvalue = _null ) PURE;
	//!	Get value.
	//!	@param		index		The column index.
	//!	@param		nullvalue	True indicates it's null value.
	//! @return		The value.
	virtual _byte GetByte( _dword index, _ubool* nullvalue = _null ) PURE;
	//!	Get value.
	//!	@param		index		The column index.
	//!	@param		nullvalue	True indicates it's null value.
	//! @return		The value.
	virtual _word GetWord( _dword index, _ubool* nullvalue = _null ) PURE;
	//!	Get value.
	//!	@param		index		The column index.
	//!	@param		nullvalue	True indicates it's null value.
	//! @return		The value.
	virtual _dword GetDword( _dword index, _ubool* nullvalue = _null ) PURE;

	//!	Get value string.
	//!	@param		index		The column index.
	//!	@param		nullvalue	True indicates it's null value.
	//! @return		The value string.
	virtual WStringR GetString( _dword index, _ubool* nullvalue = _null ) PURE;
	//!	Get value time.
	//!	@param		index		The column index.
	//!	@param		nullvalue	True indicates it's null value.
	//! @return		The value time.
	virtual Time GetTime( _dword index, _ubool* nullvalue = _null ) PURE;

	//!	Get string buffer.
	//!	@param		index		The column index.
	//!	@param		buffer		The string buffer.
	//!	@param		length		The string length.
	//!	@param		nullvalue	True indicates it's null value.
	//! @return		The number of characters in buffer.
	virtual _dword GetCharBuffer( _dword index, _charw* buffer, _dword length, _ubool* nullvalue = _null ) PURE;
	//!	Get binary buffer.
	//!	@param		index		The column index.
	//!	@param		buffer		The buffer.
	//!	@param		length		The buffer size.
	//!	@param		nullvalue	True indicates it's null value.
	//! @return		The buffer size.
	virtual _dword GetBinaryBuffer( _dword index, _byte* buffer, _dword length, _ubool* nullvalue = _null ) PURE;
};

}