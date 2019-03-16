//! @file     InterfaceFactory.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

#define USE_SINGLE_THREAD_ONLY 0

//----------------------------------------------------------------------------
// Helpful Structures
//----------------------------------------------------------------------------

//!	The box vertex info
struct BoxVertexInfo
{
	Vector3	mPos;
	Color	mColor;
	Vector3	mNormal;
	Vector2	mUV;
};

//----------------------------------------------------------------------------
// Helpful Macros
//----------------------------------------------------------------------------

// Create file
#define BEGIN_CREATE_FILE( ) switch ( file_format ) {
#define END_CREATE_FILE( ) default: return _null; }
#define CREATE_FILE( x )				\
	case _FF_##x:						\
	{									\
		x##File* file = new x##File( );	\
		file->SetFlags( flags );		\
		return file;					\
	}									\
	break;
#define CREATE_FILE_2( id, x )			\
	case _FF_##id:						\
	{									\
		x##File* file = new x##File( );	\
		file->SetFlags( flags );		\
		return file;					\
	}									\
	break;
#define CREATE_NULL_FILE( x )						\
	case _FF_##x:									\
	{												\
		Null##x##File* file = new Null##x##File( );	\
		file->SetFlags( flags );					\
		return file;								\
	}												\
	break;

// Create font face
#define BEGIN_FONT_FACE( ) switch ( type ) {
#define END_FONT_FACE( ) default: return _null; }
#define FONT_FACE( type_id, stream_reader, class_name )			\
	case type_id:												\
	{															\
		class_name* font_face = new class_name( );				\
		if ( font_face->Initialize( stream_reader ) == _false )	\
			{ delete font_face; return _null; }					\
																\
		return font_face;										\
	}															\
	break;

//----------------------------------------------------------------------------
// InterfaceFactory Implementation
//----------------------------------------------------------------------------

InterfaceFactory::InterfaceFactory( )
{

}

InterfaceFactory::~InterfaceFactory( )
{

}

IBaseFile* InterfaceFactory::CreateImageFile( _FILE_FORMAT file_format, _dword flags )
{
	BEGIN_CREATE_FILE( )
		CREATE_FILE( JPG )
		CREATE_FILE( GIF )
		CREATE_FILE( DDS )
		CREATE_FILE( PSD )
		CREATE_FILE( BMP )
		CREATE_FILE( PNG )
		CREATE_FILE( TGA )
 		CREATE_FILE( ASTC )
		CREATE_FILE_2( PVR_TEX, PVRTex )
		CREATE_FILE( KTX )
		CREATE_FILE( PKM )
		CREATE_FILE( WEBP )
	END_CREATE_FILE( )
}

IBaseFile* InterfaceFactory::CreateSoundFile( _FILE_FORMAT file_format, _dword flags )
{
	BEGIN_CREATE_FILE( )
		CREATE_FILE( OGG )
		CREATE_FILE( WAV )
#ifndef _EGE_DISABLE_FLAC_FILE_
		CREATE_FILE( FLAC )
#endif
#ifndef _EGE_DISABLE_MIDI_FILE_
		CREATE_FILE( MIDI )
#endif
	END_CREATE_FILE( )
}

_ubool InterfaceFactory::IsXMLFileFormat( IStreamReader* stream_reader )
{
	_byte buffer[16];
	stream_reader->PeekBuffer( buffer, sizeof( buffer ) );

	_byte* pointer = buffer;
	SKIP_UTF_CODE_WITHOUT_SIZE( pointer )

	if ( pointer[0] == '<' && pointer[1] == '?' && pointer[2] == 'x' && pointer[3] == 'm' && pointer[4] == 'l' )
		return _true;
	else
		return _false;
}

_FILE_FORMAT InterfaceFactory::GetCommonFileFormat( IStreamReader* stream_reader )
{
	return GetInterfaceFactory( )->GetCommonFileTypeFromStream( stream_reader );
}

_FILE_FORMAT InterfaceFactory::GetImageFileFormat( IStreamReader* stream_reader )
{
	return GetInterfaceFactory( )->GetImageFileTypeFromStream( stream_reader );
}

_FILE_FORMAT InterfaceFactory::GetSoundFileFormat( IStreamReader* stream_reader )
{
	return GetInterfaceFactory( )->GetSoundFileTypeFromStream( stream_reader );
}

template< typename Type, typename InterfaceType >
PassRefPtr< InterfaceType > InterfaceFactory::ParseStreamFile( IStreamReader* stream_reader, _dword flags )
{
	// Create file
	PassRefPtr< InterfaceType > file = new Type( );
	file->SetFlags( flags );

	// Load file from stream
	if ( file->LoadFromStream( stream_reader ) == _false )
		return _null;

	return file;
}

template< typename Type, InterfaceFactory::FileFormatGetFunc _GET_FUNC, InterfaceFactory::FileFormatCheckFunc _CHECK_FUNC, InterfaceFactory::CreateFileFunc _CREATE_FUNC >
PassRefPtr< Type > InterfaceFactory::ParseStreamFile( _FILE_FORMAT file_format, IStreamReader* stream_reader, _dword flags )
{
	if ( file_format == _FF_UNKNOWN )
	{
		// Auto detect the file type
		file_format = _GET_FUNC( stream_reader );
		if ( file_format == _FF_UNKNOWN || ( _CHECK_FUNC( file_format ) == _false ) )
			return _null;
	}

	// Create file
	PassRefPtr< Type > file( (Type*) _CREATE_FUNC( file_format, flags ) );
	if ( file.IsNull( ) )
		return _null;

	// Load file from stream
	if ( file->LoadFromStream( stream_reader ) == _false )
		return _null;

	return file;
}

_ubool InterfaceFactory::Initialize( )
{
	return _true;
}

_void InterfaceFactory::Finalize( )
{
	mObjectCreateWithNameFuncs.Clear( );
	mObjectCreationArgsWithNameFuncs.Clear( );

	mObjectCreateWithIDFuncs.Clear( );
	mObjectCreationArgsWithIDFuncs.Clear( );
}

IObject* InterfaceFactory::CreateObject( const AStringObj& name )
{
	const OnObjectCreateWithNameCallback* func = mObjectCreateWithNameFuncs.Search( name );
	if ( func == _null )
		return _null;

	return (*func)( );
}

IObject* InterfaceFactory::CreateObject( const AStringObj& name, _void* arguments )
{
	const OnObjectCreateArgsWithNameCallback* func = mObjectCreationArgsWithNameFuncs.Search( name );
	if ( func == _null )
		return _null;

	return (*func)( arguments );
}

IObject* InterfaceFactory::CreateObject( _dword id )
{
	const OnObjectCreateWithIDCallback* func = mObjectCreateWithIDFuncs.Search( id );
	if ( func == _null )
		return _null;

	return (*func)( );
}

IObject* InterfaceFactory::CreateObject( _dword id, _void* arguments )
{
	const OnObjectCreateArgsWithIDCallback* func = mObjectCreationArgsWithIDFuncs.Search( id );
	if ( func == _null )
		return _null;

	return (*func)( arguments );
}

_void InterfaceFactory::RegisterObjectCreationFunc( const AStringObj& name, OnObjectCreateWithNameCallback func_pointer )
{
	mObjectCreateWithNameFuncs[ name ] = func_pointer;
}

_void InterfaceFactory::RegisterObjectCreationFunc( const AStringObj& name, OnObjectCreateArgsWithNameCallback func_pointer )
{
	mObjectCreationArgsWithNameFuncs[ name ] = func_pointer;
}

_void InterfaceFactory::RegisterObjectCreationFunc( _dword id, OnObjectCreateWithIDCallback func_pointer )
{
	mObjectCreateWithIDFuncs[id] = func_pointer;
}

_void InterfaceFactory::RegisterObjectCreationFunc( _dword id, OnObjectCreateArgsWithIDCallback func_pointer )
{
	mObjectCreationArgsWithIDFuncs[id] = func_pointer;
}

IFileCopierPassRef InterfaceFactory::CreateFileCopier( )
{
	return new FileCopier( );
}

