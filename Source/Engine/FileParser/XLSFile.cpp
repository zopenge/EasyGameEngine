//! @file     XLSFile.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

#ifndef _EGE_DISABLE_XLS_FILE_

//----------------------------------------------------------------------------
// XLSFileReader Implementation
//----------------------------------------------------------------------------

INTERNAL_HANDLER_IMPL_BEGIN( XLSFileReader )
	xls::xlsWorkBook*	mWorkbook;

	INTERNAL_HANDLER_CONSTRUCTOR( )
	{
		mWorkbook = _null;
	}
	INTERNAL_HANDLER_DESTRUCTOR( )
	{
		if ( mWorkbook != _null )
			xls::xls_close_WB( mWorkbook );
	}
INTERNAL_HANDLER_IMPL_END( )
	
XLSFileReader::XLSFileReader( )
{
	INTERNAL_HANDLER_CREATE( );
}

XLSFileReader::~XLSFileReader( )
{
	INTERNAL_HANDLER_RELEASE( );
}

_ubool XLSFileReader::Initialize( WStringPtr file_name )
{
	INTERNAL_HANDLER( )->mWorkbook = xls::xls_open( AString( ).FromString( file_name ).Str( ), "UTF-8" );
	if ( INTERNAL_HANDLER( )->mWorkbook == _null )
	{
		WLOG_ERROR_1( L"Open the '%s' as XLS workbook failed", file_name.Str( ) );
		return _false;
	}

	return _true;
}

//----------------------------------------------------------------------------
// XLSCellWriter Implementation
//----------------------------------------------------------------------------

INTERNAL_HANDLER_IMPL_BEGIN( XLSCellWriter )
	cell_t*	mCell;

	INTERNAL_HANDLER_CONSTRUCTOR( )
	{
		mCell = _null;
	}
	INTERNAL_HANDLER_DESTRUCTOR( )
	{
	}
INTERNAL_HANDLER_IMPL_END( )

XLSCellWriter::XLSCellWriter( _handle cell )
{
	INTERNAL_HANDLER_CREATE( );

	INTERNAL_HANDLER( )->mCell = ((cell_t*) cell);
}

XLSCellWriter::~XLSCellWriter( )
{
	INTERNAL_HANDLER_RELEASE( );
}

_void XLSCellWriter::SetForeColor( _XLS_COLOR color )
{
	INTERNAL_HANDLER( )->mCell->fillfgcolor( (unsigned8_t) color );
}

_void XLSCellWriter::SetBKColor( _XLS_COLOR color )
{
	INTERNAL_HANDLER( )->mCell->fillbgcolor( (unsigned8_t) color );
}

_void XLSCellWriter::SetFillStyle( _XLS_CELL_FILL style )
{
	INTERNAL_HANDLER( )->mCell->fillstyle( (fill_option_t) style );
}

_void XLSCellWriter::SetBorderStyle( _XLS_BORDER border, _XLS_BORDER_STYLE style )
{
	INTERNAL_HANDLER( )->mCell->borderstyle( (border_side_t)border, (border_style_t) style );
}

_void XLSCellWriter::SetFontName( WStringPtr font_name )
{
	INTERNAL_HANDLER( )->mCell->fontname( AString( ).FromString( font_name ).Str( ) );
}

_void XLSCellWriter::SetFontColor( _XLS_COLOR color )
{
	INTERNAL_HANDLER( )->mCell->fontcolor( (unsigned8_t) color );
}

//----------------------------------------------------------------------------
// XLSWorkSheetWriter Implementation
//----------------------------------------------------------------------------

INTERNAL_HANDLER_IMPL_BEGIN( XLSWorkSheetWriter )
	worksheet*	mWorSheet;

	INTERNAL_HANDLER_CONSTRUCTOR( )
	{
		mWorSheet = _null;
	}
	INTERNAL_HANDLER_DESTRUCTOR( )
	{
	}
INTERNAL_HANDLER_IMPL_END( )

XLSWorkSheetWriter::XLSWorkSheetWriter( _handle work_sheet )
{
	INTERNAL_HANDLER_CREATE( );

	INTERNAL_HANDLER( )->mWorSheet = ((worksheet*) work_sheet);
}

XLSWorkSheetWriter::~XLSWorkSheetWriter( )
{
	INTERNAL_HANDLER_RELEASE( );
}

