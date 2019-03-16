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

class Formula : public IFormula
{
public:
	Formula( );
	virtual ~Formula( );

// IFormula Interface
public:
	virtual _double Calculate( AStringPtr expression, _EXPR_EVAL_ERR* err_code = _null ) const override;
	virtual _double Calculate( WStringPtr expression, _EXPR_EVAL_ERR* err_code = _null ) const override;
};

}