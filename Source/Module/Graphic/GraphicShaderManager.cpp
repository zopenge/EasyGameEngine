//! @file     GraphicShaderManager.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

// Shader Files
#include "Shaders/OpenGL/Shaders.h"

//----------------------------------------------------------------------------
// GraphicShaderManager Helpful Functions Implementation
//----------------------------------------------------------------------------

// To check whether it's NULL HDR color.
static _ubool IsNullColor( const Vector4& c, _float f )
{
	if ( f == 0.0f )
		return _true;
	
	if ( c.w == 0.0f )
		return _true;
	
	if ( c.x == 0.0f && c.y == 0.0f && c.z == 0.0f )
		return _true;

	return _false;
}

//----------------------------------------------------------------------------
// GraphicShaderManager Implementation
//----------------------------------------------------------------------------

GraphicShaderManager::GraphicShaderManager( )
	: mNoticeShaderCreated( _true )
{
}

GraphicShaderManager::~GraphicShaderManager( )
{
	Finalize( );
}

_void GraphicShaderManager::CheckExternalEffects( _dword key, const GraphicEffectBase& initializer ) const
{
	for ( EffectMapWithCRCValue::Iterator it = mExternalEffects.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		_qword			it_key	= it.GetKey( );
		IGraphicEffect*	effect	= it.GetObject( );

		// If the base info is the same then key must be same
		if ( effect->GetBaseInfo( ) == initializer )
		{
			EGE_ASSERT( it_key == key );
		}
	}
}

_qword GraphicShaderManager::BuildKeyCode( _GRAPHIC_INTERNAL_EFFECT_TYPE type, _dword enabled_functions, _GRAPHIC_COLOR_OPERATION diffuse_map_color_operation ) const
{
	_qword key = (type) | (diffuse_map_color_operation << 8) | (((_qword)enabled_functions) << 32);
	return key;
}

IGraphicEffect* GraphicShaderManager::GetExistingEffect( EffectMapWithCRCValue& effects, AStringPtr vs_code, AStringPtr ps_code )
{
	for ( EffectMapWithCRCValue::Iterator it = effects.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		IGraphicEffect* effect = it.GetObject( );
		EGE_ASSERT( effect != _null );

		if ( effect->GetPSCode( ) != ps_code )
			continue;

		if ( effect->GetVSCode( ) != vs_code )
			continue;

		return effect;
	}

	return _null;
}

