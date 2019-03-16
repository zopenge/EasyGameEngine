//! @file     IInterfaceFactory.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IInterfaceFactory
//----------------------------------------------------------------------------

class IInterfaceFactory : public IObject
{
public:
	typedef IObject* (*OnObjectCreateWithNameCallback)( );
	typedef IObject* (*OnObjectCreateArgsWithNameCallback)( _void* arguments );

	typedef IObject* (*OnObjectCreateWithIDCallback)( );
	typedef IObject* (*OnObjectCreateArgsWithIDCallback)( _void* arguments );

public:
	//!	Initialize.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Initialize( ) PURE;
	//!	Finalize.
	//!	@param		none.
	//!	@return		none.
	virtual _void Finalize( ) PURE;

	//!	Create object by class name.
	//!	@param		name	The class name.
	//!	@return		The object interface.
	virtual IObject* CreateObject( const AStringObj& name ) PURE;
	//!	Create object with arguments by class name.
	//!	@param		name		The class name.
	//!	@param		arguments	The arguments.
	//!	@return		The object interface.
	virtual IObject* CreateObject( const AStringObj& name, _void* arguments ) PURE;
	//!	Create object by class ID.
	//!	@param		id			The class ID.
	//!	@return		The object interface.
	virtual IObject* CreateObject( _dword id ) PURE;
	//!	Create object with arguments by class ID.
	//!	@param		id			The class ID.
	//!	@param		arguments	The arguments.
	//!	@return		The object interface.
	virtual IObject* CreateObject( _dword id, _void* arguments ) PURE;
	//!	Register object creation function.
	//!	@param		name			The class name.
	//!	@param		func_pointer	The function pointer.
	//!	@return		none.
	virtual _void RegisterObjectCreationFunc( const AStringObj& name, OnObjectCreateWithNameCallback func_pointer ) PURE;
	//!	Register object creation function.
	//!	@param		name			The class name.
	//!	@param		func_pointer	The function pointer.
	//!	@return		none.
	virtual _void RegisterObjectCreationFunc( const AStringObj& name, OnObjectCreateArgsWithNameCallback func_pointer ) PURE;
	//!	Register object creation function.
	//!	@param		id				The class ID.
	//!	@param		func_pointer	The function pointer.
	//!	@return		none.
	virtual _void RegisterObjectCreationFunc( _dword id, OnObjectCreateWithIDCallback func_pointer ) PURE;
	//!	Register object creation function.
	//!	@param		id				The class ID.
	//!	@param		func_pointer	The function pointer.
	//!	@return		none.
	virtual _void RegisterObjectCreationFunc( _dword id, OnObjectCreateArgsWithIDCallback func_pointer ) PURE;

	//!	Create file copier.
	//!	@param		none.
	//!	@return		The file copier.
	virtual IFileCopierPassRef CreateFileCopier( ) PURE;

	//!	Create file archive.
	//!	@param		path	The directory path.
	//!	@return		The archive.
	virtual IArchivePassRef CreateFileArchive( WStringPtr path ) PURE;
	//!	Create memory archive.
	//!	@param		name						The archive name.
	//!	@param		stream_reader				The stream reader.
	//!	@param		password					The password of archive.
	//!	@param		manifest_encryption_type	The encryption type.
	//!	@param		manifest_encryption_key		The encryption key.
	//!	@return		The archive.
	virtual IArchivePassRef CreateMemArchive( WStringPtr name, IStreamReader* stream_reader, WStringPtr password, _ENCRYPTION manifest_encryption_type, WStringPtr manifest_encryption_key ) PURE;
	//!	Create PE-Res archive.
	//!	@param		module_name		The module name.
	//!	@return		The archive.
	virtual IArchivePassRef CreatePEResArchive( WStringPtr module_name ) PURE;

	//!	Create string table.
	//!	@param		none.
	//!	@return		The string table.
	virtual IStringTablePassRef CreateStringTable( ) PURE;
	
	//!	Create action recorder.
	//!	@param		none.
	//!	@return		The action recorder interface.
	virtual IActionRecorderPassRef CreateActionRecorder( ) PURE;
	//!	Create input recorder.
	//!	@param		none.
	//!	@return		The input recorder interface.
	virtual IInputRecorderPassRef CreateInputRecorder( ) PURE;
	//!	Create operation recorder.
	//!	@param		max_buffer_number	The max buffer number.
	//!	@param		performer			The performer.
	//!	@return		The operation recorder interface.
	virtual IOperationRecorderPassRef CreateOperationRecorder( _dword max_buffer_number, IOperationRecordPerformer* performer ) PURE;

	//!	Create font face.
	//!	@param		type			The font face type.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The font face interface.
	virtual IFontFacePassRef CreateFontFace( _FONT_FACE_TYPE type, IStreamReader* stream_reader ) PURE;

