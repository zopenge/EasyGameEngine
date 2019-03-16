//! @file     TGraphicScene.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TGraphicScene
//----------------------------------------------------------------------------

template< typename Type >
class TGraphicScene : public INTERFACE_OBJECT_IMPL( Type )
{
protected:
	//!	The scissor rect info
	template< typename DataType >
	struct ScissorRectInfo
	{
		_ubool				mEnable;
		Rect< DataType >	mRect;

		ScissorRectInfo( ) 
		{
			mEnable	= _false;
			mRect	= Rect< DataType >::cNull;
		}
		ScissorRectInfo( _ubool enable, const Rect< DataType >& rect )
		{
			mEnable	= enable;
			mRect	= rect;
		}
	};
	typedef ScissorRectInfo< _dword > ScissorRectUInfo;
	typedef ScissorRectInfo< _float > ScissorRectFInfo;
	typedef Stack< ScissorRectUInfo > ScissorRectUStack;
	typedef Stack< ScissorRectFInfo > ScissorRectFStack;

	//!	The overlay transform info.
	struct OverlayTransformInfo
	{
		Matrix3	mTransform;
		Matrix3	mInversedTransform;

		OverlayTransformInfo( )
		{
			mTransform			= Matrix3::cIdentity;
			mInversedTransform	= Matrix3::cIdentity;
		}
		OverlayTransformInfo( const Matrix3& transform )
		{
			mTransform			= transform;
			mInversedTransform	= transform;
			mInversedTransform.Inverse( );
		}
	};
	typedef Stack< OverlayTransformInfo > OverlayTransformInfoStack;

	//!	The render slot stack
	typedef Stack< _GRAPHIC_RENDER_QUEUE > RenderSlotStack;

protected:
	//!	The client size
	PointU						mClientSize;

	//!	The viewport of ratio
	Viewport					mViewport;

	//!	The environment's texture cube
	IGraphicTextureCubeRef		mEnvTextureCube;

	//!	The render slot stack
	RenderSlotStack				mRenderSlotStack;

	//!	The scissor rect stack
	ScissorRectUStack			mScissorRectStack;
	//!	The overlay scissor rect stack
	ScissorRectFStack			mOverlayScissorRectStack;
	//!	The overlay transform
	OverlayTransformInfoStack	mOverlayTransformStack;
	//!	The overlay world transform
	Matrix4Stack				mUserOrthoTransformStack;
	//!	The offset transform
	Matrix4Stack				mOffsetTransformStack;

	//!	The scene view
	IGraphicSceneViewRef		mSceneView;

	//!	Clear buffers operations
	GraphicClearBuffersInfo			mClearBuffersInfo;

protected:
	//!	Reset clear buffers operations.
	_void ResetClearBuffersOperations( );

protected:
	//!	When update scissor rect.
	virtual _void OnUpdateScissorRect( _ubool enable, const RectU& rect ) { }

protected:
	TGraphicScene( );
	virtual ~TGraphicScene( );

// IGraphicSceneDrawer Interface
public:
	virtual _void					SetScissorRect( _ubool enable, const RectU& rect ) override;
	virtual _void					GetScissorRect( _ubool& enable, RectU& rect ) const override;
	virtual _void					PushScissorRect( _ubool enable, const RectU& rect ) override;
	virtual _void					PopScissorRect( ) override;

	virtual _void					PushOverlayScissorRect( const RectF& rect ) override;
	virtual _void					PopOverlayScissorRect( ) override;

	virtual _void					PushOverlayTransform( const Matrix3& transform ) override;
	virtual _void					PopOverlayTransform( ) override;
	virtual _void					SetOverlayTransform( const Matrix3& transform ) override;
	virtual const Matrix3&			GetOverlayTransform( ) const override;

	virtual _void					PushUserOrthoTransform( const Matrix4& transform ) override;
	virtual _void					PopUserOrthoTransform( ) override;
	virtual _void					SetUserOrthoTransform( const Matrix4& transform ) override;
	virtual const Matrix4&			GetUserOrthoTransform( ) const override;

	virtual _void					PushOffsetTransform( const Matrix4& transform ) override;
	virtual _void					PopOffsetTransform( ) override;
	virtual _void					SetOffsetTransform( const Matrix4& transform ) override;
	virtual const Matrix4&			GetOffsetTransform( ) const override;

// IGraphicScene Interface
public:
	virtual _void					SetViewport( const Viewport& viewport ) override;
	virtual const Viewport&			GetViewport( ) const override;

	virtual _void					SetClientSize( const PointU& size ) override;
	virtual const PointU&			GetClientSize( ) const override;

