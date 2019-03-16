//! @file     InterfaceFactory.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// InterfaceFactory
//----------------------------------------------------------------------------

class InterfaceFactory : public TObject< IInterfaceFactory >
{
private:
	typedef Map< OnObjectCreateWithNameCallback, AStringObj > OnObjectCreateWithNameCallbackMap;
	typedef Map< OnObjectCreateArgsWithNameCallback, AStringObj > OnObjectCreationArgsWithNameCallbackMap;

	typedef Map< OnObjectCreateWithIDCallback, _dword > OnObjectCreateWithIDCallbackMap;
	typedef Map< OnObjectCreateArgsWithIDCallback, _dword > OnObjectCreationArgsWithIDCallbackMap;

private:
	//!	The file format get function.
	typedef _FILE_FORMAT (*FileFormatGetFunc)( IStreamReader* stream_reader );
	//!	The file format check function.
	typedef _ubool (*FileFormatCheckFunc)( _FILE_FORMAT file_format );

	//!	The create file function.
	typedef IBaseFile* (*CreateFileFunc)( _FILE_FORMAT file_format, _dword flags );

private:
	OnObjectCreateWithNameCallbackMap		mObjectCreateWithNameFuncs;
	OnObjectCreationArgsWithNameCallbackMap	mObjectCreationArgsWithNameFuncs;

	OnObjectCreateWithIDCallbackMap			mObjectCreateWithIDFuncs;
	OnObjectCreationArgsWithIDCallbackMap	mObjectCreationArgsWithIDFuncs;

private:
	//!	Create image file.
	static IBaseFile* CreateImageFile( _FILE_FORMAT file_format, _dword flags );
	//!	Create sound file.
	static IBaseFile* CreateSoundFile( _FILE_FORMAT file_format, _dword flags );

	//!	Check whether it's XML file format.
	static _ubool IsXMLFileFormat( IStreamReader* stream_reader );

	//!	Get file format.
	static _FILE_FORMAT GetCommonFileFormat( IStreamReader* stream_reader );
	static _FILE_FORMAT GetImageFileFormat( IStreamReader* stream_reader );
	static _FILE_FORMAT GetSoundFileFormat( IStreamReader* stream_reader );

private:
	//!	Parse the stream file.
	template< typename Type, typename InterfaceType >
	PassRefPtr< InterfaceType > ParseStreamFile( IStreamReader* stream_reader, _dword flags = 0 );
	//!	Parse the stream file by auto-detected file format.
	template< typename Type, FileFormatGetFunc _GET_FUNC, FileFormatCheckFunc _CHECK_FUNC, CreateFileFunc _CREATE_FUNC >
	PassRefPtr< Type > ParseStreamFile( _FILE_FORMAT file_format, IStreamReader* stream_reader, _dword flags = 0 );

public:
	InterfaceFactory( );
	virtual ~InterfaceFactory( );

// IInterfaceFactory Interface
public:
	virtual _ubool								Initialize( ) override;
	virtual _void								Finalize( ) override;

	virtual IObject*							CreateObject( const AStringObj& name ) override;
	virtual IObject*							CreateObject( const AStringObj& name, _void* arguments ) override;
	virtual IObject*							CreateObject( _dword id ) override;
	virtual IObject*							CreateObject( _dword id, _void* arguments ) override;
	virtual _void								RegisterObjectCreationFunc( const AStringObj& name, OnObjectCreateWithNameCallback func_pointer ) override;
	virtual _void								RegisterObjectCreationFunc( const AStringObj& name, OnObjectCreateArgsWithNameCallback func_pointer ) override;
	virtual _void								RegisterObjectCreationFunc( _dword id, OnObjectCreateWithIDCallback func_pointer ) override;
	virtual _void								RegisterObjectCreationFunc( _dword id, OnObjectCreateArgsWithIDCallback func_pointer ) override;

	virtual IFileCopierPassRef					CreateFileCopier( ) override;