	//!	Create image filler.
	//!	@param		type			The image filler type.
	//!	@param		size			The image filler size in pixel.
	//!	@param		space			The space size between images in pixel.
	//!	@return		The image filler interface.
	virtual IImageFillerPassRef CreateImageFiller( _IMAGE_FILLTER_TYPE type, const PointU& size, const PointU& space = PointU::cZeroPoint ) PURE;

	//!	Create regular expression.
	//!	@param		pattern			The pattern string.
	//!	@return		The regular expression interface.
	virtual IRegularExpressionPassRef CreateRegularExpression( WStringPtr pattern ) PURE;

	//!	Build the MD5 code from file.
	//!	@param		filename		The file name.
	//!	@param		md5_code		The MD5 code.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool BuildMD5CodeFromFile( WStringPtr filename, MD5Code& md5_code ) PURE;
	//!	Build the MD5 code from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@param		md5_code		The MD5 code.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool BuildMD5CodeFromStream( IStreamReader* stream_reader, MD5Code& md5_code ) PURE;
	//!	Build the MD5 code from string.
	//!	@param		string			The string.
	//! @return		The MD5 code.
	virtual MD5Code BuildMD5CodeFromString( AStringPtr string ) PURE;
	//!	Build the MD5 code from string.
	//!	@param		string			The string.
	//! @return		The MD5 code.
	virtual MD5Code BuildMD5CodeFromString( WStringPtr string ) PURE;
	//!	Create MD5 checksum builder.
	//!	@param		chunk_size		The temporary chunk buffer size to read from stream.
	//!	@return		The MD5 checksum builder interface.
	virtual IMD5ChecksumBuilderPassRef CreateMD5ChecksumBuilder( _dword chunk_size = 640 KB ) PURE;

	//!	Create projectile object.
	//!	@param		position		The start position.
	//!	@param		direction		The start direction.
	//!	@param		target			The target position.
	//!	@param		speed			The speed per-second.
	//!	@param		height_rate		The rate will affect the height(Z-Position) of projectile object.
	//!	@return		The projectile object interface.
	virtual IProjectileObjectPassRef CreateProjectileObjectBySpeed( const Vector3& position, const Vector3& direction, const Vector3& target, _float speed, _float height_rate = 1.0f ) PURE;
	//!	Create projectile object.
	//!	@param		position		The start position.
	//!	@param		direction		The start direction.
	//!	@param		target			The target position.
	//!	@param		duration		The duration in milliseconds.
	//!	@param		height_rate		The rate will affect the height(Z-Position) of projectile object.
	//!	@return		The projectile object interface.
	virtual IProjectileObjectPassRef CreateProjectileObjectByDuration( const Vector3& position, const Vector3& direction, const Vector3& target, _dword duration, _float height_rate = 1.0f ) PURE;

	//!	Create interpolator.
	//! @param		interpolator_type	The type.
	//!	@return		The interpolator interface.
	virtual IInterpolatorPassRef CreateInterpolator( _INTERPOLATOR_TYPE interpolator_type ) PURE;

	//!	Create measurable object.
	//!	@param		size		The size.
	//!	@return		The measure object.
	virtual IMeasurableObjectPassRef CreateMeasurableObj( const Vector2& size ) PURE;
	//!	Create aligner.
	//!	@param		none.
	//!	@return		The aligner interface.
	virtual IAlignerPassRef CreateAligner( ) PURE;

	//!	Create command line parser.
	//!	@param		cmdline			The command line string.
	//!	@return		The command line parser interface.
	virtual ICommandLineParserPassRef CreateCommandLineParser( ) PURE;
	//!	Create command line parser.
	//!	@param		cmdline			The command line string.
	//!	@return		The command line parser interface.
	virtual ICommandLineParserPassRef CreateCommandLineParser( AStringPtr cmdline ) PURE;
	//!	Create command line parser.
	//!	@param		cmdline			The command line string.
	//!	@return		The command line parser interface.
	virtual ICommandLineParserPassRef CreateCommandLineParser( WStringPtr cmdline ) PURE;
	//!	Create command line parser.
	//!	@param		argc			The argument number.
	//!	@param		argv			The arguments.
	//!	@return		The command line parser interface.
	virtual ICommandLineParserPassRef CreateCommandLineParser( _dword argc, const _chara* argv[] ) PURE;
	//!	Create command line parser.
	//!	@param		argc			The argument number.
	//!	@param		argv			The arguments.
	//!	@return		The command line parser interface.
	virtual ICommandLineParserPassRef CreateCommandLineParser( _dword argc, const _charw* argv[] ) PURE;
	//!	Create command line parser.
	//!	@param		argc			The argument number.
	//!	@param		argn			The argument names.
	//!	@param		argv			The argument values.
	//!	@return		The command line parser interface.
	virtual ICommandLineParserPassRef CreateCommandLineParser( _dword argc, const _chara* argn[], const _chara* argv[] ) PURE;
	//!	Create command line parser.
	//!	@param		argc			The argument number.
	//!	@param		argn			The argument names.
	//!	@param		argv			The argument values.
	//!	@return		The command line parser interface.
	virtual ICommandLineParserPassRef CreateCommandLineParser( _dword argc, const _charw* argn[], const _charw* argv[] ) PURE;

