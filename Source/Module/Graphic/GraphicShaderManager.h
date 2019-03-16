//! @file     GraphicShaderManager.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicShaderManager
//----------------------------------------------------------------------------

class GraphicShaderManager : public TObservable< TObject< IGraphicShaderManager > >
{
private:
	typedef Array< IGraphicEffectRef > IGraphicEffectRefArray;

	//!	Use the enabled functions and diffuse map color operation as key.
	typedef Map< IGraphicEffectRef, _qword > EffectMapWithQword;
	//!	Use the CRC value as key.
	typedef Map< IGraphicEffectRef, _crcvalue > EffectMapWithCRCValue;

	//!	The cached shader info
	template< typename Type >
	struct CachedShaderInfo
	{
		AStringObj		mKey;
		RefPtr< Type >	mShader;

		operator AStringObj( ) const
			{ return mKey; }
	};
	typedef CachedShaderInfo< VertexShaderRHI > VertexCachedShaderInfo;
	typedef CachedShaderInfo< PixelShaderRHI > PixelCachedShaderInfo;
	typedef Array< VertexCachedShaderInfo > VertexShaderRHIArray;
	typedef Array< PixelCachedShaderInfo > PixelShaderRHIArray;

	//!	The internal render state info
	struct InternalRenderStateInfo
	{
		_GRAPHIC_INTERNAL_SAMPLER_STATE_TYPE	mSampler;
		_GRAPHIC_INTERNAL_RASTERIZER_STATE_TYPE	mRasterizer;
		_GRAPHIC_INTERNAL_DEPTH_STATE_TYPE		mDepth;
		_GRAPHIC_INTERNAL_STENCIL_STATE_TYPE	mStencil;
		_GRAPHIC_INTERNAL_BLEND_STATE_TYPE		mBlend;

		InternalRenderStateInfo( )
		{
			mSampler	= _GI_SAMPLER_NONE;
			mRasterizer	= _GI_RASTERIZER_NONE;
			mDepth		= _GI_DEPTH_NONE;
			mStencil	= _GI_STENCIL_NONE;
			mBlend		= _GI_BLEND_NONE;
		}
	};

	//!	The render states array
	typedef RawArray< RasterizerStateRHIRef, _GI_RASTERIZER_MAX_NUMBER > RasterizerStateRHIRefArray;
	typedef RawArray< SamplerStateRHIRef, _GI_SAMPLER_MAX_NUMBER > SamplerStateRHIRefArray;
	typedef RawArray< DepthStateRHIRef, _GI_DEPTH_MAX_NUMBER > DepthStateRHIRefArray;
	typedef RawArray< BlendStateRHIRef, _GI_BLEND_MAX_NUMBER > BlendStateRHIRefArray;
	typedef RawArray< StencilStateRHIRef, _GI_STENCIL_MAX_NUMBER > StencilStateRHIRefArray;

private:
	//!	The internal render states
	RasterizerStateRHIRefArray	mInternalRasterizertates;
	SamplerStateRHIRefArray		mInternalSamplerStates;
	DepthStateRHIRefArray		mInternalDepthStates;
	BlendStateRHIRefArray		mInternalBlendStates;
	StencilStateRHIRefArray		mInternalStencilStates;

	//!	The cached vertex shaders
	VertexShaderRHIArray		mVertexShaders;
	//!	The cached pixel shaders
	PixelShaderRHIArray			mPixelShaders;

	//!	The effects
	IGraphicEffectRefArray		mResidentInternalEffects;
	IGraphicEffectRefArray		mResidentExternalEffects;
	//!	The internal effects
	EffectMapWithQword			mInternalEffects;
	//!	The external effects
	EffectMapWithCRCValue		mExternalEffects;

	_ubool						mNoticeShaderCreated;

private:

	//!	Check external effects with key.
	_void CheckExternalEffects( _dword key, const GraphicEffectBase& initializer ) const;

