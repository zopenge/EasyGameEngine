//! @file     NSPlatform.mm
//! @author   LiCode
//! @version  1.1.1.804
//! @date     2011/03/10
//! Copyright ...

#include "EGEPlatform.h"

#define USE_MAPPED_FILE 1
#define USE_NS_ZONE		0
#define USE_NS_LOG		1

#define DISABLE_LOG		0

//----------------------------------------------------------------------------
// Export Functions Implementation
//----------------------------------------------------------------------------

EGE_EXTERNAL IIOS_PlatformModule* GetIOSPlatformModule( )
{
	return &iosPlatformModule::GetInstance( );
}

//----------------------------------------------------------------------------
// NS-Helpful Structures
//----------------------------------------------------------------------------

//!	The NS data info
struct NSDataInfo
{
#if (USE_MAPPED_FILE == 1)
	NSMappedFile*	mFile;
#else
	_dword			mResSize;
	_byte*			mResBuffer;
#endif

#if (USE_MAPPED_FILE == 1)
	NSDataInfo( WStringPtr filename )
	{
		mFile = [[NSMappedFile alloc]initWithPath: NSPlatform::Utf16ToNSString( filename )];
        [mFile map];
	}
#else
	NSDataInfo( _dword res_size, _byte* res_buffer )
	{
		mResSize	= res_size;
		mResBuffer	= res_buffer;
	}
#endif
	~NSDataInfo( )
	{
#if (USE_MAPPED_FILE == 1)
		[mFile unmap];
		mFile = nil;
#else
        EGE_DELETE_ARRAY( mResBuffer );
#endif
	}
};

//----------------------------------------------------------------------------
// NSPlatform Implementation
//----------------------------------------------------------------------------

NSString* NSPlatform::AnsiToNSString( AStringPtr string )
{
	return [NSString stringWithUTF8String:string.Str( )];
}

NSString* NSPlatform::Utf8ToNSString( UStringPtr string )
{
	return [NSString stringWithUTF8String:string.Str( )];
}

NSString* NSPlatform::Utf16ToNSString( WStringPtr string )
{
	return [NSString stringWithCharacters:(const unichar*) string.Str( ) length: string.GetLength( ) ];
}

NSString* NSPlatform::AnsiToNSString( const _chara* string )
{
	return [NSString stringWithUTF8String:string];
}

NSString* NSPlatform::Utf8ToNSString( const _chara* string )
{
	return [NSString stringWithUTF8String:string];
}

NSString* NSPlatform::Utf16ToNSString( const _charw* string )
{
	return [NSString stringWithCharacters:(const unichar*) string length: Platform::StringLength( string ) ];
}

NSString* NSPlatform::AnsiToNSString( const AStringR& string )
{
	return [NSString stringWithUTF8String:((const AString&)string).Str( )];
}

NSString* NSPlatform::Utf8ToNSString( const UStringR& string )
{
	return [NSString stringWithUTF8String:((const UString&)string).Str( )];
}

NSString* NSPlatform::Utf16ToNSString( const WStringR& string )
{
	return [NSString stringWithCharacters:(const unichar*) ((const WString&)string).Str( ) length: string.GetLength( ) ];
}

WString NSPlatform::NSStringToUtf16( NSString* ns_string )
{
	EGE_ASSERT( ns_string != _null );
	
	// Get the NS-String length (contains '\0' character)
	_dword length = (_dword)ns_string.length + 1;
	MemArrayPtr< _charw > buffer( length );
	[ns_string getCString:(char*)buffer.GetPointer() maxLength:length * sizeof( _charw ) encoding:NSUTF16StringEncoding];
	
	return WString( buffer, length - 1 );
}

//----------------------------------------------------------------------------
// iosPlatformModule Implementation
//----------------------------------------------------------------------------

iosPlatformModule::iosPlatformModule( )
{
	
}

iosPlatformModule::~iosPlatformModule( )
{
	
}

_ubool iosPlatformModule::Initialize( )
{	
	// Get the main bundle path
	NSString* bundle_path = [[NSBundle mainBundle] bundlePath];
	EGE_ASSERT( bundle_path != _null );

	// Convert to UTF16 
	mMainBundlePath.FromString( _ENCODING_UTF8, [bundle_path UTF8String] );
	mMainBundlePath += L"/";

	return _true;
}

_void iosPlatformModule::Finalize( )
{
	
}

_dword iosPlatformModule::AnsiToUtf16( _charw* buffer, _dword size, const _chara* string, _dword number )
{
	NSString* nsstring = NSPlatform::AnsiToNSString( string );

	// Get the number of bytes required to store the UNICODE string
	_dword unicode_string_size = (_dword)[nsstring lengthOfBytesUsingEncoding:NSUTF16StringEncoding];
    // The length of bytes API do not contains '\0' character size, so need to increase 2 bytes here
    //unicode_string_size += sizeof( _charw );
	
	if ( buffer != _null )
	{
		EGE_ASSERT( size != 0 );

		[nsstring getCString:(char*)buffer maxLength:size * sizeof( _charw ) encoding:NSUTF16StringEncoding];
		buffer[ Math::Min( size - 1, unicode_string_size ) ] = 0;
	}

	return unicode_string_size;
}