	virtual _void					ClearRenderBuffers( _ubool clearcolor, const Color& color, _ubool cleardepth, _float depth, _ubool clearstencil, _dword stencil ) override;
	virtual _void					PresentRenderBuffers( ) override;
	virtual _void					PresentRenderBuffers( IGraphicCanvas* canvas ) override;

	virtual _void					SetSceneView( IGraphicSceneView* view ) override;
	virtual IGraphicSceneView*		GetSceneView( ) const override;

	virtual _void					PushRenderSlot( _GRAPHIC_RENDER_QUEUE slot ) override;
	virtual _void					PopRenderSlot( ) override;
	virtual _void					SetRenderSlot( _GRAPHIC_RENDER_QUEUE slot ) override;
	virtual _GRAPHIC_RENDER_QUEUE	GetRenderSlot( ) const override;
};

//----------------------------------------------------------------------------
// TGraphicScene Implementation
//----------------------------------------------------------------------------

template< typename Type >
TGraphicScene< Type >::TGraphicScene( ) 
{
	mClientSize		= PointU::cZeroPoint;

	mScale			= Vector2::cIdentity;
	mViewport		= Viewport::cNull;

	mSceneView		= GetGraphicResourceManager( )->CreateSceneView( );

	mRenderSlotStack.Push( _GRS_TRANSPARENT );

	mScissorRectStack.Push( ScissorRectUInfo( _false, RectU::cNull ) );
	mOverlayScissorRectStack.Push( ScissorRectFInfo( _false, RectF::cNull ) );
	mOverlayTransformStack.Push( OverlayTransformInfo( ) );
	mUserOrthoTransformStack.Push( Matrix4::cIdentity );
	mOffsetTransformStack.Push( Matrix4::cIdentity );

	ResetClearBuffersOperations( );

	// Enable check mesh visibility feature in default
	EnableOptions( _GSO_ENABLE_CHECK_MESH_VISIBILITY, _true );
}

template< typename Type >
TGraphicScene< Type >::~TGraphicScene( )
{
}

template< typename Type >
_void TGraphicScene< Type >::ResetClearBuffersOperations( )
{
	mClearBuffersInfo.Reset( );
}

template< typename Type >
_void TGraphicScene< Type >::SetScissorRect( _ubool enable, const RectU& rect )
{
	ScissorRectUInfo& scissor_info	= mScissorRectStack.Top( );
	scissor_info.mEnable			= enable;
	scissor_info.mRect				= rect;

	OnUpdateScissorRect( enable, rect );
}

template< typename Type >
_void TGraphicScene< Type >::GetScissorRect( _ubool& enable, RectU& rect ) const
{
	const ScissorRectUInfo& scissor_info = mScissorRectStack.Top( );

	enable	= scissor_info.mEnable;
	rect	= scissor_info.mRect;
}

template< typename Type >
_void TGraphicScene< Type >::PushScissorRect( _ubool enable, const RectU& rect )
{
	mScissorRectStack.Push( ScissorRectUInfo( enable, rect ) );

	OnUpdateScissorRect( enable, rect );
}

template< typename Type >
_void TGraphicScene< Type >::PopScissorRect( )
{
	// At least we have one scissor rect info
	if ( mScissorRectStack.Number( ) == 1 )
		return;

	mScissorRectStack.Pop( );
	const ScissorRectUInfo& scissor_info = mScissorRectStack.Top( );

	OnUpdateScissorRect( scissor_info.mEnable, scissor_info.mRect );
}

template< typename Type >
_void TGraphicScene< Type >::PushOverlayScissorRect( const RectF& rect )
{
	mOverlayScissorRectStack.Push( ScissorRectFInfo( _true, rect ) );
}

template< typename Type >
_void TGraphicScene< Type >::PopOverlayScissorRect( )
{
	// At least we have one scissor rect info
	EGE_ASSERT( mOverlayScissorRectStack.Number( ) != 1 );

	mOverlayScissorRectStack.Pop( );
}

template< typename Type >
_void TGraphicScene< Type >::PushOverlayTransform( const Matrix3& transform )
{
	mOverlayTransformStack.Push( OverlayTransformInfo( transform ) );
}

template< typename Type >
_void TGraphicScene< Type >::PopOverlayTransform( )
{
	EGE_ASSERT( mOverlayTransformStack.Number( ) != 1 );

	mOverlayTransformStack.Pop( );
}

template< typename Type >
_void TGraphicScene< Type >::SetOverlayTransform( const Matrix3& transform )
{
	mOverlayTransformStack.Top( ) = OverlayTransformInfo( transform );
}

