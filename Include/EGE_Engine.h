#pragma once

namespace EGE {

// Base Interface
REF_OBJECT_DECL(IObject);
REF_OBJECT_DECL(IInvoker);
REF_OBJECT_DECL(IGarbageCollector);
REF_OBJECT_DECL(IObserver);
REF_OBJECT_DECL(IObservable);
REF_OBJECT_DECL(IConnection);
REF_OBJECT_DECL(ITask);
REF_OBJECT_DECL(IEventHooker);
REF_OBJECT_DECL(IModule);
REF_OBJECT_DECL(IModuleManager);

// File Interface
REF_OBJECT_DECL(IFileWriter);
REF_OBJECT_DECL(IFileCopier);

// Allocator Interface
REF_OBJECT_DECL(IAllocator);
REF_OBJECT_DECL(IStackAllocator);
REF_OBJECT_DECL(IRingAllocator);
REF_OBJECT_DECL(IRangeAllocator);
REF_OBJECT_DECL(ILinearAllocator);
REF_OBJECT_DECL(IBufferAllocator);
REF_OBJECT_DECL(IOffsetAllocator);

// Application Interface
REF_OBJECT_DECL(IAppDelegate);
REF_OBJECT_DECL(IApplication);
REF_OBJECT_DECL(IConsoleApp);
REF_OBJECT_DECL(IViewBasedApp);

// Compression Interface
REF_OBJECT_DECL(ICompressionEncoder);
REF_OBJECT_DECL(ICompressionDecoder);

// Decoder Interface
REF_OBJECT_DECL(IDecoder);
REF_OBJECT_DECL(IMediaDecoder);
REF_OBJECT_DECL(IAudioDecoder);

// Encryption Interface
REF_OBJECT_DECL(ICrypto);
REF_OBJECT_DECL(IEncryptor);
REF_OBJECT_DECL(IDecryptor);

// Recorder Interface
REF_OBJECT_DECL(IActionRecord);
REF_OBJECT_DECL(IActionRecorder);
REF_OBJECT_DECL(IInputRecordTrace);
REF_OBJECT_DECL(IInputRecorder);
REF_OBJECT_DECL(IOperationRecordPerformer);
REF_OBJECT_DECL(IOperationRecorder);

// FileParser Interface
REF_OBJECT_DECL(IBaseFile);
REF_OBJECT_DECL(IImageFile);
REF_OBJECT_DECL(IBMPFile);
REF_OBJECT_DECL(IDDSFile);
REF_OBJECT_DECL(IJPGFile);
REF_OBJECT_DECL(IGIFFile);
REF_OBJECT_DECL(IPNGFile);
REF_OBJECT_DECL(IPSDFile);
REF_OBJECT_DECL(ITGAFile);
REF_OBJECT_DECL(ICompressedTexFile);
REF_OBJECT_DECL(IASTCFile);
REF_OBJECT_DECL(IPVRTexFile);
REF_OBJECT_DECL(IKTXFile);
REF_OBJECT_DECL(IWEBPFile);
REF_OBJECT_DECL(IWEBMFile);
REF_OBJECT_DECL(IOGGFile);
REF_OBJECT_DECL(IWAVFile);
REF_OBJECT_DECL(IFLACFile);
REF_OBJECT_DECL(IMIDIFile);
REF_OBJECT_DECL(IManifestDir);
REF_OBJECT_DECL(IManifestWalker);
REF_OBJECT_DECL(IManifestFile);
REF_OBJECT_DECL(IMediaFileBlockEntry);
REF_OBJECT_DECL(IMediaFileTrack);
REF_OBJECT_DECL(IMediaFileVideoTrack);
REF_OBJECT_DECL(IMediaFileAudioTrack);
REF_OBJECT_DECL(IMediaFileNotifier);
REF_OBJECT_DECL(IMediaFile);
REF_OBJECT_DECL(IStreamingPCMFile);
REF_OBJECT_DECL(ISoundFile);
REF_OBJECT_DECL(ISoundFileWriter);
REF_OBJECT_DECL(IZIPFile);
REF_OBJECT_DECL(IMarkupLangElementIterator);
REF_OBJECT_DECL(IMarkupLangFile);
REF_OBJECT_DECL(IHTMLFile);
REF_OBJECT_DECL(IGeometryMeshChunk);
REF_OBJECT_DECL(IGeometryFile);
REF_OBJECT_DECL(ICSVFile);
REF_OBJECT_DECL(IFNTFile);

// Math Interface
REF_OBJECT_DECL(IInterpolator);
REF_OBJECT_DECL(IMD5ChecksumBuilder);
REF_OBJECT_DECL(IProjectileObject);

// Parser Interface
REF_OBJECT_DECL(IRegularExpression);
REF_OBJECT_DECL(ICommandLineParser);

// Platform Interface
REF_OBJECT_DECL(IProcessDebugger);
REF_OBJECT_DECL(IRegistry);
REF_OBJECT_DECL(IShell);
REF_OBJECT_DECL(IKeychain);
REF_OBJECT_DECL(IBluetoothSocket);
REF_OBJECT_DECL(IBluetoothServerSocket);
REF_OBJECT_DECL(IBluetoothDevice);
REF_OBJECT_DECL(IBluetoothAdapterNotifier);
REF_OBJECT_DECL(IBluetoothAdapter);
REF_OBJECT_DECL(INetFirewall);
REF_OBJECT_DECL(INet);
REF_OBJECT_DECL(IMenu);
REF_OBJECT_DECL(IWebViewNotifier);
REF_OBJECT_DECL(IWebView);
REF_OBJECT_DECL(IEditBox);
REF_OBJECT_DECL(IMessageBoxNotifier);
REF_OBJECT_DECL(IMessageBox);
REF_OBJECT_DECL(ISensorManager);
REF_OBJECT_DECL(IJoystickNotifier);
REF_OBJECT_DECL(IJoystick);
REF_OBJECT_DECL(IControllerManager);
REF_OBJECT_DECL(IPlatform);
REF_OBJECT_DECL(IWinPlatform);
REF_OBJECT_DECL(IIOSPlatform);
REF_OBJECT_DECL(IJ2CArray);
REF_OBJECT_DECL(IC2JArray);
REF_OBJECT_DECL(IJ2CString);
REF_OBJECT_DECL(IC2JString);
REF_OBJECT_DECL(IC2JStringMap);
REF_OBJECT_DECL(IAndroidPlatform);
REF_OBJECT_DECL(IChromePlatform);

// Serialization Interface
REF_OBJECT_DECL(ISerializable);
REF_OBJECT_DECL(ISerializableNode);
REF_OBJECT_DECL(ISerializableNodeWalker);

// Stream Interface
REF_OBJECT_DECL(IStream);
REF_OBJECT_DECL(IStreamReader);
REF_OBJECT_DECL(IStreamWriter);
REF_OBJECT_DECL(IFileStreamReader);
REF_OBJECT_DECL(IFileStreamWriter);
REF_OBJECT_DECL(IStreamProcessorNotifier);
REF_OBJECT_DECL(IStreamProcessor);

// Interface
REF_OBJECT_DECL(ICacheBufferNotifier);
REF_OBJECT_DECL(ICacheBuffer);

// Archive Interface
REF_OBJECT_DECL(IArchive);

// Thread Interface
REF_OBJECT_DECL(IThreadTask);
REF_OBJECT_DECL(IThreadTaskSet);
REF_OBJECT_DECL(IThreadPool);

// Transaction Interface
REF_OBJECT_DECL(ITransaction);
REF_OBJECT_DECL(ITransactionManager);

// Font Interface
REF_OBJECT_DECL(IFontFace);

// Image Interface
REF_OBJECT_DECL(IImageFiller);
REF_OBJECT_DECL(IImageProcessor);

// StringTable Interface
REF_OBJECT_DECL(IStringTable);

// ProtoBuf Interface
REF_OBJECT_DECL(IProtoBufSender);
REF_OBJECT_DECL(IProtoBufMessageProcessor);
REF_OBJECT_DECL(IProtoBufProcessor);

// Properties Interface
REF_OBJECT_DECL(IProperties);

// Layout Interface
REF_OBJECT_DECL(IAligner);

// Logger Interface
REF_OBJECT_DECL(ILogger);

// Manifest Interface
REF_OBJECT_DECL(IManifestFileManager);

// Resource Interface
REF_OBJECT_DECL(IResObject);
REF_OBJECT_DECL(IResLoaderFactory);
REF_OBJECT_DECL(IResLoader);

// Interface Factory
REF_OBJECT_DECL(IInterfaceFactory);

} // namespace EGE

