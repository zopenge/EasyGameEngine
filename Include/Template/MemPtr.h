//! @file     MemPtr.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// MemPtr
//----------------------------------------------------------------------------

template< typename Type > 
class MemPtr : public MemPtrBase< Type >
{
private:
	typedef MemPtrBase< Type > TBaseClass;

public:
	MemPtr( );
	MemPtr( Type* pointer );
	~MemPtr( );

public:
	Type* Create( const Type* pointer = _null );
	_void Clear( );
};

//----------------------------------------------------------------------------
// MemPtr Implementation
//----------------------------------------------------------------------------

template< typename Type >
MemPtr< Type >::MemPtr( )
{
}

template< typename Type >
MemPtr< Type >::MemPtr( Type* pointer ) : TBaseClass( pointer )
{
}

template< typename Type >
MemPtr< Type >::~MemPtr( )
{
	Clear( );
}

template< typename Type >
Type* MemPtr< Type >::Create( const Type* pointer )
{
	Clear( );

	this->mPointer = new Type( );

	// Copy the pointer data
	if ( pointer != _null )
		*this->mPointer = *pointer;

	return this->mPointer;
}

template< typename Type >
_void MemPtr< Type >::Clear( )
{
	if ( this->IsEnableAutoDelete( ) )
		delete this->mPointer;

	this->mPointer = _null;
}

}