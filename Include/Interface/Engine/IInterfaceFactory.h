#pragma once

namespace EGE {

/// <summary>
/// The interface factory to create objects.
/// </summary>
class IInterfaceFactory : public IObject {
public:
	typedef IObject* (*OnObjectCreateCallback)();

public:
	//!	Initialize.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Initialize() PURE;
	//!	Finalize.
	//!	@param		none.
	//!	@return		none.
	virtual _void Finalize() PURE;

	//!	Create object by class name.
	//!	@param		name	The class name.
	//!	@return		The object interface.
	virtual IObject* CreateObject(WStringPtr name) PURE;
	//!	Register object creation function.
	//!	@param		name			The class name.
	//!	@param		func_pointer	The function pointer.
	//!	@return		none.
	virtual _void RegisterObjectCreationFunc(WStringPtr name, OnObjectCreateCallback func_pointer) PURE;

	//!	Create file archive.
	//!	@param		path	The directory path.
	//!	@return		The archive.
	virtual IArchivePassRef CreateFileArchive(WStringPtr path) PURE;
	//!	Create memory archive.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The archive.
	virtual IArchivePassRef CreateMemArchive(IStreamReader* stream_reader) PURE;
	//!	Create PE-Res archive.
	//!	@param		module_name		The module name.
	//!	@return		The archive.
	virtual IArchivePassRef CreatePEResArchive(WStringPtr module_name) PURE;

	//!	Create font face.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The font face interface.
	virtual IFontFacePassRef CreateFontFace(IStreamReader* stream_reader) PURE;

	//!	Create image filler.
	//!	@param		type	The image filler type.
	//!	@param		size	The image filler size in pixel.
	//!	@return		The image filler interface.
	virtual IImageFillerPassRef CreateImageFiller(ImageFillerType type, const PointU& size) PURE;
	//!	Create layouter.
	//!	@param		none.
	//!	@return		The layouter interface.
	virtual ILayouterPassRef CreateLayouter() PURE;

	//!	Create regular expression.
	//!	@param		pattern			The pattern string.
	//!	@return		The regular expression interface.
	virtual IRegularExpressionPassRef CreateRegularExpression(WStringPtr pattern) PURE;

	//!	Create command line parser.
	//!	@param		cmdline			The command line string.
	//!	@return		The command line parser interface.
	virtual ICommandLineParserPassRef CreateCommandLineParser() PURE;
	//!	Create command line parser.
	//!	@param		cmdline			The command line string.
	//!	@return		The command line parser interface.
	virtual ICommandLineParserPassRef CreateCommandLineParser(WStringPtr cmdline) PURE;
	//!	Create command line parser.
	//!	@param		cmdline			The command line strings with keys and values.
	//!	@return		The command line parser interface.
	virtual ICommandLineParserPassRef CreateCommandLineParser(const WStringArray& cmdlines) PURE;
	//!	Create command line parser.
	//!	@param		keys		The command line keys.
	//!	@param		values		The command line values.
	//!	@return		The command line parser interface.
	virtual ICommandLineParserPassRef CreateCommandLineParser(const WStringArray& keys, const WStringArray& values) PURE;

	//!	Create logger.
	//!	@param		none.
	//!	@return		The logger interface.
	virtual ILoggerPassRef CreateLogger() PURE;
	//!	Create file logger.
	//!	@param		fileName	The file name.
	//!	@return		The logger interface.
	virtual ILoggerPassRef CreateFileLogger(WStringPtr fileName) PURE;

