//! @file     iosPlatform.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

INTERNAL_HANDLER_IMPL_BEGIN( iosPlatform )
#if (USE_GOOGLE_BREAK_PAD == 1)
    BreakpadRef	mBreakpad;
#endif

    INTERNAL_HANDLER_CONSTRUCTOR( )
    {
#if (USE_GOOGLE_BREAK_PAD == 1)
        mBreakpad = _null;
#endif
    }
    INTERNAL_HANDLER_DESTRUCTOR( )
    {
#if (USE_GOOGLE_BREAK_PAD == 1)
        if ( mBreakpad != _null )
            BreakpadRelease( mBreakpad );
#endif
    }
INTERNAL_HANDLER_IMPL_END( )

//----------------------------------------------------------------------------
// Helpful Functions Implementation
//----------------------------------------------------------------------------

typedef struct FontHeader {
	int32_t fVersion;
	uint16_t fNumTables;
	uint16_t fSearchRange;
	uint16_t fEntrySelector;
	uint16_t fRangeShift;
}FontHeader;

typedef struct TableEntry {
	uint32_t fTag;
	uint32_t fCheckSum;
	uint32_t fOffset;
	uint32_t fLength;
}TableEntry;

static uint32_t CalcTableCheckSum(const uint32_t *table, uint32_t numberOfBytesInTable) {
	uint32_t sum = 0;
	uint32_t nLongs = (numberOfBytesInTable + 3) / 4;
	while (nLongs-- > 0) {
		sum += CFSwapInt32HostToBig(*table++);
	}
	return sum;
}

static uint32_t CalcTableDataRefCheckSum(CFDataRef dataRef) {
	const uint32_t *dataBuff = (const uint32_t *)CFDataGetBytePtr(dataRef);
	uint32_t dataLength = (uint32_t)CFDataGetLength(dataRef);
	return CalcTableCheckSum(dataBuff, dataLength);
}

//----------------------------------------------------------------------------
// iosPlatform Implementation
//----------------------------------------------------------------------------

iosPlatform::iosPlatform( )
{
}

iosPlatform::~iosPlatform( )
{
	Finalize( );
}

_ubool iosPlatform::InitDumper( )
{
#if (USE_GOOGLE_BREAK_PAD == 1)
	WString root_path = GetPlatform( )->GetDocumentDirectory( );
	WString dump_path = Path::BuildFilePath( root_path, L"dump" );
	if ( FileSystem::CreateDir( dump_path ) == _false )
		return _false;

	NSDictionary* dict = [NSDictionary dictionaryWithObjectsAndKeys:
        @"EGE_Core_URL", @BREAKPAD_URL,
        @"EGE_Core", @BREAKPAD_PRODUCT,
        @"1.0.0.0", @BREAKPAD_VERSION,
        NSPlatform::Utf16ToNSString( dump_path.Str( ) ), @BREAKPAD_DUMP_DIRECTORY,
        nil];
    
    INTERNAL_HANDLER( )->mBreakpad = BreakpadCreate( dict );
    if ( INTERNAL_HANDLER( )->mBreakpad == nil )
        return _false;
#endif

	return _true;
}

