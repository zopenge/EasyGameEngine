//! @file     TGraphicEffectRenderState.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TGraphicEffectRenderState
//----------------------------------------------------------------------------

template< typename Type >
class TGraphicEffectRenderState : public Type
{
protected:
	//!	The render slot
	_GRAPHIC_RENDER_QUEUE		mRenderSlot;

	//!	The render states stack
	GraphicRenderStateInfoStack	mRenderStates;

protected:
	//!	Refresh render slot.
	_void RefreshRenderSlot( );

	//!	Combine render states.
	_void CombineRenderStatesFromOther( const GraphicRenderStateInfo& info );
	_void CombineRenderStatesFromEffect( IGraphicEffect* effect );

public:
	TGraphicEffectRenderState( );
	virtual ~TGraphicEffectRenderState( );

// ITGraphicEffectRenderState Interface
public:
	virtual _void								SetSamplerState( _dword index, SamplerStateRHI* state ) override;
	virtual _void								SetCubeTextureSamplerState( SamplerStateRHI* state ) override;
	virtual _void								SetRasterizerState( RasterizerStateRHI* state ) override;
	virtual _void								SetDepthState( DepthStateRHI* state ) override;
	virtual _void								SetStencilState( StencilStateRHI* state ) override;
	virtual _void								SetBlendState( BlendStateRHI* state ) override;

	virtual SamplerStateRHI*					GetSamplerState( _dword index ) const override;
	virtual SamplerStateRHI*					GetCubeTextureSamplerState( ) const override;
	virtual RasterizerStateRHI*					GetRasterizerState( ) const override;
	virtual DepthStateRHI*						GetDepthState( ) const override;
	virtual StencilStateRHI*					GetStencilState( ) const override;
	virtual BlendStateRHI*						GetBlendState( ) const override;

	virtual _void								SetRenderStates( const GraphicRenderStateInfo& state_info ) override;
	virtual const GraphicRenderStateInfo&			GetRenderStates( ) const override;

	virtual _void								PushStates( ) override;
	virtual _void								PopStates( ) override;
	virtual const GraphicRenderStateInfoStack&	GetStates( ) const override;

	virtual _GRAPHIC_RENDER_QUEUE				GetRenderSlot( ) const override;

	virtual _void								SetManualDepth( _ubool manual_depth ) override;
	virtual _ubool								GetManualDepth( ) const override;
};

//----------------------------------------------------------------------------
// TGraphicEffectRenderState Implementation
//----------------------------------------------------------------------------

template< typename Type >
TGraphicEffectRenderState< Type >::TGraphicEffectRenderState( )
{
	mRenderSlot = _GRS_TRANSPARENT;

	// Push the initial render states
	mRenderStates.Push( GraphicRenderStateInfo( ) );
}

template< typename Type >
TGraphicEffectRenderState< Type >::~TGraphicEffectRenderState( )
{
}

template< typename Type >
_void TGraphicEffectRenderState< Type >::RefreshRenderSlot( )
{
	if ( mRenderStates.Number( ) == 0 )
	{
		mRenderSlot = _GRS_TRANSPARENT;
		return;
	}

	if ( mRenderStates.Top( ).mManualDepth )
	{
		mRenderSlot = _GRS_OPAQUE;
	}
	else
	{
		if ( mRenderStates.Top().mDepthState != _null )
		{
			DepthStateInitializerRHI depth_state = GetDynamicRHI( )->GetDepthState( mRenderStates.Top( ).mDepthState );
			if ( depth_state.mDepthTest == _CF_ALWAYS )
				mRenderSlot = _GRS_ALWAYSPASS;
			else if ( !depth_state.mEnableDepthWrite )
				mRenderSlot = _GRS_DEPTH_READ_ONLY;
			else
				mRenderSlot = _GRS_TRANSPARENT;
		}
		else
		{
			mRenderSlot = _GRS_TRANSPARENT;
		}
	}
}

template< typename Type >
_void TGraphicEffectRenderState< Type >::CombineRenderStatesFromOther( const GraphicRenderStateInfo& info )
{
	// Update sampler render states
	for ( _dword i = 0; i < _GRAPHIC_MAX_TEX_SLOT_NUMBER; ++ i )
	{
		SamplerStateRHI* sampler_state = info.mSamplerStates[i];
		if ( sampler_state == _null )
			continue;

		SetSamplerState( i, sampler_state );
	}

	// Update render states
	if ( info.mRasterizerState != _null )
		SetRasterizerState( info.mRasterizerState );
	if ( info.mDepthState != _null )
		SetDepthState( info.mDepthState );
	if ( info.mStencilState != _null )
		SetStencilState( info.mStencilState );
	if ( info.mBlendState != _null )
		SetBlendState( info.mBlendState );
	SetManualDepth( info.mManualDepth );
}