	//!	Create properties.
	//!	@param		none.
	//!	@return		The properties interface.
	virtual IPropertiesPassRef CreateProperties( ) PURE;

	//!	Create protobuf message processor.
	//!	@param		none.
	//!	@return		The protobuf message processor.
	virtual IProtoBufMessageProcessorPassRef CreateProtoBufMessageProcessor( ) PURE;
	//!	Create protobuf processor.
	//!	@param		none.
	//!	@return		The protobuf processor.
	virtual IProtoBufProcessorPassRef CreateProtoBufProcessor( ) PURE;

	//!	Create logger.
	//!	@param		none.
	//!	@return		The logger interface.
	virtual ILoggerPassRef CreateLogger( ) PURE;
	//!	Create file logger.
	//!	@param		app_name		The application name.
	//!	@return		The logger interface.
	virtual ILoggerPassRef CreateFileLogger( WStringPtr app_name ) PURE;

	//!	Create standard allocator.
	//!	@param		arrange_size	The arrange size in bytes.
	//!	@return		The memory allocator.
	virtual IAllocatorPassRef CreateStdAllocator( _dword arrange_size = 4 ) PURE;
	//!	Create memory allocator.
	//!	@param		page_size		The page size.
	//!	@param		min_chunk_size	The minimal chunk size.
	//!	@param		arrange_size	The arrange size in bytes.
	//!	@return		The memory allocator.
	virtual IAllocatorPassRef CreateMemAllocator( _dword page_size, _dword min_chunk_size = 1 KB, _dword arrange_size = 4 ) PURE;
	//!	Create stack allocator.
	//!	@param		size			The buffer size.
	//!	@param		arrange_size	The arrange size in bytes.
	//!	@return		The stack allocator.
	virtual IStackAllocatorPassRef CreateStackAllocator( _dword size, _dword arrange_size = 4 ) PURE;
	//!	Create ring allocator.
	//!	@param		size			The buffer size.
	//!	@param		arrange_size	The arrange size in bytes.
	//!	@return		The ring allocator.
	virtual IRingAllocatorPassRef CreateRingAllocator( _dword size, _dword arrange_size = 4 ) PURE;
	//!	Create linear allocator.
	//!	@param		buffer			The buffer data.
	//!	@param		size			The buffer size.
	//!	@param		arrange_size	The arrange size in bytes.
	//!	@return		The linear allocator.
	virtual ILinearAllocatorPassRef CreateLinearAllocator( _byte* buffer, _dword size, _dword arrange_size = 4 ) PURE;
	//!	Create range allocator.
	//!	@param		size			The range size.
	//!	@param		arrange_size	The arrange size in bytes.
	//!	@return		The range allocator.
	virtual IRangeAllocatorPassRef CreateRangeAllocator( _dword size, _dword arrange_size = 4 ) PURE;
	//!	Create buffer allocator.
	//!	@param		size			The max buffer size.
	//!	@param		arrange_size	The arrange size in bytes.
	//!	@return		The range allocator.
	virtual IBufferAllocatorPassRef CreateBufferAllocator( _dword size, _dword arrange_size = 4 ) PURE;
	//!	Create offset allocator.
	//!	@param		size			The range size.
	//!	@param		arrange_size	The arrange size in bytes.
	//!	@return		The offset allocator.
	virtual IOffsetAllocatorPassRef CreateOffsetAllocator( _dword size, _dword arrange_size = 4 ) PURE;

	//!	Create cache buffer.
	//!	@param		buffer_size		The buffer size in bytes.
	//!	@param		cache_size		The cache size in bytes.
	//!	@return		The stream reader.
	virtual ICacheBufferPassRef CreateCacheBuffer( _dword buffer_size, _dword cache_size, ICacheBufferNotifier* notifier ) PURE;
	