	virtual IArchivePassRef						CreateFileArchive( WStringPtr path ) override;
	virtual IArchivePassRef						CreateMemArchive( WStringPtr name, IStreamReader* stream_reader, WStringPtr password, _ENCRYPTION manifest_encryption_type, WStringPtr manifest_encryption_key ) override;
	virtual IArchivePassRef						CreatePEResArchive( WStringPtr module_name ) override;

	virtual IStringTablePassRef					CreateStringTable( ) override;

	virtual IActionRecorderPassRef				CreateActionRecorder( ) override;
	virtual IInputRecorderPassRef				CreateInputRecorder( ) override;
	virtual IOperationRecorderPassRef			CreateOperationRecorder( _dword max_buffer_number, IOperationRecordPerformer* performer ) override;

	virtual IFontFacePassRef					CreateFontFace( _FONT_FACE_TYPE type, IStreamReader* stream_reader ) override;
	
	virtual IImageFillerPassRef					CreateImageFiller( _IMAGE_FILLTER_TYPE type, const PointU& size, const PointU& space = PointU::cZeroPoint ) override;

	virtual IRegularExpressionPassRef			CreateRegularExpression( WStringPtr pattern ) override;

	virtual _ubool								BuildMD5CodeFromFile( WStringPtr filename, MD5Code& md5_code ) override;
	virtual _ubool								BuildMD5CodeFromStream( IStreamReader* stream_reader, MD5Code& md5_code ) override;
	virtual MD5Code								BuildMD5CodeFromString( AStringPtr string ) override;
	virtual MD5Code								BuildMD5CodeFromString( WStringPtr string ) override;
	virtual IMD5ChecksumBuilderPassRef			CreateMD5ChecksumBuilder( _dword chunk_size = 640 KB ) override;

	virtual IProjectileObjectPassRef 			CreateProjectileObjectBySpeed( const Vector3& position, const Vector3& direction, const Vector3& target, _float speed, _float height_rate = 1.0f ) override;
	virtual IProjectileObjectPassRef 			CreateProjectileObjectByDuration( const Vector3& position, const Vector3& direction, const Vector3& target, _dword duration, _float height_rate = 1.0f ) override;

	virtual IInterpolatorPassRef				CreateInterpolator( _INTERPOLATOR_TYPE interpolator_type ) override;

	virtual IMeasurableObjectPassRef			CreateMeasurableObj( const Vector2& size ) override;
	virtual IAlignerPassRef						CreateAligner( ) override;

	virtual ICommandLineParserPassRef			CreateCommandLineParser( ) override;
	virtual ICommandLineParserPassRef 			CreateCommandLineParser( AStringPtr cmdline ) override;
	virtual ICommandLineParserPassRef 			CreateCommandLineParser( WStringPtr cmdline ) override;
	virtual ICommandLineParserPassRef 			CreateCommandLineParser( _dword argc, const _chara* argv[] ) override;
	virtual ICommandLineParserPassRef 			CreateCommandLineParser( _dword argc, const _charw* argv[] ) override;
	virtual ICommandLineParserPassRef			CreateCommandLineParser( _dword argc, const _chara* argn[], const _chara* argv[] ) override;
	virtual ICommandLineParserPassRef			CreateCommandLineParser( _dword argc, const _charw* argn[], const _charw* argv[] ) override;

	virtual IPropertiesPassRef					CreateProperties( ) override;

	virtual IProtoBufMessageProcessorPassRef	CreateProtoBufMessageProcessor( ) override;
	virtual IProtoBufProcessorPassRef			CreateProtoBufProcessor( ) override;

	virtual ILoggerPassRef						CreateLogger( ) override;
	virtual ILoggerPassRef						CreateFileLogger( WStringPtr app_name ) override;

