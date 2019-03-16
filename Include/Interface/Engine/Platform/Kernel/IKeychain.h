//! @file     IKeychain.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IKeychain
//----------------------------------------------------------------------------

class IKeychain : public IObject
{
public:
	//!	The key type
	enum _KEY
	{
		_KEY_UNKNOWN,

		_KEY_SEC_ATTR_ACCESSGROUP,
		_KEY_SEC_ATTR_CREATIONDATE,
		_KEY_SEC_ATTR_MODIFICATIONDATE,
		_KEY_SEC_ATTR_DESCRIPTION,
		_KEY_SEC_ATTR_COMMENT,
		_KEY_SEC_ATTR_CREATOR,
		_KEY_SEC_ATTR_TYPE,
		_KEY_SEC_ATTR_LABEL,
		_KEY_SEC_ATTR_ISINVISIBLE,
		_KEY_SEC_ATTR_ISNEGATIVE,
		_KEY_SEC_ATTR_ACCOUNT,
		_KEY_SEC_ATTR_SERVICE,
		_KEY_SEC_ATTR_GENERIC,
	};

public:
	//!	Reset.
	//!	@param		none.
	//! @return		True indicates success false indicates failure.
	virtual _ubool Reset( ) PURE;

	//!	Set object.
	//!	@param		key		The key.
	//!	@param		value	The value.
	//! @return		True indicates success false indicates failure.
	virtual _ubool SetObject( _KEY key, WStringPtr value ) PURE;
	//!	Get object.
	//!	@param		key		The key.
	//!	@param		value	The value.
	//! @return		True indicates success false indicates failure.
	virtual _ubool GetObject( _KEY key, WString& value ) const PURE;
};

}