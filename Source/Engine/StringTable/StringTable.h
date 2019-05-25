//! @file     StringTable.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// StringTable
//----------------------------------------------------------------------------

class StringTable : public INTERFACE_OBJECT_IMPL( IStringTable )
{
private:
	typedef Map< WStringObj, _crcvalue > WStringObjMap;
	typedef Map< UStringObj, _crcvalue > UStringObjMap;
	typedef Map< AStringObj, _crcvalue > AStringObjMap;

	typedef Map< _dword, WString > IDObjMap;
	typedef Map< IDObjMap, WString > IDObjMaps;

private:
	//!	The thread locker
	Lock			mLocker;

	//!	The total size in bytes
	_dword			mTotalSize;

	//!	The null string object
	AStringObj		mNullAStringObj;
	UStringObj		mNullUStringObj;
	WStringObj		mNullWStringObj;

	//!	The referenced string objects map
	AStringObjMap	mAStringObjRefMap;
	UStringObjMap	mUStringObjRefMap;
	WStringObjMap	mWStringObjRefMap;

	//!	The (string, ID) resource objects map
	IDObjMaps		mResNameAndIDMaps;

private:
	//!	Clear ref string map.
	template< typename MapType >
	_void TClearObjMap( MapType& obj_map );

	//!	Get ref string with ID.
	template< typename MapType, typename StringObjType, typename Type, typename CharType >
	const StringObjType& TGetRefString( MapType& obj_map, const Type& string, _crcvalue id );
	//!	Get ref string.
	template< typename MapType, typename StringObjType, typename Type, typename CharType >
	const StringObjType& TGetRefString( MapType& obj_map, const Type& string );
	//!	Search ref string.
	template< typename MapType, typename StringObjType, typename Type >
	const StringObjType& TSearchRefString( const MapType& obj_map, const Type& string ) const;

	template< typename MapType, typename StringObjType >
	const StringObjType& TSearchRefString( const MapType& obj_map, _dword id ) const;

public:
	StringTable( );
	virtual ~StringTable( );

public:
	_void ClearAllStrings( );

// IStringTable Interface
public:
	virtual _dword				GetTotalSize( ) const override;

	virtual const AStringObj&	GetNullAString( ) const override;
	virtual const UStringObj&	GetNullUString( ) const override;
	virtual const WStringObj&	GetNullWString( ) const override;

	virtual const AStringObj&	GetRefString( const ARawString& string ) override;
	virtual const AStringObj&	GetRefString( AStringPtr string ) override;
	virtual const AStringObj&	GetRefString( const AString& string ) override;
	virtual const AStringObj&	SearchRefAStringByID( _dword id ) const override;
	virtual const AStringObj&	SearchRefString( const ARawString& string ) const override;
	virtual const AStringObj&	SearchRefString( AStringPtr string ) const override;

	virtual const UStringObj&	GetRefString( const URawString& string ) override;
	virtual const UStringObj&	GetRefString( UStringPtr string ) override;
	virtual const UStringObj&	GetRefString( const UString& string ) override;
	virtual const UStringObj&	SearchRefUStringByID( _dword id ) const override;
	virtual const UStringObj&	SearchRefString( const URawString& string ) const override;
	virtual const UStringObj&	SearchRefString( UStringPtr string ) const override;

	virtual const WStringObj&	GetRefString( const WRawString& string ) override;
	virtual const WStringObj&	GetRefString( WStringPtr string ) override;
	virtual const WStringObj&	GetRefString( const WString& string ) override;
	virtual const WStringObj&	SearchRefWStringByID( _dword id ) const override;
	virtual const WStringObj&	SearchRefString( const WRawString& string ) const override;
	virtual const WStringObj&	SearchRefString( WStringPtr string ) const override;

	virtual const AStringObj&	GetRefString( const _chara* string ) override;
	virtual const WStringObj&	GetRefString( const _charw* string ) override;

	virtual _void				MapResourceID( WStringPtr module_name, WStringPtr name, _dword id ) override;
	virtual _dword				GetResourceIDByName( WStringPtr module_name, WStringPtr name ) const override;
	virtual WStringPtr			GetResourceNameByID( WStringPtr module_name, _dword id ) const override;
};

}