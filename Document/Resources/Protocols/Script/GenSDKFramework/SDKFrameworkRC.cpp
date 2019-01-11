//! @file		SDKFrameworkRC.cpp
//! @author		Deen
//! @copyright	...
//! @version	1.0.0.0
//! @date		2017/09/12

#include "SDKFramework.h"
namespace SDKFramework
{

_void RegisterSDKFrameworkRC( WStringPtr module_name )
{
GetStringTable( )->MapResourceID( module_name, L"IDR_ACCELERATOR1", 111 );
GetStringTable( )->MapResourceID( module_name, L"IDR_XML1", 112 );
GetStringTable( )->MapResourceID( module_name, L"_APS_NEXT_RESOURCE_VALUE", 113 );
GetStringTable( )->MapResourceID( module_name, L"_APS_NEXT_COMMAND_VALUE", 40002 );
GetStringTable( )->MapResourceID( module_name, L"_APS_NEXT_CONTROL_VALUE", 1001 );
GetStringTable( )->MapResourceID( module_name, L"_APS_NEXT_SYMED_VALUE", 101 );

}
}

