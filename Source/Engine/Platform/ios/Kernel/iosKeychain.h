//! @file     iosKeychain.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// iosKeychain
//----------------------------------------------------------------------------

class iosKeychain : public INTERFACE_OBJECT_IMPL( IKeychain )
{
	INTERNAL_HANDLER_DECL( );

public:
	iosKeychain( );
	virtual ~iosKeychain( );

public:
	//! Initialize.
	_ubool Initialize( WStringPtr identifier, WStringPtr access_group );

// IKeychain Interface
public:
	virtual _ubool Reset( ) override;

	virtual _ubool SetObject( _KEY key, WStringPtr value ) override;
	virtual _ubool GetObject( _KEY key, WString& value ) const override;
};

}