	//!	Create standard allocator.
	//!	@param		arrange_size	The arrange size in bytes.
	//!	@return		The memory allocator.
	virtual IAllocatorPassRef CreateStdAllocator(_dword arrange_size = 4) PURE;
	//!	Create memory allocator.
	//!	@param		page_size		The page size.
	//!	@param		min_chunk_size	The minimal chunk size.
	//!	@param		arrange_size	The arrange size in bytes.
	//!	@return		The memory allocator.
	virtual IAllocatorPassRef CreateMemAllocator(_dword page_size, _dword min_chunk_size = 1 KB, _dword arrange_size = 4) PURE;
	//!	Create linear allocator.
	//!	@param		buffer			The buffer data.
	//!	@param		size			The buffer size.
	//!	@param		arrange_size	The arrange size in bytes.
	//!	@return		The linear allocator.
	virtual IAllocatorPassRef CreateLinearAllocator(_byte* buffer, _dword size, _dword arrange_size = 4) PURE;
	//!	Create stack allocator.
	//!	@param		size			The buffer size.
	//!	@param		arrange_size	The arrange size in bytes.
	//!	@return		The stack allocator.
	virtual IStackAllocatorPassRef CreateStackAllocator(_dword size, _dword arrange_size = 4) PURE;

	//!	Create cache buffer.
	//!	@param		buffer_size		The buffer size in bytes.
	//!	@param		cache_size		The cache size in bytes.
	//!	@return		The stream reader.
	virtual ICacheBufferPassRef CreateCacheBuffer(_dword buffer_size, _dword cache_size, ICacheBufferNotifier* notifier) PURE;

	//!	Create memory stream reader.
	//!	@param		buffer			The buffer data.
	//!	@param		size			The buffer size.
	//!	@return		The stream reader.
	virtual IStreamReaderPassRef CreateMemStreamReader(const _byte* buffer, _dword size) PURE;
	//!	Create memory stream writer.
	//!	@param		none.
	//!	@return		The stream writer.
	virtual IStreamWriterPassRef CreateMemStreamWriter() PURE;
	//!	Create memory stream writer.
	//!	@param		size			The initial buffer size.
	//!	@return		The stream writer.
	virtual IStreamWriterPassRef CreateMemStreamWriter(_dword size) PURE;
	//!	Create memory stream writer.
	//!	@param		size			The initial buffer size.
	//!	@param		grow_size		The initial grow size.
	//!	@return		The stream writer.
	virtual IStreamWriterPassRef CreateMemStreamWriter(_dword size, _dword grow_size) PURE;
	//!	Create memory stream writer.
	//!	@param		buffer			The buffer data.
	//!	@param		size			The buffer size.
	//!	@param		share_mode		True indicates use the share mode.
	//!	@return		The stream writer.
	virtual IStreamWriterPassRef CreateMemStreamWriter(_byte* buffer, _dword size) PURE;

	//!	Create bit stream reader.
	//!	@param		buffer			The buffer data.
	//!	@param		size			The buffer size.
	//!	@param		share_mode		True indicates use the share mode.
	//!	@return		The stream reader.
	virtual IStreamReaderPassRef CreateBitStreamReader(const _byte* buffer, _dword size) PURE;
	//!	Create bit stream writer.
	//!	@param		size			The initial buffer size.
	//!	@return		The stream writer.
	virtual IStreamWriterPassRef CreateBitStreamWriter(_dword size) PURE;

	//!	Create file stream reader.
	//!	@param		filename		The file name.
	//!	@return		The stream reader.
	virtual IFileStreamReaderPassRef CreateFileStreamReader(WStringPtr filename) PURE;
	//!	Create file stream writer.
	//!	@param		filename		The file name.
	//!	@return		The stream writer.
	virtual IFileStreamWriterPassRef CreateFileStreamWriter(WStringPtr filename) PURE;

	//!	Create the stream writer processor.
	//!	@param		none.
	//!	@return		The stream writer encoder.
	virtual IStreamProcessorPassRef CreateStreamWriterProcessor() PURE;
	//!	Create the stream writer processor by MD5 validation.
	//!	@param		md5_code		The MD5 code.
	//!	@return		The stream writer encoder.
	virtual IStreamProcessorPassRef CreateStreamWriterProcessor(const MD5Code& md5_code) PURE;

	//!	Create thread pool.
	//!	@param		thread_number	The thread worker number, 0 indicates use none threads, only run in main thread.
	//!	@param		name			The thread pool name.
	//!	@return		The thread pool interface.
	virtual IThreadPoolPassRef CreateThreadPool(_dword thread_number, WStringPtr name = L"") PURE;

