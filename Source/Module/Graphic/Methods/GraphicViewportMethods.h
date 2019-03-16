//! @file     GraphicViewportMethods.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

// DEFINE_VIEWPORT_METHOD is used by the includer to modify the Drawer method definitions.
#ifndef DEFINE_VIEWPORT_METHOD
	#error "The DEFINE_VIEWPORT_METHOD marco must be defined"
	#define DEFINE_VIEWPORT_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,ReturnRet) Type Name ParameterTypesAndNames
#endif

DEFINE_VIEWPORT_METHOD(
	_void,
	BeginBackSurfaceRendering,
	(_float scale),
	(scale),
	,
	;
	)
DEFINE_VIEWPORT_METHOD(
	_void,
	EndBackSurfaceRendering,
	(),
	(),
	,
	;
	)
DEFINE_VIEWPORT_METHOD(
	_void,
	ClearBackSurface,
	(),
	(),
	,
	;
	)
DEFINE_VIEWPORT_METHOD(
	_ubool,
	CreateBackSurface,
	(const PointU& size),
	(size),
	return,
	_false;
	)
DEFINE_VIEWPORT_METHOD(
	IGraphicBackSurface*,
	GetBackSurface,
	(),
	(),
	return,
	_null;
	)

DEFINE_VIEWPORT_METHOD(
	_void,
	Bind,
	(),
	(),
	,
	;
	)

#ifndef CUSTOM_PRESENT // We could implement it in other way, so use the macro to ignore it
DEFINE_VIEWPORT_METHOD(
	_void,
	Present,
	(),
	(),
	,
	;
	)
#endif
#undef CUSTOM_PRESENT

DEFINE_VIEWPORT_METHOD(
	_void,
	SetSceneProxy,
	(IGraphicScene* scene),
	(scene),
	,
	;
	)
DEFINE_VIEWPORT_METHOD(
	IGraphicScene*,
	GetSceneProxy,
	(),
	(),
	return,
	_null;
	)