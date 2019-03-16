//! @file     Win32CLR.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

EGE_BEGIN_NAMESPACE_2( EGE, CLR )

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
	!CLRObjectBase()
	{
		delete mUnmanagedObject;
	}

public:
	//!	Get the unmanaged object.
	Type& GetUnmanagedObjectRef( )
	{
		return *mUnmanagedObject;
	}
	Type* GetUnmanagedObjectPtr( )
	{
		return mUnmanagedObject;
	}
};

EGE_END_NAMESPACE_2( )