	//!	Create console application.
	//!	@param		none.
	//!	@return		The console application interface.
	virtual IConsoleAppPassRef CreateConsoleApplication() PURE;

	//!	Create view-based application.
	//!	@param		none.
	//!	@return		The view-based application interface.
	virtual IViewBasedAppPassRef CreateViewBasedApplication() PURE;
	//!	Create view-based application.
	//!	@param		app_handle		The application what pass by specified platform and analyze by specified viewbased-application.
	//!	@return		The view-based application interface.
	virtual IViewBasedAppPassRef CreateViewBasedApplication(_handle app_handle) PURE;
	//!	Create view-based application.
	//!	@param		app_handle		The application what pass by specified platform and analyze by specified viewbased-application.
	//!	@param		size			The application size.
	//!	@return		The view-based application interface.
	virtual IViewBasedAppPassRef CreateViewBasedApplication(_handle app_handle, const PointU& size) PURE;

	//!	Create the process debugger interface.
	//!	@param		none.
	//!	@return		The process debugger interface.
	virtual IProcessDebuggerPassRef CreateProcessDebugger() PURE;

	//!	Create the compression encoder.
	//!	@param		type			The compression type.
	//!	@return		The compression encoder.
	virtual ICompressionEncoderPassRef CreateCompressionEncoder(_COMPRESSION type) PURE;
	//!	Create the compression decoder.
	//!	@param		type			The compression type.
	//!	@return		The compression decoder.
	virtual ICompressionDecoderPassRef CreateCompressionDecoder(_COMPRESSION type) PURE;
	//!	Compress.
	//!	@param		type			The compression type.
	//!	@param		size			The buffer size.
	//!	@param		buffer			The buffer data.
	//!	@return		The stream reader.
	virtual IStreamReaderPassRef CompressBuffer(_COMPRESSION type, _dword size, const _byte* buffer) PURE;
	//!	Decompress.
	//!	@param		type			The compression type.
	//!	@param		size			The buffer size.
	//!	@param		buffer			The buffer data.
	//!	@return		The stream reader.
	virtual IStreamReaderPassRef DecompressBuffer(_COMPRESSION type, _dword size, const _byte* buffer) PURE;

	//!	Create OGG decoder.
	virtual IAudioDecoderPassRef CreateOGGDecoder(const SoundVorbisFormatInfo* info) PURE;

	//!	Create the encryptor.
	//!	@param		type			The encryption type.
	//!	@param		key				The encryption key.
	//!	@return		The encryptor.
	virtual IEncryptorPassRef CreateEncryptor(_ENCRYPTION type, AStringPtr key) PURE;
	//!	Create the decryptor.
	//!	@param		type			The encryption type.
	//!	@param		key				The encryption key.
	//!	@return		The decryptor.
	virtual IDecryptorPassRef CreateDecryptor(_ENCRYPTION type, AStringPtr key) PURE;
	//!	Encrypt file.
	//!	@param		source_filename	The source file name.
	//!	@param		target_filename	The target file name.
	//!	@param		type			The encryption type.
	//!	@param		key				The encryption key.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool EncryptFile(WStringPtr source_filename, WStringPtr target_filename, _ENCRYPTION type, AStringPtr key) PURE;
	//!	Decrypt file.
	//!	@param		source_filename	The source file name.
	//!	@param		target_filename	The target file name.
	//!	@param		type			The encryption type.
	//!	@param		key				The encryption key.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool DecryptFile(WStringPtr source_filename, WStringPtr target_filename, _ENCRYPTION type, AStringPtr key) PURE;
	//!	Encrypt stream.
	//!	@param		stream_reader	The stream reader.
	//!	@param		type			The encryption type.
	//!	@param		key				The encryption key.
	//! @return		The encrypt stream reader.
	virtual IStreamReaderPassRef EncryptStream(IStreamReader* stream_reader, _ENCRYPTION type, AStringPtr key) PURE;
	//!	Decrypt stream.
	//!	@param		stream_reader	The stream reader.
	//!	@param		type			The encryption type.
	//!	@param		key				The encryption key.
	//! @return		The decrypt stream reader.
	virtual IStreamReaderPassRef DecryptStream(IStreamReader* stream_reader, _ENCRYPTION type, AStringPtr key) PURE;