IArchivePassRef	InterfaceFactory::CreateFileArchive( WStringPtr path )
{
	return new FileArchive( path );
}

IArchivePassRef	InterfaceFactory::CreateMemArchive( WStringPtr name, IStreamReader* stream_reader, WStringPtr password, _ENCRYPTION manifest_encryption_type, WStringPtr manifest_encryption_key )
{
	MemoryArchive* archive = new MemoryArchive( );
	if ( archive->Initialize( name, stream_reader, password, manifest_encryption_type, manifest_encryption_key ) == _false )
		{ EGE_RELEASE( archive ); return _null; }

	return archive;
}

IArchivePassRef	InterfaceFactory::CreatePEResArchive( WStringPtr module_name )
{
	PEResArchive* archive = new PEResArchive( );
	if ( archive->Initialize( module_name ) == _false )
		{ EGE_RELEASE( archive ); return _null; }

	return archive;
}

IStringTablePassRef InterfaceFactory::CreateStringTable( )
{
	return new StringTable( );
}

IActionRecorderPassRef InterfaceFactory::CreateActionRecorder( )
{
	return new ActionRecorder( );
}

IInputRecorderPassRef InterfaceFactory::CreateInputRecorder( )
{
	InputRecorder* input_recorder = new InputRecorder( );
	if ( input_recorder->Initialize( ) == _false )
		{ EGE_RELEASE( input_recorder ); return _null; }

	return input_recorder;
}

IOperationRecorderPassRef InterfaceFactory::CreateOperationRecorder( _dword max_buffer_number, IOperationRecordPerformer* performer )
{
	return new OperationRecorder( max_buffer_number, performer );
}

IFontFacePassRef InterfaceFactory::CreateFontFace( _FONT_FACE_TYPE type, IStreamReader* stream_reader )
{
	BEGIN_FONT_FACE( )
		FONT_FACE( _FONT_FACE_FREETYPE2, stream_reader, FontFaceFreeType2 )
		FONT_FACE( _FONT_FACE_FNT, stream_reader, FontFaceFNT )
	END_FONT_FACE( )
}

IImageFillerPassRef InterfaceFactory::CreateImageFiller( _IMAGE_FILLTER_TYPE type, const PointU& size, const PointU& space )
{
	switch ( type )
	{
		case _IMAGE_FILLER_LINEAR:		return new ImageFillerLinear( size, space );
		case _IMAGE_FILLER_SCAN_LINES:	return new ImageFillerScanLines( size, space );
		case _IMAGE_FILLER_BINARY_TREE:	return new ImageFillerBinaryTree( size, space );
		default:
			return _null;
	}
}

IRegularExpressionPassRef InterfaceFactory::CreateRegularExpression( WStringPtr pattern )
{
	RegularExpression* reg_expression = new RegularExpression( );
	if ( reg_expression->SetPattern( pattern ) == _false )
		{ EGE_RELEASE( reg_expression ); return _null; }

	return reg_expression;
}

_ubool InterfaceFactory::BuildMD5CodeFromFile( WStringPtr filename, MD5Code& md5_code )
{
	// Create MD5 code builder
	IMD5ChecksumBuilderRef md5_code_builder = GetInterfaceFactory( )->CreateMD5ChecksumBuilder( );
	if ( md5_code_builder.IsNull( ) )
		return _false;

	// Get the MD5 code
	if ( md5_code_builder->BuildFromFile( filename, md5_code ) == _false )
		return _false;

	return _true;
}

_ubool InterfaceFactory::BuildMD5CodeFromStream( IStreamReader* stream_reader, MD5Code& md5_code )
{
	if ( stream_reader == _null )
		return _false;

	// Create MD5 code builder
	IMD5ChecksumBuilderRef md5_code_builder = GetInterfaceFactory( )->CreateMD5ChecksumBuilder( );
	if ( md5_code_builder.IsNull( ) )
		return _false;

	// Get the MD5 code
	if ( md5_code_builder->BuildFromStream( stream_reader, md5_code ) == _false )
		return _false;

	return _true;
}

MD5Code InterfaceFactory::BuildMD5CodeFromString( AStringPtr string )
{
	IStreamReaderRef stream_reader = CreateAStringStreamReader( string );
	if ( stream_reader.IsNull( ) )
		return MD5Code::cNull;

	MD5Code md5_code = MD5Code::cNull;
	if ( BuildMD5CodeFromStream( stream_reader, md5_code ) == _false )
		return MD5Code::cNull;

	return md5_code;
}

MD5Code	InterfaceFactory::BuildMD5CodeFromString( WStringPtr string )
{
	IStreamReaderRef stream_reader = CreateWStringStreamReader( string );
	if ( stream_reader.IsNull( ) )
		return MD5Code::cNull;

	MD5Code md5_code = MD5Code::cNull;
	if ( BuildMD5CodeFromStream( stream_reader, md5_code ) == _false )
		return MD5Code::cNull;

	return md5_code;
}

IMD5ChecksumBuilderPassRef InterfaceFactory::CreateMD5ChecksumBuilder( _dword chunk_size )
{
	if ( chunk_size == 0 )
		return _null;

	return new MD5ChecksumBuilder( chunk_size );
}

IProjectileObjectPassRef InterfaceFactory::CreateProjectileObjectBySpeed( const Vector3& position, const Vector3& direction, const Vector3& target, _float speed, _float height_rate )
{
	ProjectileObject* projectile_object = new ProjectileObject( );
	if ( projectile_object->InitBySpeed( position, direction, target, speed, height_rate ) == _false )
		{ EGE_RELEASE( projectile_object ); return _null; }

	return projectile_object;
}

IProjectileObjectPassRef InterfaceFactory::CreateProjectileObjectByDuration( const Vector3& position, const Vector3& direction, const Vector3& target, _dword duration, _float height_rate )
{
	ProjectileObject* projectile_object = new ProjectileObject( );
	if ( projectile_object->InitByDuration( position, direction, target, duration, height_rate ) == _false )
		{ EGE_RELEASE( projectile_object ); return _null; }

	return projectile_object;
}

