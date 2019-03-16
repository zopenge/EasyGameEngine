//! @file     RefOwner.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// RefOwner
//----------------------------------------------------------------------------

template< typename Type >
class RefOwner
{
public:
	RefPtr< Type > mBackupObject;
	RefPtr< Type >& mObject;

public:
	RefOwner( RefPtr< Type >& object );
	~RefOwner( );

public:
	RefOwner< Type >& operator = ( Type* pointer );

public:
	_ubool IsValid( ) const;
	_ubool IsNull( ) const;

	Type& operator * ( ) const;
	Type* operator -> ( )  const;

	template< class ClassType >
	ClassType* cast_static( );
	template< class ClassType >
	const ClassType* cast_static( ) const;

	template< class ClassType >
	ClassType* cast_dynamic( );
	template< class ClassType >
	const ClassType* cast_dynamic( ) const;
};

//----------------------------------------------------------------------------
// RefOwner Implementation
//----------------------------------------------------------------------------

template< typename Type >
RefOwner< Type >::RefOwner( RefPtr< Type >& object ) : mObject( object )
{
	mBackupObject = object;
}

template< typename Type >
RefOwner< Type >::~RefOwner( )
{
	mObject = mBackupObject;
}

template< typename Type >
RefOwner< Type >& RefOwner< Type >::operator = ( Type* pointer )
{
	mObject = pointer;

	return *this;
}

template< typename Type >
_ubool RefOwner< Type >::IsValid( ) const
{
	return mObject != _null;
}

template< typename Type >
_ubool RefOwner< Type >::IsNull( ) const
{
	return mObject == _null;
}

template< typename Type >
Type& RefOwner< Type >::operator * ( ) const
{
	return *mObject;
}

template< typename Type >
Type* RefOwner< Type >::operator -> ( )  const
{
	return mObject;
}

template< typename Type >
template< class ClassType >
ClassType* RefOwner< Type >::cast_static( )
{
	return static_cast< ClassType* >( mObject );
}

template< typename Type >
template< class ClassType >
const ClassType* RefOwner< Type >::cast_static( ) const
{
	return static_cast< const ClassType* >( mObject );
}

template< typename Type >
template< class ClassType >
ClassType* RefOwner< Type >::cast_dynamic( )
{
	return dynamic_cast< ClassType* >( mObject );
}

template< typename Type >
template< class ClassType >
const ClassType* RefOwner< Type >::cast_dynamic( ) const
{
	return dynamic_cast< const ClassType* >( mObject );
}

}
