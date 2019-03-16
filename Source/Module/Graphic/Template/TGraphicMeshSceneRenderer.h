//! @file     TGraphicMeshSceneRenderer.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TGraphicMeshSceneRenderer
//----------------------------------------------------------------------------

template< typename Type >
class TGraphicMeshSceneRenderer : public INTERFACE_OBJECT_IMPL( Type )
{
protected:
	typedef GraphicSceneManagerRendererStats Stats;

protected:
	typedef IGraphicMeshSceneRenderer::SceneInfo SceneInfo;

protected:
	IGraphicMeshSceneManagerRef mSceneManager, IGraphicScene* scene, const Viewport& viewport ) PURE;

protected:
	_void Flush( );

protected:
	TGraphicMeshSceneRenderer( );
	virtual ~TGraphicMeshSceneRenderer( );

// IGraphicMeshSceneRenderer Interface
public:
	virtual _void	Begin( SceneInfo* scene_info ) override;
	virtual _void	End( ) override;
};

//----------------------------------------------------------------------------
// TGraphicMeshSceneRenderer Implementation
//----------------------------------------------------------------------------

template< typename Type >
TGraphicMeshSceneRenderer< Type >::TGraphicMeshSceneRenderer( )
{
	mSceneInfo = _null;
}

template< typename Type >
TGraphicMeshSceneRenderer< Type >::~TGraphicMeshSceneRenderer( )
{
}

template< typename Type >
_void TGraphicMeshSceneRenderer< Type >::Flush( )
{
	EGE_ASSERT( mSceneInfo != _null );

	// Flush all VAO
	for ( _dword i = 0; i < mSceneInfo->mBufferNumber; i ++ )
	{
		IGraphicVertexArray* vao = mSceneInfo->mVAOList[i];
		EGE_ASSERT( vao != _null );

		vao->FlushBuffers( );
	}
}

template< typename Type >
_void TGraphicMeshSceneRenderer< Type >::Begin( SceneInfo* scene_info )
{
	EGE_ASSERT( scene_info != _null );

	mSceneInfo = scene_info;

	Flush( );
}

template< typename Type >
_void TGraphicMeshSceneRenderer< Type >::End( )
{
	mSceneInfo = _null;
}

}