IInterpolatorPassRef InterfaceFactory::CreateInterpolator( _INTERPOLATOR_TYPE interpolator_type )
{
	switch ( interpolator_type )
	{
	case _INTERPOLATOR_CURRENT:
		return new Interpolator( Interpolation::Current, Interpolation::IntegralCurrent );
	case _INTERPOLATOR_NEXT:
		return new Interpolator( Interpolation::Next, Interpolation::IntegralNext );
	case _INTERPOLATOR_MIDDLE:
		return new Interpolator( Interpolation::Middle, Interpolation::IntegralMiddle );
	case _INTERPOLATOR_LINEAR:
		return new Interpolator( Interpolation::Linear, Interpolation::IntegralLinear );

	case _INTERPOLATOR_SINE_IN:
		return new Interpolator( Interpolation::SineIn, Interpolation::IntegralSineIn );
	case _INTERPOLATOR_SINE_OUT:
		return new Interpolator( Interpolation::SineOut, Interpolation::IntegralSineOut );
	case _INTERPOLATOR_SINE_INOUT:
		return new Interpolator( Interpolation::SineInOut, Interpolation::IntegralSineInOut );
	case _INTERPOLATOR_SINE_OUTIN:
		return new Interpolator( Interpolation::SineOutIn, Interpolation::IntegralSineOutIn );

	case _INTERPOLATOR_QUAD_IN:
		return new Interpolator( Interpolation::QuadIn, Interpolation::IntegralQuadIn );
	case _INTERPOLATOR_QUAD_OUT:
		return new Interpolator( Interpolation::QuadOut, Interpolation::IntegralQuadOut );
	case _INTERPOLATOR_QUAD_INOUT:
		return new Interpolator( Interpolation::QuadInOut, Interpolation::IntegralQuadInOut );
	case _INTERPOLATOR_QUAD_OUTIN:
		return new Interpolator( Interpolation::QuadOutIn, Interpolation::IntegralQuadOutIn );

	case _INTERPOLATOR_CUBIC_IN:
		return new Interpolator( Interpolation::CubicIn, Interpolation::IntegralCubicIn );
	case _INTERPOLATOR_CUBIC_OUT:
		return new Interpolator( Interpolation::CubicOut, Interpolation::IntegralCubicOut );
	case _INTERPOLATOR_CUBIC_INOUT:
		return new Interpolator( Interpolation::CubicInOut, Interpolation::IntegralCubicInOut );
	case _INTERPOLATOR_CUBIC_OUTIN:
		return new Interpolator( Interpolation::CubicOutIn, Interpolation::IntegralCubicOutIn );

	case _INTERPOLATOR_QUART_IN:
		return new Interpolator( Interpolation::QuartIn, Interpolation::IntegralQuartIn );
	case _INTERPOLATOR_QUART_OUT:
		return new Interpolator( Interpolation::QuartOut, Interpolation::IntegralQuartOut );
	case _INTERPOLATOR_QUART_INOUT:
		return new Interpolator( Interpolation::QuartInOut, Interpolation::IntegralQuartInOut );
	case _INTERPOLATOR_QUART_OUTIN:
		return new Interpolator( Interpolation::QuartOutIn, Interpolation::IntegralQuartOutIn );

	case _INTERPOLATOR_QUINT_IN:
		return new Interpolator( Interpolation::QuintIn, Interpolation::IntegralQuintIn );
	case _INTERPOLATOR_QUINT_OUT:
		return new Interpolator( Interpolation::QuintOut, Interpolation::IntegralQuintOut );
	case _INTERPOLATOR_QUINT_INOUT:
		return new Interpolator( Interpolation::QuintInOut, Interpolation::IntegralQuintInOut );
	case _INTERPOLATOR_QUINT_OUTIN:
		return new Interpolator( Interpolation::QuintOutIn, Interpolation::IntegralQuintOutIn );

	case _INTERPOLATOR_EXPO_IN:
		return new Interpolator( Interpolation::ExpoIn, Interpolation::IntegralExpoIn );
	case _INTERPOLATOR_EXPO_OUT:
		return new Interpolator( Interpolation::ExpoOut, Interpolation::IntegralExpoOut );
	case _INTERPOLATOR_EXPO_INOUT:
		return new Interpolator( Interpolation::ExpoInOut, Interpolation::IntegralExpoInOut );
	case _INTERPOLATOR_EXPO_OUTIN:
		return new Interpolator( Interpolation::ExpoOutIn, Interpolation::IntegralExpoOutIn );

	case _INTERPOLATOR_CIRC_IN:
		return new Interpolator( Interpolation::CircIn, Interpolation::IntegralCircIn );
	case _INTERPOLATOR_CIRC_OUT:
		return new Interpolator( Interpolation::CircOut, Interpolation::IntegralCircOut );
	case _INTERPOLATOR_CIRC_INOUT:
		return new Interpolator( Interpolation::CircInOut, Interpolation::IntegralCircInOut );
	case _INTERPOLATOR_CIRC_OUTIN:
		return new Interpolator( Interpolation::CircOutIn, Interpolation::IntegralCircOutIn );

	case _INTERPOLATOR_ELASTIC_IN:
		return new Interpolator( Interpolation::ElasticIn, Interpolation::IntegralElasticIn );
	case _INTERPOLATOR_ELASTIC_OUT:
		return new Interpolator( Interpolation::ElasticOut, Interpolation::IntegralElasticOut );
	case _INTERPOLATOR_ELASTIC_INOUT:
		return new Interpolator( Interpolation::ElasticInOut, Interpolation::IntegralElasticInOut );
	case _INTERPOLATOR_ELASTIC_OUTIN:
		return new Interpolator( Interpolation::ElasticOutIn, Interpolation::IntegralElasticOutIn );

	case _INTERPOLATOR_BACK_IN:
		return new Interpolator( Interpolation::BackIn, Interpolation::IntegralBackIn );
	case _INTERPOLATOR_BACK_OUT:
		return new Interpolator( Interpolation::BackOut, Interpolation::IntegralBackOut );
	case _INTERPOLATOR_BACK_INOUT:
		return new Interpolator( Interpolation::BackInOut, Interpolation::IntegralBackInOut );
	case _INTERPOLATOR_BACK_OUTIN:
		return new Interpolator( Interpolation::BackOutIn, Interpolation::IntegralBackOutIn );

	case _INTERPOLATOR_BOUNCE_IN:
		return new Interpolator( Interpolation::BounceIn, Interpolation::IntegralBounceIn );
	case _INTERPOLATOR_BOUNCE_OUT:
		return new Interpolator( Interpolation::BounceOut, Interpolation::IntegralBounceOut );
	case _INTERPOLATOR_BOUNCE_INOUT:
		return new Interpolator( Interpolation::BounceInOut, Interpolation::IntegralBounceInOut );
	case _INTERPOLATOR_BOUNCE_OUTIN:
		return new Interpolator( Interpolation::BounceOutIn, Interpolation::IntegralBounceOutIn );
	}

	return _null;
}

IMeasurableObjectPassRef InterfaceFactory::CreateMeasurableObj( const Vector2& size )
{
	return new MeasurableObject( size );
}

IAlignerPassRef InterfaceFactory::CreateAligner( )
{
	return new Aligner( );
}

ICommandLineParserPassRef InterfaceFactory::CreateCommandLineParser( )
{
	return new CommandLineParser( "" );
}

ICommandLineParserPassRef InterfaceFactory::CreateCommandLineParser( AStringPtr cmdline )
{
	return new CommandLineParser( cmdline );
}

ICommandLineParserPassRef InterfaceFactory::CreateCommandLineParser( WStringPtr cmdline )
{
	return new CommandLineParser( cmdline );
}

ICommandLineParserPassRef InterfaceFactory::CreateCommandLineParser( _dword argc, const _chara* argv[] )
{
	return new CommandLineParser( argc, argv );
}

ICommandLineParserPassRef InterfaceFactory::CreateCommandLineParser( _dword argc, const _charw* argv[] )
{
	return new CommandLineParser( argc, argv );
}

ICommandLineParserPassRef InterfaceFactory::CreateCommandLineParser( _dword argc, const _chara* argn[], const _chara* argv[] )
{
	return new CommandLineParser( argc, argn, argv );
}

ICommandLineParserPassRef InterfaceFactory::CreateCommandLineParser( _dword argc, const _charw* argn[], const _charw* argv[] )
{
	return new CommandLineParser( argc, argn, argv );
}

IPropertiesPassRef InterfaceFactory::CreateProperties( )
{
	return new Properties( );
}

IProtoBufMessageProcessorPassRef InterfaceFactory::CreateProtoBufMessageProcessor( )
{
	return new ProtoBufMessageProcessor( );
}

IProtoBufProcessorPassRef InterfaceFactory::CreateProtoBufProcessor( )
{
	return new ProtoBufProcessor( );
}

ILoggerPassRef InterfaceFactory::CreateLogger( )
{
	return new Logger( );
}

ILoggerPassRef InterfaceFactory::CreateFileLogger( WStringPtr app_name )
{
	FileLogger* logger = new FileLogger( );
	if ( logger->Initialize( app_name ) == _false )
		{ EGE_RELEASE( logger ); return _null; }

	return logger;
}

IAllocatorPassRef InterfaceFactory::CreateStdAllocator( _dword arrange_size )
{
	return new StdAllocator( arrange_size );
}

IAllocatorPassRef InterfaceFactory::CreateMemAllocator( _dword page_size, _dword min_chunk_size, _dword arrange_size )
{
	MemAllocator* allocator = new MemAllocator( arrange_size );
	if ( allocator->Create( page_size, min_chunk_size ) == _false )
		{ EGE_RELEASE( allocator ); return _null; }

	return allocator;
}

IStackAllocatorPassRef InterfaceFactory::CreateStackAllocator( _dword size, _dword arrange_size )
{
	StackAllocator* allocator = new StackAllocator( arrange_size );
	if ( allocator->Create( size ) == _false )
		{ EGE_RELEASE( allocator ); return _null; }

	return allocator;
}