	//!	Create memory stream reader.
	//!	@param		buffer			The buffer data.
	//!	@param		size			The buffer size.
	//!	@param		share_mode		True indicates use the share mode.
	//!	@return		The stream reader.
	virtual IStreamReaderPassRef CreateMemStreamReader( const _byte* buffer, _dword size, _STREAM_SHARE_MODE share_mode ) PURE;
	//!	Create memory stream writer.
	//!	@param		none.
	//!	@return		The stream writer.
	virtual IStreamWriterPassRef CreateMemStreamWriter( ) PURE;
	//!	Create memory stream writer.
	//!	@param		size			The initial buffer size.
	//!	@return		The stream writer.
	virtual IStreamWriterPassRef CreateMemStreamWriter( _dword size ) PURE;
	//!	Create memory stream writer.
	//!	@param		size			The initial buffer size.
	//!	@param		grow_size		The initial grow size.
	//!	@return		The stream writer.
	virtual IStreamWriterPassRef CreateMemStreamWriter( _dword size, _dword grow_size ) PURE;
	//!	Create memory stream writer.
	//!	@param		buffer			The buffer data.
	//!	@param		size			The buffer size.
	//!	@param		share_mode		True indicates use the share mode.
	//!	@return		The stream writer.
	virtual IStreamWriterPassRef CreateMemStreamWriter( _byte* buffer, _dword size, _STREAM_SHARE_MODE share_mode ) PURE;

	//!	Create bit stream reader.
	//!	@param		buffer			The buffer data.
	//!	@param		size			The buffer size.
	//!	@param		share_mode		True indicates use the share mode.
	//!	@return		The stream reader.
	virtual IStreamReaderPassRef CreateBitStreamReader( const _byte* buffer, _dword size, _STREAM_SHARE_MODE share_mode ) PURE;
	//!	Create bit stream writer.
	//!	@param		size			The initial buffer size.
	//!	@return		The stream writer.
	virtual IStreamWriterPassRef CreateBitStreamWriter( _dword size ) PURE;

	//!	Create (ANSI) string stream reader.
	//!	@param		string			The string.
	//!	@return		The stream reader.
	virtual IStreamReaderPassRef CreateAStringStreamReader( AStringPtr string ) PURE;
	//!	Create (UTF-8) string stream reader.
	//!	@param		string			The string.
	//!	@return		The stream reader.
	virtual IStreamReaderPassRef CreateUStringStreamReader( UStringPtr string ) PURE;
	//!	Create (UTF-16) string stream reader.
	//!	@param		string			The string.
	//!	@return		The stream reader.
	virtual IStreamReaderPassRef CreateWStringStreamReader( WStringPtr string ) PURE;

	//!	Create file stream reader.
	//!	@param		filename		The file name.
	//!	@return		The stream reader.
	virtual IFileStreamReaderPassRef CreateFileStreamReader( WStringPtr filename ) PURE;
	//!	Create file stream writer.
	//!	@param		filename		The file name.
	//!	@return		The stream writer.
	virtual IFileStreamWriterPassRef CreateFileStreamWriter( WStringPtr filename ) PURE;

	//!	Create safe stream reader.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The stream reader.
	virtual IStreamReaderPassRef CreateSafeStreamReader( IStreamReader* stream_reader ) PURE;

	//!	Create the stream writer processor.
	//!	@param		none.
	//!	@return		The stream writer encoder.
	virtual IStreamProcessorPassRef CreateStreamWriterProcessor( ) PURE;
	//!	Create the stream writer processor by MD5 validation.
	//!	@param		md5_code		The MD5 code.
	//!	@return		The stream writer encoder.
	virtual IStreamProcessorPassRef CreateStreamWriterProcessor( const MD5Code& md5_code ) PURE;

	//!	Create thread pool.
	//!	@param		thread_number	The thread worker number.
	//!	@param		name			The thread pool name.
	//!	@return		The thread pool interface.
	virtual IThreadPoolPassRef CreateThreadPool( _dword thread_number, WStringPtr name = L"" ) PURE;
	//!	Create single thread pool.
	//!	@param		none.
	//!	@return		The thread pool interface.
	virtual IThreadPoolPassRef CreateSingleThreadPool( ) PURE;
	//!	Create transaction manager.
	//!	@param		thread_number	The thread worker number.
	//!	@param		name			The thread pool name.
	//!	@return		The transaction manager interface.
	virtual ITransactionManagerPassRef CreateTransactionManager( _dword thread_number, WStringPtr name = L"" ) PURE;

	//!	Create console application.
	//!	@param		none.
	//!	@return		The console application interface.
	virtual IConsoleAppPassRef CreateConsoleApplication( ) PURE;

	//!	Create view-based application.
	//!	@param		app_handle		The application what pass by specified platform and analyze by specified viewbased-application.
	//!	@return		The view-based application interface.
	virtual IViewBasedAppPassRef CreateViewBasedApplication( _void* app_handle ) PURE;
	//!	Create view-based application.
	//!	@param		app_handle		The application what pass by specified platform and analyze by specified viewbased-application.
	//!	@param		size			The application size.
	//!	@return		The view-based application interface.
	virtual IViewBasedAppPassRef CreateViewBasedApplication( _void* app_handle, const PointU& size ) PURE;
	//!	Create view-based application.
	//!	@param		flag			The application creation flag.
	//!	@return		The view-based application interface.
	virtual IViewBasedAppPassRef CreateViewBasedApplication( IViewBasedApp::_CREATION_FLAG flag ) PURE;

