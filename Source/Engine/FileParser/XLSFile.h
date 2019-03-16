//! @file     XLSFile.h
//! @author   LiCode
//! @version  1.0
//! @date     2013/07/11
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// XLSFileReader
//----------------------------------------------------------------------------

class XLSFileReader : public TObject< IXLSFileReader >
{
private:
	INTERNAL_HANDLER_DECL( );

public:
	XLSFileReader( );
	virtual ~XLSFileReader( );

public:
	//!	Initialize.
	_ubool Initialize( WStringPtr file_name );

// IXLSFileReader Interface
public:
};

//----------------------------------------------------------------------------
// XLSCellWriter
//----------------------------------------------------------------------------

class XLSCellWriter : public TObject< IXLSCellWriter >
{
private:
	INTERNAL_HANDLER_DECL( );

public:
	XLSCellWriter( _handle cell );
	virtual ~XLSCellWriter( );

// IXLSCellWriter Interface
public:
	virtual _void SetForeColor( _XLS_COLOR color ) override;
	virtual _void SetBKColor( _XLS_COLOR color ) override;

	virtual _void SetFillStyle( _XLS_CELL_FILL style ) override;
	virtual _void SetBorderStyle( _XLS_BORDER border, _XLS_BORDER_STYLE style ) override;

	virtual _void SetFontName( WStringPtr font_name ) override;
	virtual _void SetFontColor( _XLS_COLOR color ) override;
};

//----------------------------------------------------------------------------
// XLSWorkSheetWriter
//----------------------------------------------------------------------------

class XLSWorkSheetWriter : public TObject< IXLSWorkSheetWriter >
{
private:
	INTERNAL_HANDLER_DECL( );

public:
	XLSWorkSheetWriter( _handle work_sheet );
	virtual ~XLSWorkSheetWriter( );

// IXLSWorkSheetWriter Interface
public:
	virtual _void					SetColumnWidth( _dword col, _dword width ) override;
	virtual _void					SetRowHeight( _dword row, _dword height ) override;

	virtual IXLSCellWriterPassRef	SetLabel( _dword row, _dword col, WStringPtr name ) override;
	virtual IXLSCellWriterPassRef	SetNumber( _dword row, _dword col, _float value ) override;
	virtual IXLSCellWriterPassRef	SetNumber( _dword row, _dword col, _double value ) override;
	virtual IXLSCellWriterPassRef	SetNumber( _dword row, _dword col, _long value ) override;
	virtual IXLSCellWriterPassRef	SetNumber( _dword row, _dword col, _dword value ) override;
	virtual IXLSCellWriterPassRef	SetBoolean( _dword row, _dword col, _ubool value ) override;
};

//----------------------------------------------------------------------------
// XLSFileWriter
//----------------------------------------------------------------------------

class XLSFileWriter : public TObject< IXLSFileWriter >
{
private:
	INTERNAL_HANDLER_DECL( );

private:
	//!	When XLS library assertion report callback function.
	static void OnXLSLibAssertionReporter( const char* expr, const char* filename, int lineno, const char* funcname );

public:
	XLSFileWriter( );
	virtual ~XLSFileWriter( );

public:
	//!	Initialize.
	static _ubool Initialize( );

// IXLSFileWriter Interface
public:
	virtual IXLSWorkSheetWriterPassRef	GetSheet( WStringPtr name ) override;

	virtual _ubool						SaveToFile( WStringPtr file_name ) override;
};

}