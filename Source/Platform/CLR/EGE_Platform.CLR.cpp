//! @file     EGE_Platform.CLR.cpp
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright 2009-2011 LiCode's Union.

#include "EGEPlatform.h"

using namespace System;

namespace EGEPlatformCLR 
{

//----------------------------------------------------------------------------
// CLRObjectBase Implementation
//----------------------------------------------------------------------------

template<typename Type>
public ref class CLRObjectBase
{
protected:
	Type* mUnmanagedObject;

	CLRObjectBase()
	{
		mUnmanagedObject = new Type();
	}
	CLRObjectBase(const Type& object)
	{
		mUnmanagedObject = new Type();
		*mUnmanagedObject = object;
	}
	~CLRObjectBase()
	{
		delete mUnmanagedObject;
	}
};

//----------------------------------------------------------------------------
// WStringPtr Implementation
//----------------------------------------------------------------------------

public ref class WStringPtr : public CLRObjectBase< EGE::WStringPtr >
{
protected:
	typedef CLRObjectBase< EGE::WStringPtr > TBaseClass;

public:
	WStringPtr()
	{
	}
	WStringPtr(int)
	{

	}
	WStringPtr(const WStringPtr% string)
	{
	}
	WStringPtr(const WStringPtr^ string)
	{
	}
	WStringPtr(const wchar_t* string)
	{
		mUnmanagedObject = new EGE::WStringPtr( string );
	}
	~WStringPtr()
	{

	}

	const _charw* Str( )
	{
		return mUnmanagedObject->Str( );
	}
};

//----------------------------------------------------------------------------
// WString Implementation
//----------------------------------------------------------------------------

public ref class WString : public CLRObjectBase< EGE::WString >
{
protected:
	typedef CLRObjectBase< EGE::WString > TBaseClass;

public:
	WString()
	{
	}
	WString(const WString% string)
	{
	}
	WString(const wchar_t* string)
	{
		mUnmanagedObject = new EGE::WString( string );
	}
	~WString()
	{

	}
};

//----------------------------------------------------------------------------
// Address Implementation
//----------------------------------------------------------------------------

public ref class Address : public CLRObjectBase< EGE::Address >
{
public:
	Address()
	{
	}
	~Address()
	{

	}

	System::String^ GetTypeString( )
	{
		return gcnew System::String( mUnmanagedObject->GetTypeString( ).Str( ) );
	}

	const _charw* CTOString( )
	{
		return mUnmanagedObject->ToString( ).Str( );
	}

	int Show( )
	{
		return 1;
	}
};

}
