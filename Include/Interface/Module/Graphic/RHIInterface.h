//! @file     RHIInterface.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IDynamicRHI
//----------------------------------------------------------------------------

class IDynamicRHI : public IObject
{
public:
	// The RHI methods are defined as virtual functions.
	#define DEFINE_RHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) virtual Type Name ParameterTypesAndNames PURE;
	#include "Interface/Module/Graphic/RHIMethods.h"
	#undef DEFINE_RHIMETHOD
};

//----------------------------------------------------------------------------
// IResourceManagerRHI
//----------------------------------------------------------------------------

class IResourceManagerRHI : public IObject
{
public:
	//!	Initialize.
	virtual _ubool Initialize( ) PURE;
	//!	Finalize.
	virtual _void Finalize( ) PURE;

	//!	Reset.
	virtual _ubool Reset( ) PURE;
	//!	Unload.
	virtual _void Unload( ) PURE;

	//!	Create VAO.
	virtual _ubool CreateVAOResource( VertexArrayRHI* vao ) PURE;
	//!	Remove VAO.
	virtual _void RemoveVAOResource( VertexArrayRHI* vao ) PURE;

	//!	Create VBO/IBO.
	virtual _ubool CreateBuffer( VertexBufferRHI* vbo ) PURE;
	virtual _ubool CreateBuffer( IndexBufferRHI* ibo ) PURE;
	//!	Remove VBO/IBO.
	virtual _void RemoveBuffer( VertexBufferRHI* vbo ) PURE;
	virtual _void RemoveBuffer( IndexBufferRHI* ibo ) PURE;

	//!	Create shader.
	virtual _ubool CreateShader( VertexShaderRHI* vs ) PURE;
	virtual _ubool CreateShader( PixelShaderRHI* ps ) PURE;
	virtual _ubool CreateShader( BoundShaderRHI* shader ) PURE;
	//!	Remove shader.
	virtual _void RemoveShader( VertexShaderRHI* vs ) PURE;
	virtual _void RemoveShader( PixelShaderRHI* ps ) PURE;
	virtual _void RemoveShader( BoundShaderRHI* shader ) PURE;

	//!	Create textures.
	virtual _ubool CreateTexture( Texture2DRHI* texture, WStringPtr res_name, const _byte* pixels ) PURE;
	virtual _ubool CreateTexture( TextureCubeRHI* texture, WStringPtr res_name, const TextureCubeWithMipmapsRHI& mipmaps_info ) PURE;
	virtual _ubool CreateTexture( TextureCubeRHI* texture, WStringPtr res_name, const TextureCubeWithMipmapsRHI* mipmaps_info ) PURE;
	//!	Update textures.
	virtual _void UpdateTexture( Texture2DRHI* texture, const RectU& rect, const _byte* pixel ) PURE;
	//!	Remove textures.
	virtual _void RemoveTexture( Texture2DRHI* texture ) PURE;
	virtual _void RemoveTexture( TextureCubeRHI* texture ) PURE;
};

}