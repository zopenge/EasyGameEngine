#pragma once

namespace EGE {

// Common Interface
REF_OBJECT_DECL(IArchive);
REF_OBJECT_DECL(ICodec);
REF_OBJECT_DECL(IConnection);
REF_OBJECT_DECL(ILogger);
REF_OBJECT_DECL(IObject);
REF_OBJECT_DECL(IObservable);
REF_OBJECT_DECL(IObserver);
REF_OBJECT_DECL(IPlayer);
REF_OBJECT_DECL(IResourceObject);
REF_OBJECT_DECL(ITask);

// Allocator Interface
REF_OBJECT_DECL(IAllocator);
REF_OBJECT_DECL(IStackAllocator);

// Animation Interface
REF_OBJECT_DECL(IAnimationClip);
REF_OBJECT_DECL(IAnimationMixer);
REF_OBJECT_DECL(IAnimationPlayer);
REF_OBJECT_DECL(IAnimationTracker);

// Application Interface
REF_OBJECT_DECL(IAppDelegate);
REF_OBJECT_DECL(IApplication);
REF_OBJECT_DECL(IViewBasedApplication);

// Buffer Interface
REF_OBJECT_DECL(IBuffer);
REF_OBJECT_DECL(ICacheBuffer);

// FileParser Interface
REF_OBJECT_DECL(ICompressedTexFile);
REF_OBJECT_DECL(IASTCFile);
REF_OBJECT_DECL(IDDSFile);
REF_OBJECT_DECL(IKTXFile);
REF_OBJECT_DECL(IPVRTCFile);
REF_OBJECT_DECL(IFNTFile);
REF_OBJECT_DECL(IImageFile);
REF_OBJECT_DECL(ISoundFile);
REF_OBJECT_DECL(ITXTFile);
REF_OBJECT_DECL(IZIPFile);
REF_OBJECT_DECL(IManifestFile);
REF_OBJECT_DECL(IMarkupLangFile);

// Font Interface
REF_OBJECT_DECL(IFontFace);

// Layout Interface
REF_OBJECT_DECL(IFiller);
REF_OBJECT_DECL(ILayouter);

// Module Interface
REF_OBJECT_DECL(IModule);
REF_OBJECT_DECL(IModuleManager);

// Parser Interface
REF_OBJECT_DECL(IRegularExpression);
REF_OBJECT_DECL(IFormula);
REF_OBJECT_DECL(ICommandLineParser);

// Stream Interface
REF_OBJECT_DECL(IStream);
REF_OBJECT_DECL(IStreamReader);
REF_OBJECT_DECL(IStreamWriter);
REF_OBJECT_DECL(IBitStreamReader);
REF_OBJECT_DECL(IBitStreamWriter);
REF_OBJECT_DECL(IFileStreamReader);
REF_OBJECT_DECL(IFileStreamWriter);
REF_OBJECT_DECL(IStreamProcessorNotifier);
REF_OBJECT_DECL(IStreamProcessor);

// Thread Interface
REF_OBJECT_DECL(IThreadPool);
REF_OBJECT_DECL(IThreadTask);

// Platform Interface
REF_OBJECT_DECL(IProcessDebugger);
REF_OBJECT_DECL(INetwork);
REF_OBJECT_DECL(IPlatform);
REF_OBJECT_DECL(IWinPlatform);
REF_OBJECT_DECL(IIOSPlatform);
REF_OBJECT_DECL(IAndroidPlatform);

// Interface Factory
REF_OBJECT_DECL(IInterfaceFactory);

} // namespace EGE

//----------------------------------------------------------------------------
// Export Interface Declaration
//----------------------------------------------------------------------------

