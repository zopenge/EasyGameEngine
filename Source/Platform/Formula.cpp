//! @file     Formula.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Formula Implementation
//----------------------------------------------------------------------------

Formula::Formula( ) 
{
}

Formula::~Formula( )
{
}

double Formula::ParseAtom(const EVAL_CHAR*& expr) 
{
	// Skip spaces
	while(*expr == ' ')
		expr++;

	// Handle the sign before parenthesis (or before number)
	bool negative = false;
	if(*expr == '-') {
		negative = true;
		expr++;
	}
	if(*expr == '+') {
		expr++;
	}

	// Check if there is parenthesis
	if(*expr == '(') {
		expr++;
		_paren_count++;
		double res = ParseSummands(expr);
		if(*expr != ')') {
			// Unmatched opening parenthesis
			_err = _EEE_PARENTHESIS;
			_err_pos = expr;
			return 0;
		}
		expr++;
		_paren_count--;
		return negative ? -res : res;
	}

	// It should be a number; convert it to double
	char* end_ptr;
	double res = strtod(expr, &end_ptr);
	if(end_ptr == expr) {
		// Report error
		_err = _EEE_WRONG_CHAR;
		_err_pos = expr;
		return 0;
	}
	// Advance the pointer and return the result
	expr = end_ptr;
	return negative ? -res : res;
}

double Formula::ParseFactors(const EVAL_CHAR*& expr) 
{
	double num1 = ParseAtom(expr);
	for(;;) {
		// Skip spaces
		while(*expr == ' ')
			expr++;
		// Save the operation and position
		EVAL_CHAR op = *expr;
		const EVAL_CHAR* pos = expr;
		if(op != '/' && op != '*')
			return num1;
		expr++;
		double num2 = ParseAtom(expr);
		// Perform the saved operation
		if(op == '/') {
			// Handle division by zero
			if(num2 == 0) {
				_err = _EEE_DIVIDE_BY_ZERO;
				_err_pos = pos;
				return 0;
			}
			num1 /= num2;
		}
		else
			num1 *= num2;
	}
}

double Formula::ParseSummands(const EVAL_CHAR*& expr) 
{
	double num1 = ParseFactors(expr);
	for(;;) {
		// Skip spaces and tables
		while(*expr == ' ' || *expr == '\t')
			expr++;
		EVAL_CHAR op = *expr;
		if(op != '-' && op != '+' && op != '~')
			return num1;
		expr++;
		double num2 = ParseFactors(expr);
		if(op == '-')
			num1 -= num2;
		else if(op == '+')
			num1 += num2;
		else
			num1 = Random::Gen( num1, num2 );
	}
}

double Formula::Eval(const EVAL_CHAR* expr) 
{
	_paren_count = 0;
	_err = _EEE_NO_ERROR;
	double res = ParseSummands(expr);
	// Now, expr should point to '\0', and _paren_count should be zero
	if(_paren_count != 0 || *expr == ')') {
		_err = _EEE_PARENTHESIS;
		_err_pos = expr;
		return 0;
	}
	if(*expr != '\0') {
		_err = _EEE_WRONG_CHAR;
		_err_pos = expr;
		return 0;
	}
	return res;
}

Formula::_EXPR_EVAL_ERR Formula::GetErr() 
{
	return _err;
}

const Formula::EVAL_CHAR* Formula::GetErrPos() 
{
	return _err_pos;
}

_double Formula::Calculate( AStringPtr expression, _EXPR_EVAL_ERR* err_code )
{
	if ( expression.IsEmpty( ) )
		return 0.0;

	// Calculate the expression
	Formula exp_eval;
	_double value = exp_eval.Eval( expression.Str( ) );

	// Feedback the error code
	if ( err_code != _null )
		*err_code = exp_eval.GetErr( );

	return value;
}

_double Formula::Calculate( WStringPtr expression, _EXPR_EVAL_ERR* err_code ) 
{
	return Calculate( AString( ).FromString( expression ), err_code );
}