	//!	Build the effect key code.
	_crcvalue BuildKeyCode( const GraphicEffectBase& initializer ) const;
	_qword BuildKeyCode( _GRAPHIC_INTERNAL_EFFECT_TYPE type, _dword enabled_functions, _GRAPHIC_COLOR_OPERATION diffuse_map_color_operation ) const;

	//!	Try to get the existing effect.
	IGraphicEffect* GetExistingEffect( EffectMapWithCRCValue& effects, AStringPtr vs_code, AStringPtr ps_code );

	//!	Load the internal render states.
	_ubool LoadInternalRenderStates( );
	//!	Update render states if it's necessary.
	_void UpdateRenderStatesIfNecessary( IGraphicEffect* effect, const InternalRenderStateInfo& info );

	//!	Build effect initializer from material info.
	_void BuildEffectInitializer( GraphicEffectInitializer& initializer, const GraphicMaterialInfo& info, _dword enabled_functions, _GRAPHIC_EMBEDDED_SYSTEM system_type ) const;
	_void BuildEffectInitializer( GraphicEffectInitializer& initializer, const GraphicMaterialInfo& info, _dword enabled_functions, _GRAPHIC_EMBEDDED_SYSTEM system_type, IGraphicLight** lights ) const;

	//!	Create effect.
	IGraphicEffectPassRef CreateGraphicEffect( _GRAPHIC_EMBEDDED_SYSTEM embedded_system, AStringPtr name, AStringPtr vs_code, AStringPtr ps_code, const GraphicEffectBase& base_info, const GraphicRenderStateInfo& render_state_info );

	//!	Build internal effect.
	IGraphicEffectPassRef BuildInternalEffect( _GRAPHIC_INTERNAL_EFFECT_TYPE type, _dword enabled_functions, _GRAPHIC_COLOR_OPERATION diffuse_map_color_operation );
	IGraphicEffect* GetExternalEffect( const GraphicEffectInitializer& initializer, const GraphicShaderInitializer& shader_initializer );
public:
	GraphicShaderManager( );
	virtual ~GraphicShaderManager( );

public:
	//!	Initialize.
	_ubool Initialize( );
	//!	Finalize.
	_void Finalize( );

	//!	Reset.
	_ubool ResetResources( );
	//!	Unload.
	_void UnloadResources( );

// IGraphicShaderManager Interface
public:
	virtual SamplerStateRHI*			GetInternalSamplerState( _GRAPHIC_INTERNAL_SAMPLER_STATE_TYPE type ) const override;
	virtual RasterizerStateRHI*			GetInternalRasterizerState( _GRAPHIC_INTERNAL_RASTERIZER_STATE_TYPE type ) const override;
	virtual DepthStateRHI*				GetInternalDepthState( _GRAPHIC_INTERNAL_DEPTH_STATE_TYPE type ) const override;
	virtual BlendStateRHI*				GetInternalBlendState( _GRAPHIC_INTERNAL_BLEND_STATE_TYPE type ) const override;
	virtual StencilStateRHI*			GetInternalStencilState( _GRAPHIC_INTERNAL_STENCIL_STATE_TYPE type ) const override;

	virtual AStringPtr					GetEffectShaderCode( _GRAPHIC_INTERNAL_EFFECT_TYPE type ) const override;

	virtual _ubool						OptimizeShaderCode( const GraphicEffectInitializer& initializer, AStringPtr technique_node, AString& name, AString& vs_code, AString& ps_code ) override;
	virtual _ubool						OptimizeShaderCode( const GraphicMaterialInfo& info, _GRAPHIC_EMBEDDED_SYSTEM system_type, AString& name, AString& vs_code, AString& ps_code ) const override;
	virtual _ubool						OptimizeShaderCode( const GraphicMaterialInfo& info, _GRAPHIC_EMBEDDED_SYSTEM system_type, AString& name, AString& vs_code, AString& ps_code, GraphicRenderStateInfo& render_state_info ) const override;

	virtual VertexShaderRHIRef			CreateVertexShader( AStringPtr code ) override;
	virtual PixelShaderRHIRef			CreatePixelShader( AStringPtr code ) override;

