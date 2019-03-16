//! @file     MeasurableObject.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// MeasurableObject
//----------------------------------------------------------------------------

class MeasurableObject : public INTERFACE_OBJECT_IMPL( IMeasurableObject )
{
private:
	_dword	mLineNumber;
	Vector2	mSize;
	Vector2	mPosition;

public:
	MeasurableObject( const Vector2& size );
	virtual ~MeasurableObject( );

// IMeasurableObject Interface
public:
	virtual _void	SetLineNumber( _dword number ) override;
	virtual _dword	GetLineNumber( ) const override;

	virtual RectF	GetRegion( ) const override;
	virtual _float	GetLeft( ) const override;
	virtual _float	GetBottom( ) const override;
	virtual _float	GetBaseLineHeight( ) const override;

	virtual Vector2	GetPosition( ) const override;
	virtual _void	SetPosition( const Vector2& pos ) override;

	virtual _float	GetSpace( ) const override;

	virtual _ubool	IsWordSeparatorTag( ) const override;
	virtual _ubool	IsNewLineTag( ) const override;
};

//----------------------------------------------------------------------------
// MeasurableObject Implementation
//----------------------------------------------------------------------------

}