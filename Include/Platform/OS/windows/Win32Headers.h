#pragma once

// Exclude rarely-used stuff from Windows headers
#ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN
#endif

// We initialize GUID in static library way
#ifndef INITGUID
#	define INITGUID
#endif

// The windows base header file
#include <windows.h>
// The IP header file
#include <IPHlpApi.h>

//#if !defined(strdup)
//	#define strdup _strdup
//#endif
