//! @file     IRegistry.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IRegistry
//----------------------------------------------------------------------------

class IRegistry : public IObject
{
public:
	//!	The root key type
	enum _ROOT_KEY
	{
		_KEY_CLASSES_ROOT		= 0x80000000,
		_KEY_CURRENT_USER		= 0x80000001,
		_KEY_LOCAL_MACHINE		= 0x80000002,
		_KEY_USERS				= 0x80000003,
		_KEY_PERFORMANCE_DATA	= 0x80000004,
		_KEY_CURRENT_CONFIG		= 0x80000005,
		_KEY_DYN_DATA			= 0x80000006,
	};

	//!	The key type
	enum _KEY_TYPE
	{
		_TYPE_NONE				= 0,
		_TYPE_STRING			= 1,
		_TYPE_BINARY			= 3,
		_TYPE_DWORD				= 4,
		_TYPE_LINK				= 6,
		_TYPE_QWORD				= 11,
	};

public:
	//!	Get the root key.
	//!	@param		none.
	//!	@return		The root key handle.
	virtual _handle GetRootKey( ) const PURE;

	//! Check whether the key is existing or not.
	//!	@param		keyname		The key name.
	//!	@return		True indicates the key is existing.
	virtual _ubool DoesKeyExist( WStringPtr keyname ) const PURE;
	//! Create key.
	//!	@param		keyname		The key name.
	//! @return		The key handle.
	virtual _handle CreateKey( WStringPtr keyname ) PURE;
	//! Delete key.
	//!	@param		keyname		The key name.
	//! @return		True indicates success false indicates failure.
	virtual _ubool DeleteKey( WStringPtr keyname ) PURE;

	//! Check whether the key value is existing or not.
	//! @param		key			The key handle.
	//!	@param		valuename	The value name.
	//! @return		True indicates success false indicates failure.
	virtual _ubool DoesValueExist( _handle key, WStringPtr valuename ) const PURE;
	//! Read value.
	//! @param		key			The key handle.
	//!	@param		valuename	The value name.
	//!	@param		type		The key type.
	//!	@param		buffer		The buffer what save the key info.
	//!	@param		size		The buffer size.
	//! @return		True indicates success false indicates failure.
	virtual _ubool ReadValue( _handle key, WStringPtr valuename, _KEY_TYPE& type, _void* buffer, _dword& size ) const PURE;
	//! Read value string.
	//! @param		key			The key handle.
	//!	@param		valuename	The value name.
	//!	@param		string		The value string.
	//! @return		True indicates success false indicates failure.
	virtual _ubool ReadValueString( _handle key, WStringPtr valuename, WString& string ) const PURE;
	//! Write value.
	//! @param		key			The key handle.
	//!	@param		valuename	The value name.
	//!	@param		type		The key type.
	//!	@param		buffer		The buffer what save the key info.
	//!	@param		size		The buffer size.
	//! @return		True indicates success false indicates failure.
	virtual _ubool WriteValue( _handle key, WStringPtr valuename, _KEY_TYPE type, const _void* buffer, _dword size ) PURE;
	//! Delete value.
	//! @param		key			The key handle.
	//!	@param		valuename	The value name.
	//! @return		True indicates success false indicates failure.
	virtual _ubool DeleteValue( _handle key, WStringPtr valuename ) PURE;
};

}