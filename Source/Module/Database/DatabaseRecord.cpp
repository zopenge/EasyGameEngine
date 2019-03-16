//! @file     DatabaseRecord.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEDatabase.h"

//----------------------------------------------------------------------------
// DatabaseRecord Implementation
//----------------------------------------------------------------------------

DatabaseRecord::DatabaseRecord( _handle sql_state_handle ) : mSQLStatement( sql_state_handle )
{
	mColumnNumber		= 0;
	mColumnDescBuffer	= _null;
}

DatabaseRecord::~DatabaseRecord( )
{
//	::SQLCloseCursor( mSQLStatement );
}

_ubool DatabaseRecord::GetColumnHelper( _dword index )
{
	RecordColumnDesc* columndesc = &mColumnDescBuffer[ index ];

	if ( columndesc->mName[0] != 0 )
		return _true;

	_dword namelength = 0, datatype = 0, decimaldigits = 0;

	// Get column from record
	SQLULEN col_size = 0;
	if ( ! SQL_SUCCEEDED( ::SQLDescribeColW( mSQLStatement, (SQLSMALLINT) index + 1, columndesc->mName, RecordColumnDesc::_MAX_STRING_LENGTH,
		(SQLSMALLINT*) &namelength, (SQLSMALLINT*) &datatype, &col_size, (SQLSMALLINT*) &decimaldigits, (SQLSMALLINT*) &columndesc->mNullable ) ) )
	{
		return _false;
	}

	if ( namelength == 0 )
		return _false;

	columndesc->mSize = col_size;

	switch ( datatype )
	{
		case SQL_CHAR:			columndesc->mType = RecordColumnDesc::_TYPE_CHAR; break;
		case SQL_NUMERIC:		columndesc->mType = RecordColumnDesc::_TYPE_NUMERIC; break;
		case SQL_DECIMAL:		columndesc->mType = RecordColumnDesc::_TYPE_DECIMAL; break;
		case SQL_INTEGER:		columndesc->mType = RecordColumnDesc::_TYPE_INTEGER; break;
		case SQL_SMALLINT:		columndesc->mType = RecordColumnDesc::_TYPE_SMALLINT; break;
		case SQL_FLOAT:			columndesc->mType = RecordColumnDesc::_TYPE_FLOAT; break;
		case SQL_REAL:			columndesc->mType = RecordColumnDesc::_TYPE_REAL; break;
		case SQL_DOUBLE:		columndesc->mType = RecordColumnDesc::_TYPE_DOUBLE; break;
		case SQL_DATETIME:		columndesc->mType = RecordColumnDesc::_TYPE_DATETIME; break;
		case SQL_TIME:			columndesc->mType = RecordColumnDesc::_TYPE_TIME; break;
		case SQL_TIMESTAMP:		columndesc->mType = RecordColumnDesc::_TYPE_TIMESTAMP; break;
		case SQL_VARCHAR:		columndesc->mType = RecordColumnDesc::_TYPE_VARCHAR; break;
		case SQL_LONGVARCHAR:	columndesc->mType = RecordColumnDesc::_TYPE_LONGVARCHAR; break;
		case SQL_BINARY:		columndesc->mType = RecordColumnDesc::_TYPE_BINARY; break;
		case SQL_VARBINARY:		columndesc->mType = RecordColumnDesc::_TYPE_VARBINARY; break;
		case SQL_LONGVARBINARY:	columndesc->mType = RecordColumnDesc::_TYPE_LONGVARBINARY; break;
		case SQL_BIGINT:		columndesc->mType = RecordColumnDesc::_TYPE_BIGINT; break;
		case SQL_TINYINT:		columndesc->mType = RecordColumnDesc::_TYPE_TINYINT; break;
		case SQL_BIT:			columndesc->mType = RecordColumnDesc::_TYPE_BINARY; break;
		default:
			return _false;
	}

	return columndesc->mName[0] != 0;
}

_ubool DatabaseRecord::GetValueHelper( _dword index, _dword type, _void* buffer, _dword length, _dword* outlength, _ubool* nullvalue )
{
	if ( outlength != _null )
		*outlength = 0;

	if ( nullvalue != _null )
		*nullvalue = _false;

	// We need random access, so we must scroll fetch cursor
	if ( ! SQL_SUCCEEDED( ::SQLFetchScroll( mSQLStatement, SQL_FETCH_RELATIVE, 0 ) ) )
		return _false;

	_dword tempout = 0;
	if ( ! SQL_SUCCEEDED( ::SQLGetData( mSQLStatement, (SQLUSMALLINT) index + 1, (SQLSMALLINT) type, buffer, length, (SQLINTEGER*) &tempout ) ) )
	{
		if ( nullvalue != _null )
			*nullvalue = _true;
	}
	else
	{
		if ( tempout > length )
		{
			if ( nullvalue != _null )
				*nullvalue = _true;

			tempout = 0;
		}

		if ( outlength != _null )
			*outlength = tempout;
	}

	return _true;
}

_ubool DatabaseRecord::Initialize( )
{
	if ( ! SQL_SUCCEEDED( ::SQLNumResultCols( mSQLStatement, (SQLSMALLINT*) &mColumnNumber ) ) )
		return _false;

	mColumnDescBuffer = new RecordColumnDesc[ mColumnNumber ];

	return _true;
}

_ubool DatabaseRecord::MoveFirst( )
{
	return SQL_SUCCEEDED( ::SQLFetchScroll( mSQLStatement, SQL_FETCH_FIRST, 0 ) );
}

