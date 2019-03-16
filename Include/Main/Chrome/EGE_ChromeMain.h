//! @file     EGE_ChromeMain.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

// PPAPI SDK Files
#include <ppapi/c/pp_errors.h>
#include <ppapi/c/ppb_instance.h>
#include <ppapi/c/ppp.h>
#include <ppapi/c/ppp_instance.h>
#include <sdk_util/macros.h>

// ViewBased Application
#define RUN_VIEWBASED_APP( creation_flag /*not used*/, x )											\
	FORCE_LINK_THIS( ps_entry )																		\
	EGE_EXTERNAL																					\
	{																								\
		/* Be used by Chrome-Application to create the user application delegate in core */			\
		EGE_INTERNAL EGE::IViewBasedAppDelegate* CreateChromeAppDelegate( )							\
		{																							\
			return new x( );																		\
		}																							\
		/* Initialize module */																		\
		PP_EXPORT int32_t PPP_InitializeModule( PP_Module module_id, PPB_GetInterface get_browser ) \
		{																							\
			return GetPPResourceModule( )->OnInitializeModule( module_id, get_browser );			\
		}																							\
		/* Get interface */																			\
		PP_EXPORT const void* PPP_GetInterface( const char* interface_name )						\
		{																							\
			return GetPPResourceModule( )->OnGetInterface( interface_name );						\
		}																							\
		/* Module shutdown */																		\
		PP_EXPORT void PPP_ShutdownModule( )														\
		{																							\
			GetPPResourceModule( )->OnShutdownModule( );											\
		}																							\
	}