template< typename Type >
_void TGraphicEffectRenderState< Type >::CombineRenderStatesFromEffect( IGraphicEffect* effect )
{
	if ( effect == _null )
		return;

	CombineRenderStatesFromOther( effect->GetRenderStates( ) );
}

template< typename Type >
_void TGraphicEffectRenderState< Type >::SetSamplerState( _dword index, SamplerStateRHI* state )
{
	mRenderStates.Top( ).mSamplerStates[ index ] = state;
}

template< typename Type >
_void TGraphicEffectRenderState< Type >::SetCubeTextureSamplerState( SamplerStateRHI* state )
{
	mRenderStates.Top( ).mCubeTextureSamplerState = state;
}

template< typename Type >
_void TGraphicEffectRenderState< Type >::SetRasterizerState( RasterizerStateRHI* state )
{
	mRenderStates.Top( ).mRasterizerState = state;
}

template< typename Type >
_void TGraphicEffectRenderState< Type >::SetDepthState( DepthStateRHI* state )
{
	mRenderStates.Top( ).mDepthState = state;

	RefreshRenderSlot( );
}

template< typename Type >
_void TGraphicEffectRenderState< Type >::SetStencilState( StencilStateRHI* state )
{
	mRenderStates.Top( ).mStencilState = state;
}

template< typename Type >
_void TGraphicEffectRenderState< Type >::SetBlendState( BlendStateRHI* state )
{
	mRenderStates.Top( ).mBlendState = state;
}

template< typename Type >
SamplerStateRHI* TGraphicEffectRenderState< Type >::GetSamplerState( _dword index ) const
{
	return mRenderStates.Top( ).mSamplerStates[ index ];
}

template< typename Type >
SamplerStateRHI* TGraphicEffectRenderState< Type >::GetCubeTextureSamplerState( ) const
{
	return mRenderStates.Top( ).mCubeTextureSamplerState;
}

template< typename Type >
RasterizerStateRHI* TGraphicEffectRenderState< Type >::GetRasterizerState( ) const
{
	return mRenderStates.Top( ).mRasterizerState;
}

template< typename Type >
DepthStateRHI* TGraphicEffectRenderState< Type >::GetDepthState( ) const
{
	return mRenderStates.Top( ).mDepthState;
}

template< typename Type >
StencilStateRHI* TGraphicEffectRenderState< Type >::GetStencilState( ) const
{
	return mRenderStates.Top( ).mStencilState;
}

template< typename Type >
BlendStateRHI* TGraphicEffectRenderState< Type >::GetBlendState( ) const
{
	return mRenderStates.Top( ).mBlendState;
}

template< typename Type >
_void TGraphicEffectRenderState< Type >::SetRenderStates( const GraphicRenderStateInfo& state_info )
{
	mRenderStates.Top( ) = state_info;
}

template< typename Type >
const GraphicRenderStateInfo&	TGraphicEffectRenderState< Type >::GetRenderStates( ) const
{
	return mRenderStates.Top( );
}

template< typename Type >
_void TGraphicEffectRenderState< Type >::PushStates( )
{
	GraphicRenderStateInfo states = mRenderStates.Top( );
	mRenderStates.Push( states );
}

template< typename Type >
_void TGraphicEffectRenderState< Type >::PopStates( )
{
	mRenderStates.Pop( );

	RefreshRenderSlot( );
}

template< typename Type >
const GraphicRenderStateInfoStack& TGraphicEffectRenderState< Type >::GetStates( ) const
{
	return mRenderStates;
}

template< typename Type >
_GRAPHIC_RENDER_QUEUE TGraphicEffectRenderState< Type >::GetRenderSlot( ) const
{
	return mRenderSlot;
}

template< typename Type >
_void TGraphicEffectRenderState< Type >::SetManualDepth( _ubool manual_depth )
{
	mRenderStates.Top( ).mManualDepth = manual_depth;

	RefreshRenderSlot( );
}

template< typename Type >
_ubool TGraphicEffectRenderState< Type >::GetManualDepth( ) const
{
	return mRenderStates.Top( ).mManualDepth;
}

}