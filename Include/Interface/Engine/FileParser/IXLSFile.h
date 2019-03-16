//! @file     IXLSFile.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// XLSFile Enumerations
//----------------------------------------------------------------------------

//! Foreground, background, and text color options. Change to BIFF8 may cause some of these to be incorrect...
enum _XLS_COLOR
{
	_XLS_COLOR_NULL,

	_XLS_COLOR_BLACK,
	_XLS_COLOR_BROWN,
	_XLS_COLOR_OLIVE_GREEN,
	_XLS_COLOR_DARK_GREEN,
	_XLS_COLOR_DARK_TEAL,
	_XLS_COLOR_DARK_BLUE,
	_XLS_COLOR_INDIGO,
	_XLS_COLOR_GRAY80,

	_XLS_COLOR_DARK_RED,
	_XLS_COLOR_ORANGE,
	_XLS_COLOR_DARK_YELLOW,
	_XLS_COLOR_GREEN,
	_XLS_COLOR_TEAL,
	_XLS_COLOR_BLUE,
	_XLS_COLOR_BLUE_GRAY,
	_XLS_COLOR_GRAY50,

	_XLS_COLOR_RED,
	_XLS_COLOR_LIGHT_ORANGE,
	_XLS_COLOR_LIME,
	_XLS_COLOR_SEA_GREEN,
	_XLS_COLOR_AQUA,
	_XLS_COLOR_LIGHT_BLUE,
	_XLS_COLOR_VIOLET,
	_XLS_COLOR_GRAY40,

	_XLS_COLOR_PINK,
	_XLS_COLOR_GOLD,
	_XLS_COLOR_YELLOW,
	_XLS_COLOR_BRIGHT_GREEN,
	_XLS_COLOR_TURQUOISE,
	_XLS_COLOR_SKY_BLUE,
	_XLS_COLOR_PLUM,
	_XLS_COLOR_GRAY25,

	_XLS_COLOR_ROSE,
	_XLS_COLOR_TAN,
	_XLS_COLOR_LIGHT_YELLOW,
	_XLS_COLOR_LIGHT_GREEN,
	_XLS_COLOR_LIGHT_TURQUOISE,
	_XLS_COLOR_PALEBLUE,
	_XLS_COLOR_LAVENDER,
	_XLS_COLOR_WHITE,

	_XLS_COLOR_PERIWINKLE,
	_XLS_COLOR_DARK_BLUE2,
	_XLS_COLOR_PLUM2,
	_XLS_COLOR_PINK2,
	_XLS_COLOR_IVORY,
	_XLS_COLOR_YELLOW2,
	_XLS_COLOR_LIGHT_TURQUOISE2,
	_XLS_COLOR_TURQUOISE2,

	_XLS_COLOR_DARK_PURPLE,
	_XLS_COLOR_VIOLET2,
	_XLS_COLOR_CORAL,
	_XLS_COLOR_DARK_RED2,
	_XLS_COLOR_OCEAN_BLUE,
	_XLS_COLOR_TEAL2,
	_XLS_COLOR_ICE_BLUE,
	_XLS_COLOR_BLUE2,

	_XLS_COLOR_SYS_WIND_FG,
	_XLS_COLOR_SYS_WIND_BG 
};

//! Cell fill
enum _XLS_CELL_FILL
{
	_XLS_CELL_FILL_NONE = 0,
	_XLS_CELL_FILL_SOLID,
	_XLS_CELL_FILL_ATEN75,
	_XLS_CELL_FILL_ATEN50,
	_XLS_CELL_FILL_ATEN25,
	_XLS_CELL_FILL_ATEN12,
	_XLS_CELL_FILL_ATEN06,
	_XLS_CELL_FILL_HORIZ_LIN,
	_XLS_CELL_FILL_VERTICAL_LIN,
	_XLS_CELL_FILL_DIAG,
	_XLS_CELL_FILL_INV_DIAG,
	_XLS_CELL_FILL_INTER_DIAG,
	_XLS_CELL_FILL_DIAG_THICK_INTER,
	_XLS_CELL_FILL_HORIZ_LINES_THIN,
	_XLS_CELL_FILL_VERTICAL_LINES_THIN,
	_XLS_CELL_FILL_DIAG_THIN,
	_XLS_CELL_FILL_INV_DIAG_THIN,
	_XLS_CELL_FILL_HORIZ_INT_THIN,
	_XLS_CELL_FILL_HORIZ_INTER_THICK   
};

//! Border lines
enum _XLS_BORDER_STYLE
{
	_XLS_BORDER_STYLE_NONE = 0,
	_XLS_BORDER_STYLE_THIN,
	_XLS_BORDER_STYLE_MEDIUM,
	_XLS_BORDER_STYLE_DASHED,
	_XLS_BORDER_STYLE_DOTTED,
	_XLS_BORDER_STYLE_THICK,
	_XLS_BORDER_STYLE_DOUBLE,
	_XLS_BORDER_STYLE_HAIR    
};

//! Where to put border lines
enum _XLS_BORDER
{
	_XLS_BORDER_BOTTOM = 0,
	_XLS_BORDER_TOP,
	_XLS_BORDER_LEFT,
	_XLS_BORDER_RIGHT 
};

