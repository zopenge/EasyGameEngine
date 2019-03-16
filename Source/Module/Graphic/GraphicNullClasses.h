//! @file     GraphicNullClasses.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NullResourceManagerRHI
//----------------------------------------------------------------------------

class NullResourceManagerRHI : public INTERFACE_OBJECT_IMPL( IResourceManagerRHI )
{
public:
	NullResourceManagerRHI( ) { }
	virtual ~NullResourceManagerRHI( ) { }

// IResourceManagerRHI Interface
public:
	virtual _ubool	Initialize( ) { return _true; }
	virtual _void	Finalize( ) { }

	virtual _ubool	Reset( ) { return _true; }
	virtual _void	Unload( ) { }

	virtual _ubool	CreateVAOResource( VertexArrayRHI* vao ) { return _true; }
	virtual _void	RemoveVAOResource( VertexArrayRHI* vao ) { }

	virtual _ubool	CreateFBOResource( SurfaceRHI* rendertarget, SurfaceRHI* depthstencil ) { return _true; }
	virtual _void	RemoveFBOResource( SurfaceRHI* rendertarget, SurfaceRHI* depthstencil ) { }

	virtual _ubool	CreateBuffer( VertexBufferRHI* vbo ) { return _true; }
	virtual _ubool	CreateBuffer( IndexBufferRHI* ibo ) { return _true; }
	virtual _void	RemoveBuffer( VertexBufferRHI* vbo ) { }
	virtual _void	RemoveBuffer( IndexBufferRHI* ibo ) { }

	virtual _ubool	CreateShader( VertexShaderRHI* vs ) { return _true; }
	virtual _ubool	CreateShader( PixelShaderRHI* ps ) { return _true; }
	virtual _ubool	CreateShader( BoundShaderRHI* shader ) { return _true; }
	virtual _void	RemoveShader( VertexShaderRHI* vs ) { }
	virtual _void	RemoveShader( PixelShaderRHI* ps ) { }
	virtual _void	RemoveShader( BoundShaderRHI* shader ) { }

	virtual _ubool	CreateTexture( Texture2DRHI* texture, WStringPtr res_name, const _byte* pixels ) { return _true; }
	virtual _ubool	CreateTexture( TextureCubeRHI* texture, WStringPtr res_name, const TextureCubeWithMipmapsRHI& mipmaps_info ) { return _true; }
	virtual _ubool	CreateTexture( TextureCubeRHI* texture, WStringPtr res_name, const TextureCubeWithMipmapsRHI* mipmaps_info ) { return _true; }
	virtual _void	UpdateTexture( Texture2DRHI* texture, const RectU& rect, const _byte* pixel ) { }
	virtual _void	RemoveTexture( Texture2DRHI* texture ) { }
	virtual _void	RemoveTexture( TextureCubeRHI* texture ) { }
};

//----------------------------------------------------------------------------
// NullGraphicFilter
//----------------------------------------------------------------------------

class NullGraphicFilter : public INTERFACE_OBJECT_IMPL( IGraphicFilter )
{
public:
	NullGraphicFilter( ) { }
	virtual ~NullGraphicFilter( ) { }

// IGraphicFilter Interface
public:
	virtual _void ProcessBlurEffect( IGraphicCanvas* canvas, const PointF& step_size, IGraphicSurface* surface ) { }
};

//----------------------------------------------------------------------------
// NullGraphicBackSurface
//----------------------------------------------------------------------------

class NullGraphicBackSurface : public INTERFACE_OBJECT_IMPL( IGraphicBackSurface )
{
public:
	NullGraphicBackSurface( ) { }
	virtual ~NullGraphicBackSurface( ) { }

// IGraphicBackSurface Interface
public:
	virtual _ubool			IsRendering( ) const { return _false; }

	virtual IGraphicCanvas* GetCanvas( ) { return _null; }

	virtual PointU			GetSize( ) const { return PointU::cZeroPoint; }

	virtual _void			SetPrevClientSize( const PointU& size ) { }

	virtual _void			SetClearBuffersInfo( const GraphicClearBuffersInfo& info ) { }

	virtual _void			SetRenderScale( _float scale ) { }
	virtual _float			GetRenderScale( ) const { return 1.0f; }

	virtual _void			BeginRender( IGraphicScene* scene ) { }
	virtual _void			EndRender( ) { }

	virtual _void			RenderToScene( IGraphicScene* scene ) { }
	virtual _void			RenderToScene( IGraphicScene* scene, IGraphicEffect* effect ) { }

	virtual _void			PresentRenderBuffers( ) { }
};

//----------------------------------------------------------------------------
// NullGraphicVRDevice
//----------------------------------------------------------------------------

class NullGraphicVRDevice : public INTERFACE_OBJECT_IMPL( IGraphicVRDevice )
{
public:
	NullGraphicVRDevice( ) { }
	virtual ~NullGraphicVRDevice( ) { }

// IGraphicDrawer Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_DRAWER_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames { Return NullImplementation }
	#include "Module/Graphic/Methods/GraphicDrawerMethods.h"
	#undef DEFINE_DRAWER_METHOD

// IGraphicScene Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_SCENE_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames { Return NullImplementation }
	#include "Module/Graphic/Methods/GraphicSceneMethods.h"
	#undef DEFINE_SCENE_METHOD
	
// IGraphicVRDevice Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_VRDEVICE_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames { Return NullImplementation }
	#include "Module/Graphic/Methods/GraphicVRDeviceMethods.h"
	#undef DEFINE_VRDEVICE_METHOD
};

//----------------------------------------------------------------------------
// NullGraphic
//----------------------------------------------------------------------------

class NullGraphic
{
	SINGLETON( NullGraphic )

private:
	NullResourceManagerRHI	mDeviceManagerRHI;
	NullGraphicFilter		mGraphicFilter;
	NullGraphicBackSurface	mGraphicBackSurface;
	NullGraphicVRDevice		mGraphicVRDevice;

public:
	EGE_GETR_ACCESSOR( NullResourceManagerRHI, DeviceManagerRHI )
	EGE_GETR_ACCESSOR( NullGraphicFilter, GraphicFilter )
	EGE_GETR_ACCESSOR( NullGraphicBackSurface, GraphicBackSurface )
	EGE_GETR_ACCESSOR( NullGraphicVRDevice, GraphicVRDevice )
};

}