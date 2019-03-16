//! @file     GraphicVRDeviceMethods.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

// DEFINE_VRDEVICE_METHOD is used by the includer to modify the Drawer method definitions.
#ifndef DEFINE_VRDEVICE_METHOD
	#error "The DEFINE_VRDEVICE_METHOD marco must be defined"
	#define DEFINE_VRDEVICE_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) Type Name ParameterTypesAndNames
#endif

DEFINE_VRDEVICE_METHOD(
	_ubool,
	Initialize,
	(),
	(),
	return,
	_false;
	)

DEFINE_VRDEVICE_METHOD(
	_void,
	HandleEvent,
	(EventBase& event),
	(event),
	,
	;
	)

DEFINE_VRDEVICE_METHOD(
	_void,
	Present,
	(),
	(),
	,
	;
	)

DEFINE_VRDEVICE_METHOD(
	_float,
	GetEyeDistance,
	(_dword index) const,
	(index),
	return,
	0.0f;
	)
DEFINE_VRDEVICE_METHOD(
	VREyeRHI,
	GetEyeInfo,
	(_dword index) const,
	(index),
	return,
	VREyeRHI( );
	)