//----------------------------------------------------------------------------
// Helpful Macros
//----------------------------------------------------------------------------

// Get string object from string table
#define G_STROBJ(x) GetStringTable()->GetRefString(x)
#define G_STROBJ_STR(x) G_STROBJ(x).Str()

// The static string object variable from string table
#define STATIC_ASTROBJ(x) static AStringObj a_##x##_obj = GetStringTable()->GetRefString(AStringPtr(#x))
#define STATIC_USTROBJ(x) static UStringObj u_##x##_obj = GetStringTable()->GetRefString(UStringPtr(#x))
#define STATIC_WSTROBJ(x) static WStringObj w_##x##_obj = GetStringTable()->GetRefString(_WIDEN(#x))
#define STATIC_ASTROBJ_V(x, value) static AStringObj a_##x##_obj = GetStringTable()->GetRefString(value)
#define STATIC_USTROBJ_V(x, value) static UStringObj u_##x##_obj = GetStringTable()->GetRefString(value)
#define STATIC_WSTROBJ_V(x, value) static WStringObj w_##x##_obj = GetStringTable()->GetRefString(value)
#define ASTROBJ(x) a_##x##_obj
#define USTROBJ(x) u_##x##_obj
#define WSTROBJ(x) w_##x##_obj

//----------------------------------------------------------------------------
// Export Interface Declaration
//----------------------------------------------------------------------------

