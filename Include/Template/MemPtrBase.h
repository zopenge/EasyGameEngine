//! @file     MemPtrBase.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// MemPtrBase
//----------------------------------------------------------------------------

template< typename Type > 
class MemPtrBase
{
protected:
	_ubool	mAutoDelete;
	Type*	mPointer;

protected:
	MemPtrBase( );
	MemPtrBase( Type* pointer );
	~MemPtrBase( );

public:
	bool operator == ( const MemPtrBase& memptr ) const;
	bool operator != ( const MemPtrBase& memptr ) const;
	bool operator == ( const Type* pointer ) const;
	bool operator != ( const Type* pointer ) const;
	bool operator == ( Type* pointer ) const;
	bool operator != ( Type* pointer ) const;

	operator Type* ( ) const;
	operator const Type* ( ) const;

	operator _void* ( ) const;
	operator const _void* ( ) const;

	_void EnableAutoDelete( _ubool enable );
	_ubool IsEnableAutoDelete( ) const;

	_ubool IsNull( ) const;
	_ubool IsValid( ) const;

	Type* GetPointer( );
	const Type* GetPointer( ) const;

	_void SetPointer( Type* ptr );

	Type*& GetRawRef( );

	Type& operator * ( ) const;
	Type* operator -> ( )  const;
};

//----------------------------------------------------------------------------
// MemPtrBase Implementation
//----------------------------------------------------------------------------

template< typename Type >
MemPtrBase< Type >::MemPtrBase( )
{
	mAutoDelete	= _true;
	mPointer	= _null;
}

template< typename Type >
MemPtrBase< Type >::MemPtrBase( Type* pointer )
{
	mAutoDelete	= _true;
	mPointer	= pointer;
}

template< typename Type >
MemPtrBase< Type >::~MemPtrBase( )
{
	// The pointer must be clear in inherited class
	EGE_ASSERT( mPointer == _null );
}

template< typename Type >
bool MemPtrBase< Type >::operator == ( const MemPtrBase& memptr ) const
{
	return mPointer == memptr.mpointer;
}

template< typename Type >
bool MemPtrBase< Type >::operator != ( const MemPtrBase& memptr ) const
{
	return mPointer != memptr.mpointer;
}

template< typename Type >
bool MemPtrBase< Type >::operator == ( const Type* pointer ) const
{
	return mPointer == pointer;
}

template< typename Type >
bool MemPtrBase< Type >::operator != ( const Type* pointer ) const
{
	return mPointer != pointer;
}

template< typename Type >
bool MemPtrBase< Type >::operator == ( Type* pointer ) const
{
	return mPointer == pointer;
}

template< typename Type >
bool MemPtrBase< Type >::operator != ( Type* pointer ) const
{
	return mPointer != pointer;
}

template< typename Type >
_void MemPtrBase< Type >::EnableAutoDelete( _ubool enable )
{
	mAutoDelete = enable;
}

template< typename Type >
_ubool MemPtrBase< Type >::IsEnableAutoDelete( ) const
{
	return mAutoDelete;
}

template< typename Type >
MemPtrBase< Type >::operator Type* ( ) const
{
	return mPointer;
}

template< typename Type >
MemPtrBase< Type >::operator const Type* ( ) const
{
	return mPointer;
}

template< typename Type >
MemPtrBase< Type >::operator _void* ( ) const
{
	return mPointer;
}

template< typename Type >
MemPtrBase< Type >::operator const _void* ( ) const
{
	return mPointer;
}

template< typename Type >
_ubool MemPtrBase< Type >::IsNull( ) const
{
	return mPointer == _null;
}

template< typename Type >
_ubool MemPtrBase< Type >::IsValid( ) const
{
	return mPointer != _null;
}

template< typename Type >
Type* MemPtrBase< Type >::GetPointer( )
{
	return mPointer;
}

template< typename Type >
const Type* MemPtrBase< Type >::GetPointer( ) const
{
	return mPointer;
}

template< typename Type >
_void MemPtrBase< Type >::SetPointer( Type* ptr )
{
	mPointer = ptr;
}

template< typename Type >
Type*& MemPtrBase< Type >::GetRawRef( )
{
	return mPointer;
}

template< typename Type >
Type& MemPtrBase< Type >::operator * ( ) const
{
	return *mPointer;
}

template< typename Type >
Type* MemPtrBase< Type >::operator -> ( )  const
{
	return mPointer;
}

}