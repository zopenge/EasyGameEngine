//! @file     filename.h
//! @author   author name
//! @version  xxx.xxx.xxx.xxx
//! @date     2011/??/??
//! Copyright 2010-2011 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// SampleClass
//----------------------------------------------------------------------------

//!	The brief of this class usage
class SampleClass
{
private:
	//!	Enumeration ( use '_' as prefix name and all uppercase )
	enum _TYPE
	{
		_TYPE_UNKNOWN,
		_TYPE_ANOTHER,
	};

	//!	Private members ( static member use 's' prefix name )
	static const _dword sStaticValue;
	
	// Member use 'm' prefix name
	_dword mMemberValue;

public:
	SampleClass( );
	~SampleClass( );

public:
	//!	Function description.
	//!	@param		parameter1		The parameter description.
	//!	@return		The return description.
	_bool DoSomething( _void* parameter1 );
};

}