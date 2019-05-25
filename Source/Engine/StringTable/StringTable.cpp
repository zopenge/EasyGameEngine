//! @file     StringTable.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// StringTable Implementation
//----------------------------------------------------------------------------

StringTable::StringTable( )
{
	mTotalSize		= 0;

	mNullAStringObj	= GetRefString( AStringPtr( "" ) );
	mNullUStringObj = GetRefString( UStringPtr( "" ) );
	mNullWStringObj = GetRefString( WStringPtr( L"" ) );
}

StringTable::~StringTable( )
{
	ClearAllStrings( );
}

template< typename MapType >
_void StringTable::TClearObjMap( MapType& obj_map )
{
	for ( typename MapType::Iterator it = obj_map.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		_byte* string_buffer = (_byte*) it.GetObject( ).Str( );
		EGE_DELETE_ARRAY( string_buffer );
	}

	obj_map.Clear( );
}

template< typename MapType, typename StringObjType, typename Type, typename CharType >
const StringObjType& StringTable::TGetRefString( MapType& obj_map, const Type& string, _crcvalue id )
{
	// Search the referenced string object from map
	mLocker.Enter( );
	StringObjType& refstring = obj_map[id];
	mLocker.Leave( );

	// Is an existing referenced string object ?
	if ( refstring.GetID( ) == -1 )
	{
		// Update total size in bytes
		_dword size = string.SizeOfBytes( );
		mTotalSize += size;

		// Copy into string buffer
		_byte* string_buffer = new _byte[size];
		EGE_MEM_CPY( string_buffer, (const _byte*)string.Str( ), size );

		// Update its string
		refstring = StringObjType( id, (const CharType*)string_buffer );
	}

	return refstring;
}

template< typename MapType, typename StringObjType, typename Type, typename CharType >
const StringObjType& StringTable::TGetRefString( MapType& obj_map, const Type& string )
{
	return TGetRefString< MapType, StringObjType, Type, CharType >( obj_map, string, string.GetCRCValue( ) );
}

template< typename MapType, typename StringObjType, typename Type >
const StringObjType& StringTable::TSearchRefString( const MapType& obj_map, const Type& string ) const
{
	// Build the CRC value ID
	_crcvalue id = string.GetCRCValue( );

	// Search the referenced string object from map
	const StringObjType* refstring = obj_map.Search( id );
	if ( refstring == _null )
	{
		static StringObjType sNull;
		return sNull;
	}

	// Use the referenced string object wrapper to manager it
	return *refstring;
}

template< typename MapType, typename StringObjType >
const StringObjType& StringTable::TSearchRefString( const MapType& obj_map, _dword id ) const
{
	// Search the referenced string object from map
	const StringObjType* refstring = obj_map.Search( id );
	if ( refstring == _null )
	{
		static StringObjType sNull;
		return sNull;
	}

	// Use the referenced string object wrapper to manager it
	return *refstring;
}

_void StringTable::ClearAllStrings( )
{
	TClearObjMap( mAStringObjRefMap );
	TClearObjMap( mUStringObjRefMap );
	TClearObjMap( mWStringObjRefMap );

	mResNameAndIDMaps.Clear( );
}

_dword StringTable::GetTotalSize( ) const
{
	return mTotalSize;
}

const AStringObj& StringTable::GetNullAString( ) const
{
	return mNullAStringObj;
}

const UStringObj& StringTable::GetNullUString( ) const
{
	return mNullUStringObj;
}

const WStringObj& StringTable::GetNullWString( ) const
{
	return mNullWStringObj;
}

const AStringObj& StringTable::GetRefString( const ARawString& string )
{
	return TGetRefString< AStringObjMap, AStringObj, ARawString, _chara >( mAStringObjRefMap, string );
}

const AStringObj& StringTable::GetRefString( AStringPtr string )
{
	return TGetRefString< AStringObjMap, AStringObj, AStringPtr, _chara >( mAStringObjRefMap, string );
}

const AStringObj& StringTable::GetRefString( const AString& string )
{
	return TGetRefString< AStringObjMap, AStringObj, AString, _chara >( mAStringObjRefMap, string );
}

