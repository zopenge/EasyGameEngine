//! @file     EGEScript.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#ifndef _EGE_SCRIPT_PCH_
#define _EGE_SCRIPT_PCH_

// The compile config
#include "EGE_Compile.h"

// Script library config file
#include "Module/Script/ScriptLibraryConfig.h"

// Python SDK
#if (_SCRIPT_USE_PYTHON_ == 1)
	#include "Python.h"
	#include "frameobject.h"
// JavaScript SDK
#elif (_SCRIPT_USE_JAVA_SCRIPT_CORE_ == 1)
	#define JS_NO_EXPORT
	#include "JavaScriptCore/JavaScript.h"
	#include "JavaScriptCore/API/JSBasePrivate.h"
	#include "JavaScriptCore/API/JSContextRefPrivate.h"
	#include "JavaScriptCore/API/JSObjectRefPrivate.h"
// Google-v8 SDK
#elif (_SCRIPT_USE_GOOGLE_V8_ == 1)
	#include "v8.h"
// SpiderMonkey SDK
#elif (_SCRIPT_USE_SPIDER_MONKEY_ == 1)
	#ifdef _PLATFORM_WINDOWS_
		#define XP_WIN
		#define __STDC_LIMIT_MACROS 
		#include <stdint.h>
		#define STATIC_JS_API
	#elif _PLATFORM_ANDROID_
		#ifdef _SCRIPT_USE_OLD_SPIDER_MONKEY_
			#define JS_CPU_ARM
			#define XP_UNIX
			#define JS_HAVE_STDINT_H
			#define __STDC_LIMIT_MACROS
			#define IS_BIG_ENDIAN 1
			#define JS_BYTES_PER_DOUBLE 8
			#define JS_BYTES_PER_WORD 4
			#define JS_BITS_PER_WORD_LOG2 5
			#define JS_ALIGN_OF_POINTER 4
		#else
			#define __STDC_LIMIT_MACROS 
			#define STATIC_JS_API
			#ifdef DEBUG
				#define JS_DEBUG
			#endif
			#include <stdint.h>
		#endif
	#endif

	#pragma warning( push )
	#pragma warning( disable : 4800 )
	#include "jsapi.h"
	#include "jsdbgapi.h"
	#ifdef _SCRIPT_USE_OLD_SPIDER_MONKEY_
		#include "jsvalue.h"
		#include "jsfun.h"
	#endif
	#pragma warning( pop ) 
// LUA SDK
#elif (_SCRIPT_USE_LUA_ == 1)
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "tolua/tolua.h"
}
extern "C" {
#include "luasocket.h"
}
#endif

// Windows Platform
#if defined _PLATFORM_WINDOWS_

	#include "Platform/OS/windows/Win32Headers.h"
	#include "Platform/OS/windows/Win32Macros.h"
	
// IOS Platform
#elif defined _PLATFORM_IOS_

#endif

// EasyGameEngine Headers
#include "EGE_Always.h"
#include "EGE_Engine.h"
#include "EGE_Modules.h"
#include "Interface/Module/EGE_Script.h"

// Log Files
#undef DEFINE_MODULE 
#define DEFINE_MODULE gScriptModule->
#include "EGE_Logs.h"

// Internal Script Interface Files
#include "Module/Script/script/_script.h"
#include "Module/Script/script/_scriptSystem.h"

// Null Classes
#include "Module/Script/ScriptNullClasses.h"

// Global variables
extern EGE::IScriptResourceManager*	gScriptResourceManager;
extern EGE::IScriptModule*			gScriptModule;

// Script Call-Invoker Files ( Thanks for AngelScript sharing the code )
#include "Module/Script/callfunc/script_callfunc_config.h"
#include "Module/Script/callfunc/script_callfunc.h"

// Internal Script Files
#include "Module/Script/script/_scriptHelper.h"

// Template Files
#include "Module/Script/script/template/_t_scriptSystem.h"

// _script[python] Files
#if (_SCRIPT_USE_PYTHON_ == 1)
#include "Module/Script/script/python/_pyHelper.h"
#include "Module/Script/script/python/_pyObjResource.h"
#include "Module/Script/script/python/_pyTypeObjManager.h"
#include "Module/Script/script/python/_pyValue.h"
#include "Module/Script/script/python/_pyFunction.h"
#include "Module/Script/script/python/_pyModule.h"
#include "Module/Script/script/python/_pyVM.h"
#include "Module/Script/script/python/_pySystem.h"
#elif (_SCRIPT_USE_JS_ == 1)
#include "Module/Script/script/jsc/_jscHelper.h"
#include "Module/Script/script/jsc/_jscObjResource.h"
#include "Module/Script/script/jsc/_jscCore.h"
#include "Module/Script/script/jsc/_jscValue.h"
#include "Module/Script/script/jsc/_jscException.h"
#include "Module/Script/script/jsc/_jscFunction.h"
#include "Module/Script/script/jsc/_jscModule.h"
#include "Module/Script/script/jsc/_jscGlobal.h"
#include "Module/Script/script/jsc/_jscVM.h"
#include "Module/Script/script/jsc/_jscCallStack.h"
#include "Module/Script/script/jsc/_jscSystem.h"
#elif (_SCRIPT_USE_LUA_ == 1)
#include "Module/Script/script/lua/_luaHelper.h"
#include "Module/Script/script/lua/_luaObjResource.h"
#include "Module/Script/script/lua/_luaValue.h"
#include "Module/Script/script/lua/_luaHelper.h"
#include "Module/Script/script/lua/_luaFunction.h"
#include "Module/Script/script/lua/_luaModule.h"
#include "Module/Script/script/lua/_luaCore.h"
#include "Module/Script/script/lua/_luaVM.h"
#include "Module/Script/script/lua/_luaDebuggerCode.h"
#include "Module/Script/script/lua/_luaSystem.h"
#endif

// Script Files
#include "Module/Script/ScriptVersion.h"
#include "Module/Script/ScriptParser.h"
#include "Module/Script/ScriptValue.h"
#include "Module/Script/ScriptFunction.h"
#include "Module/Script/ScriptFile.h"
#include "Module/Script/ScriptClass.h"
#include "Module/Script/ScriptGeneric.h"
#include "Module/Script/ScriptVM.h"
#include "Module/Script/ScriptResourceManager.h"
#include "Module/Script/ScriptModule.h"

// Using namespace here to prevent some name conflict 
using namespace EGE;

// Link external libraries
#if defined _PLATFORM_WINDOWS_
	#if (_SCRIPT_USE_PYTHON_ == 1)
		#pragma comment( lib, "libpython.lib" )
	#elif (_SCRIPT_USE_JAVA_SCRIPT_CORE_ == 1)
		#pragma comment( lib, "libICU.lib" )
		#pragma comment( lib, "libwtf.lib" )
		#pragma comment( lib, "libJavaScriptCore.lib" )
	#elif (_SCRIPT_USE_GOOGLE_V8_ == 1)
		#pragma comment( lib, "libICU.lib" )
		#pragma comment( lib, "libv8.lib" )
	#elif (_SCRIPT_USE_SPIDER_MONKEY_ == 1)
		#pragma comment( lib, "libspidermonkey.lib" )
	#elif (_SCRIPT_USE_LUA_ == 1)
		#pragma comment( lib, "liblua.lib" )
		#pragma comment( lib, "libluasocket.lib" )
	#endif
#elif defined _PLATFORM_IOS_

#endif


#endif // _EGE_SCRIPT_PCH_