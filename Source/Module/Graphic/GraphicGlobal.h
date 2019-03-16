//! @file     GraphicGlobal.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#pragma once

namespace EGE
{

//! The default vertex type
enum _DEFAULT_VERTEX_TYPE
{
	_DVT_OVERLAY_WITHOUT_TEX,
	_DVT_OVERLAY_WITH_TEX1,
	_DVT_OVERLAY_WITH_TEX2,
	_DVT_OVERLAY_TEXT,

	_DVT_PRIMITIVE_WITHOUT_TEX,
	_DVT_PRIMITIVE_WITH_TEX1,
	_DVT_PRIMITIVE_WITH_TEX2,
	_DVT_PRIMITIVE_TEXT,

	_DVT_MAX_NUMBER,

	_DVT_UNKNOWN = -1,
};

//! The renderable overlay without texture
struct RenderableOverlayWithoutTex
{
	Vector2	mPosition;
	_dword	mColor;

	_void Init( const Vector2& pos, _dword color )
	{
		mPosition	= pos;
		mColor		= color;
	}
};

//! The renderable overlay with 1 texture
struct RenderableOverlayWithTex1 : public RenderableOverlayWithoutTex
{
	Vector2	mUV1;

	_void Init( const Vector2& pos, _dword color, const Vector2& uv )
	{
		mUV1 = uv;

		RenderableOverlayWithoutTex::Init( pos, color );
	}
};

//! The renderable overlay with 2 texture
struct RenderableOverlayWithTex2 : public RenderableOverlayWithTex1
{
	Vector2	mUV2;
};

//! The renderable primitive without texture
struct RenderablePrimitiveWithoutTex
{
	Vector3	mPosition;
	_dword	mColor;

	_void Init( const Vector3& pos, _dword color )
	{
		mPosition	= pos;
		mColor		= color;
	}
};

//! The renderable primitive with 1 texture
struct RenderablePrimitiveWithTex1 : public RenderablePrimitiveWithoutTex
{
	Vector2	mUV1;

	_void Init( const Vector3& pos, _dword color, const Vector2& uv )
	{
		mUV1 = uv;

		RenderablePrimitiveWithoutTex::Init( pos, color );
	}
};

//! The renderable primitive with 2 texture
struct RenderablePrimitiveWithTex2 : public RenderablePrimitiveWithTex1
{
	Vector2	mUV2;
};

}