_ubool GraphicShaderManager::LoadInternalRenderStates( )
{
	// Create internal sampler states
	{
		mInternalSamplerStates[ _GI_SAMPLER_NEAREST ] = gDynamicRHI->CreateSamplerState( SamplerStateInitializerRHI( _SF_NEAREST ) );
		if ( mInternalSamplerStates[ _GI_SAMPLER_NEAREST ].IsNull( ) )
			return _false;

		mInternalSamplerStates[ _GI_SAMPLER_LINEAR ] = gDynamicRHI->CreateSamplerState( SamplerStateInitializerRHI( _SF_LINEAR ) );
		if ( mInternalSamplerStates[ _GI_SAMPLER_LINEAR ].IsNull( ) )
			return _false;

		mInternalSamplerStates[ _GI_SAMPLER_CLAMP ] = gDynamicRHI->CreateSamplerState( SamplerStateInitializerRHI( _SF_LINEAR, _SAM_CLAMP, _SAM_CLAMP, _SAM_CLAMP ) );
		if ( mInternalSamplerStates[ _GI_SAMPLER_CLAMP ].IsNull( ) )
			return _false;

		mInternalSamplerStates[_GI_SAMPLER_CLAMP_TO_EDGE] = gDynamicRHI->CreateSamplerState( SamplerStateInitializerRHI( _SF_LINEAR, _SAM_CLAMP_TO_EDGE, _SAM_CLAMP_TO_EDGE, _SAM_CLAMP_TO_EDGE ) );
		if ( mInternalSamplerStates[_GI_SAMPLER_CLAMP_TO_EDGE].IsNull( ) )
			return _false;
	}

	// Create internal rasterizer states
	{
		// Create enable color write state
		mInternalRasterizertates[ _GI_RASTERIZER_ENABLE_COLOR_WRITE ] = gDynamicRHI->CreateRasterizerState( RasterizerStateInitializerRHI( _true, _true, _true, _true, _RFM_SOLID, _RCM_NONE ) );
		if ( mInternalRasterizertates[ _GI_RASTERIZER_ENABLE_COLOR_WRITE ].IsNull( ) )
			return _false;

		// Create on color write state
		mInternalRasterizertates[ _GI_RASTERIZER_DISABLE_COLOR_WRITE ] = gDynamicRHI->CreateRasterizerState( RasterizerStateInitializerRHI( _false, _false, _false, _false, _RFM_SOLID, _RCM_NONE ) );
		if ( mInternalRasterizertates[ _GI_RASTERIZER_DISABLE_COLOR_WRITE ].IsNull( ) )
			return _false;

		// Create alpha only blend state
		mInternalRasterizertates[ _GI_RASTERIZER_ALPHA_ONLY ] = gDynamicRHI->CreateRasterizerState( RasterizerStateInitializerRHI( _false, _true, _false, _true, _RFM_SOLID, _RCM_NONE ) );
		if ( mInternalRasterizertates[ _GI_RASTERIZER_ALPHA_ONLY ].IsNull( ) )
			return _false;

		// create cw state
		mInternalRasterizertates[_GI_RASTERIZER_CULLMODE_CW] = gDynamicRHI->CreateRasterizerState( RasterizerStateInitializerRHI( _true, _true, _true, _true, _RFM_SOLID, _RCM_CW ) );
		if ( mInternalRasterizertates[_GI_RASTERIZER_CULLMODE_CW].IsNull( ) )
			return _false;

		// create ccw state
		mInternalRasterizertates[_GI_RASTERIZER_CULLMODE_CCW] = gDynamicRHI->CreateRasterizerState( RasterizerStateInitializerRHI( _true, _true, _true, _true, _RFM_SOLID, _RCM_CCW ) );
		if ( mInternalRasterizertates[_GI_RASTERIZER_CULLMODE_CCW].IsNull( ) )
			return _false;
	}

	// Create internal depth states
	{
		mInternalDepthStates[ _GI_DEPTH_ENABLE ] = GetDynamicRHI( )->CreateDepthState( DepthStateInitializerRHI( _true, _CF_LESS_EQUAL ) );
		if ( mInternalDepthStates[ _GI_DEPTH_ENABLE ].IsNull( ) )
			return _false;

		mInternalDepthStates[ _GI_DEPTH_READ_ONLY ] = GetDynamicRHI( )->CreateDepthState( DepthStateInitializerRHI( _false, _CF_LESS_EQUAL ) );
		if ( mInternalDepthStates[ _GI_DEPTH_READ_ONLY ].IsNull( ) )
			return _false;

		mInternalDepthStates[ _GI_DEPTH_ALWAYS_PASS ] = GetDynamicRHI( )->CreateDepthState( DepthStateInitializerRHI( _true, _CF_ALWAYS ) );
		if ( mInternalDepthStates[ _GI_DEPTH_ALWAYS_PASS ].IsNull( ) )
			return _false;

		mInternalDepthStates[ _GI_DEPTH_ALWAYS_PASS_READ_ONLY ] = GetDynamicRHI( )->CreateDepthState( DepthStateInitializerRHI( _false, _CF_ALWAYS ) );
		if ( mInternalDepthStates[ _GI_DEPTH_ALWAYS_PASS_READ_ONLY ].IsNull( ) )
			return _false;
	}

	// Create internal blend states
	{
		// Create default blend
		BlendStateInitializerRHI default_blend_state_init;
		default_blend_state_init.mEnableBlend				= _true;
		default_blend_state_init.mColorSourceBlendFactor	= _BF_SOURCE_ALPHA;
		default_blend_state_init.mColorDestBlendFactor		= _BF_INVERSE_SOURCE_ALPHA;
		default_blend_state_init.mAlphaSourceBlendFactor	= _BF_ONE;
		default_blend_state_init.mAlphaDestBlendFactor		= _BF_INVERSE_SOURCE_ALPHA;
		mInternalBlendStates[ _GI_BLEND_DEFAULT ] = gDynamicRHI->CreateBlendState( default_blend_state_init );
		if ( mInternalBlendStates[ _GI_BLEND_DEFAULT ].IsNull( ) )
			return _false;

		// Create alpha mask blend state
		BlendStateInitializerRHI mask_alpha_blend_state_init;
		mask_alpha_blend_state_init.mEnableBlend			= _true;
		mask_alpha_blend_state_init.mColorSourceBlendFactor	= _BF_ZERO;
		mask_alpha_blend_state_init.mColorDestBlendFactor	= _BF_ONE;
		mask_alpha_blend_state_init.mAlphaSourceBlendFactor	= _BF_DEST_ALPHA;
		mask_alpha_blend_state_init.mAlphaDestBlendFactor	= _BF_ZERO;
		mInternalBlendStates[ _GI_BLEND_ALPHA_MASK ] = gDynamicRHI->CreateBlendState( mask_alpha_blend_state_init );
		if ( mInternalBlendStates[ _GI_BLEND_ALPHA_MASK ].IsNull( ) )
			return _false;

		// Create additive alpha blend state
		BlendStateInitializerRHI additive_blend_state_init;
		additive_blend_state_init.mEnableBlend				= _true;
		additive_blend_state_init.mColorSourceBlendFactor	= _BF_SOURCE_ALPHA;
		additive_blend_state_init.mColorDestBlendFactor		= _BF_ONE;
		additive_blend_state_init.mAlphaSourceBlendFactor	= _BF_ONE;
		additive_blend_state_init.mAlphaDestBlendFactor		= _BF_INVERSE_SOURCE_ALPHA;
		mInternalBlendStates[ _GI_BLEND_ADDITIVE_COLOR ] = gDynamicRHI->CreateBlendState( additive_blend_state_init );
		if ( mInternalBlendStates[ _GI_BLEND_ADDITIVE_COLOR ].IsNull( ) )
			return _false;

		BlendStateInitializerRHI multi_blend_state_init;
		multi_blend_state_init.mEnableBlend				= _true;
		multi_blend_state_init.mColorSourceBlendFactor	= _BF_DEST_COLOR;
		multi_blend_state_init.mColorDestBlendFactor	= _BF_ZERO;
		multi_blend_state_init.mAlphaSourceBlendFactor	= _BF_ONE;
		multi_blend_state_init.mAlphaDestBlendFactor	= _BF_INVERSE_SOURCE_ALPHA;
		mInternalBlendStates[ _GI_BLEND_MULTI_COLOR ] = gDynamicRHI->CreateBlendState( multi_blend_state_init );
		if ( mInternalBlendStates[ _GI_BLEND_MULTI_COLOR ].IsNull( ) )
			return _false;

		BlendStateInitializerRHI disable_blend_state_init;
		disable_blend_state_init.mEnableBlend			= _true;
		disable_blend_state_init.mColorSourceBlendFactor= _BF_ONE;
		disable_blend_state_init.mColorDestBlendFactor	= _BF_ZERO;
		disable_blend_state_init.mAlphaSourceBlendFactor= _BF_ONE;
		disable_blend_state_init.mAlphaDestBlendFactor	= _BF_ZERO;
		mInternalBlendStates[ _GI_BLEND_DISABLE ] = gDynamicRHI->CreateBlendState( disable_blend_state_init );
		if ( mInternalBlendStates[ _GI_BLEND_DISABLE ].IsNull( ) )
			return _false;
	}

	// Create internal stencil state
	{
		// Create disable stencil state
		StencilStateInitializerRHI disable_stencil_state_init;
		mInternalStencilStates[ _GI_STENCIL_DISABLE ] = gDynamicRHI->CreateStencilState( disable_stencil_state_init );
		if ( mInternalStencilStates[ _GI_STENCIL_DISABLE ].IsNull( ) )
			return _false;
	}

	return _true;
}

