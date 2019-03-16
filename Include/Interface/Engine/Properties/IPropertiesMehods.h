//! @file     IPropertiesMehods.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

// DEFINE_PROPERTIES_METHOD is used by the includer to modify the method definitions.
#ifndef DEFINE_PROPERTIES_METHOD
	#error "The DEFINE_PROPERTIES_METHOD marco must be defined"
	#define DEFINE_PROPERTIES_METHOD(Type,Name,ParameterTypesAndNames,Parameters,NullImplementation) Type Name ParameterTypesAndNames
#endif

//----------------------------------------------------------------------------
// IProperties Interfaces
//----------------------------------------------------------------------------

//!	Clear all properties.
//!	@param		none.
//!	@return		none.
DEFINE_PROPERTIES_METHOD(
	_void,
	ClearProperties,
	(),
	(),
	;
	)

//!	Get the properties with key map.
//!	@param		none.
//!	@return		The properties map.
DEFINE_PROPERTIES_METHOD(
	const PropertyWithNameMap&,
	GetProperties,
	() const,
	(),
	static PropertyWithNameMap sPropertyWithNameMap; return sPropertyWithNameMap;
	)

//!	Set property.
//!	@param		name	The property name.
//!	@param		value	The property value.
//! @return		The property value.
DEFINE_PROPERTIES_METHOD(
	const Variable&,
	SetProperty,
	(WStringPtr name, _int value),
	(name, value),
	return Variable::cNull;
	)
//!	Set property.
//!	@param		name	The property name.
//!	@param		value	The property value.
//! @return		The property value.
DEFINE_PROPERTIES_METHOD(
	const Variable&,
	SetProperty,
	(WStringPtr name, _dword value),
	(name, value),
	return Variable::cNull;
	)
//!	Set property.
//!	@param		name	The property name.
//!	@param		value	The property value.
//! @return		The property value.
DEFINE_PROPERTIES_METHOD(
	const Variable&,
	SetProperty,
	(WStringPtr name, _float value),
	(name, value),
	return Variable::cNull;
	)
//!	Set property.
//!	@param		name	The property name.
//!	@param		value	The property value.
//! @return		The property value.
DEFINE_PROPERTIES_METHOD(
	const Variable&,
	SetProperty,
	(WStringPtr name, _double value),
	(name, value),
	return Variable::cNull;
	)
//!	Set property.
//!	@param		name	The property name.
//!	@param		value	The property value.
//! @return		The property value.
DEFINE_PROPERTIES_METHOD(
	const Variable&,
	SetProperty,
	(WStringPtr name, WStringPtr value),
	(name, value),
	return Variable::cNull;
	)
//!	Set property.
//!	@param		name	The property name.
//!	@param		value	The property value.
//! @return		The property value.
DEFINE_PROPERTIES_METHOD(
	const Variable&,
	SetProperty,
	(WStringPtr name, const WStringR& value),
	(name, value),
	return Variable::cNull;
	)
//!	Set property.
//!	@param		name	The property name.
//!	@param		value	The property value.
//! @return		The property value.
DEFINE_PROPERTIES_METHOD(
	const Variable&,
	SetProperty,
	(WStringPtr name, const Variable& value),
	(name, value),
	return Variable::cNull;
	)

//!	Get property as boolean value by key.
//!	@param		name	The property name.
//! @return		The property boolean value.
DEFINE_PROPERTIES_METHOD(
	_ubool,
	GetPropertyBool,
	(WStringPtr name) const,
	(name),
	return _false;
	)
//!	Get property as signed-integer value by key.
//!	@param		name	The property name.
//! @return		The property signed-integer value.
DEFINE_PROPERTIES_METHOD(
	_int,
	GetPropertyLong,
	(WStringPtr name) const,
	(name),
	return 0;
	)
//!	Get property as integer value by key.
//!	@param		name	The property name.
//! @return		The property integer value.
DEFINE_PROPERTIES_METHOD(
	_dword,
	GetPropertyDword,
	(WStringPtr name) const,
	(name),
	return 0;
	)