// The platform function declaration for engine
#define PLATFORM_FUNC_DECL(Type, Platform, Name, ParameterTypesAndNames) \
	EGE_EXTERNAL Type Get##Platform##Name ParameterTypesAndNames;        \
	typedef Type(*Platform##_##Name##Func) ParameterTypesAndNames;       \
	static Platform##_##Name##Func Get##Name = Get##Platform##Name;

// The Platform Interface Declarations
#define PLATFORM_INTERFACE_DECL(x) \
	PLATFORM_FUNC_DECL(EGE::I##x##Platform*, x, Platform, ())

// Platform OS Interface declarations
#if defined _PLATFORM_WINDOWS_
PLATFORM_INTERFACE_DECL(Win)
#elif defined _PLATFORM_IOS_
PLATFORM_INTERFACE_DECL(IOS)
#elif defined _PLATFORM_ANDROID_
PLATFORM_INTERFACE_DECL(Android)
#endif

#undef PLATFORM_FUNC_DECL

// The main global interfaces
DEFINE_IMPORT_FUNC(EGE::_handle, GetMainWindowHandle, ())
DEFINE_IMPORT_FUNC(EGE::IViewBasedApp*, GetMainViewBasedApp, ())
DEFINE_IMPORT_FUNC(EGE::IAppDelegate*, GetAppDelegate, ())
DEFINE_IMPORT_FUNC(EGE::IModuleManager*, GetModuleManager, ())
DEFINE_IMPORT_FUNC(EGE::IArchive*, GetWorkingArchive, ())
DEFINE_IMPORT_FUNC(EGE::IInterfaceFactory*, GetInterfaceFactory, ())

// Engine Basic Files
#include "Interface/Engine/EngineConst.h"
#include "Interface/Engine/EngineStruct.h"

// Common Interface Files
#include "Interface/Engine/ICodec.h"
#include "Interface/Engine/IConnection.h"
#include "Interface/Engine/ILogger.h"
#include "Interface/Engine/IObject.h"
#include "Interface/Engine/IObservable.h"
#include "Interface/Engine/IObserver.h"
#include "Interface/Engine/IPlayer.h"
#include "Interface/Engine/IResourceObject.h"
#include "Interface/Engine/ITask.h"

// Allocator Interface Files
#include "Interface/Engine/Allocator/IAllocator.h"
#include "Interface/Engine/Allocator/IStackAllocator.h"

// Animation Interface Files
#include "Interface/Engine/Animation/IAnimationClip.h"
#include "Interface/Engine/Animation/IAnimationMixer.h"
#include "Interface/Engine/Animation/IAnimationPlayer.h"
#include "Interface/Engine/Animation/IAnimationTrack.h"

// Application Interface Files
#include "Interface/Engine/Application/IAppDelegate.h"
#include "Interface/Engine/Application/IApplication.h"
#include "Interface/Engine/Application/IViewBasedApplication.h"

// Buffer Interface Files
#include "Interface/Engine/Buffer/IBuffer.h"
#include "Interface/Engine/Buffer/ICacheBuffer.h"

// FileParser Interface Files
#include "Interface/Engine/FileParser/IASTCFile.h"
#include "Interface/Engine/FileParser/ICSVFile.h"
#include "Interface/Engine/FileParser/ICompressedTexFile.h"
#include "Interface/Engine/FileParser/IDDSFile.h"
#include "Interface/Engine/FileParser/IFNTFile.h"
#include "Interface/Engine/FileParser/IImageFile.h"
#include "Interface/Engine/FileParser/IKTXFile.h"
#include "Interface/Engine/FileParser/IManifestFile.h"
#include "Interface/Engine/FileParser/IMarkupLangFile.h"
#include "Interface/Engine/FileParser/IPVRTCFile.h"
#include "Interface/Engine/FileParser/ISoundFile.h"
#include "Interface/Engine/FileParser/ITXTFile.h"
#include "Interface/Engine/FileParser/IZIPFile.h"

// Font Interface Files
#include "Interface/Engine/Font/IFontFace.h"

// Layout Interface Files
#include "Interface/Engine/Layout/IFiller.h"
#include "Interface/Engine/Layout/ILayouter.h"

// Module Interface Files
#include "Interface/Engine/Module/IModule.h"
#include "Interface/Engine/Module/IModuleManager.h"

// Parser Interface Files
#include "Interface/Engine/Parser/ICommandLineParser.h"
#include "Interface/Engine/Parser/IFormula.h"
#include "Interface/Engine/Parser/IRegularExpression.h"

// Stream Interface Files
#include "Interface/Engine/Stream/IBitStreamReader.h"
#include "Interface/Engine/Stream/IBitStreamWriter.h"
#include "Interface/Engine/Stream/IFileStreamReader.h"
#include "Interface/Engine/Stream/IFileStreamWriter.h"
#include "Interface/Engine/Stream/IStream.h"
#include "Interface/Engine/Stream/IStreamProcessor.h"
#include "Interface/Engine/Stream/IStreamReader.h"
#include "Interface/Engine/Stream/IStreamWriter.h"

// Platform Interface Files
#include "Interface/Engine/Thread/IThreadPool.h"
#include "Interface/Engine/Thread/IThreadTask.h"

// Platform Interface Files
#include "Interface/Engine/Platform/IPlatform.h"
#include "Interface/Engine/Platform/Kernel/IProcessDebugger.h"
#include "Interface/Engine/Platform/Network/INetwork.h"
#if defined _PLATFORM_WINDOWS_
#	include "Interface/Engine/Platform/IWinPlatform.h"
#elif defined _PLATFORM_IOS_
#	include "Interface/Engine/Platform/IIOSPlatform.h"
#elif defined _PLATFORM_ANDROID_
#	include "Interface/Engine/Platform/IAndroidPlatform.h"
#endif

} // namespace EGE