_void GraphicShaderManager::UpdateRenderStatesIfNecessary( IGraphicEffect* effect, const InternalRenderStateInfo& info )
{
	EGE_ASSERT( effect != _null );

	if ( effect->GetSamplerState( 0 ) == _null )
		effect->SetSamplerState( 0, GetInternalSamplerState( info.mSampler ) );

	if ( effect->GetRasterizerState( ) == _null )
		effect->SetRasterizerState( GetInternalRasterizerState( info.mRasterizer ) );

	if ( effect->GetDepthState( ) == _null )
		effect->SetDepthState( GetInternalDepthState( info.mDepth ) );

	if ( effect->GetStencilState( ) == _null )
		effect->SetStencilState( GetInternalStencilState( info.mStencil ) );

	if ( effect->GetBlendState( ) == _null )
		effect->SetBlendState( GetInternalBlendState( info.mBlend ) );
}

_void GraphicShaderManager::BuildEffectInitializer( GraphicEffectInitializer& initializer, const GraphicMaterialInfo& info, _dword enabled_functions, _GRAPHIC_EMBEDDED_SYSTEM system_type ) const
{
	initializer.mEmbeddedSystem				= system_type;
	initializer.mDiffuseMapColorOperation	= info.mDiffuseMapColorOperation;
	initializer.mMirrorOperation			= info.mMirrorOperation;
	initializer.mEnabledFunctions			= info.mEnabledFunctions | enabled_functions;
	for ( _dword i = 0; i < _GLS_MAX_NUMBER; i ++ )
		initializer.mEnabledLightSlotFunctions[i] = info.mEnabledLightSlotFunctions[i];

	if ( info.mDiscardAlphaValue != 0.5f )
		initializer.mEnabledFunctions |= _GEF_USE_DISCARD_ALPHA_VALUE_;

	if ( info.mUVSpeed.x != 0.0f )
		initializer.mEnabledFunctions |= _GEF_UV_OFFSET_X_;
	if ( info.mUVSpeed.y != 0.0f )
		initializer.mEnabledFunctions |= _GEF_UV_OFFSET_Y_;
}

_void GraphicShaderManager::BuildEffectInitializer( GraphicEffectInitializer& initializer, const GraphicMaterialInfo& info, _dword enabled_functions, _GRAPHIC_EMBEDDED_SYSTEM system_type, IGraphicLight** lights ) const
{
	BuildEffectInitializer( initializer, info, enabled_functions, system_type );

	if ( lights != _null )
	{
		_ubool only_projtex_light = _true;
		for ( _dword i = 0; i < _GLS_MAX_NUMBER; ++ i )
		{
			IGraphicLight* light = lights[i];
			if ( light == _null )
				continue;

			if ( only_projtex_light && light->GetLightType( ) != _GLT_PROJTEX_SPOT_LIGHT )
				only_projtex_light = _false;

			initializer.mEnabledLightSlotFunctions[i] = GetEffectLightSlotFunction( info, light );
		}

		if ( only_projtex_light )
			initializer.mEnabledFunctions |= _GEF_ONLY_PROJTEX_SPOT_LIGHT_;
	}
}

IGraphicEffectPassRef GraphicShaderManager::CreateGraphicEffect( _GRAPHIC_EMBEDDED_SYSTEM embedded_system, AStringPtr name, AStringPtr vs_code, AStringPtr ps_code, const GraphicEffectBase& base_info, const GraphicRenderStateInfo& render_state_info )
{
	GraphicEffect* effect = new GraphicEffect( );
	if ( effect->Initialize( _true, embedded_system, name, vs_code, ps_code, base_info, render_state_info ) == _false )
		return _null;

	GraphicAsyncEffect* async_effect = new GraphicAsyncEffect( effect );
	effect->Release( );
	return async_effect;
}