//!	Get property as float value by key.
//!	@param		name	The property name.
//! @return		The property float value.
DEFINE_PROPERTIES_METHOD(
	_float,
	GetPropertyFloat,
	(WStringPtr name) const,
	(name),
	return 0.0f;
	)
//!	Get property as double value by key.
//!	@param		name	The property name.
//! @return		The property double value.
DEFINE_PROPERTIES_METHOD(
	_double,
	GetPropertyDouble,
	(WStringPtr name) const,
	(name),
	return 0.0;
	)
//!	Get property as string by key.
//!	@param		name	The property name.
//! @return		The property string value.
DEFINE_PROPERTIES_METHOD(
	WStringPtr,
	GetPropertyString,
	(WStringPtr name) const,
	(name),
	return L"";
	)

//!	Get property as boolean value by key.
//!	@param		name	The property name.
//!	@return		True indicates successful, otherwise indicates failure.
DEFINE_PROPERTIES_METHOD(
	_ubool,
	GetPropertyBool,
	(WStringPtr name, _ubool& value) const,
	(name, value),
	return _false;
	)
//!	Get property as signed-integer value by key.
//!	@param		name	The property name.
//!	@return		True indicates successful, otherwise indicates failure.
DEFINE_PROPERTIES_METHOD(
	_ubool,
	GetPropertyLong,
	(WStringPtr name, _int& value) const,
	(name, value),
	return _false;
	)
//!	Get property as integer value by key.
//!	@param		name	The property name.
//!	@return		True indicates successful, otherwise indicates failure.
DEFINE_PROPERTIES_METHOD(
	_ubool,
	GetPropertyDword,
	(WStringPtr name, _dword& value) const,
	(name, value),
	return _false;
	)
//!	Get property as float value by key.
//!	@param		name	The property name.
//!	@return		True indicates successful, otherwise indicates failure.
DEFINE_PROPERTIES_METHOD(
	_ubool,
	GetPropertyFloat,
	(WStringPtr name, _float& value) const,
	(name, value),
	return _false;
	)
//!	Get property as double value by key.
//!	@param		name	The property name.
//!	@return		True indicates successful, otherwise indicates failure.
DEFINE_PROPERTIES_METHOD(
	_ubool,
	GetPropertyDouble,
	(WStringPtr name, _double& value) const,
	(name, value),
	return _false;
	)
//!	Get property as string by key.
//!	@param		name	The property name.
//!	@return		True indicates successful, otherwise indicates failure.
DEFINE_PROPERTIES_METHOD(
	_ubool,
	GetPropertyString,
	(WStringPtr name, WString& value) const,
	(name, value),
	return _false;
	)
DEFINE_PROPERTIES_METHOD(
	_ubool,
	GetPropertyString,
	(WStringPtr name, WStringObj& value) const,
	(name, value),
	return _false;
	)

//!	Remove property by name.
//!	@param		name	The property name.
//! @return		none.
DEFINE_PROPERTIES_METHOD(
	_void,
	RemoveProperty,
	(WStringPtr name),
	(name),
	;
	)
//!	Check whether has this property or not.
//!	@param		name	The property name.
//!	@param		value	The property value.
//! @return		True indicates this property is existing.
DEFINE_PROPERTIES_METHOD(
	_ubool,
	HasProperty,
	(WStringPtr name) const,
	(name),
	return _false;
	)

//!	Set property.
//!	@param		name	The property name.
//!	@param		value	The property value.
//! @return		The property value.
DEFINE_PROPERTIES_METHOD(
	const Variable&,
	SetProperty,
	(const WStringObj& name, _int value),
	(name, value),
	return Variable::cNull;
	)