_ubool DatabaseRecord::MoveLast( )
{
	return SQL_SUCCEEDED( ::SQLFetchScroll( mSQLStatement, SQL_FETCH_LAST, 0 ) );
}

_ubool DatabaseRecord::MovePrior( )
{
	return SQL_SUCCEEDED( ::SQLFetchScroll( mSQLStatement, SQL_FETCH_PRIOR, 0 ) );
}

_ubool DatabaseRecord::MoveNext( )
{
	return SQL_SUCCEEDED( ::SQLFetchScroll( mSQLStatement, SQL_FETCH_NEXT, 0 ) );
}

_dword DatabaseRecord::GetColumnNumber( ) const
{
	return mColumnNumber;
}

_dword DatabaseRecord::GetColumnIndex( WStringPtr filed )
{
	_ubool needgetcolumn = _false;

	// Get in existing column desc.
	for ( _dword i = 0; i < mColumnNumber; i ++ )
	{
		if ( mColumnDescBuffer[i].mName[0] == 0 )
		{
			needgetcolumn = _true;
			continue;
		}

		if ( filed.Compare( mColumnDescBuffer[i].mName, _true ) == 0 )
			return i;
	}

	// There is some column desc need to get.
	if ( needgetcolumn )
	{
		for ( _dword i = 0; i < mColumnNumber; i ++ )
		{
			if ( mColumnDescBuffer[i].mName[0] != 0 )
				continue;

			// Get this column desc.
			if ( GetColumnHelper( i ) == _false )
				continue;

			if ( filed.Compare( mColumnDescBuffer[i].mName, _true ) == 0 )
				return i;
		}
	}

	return -1;
}

RecordColumnDesc* DatabaseRecord::GetColumnDesc( _dword index )
{
	if ( index >= mColumnNumber )
		return _null;

	if ( GetColumnHelper( index ) == _false )
		return _null;

	return &mColumnDescBuffer[ index ];
}

_tiny DatabaseRecord::GetTiny( _dword index, _ubool* nullvalue )
{
	_tiny value = 0;
	if ( GetValueHelper( index, SQL_C_STINYINT, &value, sizeof( value ), _null, nullvalue ) == _false )
		return 0;

	return value;
}

_short DatabaseRecord::GetShort( _dword index, _ubool* nullvalue )
{
	_short value = 0;
	if ( GetValueHelper( index, SQL_C_SSHORT, &value, sizeof( value ), _null, nullvalue ) == _false )
		return 0;

	return value;
}

_int DatabaseRecord::GetLong( _dword index, _ubool* nullvalue )
{
	_int value = 0;
	if ( GetValueHelper( index, SQL_C_SLONG, &value, sizeof( value ), _null, nullvalue ) == _false )
		return 0;

	return value;
}

_byte DatabaseRecord::GetByte( _dword index, _ubool* nullvalue )
{
	_int value = 0;
	if ( GetValueHelper( index, SQL_C_UTINYINT, &value, sizeof( value ), _null, nullvalue ) == _false )
		return 0;

	return value;
}

_word DatabaseRecord::GetWord( _dword index, _ubool* nullvalue )
{
	_int value = 0;
	if ( GetValueHelper( index, SQL_C_USHORT, &value, sizeof( value ), _null, nullvalue ) == _false )
		return 0;

	return value;
}

_dword DatabaseRecord::GetDword( _dword index, _ubool* nullvalue )
{
	_int value = 0;
	if ( GetValueHelper( index, SQL_C_ULONG, &value, sizeof( value ), _null, nullvalue ) == _false )
		return 0;

	return value;
}

WStringR DatabaseRecord::GetString( _dword index, _ubool* nullvalue )
{
	_charw buffer[1024]; _dword outlength = 0;
	if ( GetValueHelper( index, SQL_WCHAR, buffer, sizeof( buffer ), &outlength, nullvalue ) == _false )
		return WString( L"" );

	buffer[ outlength ] = 0;

	return buffer;
}

Time DatabaseRecord::GetTime( _dword index, _ubool* nullvalue )
{
	SQL_TIMESTAMP_STRUCT timestamp = { 0 };
	if ( GetValueHelper( index, SQL_C_TIMESTAMP, &timestamp, sizeof( timestamp ), _null, nullvalue ) == _false )
		return Time( );

	CalendarTime system_time;
	system_time.mYear			= timestamp.year;
	system_time.mMonth			= timestamp.month;
	system_time.mDayOfMonth		= timestamp.day;
	system_time.mHour			= timestamp.hour;
	system_time.mMinute			= timestamp.minute;
	system_time.mSecond			= timestamp.second;
	system_time.mMilliseconds	= (_word) timestamp.fraction;

	return Time( system_time );
}

_dword DatabaseRecord::GetCharBuffer( _dword index, _charw* buffer, _dword length, _ubool* nullvalue )
{
	_dword outlength = 0;
	if ( GetValueHelper( index, SQL_WCHAR, buffer, length, &outlength, nullvalue ) == _false )
		return 0;

	return outlength;
}

_dword DatabaseRecord::GetBinaryBuffer( _dword index, _byte* buffer, _dword length, _ubool* nullvalue )
{
	_dword outlength = 0;
	if ( GetValueHelper( index, SQL_C_BINARY, buffer, length, &outlength, nullvalue ) == _false )
		return _false;

	return outlength;
}