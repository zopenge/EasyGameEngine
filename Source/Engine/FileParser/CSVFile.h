//! @file     CSVFile.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// CSVFile
//----------------------------------------------------------------------------

class CSVFile : public INTERFACE_BASEFILE_IMPL( ICSVFile )
{
private:
	typedef INTERFACE_BASEFILE_IMPL( ICSVFile ) BaseClass;

private:
	//!	The columns number
	_dword			mColumns;
	//!	The rows number
	_dword			mRows;

	//!	The grids string 
	WStringArray	mGrids;

private:
	//!	When read column.
	static _void OnReadColumn( _void* data, size_t size, _void* userdata );
	//!	When read row.
	static _void OnReadRow( int, _void* userdata );

public:
	CSVFile( );
	virtual ~CSVFile( );

// IBaseFile Interface
public:
	virtual _FILE_FORMAT	GetFileID( ) const override;

	virtual _ubool 			LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 			Unload( ) override;

// ICSVFile Interface
public:
	virtual _dword 			GetRows( ) const override;
	virtual _dword 			GetColumns( ) const override;

	virtual WStringPtr		GetGridString( _dword column, _dword row ) const override;
};

}