//! Thickness
enum _XLS_THICKNESS
{
	_XLS_THICKNESS_BOLD = 0,
	_XLS_THICKNESS_HALF,
	_XLS_THICKNESS_NORMAL,
	_XLS_THICKNESS_DOUBLE
};

//! Sub/super script
enum _XLS_SUB_SCRIPT
{
	_XLS_SUB_SCRIPT_NONE = 0,
	_XLS_SUB_SCRIPT_SUPER,
	_XLS_SUB_SCRIPT_SUB
};

//! Underlining
enum _XLS_UNDERLINE
{
	_XLS_UNDERLINE_NONE = 0,
	_XLS_UNDERLINE_SINGLE,
	_XLS_UNDERLINE_DOUBLE,
	_XLS_UNDERLINE_SINGLEACC,
	_XLS_UNDERLINE_DOUBLEACC
};

//----------------------------------------------------------------------------
// IXLSFileReader
//----------------------------------------------------------------------------

class IXLSFileReader : public IObject
{
public:
};

//----------------------------------------------------------------------------
// IXLSCellWriter
//----------------------------------------------------------------------------

class IXLSCellWriter : public IObject
{
public:
	//!	Set the foreground color.
	//!	@param		color	The color.
	//!	@return		none.
	virtual _void SetForeColor( _XLS_COLOR color ) PURE;
	//!	Set the background color.
	//!	@param		color	The color.
	//!	@return		none.
	virtual _void SetBKColor( _XLS_COLOR color ) PURE;

	//!	Set the fill style.
	//!	@param		style	The style.
	//!	@return		none.
	virtual _void SetFillStyle( _XLS_CELL_FILL style ) PURE;
	//!	Set the border style.
	//!	@param		border	The border.
	//!	@param		style	The style.
	//!	@return		none.
	virtual _void SetBorderStyle( _XLS_BORDER border, _XLS_BORDER_STYLE style ) PURE;

	//!	Set the font name.
	//!	@param		font_name	The font name.
	//!	@return		none.
	virtual _void SetFontName( WStringPtr font_name ) PURE;
	//!	Set the font color.
	//!	@param		color	The color.
	//!	@return		none.
	virtual _void SetFontColor( _XLS_COLOR color ) PURE;
};

//----------------------------------------------------------------------------
// IXLSWorkSheetWriter
//----------------------------------------------------------------------------

class IXLSWorkSheetWriter : public IObject
{
public:
	//!	Set the column width.
	//!	@param		col		The column number, start from 0.
	//!	@param		width	The column width.
	//!	@return		none.
	virtual _void SetColumnWidth( _dword col, _dword width ) PURE;
	//!	Set the row height.
	//!	@param		row		The row number, start from 0.
	//!	@param		height	The row height.
	//!	@return		none.
	virtual _void SetRowHeight( _dword row, _dword height ) PURE;

	//!	Set the label.
	//!	@param		row		The row number, start from 0.
	//!	@param		col		The column number, start from 0.
	//!	@param		name	The label name.
	//!	@return		The cell writer interface.
	virtual IXLSCellWriterPassRef SetLabel( _dword row, _dword col, WStringPtr name ) PURE;
	//!	Set the number.
	//!	@param		row		The row number, start from 0.
	//!	@param		col		The column number, start from 0.
	//!	@param		value	The value.
	//!	@return		The cell writer interface.
	virtual IXLSCellWriterPassRef SetNumber( _dword row, _dword col, _float value ) PURE;
	//!	Set the number.
	//!	@param		row		The row number, start from 0.
	//!	@param		col		The column number, start from 0.
	//!	@param		value	The value.
	//!	@return		The cell writer interface.
	virtual IXLSCellWriterPassRef SetNumber( _dword row, _dword col, _double value ) PURE;
	//!	Set the number.
	//!	@param		row		The row number, start from 0.
	//!	@param		col		The column number, start from 0.
	//!	@param		value	The value.
	//!	@return		The cell writer interface.
	virtual IXLSCellWriterPassRef SetNumber( _dword row, _dword col, _long value ) PURE;
	//!	Set the number.
	//!	@param		row		The row number, start from 0.
	//!	@param		col		The column number, start from 0.
	//!	@param		value	The value.
	//!	@return		The cell writer interface.
	virtual IXLSCellWriterPassRef SetNumber( _dword row, _dword col, _dword value ) PURE;
	//!	Set the boolean value.
	//!	@param		row		The row number, start from 0.
	//!	@param		col		The column number, start from 0.
	//!	@param		value	The boolean value.
	//!	@return		The cell writer interface.
	virtual IXLSCellWriterPassRef SetBoolean( _dword row, _dword col, _ubool value ) PURE;
};

//----------------------------------------------------------------------------
// IXLSFileWriter
//----------------------------------------------------------------------------

class IXLSFileWriter : public IObject
{
public:
	//!	Create or get the sheet by name.
	//!	@param		name		The sheet name.
	//!	@return		The sheet interface.
	virtual IXLSWorkSheetWriterPassRef GetSheet( WStringPtr name ) PURE;

	//!	Save to file.
	//!	@param		file_name	The absolute file name.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SaveToFile( WStringPtr file_name ) PURE;
};

}