IRingAllocatorPassRef InterfaceFactory::CreateRingAllocator( _dword size, _dword arrange_size )
{
	RingAllocator* allocator = new RingAllocator( arrange_size );
	if ( allocator->Create( size ) == _false )
		{ EGE_RELEASE( allocator ); return _null; }

	return allocator;
}

ILinearAllocatorPassRef InterfaceFactory::CreateLinearAllocator( _byte* buffer, _dword size, _dword arrange_size )
{
	LinearAllocator* allocator = new LinearAllocator( arrange_size );
	if ( allocator->Create( buffer, size ) == _false )
		{ EGE_RELEASE( allocator ); return _null; }

	return allocator;
}

IRangeAllocatorPassRef InterfaceFactory::CreateRangeAllocator( _dword size, _dword arrange_size )
{
	RangeAllocator* allocator = new RangeAllocator( );
	if ( allocator->Create( size, arrange_size ) == _false )
		{ EGE_RELEASE( allocator ); return _null; }

	return allocator;
}

IBufferAllocatorPassRef InterfaceFactory::CreateBufferAllocator( _dword size, _dword arrange_size )
{
	BufferAllocator* allocator = new BufferAllocator( );
	if ( allocator->Create( size, arrange_size ) == _false )
		{ EGE_RELEASE( allocator ); return _null; }

	return allocator;
}

IOffsetAllocatorPassRef InterfaceFactory::CreateOffsetAllocator( _dword size, _dword arrange_size )
{
	OffsetAllocator* allocator = new OffsetAllocator( );
	if ( allocator->Create( size, arrange_size ) == _false )
		{ EGE_RELEASE( allocator ); return _null; }

	return allocator;
}

ICacheBufferPassRef InterfaceFactory::CreateCacheBuffer( _dword buffer_size, _dword cache_size, ICacheBufferNotifier* notifier )
{
	CacheBuffer* cache_buffer = new CacheBuffer( );
	if ( cache_buffer->Initialize( buffer_size, cache_size, notifier ) == _false )
		{ EGE_RELEASE( cache_buffer ); return _null; }

	return cache_buffer;
}

IStreamReaderPassRef InterfaceFactory::CreateMemStreamReader( const _byte* buffer, _dword size, _STREAM_SHARE_MODE share_mode )
{
	return new MemStreamReader( buffer, size, share_mode );
}

IStreamWriterPassRef InterfaceFactory::CreateMemStreamWriter( )
{
	return new MemStreamWriter( 1, 0 );
}

IStreamWriterPassRef InterfaceFactory::CreateMemStreamWriter( _dword size )
{
	return new MemStreamWriter( size, 0 );
}

IStreamWriterPassRef InterfaceFactory::CreateMemStreamWriter( _dword size, _dword grow_size )
{
	return new MemStreamWriter( size, grow_size );
}

IStreamWriterPassRef InterfaceFactory::CreateMemStreamWriter( _byte* buffer, _dword size, _STREAM_SHARE_MODE share_mode )
{
	return new MemStreamWriter( buffer, size, share_mode );
}

IStreamReaderPassRef InterfaceFactory::CreateBitStreamReader( const _byte* buffer, _dword size, _STREAM_SHARE_MODE share_mode )
{
	return new BitStreamReader( buffer, size, share_mode );
}

IStreamWriterPassRef InterfaceFactory::CreateBitStreamWriter( _dword size )
{
	return new BitStreamWriter( size );
}

IStreamReaderPassRef InterfaceFactory::CreateAStringStreamReader( AStringPtr string )
{
	return new AStringStreamReader( string );
}

IStreamReaderPassRef InterfaceFactory::CreateUStringStreamReader( UStringPtr string )
{
	return new UStringStreamReader( string );
}

IStreamReaderPassRef InterfaceFactory::CreateWStringStreamReader( WStringPtr string )
{
	return new WStringStreamReader( string );
}

IFileStreamReaderPassRef InterfaceFactory::CreateFileStreamReader( WStringPtr filename )
{
	FileStreamReader* stream = new FileStreamReader( );
	if ( stream->Initialize( L"", filename ) == _false )
		{ EGE_RELEASE( stream ); return _null; }

	return stream;
}

IFileStreamWriterPassRef InterfaceFactory::CreateFileStreamWriter( WStringPtr filename )
{
	FileStreamWriter* stream = new FileStreamWriter( );
	if ( stream->Initialize( L"", filename ) == _false )
		{ EGE_RELEASE( stream ); return _null; }

	return stream;
}

IStreamReaderPassRef InterfaceFactory::CreateSafeStreamReader( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _null;

	return new SafeStreamReader( stream_reader );
}

IStreamProcessorPassRef	InterfaceFactory::CreateStreamWriterProcessor( )
{
	return new StreamWriterProcessor( MD5Code::cNull );
}

IStreamProcessorPassRef	InterfaceFactory::CreateStreamWriterProcessor( const MD5Code& md5_code )
{
	return new StreamWriterProcessor( md5_code );
}

IThreadPoolPassRef InterfaceFactory::CreateThreadPool( _dword thread_number, WStringPtr name )
{
#if (USE_SINGLE_THREAD_ONLY == 1)
	return new SingleThreadPool( );
#else
	ThreadPool* thread_pool = new ThreadPool( );
	if ( thread_pool->Create( thread_number, name ) == _false )
		{ EGE_RELEASE( thread_pool ); return _null; }

	return thread_pool;
#endif
}

IThreadPoolPassRef InterfaceFactory::CreateSingleThreadPool( )
{
	return new SingleThreadPool( );
}

ITransactionManagerPassRef InterfaceFactory::CreateTransactionManager( _dword thread_number, WStringPtr name )
{
	TransactionManager* transaction_manager = new TransactionManager( );
	if ( transaction_manager->Create( thread_number, name ) == _false )
		{ EGE_RELEASE( transaction_manager ); return _null; }

	return transaction_manager;
}

ISerializableNodePassRef InterfaceFactory::CreateXMLSerializableNode( )
{
	IMarkupLangFileRef xml_file = CreateXMLFile( );
	if ( xml_file.IsNull( ) )
		return _null;

	return CreateMarkupLangSerializableNode( xml_file );
}

ISerializableNodePassRef InterfaceFactory::CreateXMLSerializableNode( AStringPtr string )
{
	UString string_utf8;
	string_utf8.FromString( string );

	return CreateXMLSerializableNode( string_utf8 );
}

ISerializableNodePassRef InterfaceFactory::CreateXMLSerializableNode( UStringPtr string )
{
	IMarkupLangFileRef xml_file = ParseXMLFile( CreateUStringStreamReader( string ).GetPtr( ) );
	if ( xml_file.IsNull( ) )
		return _null;

	return CreateMarkupLangSerializableNode( xml_file );
}

ISerializableNodePassRef InterfaceFactory::CreateXMLSerializableNode( WStringPtr string )
{
	UString string_utf8;
	string_utf8.FromString( string );

	return CreateXMLSerializableNode( string_utf8 );
}

ISerializableNodePassRef InterfaceFactory::CreateJSONSerializableNode( )
{
	IMarkupLangFileRef json_file = CreateJSONFile( );
	if ( json_file.IsNull( ) )
		return _null;

	return CreateMarkupLangSerializableNode( json_file );
}

ISerializableNodePassRef InterfaceFactory::CreateJSONSerializableNode( AStringPtr string )
{
	UString string_utf8;
	string_utf8.FromString( string );

	return CreateJSONSerializableNode( string_utf8 );
}

ISerializableNodePassRef InterfaceFactory::CreateJSONSerializableNode( UStringPtr string )
{
	IMarkupLangFileRef json_file = ParseJSONFile( string );
	if ( json_file.IsNull( ) )
		return _null;

	return CreateMarkupLangSerializableNode( json_file );
}

ISerializableNodePassRef InterfaceFactory::CreateJSONSerializableNode( WStringPtr string )
{
	UString string_utf8;
	string_utf8.FromString( string );

	return CreateJSONSerializableNode( string_utf8 );
}

