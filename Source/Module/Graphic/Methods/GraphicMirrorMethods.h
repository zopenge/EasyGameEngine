//! @file     GraphicMirrorMethods.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

// DEFINE_MIRROR_METHOD is used by the includer to modify the Drawer method definitions.
#ifndef DEFINE_MIRROR_METHOD
	#error "The DEFINE_MIRROR_METHOD marco must be defined"
	#define DEFINE_MIRROR_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) Type Name ParameterTypesAndNames
#endif

DEFINE_MIRROR_METHOD(
	_GRAPHIC_MIRROR_TYPE,
	GetMirrorType,
	() const,
	(),
	return,
	_GRAPHIC_MIRROR_NONE;
	)

DEFINE_MIRROR_METHOD(
	const PointU&,
	GetMirrorSize,
	() const,
	(),
	return,
	PointU::cZeroPoint;
	)

DEFINE_MIRROR_METHOD(
	const Viewport&,
	GetMirrorViewport,
	() const,
	(),
	return,
	Viewport::cNull;
	)