	//!	Create the XML serializable node.
	//!	@param		none.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef CreateXMLSerializableNode( ) PURE;
	//!	Create the XML serializable node (ANSI).
	//!	@param		string			The XML format string.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef CreateXMLSerializableNode( AStringPtr string ) PURE;
	//!	Create the XML serializable node (UTF-8).
	//!	@param		string			The XML format string.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef CreateXMLSerializableNode( UStringPtr string ) PURE;
	//!	Create the XML serializable node (UTF-16).
	//!	@param		string			The XML format string.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef CreateXMLSerializableNode( WStringPtr string ) PURE;

	//!	Create the JSON serializable node.
	//!	@param		none.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef CreateJSONSerializableNode( ) PURE;
	//!	Create the JSON serializable node (ANSI).
	//!	@param		string			The JSON format string.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef CreateJSONSerializableNode( AStringPtr string ) PURE;
	//!	Create the JSON serializable node (UTF-8).
	//!	@param		string			The JSON format string.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef CreateJSONSerializableNode( UStringPtr string ) PURE;
	//!	Create the JSON serializable node (UTF-16).
	//!	@param		string			The JSON format string.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef CreateJSONSerializableNode( WStringPtr string ) PURE;

	//!	Create the markup language serializable node (ANSI).
	//!	@param		string			The markup language format string.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef CreateMarkupLangSerializableNode( AStringPtr string ) PURE;
	//!	Create the markup language serializable node (UTF-8).
	//!	@param		string			The markup language format string.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef CreateMarkupLangSerializableNode( UStringPtr string ) PURE;
	//!	Create the markup language serializable node (UTF-16).
	//!	@param		string			The markup language format string.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef CreateMarkupLangSerializableNode( WStringPtr string ) PURE;
	//!	Create the markup language serializable node.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef CreateMarkupLangSerializableNode( IStreamReader* stream_reader ) PURE;
	//!	Create the markup language serializable node by the first child element of root.
	//!	@param		file			The markup language file.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef CreateMarkupLangSerializableNode( IMarkupLangFile* file ) PURE;
	//!	Create the markup language serializable node by the first child element of root.
	//!	@param		element			The markup language element.
	//!	@param		file			The markup language file.
	//!	@return		The serializable node.
	virtual ISerializableNodePassRef CreateMarkupLangSerializableNode( IMarkupLangElement* element, IMarkupLangFile* file ) PURE;

	//!	Create the network firewall interface.
	//!	@param		none.
	//!	@return		The network firewall interface.
	virtual INetFirewallPassRef CreateNetFirewall( ) PURE;
	//!	Create the shell link interface.
	//!	@param		none.
	//!	@return		The shell link interface.
	virtual IShellPassRef CreateShell( ) PURE;
	//!	Create the menu interface.
	//!	@param		popup			True indicates it's popup menu.
	//!	@return		The menu interface.
	virtual IMenuPassRef CreateMenu( _ubool popup ) PURE;
	//!	Create the process debugger interface.
	//!	@param		none.
	//!	@return		The process debugger interface.
	virtual IProcessDebuggerPassRef CreateProcessDebugger( ) PURE;
	//!	Create the registry interface.
	//!	@param		root			The root key type.
	//!	@param		keyname			The key name.
	//!	@return		The registry interface.
	virtual IRegistryPassRef CreateRegistry( IRegistry::_ROOT_KEY root, WStringPtr keyname ) PURE;

	//!	Create the compression encoder.
	//!	@param		type			The compression type.
	//!	@return		The compression encoder.
	virtual ICompressionEncoderPassRef CreateCompressionEncoder( _COMPRESSION type ) PURE;
	//!	Create the compression decoder.
	//!	@param		type			The compression type.
	//!	@return		The compression decoder.
	virtual ICompressionDecoderPassRef CreateCompressionDecoder( _COMPRESSION type ) PURE;
	//!	Compress.
	//!	@param		type			The compression type.
	//!	@param		size			The buffer size.
	//!	@param		buffer			The buffer data.
	//!	@return		The stream reader.
	virtual IStreamReaderPassRef CompressBuffer( _COMPRESSION type, _dword size, const _byte* buffer ) PURE;
	//!	Decompress.
	//!	@param		type			The compression type.
	//!	@param		size			The buffer size.
	//!	@param		buffer			The buffer data.
	//!	@return		The stream reader.
	virtual IStreamReaderPassRef DecompressBuffer( _COMPRESSION type, _dword size, const _byte* buffer ) PURE;

