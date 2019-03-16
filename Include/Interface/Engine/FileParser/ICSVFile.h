//! @file     ICSVFile.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ICSVFile
//----------------------------------------------------------------------------

class ICSVFile : public IBaseFile
{
public:
	//!	Get the rows number.
	//!	@param		none.
	//!	@return		The number of rows.
	virtual _dword GetRows( ) const PURE;
	//!	Get the columns number.
	//!	@param		none.
	//!	@return		The number of columns.
	virtual _dword GetColumns( ) const PURE;

	//!	Get the grid string.
	//!	@param		column	The column index ( start from 0 ).
	//!	@param		row		The row index ( start from 0 ).
	//!	@return		The string of grid.
	virtual WStringPtr GetGridString( _dword column, _dword row ) const PURE;
};

}