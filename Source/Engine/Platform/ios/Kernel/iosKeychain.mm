//! @file     iosKeychain.mm
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

INTERNAL_HANDLER_IMPL_BEGIN( iosKeychain )
	KeychainItemWrapper*	mKeychain;
INTERNAL_HANDLER_IMPL_END( )

//----------------------------------------------------------------------------
// Helpful Functions Implementation
//----------------------------------------------------------------------------

static CFTypeRef GetObjectKey( IKeychain::_KEY key )
{
	switch ( key )
	{
		case IKeychain::_KEY_SEC_ATTR_ACCESSGROUP:		return kSecAttrAccessGroup;
		case IKeychain::_KEY_SEC_ATTR_CREATIONDATE:		return kSecAttrCreationDate;
		case IKeychain::_KEY_SEC_ATTR_MODIFICATIONDATE:	return kSecAttrModificationDate;
		case IKeychain::_KEY_SEC_ATTR_DESCRIPTION:		return kSecAttrDescription;
		case IKeychain::_KEY_SEC_ATTR_COMMENT:			return kSecAttrComment;
		case IKeychain::_KEY_SEC_ATTR_CREATOR:			return kSecAttrCreator;
		case IKeychain::_KEY_SEC_ATTR_TYPE:				return kSecAttrType;
		case IKeychain::_KEY_SEC_ATTR_LABEL:			return kSecAttrLabel;
		case IKeychain::_KEY_SEC_ATTR_ISINVISIBLE:		return kSecAttrIsInvisible;
		case IKeychain::_KEY_SEC_ATTR_ISNEGATIVE:		return kSecAttrIsNegative;
		case IKeychain::_KEY_SEC_ATTR_ACCOUNT:			return kSecAttrAccount;
		case IKeychain::_KEY_SEC_ATTR_SERVICE:			return kSecAttrService;
		case IKeychain::_KEY_SEC_ATTR_GENERIC:			return kSecAttrGeneric;
		default:
			return _null;
	}
}

//----------------------------------------------------------------------------
// iosKeychain Implementation
//----------------------------------------------------------------------------

iosKeychain::iosKeychain( )
{
	INTERNAL_HANDLER_CREATE( );
}

iosKeychain::~iosKeychain( )
{
	INTERNAL_HANDLER_RELEASE( );
}

_ubool iosKeychain::Initialize( WStringPtr identifier, WStringPtr access_group )
{
	NSString* ns_identifier		= NSPlatform::Utf16ToNSString( identifier );
	NSString* ns_access_group	= access_group.IsEmpty( ) ? nil : NSPlatform::Utf16ToNSString( access_group );

	INTERNAL_HANDLER( )->mKeychain = [[KeychainItemWrapper alloc] initWithIdentifier:ns_identifier accessGroup:ns_access_group];
	if ( INTERNAL_HANDLER( )->mKeychain == nil )
		return _false;

	return _true;
}

_ubool iosKeychain::Reset( )
{
	[INTERNAL_HANDLER( )->mKeychain resetKeychainItem];

	return _true;
}

_ubool iosKeychain::SetObject( _KEY key, WStringPtr value )
{
	if ( value.IsEmpty( ) )
		return _false;

	CFTypeRef ns_key = GetObjectKey( key );
	if ( ns_key == _null )
		return _false;

	NSString* ns_value = NSPlatform::Utf16ToNSString( value );

	[INTERNAL_HANDLER( )->mKeychain setObject:ns_value forKey:(__bridge id)ns_key];

	return _true;
}

_ubool iosKeychain::GetObject( _KEY key, WString& value ) const
{
	CFTypeRef ns_key = GetObjectKey( key );
	if ( ns_key == _null )
		return _false;

	id ns_value = [INTERNAL_HANDLER( )->mKeychain objectForKey:(__bridge id)ns_key];
	if ( ns_value == nil )
		return _false;

	value = NSPlatform::NSStringToUtf16( (NSString*) ns_value );

	return _true;
}