	//!	Create OGG decoder.
	virtual IAudioDecoderPassRef CreateOGGDecoder( const SoundVorbisFormatInfo* info ) PURE;

	//!	Create the encryptor.
	//!	@param		type			The encryption type.
	//!	@param		key				The encryption key.
	//!	@return		The encryptor.
	virtual IEncryptorPassRef CreateEncryptor( _ENCRYPTION type, AStringPtr key ) PURE;
	//!	Create the decryptor.
	//!	@param		type			The encryption type.
	//!	@param		key				The encryption key.
	//!	@return		The decryptor.
	virtual IDecryptorPassRef CreateDecryptor( _ENCRYPTION type, AStringPtr key ) PURE;
	//!	Encrypt file.
	//!	@param		source_filename	The source file name.
	//!	@param		target_filename	The target file name.
	//!	@param		type			The encryption type.
	//!	@param		key				The encryption key.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool EncryptFile( WStringPtr source_filename, WStringPtr target_filename, _ENCRYPTION type, AStringPtr key ) PURE;
	//!	Decrypt file.
	//!	@param		source_filename	The source file name.
	//!	@param		target_filename	The target file name.
	//!	@param		type			The encryption type.
	//!	@param		key				The encryption key.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool DecryptFile( WStringPtr source_filename, WStringPtr target_filename, _ENCRYPTION type, AStringPtr key ) PURE;
	//!	Encrypt stream.
	//!	@param		stream_reader	The stream reader.
	//!	@param		type			The encryption type.
	//!	@param		key				The encryption key.
	//! @return		The encrypt stream reader.
	virtual IStreamReaderPassRef EncryptStream( IStreamReader* stream_reader, _ENCRYPTION type, AStringPtr key ) PURE;
	//!	Decrypt stream.
	//!	@param		stream_reader	The stream reader.
	//!	@param		type			The encryption type.
	//!	@param		key				The encryption key.
	//! @return		The decrypt stream reader.
	virtual IStreamReaderPassRef DecryptStream( IStreamReader* stream_reader, _ENCRYPTION type, AStringPtr key ) PURE;

	//!	Get the common file type ID from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The file type ID.
	virtual _FILE_FORMAT GetCommonFileTypeFromStream( IStreamReader* stream_reader ) const PURE;
	//!	Get the image file type ID from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The file type ID.
	virtual _FILE_FORMAT GetImageFileTypeFromStream( IStreamReader* stream_reader ) const PURE;
	//!	Get the sound file type ID from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The file type ID.
	virtual _FILE_FORMAT GetSoundFileTypeFromStream( IStreamReader* stream_reader ) const PURE;

	//!	Create the XML file.
	//!	@param		none.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef CreateXMLFile( ) PURE;
	//!	Create the XML file.
	//!	@param		root_name	The root name.
	//!	@param		version		The version.
	//!	@param		encoding	The encoding type.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef CreateXMLFile( WStringPtr root_name, _ENCODING encoding = _ENCODING_UTF8, const Version& version = Version::cInitial ) PURE;
	//!	Create the XML file.
	//!	@param		node		The serializable node.
	//!	@param		version		The version.
	//!	@param		encoding	The encoding type.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef CreateXMLFile( const ISerializableNode* node, _ENCODING encoding = _ENCODING_UTF8, const Version& version = Version::cInitial ) PURE;
	//!	Create the BXML file.
	//!	@param		markup_file	The markup file.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef CreateBXMLFile( IMarkupLangFile* markup_file ) PURE;
	//!	Create the JSON file.
	//!	@param		none.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef CreateJSONFile( ) PURE;
	//!	Create the manifest file.
	//!	@param		none.
	//!	@return		The manifest file interface.
	virtual IManifestFilePassRef CreateManifestFile( ) PURE;
	//!	Create the geometry file.
	//!	@param		none.
	//!	@return		The geometry file interface.
	virtual IGeometryFilePassRef CreateGeometryFile( ) PURE;
	//!	Create the geometry mesh chunk.
	//!	@param		vertex_type		The vertex type, @see _GEOMETRY_VERTEX_TYPE.
	//!	@param		vb_data			The vertex buffer data.
	//!	@param		vb_size			The vertex buffer size.
	//!	@param		ib_data			The index buffer data.
	//!	@param		ib_size			The index buffer size.
	//!	@return		The geometry mesh chunk interface.
	virtual IGeometryMeshChunkPassRef CreateGeometryMeshChunk( _dword vertex_type, const _byte* vb_data, _dword vb_size, const _word* ib_data, _dword ib_size ) PURE;
	//!	Create box geometry.
	//!	@param		min_vector	The min vector.
	//!	@param		max_vector	The max vector.
	//!	@return		The box geometry chunk interface.
	virtual IGeometryMeshChunkPassRef CreateBoxGeometryMeshChunk( const Vector3& min_vector, const Vector3& max_vector ) PURE;
	//!	Create the image file.
	//!	@param		file_format		The file format.
	//!	@param		width			The image width.
	//!	@param		height			The image height.
	//!	@param		pixelformat		The image pixel format.
	//!	@param		pixelbuffer		The image pixel buffer.
	//! @return		The image file.
	virtual IImageFilePassRef CreateImageFile( _FILE_FORMAT file_format, _dword width, _dword height, _PIXEL_FORMAT pixelformat, const _void* pixelbuffer = _null ) PURE;
	//!	Create sound file writer.
	//!	@param		file_format		The file format.
	virtual ISoundFileWriterPassRef CreateSoundFileWriter( _FILE_FORMAT file_format ) PURE;
	//!	Create streaming PCM file.
	virtual IStreamingPCMFilePassRef CreateStreamingPCMFile( const SoundHeaderInfo& info ) PURE;
	//!	Create the zip file.
	//!	@param		filename		The absolute file name.
	//!	@param		password		The password.
	//!	@return		The zip file.
	virtual IZIPFilePassRef CreateZipFile( WStringPtr filename, WStringPtr password = L"" ) PURE;
	//!	Create the 7z file.
	//!	@param		filename		The absolute file name.
	//!	@param		password		The password.
	//!	@return		The 7z file.
	virtual IZIPFilePassRef Create7zFile( WStringPtr filename, WStringPtr password = L"" ) PURE;
	//!	Create the package file.
	//!	@param		filename		The absolute file name.
	//!	@return		The package file.
	virtual IZIPFilePassRef CreatePackageFile( WStringPtr filename ) PURE;

