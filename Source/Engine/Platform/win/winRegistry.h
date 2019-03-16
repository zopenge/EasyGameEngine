//! @file     winRegistry.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// winRegistry
//----------------------------------------------------------------------------

class winRegistry : public INTERFACE_OBJECT_IMPL( IRegistry )
{
private:
	//!	The root key handle
	HKEY mRootKey;

public:
	winRegistry( );
	virtual ~winRegistry( );

public:
	//! Initialize.
	//!	@param		root		The root key type.
	//!	@param		keyname		The key name.
	//! @return		True indicates success, false indicates failure.
	_ubool Initialize( _ROOT_KEY root, WStringPtr keyname );

// IRegistry Interface
public:
	virtual _handle GetRootKey( ) const override;

	virtual _ubool	DoesKeyExist( WStringPtr keyname ) const override;
	virtual _handle CreateKey( WStringPtr keyname ) override;
	virtual _ubool	DeleteKey( WStringPtr keyname ) override;

	virtual _ubool 	DoesValueExist( _handle key, WStringPtr valuename ) const override;
	virtual _ubool 	ReadValue( _handle key, WStringPtr valuename, _KEY_TYPE& type, _void* buffer, _dword& size ) const override;
	virtual _ubool 	ReadValueString( _handle key, WStringPtr valuename, WString& string ) const override;
	virtual _ubool 	WriteValue( _handle key, WStringPtr valuename, _KEY_TYPE type, const _void* buffer, _dword size ) override;
	virtual _ubool 	DeleteValue( _handle key, WStringPtr valuename ) override;
};

}