IGraphicEffectPassRef GraphicShaderManager::BuildInternalEffect( _GRAPHIC_INTERNAL_EFFECT_TYPE type, _dword enabled_functions, _GRAPHIC_COLOR_OPERATION diffuse_map_color_operation )
{
	// The default render states
	static _dword cDefaultRenderStatesID[ _GIET_MAX_NUMBER * 5 ] =
	{
		//												Sampler					Rasterizer							Depth								Stencil					Blend
		// ================================ 2D effects ================================
		/*_GIET_OVERLAY_VERTEX_COLOR*/					_GI_SAMPLER_LINEAR,	_GI_RASTERIZER_ENABLE_COLOR_WRITE,	_GI_DEPTH_ALWAYS_PASS_READ_ONLY,	_GI_STENCIL_DISABLE,	_GI_BLEND_DEFAULT,
		/*_GIET_OVERLAY_AIO*/							_GI_SAMPLER_LINEAR,	_GI_RASTERIZER_ENABLE_COLOR_WRITE,	_GI_DEPTH_ALWAYS_PASS_READ_ONLY,	_GI_STENCIL_DISABLE,	_GI_BLEND_DEFAULT,
		/*_GIET_OVERLAY_DRAW_TEXT*/						_GI_SAMPLER_LINEAR,	_GI_RASTERIZER_ENABLE_COLOR_WRITE,	_GI_DEPTH_ALWAYS_PASS_READ_ONLY,	_GI_STENCIL_DISABLE,	_GI_BLEND_DEFAULT,
		/*_GIET_OVERLAY_POST_EFFECT_GAUSSIAN_BLUR*/		_GI_SAMPLER_LINEAR,	_GI_RASTERIZER_ENABLE_COLOR_WRITE,	_GI_DEPTH_ALWAYS_PASS_READ_ONLY,	_GI_STENCIL_DISABLE,	_GI_BLEND_DEFAULT,
		// ================================ 3D effects ================================
		/*_GIET_PRIMITIVE_VERTEX_COLOR*/				_GI_SAMPLER_LINEAR,	_GI_RASTERIZER_ENABLE_COLOR_WRITE,	_GI_DEPTH_ENABLE,					_GI_STENCIL_DISABLE,	_GI_BLEND_DEFAULT,
		/*_GIET_PRIMITIVE_TEX0*/						_GI_SAMPLER_LINEAR,	_GI_RASTERIZER_ENABLE_COLOR_WRITE,	_GI_DEPTH_ENABLE,					_GI_STENCIL_DISABLE,	_GI_BLEND_DEFAULT,
		/*_GIET_PRIMITIVE_TEX0_DISCARD_TRANSPARENT*/	_GI_SAMPLER_LINEAR,	_GI_RASTERIZER_ENABLE_COLOR_WRITE,	_GI_DEPTH_ENABLE,					_GI_STENCIL_DISABLE,	_GI_BLEND_DEFAULT,
		/*_GIET_PRIMITIVE_TEX0_STROKE*/					_GI_SAMPLER_LINEAR,	_GI_RASTERIZER_ENABLE_COLOR_WRITE,	_GI_DEPTH_ENABLE,					_GI_STENCIL_DISABLE,	_GI_BLEND_DEFAULT,
		/*_GIET_PRIMITIVE_ZBUFFER*/						_GI_SAMPLER_LINEAR,	_GI_RASTERIZER_DISABLE_COLOR_WRITE,	_GI_DEPTH_ENABLE,					_GI_STENCIL_DISABLE,	_GI_BLEND_DEFAULT,
		/*_GIET_PRIMITIVE_SKYBOX*/						_GI_SAMPLER_LINEAR,	_GI_RASTERIZER_ENABLE_COLOR_WRITE,	_GI_DEPTH_ENABLE,					_GI_STENCIL_DISABLE,	_GI_BLEND_DEFAULT,
		/*_GIET_PRIMITIVE_AIO*/							_GI_SAMPLER_LINEAR,	_GI_RASTERIZER_ENABLE_COLOR_WRITE,	_GI_DEPTH_ENABLE,					_GI_STENCIL_DISABLE,	_GI_BLEND_DEFAULT,
	};

	// Create new one from exist one
	GraphicEffectInitializer effect_initer;
	effect_initer.mDiffuseMapColorOperation = diffuse_map_color_operation;
	effect_initer.mEnabledFunctions			= enabled_functions;

	// Create shader code
	AString name, vs_code, ps_code;  GraphicRenderStateInfo render_state_info;
	if ( ShaderOptimizer::GetInstance( ).OptimizeShaderCode( effect_initer, GetEffectShaderCode( type ), name, vs_code, ps_code, render_state_info ) == _false )
		return _null;

	// Create effect in pass referenced pointer mode (we would let the resident effects container to manage it)
	IGraphicEffectPassRef new_effect = CreateGraphicEffect( effect_initer.mEmbeddedSystem, name, vs_code, ps_code, effect_initer, render_state_info );
	if ( new_effect.IsNull( ) )
	{
		WLOG_ERROR_1( L"Load effect with '0x%.8x' enabled functions failed in getting internal effects", effect_initer.mEnabledFunctions.GetFlags( ) );
		return _null;
	}

	// Save it
	mResidentInternalEffects.Append( new_effect );

	// Create the shared effect
	GraphicSharedEffect* shared_effect = new GraphicSharedEffect( new_effect.GetPtr( ), new_effect->GetBaseInfo( ) );

	// Get the default render stats ID
	InternalRenderStateInfo default_render_state_info;
	default_render_state_info.mSampler		= (_GRAPHIC_INTERNAL_SAMPLER_STATE_TYPE)cDefaultRenderStatesID[ type * 5 + 0 ];
	default_render_state_info.mRasterizer	= (_GRAPHIC_INTERNAL_RASTERIZER_STATE_TYPE)cDefaultRenderStatesID[ type * 5 + 1 ];
	default_render_state_info.mDepth		= (_GRAPHIC_INTERNAL_DEPTH_STATE_TYPE)cDefaultRenderStatesID[ type * 5 + 2 ];
	default_render_state_info.mStencil		= (_GRAPHIC_INTERNAL_STENCIL_STATE_TYPE)cDefaultRenderStatesID[ type * 5 + 3 ];
	default_render_state_info.mBlend		= (_GRAPHIC_INTERNAL_BLEND_STATE_TYPE)cDefaultRenderStatesID[ type * 5 + 4 ];

	// Set the default render stats
	UpdateRenderStatesIfNecessary( shared_effect, default_render_state_info );

	return shared_effect;
}

_ubool GraphicShaderManager::Initialize( )
{
	WLOG_TRACE( L"Initialize graphic shader manager ..." );

	// Load the internal render states
	if ( LoadInternalRenderStates( ) == _false )
	{
		WLOG_ERROR( L"Load internal render states failed" );
		return _false;
	}

	WLOG_TRACE( L"Initialize graphic shader manager OK" );

	return _true;
}