	//!	Save the image file.
	//!	@param		file_format		The file type ID.
	//!	@param		pixelformat		The image pixel format.
	//!	@param		filename		The file name.
	//!	@param		image			The image file.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SaveImageFile( _FILE_FORMAT file_format, _PIXEL_FORMAT pixelformat, WStringPtr filename, IImageFile* image ) PURE;

	//!	Parse FNT file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The FNT file interface.
	virtual IFNTFilePassRef ParseFNTFile( IStreamReader* stream_reader ) PURE;
	//!	Parse CSV file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The CSV file interface.
	virtual ICSVFilePassRef ParseCSVFile( IStreamReader* stream_reader ) PURE;
	//!	Parse geometry file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The geometry file interface.
	virtual IGeometryFilePassRef ParseGeometryFile( IStreamReader* stream_reader ) PURE;
	//!	Parse XML file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef ParseXMLFile( IStreamReader* stream_reader ) PURE;
	//!	Parse XML file from stream with encryption.
	//!	@param		stream_reader	The stream reader.
	//!	@param		encryption_type	The encryption type.
	//!	@param		encryption_key	The encryption key.
	//!	@return		The XML file interface.
	virtual IMarkupLangFilePassRef ParseXMLFile( IStreamReader* stream_reader, _ENCRYPTION encryption_type, AStringPtr encryption_key ) PURE;
	//!	Parse HTML file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The HTML file interface.
	virtual IHTMLFilePassRef ParseHTMLFile( IStreamReader* stream_reader ) PURE;
	//!	Parse JSON file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef ParseJSONFile( IStreamReader* stream_reader ) PURE;
	//!	Parse JSON file from ANSI.
	//!	@param		string			The ANSI string.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef ParseJSONFile( AStringPtr string ) PURE;
	//!	Parse JSON file from UTF-8.
	//!	@param		string			The UTF-8 string.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef ParseJSONFile( UStringPtr string ) PURE;
	//!	Parse JSON file from UTF-16.
	//!	@param		string			The UTF-8 string.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef ParseJSONFile( WStringPtr string ) PURE;
	//!	Parse markup file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef ParseMarkupLangFile( IStreamReader* stream_reader ) PURE;
	//!	Parse manifest file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The manifest file interface.
	virtual IManifestFilePassRef ParseManifestFile( IStreamReader* stream_reader ) PURE;
	//!	Parse manifest file from stream with encryption.
	//!	@param		stream_reader	The stream reader.
	//!	@param		encryption_type	The encryption type.
	//!	@param		encryption_key	The encryption key.
	//!	@return		The manifest file interface.
	virtual IManifestFilePassRef ParseManifestFile( IStreamReader* stream_reader, _ENCRYPTION encryption_type, WStringPtr encryption_key ) PURE;
	//!	Parse PSD file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@param		flags			The file flags.
	//!	@return		The file interface.
	virtual IPSDFilePassRef ParsePSDFile( IStreamReader* stream_reader, _dword flags = 0 ) PURE;
	//!	Parse image file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@param		file_format		The file format, _FF_UNKNOWN indicates auto detect.
	//!	@param		flags			The file flags, @see IImageFile::_FLAG.
	//!	@return		The file interface.
	virtual IImageFilePassRef ParseImageFile( IStreamReader* stream_reader, _FILE_FORMAT file_format = _FF_UNKNOWN, _dword flags = 0 ) PURE;
	//!	Parse sound file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@param		file_format		The file format, _FF_UNKNOWN indicates auto detect.
	//!	@param		flags			The file flags.
	//!	@return		The file interface.
	virtual ISoundFilePassRef ParseSoundFile( IStreamReader* stream_reader, _FILE_FORMAT file_format = _FF_UNKNOWN, _dword flags = 0 ) PURE;
	//!	Parse the compressed file.
	//!	@param		stream_reader	The stream reader.
	//!	@param		password		The password.
	//!	@param		flags			The file flags.
	//!	@return		The zip file.
	virtual IZIPFilePassRef ParseCompressedFile( IStreamReader* stream_reader, WStringPtr password = L"", _dword flags = 0 ) PURE;
	//!	Parse the zip file.
	//!	@param		stream_reader	The stream reader.
	//!	@param		password		The password.
	//!	@param		flags			The file flags.
	//!	@return		The zip file.
	virtual IZIPFilePassRef ParseZipFile( IStreamReader* stream_reader, WStringPtr password = L"", _dword flags = 0 ) PURE;
	//!	Parse the 7z file.
	//!	@param		stream_reader	The stream reader.
	//!	@param		password		The password.
	//!	@param		flags			The file flags.
	//!	@return		The 7z file.
	virtual IZIPFilePassRef Parse7zFile( IStreamReader* stream_reader, WStringPtr password = L"", _dword flags = 0 ) PURE;
	//!	Parse the package file.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The package file.
	virtual IZIPFilePassRef ParsePackageFile( IStreamReader* stream_reader ) PURE;
	//!	Parse webm file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The file interface.
	virtual IWEBMFilePassRef ParseWEBMFile( IStreamReader* stream_reader ) PURE;

