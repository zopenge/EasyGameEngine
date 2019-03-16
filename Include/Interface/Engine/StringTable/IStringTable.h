//! @file     IStringTable.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IStringTable
//----------------------------------------------------------------------------

class IStringTable : public IObject
{
public:
	//!	Get the total size in bytes.
	//!	@param		none.
	//!	@return		The total size in bytes.
	virtual _dword GetTotalSize( ) const PURE;

	//!	Get the referenced null string object.
	//!	@param		none
	//!	@return		The referenced string object wrapper.
	virtual const AStringObj& GetNullAString( ) const PURE;
	//!	Get the referenced null string object.
	//!	@param		none
	//!	@return		The referenced string object wrapper.
	virtual const UStringObj& GetNullUString( ) const PURE;
	//!	Get the referenced null string object.
	//!	@param		none
	//!	@return		The referenced string object wrapper.
	virtual const WStringObj& GetNullWString( ) const PURE;

	//!	Get the referenced string object.
	//!	@remark		If the string is not referenced object then will auto-create it.
	//!	@param		string		The string.
	//!	@return		The referenced string object wrapper.
	virtual const AStringObj& GetRefString( const ARawString& string ) PURE;
	//!	Get the referenced string object.
	//!	@remark		If the string is not referenced object then will auto-create it.
	//!	@param		string		The string.
	//!	@return		The referenced string object wrapper.
	virtual const AStringObj& GetRefString( AStringPtr string ) PURE;
	//!	Get the referenced string object.
	//!	@remark		If the string is not referenced object then will auto-create it.
	//!	@param		string		The string.
	//!	@return		The referenced string object wrapper.
	virtual const AStringObj& GetRefString( const AStringR& string ) PURE;
	//!	Search the referenced string object.
	//!	@param		id			The string id.
	//!	@return		The referenced string object wrapper.
	virtual const AStringObj& SearchRefAStringByID( _dword id ) const PURE;
	//!	Search the referenced string object.
	//!	@param		string		The string.
	//!	@return		The referenced string object wrapper.
	virtual const AStringObj& SearchRefString( const ARawString& string ) const PURE;
	//!	Search the referenced string object.
	//!	@param		string		The string.
	//!	@return		The referenced string object wrapper.
	virtual const AStringObj& SearchRefString( AStringPtr string ) const PURE;

	//!	Get the referenced string object.
	//!	@remark		If the string is not referenced object then will auto-create it.
	//!	@param		string		The string.
	//!	@return		The referenced string object wrapper.
	virtual const UStringObj& GetRefString( const URawString& string ) PURE;
	//!	Get the referenced string object.
	//!	@remark		If the string is not referenced object then will auto-create it.
	//!	@param		string		The string.
	//!	@return		The referenced string object wrapper.
	virtual const UStringObj& GetRefString( UStringPtr string ) PURE;
	//!	Get the referenced string object.
	//!	@remark		If the string is not referenced object then will auto-create it.
	//!	@param		string		The string.
	//!	@return		The referenced string object wrapper.
	virtual const UStringObj& GetRefString( const UStringR& string ) PURE;
	//!	Search the referenced string object.
	//!	@param		id			The string id.
	//!	@return		The referenced string object wrapper.
	virtual const UStringObj& SearchRefUStringByID( _dword id ) const PURE;
	//!	Search the referenced string object.
	//!	@param		string		The string.
	//!	@return		The referenced string object wrapper.
	virtual const UStringObj& SearchRefString( const URawString& string ) const PURE;
	//!	Search the referenced string object.
	//!	@param		string		The string.
	//!	@return		The referenced string object wrapper.
	virtual const UStringObj& SearchRefString( UStringPtr string ) const PURE;

	//!	Get the referenced string object.
	//!	@remark		If the string is not referenced object then will auto-create it.
	//!	@param		string		The string.
	//!	@return		The referenced string object wrapper.
	virtual const WStringObj& GetRefString( const WRawString& string ) PURE;
	//!	Get the referenced string object.
	//!	@remark		If the string is not referenced object then will auto-create it.
	//!	@param		string		The string.
	//!	@return		The referenced string object wrapper.
	virtual const WStringObj& GetRefString( WStringPtr string ) PURE;
	//!	Get the referenced string object.
	//!	@remark		If the string is not referenced object then will auto-create it.
	//!	@param		string		The string.
	//!	@return		The referenced string object wrapper.
	virtual const WStringObj& GetRefString( const WStringR& string ) PURE;
	//!	Search the referenced string object.
	//!	@param		id			The string id.
	//!	@return		The referenced string object wrapper.
	virtual const WStringObj& SearchRefWStringByID( _dword id ) const PURE;
	//!	Search the referenced string object.
	//!	@param		string		The string.
	//!	@return		The referenced string object wrapper.
	virtual const WStringObj& SearchRefString( const WRawString& string ) const PURE;
	//!	Search the referenced string object.
	//!	@param		string		The string.
	//!	@return		The referenced string object wrapper.
	virtual const WStringObj& SearchRefString( WStringPtr string ) const PURE;

	//!	Get the referenced string object.
	//!	@remark		If the string is not referenced object then will auto-create it.
	//!	@param		string		The string.
	//!	@return		The referenced string object wrapper.
	virtual const AStringObj& GetRefString( const _chara* string ) PURE;
	//!	Get the referenced string object.
	//!	@remark		If the string is not referenced object then will auto-create it.
	//!	@param		string		The string.
	//!	@return		The referenced string object wrapper.
	virtual const WStringObj& GetRefString( const _charw* string ) PURE;

	//!	Map the resource ID and name.
	//!	@param		module_name	The module name.
	//!	@param		name		The resource name.
	//!	@param		id			The resource ID, 0 indicates failure.
	//!	@return		none.
	virtual _void MapResourceID( WStringPtr module_name, WStringPtr name, _dword id ) PURE;
	//!	Get the resource ID by name.
	//!	@param		module_name	The module name.
	//!	@param		name		The resource name.
	//!	@return		The resource ID, 0 indicates failure.
	virtual _dword GetResourceIDByName( WStringPtr module_name, WStringPtr name ) const PURE;
	//!	Get the resource name by ID.
	//!	@param		module_name	The module name.
	//!	@param		id			The resource ID, 0 indicates failure.
	//!	@return		The resource name.
	virtual WStringPtr GetResourceNameByID( WStringPtr module_name, _dword id ) const PURE;
};

}