const AStringObj& StringTable::SearchRefAStringByID( _dword id ) const
{
	return TSearchRefString< AStringObjMap, AStringObj >( mAStringObjRefMap, id );
}

const AStringObj& StringTable::SearchRefString( const ARawString& string ) const
{
	return TSearchRefString< AStringObjMap, AStringObj, ARawString >( mAStringObjRefMap, string );
}

const AStringObj& StringTable::SearchRefString( AStringPtr string ) const
{
	return TSearchRefString< AStringObjMap, AStringObj, AStringPtr >( mAStringObjRefMap, string );
}

const UStringObj& StringTable::GetRefString( const URawString& string )
{
	return TGetRefString< UStringObjMap, UStringObj, URawString, _chara >( mUStringObjRefMap, string );
}

const UStringObj& StringTable::GetRefString( UStringPtr string )
{
	return TGetRefString< UStringObjMap, UStringObj, UStringPtr, _chara >( mUStringObjRefMap, string );
}

const UStringObj& StringTable::GetRefString( const UString& string )
{
	return TGetRefString< UStringObjMap, UStringObj, UString, _chara >( mUStringObjRefMap, string );
}

const UStringObj& StringTable::SearchRefUStringByID( _dword id ) const
{
	return TSearchRefString< UStringObjMap, UStringObj >( mUStringObjRefMap, id );
}

const UStringObj& StringTable::SearchRefString( const URawString& string ) const
{
	return TSearchRefString< UStringObjMap, UStringObj, URawString >( mUStringObjRefMap, string );
}

const UStringObj& StringTable::SearchRefString( UStringPtr string ) const
{
	return TSearchRefString< UStringObjMap, UStringObj, UStringPtr >( mUStringObjRefMap, string );
}

const WStringObj& StringTable::GetRefString( const WRawString& string )
{
	return TGetRefString< WStringObjMap, WStringObj, WRawString, _charw >( mWStringObjRefMap, string );
}

const WStringObj& StringTable::GetRefString( WStringPtr string )
{
	return TGetRefString< WStringObjMap, WStringObj, WStringPtr, _charw >( mWStringObjRefMap, string );
}

const WStringObj& StringTable::GetRefString( const WString& string )
{
	return TGetRefString< WStringObjMap, WStringObj, WString, _charw >( mWStringObjRefMap, string );
}

const WStringObj& StringTable::SearchRefWStringByID( _dword id ) const
{
	return TSearchRefString< WStringObjMap, WStringObj >( mWStringObjRefMap, id );
}

const WStringObj& StringTable::SearchRefString( const WRawString& string ) const
{
	return TSearchRefString< WStringObjMap, WStringObj, WRawString >( mWStringObjRefMap, string );
}

const WStringObj& StringTable::SearchRefString( WStringPtr string ) const
{
	return TSearchRefString< WStringObjMap, WStringObj, WStringPtr >( mWStringObjRefMap, string );
}

const AStringObj& StringTable::GetRefString( const _chara* string )
{
	return TGetRefString< AStringObjMap, AStringObj, AStringPtr, _chara >( mAStringObjRefMap, string );
}

const WStringObj& StringTable::GetRefString( const _charw* string )
{
	return TGetRefString< WStringObjMap, WStringObj, WStringPtr, _charw >( mWStringObjRefMap, string );
}

_void StringTable::MapResourceID( WStringPtr module_name, WStringPtr string, _dword id )
{
	mResNameAndIDMaps[module_name][string] = id;
}

_dword StringTable::GetResourceIDByName( WStringPtr module_name, WStringPtr string ) const
{
	const IDObjMap* res_objs = mResNameAndIDMaps.Search( module_name );
	if ( res_objs == _null )
		return 0;

	const _dword* id = res_objs->Search( string );
	if ( id == _null )
		return 0;

	return *id;
}

WStringPtr StringTable::GetResourceNameByID( WStringPtr module_name, _dword id ) const
{
	const IDObjMap* res_objs = mResNameAndIDMaps.Search( module_name );
	if ( res_objs == _null )
		return L"";

	for ( IDObjMap::Iterator it = res_objs->GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		if ( it.GetObject( ) == id )
			return it.GetKey( );
	}

	return L"";
}
