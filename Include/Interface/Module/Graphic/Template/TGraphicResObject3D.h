//! @file     TGraphicResObject3D.h
//! @author   LiCode
//! @version  1.1
//! @date     2015.06
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TGraphicResObject3D
//----------------------------------------------------------------------------

template< typename Type >
class TGraphicResObject3D : public TGraphicResObject< Type >
{
protected:
	typedef TGraphicResObject< Type > TBaseClass;

protected:
	Transform3D			mTransform3D;
	AxisAlignedBox		mAABox;

	IGraphicEffectRef	mEffect;

protected:
	Matrix4 GetTransform4x4( const Matrix4& transform ) const;

public:
	TGraphicResObject3D( );
	virtual ~TGraphicResObject3D( );

// IGraphicResObject Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_GRAPHIC_RESOBJ_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Interface/Module/Graphic/Methods/GraphicResObjectMethods.h"
	#undef DEFINE_GRAPHIC_RESOBJ_METHOD
};

//----------------------------------------------------------------------------
// TGraphicResObject3D Implementation
//----------------------------------------------------------------------------

template< typename Type >
TGraphicResObject3D< Type >::TGraphicResObject3D( )
{
	mTransform3D	= Transform3D::cZero;
	mAABox			= AxisAlignedBox::cNullBox;
}

template< typename Type >
TGraphicResObject3D< Type >::~TGraphicResObject3D( )
{
}

template< typename Type >
Matrix4 TGraphicResObject3D< Type >::GetTransform4x4( const Matrix4& transform ) const
{
	return mTransform3D.ToMatrix( ) * transform;
}

template< typename Type >
_void TGraphicResObject3D< Type >::SetTransform3D( const Transform3D& transform )
{
	mTransform3D = transform;
}

template< typename Type >
Transform3D TGraphicResObject3D< Type >::GetTransform3D( ) const
{
	return mTransform3D;
}

template< typename Type >
_void TGraphicResObject3D< Type >::SetAABox( const AxisAlignedBox& box )
{
	mAABox = box;
}

template< typename Type >
OrientedBox2D TGraphicResObject3D< Type >::GetOBBox( ) const
{
	return TBaseClass::GetOBBox( );
}

template< typename Type >
OrientedBox2D TGraphicResObject3D< Type >::GetOriginalOBBox( ) const
{
	return TBaseClass::GetOriginalOBBox( );
}

template< typename Type >
AxisAlignedBox TGraphicResObject3D< Type >::GetAABox( ) const
{
	return mAABox * mTransform3D.ToMatrix( );
}

template< typename Type >
AxisAlignedBox TGraphicResObject3D< Type >::GetOriginAABox( ) const
{
	return mAABox;
}

template< typename Type >
Box TGraphicResObject3D< Type >::GetBox( ) const
{
	const AxisAlignedBox& aabox = mAABox;

	Box box( aabox.mMinVector, aabox.mMaxVector );
	return box * mTransform3D.ToMatrix( );
}

template< typename Type >
_ubool TGraphicResObject3D< Type >::TestPoint( const Matrix3& camera_transform, const Vector2& position ) const
{
	Matrix3 inverse_transform = camera_transform;
	inverse_transform.Inverse( );

	return TestPoint( position * inverse_transform );
}

template< typename Type >
_ubool TGraphicResObject3D< Type >::TestPoint( const Vector2& position ) const
{
	return _false;
}

template< typename Type >
_ubool TGraphicResObject3D< Type >::TestRegion( const RectF& region ) const
{
	return _false;
}

template< typename Type >
_void TGraphicResObject3D< Type >::RenderOverlay( IGraphicScene* scene, const Matrix3& transform, const Color& color )
{
}

template< typename Type >
_void TGraphicResObject3D< Type >::RenderScreenAlignedBillboard( IGraphicScene* scene, const Matrix3& matrix, const Vector3& position, const Color& color )
{
}

template< typename Type >
_void TGraphicResObject3D< Type >::RenderViewpointOrientedBillboard( IGraphicScene* scene, const Matrix3& matrix, const Vector3& position, const Color& color )
{
}

template< typename Type >
_void TGraphicResObject3D< Type >::RenderAxialBillboard( IGraphicScene* scene, const Matrix3& matrix, const Vector3& position, const Vector3& axis, const Color& color, const Vector3* result_scaling )
{
}

template< typename Type >
_void TGraphicResObject3D< Type >::RenderRectBillboard( IGraphicScene* scene, const Matrix3& matrix, const Vector3& position, const Color& color )
{
}

template< typename Type >
_void TGraphicResObject3D< Type >::RenderWireFrame( IGraphicScene* scene, const Matrix4& transform, const Color& color )
{

}

template< typename Type >
_void TGraphicResObject3D< Type >::RenderNormal( IGraphicScene* scene, const Matrix4& transform, const Color& color )
{

}

template< typename Type >
_void TGraphicResObject3D< Type >::RenderAxisAlignedBox( IGraphicScene* scene, const Matrix4& transform, const Color& color )
{

}

template< typename Type >
_void TGraphicResObject3D< Type >::RenderStroke( IGraphicScene* viewport, const Matrix4& transform, const Color& color )
{

}

template< typename Type >
_void TGraphicResObject3D< Type >::RenderZBuffer( IGraphicScene* viewport, const Matrix4& transform )
{

}

template< typename Type >
_void TGraphicResObject3D< Type >::RenderGeometry( IGraphicScene* viewport, const Matrix4& transform, const Color& color )
{

}

}