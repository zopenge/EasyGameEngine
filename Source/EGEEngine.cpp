//! @file     EGEEngine.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

// The global variables
#if _ENABLE_CAPTURE_STD_STREAM == 1
EGE::stdCapture* sstdCapture = _null;
EGE::stdTraceStreamBuf* sstdTraceStreamBuf = _null;
EGE::stdErrorStreamBuf* sstdErrorStreamBuf = _null;
EGE::stdTraceStreamPipe* sstdTraceStreamPipe = _null;
EGE::stdErrorStreamPipe* sstdErrorStreamPipe = _null;
#endif
#if defined(_PLATFORM_ANDROID_)
EGE::androidViewBasedApp gAndroidViewbasedApp;
#endif

// The global variables
_dword gFrameNumber = 0;
_handle gMainWindowHandle = _null;
IViewBasedApp* gMainViewBasedApp = _null;
IGarbageCollector* gGarbageCollector = _null;
IAppDelegate* gAppDelegate = _null;
IModuleManager* gModuleManager = &NullEngine::GetInstance().GetModuleManager();

//----------------------------------------------------------------------------
// Interface Accessors Implementation
//----------------------------------------------------------------------------

#if defined _PLATFORM_WINDOWS_

#	undef GetWinPlatform
EGE_INTERNAL IWinPlatform* GetWinPlatform() {
	static winPlatform sWinPlatform;
	return &sWinPlatform;
}

#	undef GetWinBluetoothAdapter
EGE_INTERNAL IBluetoothAdapter* GetWinBluetoothAdapter() {
	static winBluetoothAdapter sWinBluetoothAdapter;
	return &sWinBluetoothAdapter;
}

#	undef GetWinNet
EGE_INTERNAL INet* GetWinNet() {
	static winNet sWinNet;
	return &sWinNet;
}

#	undef GetWinSensorManager
EGE_INTERNAL ISensorManager* GetWinSensorManager() {
	static winSensorManager sWinSensorManager;
	return &sWinSensorManager;
}

#	undef GetWinControllerManager
EGE_INTERNAL IControllerManager* GetWinControllerManager() {
	static winControllerManager sWinControllerManager;
	return &sWinControllerManager;
}

#elif defined _PLATFORM_IOS_

#	undef GetIOSPlatform
EGE_INTERNAL IIOSPlatform* GetIOSPlatform() {
	static iosPlatform sIOSPlatform;
	return &sIOSPlatform;
}

#	undef GetIOSBluetoothAdapter
EGE_INTERNAL IBluetoothAdapter* GetIOSBluetoothAdapter() {
	static iosBluetoothAdapter sIOSBluetoothAdapter;
	return &sIOSBluetoothAdapter;
}

#	undef GetIOSNet
EGE_INTERNAL INet* GetIOSNet() {
	static iosNet sIOSNet;
	return &sIOSNet;
}

#	undef GetIOSSensorManager
EGE_INTERNAL ISensorManager* GetIOSSensorManager() {
	static iosSensorManager sIOSSensorManager;
	return &sIOSSensorManager;
}

#	undef GetIOSControllerManager
EGE_INTERNAL IControllerManager* GetIOSControllerManager() {
	static iosControllerManager sIOSControllerManager;
	return &sIOSControllerManager;
}

#elif defined _PLATFORM_ANDROID_

#	undef GetAndroidPlatform
EGE_INTERNAL IAndroidPlatform* GetAndroidPlatform() {
	static androidPlatform sAndroidPlatform;
	return &sAndroidPlatform;
}

#	undef GetAndroidBluetoothAdapter
EGE_INTERNAL IBluetoothAdapter* GetAndroidBluetoothAdapter() {
	static androidBluetoothAdapter sAndroidBluetoothAdapter;
	return &sAndroidBluetoothAdapter;
}

#	undef GetAndroidNet
EGE_INTERNAL INet* GetAndroidNet() {
	static androidNet sAndroidNet;
	return &sAndroidNet;
}

#	undef GetAndroidSensorManager
EGE_INTERNAL ISensorManager* GetAndroidSensorManager() {
	static androidSensorManager sAndroidSensorManager;
	return &sAndroidSensorManager;
}

#	undef GetAndroidControllerManager
EGE_INTERNAL IControllerManager* GetAndroidControllerManager() {
	static androidControllerManager sAndroidControllerManager;
	return &sAndroidControllerManager;
}

#endif

