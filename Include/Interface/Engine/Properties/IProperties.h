//! @file     IProperties.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//!	Property value, Property name
typedef Map< Variable, WStringObj > PropertyWithNameMap;

//----------------------------------------------------------------------------
// IProperties
//----------------------------------------------------------------------------

class IProperties : public ITSerializable< IObject >
{
public:
	// The methods are defined as virtual functions.
	#define DEFINE_PROPERTIES_METHOD(Type,Name,ParameterTypesAndNames,Parameters,NullImplementation) virtual Type Name ParameterTypesAndNames PURE;
	#include "IPropertiesMehods.h"
	#undef DEFINE_PROPERTIES_METHOD
};

//----------------------------------------------------------------------------
// ITProperties
//----------------------------------------------------------------------------

template< typename Type >
class ITProperties : public Type
{
public:
	// The methods are defined as virtual functions.
	#define DEFINE_PROPERTIES_METHOD(Type,Name,ParameterTypesAndNames,Parameters,NullImplementation) virtual Type Name ParameterTypesAndNames PURE;
	#include "IPropertiesMehods.h"
	#undef DEFINE_PROPERTIES_METHOD
};

}