	virtual FlagsObject					GetEffectLightSlotFunction( const GraphicMaterialInfoBase& info, const IGraphicLight* light ) const override;

	virtual IGraphicEffectPassRef		CreateSharedEffect( IGraphicEffect* base_effect ) override;

	virtual IGraphicEffectPassRef		CreateAIOEffect( const GraphicMaterialInfo& info, IGraphicLight** lights, _dword enabled_functions, _GRAPHIC_EMBEDDED_SYSTEM system_type ) override;
	virtual IGraphicEffectPassRef		CreateAIOEffect( IGraphicEffect* base_effect, const GraphicEffectBase& base_info ) override;
	virtual IGraphicEffectPassRef		CreateAIOEffect( IGraphicEffect* base_effect, _dword enabled_functions ) override;
	virtual IGraphicEffectPassRef		CreateAIOEffect( IGraphicEffect* base_effect, const GraphicEffectBase& base_info, _dword enabled_functions ) override;
	virtual IGraphicEffectPassRef		CreateAIOEffectExclude( IGraphicEffect* base_effect, _dword disabled_functions, _dword* disable_lights_functions ) override;
	virtual IGraphicEffectPassRef		CreateAIOSkinEffect( const GraphicMaterialInfo& info, IGraphicLight** lights, _GRAPHIC_EMBEDDED_SYSTEM system_type ) override;
	virtual IGraphicEffectPassRef		CreateAIOTransparentEffect( const GraphicMaterialInfo& info, IGraphicLight** lights, _GRAPHIC_EMBEDDED_SYSTEM system_type ) override;

	virtual IGraphicEffectPassRef		CreateOverlayAIOEffect( _dword enabled_functions, _GRAPHIC_COLOR_OPERATION diffuse_map_color_operation ) override;
	virtual IGraphicEffectPassRef		CreateOverlayAIOEffect( _dword enabled_functions, _GRAPHIC_COLOR_OPERATION diffuse_map_color_operation, _GRAPHIC_INTERNAL_BLEND_STATE_TYPE blend_state ) override;
	virtual IGraphicEffectPassRef		CreateOverlayAIOEffect( _dword enabled_functions, _GRAPHIC_COLOR_OPERATION diffuse_map_color_operation, _GRAPHIC_INTERNAL_BLEND_STATE_TYPE blend_state, _GRAPHIC_INTERNAL_DEPTH_STATE_TYPE depth_state ) override;
	virtual IGraphicEffectPassRef		CreateOverlayAIOEffect( IGraphicEffect* base_effect, _dword enabled_functions ) override;

	virtual IGraphicEffect*				GetExternalEffect( const GraphicEffectInitializer& initializer, AStringPtr technique_node ) override;
	virtual IGraphicEffect*				GetExternalEffect( const GraphicEffectInitializer& initializer, ISerializableNode* vs_node, ISerializableNode* ps_node ) override;
	virtual IGraphicEffect*				GetExternalEffect( const GraphicEffectBase& base_effect_info, const GraphicEffectInitializer& initializer ) override;
	virtual _ubool						ImportEffectsWithSharedShader( const GraphicShaderSerializeInfo& info ) override;

	virtual IGraphicEffect*				GetInternalEffect( _GRAPHIC_INTERNAL_EFFECT_TYPE type ) override;
	virtual IGraphicEffect*				GetInternalEffect( _GRAPHIC_INTERNAL_EFFECT_TYPE type, _dword enabled_functions, _GRAPHIC_COLOR_OPERATION diffuse_map_color_operation ) override;
	virtual IGraphicEffectPassRef		CreateInternalEffect( _GRAPHIC_INTERNAL_EFFECT_TYPE type ) override;
	virtual IGraphicEffectPassRef		CreateInternalEffect( _GRAPHIC_INTERNAL_EFFECT_TYPE type, _dword enabled_functions, _GRAPHIC_COLOR_OPERATION diffuse_map_color_operation ) override;
};

//----------------------------------------------------------------------------
// GraphicShaderManager Implementation
//----------------------------------------------------------------------------

}