//! @file     COMBSTR.h
//! @author   LiCode
//! @version  1.1.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// COMBSTR
//----------------------------------------------------------------------------

class COMBSTR
{
protected:
	//!	The BSTR string pointer
	BSTR	mBSTRPointer;

public:
	COMBSTR( WStringPtr string )
	{
		mBSTRPointer = ::SysAllocString( string.Str( ) );
	}

	~COMBSTR( )
	{
		if ( mBSTRPointer != _null )
			::SysFreeString( mBSTRPointer );
	}

public:
	//!	Get BSTR string pointer.
	inline operator BSTR( ) const
	{
		return mBSTRPointer;
	}
};

//----------------------------------------------------------------------------
// COMBSTR Implementation
//----------------------------------------------------------------------------

}