//! @file     CSVFile.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

#ifndef _EGE_DISABLE_CSV_FILE_

//----------------------------------------------------------------------------
// CSVFile Helpful Functions Implementation
//----------------------------------------------------------------------------

//!	Output the CSV parser error log.
static _void OutputCSVParserErrorLog( csv_parser& parser )
{
	// Get the error ID and string
	_int			error_id	= ::csv_error( &parser );
	const _chara*	error_msg	= ::csv_strerror( error_id );
	if ( error_msg == _null )
		error_msg = "unknown";

	// Output the error string
	ALOG_ERROR_2( "Parse CSV file failed, errid:%d, errmsg:%s", error_id, error_msg );
}

//----------------------------------------------------------------------------
// CSVFile Implementation
//----------------------------------------------------------------------------

CSVFile::CSVFile( )
{
	mRows		= 0;
	mColumns	= 0;
}

CSVFile::~CSVFile( )
{
	Unload( );
}

_void CSVFile::OnReadColumn( _void* data, size_t size, _void* userdata )
{
	CSVFile* csv_file = (CSVFile*) userdata;
	EGE_ASSERT( csv_file != _null );

	// Update the columns number
	csv_file->mColumns ++;
}

_void CSVFile::OnReadRow( int, _void* userdata )
{
	CSVFile* csv_file = (CSVFile*) userdata;
	EGE_ASSERT( csv_file != _null );

	// Reset the columns number
	csv_file->mColumns = 0;

	// Update the rows number
	csv_file->mRows ++;
}

_FILE_FORMAT CSVFile::GetFileID( ) const
{
	return _FF_CSV;
}

_ubool CSVFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	// Get the stream size
	_dword size = stream_reader->GetSize( );
	if ( size == 0 )
		return _false;

	Unload( );
	
	// Initialize CSV parser
	csv_parser parser;
	::csv_init( &parser, CSV_STRICT );

	// Read the CSV text string
	MemArrayPtr< _byte > buffer( size );
	stream_reader->ReadBuffer( buffer, size );

	// Parse it
	_dword retval = ::csv_parse( &parser, buffer, size, OnReadColumn, OnReadRow, this );
	if ( retval != size )
	{
		// Parse failed
		OutputCSVParserErrorLog( parser );
	}
	else
	{
		// Finish parse
		retval = ::csv_fini( &parser, OnReadColumn, OnReadRow, this );
		if ( retval != 0 )
		{
			// Something wrong with the last character
			OutputCSVParserErrorLog( parser );
		}
	}

	// Free the CSV parser
	::csv_free( &parser );

	// Check whether it's successful
	return retval == 0;
}

_void CSVFile::Unload( )
{
	mRows		= 0;
	mColumns	= 0;

	mGrids.Clear( );
}

_dword CSVFile::GetRows( ) const
{
	return mRows;
}

_dword CSVFile::GetColumns( ) const
{
	return mColumns;
}

WStringPtr CSVFile::GetGridString( _dword column, _dword row ) const
{
	_dword index = row * mColumns + column;
	if ( index >= mGrids.Number( ) )
		return L"";

	return mGrids[ index ];
}

#endif
