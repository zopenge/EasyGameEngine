//! @file     Formula.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Formula
//----------------------------------------------------------------------------

// (c) Peter Kankowski, 2007. http://smallcode.weblogs.us mailto:kankowski@narod.ru
class Formula
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

private:
	typedef _chara EVAL_CHAR;

private:
	_EXPR_EVAL_ERR		_err;
	const EVAL_CHAR*	_err_pos;
	_int				_paren_count;

private:
	// Parse a number or an expression in parenthesis
	double ParseAtom(const EVAL_CHAR*& expr);

	// Parse multiplication and division
	double ParseFactors(const EVAL_CHAR*& expr);

	// Parse addition and subtraction
	double ParseSummands(const EVAL_CHAR*& expr);

	double Eval(const EVAL_CHAR* expr);

	_EXPR_EVAL_ERR GetErr();
	const EVAL_CHAR* GetErrPos();

public:
	Formula( );
	~Formula( );

public:
	static _double Calculate( AStringPtr expression, _EXPR_EVAL_ERR* err_code = _null );
	static _double Calculate( WStringPtr expression, _EXPR_EVAL_ERR* err_code = _null );
};

}