_ubool iosPlatform::GetCGFontData( AStringPtr font_name, _byte*& font_buffer, _int& font_buffer_size )
{
    if ( font_name.IsEmpty( ) )
        return _false;
    
    // Get the CG font info
    CGFontRef cgFont = CGFontCreateWithFontName( (__bridge CFStringRef)[NSString stringWithUTF8String:font_name.Str( )] );
    if ( !cgFont )
        return _false;
    
    // Get the table of font
    CFArrayRef tags = CGFontCopyTableTags(cgFont);
    CFIndex tableCount = CFArrayGetCount(tags);
    
    // Create table buffer
    MemArrayPtr< size_t > tableSizes( tableCount );
    EGE_MEM_SET(tableSizes, 0, sizeof(size_t) * tableCount);
    
    // The table info
    BOOL containsCFFTable = NO;
    
    // Get the font buffer size and update table buffer
    font_buffer_size = sizeof(FontHeader) + sizeof(TableEntry) * (_int)tableCount;
    for (int index = 0; index < tableCount; ++index)
    {
        //get size
        size_t tableSize = 0;
        size_t aTag = (size_t)CFArrayGetValueAtIndex(tags, index);
        
        if (aTag == 'CFF ' && !containsCFFTable) {
            containsCFFTable = YES;
        }
        
        CFDataRef tableDataRef = CGFontCopyTableForTag(cgFont, (uint32_t)aTag);
        if (tableDataRef != NULL) {
            tableSize = CFDataGetLength(tableDataRef);
            CFRelease(tableDataRef);
        }
        font_buffer_size += (tableSize + 3) & ~3;
        
        tableSizes[index] = tableSize;
    }
    
    font_buffer = new _byte [font_buffer_size];
    
    char* dataStart = (char*)font_buffer;
    char* dataPtr = dataStart;
    
    // compute font header entries
    uint16_t entrySelector = 0;
    uint16_t searchRange = 1;
    
    while (searchRange < tableCount >> 1) {
        entrySelector++;
        searchRange <<= 1;
    }
    searchRange <<= 4;
    
    uint16_t rangeShift = (tableCount << 4) - searchRange;
    
    // write font header (also called sfnt header, offset subtable)
    FontHeader* offsetTable = (FontHeader*)dataPtr;
    
    //OpenType Font contains CFF Table use 'OTTO' as version, and with .otf extension
    //otherwise 0001 0000
    offsetTable->fVersion = containsCFFTable ? 'OTTO' : CFSwapInt16HostToBig(1);
    offsetTable->fNumTables = CFSwapInt16HostToBig((uint16_t)tableCount);
    offsetTable->fSearchRange = CFSwapInt16HostToBig((uint16_t)searchRange);
    offsetTable->fEntrySelector = CFSwapInt16HostToBig((uint16_t)entrySelector);
    offsetTable->fRangeShift = CFSwapInt16HostToBig((uint16_t)rangeShift);
    
    dataPtr += sizeof(FontHeader);
    
    // write tables
    TableEntry* entry = (TableEntry*)dataPtr;
    dataPtr += sizeof(TableEntry) * tableCount;
    
    for (int index = 0; index < tableCount; ++index) {
        
        size_t aTag = (size_t)CFArrayGetValueAtIndex(tags, index);
        CFDataRef tableDataRef = CGFontCopyTableForTag(cgFont, (uint32_t)aTag);
        size_t tableSize = CFDataGetLength(tableDataRef);
        
        memcpy(dataPtr, CFDataGetBytePtr(tableDataRef), tableSize);
        
        entry->fTag = CFSwapInt32HostToBig((uint32_t)aTag);
        entry->fCheckSum = CFSwapInt32HostToBig(CalcTableCheckSum((uint32_t *)dataPtr, (uint32_t)tableSize));
        
        uint32_t offset = (uint32_t)(dataPtr - dataStart);
        entry->fOffset = CFSwapInt32HostToBig((uint32_t)offset);
        entry->fLength = CFSwapInt32HostToBig((uint32_t)tableSize);
        dataPtr += (tableSize + 3) & ~3;
        ++entry;
        CFRelease(tableDataRef);
    }
	
	// Release CG font
	CFRelease( tags );
	CFRelease( cgFont );

	return _true;
}

_ubool iosPlatform::Initialize( )
{
	if ( BaseClass::Initialize( ) == _false )
		return _false;

	INTERNAL_HANDLER_CREATE( );

	if ( InitDumper( ) == _false )
		return _false;

	return _true;
}

_void iosPlatform::Finalize( )
{
	INTERNAL_HANDLER_RELEASE( );

	BaseClass::Finalize( );
}

const PlatformDeviceInfo& iosPlatform::GetDeviceInfo( )
{
	if ( mDeviceInfo.mDeviceName.IsEmpty( ) )
	{
		mDeviceInfo.mAdvertisingIdentifier	= NSDevice_GetAdvertisingIdentifier( );
		mDeviceInfo.mIdentifierForVendor	= NSDevice_GetIdentifierForVendor( );
		mDeviceInfo.mDeviceName				= NSDevice_GetDeviceName( );
		mDeviceInfo.mModelName				= NSDevice_GetModelName( );
		mDeviceInfo.mSystemName				= NSDevice_GetSystemName( );
		mDeviceInfo.mSystemVersion			= NSDevice_GetSystemVersion( );
		mDeviceInfo.mUserInterface			= NSDevice_GetUserInterfaceIdiom( );
		mDeviceInfo.mHardwareIDv2			= NSDevice_GetHardwareID( );
	}

	return BaseClass::GetDeviceInfo( );
}