ISerializableNodePassRef InterfaceFactory::CreateMarkupLangSerializableNode( AStringPtr string )
{
	return CreateMarkupLangSerializableNode( CreateAStringStreamReader( string ).GetPtr( ) );
}

ISerializableNodePassRef InterfaceFactory::CreateMarkupLangSerializableNode( UStringPtr string )
{
	return CreateMarkupLangSerializableNode( CreateUStringStreamReader( string ).GetPtr( ) );
}

ISerializableNodePassRef InterfaceFactory::CreateMarkupLangSerializableNode( WStringPtr string )
{
	UString string_utf8;
	string_utf8.FromString( string );

	return CreateMarkupLangSerializableNode( string_utf8 );
}

ISerializableNodePassRef InterfaceFactory::CreateMarkupLangSerializableNode( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _null;

	IMarkupLangFileRef markup_lang_file = ParseMarkupLangFile( stream_reader );
	if ( markup_lang_file.IsNull( ) )
		return _null;

	return CreateMarkupLangSerializableNode( markup_lang_file );
}

ISerializableNodePassRef InterfaceFactory::CreateMarkupLangSerializableNode( IMarkupLangFile* file )
{
	if ( file == _null )
	{
		WLOG_ERROR( L"The markup language file is null, create markup language serializable node failed" );
		return _null;
	}

	// Get the root element
	IMarkupLangElement* root_element = file->GetRootElement( );
	if ( root_element == _null )
		return _null;

	// Locate at root element
	return new MarkupLangSerializableNode( root_element, file );
}

ISerializableNodePassRef InterfaceFactory::CreateMarkupLangSerializableNode( IMarkupLangElement* element, IMarkupLangFile* file )
{
	if ( element == _null )
	{
		WLOG_ERROR( L"The markup element is null, create markup language serializable node failed" );
		return _null;
	}

	if ( file == _null )
	{
		WLOG_ERROR( L"The markup language file is null, create markup language serializable node failed" );
		return _null;
	}

	return new MarkupLangSerializableNode( element, file );
}

ICompressionEncoderPassRef InterfaceFactory::CreateCompressionEncoder( _COMPRESSION type )
{
	switch ( type )
	{
		case _COMPRESSION_ZLIB:	return new CompressionEncoderZLIB( );
		default:
			return _null;
	}
}

ICompressionDecoderPassRef InterfaceFactory::CreateCompressionDecoder( _COMPRESSION type )
{
	switch ( type )
	{
		case _COMPRESSION_ZLIB:	return new CompressionDecoderZLIB( );
		default:
			return _null;
	}
}

IStreamReaderPassRef InterfaceFactory::CompressBuffer( _COMPRESSION type, _dword size, const _byte* buffer )
{
	ICompressionEncoderRef encoder = CreateCompressionEncoder( type );
	if ( encoder.IsNull( ) )
		return _null;

	IStreamWriterRef stream_writer = GetInterfaceFactory( )->CreateMemStreamWriter( );
	if ( stream_writer.IsNull( ) )
		return _null;

	_dword output_size = 0;
	if ( encoder->Process( buffer, size, stream_writer, 64 KB, output_size ) == _false )
		return _null;

	return GetInterfaceFactory( )->CreateMemStreamReader( stream_writer->GetBuffer( ), stream_writer->GetOffset( ), _STREAM_SHARE_MODE_NONE );
}

IStreamReaderPassRef InterfaceFactory::DecompressBuffer( _COMPRESSION type, _dword size, const _byte* buffer )
{
	ICompressionDecoderRef decoder = CreateCompressionDecoder( type );
	if ( decoder.IsNull( ) )
		return _null;

	IStreamWriterRef stream_writer = GetInterfaceFactory( )->CreateMemStreamWriter( );
	if ( stream_writer.IsNull( ) )
		return _null;

	_dword output_size = 0;
	if ( decoder->Process( buffer, size, stream_writer, 64 KB, output_size ) == _false )
		return _null;

	return GetInterfaceFactory( )->CreateMemStreamReader( stream_writer->GetBuffer( ), stream_writer->GetOffset( ), _STREAM_SHARE_MODE_NONE );
}

IAudioDecoderPassRef InterfaceFactory::CreateOGGDecoder( const SoundVorbisFormatInfo* info )
{
	OGGDecoder* decoder = new OGGDecoder( );
	if ( decoder->Initialize( info ) == _false )
		{ EGE_RELEASE( decoder ); return _null; }

	return decoder;
}

IEncryptorPassRef InterfaceFactory::CreateEncryptor( _ENCRYPTION type, AStringPtr key )
{
	IEncryptor* encryptor = _null;

	switch ( type )
	{
		case _ENCRYPTION_UNKNOWN:	return _null;
		case _ENCRYPTION_DES:		encryptor = new DESEncryptor( ); break;
		case _ENCRYPTION_AES:		encryptor = new AESEncryptor( ); break;
		default:
			return _null;
	}

	if ( encryptor->SetKey( key ) == _false )
		{ EGE_RELEASE( encryptor ); return _null; }

	return encryptor;
}

IDecryptorPassRef InterfaceFactory::CreateDecryptor( _ENCRYPTION type, AStringPtr key )
{
	IDecryptor* decryptor = _null;

	switch ( type )
	{
		case _ENCRYPTION_UNKNOWN:	return _null;
		case _ENCRYPTION_DES:		decryptor = new DESDecryptor( ); break;
		case _ENCRYPTION_AES:		decryptor = new AESDecryptor( ); break;
		default:
			return _null;
	}

	if ( decryptor->SetKey( key ) == _false )
		{ EGE_RELEASE( decryptor ); return _null; }

	return decryptor;
}

_ubool InterfaceFactory::EncryptFile( WStringPtr source_filename, WStringPtr target_filename, _ENCRYPTION type, AStringPtr key )
{
	// Open the source file
	File file;
	if ( file.Open( source_filename, _FILE_OPEN_EXISTING, _FILE_OPERATION_READ ) == _false )
		return _false;

	// Get the file size
	_dword source_file_size = file.GetSize( );
	if ( source_file_size == 0 )
		return _false;

	// Read the file data
	MemArrayPtr< _byte > source_file_data( source_file_size );
	file.ReadBuffer( source_file_data, source_file_size );

	// Close file
	file.Close( );

	// Create encryptor
	IEncryptorRef encryptor = GetInterfaceFactory( )->CreateEncryptor( type, key );
	if ( encryptor.IsNull( ) )
		return _false;

	// Start to encrypt
	encryptor->ProcessBuffer( source_file_size, source_file_data );

	// Save to file
	if ( FileSystem::CreateFile( target_filename, encryptor->GetProcessedBufferSize( ), encryptor->GetProcessedBufferData( ) ) == _false )
		return _false;

	return _true;
}

_ubool InterfaceFactory::DecryptFile( WStringPtr source_filename, WStringPtr target_filename, _ENCRYPTION type, AStringPtr key )
{
	// Open the source file
	File file;
	if ( file.Open( source_filename, _FILE_OPEN_EXISTING, _FILE_OPERATION_READ ) == _false )
		return _false;

	// Get the file size
	_dword source_file_size = file.GetSize( );
	if ( source_file_size == 0 )
		return _false;

	// Read the file data
	MemArrayPtr< _byte > source_file_data( source_file_size );
	file.ReadBuffer( source_file_data, source_file_size );

	// Close file
	file.Close( );

	// Create decryptor
	IDecryptorRef decryptor = GetInterfaceFactory( )->CreateDecryptor( type, key );
	if ( decryptor.IsNull( ) )
		return _false;

	// Start to decrypt
	decryptor->ProcessBuffer( source_file_size, source_file_data );

	// Save to file
	if ( FileSystem::CreateFile( target_filename, decryptor->GetProcessedBufferSize( ), decryptor->GetProcessedBufferData( ) ) == _false )
		return _false;

	return _true;
}