#undef GetMainWindowHandle
EGE_INTERNAL _handle GetMainWindowHandle() {
	return gMainWindowHandle;
}

#undef GetMainViewBasedApp
EGE_INTERNAL IViewBasedApp* GetMainViewBasedApp() {
	return gMainViewBasedApp;
}

#undef GetAppDelegate
EGE_INTERNAL IAppDelegate* GetAppDelegate() {
	return gAppDelegate;
}

#undef GetModuleManager
EGE_INTERNAL IModuleManager* GetModuleManager() {
	return gModuleManager;
}

#undef GetGarbageCollector
EGE_INTERNAL IGarbageCollector* GetGarbageCollector() {
	return gGarbageCollector;
}

#undef GetImageProcessor
EGE_INTERNAL IImageProcessor* GetImageProcessor() {
	static ImageProcessor sImageProcessor;
	return &sImageProcessor;
}

#undef GetStringTable
EGE_INTERNAL IStringTable* GetStringTable() {
	static StringTable sStringTable;
	return &sStringTable;
}

#undef GetWorkingArchive
EGE_INTERNAL IArchive* GetWorkingArchive() {
	return GetPlatform()->GetWorkingArchive();
}

#undef GetInterfaceFactory
EGE_INTERNAL IInterfaceFactory* GetInterfaceFactory() {
	static InterfaceFactory sInterfaceFactory;
	return &sInterfaceFactory;
}

#undef SetMainWindowHandle
EGE_INTERNAL _void SetMainWindowHandle(_handle handle) {
	gMainWindowHandle = handle;
}

#undef SetMainViewBasedApp
EGE_INTERNAL _void SetMainViewBasedApp(IViewBasedApp* app) {
	if (app != _null)
		app->AddRef();

	if (gMainViewBasedApp != _null)
		gMainViewBasedApp->Release();

	gMainViewBasedApp = app;
	WLOG_TRACE_1(L"Set '0x%.8x' as main viewbased application", (_qword)app);

	if (app != _null) {
		gMainWindowHandle = app->GetApplicationHandle();
		WLOG_TRACE_1(L"Set '0x%.8x' as main window handle", (_qword)gMainWindowHandle);
	}
}

#undef EGE_ResetResources
EGE_INTERNAL _boolean EGE_ResetResources() {
	WLOG_TRACE(L"Resetting EGE ... \n");

	// Resume all modules resources
	if (GetModuleManager()->ResetResources() == _false) {
		WLOG_TRACE(L"Resetting EGE failed \n");
		return _false;
	}

	WLOG_TRACE(L"Resetting EGE OK \n");

	return _true;
}

#undef EGE_UnloadResources
EGE_INTERNAL _void EGE_UnloadResources() {
	// Unload all modules resources
	GetModuleManager()->UnloadResources();
}

#undef EGE_Initialize
EGE_INTERNAL _boolean EGE_Initialize() {
	OUTPUT_DEBUG_STRING(L"Initializing EGE ... \n");

	// Initialize memory
	if (Memory::GetInstance().Initialize() == _false) {
		OUTPUT_DEBUG_STRING(L"Initialize EGE-Memory failed \n");
		return _false;
	}

	// Initialize platform
	if (Platform::Initialize() == _false) {
		OUTPUT_DEBUG_STRING(L"Initialize EGE-Platform failed \n");
		return _false;
	}

	// Initialize thread
	if (Thread::Initialize() == _false) {
		OUTPUT_DEBUG_STRING(L"Initialize EGE-Thread failed \n");
		return _false;
	}

	// Initialize factory
	if (GetInterfaceFactory()->Initialize() == _false)
		return _false;

	// Create GC collector
	gGarbageCollector = new GarbageCollector();

#if _ENABLE_CAPTURE_STD_STREAM == 1
	// Capture standard C stream
	sstdTraceStreamBuf = new EGE::stdTraceStreamBuf(1 KB);
	sstdErrorStreamBuf = new EGE::stdErrorStreamBuf(1 KB);
	sstdTraceStreamPipe = new EGE::stdTraceStreamPipe();
	sstdErrorStreamPipe = new EGE::stdErrorStreamPipe();
	sstdCapture = new stdCapture(sstdTraceStreamBuf, sstdErrorStreamBuf);
#endif

	// Create module manager
	gModuleManager = new ModuleManager();

	// Initialize freetype2 library
	if (FontFaceFreeType2Lib::GetInstance().Initialize() == _false) {
		OUTPUT_DEBUG_STRING(L"Initialize EGE-FontFaceFreeType2 library failed \n");
		return _false;
	}

	// Initialize XML
	if (XMLFile::Initialize() == _false) {
		OUTPUT_DEBUG_STRING(L"Initialize EGE-XMLFile failed \n");
		return _false;
	}

	// Initialize JSON
	if (JSONFile::Initialize() == _false) {
		OUTPUT_DEBUG_STRING(L"Initialize EGE-JSONFile failed \n");
		return _false;
	}

	// Initialize 7Z
	if (SZFile::Initialize() == _false) {
		OUTPUT_DEBUG_STRING(L"Initialize EGE-7ZFile failed \n");
		return _false;
	}

	// Initialize platform
	if (GetPlatform()->Initialize() == _false) {
		OUTPUT_DEBUG_STRING(L"Initialize platform failed \n");
		return _false;
	}

	OUTPUT_DEBUG_STRING(L"Initialized EGE done \n");

	return _true;
}

