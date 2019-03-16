//! @file     TGraphicViewport.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TGraphicViewport
//----------------------------------------------------------------------------

template< typename Type >
class TGraphicViewport : public INTERFACE_OBJECT_IMPL( Type )
{
protected:
	//!	The scene
	IGraphicSceneRef		mScene;
	//!	The scene view
	IGraphicSceneViewRef	mSceneView;

public:
	TGraphicViewport( );
	virtual ~TGraphicViewport( );

// IGraphicViewport Interface
public:
	virtual _void			Clear( _ubool clearcolor, const Color& color, _ubool cleardepth, _float depth, _ubool clearstencil, _dword stencil ) override;

	virtual _void			SetSceneProxy( IGraphicScene* scene ) override;
	virtual IGraphicScene*	GetSceneProxy( ) override;

	virtual Vector2			Convert3DTo2D( const Vector3& point, _float* zsort ) override;
	virtual Vector2			Convert3DTo2D( const PointU& size, const Vector3& point, _float* zsort ) override;
	virtual Ray				GetPickRay( _int x, _int y ) override;
	virtual Ray				GetPickRay( const PointU& size, _int x, _int y ) override;
};

//----------------------------------------------------------------------------
// TGraphicViewport Implementation
//----------------------------------------------------------------------------

template< typename Type >
TGraphicViewport< Type >::TGraphicViewport( )
{
}

template< typename Type >
TGraphicViewport< Type >::~TGraphicViewport( )
{
}

template< typename Type >
_void TGraphicViewport< Type >::Clear( _ubool clearcolor, const Color& color, _ubool cleardepth, _float depth, _ubool clearstencil, _dword stencil )
{
	// Clear buffers
	gDynamicRHI->Clear( clearcolor, color, cleardepth, depth, clearstencil, stencil );
}

template< typename Type >
_void TGraphicViewport< Type >::SetSceneProxy( IGraphicScene* scene )
{
	if ( scene == _null )
		return;

	mScene = scene;
}

template< typename Type >
IGraphicScene* TGraphicViewport< Type >::GetSceneProxy( )
{
	return mScene;
}

template< typename Type >
Vector2 TGraphicViewport< Type >::Convert3DTo2D( const Vector3& point, _float* zsort )
{
	const PointU& client_size = mScene->GetViewport( ).GetSize( );

	return mSceneView->Convert3DTo2D( client_size, point, zsort );
}

template< typename Type >
Vector2 TGraphicViewport< Type >::Convert3DTo2D( const PointU& size, const Vector3& point, _float* zsort )
{
	return mSceneView->Convert3DTo2D( size, point, zsort );
}

template< typename Type >
Ray TGraphicViewport< Type >::GetPickRay( _int x, _int y )
{
	const PointU& client_size = mScene->GetClientSize( );

	return mSceneView->GetPickRay( client_size, x, y );
}

template< typename Type >
Ray TGraphicViewport< Type >::GetPickRay( const PointU& size, _int x, _int y )
{
	return mSceneView->GetPickRay( size, x, y );
}

}