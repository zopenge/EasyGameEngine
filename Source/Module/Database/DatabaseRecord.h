//! @file     DatabaseRecord.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

class DatabaseConnection;

//----------------------------------------------------------------------------
// DatabaseRecord
//----------------------------------------------------------------------------

class DatabaseRecord : public INTERFACE_OBJECT_IMPL( IDatabaseRecord )
{
private:
	//!	The column number of records
	_dword				mColumnNumber;
	//!	The column records
	RecordColumnDesc*	mColumnDescBuffer;

	//!	The SQL state handle
	_handle				mSQLStatement;

private:
	//!	Get column.
	//!	@param		index		The column index.
	//! @return		True indicates success, false indicates failure.
	_ubool GetColumnHelper( _dword index );
	//!	Get value.
	//!	@param		index		The column index.
	//!	@param		type		The value type.
	//!	@param		buffer		The value buffer.
	//!	@param		length		The value buffer length.
	//!	@param		outlength	The value buffer length what has read.
	//!	@param		nullvalue	The value whether is null or not.
	//! @return		True indicates success, false indicates failure.
	_ubool GetValueHelper( _dword index, _dword type, _void* buffer, _dword length, _dword* outlength, _ubool* nullvalue );

public:
	DatabaseRecord( _handle sql_state_handle );
	virtual ~DatabaseRecord( );

public:
	//!	Initialize.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	_ubool Initialize( );

// IDatabaseRecord Interface
public:
	virtual _ubool				MoveFirst( );
	virtual _ubool				MoveLast( );

	virtual _ubool				MovePrior( );
	virtual _ubool				MoveNext( );

	virtual _dword				GetColumnNumber( ) const;
	virtual _dword				GetColumnIndex( WStringPtr filed );
	virtual RecordColumnDesc*	GetColumnDesc( _dword index );

	virtual _tiny				GetTiny( _dword index, _ubool* nullvalue );
	virtual _short				GetShort( _dword index, _ubool* nullvalue );
	virtual _int				GetLong( _dword index, _ubool* nullvalue );
	virtual _byte				GetByte( _dword index, _ubool* nullvalue );
	virtual _word				GetWord( _dword index, _ubool* nullvalue );
	virtual _dword				GetDword( _dword index, _ubool* nullvalue );

	virtual WStringR			GetString( _dword index, _ubool* nullvalue );
	virtual Time				GetTime( _dword index, _ubool* nullvalue );

	virtual _dword				GetCharBuffer( _dword index, _charw* buffer, _dword length, _ubool* nullvalue );
	virtual _dword				GetBinaryBuffer( _dword index, _byte* buffer, _dword length, _ubool* nullvalue );
};

}