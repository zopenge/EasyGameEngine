//! @file     Formula.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// Formula Implementation
//----------------------------------------------------------------------------

Formula::Formula( ) 
{
}

Formula::~Formula( )
{
}

_double Formula::Calculate( AStringPtr expression, _EXPR_EVAL_ERR* err_code ) const
{
	if ( expression.IsEmpty( ) )
		return 0.0;

	// Calculate the expression
	ExprEval exp_eval;
	_double value = exp_eval.Eval( expression.Str( ) );

	// Feedback the error code
	if ( err_code != _null )
		*err_code = exp_eval.GetErr( );

	return value;
}

_double Formula::Calculate( WStringPtr expression, _EXPR_EVAL_ERR* err_code ) const
{
	return Calculate( AString( ).FromString( expression ), err_code );
}