	virtual IAllocatorPassRef					CreateStdAllocator( _dword arrange_size = 4 ) override;
	virtual IAllocatorPassRef					CreateMemAllocator( _dword page_size, _dword min_chunk_size = 1 KB, _dword arrange_size = 4 ) override;
	virtual IStackAllocatorPassRef				CreateStackAllocator( _dword size, _dword arrange_size = 4 ) override;
	virtual IRingAllocatorPassRef				CreateRingAllocator( _dword size, _dword arrange_size = 4 ) override;
	virtual ILinearAllocatorPassRef				CreateLinearAllocator( _byte* buffer, _dword size, _dword arrange_size = 4 ) override;
	virtual IRangeAllocatorPassRef				CreateRangeAllocator( _dword size, _dword arrange_size = 4 ) override;
	virtual IBufferAllocatorPassRef				CreateBufferAllocator( _dword size, _dword arrange_size = 4 ) override;
	virtual IOffsetAllocatorPassRef				CreateOffsetAllocator( _dword size, _dword arrange_size = 4 ) override;

	virtual ICacheBufferPassRef					CreateCacheBuffer( _dword buffer_size, _dword cache_size, ICacheBufferNotifier* notifier ) override;

	virtual IStreamReaderPassRef 				CreateMemStreamReader( const _byte* buffer, _dword size, _STREAM_SHARE_MODE share_mode ) override;
	virtual IStreamWriterPassRef				CreateMemStreamWriter( ) override;
	virtual IStreamWriterPassRef 				CreateMemStreamWriter( _dword size ) override;
	virtual IStreamWriterPassRef				CreateMemStreamWriter( _dword size, _dword grow_size ) override;
	virtual IStreamWriterPassRef 				CreateMemStreamWriter( _byte* buffer, _dword size, _STREAM_SHARE_MODE share_mode ) override;

	virtual IStreamReaderPassRef 				CreateBitStreamReader( const _byte* buffer, _dword size, _STREAM_SHARE_MODE share_mode ) override;
	virtual IStreamWriterPassRef 				CreateBitStreamWriter( _dword size ) override;

	virtual IStreamReaderPassRef				CreateAStringStreamReader( AStringPtr string ) override;
	virtual IStreamReaderPassRef				CreateUStringStreamReader( UStringPtr string ) override;
	virtual IStreamReaderPassRef				CreateWStringStreamReader( WStringPtr string ) override;

	virtual IFileStreamReaderPassRef 			CreateFileStreamReader( WStringPtr filename ) override;
	virtual IFileStreamWriterPassRef 			CreateFileStreamWriter( WStringPtr filename ) override;

	virtual IStreamReaderPassRef				CreateSafeStreamReader( IStreamReader* stream_reader ) override;

	virtual IStreamProcessorPassRef				CreateStreamWriterProcessor( ) override;
	virtual IStreamProcessorPassRef				CreateStreamWriterProcessor( const MD5Code& md5_code ) override;

	virtual IThreadPoolPassRef					CreateThreadPool( _dword thread_number, WStringPtr name = L"" ) override;
	virtual IThreadPoolPassRef					CreateSingleThreadPool( ) override;
	virtual ITransactionManagerPassRef			CreateTransactionManager( _dword thread_number, WStringPtr name = L"" ) override;

	virtual IConsoleAppPassRef	 				CreateConsoleApplication( ) override;

	virtual IViewBasedAppPassRef				CreateViewBasedApplication( _void* app_handle ) override;
	virtual IViewBasedAppPassRef				CreateViewBasedApplication( _void* app_handle, const PointU& size ) override;
	virtual IViewBasedAppPassRef 				CreateViewBasedApplication( IViewBasedApp::_CREATION_FLAG flag ) override;

	virtual ISerializableNodePassRef			CreateXMLSerializableNode( ) override;
	virtual ISerializableNodePassRef			CreateXMLSerializableNode( AStringPtr string ) override;
	virtual ISerializableNodePassRef			CreateXMLSerializableNode( UStringPtr string ) override;
	virtual ISerializableNodePassRef			CreateXMLSerializableNode( WStringPtr string ) override;

	virtual ISerializableNodePassRef			CreateJSONSerializableNode( ) override;
	virtual ISerializableNodePassRef			CreateJSONSerializableNode( AStringPtr string ) override;
	virtual ISerializableNodePassRef			CreateJSONSerializableNode( UStringPtr string ) override;
	virtual ISerializableNodePassRef			CreateJSONSerializableNode( WStringPtr string ) override;