//!	Set property.
//!	@param		name	The property name.
//!	@param		value	The property value.
//! @return		The property value.
DEFINE_PROPERTIES_METHOD(
	const Variable&,
	SetProperty,
	(const WStringObj& name, _dword value),
	(name, value),
	return Variable::cNull;
	)
//!	Set property.
//!	@param		name	The property name.
//!	@param		value	The property value.
//! @return		The property value.
DEFINE_PROPERTIES_METHOD(
	const Variable&,
	SetProperty,
	(const WStringObj& name, _float value),
	(name, value),
	return Variable::cNull;
	)
//!	Set property.
//!	@param		name	The property name.
//!	@param		value	The property value.
//! @return		The property value.
DEFINE_PROPERTIES_METHOD(
	const Variable&,
	SetProperty,
	(const WStringObj& name, WStringPtr value),
	(name, value),
	return Variable::cNull;
	)
//!	Set property.
//!	@param		name	The property name.
//!	@param		value	The property value.
//! @return		The property value.
DEFINE_PROPERTIES_METHOD(
	const Variable&,
	SetProperty,
	(const WStringObj& name, const WStringR& value),
	(name, value),
	return Variable::cNull;
	)
//!	Set property.
//!	@param		name	The property name.
//!	@param		value	The property value.
//! @return		The property value.
DEFINE_PROPERTIES_METHOD(
	const Variable&,
	SetProperty,
	(const WStringObj& name, const Variable& value),
	(name, value),
	return Variable::cNull;
	)

//!	Set property.
//!	@param		name	The property name.
//!	@param		value	The property value.
//! @return		The property value.
DEFINE_PROPERTIES_METHOD(
	const Variable&,
	SetProperty,
	(const WStringR& name, _int value),
	(name, value),
	return Variable::cNull;
	)
//!	Set property.
//!	@param		name	The property name.
//!	@param		value	The property value.
//! @return		The property value.
DEFINE_PROPERTIES_METHOD(
	const Variable&,
	SetProperty,
	(const WStringR& name, _dword value),
	(name, value),
	return Variable::cNull;
	)
//!	Set property.
//!	@param		name	The property name.
//!	@param		value	The property value.
//! @return		The property value.
DEFINE_PROPERTIES_METHOD(
	const Variable&,
	SetProperty,
	(const WStringR& name, _float value),
	(name, value),
	return Variable::cNull;
	)
//!	Set property.
//!	@param		name	The property name.
//!	@param		value	The property value.
//! @return		The property value.
DEFINE_PROPERTIES_METHOD(
	const Variable&,
	SetProperty,
	(const WStringR& name, WStringPtr value),
	(name, value),
	return Variable::cNull;
	)
//!	Set property.
//!	@param		name	The property name.
//!	@param		value	The property value.
//! @return		The property value.
DEFINE_PROPERTIES_METHOD(
	const Variable&,
	SetProperty,
	(const WStringR& name, const WStringR& value),
	(name, value),
	return Variable::cNull;
	)
//!	Set property.
//!	@param		name	The property name.
//!	@param		value	The property value.
//! @return		The property value.
DEFINE_PROPERTIES_METHOD(
	const Variable&,
	SetProperty,
	(const WStringR& name, const Variable& value),
	(name, value),
	return Variable::cNull;
	)
		
//!	Get property as boolean value by key.
//!	@param		name	The property name.
//! @return		The property boolean value.
DEFINE_PROPERTIES_METHOD(
	_ubool,
	GetPropertyBool,
	(const WStringObj& name) const,
	(name),
	return _false;
	)
//!	Get property as signed-integer value by key.
//!	@param		name	The property name.
//! @return		The property signed-integer value.
DEFINE_PROPERTIES_METHOD(
	_int,
	GetPropertyLong,
	(const WStringObj& name) const,
	(name),
	return 0;
	)
//!	Get property as integer value by key.
//!	@param		name	The property name.
//! @return		The property integer value.
DEFINE_PROPERTIES_METHOD(
	_dword,
	GetPropertyDword,
	(const WStringObj& name) const,
	(name),
	return 0;
	)