_void XLSWorkSheetWriter::SetColumnWidth( _dword col, _dword width )
{
	INTERNAL_HANDLER( )->mWorSheet->colwidth( col, width );
}

_void XLSWorkSheetWriter::SetRowHeight( _dword row, _dword height )
{
	INTERNAL_HANDLER( )->mWorSheet->rowheight( row, height );
}

IXLSCellWriterPassRef XLSWorkSheetWriter::SetLabel( _dword row, _dword col, WStringPtr name )
{
	return new XLSCellWriter( INTERNAL_HANDLER( )->mWorSheet->label( row, col, name.Str( ) ) );
}

IXLSCellWriterPassRef XLSWorkSheetWriter::SetNumber( _dword row, _dword col, _float value )
{
	return new XLSCellWriter( INTERNAL_HANDLER( )->mWorSheet->number( row, col, value ) );
}

IXLSCellWriterPassRef XLSWorkSheetWriter::SetNumber( _dword row, _dword col, _double value )
{
	return new XLSCellWriter( INTERNAL_HANDLER( )->mWorSheet->number( row, col, value ) );
}

IXLSCellWriterPassRef XLSWorkSheetWriter::SetNumber( _dword row, _dword col, _long value )
{
	return new XLSCellWriter( INTERNAL_HANDLER( )->mWorSheet->number( row, col, value ) );
}

IXLSCellWriterPassRef XLSWorkSheetWriter::SetNumber( _dword row, _dword col, _dword value )
{
	return new XLSCellWriter( INTERNAL_HANDLER( )->mWorSheet->number( row, col, value ) );
}

IXLSCellWriterPassRef XLSWorkSheetWriter::SetBoolean( _dword row, _dword col, _ubool value )
{
	return new XLSCellWriter( INTERNAL_HANDLER( )->mWorSheet->boolean( row, col, EGE_BOOLEAN( value ) ) );
}

//----------------------------------------------------------------------------
// XLSFileWriter Implementation
//----------------------------------------------------------------------------

INTERNAL_HANDLER_IMPL_BEGIN( XLSFileWriter )
	workbook*	mWorkbook;

	INTERNAL_HANDLER_CONSTRUCTOR( )
	{
		mWorkbook = ::xlsNewWorkbook( );
	}
	INTERNAL_HANDLER_DESTRUCTOR( )
	{
		if ( mWorkbook != _null )
			::xlsDeleteWorkbook( mWorkbook );
	}
INTERNAL_HANDLER_IMPL_END( )

XLSFileWriter::XLSFileWriter( )
{
	INTERNAL_HANDLER_CREATE( );
}

XLSFileWriter::~XLSFileWriter( )
{
	INTERNAL_HANDLER_RELEASE( );
}

void XLSFileWriter::OnXLSLibAssertionReporter( const char* expr, const char* filename, int lineno, const char* funcname )
{
	AString err_string;
	err_string += FORMAT_ASTRING_2( "Assertion failed: %s at line %d", (expr ? expr : "???"), lineno );

	if ( funcname != _null )
		err_string += FORMAT_ASTRING_1( " (%s)", funcname );
	if ( filename != _null )
		err_string += FORMAT_ASTRING_1( " in %s\n", filename );
	else
		err_string += " in [unidentified source file]\n";

	ALOG_ERROR( err_string.Str( ) );
}

_ubool XLSFileWriter::Initialize( )
{
	::xlslib_register_assert_reporter( &OnXLSLibAssertionReporter );

	return _true;
}

IXLSWorkSheetWriterPassRef XLSFileWriter::GetSheet( WStringPtr name )
{
	worksheet* work_sheet = INTERNAL_HANDLER( )->mWorkbook->sheet( AString( ).FromString( name ).Str( ) );
	if ( work_sheet == _null )
		return _null;

	return new XLSWorkSheetWriter( work_sheet );
}

_ubool XLSFileWriter::SaveToFile( WStringPtr file_name )
{
	_long ret = ::xlsWorkbookDump( INTERNAL_HANDLER( )->mWorkbook, AString( ).FromString( file_name ).Str( ) );
	if ( ret != NO_ERRORS )
	{
		WLOG_ERROR_2( L"Save to '%s' XLS file failed (ret: %d)", file_name.Str( ), ret );
		return _false;
	}

	return _true;
}

#endif