	virtual ISerializableNodePassRef			CreateMarkupLangSerializableNode( AStringPtr string ) override;
	virtual ISerializableNodePassRef			CreateMarkupLangSerializableNode( UStringPtr string ) override;
	virtual ISerializableNodePassRef			CreateMarkupLangSerializableNode( WStringPtr string ) override;
	virtual ISerializableNodePassRef			CreateMarkupLangSerializableNode( IStreamReader* stream_reader ) override;
	virtual ISerializableNodePassRef			CreateMarkupLangSerializableNode( IMarkupLangFile* file ) override;
	virtual ISerializableNodePassRef			CreateMarkupLangSerializableNode( IMarkupLangElement* element, IMarkupLangFile* file ) override;

	virtual INetFirewallPassRef					CreateNetFirewall( ) override;
	virtual IShellPassRef						CreateShell( ) override;
	virtual IMenuPassRef						CreateMenu( _ubool popup ) override;
	virtual IProcessDebuggerPassRef				CreateProcessDebugger( ) override;
	virtual IRegistryPassRef					CreateRegistry( IRegistry::_ROOT_KEY root, WStringPtr keyname ) override;

	virtual ICompressionEncoderPassRef 			CreateCompressionEncoder( _COMPRESSION type ) override;
	virtual ICompressionDecoderPassRef 			CreateCompressionDecoder( _COMPRESSION type ) override;
	virtual IStreamReaderPassRef				CompressBuffer( _COMPRESSION type, _dword size, const _byte* buffer ) override;
	virtual IStreamReaderPassRef				DecompressBuffer( _COMPRESSION type, _dword size, const _byte* buffer ) override;

	virtual IAudioDecoderPassRef				CreateOGGDecoder( const SoundVorbisFormatInfo* info ) override;

	virtual IEncryptorPassRef					CreateEncryptor( _ENCRYPTION type, AStringPtr key ) override;
	virtual IDecryptorPassRef					CreateDecryptor( _ENCRYPTION type, AStringPtr key ) override;
	virtual _ubool								EncryptFile( WStringPtr source_filename, WStringPtr target_filename, _ENCRYPTION type, AStringPtr key ) override;
	virtual _ubool								DecryptFile( WStringPtr source_filename, WStringPtr target_filename, _ENCRYPTION type, AStringPtr key ) override;
	virtual IStreamReaderPassRef				EncryptStream( IStreamReader* stream_reader, _ENCRYPTION type, AStringPtr key ) override;
	virtual IStreamReaderPassRef				DecryptStream( IStreamReader* stream_reader, _ENCRYPTION type, AStringPtr key ) override;

	virtual _FILE_FORMAT						GetCommonFileTypeFromStream( IStreamReader* stream_reader ) const override;
	virtual _FILE_FORMAT						GetImageFileTypeFromStream( IStreamReader* stream_reader ) const override;
	virtual _FILE_FORMAT						GetSoundFileTypeFromStream( IStreamReader* stream_reader ) const override;

	virtual IMarkupLangFilePassRef 				CreateXMLFile( ) override;
	virtual IMarkupLangFilePassRef				CreateXMLFile( WStringPtr root_name, _ENCODING encoding = _ENCODING_UTF8, const Version& version = Version::cInitial ) override;
	virtual IMarkupLangFilePassRef				CreateXMLFile( const ISerializableNode* node, _ENCODING encoding = _ENCODING_UTF8, const Version& version = Version::cInitial ) override;
	virtual IMarkupLangFilePassRef				CreateBXMLFile( IMarkupLangFile* markup_file ) override;
	virtual IMarkupLangFilePassRef				CreateJSONFile( ) override;
	virtual IManifestFilePassRef				CreateManifestFile( ) override;
	virtual IGeometryFilePassRef				CreateGeometryFile( ) override;
	virtual IGeometryMeshChunkPassRef			CreateGeometryMeshChunk( _dword vertex_type, const _byte* vb_data, _dword vb_size, const _word* ib_data, _dword ib_size ) override;
	virtual IGeometryMeshChunkPassRef			CreateBoxGeometryMeshChunk( const Vector3& min_vector, const Vector3& max_vector ) override;
	virtual IImageFilePassRef					CreateImageFile( _FILE_FORMAT file_format, _dword width, _dword height, _PIXEL_FORMAT pixelformat, const _void* pixelbuffer = _null ) override;
	virtual ISoundFileWriterPassRef				CreateSoundFileWriter( _FILE_FORMAT file_format ) override;
	virtual IStreamingPCMFilePassRef			CreateStreamingPCMFile( const SoundHeaderInfo& info ) override;
	virtual IZIPFilePassRef						CreateZipFile( WStringPtr filename, WStringPtr password = L"" ) override;
	virtual IZIPFilePassRef						Create7zFile( WStringPtr filename, WStringPtr password = L"" ) override;
	virtual IZIPFilePassRef						CreatePackageFile( WStringPtr filename ) override;