_void GraphicShaderManager::Finalize( )
{
	for ( _dword i = 0; i < mInternalRasterizertates.Number( ); i ++ )
		mInternalRasterizertates[i].Clear( );

	for ( _dword i = 0; i < mInternalSamplerStates.Number( ); i ++ )
		mInternalSamplerStates[i].Clear( );

	for ( _dword i = 0; i < mInternalDepthStates.Number( ); i ++ )
		mInternalDepthStates[i].Clear( );

	for ( _dword i = 0; i < mInternalBlendStates.Number( ); i ++ )
		mInternalBlendStates[i].Clear( );

	for ( _dword i = 0; i < mInternalStencilStates.Number( ); i ++ )
		mInternalStencilStates[i].Clear( );

	mInternalEffects.Clear( );
	mExternalEffects.Clear( );

	mResidentInternalEffects.Clear( _true );
	mResidentExternalEffects.Clear( _true );

	mVertexShaders.Clear( _true );
	mPixelShaders.Clear( _true );
}

_ubool GraphicShaderManager::ResetResources( )
{
	// Reset resident internal effects
	for ( _dword i = 0; i < mResidentInternalEffects.Number( ); i ++ )
		mResidentInternalEffects[i]->ResetUBOs( );

	// Reset external resident effects
	for ( _dword i = 0; i < mResidentExternalEffects.Number( ); i ++ )
		mResidentExternalEffects[i]->ResetUBOs( );

	return _true;
}

_void GraphicShaderManager::UnloadResources( )
{
}

RasterizerStateRHI* GraphicShaderManager::GetInternalRasterizerState( _GRAPHIC_INTERNAL_RASTERIZER_STATE_TYPE type ) const
{
	if ( (_dword)type >= mInternalRasterizertates.Number( ) )
		return _null;

	return mInternalRasterizertates[type].GetPtr( );
}

SamplerStateRHI* GraphicShaderManager::GetInternalSamplerState( _GRAPHIC_INTERNAL_SAMPLER_STATE_TYPE type ) const
{
	if ( (_dword)type >= mInternalSamplerStates.Number( ) )
		return _null;

	return mInternalSamplerStates[type].GetPtr( );
}

DepthStateRHI* GraphicShaderManager::GetInternalDepthState( _GRAPHIC_INTERNAL_DEPTH_STATE_TYPE type ) const
{
	if ( (_dword)type >= mInternalDepthStates.Number( ) )
		return _null;

	return mInternalDepthStates[type].GetPtr( );
}

BlendStateRHI* GraphicShaderManager::GetInternalBlendState( _GRAPHIC_INTERNAL_BLEND_STATE_TYPE type ) const
{
	if ( (_dword)type >= mInternalBlendStates.Number( ) )
		return _null;

	return mInternalBlendStates[type].GetPtr( );
}

StencilStateRHI* GraphicShaderManager::GetInternalStencilState( _GRAPHIC_INTERNAL_STENCIL_STATE_TYPE type ) const
{
	if ( (_dword)type >= mInternalStencilStates.Number( ) )
		return _null;

	return mInternalStencilStates[type].GetPtr( );
}

AStringPtr GraphicShaderManager::GetEffectShaderCode( _GRAPHIC_INTERNAL_EFFECT_TYPE type ) const
{
	EGE_ASSERT( type < _GIET_MAX_NUMBER );

	// The shader code text table
	#define GIET_CODE( x ) c##x##_effect
	static AStringPtr cShaderCodeTextTable[_GIET_MAX_NUMBER] = { GIET_TABLE( GIET_CODE ) };
	return cShaderCodeTextTable[ type ];
}

_ubool GraphicShaderManager::OptimizeShaderCode( const GraphicEffectInitializer& initializer, AStringPtr technique_node, AString& name, AString& vs_code, AString& ps_code )
{
	// Create shader code
	if ( ShaderOptimizer::GetInstance( ).OptimizeShaderCode( initializer, technique_node, name, vs_code, ps_code ) == _false )
		return _false;

	return _true;
}

_ubool GraphicShaderManager::OptimizeShaderCode( const GraphicMaterialInfo& info, _GRAPHIC_EMBEDDED_SYSTEM system_type, AString& name, AString& vs_code, AString& ps_code ) const
{
	// Build effect initializer
	GraphicEffectInitializer initializer;
	BuildEffectInitializer( initializer, info, 0, system_type );

	// Create shader code
	if ( ShaderOptimizer::GetInstance( ).OptimizeShaderCode( initializer, GetEffectShaderCode( _GIET_PRIMITIVE_AIO ), name, vs_code, ps_code ) == _false )
		return _false;

	return _true;
}

_ubool GraphicShaderManager::OptimizeShaderCode( const GraphicMaterialInfo& info, _GRAPHIC_EMBEDDED_SYSTEM system_type, AString& name, AString& vs_code, AString& ps_code, GraphicRenderStateInfo& render_state_info ) const
{
	// Build effect initializer
	GraphicEffectInitializer initializer;
	BuildEffectInitializer( initializer, info, 0, system_type );

	// Create shader code
	if ( ShaderOptimizer::GetInstance( ).OptimizeShaderCode( initializer, GetEffectShaderCode( _GIET_PRIMITIVE_AIO ), name, vs_code, ps_code, render_state_info ) == _false )
		return _false;

	return _true;
}

VertexShaderRHIRef GraphicShaderManager::CreateVertexShader( AStringPtr code )
{
	AStringObj key = code;

	VertexShaderRHIArray::Iterator it = mVertexShaders.SearchAscending( key );
	if ( it.IsValid( ) )
		return it.GetObject( ).mShader;

	VertexCachedShaderInfo shader_info;
	shader_info.mKey	= key;
	shader_info.mShader	= gDynamicRHI->CreateVertexShader( code );
	mVertexShaders.InsertAscending< AStringObj >( shader_info );

	return shader_info.mShader;
}

