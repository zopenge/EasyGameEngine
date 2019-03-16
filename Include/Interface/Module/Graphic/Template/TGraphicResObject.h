//! @file     TGraphicResObject.h
//! @author   LiCode
//! @version  1.1
//! @date     2015.06
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TGraphicResObject
//----------------------------------------------------------------------------

template< typename Type >
class TGraphicResObject : public Type
{
protected:
	Color				mColor;
	Transform2D			mTransform2D;

	IGraphicEffectRef	mEffect;

protected:
	Matrix3 GetTransform3x3( const Matrix3& transform ) const;

public:
	TGraphicResObject( );
	virtual ~TGraphicResObject( );

// IGraphicResObject Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_GRAPHIC_RESOBJ_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Interface/Module/Graphic/Methods/GraphicResObjectMethods.h"
	#undef DEFINE_GRAPHIC_RESOBJ_METHOD
};

//----------------------------------------------------------------------------
// TGraphicResObject Implementation
//----------------------------------------------------------------------------

template< typename Type >
TGraphicResObject< Type >::TGraphicResObject( )
{
	mColor			= Color::cWhite;
	mTransform2D	= Transform2D::cZero;
}

template< typename Type >
TGraphicResObject< Type >::~TGraphicResObject( )
{
}

template< typename Type >
Matrix3 TGraphicResObject< Type >::GetTransform3x3( const Matrix3& transform ) const
{
	return mTransform2D.ToMatrix( ) * transform;
}

template< typename Type >
_void TGraphicResObject< Type >::SetEffect( IGraphicEffect* effect )
{
	EGE_ASSERT( effect != _null );

	mEffect = effect;
}

template< typename Type >
IGraphicEffect* TGraphicResObject< Type >::GetEffect( ) const
{
	return mEffect;
}

template< typename Type >
_void TGraphicResObject< Type >::SetColor( const Color& color )
{
	mColor = color;
}

template< typename Type >
const Color& TGraphicResObject< Type >::GetColor( ) const
{
	return mColor;
}

template< typename Type >
_void TGraphicResObject< Type >::SetPosition2D( const Vector2& position )
{
	mTransform2D.mPosition = position;
}

template< typename Type >
Vector2 TGraphicResObject< Type >::GetPosition2D( ) const
{
	return mTransform2D.mPosition;
}

template< typename Type >
_void TGraphicResObject< Type >::SetScale2D( const Vector2& scale )
{
	mTransform2D.mScale = scale;
}

template< typename Type >
Vector2 TGraphicResObject< Type >::GetScale2D( ) const
{
	return mTransform2D.mScale;
}

template< typename Type >
_void TGraphicResObject< Type >::SetTransform2D( const Transform2D& transform )
{
	mTransform2D = transform;
}

template< typename Type >
Transform2D TGraphicResObject< Type >::GetTransform2D( ) const
{
	return mTransform2D;
}

template< typename Type >
_void TGraphicResObject< Type >::SetTransform3D( const Transform3D& transform )
{

}

template< typename Type >
Transform3D TGraphicResObject< Type >::GetTransform3D( ) const
{
	return Transform3D::cZero;
}

template< typename Type >
_void TGraphicResObject< Type >::SetAABox( const AxisAlignedBox& box )
{

}

template< typename Type >
OrientedBox2D TGraphicResObject< Type >::GetOBBox( ) const
{
	return OrientedBox2D::cNull;
}

template< typename Type >
OrientedBox2D TGraphicResObject< Type >::GetOriginalOBBox( ) const
{
	return OrientedBox2D::cNull;
}

template< typename Type >
AxisAlignedBox TGraphicResObject< Type >::GetAABox( ) const
{
	return AxisAlignedBox::cNullBox;
}

template< typename Type >
AxisAlignedBox TGraphicResObject< Type >::GetOriginAABox( ) const
{
	return AxisAlignedBox::cNullBox;
}

template< typename Type >
Box TGraphicResObject< Type >::GetBox( ) const
{
	return Box::cNullBox;
}

template< typename Type >
_ubool TGraphicResObject< Type >::TestPoint( const Matrix3& camera_transform, const Vector2& position ) const
{
	Matrix3 inverse_transform = camera_transform;
	inverse_transform.Inverse( );

	return TestPoint( position * inverse_transform );
}

template< typename Type >
_ubool TGraphicResObject< Type >::TestPoint( const Vector2& position ) const
{
	return _false;
}

template< typename Type >
_ubool TGraphicResObject< Type >::TestRegion( const RectF& region ) const
{
	return _false;
}

template< typename Type >
_void TGraphicResObject< Type >::RenderOverlay( IGraphicScene* scene, const Matrix3& transform, const Color& color )
{
}

template< typename Type >
_void TGraphicResObject< Type >::RenderScreenAlignedBillboard( IGraphicScene* scene, const Matrix3& matrix, const Vector3& position, const Color& color )
{
}

template< typename Type >
_void TGraphicResObject< Type >::RenderViewpointOrientedBillboard( IGraphicScene* scene, const Matrix3& matrix, const Vector3& position, const Color& color )
{
}

template< typename Type >
_void TGraphicResObject< Type >::RenderAxialBillboard( IGraphicScene* scene, const Matrix3& matrix, const Vector3& position, const Vector3& axis, const Color& color, const Vector3* result_scaling )
{
}

template< typename Type >
_void TGraphicResObject< Type >::RenderRectBillboard( IGraphicScene* scene, const Matrix3& matrix, const Vector3& position, const Color& color )
{
}

template< typename Type >
_void TGraphicResObject< Type >::RenderWireFrame( IGraphicScene* scene, const Matrix4& transform, const Color& color )
{

}

template< typename Type >
_void TGraphicResObject< Type >::RenderNormal( IGraphicScene* scene, const Matrix4& transform, const Color& color )
{

}

template< typename Type >
_void TGraphicResObject< Type >::RenderAxisAlignedBox( IGraphicScene* scene, const Matrix4& transform, const Color& color )
{

}

template< typename Type >
_void TGraphicResObject< Type >::RenderStroke( IGraphicScene* viewport, const Matrix4& transform, const Color& color )
{

}

template< typename Type >
_void TGraphicResObject< Type >::RenderZBuffer( IGraphicScene* viewport, const Matrix4& transform )
{

}

template< typename Type >
_void TGraphicResObject< Type >::RenderGeometry( IGraphicScene* viewport, const Matrix4& transform, const Color& color )
{

}

}