_dword iosPlatformModule::Utf16ToAnsi( _chara* buffer, _dword size, const _charw* string, _dword number )
{
	NSString* nsstring = NSPlatform::Utf16ToNSString( string );

	// Get the number of bytes required to store the ANSI string
	_dword ansi_string_size = (_dword)[nsstring lengthOfBytesUsingEncoding:NSASCIIStringEncoding];
    // The length of bytes API do not contains '\0' character size, so need to increase 1 bytes here
    //ansi_string_size += sizeof( _chara );

	if ( buffer != _null )
	{
		EGE_ASSERT( size != 0 );

		[nsstring getCString:(char*)buffer maxLength:size encoding:NSASCIIStringEncoding];
		buffer[ Math::Min( size - 1, ansi_string_size ) ] = 0;
	}

	return ansi_string_size;
}

_dword iosPlatformModule::Utf8ToUtf16( _charw* buffer, _dword size, const _chara* string, _dword number )
{
	NSString* nsstring = NSPlatform::Utf8ToNSString( string );

	// Get the number of bytes required to store the UNICODE string
	_dword unicode_string_size = (_dword)[nsstring lengthOfBytesUsingEncoding:NSUTF16StringEncoding];
    // The length of bytes API do not contains '\0' character size, so need to increase 2 bytes here
    //unicode_string_size += sizeof( _charw );

	if ( buffer != _null )
	{	
		EGE_ASSERT( size != 0 );

		[nsstring getCString:(char*)buffer maxLength:size * sizeof( _charw ) encoding:NSUTF16StringEncoding];
		buffer[ Math::Min< _dword >( size - 1, unicode_string_size / sizeof( _charw ) ) ] = 0;
	}

	return unicode_string_size + sizeof( _charw );
}

_dword iosPlatformModule::Utf16ToUtf8( _chara* buffer, _dword size, const _charw* string, _dword number )
{
	NSString* nsstring = NSPlatform::Utf16ToNSString( string );

	// Get the number of bytes required to store the UNICODE string
	_dword ansi_string_size = (_dword)[nsstring lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
    // The length of bytes API do not contains '\0' character size, so need to increase 1 bytes here
    //ansi_string_size += sizeof( _chara );

	if ( buffer != _null )
	{
		EGE_ASSERT( size != 0 );

        [nsstring getCString:(char*)buffer maxLength:size encoding:NSUTF8StringEncoding];
		buffer[ Math::Min( size - 1, ansi_string_size ) ] = 0;
	}

	return ansi_string_size;
}

_void iosPlatformModule::LogA( const _chara* buffer )
{
#if (DISABLE_LOG == 0)
#if (USE_NS_LOG == 1)
	NSString* string = NSPlatform::AnsiToNSString( buffer );
	NSLog( @"%@", string);
#else
	printf( "%s", buffer );
#endif
#endif
}

_void iosPlatformModule::LogW( const _charw* buffer )
{
#if (DISABLE_LOG == 0)
#if (USE_NS_LOG == 1)
    NSString* string = NSPlatform::Utf16ToNSString( buffer );
	NSLog( @"%@", string);
#else
	AString string = AString( ).FromString( _ENCODING_UTF16, buffer );
	printf( "%s", string.Str( ) );
#endif
#endif
}

_handle iosPlatformModule::CreateAutoReleasePool( )
{
#if __has_feature(objc_arc)
    return _null;
#else
	return [[NSAutoreleasePool alloc] init];
#endif
}

_void iosPlatformModule::ReleaseAutoReleasePool( _handle pool )
{
#if __has_feature(objc_arc)
#else
	NSAutoreleasePool* ns_pool = (NSAutoreleasePool*) pool;
	EGE_ASSERT( ns_pool != _null );
    
	[ns_pool release];
#endif
}

_void* iosPlatformModule::GlobalAlloc( _dword size )
{
	if ( size == 0 )
		return _null;

#if (USE_NS_ZONE == 1)
	return NSZoneMalloc( NSDefaultMallocZone( ), size );
#else
	return malloc( size );
#endif
}

_void* iosPlatformModule::GlobalReAlloc( _void* pointer, _dword size )
{
	if ( size == 0 )
		return _null;

#if (USE_NS_ZONE == 1)
	return NSZoneRealloc( NSDefaultMallocZone( ), pointer, size );
#else
	return realloc( pointer, size );
#endif
}

_void iosPlatformModule::GlobalFree( _void* pointer )
{
	if ( pointer == _null )
		return;

#if (USE_NS_ZONE == 1)
	NSZoneFree( NSDefaultMallocZone( ), pointer );
#else
	free( pointer );
#endif
}

_ubool iosPlatformModule::GetFileAttributes( const _charw* filename, _dword& attributes )
{
	// Get the file manager
	NSFileManager* file_manager = [NSFileManager defaultManager];
	EGE_ASSERT( file_manager != _null );

	// Convert file name to NS-String style
	NSString* nsstring_filename = NSPlatform::Utf16ToNSString( filename );
	EGE_ASSERT( nsstring_filename != _null );

	// Get the file attributes
	NSDictionary* file_attributes = [file_manager attributesOfItemAtPath:nsstring_filename error:_null];
	if ( file_attributes == _null )
		return _false;

	// Clear previous attributes
	attributes = 0;

	// It's directory
	if ( [file_attributes objectForKey:NSFileType] == NSFileTypeDirectory )
		attributes |= _FILE_ATTRIBUTE_DIRECTORY;

	return _true;
}

_ubool iosPlatformModule::GetDocumentPathInDomains( _charw* path, _dword length )
{
	NSArray* paths = NSSearchPathForDirectoriesInDomains( NSDocumentDirectory, NSUserDomainMask, YES );
	if ( paths == _null )
		return _false;

	NSString* document = [paths objectAtIndex:0];
	if ( document == _null )
		return _false;
	
	_charw buffer[2048] = {0};
	[document getCString:(char*)buffer maxLength:2048 encoding:NSUTF16StringEncoding];

	Platform::CopyString( path, buffer, length );

	return _true;
}

_ubool iosPlatformModule::EnumResourceNames( const _charw* sub_dir_name, Platform::OnEnumResNameProc funcpointer, _void* parameter )
{
	// Get the sub directory path
	WString sub_dir_name_in_bundle = mMainBundlePath + sub_dir_name;

	// Convert file name to NS-String style
	NSString* ns_sub_dir_name_in_bundle = NSPlatform::Utf16ToNSString( sub_dir_name_in_bundle );
	EGE_ASSERT( ns_sub_dir_name_in_bundle != _null );
	
	// Now enumerate sub elements of it
	NSError* error = nil;
	NSArray* paths = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:ns_sub_dir_name_in_bundle error:&error];
	if ( paths == _null )
		return _false;

	for ( _dword i = 0; i < paths.count; i ++ )
	{
		NSString* sub_path = [paths objectAtIndex:i];
		if ( sub_path == _null )
			return _false;

		_charw sub_path_utf16[2048] = {0};
		[sub_path getCString:(char*)sub_path_utf16 maxLength:2048 encoding:NSUTF16StringEncoding];

		// Build the whole path
		WString whole_path = Path::BuildFilePath( sub_dir_name_in_bundle, sub_path_utf16 );
		
		// It's directory
		if ( FileSystem::IsDirectoryExist( whole_path ) )
		{
			WString relative_sub_dir_path = Path::BuildFilePath( sub_dir_name, sub_path_utf16 );
			if ( EnumResourceNames( relative_sub_dir_path.Str( ), funcpointer, parameter ) )
				break;
		}
		// It's file
		else
		{
			if ( (*funcpointer)( whole_path.Str( ), parameter ) == _false )
				break; // Found it
		}
	}
	
	return _true;
}

