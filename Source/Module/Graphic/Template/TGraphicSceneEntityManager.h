//! @file     TGraphicSceneEntityManager.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TGraphicSceneEntityManager
//----------------------------------------------------------------------------

template< typename Type >
class TGraphicSceneEntityManager : public TObject< Type >
{
protected:

protected:
	TGraphicSceneEntityManager( );
	virtual ~TGraphicSceneEntityManager( );

// IGraphicSceneEntityManager Interface
public:
	virtual _void	OnAddMesh( IGraphicMesh* mesh ) override;
	virtual _void	OnRemoveMesh( IGraphicMesh* mesh ) override;
	virtual _void	OnUpdateMesh( IGraphicMesh* mesh ) override;
};

//----------------------------------------------------------------------------
// TGraphicSceneEntityManager Implementation
//----------------------------------------------------------------------------

template< typename Type >
TGraphicSceneEntityManager< Type >::TGraphicSceneEntityManager( )
{
}

template< typename Type >
TGraphicSceneEntityManager< Type >::~TGraphicSceneEntityManager( )
{
}

template< typename Type >
_void TGraphicSceneEntityManager< Type >::OnAddMesh( IGraphicMesh* mesh )
{

}

template< typename Type >
_void TGraphicSceneEntityManager< Type >::OnRemoveMesh( IGraphicMesh* mesh )
{

}

template< typename Type >
_void TGraphicSceneEntityManager< Type >::OnUpdateMesh( IGraphicMesh* mesh )
{

}

}