IStreamReaderPassRef InterfaceFactory::EncryptStream( IStreamReader* stream_reader, _ENCRYPTION type, AStringPtr key )
{
	if ( stream_reader == _null )
		return _null;

	// Get the file size
	_dword source_file_size = stream_reader->GetSize( );
	if ( source_file_size == 0 )
		return _null;

	// Read the file data
	MemArrayPtr< _byte > source_file_data( source_file_size );
	stream_reader->ReadBuffer( source_file_data, source_file_size );

	// Create encryptor
	IEncryptorRef encryptor = GetInterfaceFactory( )->CreateEncryptor( type, key );
	if ( encryptor.IsNull( ) )
		return _null;

	// Start to encrypt
	encryptor->ProcessBuffer( source_file_size, source_file_data );

	// Create stream reader
	return GetInterfaceFactory( )->CreateMemStreamReader( encryptor->GetProcessedBufferData( ), encryptor->GetProcessedBufferSize( ), _STREAM_SHARE_MODE_NONE );
}

IStreamReaderPassRef InterfaceFactory::DecryptStream( IStreamReader* stream_reader, _ENCRYPTION type, AStringPtr key )
{
	if ( stream_reader == _null )
		return _null;

	// Get the file size
	_dword source_file_size = stream_reader->GetSize( );
	if ( source_file_size == 0 )
		return _null;

	// Read the file data
	MemArrayPtr< _byte > source_file_data( source_file_size );
	stream_reader->ReadBuffer( source_file_data, source_file_size );

	// Create decryptor
	IDecryptorRef decryptor = GetInterfaceFactory( )->CreateDecryptor( type, key );
	if ( decryptor.IsNull( ) )
		return _null;

	// Start to decrypt
	decryptor->ProcessBuffer( source_file_size, source_file_data );

	// Create stream reader
	return GetInterfaceFactory( )->CreateMemStreamReader( decryptor->GetProcessedBufferData( ), decryptor->GetProcessedBufferSize( ), _STREAM_SHARE_MODE_NONE );
}

_FILE_FORMAT InterfaceFactory::GetCommonFileTypeFromStream( IStreamReader* stream_reader ) const
{
	if ( stream_reader == _null )
		return _FF_UNKNOWN;

	// Read the file unique ID
	_dword file_format = 0;
	stream_reader->PeekBuffer( &file_format, sizeof( _dword ) );

	// Check the file unique ID
	switch ( file_format )
	{
		// Binary xml file
		case BinaryXMLFile::_FILE_ID:
			return _FF_BXML;

		// Binary geometry file
		case GeometryFile::_FILE_ID:
			return _FF_GEOMETRY;

		// 7z file
		case SZFile::_FILE_ID:
			return _FF_7Z;

		// Zip file
		case ZIPFile::_FILE_ID:
			return _FF_ZIP;

		default:
			break;
	}

	// Unknown File
	return _FF_UNKNOWN;
}

_FILE_FORMAT InterfaceFactory::GetImageFileTypeFromStream( IStreamReader* stream_reader ) const
{
	if ( stream_reader == _null )
		return _FF_UNKNOWN;

	// Read the file unique ID
	_dword file_format = 0;
	stream_reader->PeekBuffer( &file_format, sizeof( _dword ) );

	// Check the file unique ID
	switch ( file_format )
	{
		// PSD Image File
		case PSDFile::_FILE_ID: 
			return _FF_PSD;

		// PNG Image File
		case PNGFile::_FILE_ID: 
			return _FF_PNG;

		// DDS Image File
		case DDSFile::_FILE_ID: 
			return _FF_DDS;

		// GIF Image File
		case GIFFile::_FILE_ID:
			return _FF_GIF;

		// TGA Image file
		case 0x00020000:
		case 0x00030000:
		case 0x000A0000:
			return _FF_TGA;

 		// ASTC Image File
 		case ASTCFile::_FILE_ID:
 			return _FF_ASTC;

		// PVRTex Image File
		case PVRTexFile::_FILE_ID: 
			return _FF_PVR_TEX;

		// KTX Image File
		case KTXFile::_FILE_ID: 
			return _FF_KTX;

		// ETC Image File
		case PKMFile::_FILE_ID: 
			return _FF_PKM;

		// WEBP Image File
		case WEBPFile::_FILE_ID: 
			return _FF_WEBP;

		default:
			break;
	}

	// JFIF Image File (http://blog.csdn.net/kickxxx/article/details/8173332)
	_dword jpg_file_id = file_format & 0x0000FFFF;
	if ( jpg_file_id == 0xD8FF )
		return _FF_JPG;

	// Unknown File
	return _FF_UNKNOWN;
}

_FILE_FORMAT InterfaceFactory::GetSoundFileTypeFromStream( IStreamReader* stream_reader ) const
{
	if ( stream_reader == _null )
		return _FF_UNKNOWN;

	// Read the file unique ID
	_dword file_format = 0;
	stream_reader->PeekBuffer( &file_format, sizeof( _dword ) );

	// Check the file unique ID
	switch ( file_format )
	{
		// WAV Sound File
		case WAVFile::_FILE_ID: 
			return _FF_WAV;

		// OGG Sound File
		case OGGFile::_FILE_ID: 
			return _FF_OGG;

#ifndef _EGE_DISABLE_MIDI_FILE_
		// MIDI Sound File
		case MIDIFile::_FILE_ID: 
			return _FF_MIDI;
#endif

		default:
			break;
	}

	// Unknown File
	return _FF_UNKNOWN;
}

IMarkupLangFilePassRef InterfaceFactory::CreateXMLFile( )
{
	XMLFile* xml_file = new XMLFile( );
	xml_file->InitXMLDocument( );

	return xml_file;
}

IMarkupLangFilePassRef InterfaceFactory::CreateXMLFile( WStringPtr root_name, _ENCODING encoding, const Version& version )
{
	XMLFile* xml_file = new XMLFile( );
	xml_file->InitXMLDocument( );

	// Get the declaration
	IMarkupLangDeclaration* declaration = xml_file->GetDeclaration( );
	if ( declaration == _null )
		{ EGE_RELEASE( xml_file ); return _null; }

	// Set the version info
	declaration->SetEncoding( encoding );
	declaration->SetVersion( version );
	
	// Set the root name
	if ( xml_file->GetRootElement( )->SetName( root_name ) == _false )
		{ EGE_RELEASE( xml_file ); return _null; }

	return xml_file;
}

IMarkupLangFilePassRef InterfaceFactory::CreateXMLFile( const ISerializableNode* node, _ENCODING encoding, const Version& version )
{
	if ( node == _null || node->HasObject( ) == _false )
		return _null;

	// Get the XML element
	const IMarkupLangElement* xml_element = node->GetMarkupLangElement( );
	if ( xml_element == _null )
		return _null;

	// Get the node name
	WString node_name = node->GetNodeName( );

	// Create XML file
	IMarkupLangFilePassRef xml_file = CreateXMLFile( node_name, encoding, version );
	if ( xml_file.IsNull( ) )
		return _null;

	// Get the root of element
	IMarkupLangElement* root_element = xml_file->GetRootElement( );
	if ( root_element == _null )
		return _null;

	// Set all attributes of root element
	for ( _dword i = 0; i < xml_element->GetAttributesNumber( ); i ++ )
	{
		IMarkupLangAttribute* attribute = xml_element->GetAttributeByIndex( i );
		EGE_ASSERT( attribute != _null );

		WString attribute_name	= attribute->GetName( );
		WString attribute_value = attribute->GetStringW( );

		if ( root_element->SetAttributeString( attribute_name, attribute_value ) == _false )
			return _null;
	}

	// Insert all childs to root
	const IMarkupLangElement* child_element = xml_element->GetFirstChildElement( );
	for ( ; child_element != _null; child_element = child_element->GetNextElement( ) )
	{
		if ( root_element->InsertChildElement( child_element, _true ) == _null )
			return _null;
	}

	return xml_file;
}

