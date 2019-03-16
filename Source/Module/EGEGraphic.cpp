//! @file     EGEGraphic.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEGraphic.h"

IDynamicRHI*				gDynamicRHI				= _null;
ViewportRHI*				gSharedViewportRHI		= _null;
IResourceManagerRHI*		gResourceManagerRHI		= &NullGraphic::GetInstance( ).GetDeviceManagerRHI( );
IGraphicViewport*			gGraphicViewport		= _null;
IGraphicResourceManager*	gGraphicResourceManager	= _null;
IGraphicVRDevice*			gGraphicVRDevice		= &NullGraphic::GetInstance( ).GetGraphicVRDevice( );
IGraphicModule*				gGraphicModule			= _null;

//----------------------------------------------------------------------------
// Interface Accessors Implementation
//----------------------------------------------------------------------------

#undef GetGraphicViewport
EGE_INTERNAL IGraphicViewport* GetGraphicViewport( )
{
	return gGraphicViewport;
}

#undef GetGraphicVRDevice
EGE_INTERNAL IGraphicVRDevice* GetGraphicVRDevice( )
{
	return gGraphicVRDevice;
}

#undef GetGraphicResourceManager
EGE_INTERNAL IGraphicResourceManager* GetGraphicResourceManager( )
{
	return gGraphicResourceManager;
}

#undef GetGraphicModule
EGE_INTERNAL IGraphicModule* GetGraphicModule( )
{
	return gGraphicModule;
}

#undef GetDynamicRHI
EGE_INTERNAL IDynamicRHI* GetDynamicRHI( )
{
	return gDynamicRHI;
}

#undef GetResourceManagerRHI
EGE_INTERNAL IResourceManagerRHI* GetResourceManagerRHI( )
{
	return gResourceManagerRHI;
}

#undef CreateGraphicModule
EGE_INTERNAL _boolean CreateGraphicModule( _handle app_handle, const PointU& size, _dword multisample )
{
	// Create module
	typedef PassRefPtr< GraphicModule > GraphicModulePassRef;
	GraphicModulePassRef module = new GraphicModule( );

	// Update the global module
	gGraphicModule = module.GetPtr( );

	// Register it to module manager
	GetModuleManager( )->RegisterModule( module.GetPtr( ), EGE_GRAPHIC_MODULE_PRIORITY );

	// Initialize module
	_boolean ret = EGE_BOOLEAN( module->Initialize( app_handle, size, multisample ) );
	return ret;
}