PixelShaderRHIRef GraphicShaderManager::CreatePixelShader( AStringPtr code )
{
	AStringObj key = code;

	PixelShaderRHIArray::Iterator it = mPixelShaders.SearchAscending( key );
	if ( it.IsValid( ) )
		return it.GetObject( ).mShader;

	PixelCachedShaderInfo shader_info;
	shader_info.mKey	= key;
	shader_info.mShader	= gDynamicRHI->CreatePixelShader( code );
	mPixelShaders.InsertAscending< AStringObj >( shader_info );

	return shader_info.mShader;
}

FlagsObject	GraphicShaderManager::GetEffectLightSlotFunction( const GraphicMaterialInfoBase& info, const IGraphicLight* light ) const
{
	if ( light == _null )
		return FlagsObject::cNull;

	// The functions of light
	FlagsObject enabled_functions;

	// Enable light
	enabled_functions.CombineFlags( _GELSF_LIGHT_ );

	// Check whether it's unimportant light
	_ubool unimportant = info.mLightImportantType == _GIT_UNIMPORTANT;

	// Get the light type
	_GRAPHIC_LIGHT_TYPE light_type = light->GetLightType( );

	// Check whether enable attenuation
	if ( light->IsEnableAttenuation( ) )
	{
		if ( light_type == _GLT_POINT_LIGHT || light_type == _GLT_SPOT_LIGHT )
			enabled_functions.CombineFlags( _GELSF_GLA_ );
	}

	// It's directional light
	if ( light_type == _GLT_DIRECTIONAL_LIGHT )
		enabled_functions.CombineFlags( _GELSF_GL_DIRECTIONAL_ );
	
	// It's projective texture spot light
	if ( light_type == _GLT_PROJTEX_SPOT_LIGHT )
	{
		enabled_functions.CombineFlags( _GELSF_GL_PROJTEX_SPOT_ );
		IGraphicProjTextureSpotLight* projtex_light = (IGraphicProjTextureSpotLight*)light;
		switch ( projtex_light->GetColorOperation( ) )
		{
			case _GCO_ADD_:
				enabled_functions.CombineFlags( _GELSF_GL_PROJTEX_OPERATION_ADD_ );
				break;
			case _GCO_MUL_:
				enabled_functions.CombineFlags( _GELSF_GL_PROJTEX_OPERATION_MUL_ );
				break;
			case _GCO_ORIGIN_:
				enabled_functions.CombineFlags( _GELSF_GL_PROJTEX_OPERATION_ORIGIN_ );
				break;

			default:
				break;
		}
	}
	// Other light
	else
	{
		if ( info.mLightingModelType == _GLMT_NONE )
			return FlagsObject::cNull;

		const Vector4& hdr_color = light->GetHDRColor( );

		if ( !IsNullColor( hdr_color, 1.0f ) )
		{
			switch ( info.mLightingModelType )
			{
			case _GLMT_PHYSICALLY_BASED:
			{
				enabled_functions.CombineFlags( _GELSF_PHYSICALLY_BASED_LIGHTING );
			}
			break;
			case _GLMT_BRDF_RAMPTEX:
			{
				enabled_functions.CombineFlags( _GELSF_BRDF_RAMPTEX_LIGHTING );
			}
			break;
			}
		}
	}

	// If it's unimportant light then we use the light base on the vertex, not pixels
	if ( unimportant )
		enabled_functions.CombineFlags( _GELSF_VERTEX_LIGHT_ );

	// Check whether use the color of light
	const Vector4& light_color = light->GetHDRColor( );
	if ( light_color.x != 1.0f || light_color.y != 1.0f || light_color.z != 1.0f )
		enabled_functions.CombineFlags( _GELSF_USE_LIGHT_COLOR_ );

	return enabled_functions;
}

IGraphicEffectPassRef GraphicShaderManager::CreateSharedEffect( IGraphicEffect* base_effect )
{
	if ( base_effect == _null )
		return _null;

	return new GraphicSharedEffect( base_effect, base_effect->GetBaseInfo( ) );
}

IGraphicEffectPassRef GraphicShaderManager::CreateAIOEffect( const GraphicMaterialInfo& info, IGraphicLight** lights, _dword enabled_functions, _GRAPHIC_EMBEDDED_SYSTEM system_type )
{
	// Build effect initializer
	GraphicEffectInitializer initializer;
	BuildEffectInitializer( initializer, info, enabled_functions, system_type, lights );

	// Load effect
	IGraphicEffect* effect = GetExternalEffect( initializer, GetEffectShaderCode( _GIET_PRIMITIVE_AIO ) );
	if ( effect == _null )
		return _null;

	return new GraphicSharedEffect( effect, info );
}

IGraphicEffectPassRef GraphicShaderManager::CreateAIOEffect( IGraphicEffect* base_effect, const GraphicEffectBase& base_info )
{
	return CreateAIOEffect( base_effect, base_info, 0 );
}

IGraphicEffectPassRef GraphicShaderManager::CreateAIOEffect( IGraphicEffect* base_effect, _dword enabled_functions )
{
	return CreateAIOEffect( base_effect, base_effect->GetBaseInfo( ), enabled_functions );
}

IGraphicEffectPassRef GraphicShaderManager::CreateAIOEffect( IGraphicEffect* base_effect, const GraphicEffectBase& base_info, _dword enabled_functions )
{
	// Load external effect
	IGraphicEffect* effect = GetExternalEffect( GraphicEffectInitializer( base_info, enabled_functions ), GetEffectShaderCode( _GIET_PRIMITIVE_AIO ) );
	if ( effect == _null )
		return _null;

	// Create shared effect
	IGraphicEffectPassRef shared_effect = new GraphicSharedEffect( effect, base_info );
	if ( shared_effect.IsNull( ) )
		return _null;

	// Combine with base effect's render states
	if ( base_effect != _null )
		shared_effect->CombineRenderStates( base_effect );

	return shared_effect;
}

