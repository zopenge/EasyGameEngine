//! @file     TVMXSHI.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TVMXSHI
//----------------------------------------------------------------------------

template< class Type >
class TVMXSHI : public Type
{
public:
	//!	The VM flags
	enum _FLAG
	{
		_FLAG_CALLING_NATIVE_FUNC = 1 << 0, //!	True indicates it's calling native function
	};

protected:
	//!	The VM flags.
	FlagsObject	mFlags;
	//!	The VM registers
	VMRegisters	mRegisters;

	//!	The exception description
	WString		mExceptionDesc;

protected:
	TVMXSHI( );
	virtual ~TVMXSHI( );

public:
	//!	Get the flags.
	EGE_GETR_ACCESSOR( FlagsObject, Flags )
	//!	Get the registers.
	EGE_GETR_ACCESSOR( VMRegisters, Registers )
	//!	Access the exception description.
	EGE_GET_SET_ACCESSOR( WStringPtr, ExceptionDesc )
};

//----------------------------------------------------------------------------
// TVMXSHI Implementation
//----------------------------------------------------------------------------

template< class Type >
TVMXSHI< Type >::TVMXSHI( )
{
}

template< class Type >
TVMXSHI< Type >::~TVMXSHI( )
{
}

}