//! @file     GraphicCanvasMethods.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

// DEFINE_CANVAS_METHOD is used by the includer to modify the Drawer method definitions.
#ifndef DEFINE_CANVAS_METHOD
	#error "The DEFINE_CANVAS_METHOD marco must be defined"
	#define DEFINE_CANVAS_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) Type Name ParameterTypesAndNames
#endif

DEFINE_CANVAS_METHOD(
	_void,
	SetScene,
	(IGraphicScene* scene),
	(scene),
	,
	;
	)
DEFINE_CANVAS_METHOD(
	IGraphicScene*,
	GetScene,
	(),
	(),
	return,
	_null;
	)

DEFINE_CANVAS_METHOD(
	const PointU&,
	GetSize,
	() const,
	(),
	return,
	PointU::cZeroPoint;
	)

DEFINE_CANVAS_METHOD(
	IGraphicSurface*,
	GetRenderTarget,
	(),
	(),
	return,
	_null;
	)

DEFINE_CANVAS_METHOD(
	IGraphicSurface*,
	GetDepthStencil,
	(),
	(),
	return,
	_null;
	)

DEFINE_CANVAS_METHOD(
	_void*,
	LockRenderTarget,
	(_dword& stride),
	(stride),
	return,
	_null;
	)
DEFINE_CANVAS_METHOD(
	_void,
	UnlockRenderTarget,
	(),
	(),
	,
	;
	)

DEFINE_CANVAS_METHOD(
	_void,
	SetViewportAndProjectionTransform,
	(const PointU& client_size, IGraphicScene* scene),
	(client_size, scene),
	,
	;
	)