//!	Get property as float value by key.
//!	@param		name	The property name.
//! @return		The property float value.
DEFINE_PROPERTIES_METHOD(
	_float,
	GetPropertyFloat,
	(const WStringObj& name) const,
	(name),
	return 0.0f;
	)
//!	Get property as double value by key.
//!	@param		name	The property name.
//! @return		The property double value.
DEFINE_PROPERTIES_METHOD(
	_double,
	GetPropertyDouble,
	(const WStringObj& name) const,
	(name),
	return 0.0;
	)
//!	Get property as string by key.
//!	@param		name	The property name.
//! @return		The property string value.
DEFINE_PROPERTIES_METHOD(
	WStringPtr,
	GetPropertyString,
	(const WStringObj& name) const,
	(name),
	return L"";
	)

//!	Get property as boolean value by key.
//!	@param		name	The property name.
//!	@return		True indicates successful, otherwise indicates failure.
DEFINE_PROPERTIES_METHOD(
	_ubool,
	GetPropertyBool,
	(const WStringObj& name, _ubool& value) const,
	(name, value),
	return _false;
	)
//!	Get property as signed-integer value by key.
//!	@param		name	The property name.
//!	@return		True indicates successful, otherwise indicates failure.
DEFINE_PROPERTIES_METHOD(
	_ubool,
	GetPropertyLong,
	(const WStringObj& name, _int& value) const,
	(name, value),
	return _false;
	)
//!	Get property as integer value by key.
//!	@param		name	The property name.
//!	@return		True indicates successful, otherwise indicates failure.
DEFINE_PROPERTIES_METHOD(
	_ubool,
	GetPropertyDword,
	(const WStringObj& name, _dword& value) const,
	(name, value),
	return _false;
	)
//!	Get property as float value by key.
//!	@param		name	The property name.
//!	@return		True indicates successful, otherwise indicates failure.
DEFINE_PROPERTIES_METHOD(
	_ubool,
	GetPropertyFloat,
	(const WStringObj& name, _float& value) const,
	(name, value),
	return _false;
	)
//!	Get property as double value by key.
//!	@param		name	The property name.
//!	@return		True indicates successful, otherwise indicates failure.
DEFINE_PROPERTIES_METHOD(
	_ubool,
	GetPropertyDouble,
	(const WStringObj& name, _double& value) const,
	(name, value),
	return _false;
	)
//!	Get property as string by key.
//!	@param		name	The property name.
//!	@return		True indicates successful, otherwise indicates failure.
DEFINE_PROPERTIES_METHOD(
	_ubool,
	GetPropertyString,
	(const WStringObj& name, WString& value) const,
	(name, value),
	return _false;
	)
DEFINE_PROPERTIES_METHOD(
	_ubool,
	GetPropertyString,
	(const WStringObj& name, WStringObj& value) const,
	(name, value),
	return _false;
	)

//!	Remove property by name.
//!	@param		name	The property name.
//! @return		none.
DEFINE_PROPERTIES_METHOD(
	_void,
	RemoveProperty,
	(const WStringObj& name),
	(name),
	;
	)
//!	Check whether has this property or not.
//!	@param		name	The property name.
//!	@param		value	The property value.
//! @return		True indicates this property is existing.
DEFINE_PROPERTIES_METHOD(
	_ubool,
	HasProperty,
	(const WStringObj& name) const,
	(name),
	return _false;
	)

//!	Combine properties.
//!	@param		properties	The properties what will combine.
//!	@return		none.
DEFINE_PROPERTIES_METHOD(
	_void,
	Combine,
	(const IProperties* properties),
	(properties),
	;
	)
//!	Combine properties.
//!	@param		properties	The properties what will combine.
//!	@return		none.
DEFINE_PROPERTIES_METHOD(
	_void,
	Combine,
	(const PropertyWithNameMap& properties),
	(properties),
	;
	)