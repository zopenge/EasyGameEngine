//! @file     PassRefPtr.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// PassRefPtr
//----------------------------------------------------------------------------

template< typename Type > 
class PassRefPtr : public Ref< Type >
{
protected:
	typedef Ref< Type > TBaseClass;

protected:
	//! We disable construct or copy from Ref< Type >
	PassRefPtr( Ref< Type > );
	PassRefPtr& operator = ( const Ref< Type >& );

public:
	PassRefPtr( );
	PassRefPtr( Type* object );
	PassRefPtr( const PassRefPtr< Type >& refptr );
	template< typename AnyType >
	PassRefPtr( const PassRefPtr< AnyType >& refptr );
	~PassRefPtr( );

public:
	PassRefPtr< Type >& operator = ( Type* pointer );
	PassRefPtr< Type >& operator = ( const PassRefPtr< Type >& refptr );
};

//----------------------------------------------------------------------------
// PassRefPtr Implementation
//----------------------------------------------------------------------------

template< typename Type >
PassRefPtr< Type >::PassRefPtr( )
{
}

template< typename Type >
PassRefPtr< Type >::PassRefPtr( Type* object )
{
	TBaseClass::mObject = object;
}

template< typename Type >
PassRefPtr< Type >::PassRefPtr( const PassRefPtr< Type >& refptr )
{
	if ( refptr.GetPtr( ) != _null )
		refptr.GetPtr( )->AddRef( );

	TBaseClass::mObject = refptr.GetPtr( );
}

template< typename Type >
template< typename AnyType >
PassRefPtr< Type >::PassRefPtr( const PassRefPtr< AnyType >& refptr )
{
	if ( refptr.GetPtr( ) != _null )
		refptr.GetPtr( )->AddRef( );

	TBaseClass::mObject = static_cast< Type* >( refptr.GetPtr( ) );
}

template< typename Type >
PassRefPtr< Type >::~PassRefPtr( )
{
}

template< typename Type >
PassRefPtr< Type >& PassRefPtr< Type >::operator = ( Type* pointer )
{
	// If the pointer is same then we skip to decrease referenced counter, or else the ref counter will be sub by 2 times
	if ( TBaseClass::mObject != pointer )
		this->Clear( );

	TBaseClass::mObject = pointer;

	return *this;
}

template< typename Type >
PassRefPtr< Type >& PassRefPtr< Type >::operator = ( const PassRefPtr< Type >& refptr )
{
	this->Clear( );

	if ( refptr.GetPtr( ) != _null )
		refptr.GetPtr( )->AddRef( );

	TBaseClass::mObject = refptr.GetPtr( );

	return *this;
}

}