	//!	Create the manifest file manager.
	//!	@param		none.
	//!	@return		The manifest file manager interface.
	virtual IManifestFileManagerPassRef CreateManifestFileManager( ) PURE;

	//!	Create the resource loader.
	//!	@param		thread_number	The thread number for async-loading tasks.
	//!	@param		name			The resource loader name.
	//!	@param		factory			The resource factory.
	//!	@return		The resource loader interface.
	virtual IResLoaderPassRef CreateResLoader( _dword thread_number, WStringPtr name, IResLoaderFactory* factory ) PURE;

public:
	//!	Create object by interface name.
	//!	@return		The object interface.
	template< typename Type >
	PassRefPtr< Type > CreateObjectPassRef( )
	{
		STATIC_ASTROBJ_V( class_name, typeid( Type ).name( ) );

		Type* object = (Type*)CreateObject( ASTROBJ( class_name ) );
		return object;
	}
	//!	Create object by interface name.
	//!	@param		arguments	The arguments.
	//!	@return		The object interface.
	template< typename Type >
	PassRefPtr< Type > CreateObjectPassRef( _void* arguments )
	{
		STATIC_ASTROBJ_V( class_name, typeid( Type ).name( ) );

		Type* object = (Type*)CreateObject( ASTROBJ( class_name ), arguments );
		return object;
	}

	//!	Create object by class name.
	//!	@param		name	The class name.
	//!	@return		The object interface.
	template< typename Type >
	PassRefPtr< Type > CreateObjectPassRef( const AStringObj& name )
	{
		Type* object = (Type*) CreateObject( name );
		return object;
	}
	//!	Create object with arguments by class name.
	//!	@param		name		The class name.
	//!	@param		arguments	The arguments.
	//!	@return		The object interface.
	template< typename Type >
	PassRefPtr< Type > CreateObjectPassRef( const AStringObj& name, _void* arguments )
	{
		Type* object = (Type*) CreateObject( name, arguments );
		return object;
	}

	//!	Create object by class ID.
	//!	@param		id	The class ID.
	//!	@return		The object interface.
	template< typename Type >
	PassRefPtr< Type > CreateObjectPassRef( _dword id )
	{
		Type* object = (Type*)CreateObject( id );
		return object;
	}
	//!	Create object with arguments by class ID.
	//!	@param		name		The class ID.
	//!	@param		arguments	The arguments.
	//!	@return		The object interface.
	template< typename Type >
	PassRefPtr< Type > CreateObjectPassRef( _dword id, _void* arguments )
	{
		Type* object = (Type*)CreateObject( id, arguments );
		return object;
	}
};

}