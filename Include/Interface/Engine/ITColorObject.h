//! @file     ITColorObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ITColorObject
//----------------------------------------------------------------------------

template< typename Type >
class ITColorObject : public Type
{
public:
	//!	Set the alpha.
	//!	@param		alpha	The alpha.
	//!	@return		none.
	virtual _void SetAlpha( _float alpha ) PURE;
	//!	Get the alpha.
	//!	@param		none.
	//!	@return		The alpha.
	virtual _float GetAlpha( ) const PURE;

	//!	Set the color.
	//!	@param		color	The color.
	//!	@return		none.
	virtual _void SetColor( const Color& color ) PURE;
	//!	Get the color.
	//!	@param		none.
	//!	@return		The color.
	virtual const Color& GetColor( ) const PURE;
};

}