	//!	Get the common file type ID from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The file type ID.
	virtual _FILE_FORMAT GetCommonFileTypeFromStream(IStreamReader* stream_reader) const PURE;
	//!	Get the image file type ID from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The file type ID.
	virtual _FILE_FORMAT GetImageFileTypeFromStream(IStreamReader* stream_reader) const PURE;
	//!	Get the sound file type ID from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The file type ID.
	virtual _FILE_FORMAT GetSoundFileTypeFromStream(IStreamReader* stream_reader) const PURE;

	//!	Create the XML file.
	//!	@param		none.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef CreateXMLFile() PURE;
	//!	Create the XML file.
	//!	@param		root_name	The root name.
	//!	@param		version		The version.
	//!	@param		encoding	The encoding type.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef CreateXMLFile(WStringPtr root_name, _ENCODING encoding = _ENCODING_UTF8, const Version& version = Version::cInitial) PURE;
	//!	Create the XML file.
	//!	@param		node		The serializable node.
	//!	@param		version		The version.
	//!	@param		encoding	The encoding type.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef CreateXMLFile(const ISerializableNode* node, _ENCODING encoding = _ENCODING_UTF8, const Version& version = Version::cInitial) PURE;
	//!	Create the BXML file.
	//!	@param		markup_file	The markup file.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef CreateBXMLFile(IMarkupFile* markup_file) PURE;
	//!	Create the JSON file.
	//!	@param		none.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef CreateJSONFile() PURE;
	//!	Create the manifest file.
	//!	@param		none.
	//!	@return		The manifest file interface.
	virtual IManifestFilePassRef CreateManifestFile() PURE;
	//!	Create the geometry file.
	//!	@param		none.
	//!	@return		The geometry file interface.
	virtual IGeometryFilePassRef CreateGeometryFile() PURE;
	//!	Create the geometry mesh chunk.
	//!	@param		vertex_type		The vertex type, @see _GEOMETRY_VERTEX_TYPE.
	//!	@param		vb_data			The vertex buffer data.
	//!	@param		vb_size			The vertex buffer size.
	//!	@param		ib_data			The index buffer data.
	//!	@param		ib_size			The index buffer size.
	//!	@return		The geometry mesh chunk interface.
	virtual IGeometryMeshChunkPassRef CreateGeometryMeshChunk(_dword vertex_type, const _byte* vb_data, _dword vb_size, const _word* ib_data, _dword ib_size) PURE;
	//!	Create box geometry.
	//!	@param		min_vector	The min vector.
	//!	@param		max_vector	The max vector.
	//!	@return		The box geometry chunk interface.
	virtual IGeometryMeshChunkPassRef CreateBoxGeometryMeshChunk(const Vector3& min_vector, const Vector3& max_vector) PURE;
	//!	Create the image file.
	//!	@param		file_format		The file format.
	//!	@param		width			The image width.
	//!	@param		height			The image height.
	//!	@param		pixelformat		The image pixel format.
	//!	@param		pixelbuffer		The image pixel buffer.
	//! @return		The image file.
	virtual IImageFilePassRef CreateImageFile(_FILE_FORMAT file_format, _dword width, _dword height, _PIXEL_FORMAT pixelformat, const _void* pixelbuffer = _null) PURE;
	//!	Create sound file writer.
	//!	@param		file_format		The file format.
	virtual ISoundFileWriterPassRef CreateSoundFileWriter(_FILE_FORMAT file_format) PURE;
	//!	Create streaming PCM file.
	virtual IStreamingPCMFilePassRef CreateStreamingPCMFile(const SoundHeaderInfo& info) PURE;
	//!	Create the zip file.
	//!	@param		filename		The absolute file name.
	//!	@param		password		The password.
	//!	@return		The zip file.
	virtual IZIPFilePassRef CreateZipFile(WStringPtr filename, WStringPtr password = L"") PURE;
	//!	Create the 7z file.
	//!	@param		filename		The absolute file name.
	//!	@param		password		The password.
	//!	@return		The 7z file.
	virtual IZIPFilePassRef Create7zFile(WStringPtr filename, WStringPtr password = L"") PURE;
	//!	Create the package file.
	//!	@param		filename		The absolute file name.
	//!	@return		The package file.
	virtual IZIPFilePassRef CreatePackageFile(WStringPtr filename) PURE;

