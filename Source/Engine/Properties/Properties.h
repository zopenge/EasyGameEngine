//! @file     Properties.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Properties
//----------------------------------------------------------------------------

class Properties : public TSerializable< TObject< IProperties > >
{
private:
	//!	The properties with key
	PropertyWithNameMap	mPropertiesWithName;

private:
	//!	Set the property value by name.
	template< typename KeyType, typename ValueType >
	const Variable& SetPropertyValue( const KeyType& name, ValueType value );
	//!	Get the property value by name.
	template< typename KeyType, typename ValueType >
	ValueType GetPropertyValue( const KeyType& name ) const;
	template< typename KeyType, typename ValueType >
	_ubool GetPropertyValue( const KeyType& name, ValueType& value ) const;

public:
	Properties( );
	virtual ~Properties( );

// IObject Interface
public:
	virtual IObject*	CloneTo( _ubool standalone ) const override;

// ISerializable Interface
public:
	virtual _ubool		Import( ISerializableNode* node ) override;
	virtual _ubool		Export( ISerializableNode* node ) const override;

// IProperties Interface
public:
	#define DEFINE_PROPERTIES_METHOD(Type,Name,ParameterTypesAndNames,Parameters,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Interface/Engine/Properties/IPropertiesMehods.h"
	#undef DEFINE_PROPERTIES_METHOD
};

// --------------------------------------------------------------------------------------------------------------
// Properties Implementation
// --------------------------------------------------------------------------------------------------------------

}