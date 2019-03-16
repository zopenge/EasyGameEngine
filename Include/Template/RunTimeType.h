//! @file     RunTimeType.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Helpful Macros
//----------------------------------------------------------------------------

// RTTI Declaration
#define EGE_RTTI_DECL( )																	\
public:																						\
	EGE_GET_ACCESSOR_OP( const _chara*, RTTIClassName, sRTTI.GetBaseRTTI( )->GetName( ) )	\
public:																						\
	static const RunTimeType sRTTI;

// RTTI Root Implementation
#define EGE_RTTI_ROOT_IMPL( classname )														\
	const RunTimeType classname::sRTTI( #classname, _null );

// RTTI Implementation

// DEBUG
#ifdef _DEBUG

//!	Test the RTTI-Inherit ( make sure the inherit-tree only works on the first base class )
template< typename T, class S >
void EGE_TestRTTIInherit( const _chara* classname, const _chara* baseclassname, const _chara* filename, _dword linenumber )
{
	_chara stringbuffer[1024];
	sprintf( stringbuffer, "%s is not the first base class for %s", baseclassname, classname );
#if defined(_PLATFORM_IOS_)
	(_void) ( ( ( (_dword) ( (T*) ( (S*) 1 ) ) ) == (_dword)( (T*) 1 ) ) || ( __assert( stringbuffer, filename, linenumber ), 0 ) );
#else
	(_void) ( ( ( (_dword) ( (T*) ( (S*) 1 ) ) ) == (_dword) ( (T*) 1 ) ) || ( __assert( stringbuffer, linenumber, filename ), 0 ) );
#endif
}

#define EGE_RTTI_IMPL( classname, baseclassname )																			\
	struct classname##classname { };																						\
	struct classname##baseclassname { };																					\
	static struct __tvar##classname##classname																				\
	{  																														\
		__tvar##classname##classname( )																						\
			{ EGE_TestRTTIInherit< classname, baseclassname >( #classname, #baseclassname, _FILENAME_A, _LINENUMBER ); }	\
	} __inst##class_name##classname;																						\
	const RunTimeType classname::sRTTI( #classname, &baseclassname::sRTTI );

// RELEASE
#else

#define EGE_RTTI_IMPL( classname, baseclassname )																			\
	const RunTimeType classname::sRTTI( #classname, &baseclassname::sRTTI );

#endif

//----------------------------------------------------------------------------
// RunTimeType
//----------------------------------------------------------------------------

class RunTimeType
{
private:
	//!	The class name
	const _chara*		mName;
	//!	The base RTTI pointer
	const RunTimeType * mBaseRTTI;

	//!	The dummy structure to identify the class inherit 
	template< _dword N >
	struct DummyStruct { char mDummy[N]; };

	//!	The identify class inherit function
	template< typename T >
	static DummyStruct< 2 > StaticIsEqualOrDerivedFrom( const T* ) { return DummyStruct< 2 >( ); }
	template< typename T >
	static DummyStruct< 1 > StaticIsEqualOrDerivedFrom( ... ) { return DummyStruct< 1 >( ); }

public:
	RunTimeType( const _chara* name, const RunTimeType* basertti ) 
		: mName( name ), mBaseRTTI( basertti ) { }

public:
	//!	Accessors.
	EGE_GET_ACCESSOR_CONST( const _chara*, Name )
	EGE_GET_ACCESSOR_CONST( const RunTimeType*, BaseRTTI )

public:
	//!	Check whether the specified class be equal or derived from this class or not
	//!	@param		basertti		The base run time type pointer.
	//!	@return		True indicates it's equal or derived from this class.
	_ubool IsEqualOrDerivedFrom( const RunTimeType* basertti ) const
	{
		const RunTimeType* rtti = this;
		while ( rtti != _null )
		{
			if ( rtti == basertti )
				return _true;

			rtti = basertti->GetBaseRTTI( );
		}

		return _false;
	}
};

//----------------------------------------------------------------------------
// Casting Functions Implementation
//----------------------------------------------------------------------------

template< typename T > 
_ubool EGE_IsType( const _void* pointer )
{
	if ( pointer == _null )
		return _false;

	return ( (T*) pointer )->sRTTI.IsEqualOrDerivedFrom( &T::sRTTI );
}

template< typename T > 
_ubool EGE_IsExactType( const _void* pointer )
{
	if ( pointer == _null )
		return _false;

	return ( (T*) pointer )->sRTTI == &T::sRTTI;
}

template< typename T > 
T* EGE_DynamicCast( _void* pointer )
{
	if ( EGE_IsType< T >( pointer ) )
		return (T*) pointer;

	return _null;
}

template< typename T > 
const T* EGE_DynamicCast( const _void* pointer )
{
	if ( EGE_IsType< T >( pointer ) )
		return (const T*) pointer;

	return _null;
}

}
