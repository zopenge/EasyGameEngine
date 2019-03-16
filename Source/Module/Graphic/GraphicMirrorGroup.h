//! @file     GraphicMirrorGroup.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicMirrorGroup
//----------------------------------------------------------------------------

class GraphicMirrorGroup
{
private:
	//!	The mirror info
	struct MirrorInfo
	{
		_ubool				mEnabled;
		IGraphicMirrorRef	mMirror;

		MirrorInfo( )
		{
			mEnabled = _false;
		}
	};
	typedef Array< MirrorInfo* > MirrorInfoArray;
	typedef Map< MirrorInfoArray, _GRAPHIC_MIRROR_TYPE > MirrorInfoMap;

private:
	//! The mirrors
	MirrorInfoMap	mMirrors;

private:
	//!	Create the mirror info
	MirrorInfo* CreateMirrorInfo( MirrorInfoArray& mirrors, IGraphicMirror* mirror );

	//!	Get the flat mirror info
	MirrorInfo* GetFlatMirrorInfo( const Plane& plane, _dword mirror_size );
	//!	Get the sphere mirror info
	MirrorInfo* GetSphereMirrorInfo( _dword mirror_size );

public:
	GraphicMirrorGroup( );
	~GraphicMirrorGroup( );

public:
	_ubool AddFlatMirrorFromGeometry( IGraphicSceneView* scene_view, const Plane& plane, _dword mirror_size, GraphicGeometry& geometry );
	_ubool AddSphereMirrorFromGeometry( _dword mirror_size, GraphicGeometry& geometry );
	
	_void RenderGeometryInMirrors( IGraphicSceneView* scene_view, IGraphicEffect* effect, _dword mirror_reflect_type, GraphicGeometry& geometry );

	_void PresentMirrors( );
};

//----------------------------------------------------------------------------
// GraphicMirrorGroup Implementation
//----------------------------------------------------------------------------

}