	//!	Save the image file.
	//!	@param		file_format		The file type ID.
	//!	@param		pixelformat		The image pixel format.
	//!	@param		filename		The file name.
	//!	@param		image			The image file.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SaveImageFile(_FILE_FORMAT file_format, _PIXEL_FORMAT pixelformat, WStringPtr filename, IImageFile* image) PURE;

	//!	Parse FNT file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The FNT file interface.
	virtual IFNTFilePassRef ParseFNTFile(IStreamReader* stream_reader) PURE;
	//!	Parse CSV file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The CSV file interface.
	virtual ICSVFilePassRef ParseCSVFile(IStreamReader* stream_reader) PURE;
	//!	Parse geometry file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The geometry file interface.
	virtual IGeometryFilePassRef ParseGeometryFile(IStreamReader* stream_reader) PURE;
	//!	Parse XML file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef ParseXMLFile(IStreamReader* stream_reader) PURE;
	//!	Parse XML file from stream with encryption.
	//!	@param		stream_reader	The stream reader.
	//!	@param		encryption_type	The encryption type.
	//!	@param		encryption_key	The encryption key.
	//!	@return		The XML file interface.
	virtual IMarkupLangFilePassRef ParseXMLFile(IStreamReader* stream_reader, _ENCRYPTION encryption_type, AStringPtr encryption_key) PURE;
	//!	Parse HTML file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The HTML file interface.
	virtual IHTMLFilePassRef ParseHTMLFile(IStreamReader* stream_reader) PURE;
	//!	Parse JSON file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef ParseJSONFile(IStreamReader* stream_reader) PURE;
	//!	Parse JSON file from ANSI.
	//!	@param		string			The ANSI string.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef ParseJSONFile(AStringPtr string) PURE;
	//!	Parse JSON file from UTF-8.
	//!	@param		string			The UTF-8 string.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef ParseJSONFile(UStringPtr string) PURE;
	//!	Parse JSON file from UTF-16.
	//!	@param		string			The UTF-8 string.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef ParseJSONFile(WStringPtr string) PURE;
	//!	Parse markup file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef ParseMarkupLangFile(IStreamReader* stream_reader) PURE;
	//!	Parse manifest file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The manifest file interface.
	virtual IManifestFilePassRef ParseManifestFile(IStreamReader* stream_reader) PURE;
	//!	Parse manifest file from stream with encryption.
	//!	@param		stream_reader	The stream reader.
	//!	@param		encryption_type	The encryption type.
	//!	@param		encryption_key	The encryption key.
	//!	@return		The manifest file interface.
	virtual IManifestFilePassRef ParseManifestFile(IStreamReader* stream_reader, _ENCRYPTION encryption_type, WStringPtr encryption_key) PURE;
	//!	Parse PSD file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@param		flags			The file flags.
	//!	@return		The file interface.
	virtual IPSDFilePassRef ParsePSDFile(IStreamReader* stream_reader, _dword flags = 0) PURE;
	//!	Parse image file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@param		file_format		The file format, _FF_UNKNOWN indicates auto detect.
	//!	@param		flags			The file flags, @see IImageFile::_FLAG.
	//!	@return		The file interface.
	virtual IImageFilePassRef ParseImageFile(IStreamReader* stream_reader, _FILE_FORMAT file_format = _FF_UNKNOWN, _dword flags = 0) PURE;
	//!	Parse sound file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@param		file_format		The file format, _FF_UNKNOWN indicates auto detect.
	//!	@param		flags			The file flags.
	//!	@return		The file interface.
	virtual ISoundFilePassRef ParseSoundFile(IStreamReader* stream_reader, _FILE_FORMAT file_format = _FF_UNKNOWN, _dword flags = 0) PURE;
	//!	Parse the compressed file.
	//!	@param		stream_reader	The stream reader.
	//!	@param		password		The password.
	//!	@param		flags			The file flags.
	//!	@return		The zip file.
	virtual IZIPFilePassRef ParseCompressedFile(IStreamReader* stream_reader, WStringPtr password = L"", _dword flags = 0) PURE;
	//!	Parse the zip file.
	//!	@param		stream_reader	The stream reader.
	//!	@param		password		The password.
	//!	@param		flags			The file flags.
	//!	@return		The zip file.
	virtual IZIPFilePassRef ParseZipFile(IStreamReader* stream_reader, WStringPtr password = L"", _dword flags = 0) PURE;
	//!	Parse the 7z file.
	//!	@param		stream_reader	The stream reader.
	//!	@param		password		The password.
	//!	@param		flags			The file flags.
	//!	@return		The 7z file.
	virtual IZIPFilePassRef Parse7zFile(IStreamReader* stream_reader, WStringPtr password = L"", _dword flags = 0) PURE;
	//!	Parse the package file.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The package file.
	virtual IZIPFilePassRef ParsePackageFile(IStreamReader* stream_reader) PURE;
	//!	Parse webm file from stream.
	//!	@param		stream_reader	The stream reader.
	//!	@return		The file interface.
	virtual IWEBMFilePassRef ParseWEBMFile(IStreamReader* stream_reader) PURE;

