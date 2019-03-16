//! @file     IFormula.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IFormula
//----------------------------------------------------------------------------

class IFormula
{
public:
	//! The Error Codes
	enum _EXPR_EVAL_ERR 
	{
		_EEE_NO_ERROR		= 0,
		_EEE_PARENTHESIS	= 1,
		_EEE_WRONG_CHAR		= 2,
		_EEE_DIVIDE_BY_ZERO = 3
	};

public:
	//!	Calculate the expression.
	//!	@param		expression	The expression string.
	//!	@param		err_code	The error code.
	//!	@return		The result of expression.
	virtual _double Calculate( AStringPtr expression, _EXPR_EVAL_ERR* err_code = _null ) const PURE;
	//!	Calculate the expression.
	//!	@param		expression	The expression string.
	//!	@param		err_code	The error code.
	//!	@return		The result of expression.
	virtual _double Calculate( WStringPtr expression, _EXPR_EVAL_ERR* err_code = _null ) const PURE;
};

}