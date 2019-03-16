//! @file     GraphicSharedViewport.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicSharedViewport
//----------------------------------------------------------------------------

class GraphicSharedViewport : public TObject< IGraphicViewport >
{
private:
	//!	The viewport
	IGraphicViewportRef	mViewport;

private:
	_void BindViewport( );
	_void BindViewport( ) const;

public:
	GraphicSharedViewport( IGraphicViewport* viewport );
	virtual ~GraphicSharedViewport( );

// IGraphicDrawer Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_DRAWER_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames { BindViewport( ); Return mViewport->Name Parameters; }
	#include "Module/Graphic/Methods/GraphicDrawerMethods.h"
	#undef DEFINE_DRAWER_METHOD

// IGraphicScene Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_SCENE_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames { BindViewport( ); Return mViewport->Name Parameters; }
	#include "Module/Graphic/Methods/GraphicSceneMethods.h"
	#undef DEFINE_SCENE_METHOD

// IGraphicViewport Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_VIEWPORT_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames { BindViewport( ); Return mViewport->Name Parameters; }
	#define CUSTOM_PRESENT
	#include "Module/Graphic/Methods/GraphicViewportMethods.h"
	#undef DEFINE_VIEWPORT_METHOD

	virtual _void Present( ) override;
};

//----------------------------------------------------------------------------
// GraphicSharedViewport Implementation
//----------------------------------------------------------------------------

}