#undef EGE_Tick
EGE_INTERNAL _void EGE_Tick(_dword limited_elapse, _dword elapse) {
	GetModuleManager()->Tick(limited_elapse, elapse);
	GetModuleManager()->FrameTick(++gFrameNumber);
}

#undef EGE_Finalize
EGE_INTERNAL _void EGE_Finalize() {
	OUTPUT_DEBUG_STRING(L"Finalizing EGE ... \n");

	// Prepare the frame number
	gFrameNumber = 0;

	// Finalize managers
	GetControllerManager()->Finalize();

	// Cleanup GC collector and disable it
	GetGarbageCollector()->Cleanup(-1);
	GetGarbageCollector()->Enable(_false);

	// Release module manager
	if (gModuleManager != &NullEngine::GetInstance().GetModuleManager()) {
		EGE_RELEASE(gModuleManager);
		gModuleManager = &NullEngine::GetInstance().GetModuleManager();
	}

#if _ENABLE_CAPTURE_STD_STREAM == 1
	// Release standard C stream captures
	OUTPUT_DEBUG_STRING(L"Finalizing EGE's std stream capture ... \n");
	EGE_DELETE(sstdCapture);
	EGE_DELETE(sstdTraceStreamBuf);
	EGE_DELETE(sstdErrorStreamBuf);
	EGE_DELETE(sstdTraceStreamPipe);
	EGE_DELETE(sstdErrorStreamPipe);
	OUTPUT_DEBUG_STRING(L"Finalizing EGE's std stream capture OK \n");
#endif

	// Clear delegate application
	EGE_RELEASE(gAppDelegate);

	// Clear the main viewbased application
	SetMainViewBasedApp(_null);

	// Finalize platform
	GetPlatform()->Finalize();

	// Finalize libraries
	XMLFile::Finalize();
	JSONFile::Finalize();
	FontFaceFreeType2Lib::GetInstance().Finalize();
	SZFile::Finalize();

	// Finalize interface
	GetInterfaceFactory()->Finalize();

	// Clear string table
	StringTable* string_table = (StringTable*)GetStringTable();
	string_table->ClearAllStrings();

	// Release GC collector
	EGE_RELEASE(gGarbageCollector);

	OUTPUT_DEBUG_STRING(L"Finalize EGE-Thread ... \n");
	Thread::Finalize();
	OUTPUT_DEBUG_STRING(L"Finalize EGE-Thread done \n");

	OUTPUT_DEBUG_STRING(L"Finalize EGE-Platform ... \n");
	Platform::Finalize();
	OUTPUT_DEBUG_STRING(L"Finalize EGE-Platform done \n");

#ifdef _PLATFORM_WINDOWS_
	// Shutdown the google-protocol library
	OUTPUT_DEBUG_STRING(L"Global-Finalize google-protobuf ... \n");
	google::protobuf::ShutdownProtobufLibrary();
	OUTPUT_DEBUG_STRING(L"Global-Finalize google-protobuf done \n");

	// Dump the memory leak
	OUTPUT_DEBUG_STRING(L"Dump memory leak ... \n");
	Memory::GetInstance().DumpLeakInfo();
	OUTPUT_DEBUG_STRING(L"Dump memory leak done \n");

	OUTPUT_DEBUG_STRING(L"Finalize EGE-Memory ... \n");
	Memory::GetInstance().Finalize();
	OUTPUT_DEBUG_STRING(L"Finalize EGE-Memory done \n");
#endif

	OUTPUT_DEBUG_STRING(L"Finalized EGE done \n");
}