IMarkupLangFilePassRef InterfaceFactory::CreateBXMLFile( IMarkupLangFile* markup_file )
{
	if ( markup_file == _null )
		return _null;

	BinaryXMLFile* xml_file = new BinaryXMLFile( );
	if ( xml_file->LoadFromMarkupFile( markup_file ) == _false )
		{ EGE_RELEASE( xml_file ); return _null; }

	return xml_file;
}

IMarkupLangFilePassRef InterfaceFactory::CreateJSONFile( )
{
	return new JSONFile( );
}

IManifestFilePassRef InterfaceFactory::CreateManifestFile( )
{
	return new ManifestFile( );
}

IGeometryFilePassRef InterfaceFactory::CreateGeometryFile( )
{
	return new GeometryFile( );
}

IGeometryMeshChunkPassRef InterfaceFactory::CreateGeometryMeshChunk( _dword vertex_type, const _byte* vb_data, _dword vb_size, const _word* ib_data, _dword ib_size )
{
	if ( vertex_type == 0 || vb_data == _null || vb_size == 0 || ib_data == _null || ib_size == 0 )
		return _null;

	return new GeometryMeshChunk( vertex_type, vb_data, vb_size, ib_data, ib_size );
}

IGeometryMeshChunkPassRef InterfaceFactory::CreateBoxGeometryMeshChunk( const Vector3& min_vector, const Vector3& max_vector )
{
	Box box( min_vector, max_vector );

	BoxVertexInfo vertices[8];

	for ( _dword i = 0; i < 8; i ++ )
	{
		vertices[i].mPos = box.mVectors[i];
		vertices[i].mColor = Color::cWhite;
	}

	vertices[0].mNormal = Vector3::cXAxis;
	vertices[1].mNormal = Vector3::cXAxis;
	vertices[2].mNormal = -Vector3::cXAxis;
	vertices[3].mNormal = -Vector3::cXAxis;
	vertices[4].mNormal = Vector3::cXAxis;
	vertices[5].mNormal = Vector3::cXAxis;
	vertices[6].mNormal = -Vector3::cXAxis;
	vertices[7].mNormal = -Vector3::cXAxis;

	vertices[0].mUV = Vector2( 0.0f, 0.0f );
	vertices[1].mUV = Vector2( 0.0f, 0.0f );
	vertices[2].mUV = Vector2( 0.0f, 0.0f );
	vertices[3].mUV = Vector2( 0.0f, 0.0f );
	vertices[4].mUV = Vector2( 0.0f, 0.0f );
	vertices[5].mUV = Vector2( 0.0f, 0.0f );
	vertices[6].mUV = Vector2( 0.0f, 0.0f );
	vertices[7].mUV = Vector2( 0.0f, 0.0f );

	WordArray indices;
	indices.Append( 0 ); indices.Append( 1 ); indices.Append( 4 ); 
	indices.Append( 4 ); indices.Append( 1 ); indices.Append( 5 ); 
	indices.Append( 1 ); indices.Append( 3 ); indices.Append( 5 ); 
	indices.Append( 5 ); indices.Append( 3 ); indices.Append( 7 ); 
	indices.Append( 2 ); indices.Append( 3 ); indices.Append( 6 ); 
	indices.Append( 6 ); indices.Append( 3 ); indices.Append( 7 ); 
	indices.Append( 0 ); indices.Append( 2 ); indices.Append( 4 ); 
	indices.Append( 4 ); indices.Append( 2 ); indices.Append( 6 ); 
	indices.Append( 0 ); indices.Append( 1 ); indices.Append( 2 ); 
	indices.Append( 2 ); indices.Append( 1 ); indices.Append( 3 ); 
	indices.Append( 4 ); indices.Append( 5 ); indices.Append( 6 ); 
	indices.Append( 6 ); indices.Append( 5 ); indices.Append( 7 ); 

	_dword vertex_type = _GVT_POS | _GVT_COLOR0 | _GVT_NORMAL | _GVT_UV1;

	return CreateGeometryMeshChunk( vertex_type, (const _byte*)vertices, sizeof( vertices ), indices.GetBuffer( ), indices.Number( ) * sizeof( _word ) );
}

IImageFilePassRef InterfaceFactory::CreateImageFile( _FILE_FORMAT file_format, _dword width, _dword height, _PIXEL_FORMAT pixelformat, const _void* pixelbuffer )
{
	// Check the file format
	if ( IsImageFileFormat( file_format ) == _false )
		return _null;

	// Create image file
	IImageFilePassRef image_file = (IImageFile*) CreateImageFile( file_format, 0 );
	if ( image_file.IsNull( ) )
		return _null;

	// Set the image pixel buffer
	if ( image_file->Create( width, height, pixelformat, (const _byte*) pixelbuffer ) == _false )
		return _null;

	return image_file;
}

ISoundFileWriterPassRef InterfaceFactory::CreateSoundFileWriter( _FILE_FORMAT file_format )
{
	switch ( file_format )
	{
		case _FF_WAV: return new WAVFileWriter( );
		case _FF_OGG: return new OGGFileWriter( );
		default:
			break;
	}

	return _null;
}

IStreamingPCMFilePassRef InterfaceFactory::CreateStreamingPCMFile( const SoundHeaderInfo& info )
{
	StreamingPCMFile* file = new StreamingPCMFile( );
	if ( file->Initialize( info ) == _false )
		{ EGE_RELEASE( file ); return _null; }

	return file;
}

IZIPFilePassRef InterfaceFactory::CreateZipFile( WStringPtr filename, WStringPtr password )
{
	ZIPFile* zip_file = new ZIPFile( password );
	if ( zip_file->CreateFile( filename ) == _false )
		{ EGE_RELEASE( zip_file ); return _null; }

	return zip_file;
}

IZIPFilePassRef InterfaceFactory::Create7zFile( WStringPtr filename, WStringPtr password )
{
	SZFile* sz_file = new SZFile( password );
	if ( sz_file->CreateFile( filename ) == _false )
		{ EGE_RELEASE( sz_file ); return _null; }

	return sz_file;
}

IZIPFilePassRef	InterfaceFactory::CreatePackageFile( WStringPtr filename )
{
	PackageFile* package_file = new PackageFile( );
	if ( package_file->CreateFile( filename ) == _false )
		{ EGE_RELEASE( package_file ); return _null; }

	return package_file;
}

_ubool InterfaceFactory::SaveImageFile( _FILE_FORMAT file_format, _PIXEL_FORMAT pixelformat, WStringPtr filename, IImageFile* image )
{
	if ( IsImageFileFormat( file_format ) == _false || filename.IsEmpty( ) || image == _null )
		return _false;

	// Create image file prepare to save it
	IImageFileRef save_image = CreateImageFile( file_format, image->GetWidth( ), image->GetHeight( ), pixelformat, image->GetPixelBuffer( ) );
	if ( save_image.IsNull( ) )
		return _false;

	// Save image file
	return save_image->SaveToFile( filename );
}

IFNTFilePassRef InterfaceFactory::ParseFNTFile( IStreamReader* stream_reader )
{
	return ParseStreamFile< FNTFile, IFNTFile >( stream_reader );
}

ICSVFilePassRef	InterfaceFactory::ParseCSVFile( IStreamReader* stream_reader )
{
#ifndef _EGE_DISABLE_CSV_FILE_
	return ParseStreamFile< CSVFile, ICSVFile >( stream_reader );
#else
	return new NullCSVFile( );
#endif
}

IGeometryFilePassRef InterfaceFactory::ParseGeometryFile( IStreamReader* stream_reader )
{
	return ParseStreamFile< GeometryFile, IGeometryFile >( stream_reader );
}

IMarkupLangFilePassRef InterfaceFactory::ParseXMLFile( IStreamReader* stream_reader )
{
	if ( this->GetCommonFileTypeFromStream( stream_reader ) == _FF_BXML )
		return ParseStreamFile< BinaryXMLFile, IMarkupLangFile >( stream_reader );	

	return ParseStreamFile< XMLFile, IMarkupLangFile >( stream_reader );
}