IGraphicEffectPassRef GraphicShaderManager::CreateAIOEffectExclude( IGraphicEffect* base_effect, _dword disabled_functions, _dword* disable_lights_functions )
{
	if ( base_effect == _null )
		return _null;

	// Build effect initializer
	GraphicEffectBase base_info = base_effect->GetBaseInfo( );
	base_info.mEnabledFunctions.ClearFlags( disabled_functions );

	if ( disable_lights_functions != _null )
	{
		for ( _dword i = 0; i < _GLS_MAX_NUMBER; ++ i )
			base_info.mEnabledLightSlotFunctions[i].ClearFlags( disable_lights_functions[i] );
	}

	return CreateAIOEffect( base_effect, base_info );
}

IGraphicEffectPassRef GraphicShaderManager::CreateAIOSkinEffect( const GraphicMaterialInfo& info, IGraphicLight** lights, _GRAPHIC_EMBEDDED_SYSTEM system_type )
{
	return CreateAIOEffect( info, lights, _GEF_WITH_BONE_ANIMATION_, system_type );
}

IGraphicEffectPassRef GraphicShaderManager::CreateAIOTransparentEffect( const GraphicMaterialInfo& info, IGraphicLight** lights, _GRAPHIC_EMBEDDED_SYSTEM system_type )
{
	GraphicMaterialInfo transparent_info = info;
	transparent_info.mEnabledFunctions.ClearFlags( _GEF_DISCARD_TRANSPARENT_ );
	transparent_info.mDepthStateType = _GI_DEPTH_READ_ONLY;

	return CreateAIOEffect( transparent_info, lights, _GEF_DISCARD_OPACITY_, system_type );
}

IGraphicEffectPassRef GraphicShaderManager::CreateOverlayAIOEffect( _dword enabled_functions, _GRAPHIC_COLOR_OPERATION diffuse_map_color_operation )
{
	IGraphicEffect* effect = GetInternalEffect( _GIET_OVERLAY_AIO, enabled_functions, diffuse_map_color_operation );
	if ( effect == _null )
		return _null;

	return new GraphicSharedEffect( effect, effect->GetBaseInfo( ) );
}

IGraphicEffectPassRef GraphicShaderManager::CreateOverlayAIOEffect( _dword enabled_functions, _GRAPHIC_COLOR_OPERATION diffuse_map_color_operation, _GRAPHIC_INTERNAL_BLEND_STATE_TYPE blend_state )
{
	IGraphicEffectPassRef effect = CreateOverlayAIOEffect( enabled_functions, diffuse_map_color_operation );
	if ( effect.IsNull( ) )
		return _null;

	effect->SetBlendState( GetGraphicShaderManager( )->GetInternalBlendState( blend_state ) );

	return effect;
}

IGraphicEffectPassRef GraphicShaderManager::CreateOverlayAIOEffect( _dword enabled_functions, _GRAPHIC_COLOR_OPERATION diffuse_map_color_operation, _GRAPHIC_INTERNAL_BLEND_STATE_TYPE blend_state, _GRAPHIC_INTERNAL_DEPTH_STATE_TYPE depth_state )
{
	IGraphicEffectPassRef effect = CreateOverlayAIOEffect( enabled_functions, diffuse_map_color_operation );
	if ( effect.IsNull( ) )
		return _null;

	effect->SetBlendState( GetGraphicShaderManager( )->GetInternalBlendState( blend_state ) );
	effect->SetDepthState( GetGraphicShaderManager( )->GetInternalDepthState( depth_state ) );

	return effect;
}

IGraphicEffectPassRef GraphicShaderManager::CreateOverlayAIOEffect( IGraphicEffect* base_effect, _dword enabled_functions )
{
	if ( base_effect == _null )
		return _null;

	// Get the final enable functions
	_dword final_enable_functions = base_effect->GetEnabledFunctions( ) | enabled_functions;

	// Get the color operation
	_GRAPHIC_COLOR_OPERATION color_operation = base_effect->GetBaseInfo( ).mDiffuseMapColorOperation;

	// Create effect
	IGraphicEffectPassRef effect = CreateOverlayAIOEffect( final_enable_functions, color_operation );
	if ( effect.IsNull( ) )
		return _null;

	// Combine render states
	effect->SetRenderStates( base_effect->GetRenderStates( ) );

	return effect;
}