	virtual _ubool								SaveImageFile( _FILE_FORMAT file_format, _PIXEL_FORMAT pixelformat, WStringPtr filename, IImageFile* image ) override;

	virtual IFNTFilePassRef						ParseFNTFile( IStreamReader* stream_reader ) override;
	virtual ICSVFilePassRef						ParseCSVFile( IStreamReader* stream_reader ) override;
	virtual IGeometryFilePassRef				ParseGeometryFile( IStreamReader* stream_reader ) override;
	virtual IMarkupLangFilePassRef				ParseXMLFile( IStreamReader* stream_reader ) override;
	virtual IMarkupLangFilePassRef				ParseXMLFile( IStreamReader* stream_reader, _ENCRYPTION encryption_type, AStringPtr encryption_key ) override;
	virtual IHTMLFilePassRef					ParseHTMLFile( IStreamReader* stream_reader ) override;
	virtual IMarkupLangFilePassRef				ParseJSONFile( IStreamReader* stream_reader ) override;
	virtual IMarkupLangFilePassRef				ParseJSONFile( AStringPtr string ) override;
	virtual IMarkupLangFilePassRef				ParseJSONFile( UStringPtr string ) override;
	virtual IMarkupLangFilePassRef				ParseJSONFile( WStringPtr string ) override;
	virtual IMarkupLangFilePassRef				ParseMarkupLangFile( IStreamReader* stream_reader ) override;
	virtual IManifestFilePassRef				ParseManifestFile( IStreamReader* stream_reader ) override;
	virtual IManifestFilePassRef				ParseManifestFile( IStreamReader* stream_reader, _ENCRYPTION encryption_type, WStringPtr encryption_key ) override;
	virtual IPSDFilePassRef						ParsePSDFile( IStreamReader* stream_reader, _dword flags = 0 ) override;
	virtual IImageFilePassRef					ParseImageFile( IStreamReader* stream_reader, _FILE_FORMAT file_format = _FF_UNKNOWN, _dword flags = 0 ) override;
	virtual ISoundFilePassRef					ParseSoundFile( IStreamReader* stream_reader, _FILE_FORMAT file_format = _FF_UNKNOWN, _dword flags = 0 ) override;
	virtual IZIPFilePassRef						ParseCompressedFile( IStreamReader* stream_reader, WStringPtr password = L"", _dword flags = 0 ) override;
	virtual IZIPFilePassRef						ParseZipFile( IStreamReader* stream_reader, WStringPtr password = L"", _dword flags = 0 ) override;
	virtual IZIPFilePassRef						Parse7zFile( IStreamReader* stream_reader, WStringPtr password = L"", _dword flags = 0 ) override;
	virtual IZIPFilePassRef						ParsePackageFile( IStreamReader* stream_reader ) override;
	virtual IWEBMFilePassRef					ParseWEBMFile( IStreamReader* stream_reader ) override;

	virtual IManifestFileManagerPassRef			CreateManifestFileManager( ) override;

	virtual IResLoaderPassRef					CreateResLoader( _dword thread_number, WStringPtr name, IResLoaderFactory* factory ) override;
};

//----------------------------------------------------------------------------
// InterfaceFactory Implementation
//----------------------------------------------------------------------------

}