IMarkupLangFilePassRef InterfaceFactory::ParseXMLFile( IStreamReader* stream_reader, _ENCRYPTION encryption_type, AStringPtr encryption_key )
{
	if ( stream_reader == _null )
		return _null;

	// If it's xml format then skip to decrypt
	if ( IsXMLFileFormat( stream_reader ) )
	{
		return ParseXMLFile( stream_reader );
	}
	// Load manifest file with encryption
	else
	{
		IDecryptorRef decryptor = GetInterfaceFactory( )->CreateDecryptor( encryption_type, encryption_key );
		if ( decryptor.IsNull( ) )
			return _null;

		if ( decryptor->ProcessBuffer( stream_reader->GetSize( ), stream_reader->GetBuffer( ) ) == _false )
			return _null;

		AString manifest_string( (const _chara*) decryptor->GetProcessedBufferData( ), decryptor->GetProcessedBufferSize( ) );
		IStreamReaderRef manifest_stream_reader = GetInterfaceFactory( )->CreateAStringStreamReader( manifest_string );
		if ( manifest_stream_reader.IsNull( ) )
			return _null;

		return ParseXMLFile( manifest_stream_reader );
	}
}

IHTMLFilePassRef InterfaceFactory::ParseHTMLFile( IStreamReader* stream_reader )
{
#ifndef _EGE_DISABLE_HTML_FILE_
	return ParseStreamFile< HTMLFile, IHTMLFile >( stream_reader );
#else
	return _null;
#endif
}

IMarkupLangFilePassRef InterfaceFactory::ParseJSONFile( IStreamReader* stream_reader )
{
	return ParseStreamFile< JSONFile, IMarkupLangFile >( stream_reader );
}

IMarkupLangFilePassRef InterfaceFactory::ParseJSONFile( AStringPtr string )
{
	return ParseJSONFile( CreateUStringStreamReader( UString( ).FromString( string ) ).GetPtr( ) );
}

IMarkupLangFilePassRef InterfaceFactory::ParseJSONFile( UStringPtr string )
{
	return ParseJSONFile( CreateUStringStreamReader( string ).GetPtr( ) );
}

IMarkupLangFilePassRef InterfaceFactory::ParseJSONFile( WStringPtr string )
{
	return ParseJSONFile( CreateUStringStreamReader( UString( ).FromString( string ) ).GetPtr( ) );
}

IMarkupLangFilePassRef InterfaceFactory::ParseMarkupLangFile( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _null;

	// Get the characters tag
	_chara tags[4] = {0};
	stream_reader->PeekBuffer( tags, sizeof( tags ) );

	// Skip the UTF-8 header if needed
	const _chara* tag_string = tags;
	SKIP_UTF_CODE_WITHOUT_SIZE( tag_string );

	// Get the first character
	_chara first_char = tag_string[0];

	// It's JSON file format
	if ( first_char == '{' )
	{
		return ParseJSONFile( stream_reader );
	}
	// It's XML file format
	else
	{
		return ParseXMLFile( stream_reader );
	}
}

IManifestFilePassRef InterfaceFactory::ParseManifestFile( IStreamReader* stream_reader )
{
	return ParseStreamFile< ManifestFile, IManifestFile >( stream_reader );
}

IManifestFilePassRef InterfaceFactory::ParseManifestFile( IStreamReader* stream_reader, _ENCRYPTION encryption_type, WStringPtr encryption_key )
{
	if ( stream_reader == _null )
		return _null;

	IManifestFilePassRef manifest_file;

	// If it's xml format then skip to decrypt
	if ( IsXMLFileFormat( stream_reader ) )
	{
		manifest_file = ParseManifestFile( stream_reader );
		if ( manifest_file.IsNull( ) )
		{
			WLOG_ERROR( L"Parse XML manifest file failed" );
			return _null;
		}
	}
	// Load manifest file with encryption
	else
	{
		IDecryptorRef decryptor = GetInterfaceFactory( )->CreateDecryptor( encryption_type, AString( ).FromString( encryption_key ) );
		if ( decryptor.IsNull( ) )
			return _null;

		if ( decryptor->ProcessBuffer( stream_reader->GetSize( ), stream_reader->GetBuffer( ) ) == _false )
			return _null;

		AString manifest_string( (const _chara*) decryptor->GetProcessedBufferData( ), decryptor->GetProcessedBufferSize( ) );
		IStreamReaderRef manifest_stream_reader = GetInterfaceFactory( )->CreateAStringStreamReader( manifest_string );
		if ( manifest_stream_reader.IsNull( ) )
			return _null;
		
		manifest_file = ParseManifestFile( manifest_stream_reader );
		if ( manifest_file.IsNull( ) )
		{
			WLOG_ERROR( L"Parse encrypted manifest file failed" );
			return _null;
		}
	}

	return manifest_file;
}

IPSDFilePassRef	InterfaceFactory::ParsePSDFile( IStreamReader* stream_reader, _dword flags )
{
	return ParseStreamFile< PSDFile, IPSDFile >( stream_reader );
}

IImageFilePassRef InterfaceFactory::ParseImageFile( IStreamReader* stream_reader, _FILE_FORMAT file_format, _dword flags )
{
	return ParseStreamFile< IImageFile, GetImageFileFormat, IsImageFileFormat, CreateImageFile >( file_format, stream_reader, flags );
}

ISoundFilePassRef InterfaceFactory::ParseSoundFile( IStreamReader* stream_reader, _FILE_FORMAT file_format, _dword flags )
{
	return ParseStreamFile< ISoundFile, GetSoundFileFormat, IsSoundFileFormat, CreateSoundFile >( file_format, stream_reader, flags );
}

IZIPFilePassRef	InterfaceFactory::ParseCompressedFile( IStreamReader* stream_reader, WStringPtr password, _dword flags )
{
	if ( stream_reader == _null )
		return _null;

	// Get the file format
	_FILE_FORMAT file_format = GetCommonFileTypeFromStream( stream_reader );

	// Start to parse
	switch ( file_format )
	{
		case _FF_ZIP:	return GetInterfaceFactory( )->ParseZipFile( stream_reader, password, flags );
		case _FF_7Z:	return GetInterfaceFactory( )->Parse7zFile( stream_reader, password, flags );
		default:
			return _null;
	}
}

IZIPFilePassRef	InterfaceFactory::ParseZipFile( IStreamReader* stream_reader, WStringPtr password, _dword flags )
{
	if ( stream_reader == _null )
		return _null;

	ZIPFile* zip_file = new ZIPFile( password );
	zip_file->SetFlags( flags );

	if ( zip_file->LoadFromStream( stream_reader ) == _false )
		{ EGE_RELEASE( zip_file ); return _null; }

	return zip_file;
}

IZIPFilePassRef	InterfaceFactory::Parse7zFile( IStreamReader* stream_reader, WStringPtr password, _dword flags )
{
	if ( stream_reader == _null )
		return _null;

	SZFile* sz_file = new SZFile( password );
	sz_file->SetFlags( flags );

	if ( sz_file->LoadFromStream( stream_reader ) == _false )
		{ EGE_RELEASE( sz_file ); return _null; }

	return sz_file;
}

IZIPFilePassRef	InterfaceFactory::ParsePackageFile( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _null;

	PackageFile* package_file = new PackageFile( );
	if ( package_file->LoadFromStream( stream_reader ) == _false )
		{ EGE_RELEASE( package_file ); return _null; }

	return package_file;
}

IWEBMFilePassRef InterfaceFactory::ParseWEBMFile( IStreamReader* stream_reader )
{
	return ParseStreamFile< WEBMFile, IWEBMFile >( stream_reader );
}

IManifestFileManagerPassRef InterfaceFactory::CreateManifestFileManager( )
{
	return new ManifestFileManager( );
}

IResLoaderPassRef InterfaceFactory::CreateResLoader( _dword thread_number, WStringPtr name, IResLoaderFactory* factory )
{
	ResLoader* res_loader = new ResLoader( );
	if ( res_loader->Initialize( thread_number, name, factory ) == _false )
		{ EGE_RELEASE( res_loader ); return _null; }

	return res_loader;	
}