IGraphicEffect* GraphicShaderManager::GetExternalEffect( const GraphicEffectInitializer& initializer, const GraphicShaderInitializer& shader_initializer )
{
	// Build the key code
	_dword key = initializer.ToKey( );

	// Search for the existing effect
	const IGraphicEffectRef* effect = mExternalEffects.Search( key );
	if ( effect != _null )
		return effect->GetPtr( );

	// Optimize shader code
	AString name, vs_code, ps_code; GraphicRenderStateInfo render_state_info;
	if ( ShaderOptimizer::GetInstance( ).OptimizeShaderCode( initializer, shader_initializer, name, vs_code, ps_code, render_state_info ) == _false )
		return _null;

	// The shared effect
	IGraphicEffect* shared_effect = _null;

	// Prevent the same shader code even though the key is different
	IGraphicEffect* exist_effect = GetExistingEffect( mExternalEffects, vs_code, ps_code );
	if ( exist_effect != _null )
	{
		// It's the same shader code effect
		shared_effect = new GraphicSharedEffect( exist_effect, initializer );
		shared_effect->SetRenderStates( render_state_info );
	}
	else
	{
		// Create effect
		IGraphicEffectPassRef new_effect = CreateGraphicEffect( initializer.mEmbeddedSystem, name, vs_code, ps_code, initializer, render_state_info );
		if ( new_effect.IsNull( ) )
		{
			WLOG_ERROR_1( L"Load effect with '0x%.8x' enabled functions failed in getting external effects", initializer.mEnabledFunctions.GetFlags( ) );
			return _null;
		}

		// Save it
		mResidentExternalEffects.Append( new_effect );

		// Save effect
		shared_effect = new GraphicSharedEffect( new_effect.GetPtr( ), initializer );
	}

	// Check external effects
#ifdef _DEBUG
	CheckExternalEffects( key, initializer );
#endif

	// Update external effects
	mExternalEffects[key] = shared_effect;
	shared_effect->Release( );

	// Get the default render stats ID
	InternalRenderStateInfo default_render_state_info;
	default_render_state_info.mSampler = _GI_SAMPLER_LINEAR;
	default_render_state_info.mRasterizer = _GI_RASTERIZER_ENABLE_COLOR_WRITE;
	default_render_state_info.mDepth = _GI_DEPTH_ENABLE;
	default_render_state_info.mStencil = _GI_STENCIL_DISABLE;
	default_render_state_info.mBlend = _GI_BLEND_DEFAULT;

	// Set the default render stats
	UpdateRenderStatesIfNecessary( shared_effect, default_render_state_info );

	if ( mNoticeShaderCreated )
	{
		EventShaderCreated event;
		event.mEffect = shared_effect;
		NotifyObservers( this, event );
	}

	return shared_effect;
}

IGraphicEffect* GraphicShaderManager::GetExternalEffect( const GraphicEffectInitializer& initializer, ISerializableNode* vs_node, ISerializableNode* ps_node )
{
	return GetExternalEffect( initializer, GraphicShaderSerializeInitializer( vs_node, ps_node ) );
}

IGraphicEffect* GraphicShaderManager::GetExternalEffect( const GraphicEffectInitializer& initializer, AStringPtr technique_node )
{
	return GetExternalEffect( initializer, GraphicShaderAStringInitializer( technique_node ) );
}

IGraphicEffect* GraphicShaderManager::GetExternalEffect( const GraphicEffectBase& base_effect_info, const GraphicEffectInitializer& initializer )
{
	// Build the existing key code
	_dword existing_key = base_effect_info.ToKey( );

	// Search for the existing effect
	IGraphicEffectRef* exist_effect = mExternalEffects.Search( existing_key );
	if ( exist_effect == _null )
		return _null;

	// Create the shared effect to share same shader code
	IGraphicEffectPassRef shared_effect = new GraphicSharedEffect( *exist_effect, initializer );
	shared_effect->SetRenderStates( (*exist_effect)->GetRenderStates( ) );

	// Update external effects
	_dword key_2 = initializer.ToKey( );
	mExternalEffects[key_2] = shared_effect;

	return shared_effect.GetPtr( );
}

_ubool GraphicShaderManager::ImportEffectsWithSharedShader( const GraphicShaderSerializeInfo& info )
{
	mNoticeShaderCreated = _false;

	GraphicEffectInitializer first_initializer;
	_ubool is_first = _true;

	ISerializableNodeRef effect_node = info.mBaseInfoNode->GetFirstChildNode( );
	while ( effect_node.IsValid( ) )
	{
		GraphicEffectInitializer initializer;
		if ( initializer.Import( effect_node ) )
		{
			initializer.mEmbeddedSystem = _EMBEDDED_SYSTEM_UNKNOWN;
			initializer.mFlags.CombineFlags( GraphicEffectInitializer::_FLAG_HAS_OPTIMIZED );

			if ( is_first )
			{
				is_first = _false;
				first_initializer = initializer;
				GetGraphicShaderManager( )->GetExternalEffect( first_initializer, info.mVSShaderCodeNode, info.mPSShaderCodeNode );
			}
			else
			{
				GetGraphicShaderManager( )->GetExternalEffect( first_initializer, initializer );
			}
		}		

		if ( effect_node->MoveNext( ) == _false )
			break;
	}

	mNoticeShaderCreated = _true;

	return _true;
}

IGraphicEffect*	GraphicShaderManager::GetInternalEffect( _GRAPHIC_INTERNAL_EFFECT_TYPE type )
{
	return GetInternalEffect( type, 0, _GCO_NONE_ );
}

IGraphicEffect* GraphicShaderManager::GetInternalEffect( _GRAPHIC_INTERNAL_EFFECT_TYPE type, _dword enabled_functions, _GRAPHIC_COLOR_OPERATION diffuse_map_color_operation )
{
	EGE_ASSERT( type < _GIET_MAX_NUMBER );

	// Build the key
	_qword key = BuildKeyCode( type, enabled_functions, diffuse_map_color_operation );

	// Search for th existing effect
	IGraphicEffectRef& effect = mInternalEffects[ key ];
	if ( effect.IsValid( ) )
		return effect;

	// Create new internal effect
	effect = BuildInternalEffect( type, enabled_functions, diffuse_map_color_operation );
	return effect;
}

IGraphicEffectPassRef GraphicShaderManager::CreateInternalEffect( _GRAPHIC_INTERNAL_EFFECT_TYPE type )
{
	IGraphicEffect* effect = GetInternalEffect( type );
	if ( effect == _null )
		return _null;

	return CreateSharedEffect( effect );
}

IGraphicEffectPassRef GraphicShaderManager::CreateInternalEffect( _GRAPHIC_INTERNAL_EFFECT_TYPE type, _dword enabled_functions, _GRAPHIC_COLOR_OPERATION diffuse_map_color_operation )
{
	IGraphicEffect* effect = GetInternalEffect( type, enabled_functions, diffuse_map_color_operation );
	if ( effect == _null )
		return _null;

	return CreateSharedEffect( effect );
}