	//!	Create the manifest file manager.
	//!	@param		none.
	//!	@return		The manifest file manager interface.
	virtual IManifestFileManagerPassRef CreateManifestFileManager() PURE;

	//!	Create the resource loader.
	//!	@param		thread_number	The thread number for async-loading tasks.
	//!	@param		name			The resource loader name.
	//!	@param		factory			The resource factory.
	//!	@return		The resource loader interface.
	virtual IResLoaderPassRef CreateResLoader(_dword thread_number, WStringPtr name, IResLoaderFactory* factory) PURE;

public:
	//!	Create object by interface name.
	//!	@return		The object interface.
	template <typename Type>
	PassRefPtr<Type> CreateObjectPassRef() {
		STATIC_ASTROBJ_V(class_name, typeid(Type).name());

		Type* object = (Type*)CreateObject(ASTROBJ(class_name));
		return object;
	}
	//!	Create object by interface name.
	//!	@param		arguments	The arguments.
	//!	@return		The object interface.
	template <typename Type>
	PassRefPtr<Type> CreateObjectPassRef(_void* arguments) {
		STATIC_ASTROBJ_V(class_name, typeid(Type).name());

		Type* object = (Type*)CreateObject(ASTROBJ(class_name), arguments);
		return object;
	}

	//!	Create object by class name.
	//!	@param		name	The class name.
	//!	@return		The object interface.
	template <typename Type>
	PassRefPtr<Type> CreateObjectPassRef(const AStringObj& name) {
		Type* object = (Type*)CreateObject(name);
		return object;
	}
	//!	Create object with arguments by class name.
	//!	@param		name		The class name.
	//!	@param		arguments	The arguments.
	//!	@return		The object interface.
	template <typename Type>
	PassRefPtr<Type> CreateObjectPassRef(const AStringObj& name, _void* arguments) {
		Type* object = (Type*)CreateObject(name, arguments);
		return object;
	}

	//!	Create object by class ID.
	//!	@param		id	The class ID.
	//!	@return		The object interface.
	template <typename Type>
	PassRefPtr<Type> CreateObjectPassRef(_dword id) {
		Type* object = (Type*)CreateObject(id);
		return object;
	}
	//!	Create object with arguments by class ID.
	//!	@param		name		The class ID.
	//!	@param		arguments	The arguments.
	//!	@return		The object interface.
	template <typename Type>
	PassRefPtr<Type> CreateObjectPassRef(_dword id, _void* arguments) {
		Type* object = (Type*)CreateObject(id, arguments);
		return object;
	}
};

} // namespace EGE