template< typename Type >
const Matrix3& TGraphicScene< Type >::GetOverlayTransform( ) const
{
	return mOverlayTransformStack.Top( ).mTransform;
}

template< typename Type >
_void TGraphicScene< Type >::PushUserOrthoTransform( const Matrix4& transform )
{
	mUserOrthoTransformStack.Push( transform );
}

template< typename Type >
_void TGraphicScene< Type >::PopUserOrthoTransform( )
{
	EGE_ASSERT( mUserOrthoTransformStack.Number( ) != 1 );

	mUserOrthoTransformStack.Pop( );
}

template< typename Type >
_void TGraphicScene< Type >::SetUserOrthoTransform( const Matrix4& transform )
{
	mUserOrthoTransformStack.Top( ) = transform;
}

template< typename Type >
const Matrix4& TGraphicScene< Type >::GetUserOrthoTransform( ) const
{
	return mUserOrthoTransformStack.Top( );
}

template< typename Type >
_void TGraphicScene< Type >::PushOffsetTransform( const Matrix4& transform )
{
	mOffsetTransformStack.Push( transform );
}

template< typename Type >
_void TGraphicScene< Type >::PopOffsetTransform( )
{
	EGE_ASSERT( mOffsetTransformStack.Number( ) != 1 );

	mOffsetTransformStack.Pop( );
}

template< typename Type >
_void TGraphicScene< Type >::SetOffsetTransform( const Matrix4& transform )
{
	mOffsetTransformStack.Top( ) = transform;
}

template< typename Type >
const Matrix4& TGraphicScene< Type >::GetOffsetTransform( ) const
{
	return mOffsetTransformStack.Top( );
}

template< typename Type >
_void TGraphicScene< Type >::SetViewport( const Viewport& viewport )
{
	mViewport = viewport;
}

template< typename Type >
const Viewport& TGraphicScene< Type >::GetViewport( ) const
{
	return mViewport;
}

template< typename Type >
_void TGraphicScene< Type >::SetClientSize( const PointU& size )
{
	// Update the viewport
	mViewport = Viewport( 0.0f, 0.0f, (_float)size.x, (_float)size.y, 0.0f, 1.0f );

	// Update client size
	mClientSize = size;
}

template< typename Type >
const PointU& TGraphicScene< Type >::GetClientSize( ) const
{
	return mClientSize;
}

template< typename Type >
_void TGraphicScene< Type >::ClearRenderBuffers( _ubool clearcolor, const Color& color, _ubool cleardepth, _float depth, _ubool clearstencil, _dword stencil )
{
	mClearBuffersInfo.mIsClearColor		= clearcolor;
	mClearBuffersInfo.mIsClearDepth		= cleardepth;
	mClearBuffersInfo.mIsClearStencil	= clearstencil;
	mClearBuffersInfo.mClearColor		= color;
	mClearBuffersInfo.mClearDepth		= depth;
	mClearBuffersInfo.mClearStencil		= stencil;
}

template< typename Type >
_void TGraphicScene< Type >::PresentRenderBuffers( )
{
}

template< typename Type >
_void TGraphicScene< Type >::PresentRenderBuffers( IGraphicCanvas* canvas )
{

}

template< typename Type >
_void TGraphicScene< Type >::SetSceneView( IGraphicSceneView* view )
{
	mSceneView = view;
}

template< typename Type >
IGraphicSceneView* TGraphicScene< Type >::GetSceneView( ) const
{
	return mSceneView.GetPtr( );
}

template< typename Type >
_void TGraphicScene< Type >::SetEnvTextureCube( IGraphicTextureCube* texture_cube )
{
	mEnvTextureCube = texture_cube;
}

template< typename Type >
IGraphicTextureCube* TGraphicScene< Type >::GetEnvTextureCube( )
{
	return mEnvTextureCube;
}

template< typename Type >
_void TGraphicScene< Type >::PushRenderSlot( _GRAPHIC_RENDER_QUEUE slot )
{
	mRenderSlotStack.Push( slot );
}

template< typename Type >
_void TGraphicScene< Type >::PopRenderSlot( )
{
	mRenderSlotStack.Pop( );

	// The 'AUTO' render slot is our default setting
	EGE_ASSERT( mRenderSlotStack.Number( ) != 0 );
}

template< typename Type >
_void TGraphicScene< Type >::SetRenderSlot( _GRAPHIC_RENDER_QUEUE slot )
{
	mRenderSlotStack.Top( ) = slot;
}

template< typename Type >
_GRAPHIC_RENDER_QUEUE TGraphicScene< Type >::GetRenderSlot( ) const
{
	return mRenderSlotStack.Top( );
}

}