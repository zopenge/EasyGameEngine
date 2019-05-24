#pragma once

namespace EGE {

/// <summary>
/// CSV, comma separated values, 
/// files are commonly used to transport large amounts of tabular data between either companies or applications that are not directly connected. 
/// The files are easily editable using common spreadsheet applications like Microsoft Excel.
/// </summary>
class ICSVFile : public IObject {
public:
	//!	Get the rows number.
	//!	@param		none.
	//!	@return		The number of rows.
	virtual _dword GetRows() const PURE;
	//!	Get the columns number.
	//!	@param		none.
	//!	@return		The number of columns.
	virtual _dword GetColumns() const PURE;

	//!	Get the grid string.
	//!	@param		column	The column index ( start from 0 ).
	//!	@param		row		The row index ( start from 0 ).
	//!	@return		The string of grid.
	virtual WStringPtr GetGridString(_dword column, _dword row) const PURE;
};

} // namespace EGE