// The platform function declaration for engine
#define ENGINE_PLATFORM_FUNC_DECL(Type, Platform, Name, ParameterTypesAndNames) \
	EGE_EXTERNAL Type Get##Platform##Name ParameterTypesAndNames;               \
	typedef Type(*Platform##_##Name##Func) ParameterTypesAndNames;              \
	static Platform##_##Name##Func Get##Name = Get##Platform##Name;

// The Platform Interface Declarations
#define PLATFORM_INTERFACE_DECL(x)                                              \
	ENGINE_PLATFORM_FUNC_DECL(EGE::I##x##Platform*, x, Platform, ())            \
	ENGINE_PLATFORM_FUNC_DECL(EGE::IBluetoothAdapter*, x, BluetoothAdapter, ()) \
	ENGINE_PLATFORM_FUNC_DECL(EGE::INet*, x, Net, ())                           \
	ENGINE_PLATFORM_FUNC_DECL(EGE::ISensorManager*, x, SensorManager, ())       \
	ENGINE_PLATFORM_FUNC_DECL(EGE::IControllerManager*, x, ControllerManager, ())

// Platform OS Interface declarations
#if defined _PLATFORM_WINDOWS_
PLATFORM_INTERFACE_DECL(Win)
#elif defined _PLATFORM_IOS_
PLATFORM_INTERFACE_DECL(IOS)
#elif defined _PLATFORM_OSX_
PLATFORM_INTERFACE_DECL(OSX)
#elif defined _PLATFORM_ANDROID_
PLATFORM_INTERFACE_DECL(Android)
#elif defined _PLATFORM_CHROME_
PLATFORM_INTERFACE_DECL(Chrome)
#endif

#undef ENGINE_PLATFORM_FUNC_DECL

// Get operations
DEFINE_IMPORT_FUNC(EGE::_handle, GetMainWindowHandle, ())
DEFINE_IMPORT_FUNC(EGE::IViewBasedApp*, GetMainViewBasedApp, ())
DEFINE_IMPORT_FUNC(EGE::IAppDelegate*, GetAppDelegate, ())
DEFINE_IMPORT_FUNC(EGE::IModuleManager*, GetModuleManager, ())
DEFINE_IMPORT_FUNC(EGE::IGarbageCollector*, GetGarbageCollector, ())
DEFINE_IMPORT_FUNC(EGE::IImageProcessor*, GetImageProcessor, ())
DEFINE_IMPORT_FUNC(EGE::IStringTable*, GetStringTable, ())
DEFINE_IMPORT_FUNC(EGE::IArchive*, GetWorkingArchive, ())
DEFINE_IMPORT_FUNC(EGE::IInterfaceFactory*, GetInterfaceFactory, ())

// Set operations
DEFINE_IMPORT_FUNC(EGE::_void, SetMainWindowHandle, (EGE::_handle handle))
DEFINE_IMPORT_FUNC(EGE::_void, SetMainViewBasedApp, (EGE::IViewBasedApp * app))

// Engine Global Initialize/Finalize
DEFINE_IMPORT_FUNC(EGE::_boolean, EGE_ResetResources, ())
DEFINE_IMPORT_FUNC(EGE::_void, EGE_UnloadResources, ())
DEFINE_IMPORT_FUNC(EGE::_boolean, EGE_Initialize, ())
DEFINE_IMPORT_FUNC(EGE::_void, EGE_Tick, (EGE::_dword limited_elapse, EGE::_dword elapse))
DEFINE_IMPORT_FUNC(EGE::_void, EGE_Finalize, ())

// Engine Common Files
#include "Interface/Engine/StringTable/StringObj.h"

// Engine global files
#include "Interface/Engine/EngineEvents.h"
#include "Interface/Engine/EngineGlobals.h"
using namespace EGE::EngineEvents;

// Base Template Interface Files
#include "Interface/Engine/ITColorObject.h"
#include "Interface/Engine/ITEnable.h"
#include "Interface/Engine/ITFlagsObject.h"
#include "Interface/Engine/ITIterator.h"
#include "Interface/Engine/ITNameObject.h"
#include "Interface/Engine/ITObjectTree.h"
#include "Interface/Engine/ITPowerable.h"
#include "Interface/Engine/ITPriorityObject.h"
#include "Interface/Engine/ITScrollableObject.h"
#include "Interface/Engine/ITShowableObject.h"
#include "Interface/Engine/ITTagNameObject.h"
#include "Interface/Engine/ITUserDataObject.h"
#include "Interface/Engine/ITVersionable.h"

// Base Interface Files
#include "Interface/Engine/IConnection.h"
#include "Interface/Engine/IEventHooker.h"
#include "Interface/Engine/IGarbageCollector.h"
#include "Interface/Engine/IInvoker.h"
#include "Interface/Engine/IMeasurableObject.h"
#include "Interface/Engine/IModule.h"
#include "Interface/Engine/IModuleManager.h"
#include "Interface/Engine/IObject.h"
#include "Interface/Engine/IObservable.h"
#include "Interface/Engine/IObserver.h"
#include "Interface/Engine/ITask.h"

// Common Interface Files
#include "Interface/Engine/Allocator/IAllocator.h"
#include "Interface/Engine/Allocator/IBufferAllocator.h"
#include "Interface/Engine/Allocator/ILinearAllocator.h"
#include "Interface/Engine/Allocator/IOffsetAllocator.h"
#include "Interface/Engine/Allocator/IRangeAllocator.h"
#include "Interface/Engine/Allocator/IRingAllocator.h"
#include "Interface/Engine/Allocator/IStackAllocator.h"
#include "Interface/Engine/Animation/IAnimationController.h"
#include "Interface/Engine/Animation/IAnimationKeyFrames.h"
#include "Interface/Engine/Animation/IAnimationPlayer.h"
#include "Interface/Engine/Animation/IAnimationTrack.h"
#include "Interface/Engine/Application/IAppDelegate.h"
#include "Interface/Engine/Application/IApplication.h"
#include "Interface/Engine/Application/IConsoleApp.h"
#include "Interface/Engine/Application/IViewBasedApp.h"
#include "Interface/Engine/Archive/IArchive.h"
#include "Interface/Engine/Buffer/ICacheBuffer.h"
#include "Interface/Engine/Compression/ICompressionDecoder.h"
#include "Interface/Engine/Compression/ICompressionEncoder.h"
#include "Interface/Engine/Decoder/IAudioDecoder.h"
#include "Interface/Engine/Decoder/IDecoder.h"
#include "Interface/Engine/Decoder/IMediaDecoder.h"
#include "Interface/Engine/Encryption/ICrypto.h"
#include "Interface/Engine/Encryption/IDecryptor.h"
#include "Interface/Engine/Encryption/IEncryptor.h"
#include "Interface/Engine/File/IFileCopier.h"
#include "Interface/Engine/File/IFileWriter.h"
#include "Interface/Engine/FileParser/IASTCFile.h"
#include "Interface/Engine/FileParser/IBMPFile.h"
#include "Interface/Engine/FileParser/IBaseFile.h"
#include "Interface/Engine/FileParser/ICSVFile.h"
#include "Interface/Engine/FileParser/ICompressedTexFile.h"
#include "Interface/Engine/FileParser/IDDSFile.h"
#include "Interface/Engine/FileParser/IFLACFile.h"
#include "Interface/Engine/FileParser/IFNTFile.h"
#include "Interface/Engine/FileParser/IGIFFile.h"
#include "Interface/Engine/FileParser/IGeometryFile.h"
#include "Interface/Engine/FileParser/IHTMLFile.h"
#include "Interface/Engine/FileParser/IImageFile.h"
#include "Interface/Engine/FileParser/IJPGFile.h"
#include "Interface/Engine/FileParser/IKTXFile.h"
#include "Interface/Engine/FileParser/IMIDIFile.h"
#include "Interface/Engine/FileParser/IManifestFile.h"
#include "Interface/Engine/FileParser/IMarkupLangFile.h"
#include "Interface/Engine/FileParser/IMediaFile.h"
#include "Interface/Engine/FileParser/IOGGFile.h"
#include "Interface/Engine/FileParser/IPKMFile.h"
#include "Interface/Engine/FileParser/IPNGFile.h"
#include "Interface/Engine/FileParser/IPSDFile.h"
#include "Interface/Engine/FileParser/IPVRTexFile.h"
#include "Interface/Engine/FileParser/ISoundFile.h"
#include "Interface/Engine/FileParser/ISpeexFile.h"
#include "Interface/Engine/FileParser/IStreamingPCMFile.h"
#include "Interface/Engine/FileParser/ITGAFile.h"
#include "Interface/Engine/FileParser/IWAVFile.h"
#include "Interface/Engine/FileParser/IWEBMFile.h"
#include "Interface/Engine/FileParser/IWEBPFile.h"
#include "Interface/Engine/FileParser/IZIPFile.h"
#include "Interface/Engine/Font/IFontFace.h"
#include "Interface/Engine/IInterfaceFactory.h"
#include "Interface/Engine/Image/IImageFiller.h"
#include "Interface/Engine/Image/IImageProcessor.h"
#include "Interface/Engine/Layout/IAligner.h"
#include "Interface/Engine/Logger/ILogger.h"
#include "Interface/Engine/Manifest/IManifestFileManager.h"
#include "Interface/Engine/Math/IInterpolator.h"
#include "Interface/Engine/Math/IMD5ChecksumBuilder.h"
#include "Interface/Engine/Math/IProjectileObject.h"
#include "Interface/Engine/Parser/ICommandLineParser.h"
#include "Interface/Engine/Parser/IRegularExpression.h"
#include "Interface/Engine/Platform/Controller/IJoystick.h"
#include "Interface/Engine/Platform/Kernel/IKeychain.h"
#include "Interface/Engine/Platform/Kernel/IProcessDebugger.h"
#include "Interface/Engine/Platform/Kernel/IRegistry.h"
#include "Interface/Engine/Platform/Kernel/IShell.h"
#include "Interface/Engine/Platform/Network/IBluetooth.h"
#include "Interface/Engine/Platform/Network/INet.h"
#include "Interface/Engine/Platform/Network/INetFirewall.h"
#include "Interface/Engine/Platform/SensorManager/ISensorManager.h"
#include "Interface/Engine/Platform/UI/IEditBox.h"
#include "Interface/Engine/Platform/UI/IMenu.h"
#include "Interface/Engine/Platform/UI/IMessageBox.h"
#include "Interface/Engine/Platform/UI/IWebView.h"
#include "Interface/Engine/Properties/IProperties.h"
#include "Interface/Engine/ProtoBuf/IProtoBufProcessor.h"
#include "Interface/Engine/Recorder/IActionRecord.h"
#include "Interface/Engine/Recorder/IActionRecorder.h"
#include "Interface/Engine/Recorder/IInputRecordTrace.h"
#include "Interface/Engine/Recorder/IInputRecorder.h"
#include "Interface/Engine/Recorder/IOperationRecordPerformer.h"
#include "Interface/Engine/Recorder/IOperationRecorder.h"
#include "Interface/Engine/Resource/IResLoader.h"
#include "Interface/Engine/Resource/IResLoaderFactory.h"
#include "Interface/Engine/Resource/IResObject.h"
#include "Interface/Engine/Serialization/ISerializable.h"
#include "Interface/Engine/Serialization/ISerializableNode.h"
#include "Interface/Engine/Serialization/ISerializableNodeWalker.h"
#include "Interface/Engine/Stream/IBitStream.h"
#include "Interface/Engine/Stream/IBitStreamReader.h"
#include "Interface/Engine/Stream/IBitStreamWriter.h"
#include "Interface/Engine/Stream/IFileStream.h"
#include "Interface/Engine/Stream/IFileStreamReader.h"
#include "Interface/Engine/Stream/IFileStreamWriter.h"
#include "Interface/Engine/Stream/IStream.h"
#include "Interface/Engine/Stream/IStreamProcessor.h"
#include "Interface/Engine/Stream/IStreamReader.h"
#include "Interface/Engine/Stream/IStreamWriter.h"
#include "Interface/Engine/StringTable/IStringTable.h"
#include "Interface/Engine/Thread/IThreadPool.h"
#include "Interface/Engine/Thread/IThreadTask.h"
#include "Interface/Engine/Thread/IThreadTaskSet.h"
#include "Interface/Engine/Transaction/ITransaction.h"
#include "Interface/Engine/Transaction/ITransactionManager.h"

// Platform OS Interface Files
#include "Interface/Engine/Platform/IPlatform.h"
#if defined _PLATFORM_WINDOWS_
#	include "Interface/Engine/Platform/IWinPlatform.h"
#elif defined _PLATFORM_IOS_
#	include "Interface/Engine/Platform/IIOSPlatform.h"
#elif defined _PLATFORM_OSX_
#	include "Interface/Engine/Platform/IOSXPlatform.h"
#elif defined _PLATFORM_ANDROID_
#	include "Interface/Engine/Platform/IAndroidPlatform.h"
#elif defined _PLATFORM_CHROME_
#	include "Interface/Engine/Platform/IChromePlatform.h"
#endif

//----------------------------------------------------------------------------
// Typedef Declarations
//----------------------------------------------------------------------------

namespace EGE {

typedef Array<AStringObj> AStringObjArray;
typedef Array<UStringObj> UStringObjArray;
typedef Array<WStringObj> WStringObjArray;

} // namespace EGE

//----------------------------------------------------------------------------
// Interface Template Files
//----------------------------------------------------------------------------

// Base Interface Template Implementation
#define INTERFACE_OBJECT_IMPL(x) EGE::TObject<x>
#define INTERFACE_OBJECT_TREE_IMPL(x, node_interface) EGE::TObjectTree<x, node_interface>
#define INTERFACE_FLAGSOBJECT_IMPL(x) EGE::TFlagsObject<x>
#define INTERFACE_USERDATAOBJECT_IMPL(x) EGE::TUserDataObject<x>
#define INTERFACE_IDOBJECT_IMPL(x) EGE::TIDObject<x>
#define INTERFACE_NAMEOBJECT_IMPL(x) EGE::TNameObject<x>
#define INTERFACE_COLOROBJECT_IMPL(x) EGE::TColorObject<x>
#define INTERFACE_OBSERVABLE_IMPL(x) EGE::TObservable<INTERFACE_OBJECT_IMPL(x)>
#define INTERFACE_OBSERVER_IMPL(x) EGE::TObserver<INTERFACE_OBSERVABLE_IMPL(x)>
#define INTERFACE_TASK_IMPL(x) EGE::TTask<INTERFACE_OBSERVABLE_IMPL(x)>
#define INTERFACE_MODULE_IMPL(x) EGE::TModule<INTERFACE_OBSERVER_IMPL(x)>
#define INTERFACE_STREAMPROCESSOR_IMPL(x) EGE::TStreamProcessor<INTERFACE_OBJECT_IMPL(x)>
#define INTERFACE_CONNECTION_IMPL(x) EGE::TConnection<INTERFACE_OBSERVABLE_IMPL(x)>

// Common Interface Template Implementation
#define INTERFACE_STREAMPROCESSOR_IMPL(x) EGE::TStreamProcessor<INTERFACE_OBJECT_IMPL(x)>
#define INTERFACE_STREAM_IMPL(x) EGE::TStream<INTERFACE_OBJECT_IMPL(x)>
#define INTERFACE_STREAM_READER_IMPL(x) EGE::TStreamReader<INTERFACE_STREAM_IMPL(x)>
#define INTERFACE_STRINGSTREAM_READER_IMPL(x, char_type, encoding) EGE::TStringStream<INTERFACE_STREAM_READER_IMPL(x), char_type, encoding>
#define INTERFACE_FILESTREAM_READER_IMPL(x) EGE::TFileStream<INTERFACE_STREAM_READER_IMPL(x)>
#define INTERFACE_STREAM_WRITER_IMPL(x) EGE::TStreamWriter<INTERFACE_STREAM_IMPL(x)>
#define INTERFACE_FILESTREAM_WRITER_IMPL(x) EGE::TFileStream<INTERFACE_STREAM_WRITER_IMPL(x)>
#define INTERFACE_ARCHIVE_IMPL(x) EGE::TArchive<INTERFACE_OBJECT_IMPL(x)>
#define INTERFACE_BASEFILE_IMPL(x) EGE::TBaseFile<INTERFACE_FLAGSOBJECT_IMPL(x)>
#define INTERFACE_IMAGEFILE_IMPL(x) EGE::TImageFile<INTERFACE_BASEFILE_IMPL(x)>
#define INTERFACE_COMPRESSEDTEXFILE_IMPL(x) EGE::TCompressedTexFile<INTERFACE_IMAGEFILE_IMPL(x)>
#define INTERFACE_SOUNDFILE_IMPL(x) EGE::TSoundFile<INTERFACE_BASEFILE_IMPL(x)>
#define INTERFACE_MEDIAFILE_IMPL(x) EGE::TMediaFile<INTERFACE_BASEFILE_IMPL(x)>
#define INTERFACE_IMAGE_FILLER_IMPL(x) EGE::TImageFiller<INTERFACE_OBJECT_IMPL(x)>
#define INTERFACE_SERIALIZABLE_NODE_IMPL(x) EGE::TSerializableNode<INTERFACE_OBJECT_IMPL(x)>
#define INTERFACE_APPLICATION_IMPL(x) EGE::TApplication<INTERFACE_OBJECT_IMPL(x)>
#define INTERFACE_VIEWBASED_APP_IMPL(x) EGE::TViewBasedApp<INTERFACE_OBJECT_IMPL(x)>
#define INTERFACE_MARKUP_LANG_ATTRIBUTE_IMPL(x) EGE::TMarkupLangAttribute<x>
#define INTERFACE_MARKUP_LANG_ELEMENT_IMPL(x) EGE::TMarkupLangElement<x>
#define INTERFACE_MARKUP_LANG_DECLARATION_IMPL(x) EGE::TMarkupLangDeclaration<x>
#define INTERFACE_RESOBJECT_IMPL(x) EGE::TResObject<x>

// Base Template Files
#include "Interface/Template/TObject.h"

// Serialization Template Files
#include "Interface/Template/Engine/Serialization/TSerializable.h"
#include "Interface/Template/Engine/Serialization/TSerializableNode.h"

// Common Template Files
#include "Interface/Template/Engine/Allocator/TAllocator.h"
#include "Interface/Template/Engine/Animation/TAnimationController.h"
#include "Interface/Template/Engine/Animation/TAnimationKeyFrames.h"
#include "Interface/Template/Engine/Animation/TAnimationPlayer.h"
#include "Interface/Template/Engine/Animation/TAnimationTrack.h"
#include "Interface/Template/Engine/Archive/TArchive.h"
#include "Interface/Template/Engine/Encryption/TCryptor.h"
#include "Interface/Template/Engine/Encryption/TDecryptor.h"
#include "Interface/Template/Engine/Encryption/TEncryptor.h"
#include "Interface/Template/Engine/File/TFileWriter.h"
#include "Interface/Template/Engine/FileParser/TBaseFile.h"
#include "Interface/Template/Engine/FileParser/TCompressedTexFile.h"
#include "Interface/Template/Engine/FileParser/TImageFile.h"
#include "Interface/Template/Engine/FileParser/TMarkupLangAttribute.h"
#include "Interface/Template/Engine/FileParser/TMarkupLangDeclaration.h"
#include "Interface/Template/Engine/FileParser/TMarkupLangElement.h"
#include "Interface/Template/Engine/FileParser/TMediaFile.h"
#include "Interface/Template/Engine/FileParser/TSoundFile.h"
#include "Interface/Template/Engine/FileParser/TSoundFileWriter.h"
#include "Interface/Template/Engine/Image/TImageFiller.h"
#include "Interface/Template/Engine/Logger/TLogger.h"
#include "Interface/Template/Engine/Resource/TResObject.h"
#include "Interface/Template/Engine/Stream/TBitStream.h"
#include "Interface/Template/Engine/Stream/TFileStream.h"
#include "Interface/Template/Engine/Stream/TMemStream.h"
#include "Interface/Template/Engine/Stream/TStream.h"
#include "Interface/Template/Engine/Stream/TStreamProcessor.h"
#include "Interface/Template/Engine/Stream/TStreamReader.h"
#include "Interface/Template/Engine/Stream/TStreamWriter.h"
#include "Interface/Template/Engine/Stream/TStringStream.h"
#include "Interface/Template/TColorObject.h"
#include "Interface/Template/TConnection.h"
#include "Interface/Template/TEnable.h"
#include "Interface/Template/TEventHooker.h"
#include "Interface/Template/TFlagsObject.h"
#include "Interface/Template/TIDObject.h"
#include "Interface/Template/TModule.h"
#include "Interface/Template/TNameObject.h"
#include "Interface/Template/TObjectTree.h"
#include "Interface/Template/TObjectTreeIterator.h"
#include "Interface/Template/TObservable.h"
#include "Interface/Template/TObserver.h"
#include "Interface/Template/TPowerable.h"
#include "Interface/Template/TPriorityObject.h"
#include "Interface/Template/TShowableObject.h"
#include "Interface/Template/TTagNameObject.h"
#include "Interface/Template/TTask.h"
#include "Interface/Template/TUserDataObject.h"
#include "Interface/Template/TVersionable.h"

//----------------------------------------------------------------------------
// Specified function implementation
//----------------------------------------------------------------------------

namespace EGE {

template <>
inline TStringObj<_chara, _ENCODING_ANSI>::TStringObj(const _chara* string) {
	*this = GetStringTable()->GetRefString((AStringPtr)string);
}

template <>
inline TStringObj<_chara, _ENCODING_ANSI>::TStringObj(AStringPtr string) {
	*this = GetStringTable()->GetRefString(string);
}

template <>
inline TStringObj<_chara, _ENCODING_ANSI>::TStringObj(const AStringR& string) {
	*this = GetStringTable()->GetRefString(string);
}

template <>
inline TStringObj<_chara, _ENCODING_UTF8>::TStringObj(UStringPtr string) {
	*this = GetStringTable()->GetRefString(string);
}

template <>
inline TStringObj<_chara, _ENCODING_UTF8>::TStringObj(const UStringR& string) {
	*this = GetStringTable()->GetRefString(string);
}

template <>
inline TStringObj<_charw, _ENCODING_UTF16>::TStringObj(const _charw* string) {
	*this = GetStringTable()->GetRefString((WStringPtr)string);
}

template <>
inline TStringObj<_charw, _ENCODING_UTF16>::TStringObj(WStringPtr string) {
	*this = GetStringTable()->GetRefString(string);
}

template <>
inline TStringObj<_charw, _ENCODING_UTF16>::TStringObj(const WStringR& string) {
	*this = GetStringTable()->GetRefString(string);
}

template <>
inline TStringObj<_chara, _ENCODING_ANSI>& TStringObj<_chara, _ENCODING_ANSI>::operator=(const _chara* string) {
	const AStringObj& string_obj = GetStringTable()->GetRefString(string);

	mID = string_obj.mID;
	mString = string_obj.mString;

	return *this;
}

template <>
inline TStringObj<_chara, _ENCODING_ANSI>& TStringObj<_chara, _ENCODING_ANSI>::operator=(AStringPtr string) {
	const AStringObj& string_obj = GetStringTable()->GetRefString(string);

	mID = string_obj.mID;
	mString = string_obj.mString;

	return *this;
}

template <>
inline TStringObj<_chara, _ENCODING_ANSI>& TStringObj<_chara, _ENCODING_ANSI>::operator=(const AStringR& string) {
	const AStringObj& string_obj = GetStringTable()->GetRefString(string);

	mID = string_obj.mID;
	mString = string_obj.mString;

	return *this;
}

template <>
inline TStringObj<_chara, _ENCODING_UTF8>& TStringObj<_chara, _ENCODING_UTF8>::operator=(UStringPtr string) {
	const UStringObj& string_obj = GetStringTable()->GetRefString(string);

	mID = string_obj.mID;
	mString = string_obj.mString;

	return *this;
}

template <>
inline TStringObj<_chara, _ENCODING_UTF8>& TStringObj<_chara, _ENCODING_UTF8>::operator=(const UStringR& string) {
	const UStringObj& string_obj = GetStringTable()->GetRefString(string);

	mID = string_obj.mID;
	mString = string_obj.mString;

	return *this;
}

template <>
inline TStringObj<_charw, _ENCODING_UTF16>& TStringObj<_charw, _ENCODING_UTF16>::operator=(const _charw* string) {
	const WStringObj& string_obj = GetStringTable()->GetRefString(string);

	mID = string_obj.mID;
	mString = string_obj.mString;

	return *this;
}

template <>
inline TStringObj<_charw, _ENCODING_UTF16>& TStringObj<_charw, _ENCODING_UTF16>::operator=(WStringPtr string) {
	const WStringObj& string_obj = GetStringTable()->GetRefString(string);

	mID = string_obj.mID;
	mString = string_obj.mString;

	return *this;
}

template <>
inline TStringObj<_charw, _ENCODING_UTF16>& TStringObj<_charw, _ENCODING_UTF16>::operator=(const WStringR& string) {
	const WStringObj& string_obj = GetStringTable()->GetRefString(string);

	mID = string_obj.mID;
	mString = string_obj.mString;

	return *this;
}

} // namespace EGE