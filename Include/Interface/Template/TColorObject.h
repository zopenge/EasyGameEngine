//! @file     TColorObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TColorObject
//----------------------------------------------------------------------------

template< typename Type >
class TColorObject : public Type
{
protected:
	//!	The color
	Color	mColor;

protected:
	TColorObject( );
	virtual ~TColorObject( );

// IColorObject Interface
public:
	virtual _void			SetAlpha( _float alpha ) override;
	virtual _float			GetAlpha( ) const override;

	virtual _void			SetColor( const Color& color ) override;
	virtual const Color&	GetColor( ) const override;
};

//----------------------------------------------------------------------------
// TColorObject Implementation
//----------------------------------------------------------------------------

template< typename Type >
TColorObject< Type >::TColorObject( )
{
	mColor = Color::cWhite;
}

template< typename Type >
TColorObject< Type >::~TColorObject( )
{
}

template< typename Type >
_void TColorObject< Type >::SetAlpha( _float alpha )
{
	mColor.Alpha( alpha );
}

template< typename Type >
_float TColorObject< Type >::GetAlpha( ) const
{
	return mColor.Alpha( );
}

template< typename Type >
_void TColorObject< Type >::SetColor( const Color& color )
{
	mColor = color;
}

template< typename Type >
const Color& TColorObject< Type >::GetColor( ) const
{
	return mColor;
}

}