//! @file     GraphicVRDevice.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

#if (_ENABLE_VR_SOFTWARE == 0)

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicVRDevice
//----------------------------------------------------------------------------

class GraphicVRDevice : public TObject< IGraphicVRDevice >
{
public:
	GraphicVRDevice( );
	virtual ~GraphicVRDevice( );

// IGraphicDrawer Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_DRAWER_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames { Return GetGraphicViewport( )->Name Parameters; }
	#include "Module/Graphic/Methods/GraphicDrawerMethods.h"
	#undef DEFINE_DRAWER_METHOD

// IGraphicScene Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_SCENE_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames { Return GetGraphicViewport( )->Name Parameters; }
	#include "Module/Graphic/Methods/GraphicSceneMethods.h"
	#undef DEFINE_SCENE_METHOD
	
// IGraphicVRDevice Interface
public:
	// The drawer methods are defined as virtual functions.
	#define DEFINE_VRDEVICE_METHOD(Type,Name,ParameterTypesAndNames,Parameters,Return,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Module/Graphic/Methods/GraphicVRDeviceMethods.h"
	#undef DEFINE_VRDEVICE_METHOD
};

}

#endif