_handle iosPlatformModule::LoadMainBundleResource( const _charw* relative_name )
{
	// Get the resource file name
	WString filename = mMainBundlePath + relative_name;

	// Check whether it's exsiting
	if ( FileSystem::IsFileExist( filename ) == _false )
		return _false;
   
#if (USE_MAPPED_FILE == 1)
	return new NSDataInfo( filename );
#else
	// Open the resource file
	_handle res_handle = Platform::OpenFile( filename, _FILE_OPEN_EXISTING, _FILE_OPERATION_READ, _FILE_SHARE_READ, _FILE_ATTRIBUTE_READONLY );
    if ( res_handle == _null )
		return _null;

	// Get the resource file size in bytes
	_dword res_size = Platform::GetFileSize( res_handle );

	// Read resource buffer data
	_byte* res_buffer = new _byte[ res_size ];
	Platform::ReadFile( res_handle, res_buffer, res_size );

	// Close file
	Platform::CloseFile( res_handle );

	// Create NS data info
	return new NSDataInfo( res_size, res_buffer );
#endif
}

_dword iosPlatformModule::GetSizeOfMainBundleResource( _handle file )
{
    NSDataInfo* data_info = (NSDataInfo*) file;
    if ( data_info == _null )
		return 0;

#if (USE_MAPPED_FILE == 1)
	return (_dword)[data_info->mFile size];
#else
	return data_info->mResSize;
#endif
}

const _byte* iosPlatformModule::GetDataOfMainBundleResource( _handle file )
{
    NSDataInfo* data_info = (NSDataInfo*) file;
    if ( data_info == _null )
		return _null;

#if (USE_MAPPED_FILE == 1)
	return (const _byte*) [data_info->mFile map];
#else
	return data_info->mResBuffer;
#endif
}

_void iosPlatformModule::UnloadMainBundleResource( _handle file )
{
    NSDataInfo* data_info = (NSDataInfo*) file;
    if ( data_info == _null )
        return;

    EGE_DELETE( data_info );
}
