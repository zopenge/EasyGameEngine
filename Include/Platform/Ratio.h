//! @file     Ratio.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Ratio
//----------------------------------------------------------------------------

class Ratio
{
public:
	static Ratio cNull;

public:
	//£¡	The scale
	_float	mScale;
	//!	The base size
	PointF	mBaseSize;
	//!	The offset of left and top
	PointF	mOffset;

public:
	Ratio( );
	Ratio( const Ratio& ratio );
	Ratio( const Vector2& size );
	Ratio( _float width, _float height );

public:
	template< typename Type >
	PointF ConvertPos( const Type& pos ) const;
	template< typename Type >
	PointF InverseConvertPos( const Type& pos ) const;

	_ubool operator == ( const Ratio& ratio ) const;
	_ubool operator != ( const Ratio& ratio ) const;

public:
	//!	Initialize.
	_void Init( _float width, _float height );
	//!	Update size.
	PointF UpdateSize( _float width, _float height );
	PointU UpdateSize( _dword width, _dword height );

	//!	Get the base size.
	Vector2 GetBaseSize( ) const;
	//!	Get the offset.
	Vector2 GetOffset( ) const;

	//!	Fix size.
	PointU FixSizeU( const PointU& size ) const;
	PointF FixSizeF( const PointU& size ) const;

public:
	//!	Fix size by ratio info.
	static PointU FixSizeU( const Ratio& ratio, const PointU& size );
	static PointF FixSizeF( const Ratio& ratio, const PointU& size );

	//!	Keep the ratio and use the new size to create ratio.
	static Ratio Create( const Ratio& ratio, const PointU& size );
};

//----------------------------------------------------------------------------
// Ratio Implementation
//----------------------------------------------------------------------------

template< typename Type >
PointF Ratio::ConvertPos( const Type& pos ) const
{
	if ( mScale > 0 )
		return PointF( ( (_float) pos.x - mOffset.x ) / mScale, ( (_float) pos.y - mOffset.y ) / mScale );
	else
		return PointF( 0.0f, 0.0f );
}

template< typename Type >
PointF Ratio::InverseConvertPos( const Type& pos ) const
{
	if ( mScale > 0 )
		return PointF( (_float) pos.x * mScale + mOffset.x, (_float) pos.y * mScale + mOffset.y );
	else
		return PointF( 0.0f, 0.0f );
}

}