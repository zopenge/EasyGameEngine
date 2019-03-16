//! @file     TPhysxShape.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TPhysxShape
//----------------------------------------------------------------------------

template< typename T, typename ShapePHIType, typename Type >
class TPhysxShape : public INTERFACE_OBJECT_IMPL( Type )
{
protected:
	//!	The shape type
	IPhysxShape::_TYPE		mShapeType;

	//!	The shape resource
	RefPtr< ShapePHIType >	mShapeResource;

protected:
	TPhysxShape( IPhysxShape::_TYPE type, ShapePHIType* shape );
	virtual ~TPhysxShape( );

// IObject Interface
public:
	virtual IObject*			CloneTo( _ubool standalone ) const override;

// IPhysxShape Interface
public:
	virtual IPhysxShape::_TYPE	GetType( ) const override;
	virtual ShapePHIRef			GetShapeResource( ) override;
};

//----------------------------------------------------------------------------
// TPhysxShape Implementation
//----------------------------------------------------------------------------

template< typename T, typename ShapePHIType, typename Type >
TPhysxShape< T, ShapePHIType, Type >::TPhysxShape( IPhysxShape::_TYPE type, ShapePHIType* shape ) : mShapeType( type ), mShapeResource( shape )
{
}

template< typename T, typename ShapePHIType, typename Type >
TPhysxShape< T, ShapePHIType, Type >::~TPhysxShape( )
{
}

template< typename T, typename ShapePHIType, typename Type >
IObject* TPhysxShape< T, ShapePHIType, Type >::CloneTo( _ubool standalone ) const
{
	ShapePHIRef shape = gDynamicPHI->CloneShape( mShapeResource );
	if ( shape.IsNull( ) )
		return _null;

	return new T( shape.cast_static< ShapePHIType >( ) );
}

template< typename T, typename ShapePHIType, typename Type >
IPhysxShape::_TYPE TPhysxShape< T, ShapePHIType, Type >::GetType( ) const
{
	return mShapeType;
}

template< typename T, typename ShapePHIType, typename Type >
ShapePHIRef TPhysxShape< T, ShapePHIType, Type >::GetShapeResource( )
{
	return mShapeResource.template cast_static< ShapePHI >( );
}

}