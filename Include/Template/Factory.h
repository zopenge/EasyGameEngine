//! @file     Factory.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Helpful Macros
//----------------------------------------------------------------------------

#define REGISTER_CREATION_METHOD_WITH_FACTORY( factory, key, base_class, derived_class )		\
	static FactoryMethod< base_class, derived_class > s##base_class##_derived_class##method;	\
	factory.RegisterMethod( key, &s##base_class##_derived_class##method )

#define REGISTER_CREATION_METHOD( key, base_class, derived_class )								\
	static FactoryMethod< base_class, derived_class > s##base_class##_derived_class##method;	\
	RegisterMethod( key, &s##base_class##_derived_class##method )

//----------------------------------------------------------------------------
// EmptyKeyProcessor
//----------------------------------------------------------------------------

template< typename KeyType >
struct EmptyKeyProcessor
{
	// Nothing to do with the key
	_void operator ( ) ( KeyType& ) const 
		{ }
};

//----------------------------------------------------------------------------
// LowercaseStringKeyProcessor
//----------------------------------------------------------------------------

//! Key processors for strings to lowercase
template< typename KeyType >
struct LowercaseStringKeyProcessor
{
	_void operator ( ) ( KeyType& key ) const	
		{ key.Lowercase( );	}
};

//----------------------------------------------------------------------------
// UppercaseStringKeyProcessor
//----------------------------------------------------------------------------

//! Key processors for strings to uppercase
template< typename KeyType >
struct UppercaseStringKeyProcessor
{
	_void operator ( ) ( KeyType& key ) const	
		{ key.Uppercase( );	}
};

//----------------------------------------------------------------------------
// FactoryMethodBase
//----------------------------------------------------------------------------

template< typename BaseType >
struct FactoryMethodBase
{
	//!	Create object from the given derived object in heap
	template< typename DerivedType >
	BaseType* operator ( ) ( const DerivedType& rhs ) const
		{ return new DerivedType( rhs ); }

	//!	Create the object from heap.
	virtual BaseType* operator ( ) ( ) const PURE;
	//!	Get the size of object in bytes.
	virtual _dword Size( ) const PURE;
};

//----------------------------------------------------------------------------
// FactoryMethod
//----------------------------------------------------------------------------

template< typename BaseType, class DerivedType >
struct FactoryMethod : public FactoryMethodBase< BaseType >
{
	virtual BaseType* operator ( ) ( ) const
		{ return new DerivedType( ); }

	virtual _dword Size( ) const
		{ return sizeof( DerivedType ); }
};

//----------------------------------------------------------------------------
// Factory
//----------------------------------------------------------------------------

template< typename BaseType, typename KeyType, class KeyProcessorType = EmptyKeyProcessor< KeyType > >
class Factory
{
private:
	typedef FactoryMethodBase< BaseType >	MethodType;
	typedef Map< MethodType, KeyType >		MethodMap;

private:
	//!	The registered factory methods
	MethodMap			mFactoryMethods;
	//!	The key processor
	KeyProcessorType	mKeyProcessor;

public:
	Factory( );
	~Factory( );

public:
	//!	Register the factory method.
	//!	@remark		You must make sure the method pointer is available, because we just use the address without copy and clone operation.
	//!	@param		key		The key of method.
	//!	@param		method	The method creation pointer.
	//! @return		True indicates success, false indicates failure.
	_ubool RegisterMethod( const KeyType& key, FactoryMethodBase< BaseType >* method );
	//!	Unregister the factory method.
	//!	@param		key		The key of method.
	//! @return		True indicates success, false indicates failure.
	_ubool UnregisterMethod( const KeyType& key );
	//! Check to see if a factory exists.
	//!	@param		key		The key of method.
	//! @return		True indicates it's existing.
	_ubool HasMethod( const KeyType& key ) const;

	//! Create the specified class.
	//!	@param		key		The key of method.
	//! @return		The pointer of class.
	BaseType* Create( const KeyType& key );
	//! Create the specified class copied from the passed in class.
	//!	@param		key		The key of method.
	//!	@param		rhs		The derived class object.
	//! @return		The pointer of class.
	template< typename DerivedType >
	BaseType* Create( const KeyType& key, const DerivedType& rhs );

	//!	Clear.
	//!	@param		none.
	//!	@return		none.
	_void Clear( );
};

//----------------------------------------------------------------------------
// Factory Implementation
//----------------------------------------------------------------------------

template< typename BaseType, typename KeyType, class KeyProcessorType >
Factory< BaseType, KeyType, KeyProcessorType >::Factory( )
{
}

template< typename BaseType, typename KeyType, class KeyProcessorType >
Factory< BaseType, KeyType, KeyProcessorType >::~Factory( )
{
	Clear( );
}

template< typename BaseType, typename KeyType, class KeyProcessorType >
_ubool Factory< BaseType, KeyType, KeyProcessorType >::RegisterMethod( const KeyType& key, FactoryMethodBase< BaseType >* method )
{
	if ( method == _null )
		return _false;

	KeyType processed_key = key; KeyProcessorType( )( processed_key );
	mFactoryMethods[ processed_key ] = method;

	return _true;
}

template< typename BaseType, typename KeyType, class KeyProcessorType >
_ubool Factory< BaseType, KeyType, KeyProcessorType >::UnregisterMethod( const KeyType& key )
{
	KeyType processed_key = key; KeyProcessorType( )( processed_key );

	// Remove it from the map
	mFactoryMethods.Remove( processed_key );

	return _true;
}

template< typename BaseType, typename KeyType, class KeyProcessorType >
_ubool Factory< BaseType, KeyType, KeyProcessorType >::HasMethod( const KeyType& key ) const
{
	KeyType processed_key = key; KeyProcessorType( )( processed_key );

	return mFactoryMethods.Search( processed_key ) != _null;
}

template< typename BaseType, typename KeyType, class KeyProcessorType >
BaseType* Factory< BaseType, KeyType, KeyProcessorType >::Create( const KeyType& key )
{
	KeyType processed_key = key; KeyProcessorType( )( processed_key );

	// Search for the method by key
	MethodType* methodbase = mFactoryMethods.Search( processed_key );
	if ( methodbase == _null )
		return _false;

	// Create object by method
	return (*methodbase->GetRawRef( ))( );
}

template< typename BaseType, typename KeyType, class KeyProcessorType >
template< typename DerivedType >
BaseType* Factory< BaseType, KeyType, KeyProcessorType >::Create( const KeyType& key, const DerivedType& rhs )
{
	KeyType processed_key = key; KeyProcessorType( )( processed_key );

	// Search for the method by key
	MethodType* methodbase = mFactoryMethods.Search( processed_key );
	if ( methodbase == _null )
		return _false;

	// Create object by method
	return (*methodbase->GetRawRef( ))( rhs );
}

template< typename BaseType, typename KeyType, class KeyProcessorType >
_void Factory< BaseType, KeyType, KeyProcessorType >::Clear( )
{
	mFactoryMethods.Clear( );
}

}