_qword iosPlatform::GetCurProcessMemSize( ) const
{
	_qword mem_size = 0;
	return mem_size;
}

_qword iosPlatform::GetTotalMemSize( ) const
{
	static _qword total_mem_size = 0;
	if ( total_mem_size == 0 )
	{
		int mib[2];
		int64_t physical_memory;
		size_t length;

		// Get the Physical memory size
		mib[0] = CTL_HW;
		mib[1] = HW_MEMSIZE;
		length = sizeof(Int64);
		sysctl(mib, 2, &physical_memory, &length, NULL, 0);

		total_mem_size = (_qword)physical_memory;
	}

	return total_mem_size;
}

PointU iosPlatform::GetMainScreenSize( ) const
{
	return NS_ScreenGetSize( );
}

_ubool iosPlatform::IsScreenOn( ) const
{
	return _true;
}

_void iosPlatform::OpenURL( WStringPtr url )
{
	NSNet_OpenUrl( AString( ).FromString( url ).Str( ) );
}

IStreamReaderPassRef iosPlatform::LoadSystemFont( WStringPtr name )
{
	_byte* buffer = _null; _int buffer_size = 0;
	if ( GetCGFontData( AString( ).FromString( name ).Str( ), buffer, buffer_size ) == _false )
		return _null;

	return GetInterfaceFactory( )->CreateMemStreamReader( buffer, buffer_size, _STREAM_SHARE_MODE_MANAGED );
}

IWebViewPassRef	iosPlatform::CreateWebView( const PointI& pos, const PointI& size )
{
	iosWebView* web_view = new iosWebView( );
    if ( web_view->Initialize( pos, size ) == _false )
        { EGE_RELEASE( web_view ); return _null; }
    
    return web_view;
}

IEditBoxPassRef	iosPlatform::CreateEditBox( )
{
	return new iosEditBox( );
}

IMessageBoxPassRef iosPlatform::CreateMessageBox( WStringPtr title, WStringPtr content, _MESSAGE_BOX_TYPE type, IMessageBoxNotifier* notifier ) const
{
	return _null;
}

IMessageBoxPassRef iosPlatform::CreateMessageBox( WStringPtr title, WStringPtr content, WStringPtr yes_text, WStringPtr no_text, _MESSAGE_BOX_TYPE type, IMessageBoxNotifier* notifier ) const
{
	return _null;
}

IAnalyticsCenterPassRef iosPlatform::CreateAnalyticsCenter( UStringPtr app_id )
{
	return new iosAnalyticsCenterFlurry( app_id );
}

IAdViewPassRef iosPlatform::CreateAdView( AStringPtr app_id, IViewBasedApp* viewbased_app, IAdView::_TYPE type )
{
	iosAdView* ad_view = new iosAdView( );
	if ( ad_view->Initialize( app_id, viewbased_app, type ) == _false )
		{ EGE_RELEASE( ad_view ); return _null; }

	return ad_view;
}

IKeychainPassRef iosPlatform::CreateKeychain( WStringPtr identifier, WStringPtr access_group )
{    
    iosKeychain* keychain = new iosKeychain( );
    if ( keychain->Initialize( identifier, access_group ) == _false )
        { EGE_RELEASE( keychain ); return _null; }
    
    return keychain;
}

_void iosPlatform::InvokeService( WStringPtr name )
{

}

_ubool iosPlatform::InvokeServiceZ( WStringPtr name )
{
	return _true;
}

_void iosPlatform::Vibrate( _dword duration )
{

}

_void iosPlatform::CancelVibrate( )
{

}

IIAPManagerPassRef iosPlatform::CreateIAPManager( )
{
    return new iosIAPManager( );
}

_void iosPlatform::RegisterForPushNotification( )
{
    NSApplication_RegisterForPushNotification( );
}
