//! @file     TModule.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TModule
//----------------------------------------------------------------------------

template< typename Type >
class TModule : public TPowerable< Type >
{
protected:
	//!	The module name
	WString	mModuleName;
	//!	The module version
	Version	mModuleVersion;

protected:
	TModule( WStringPtr name, const Version& version );
	virtual ~TModule( );

// IModule Interface
public:
	virtual _ubool			ResetResources( ) override;
	virtual _void			UnloadResources( ) override;

	virtual WStringPtr		GetModuleName( ) const override;
	virtual const Version&	GetModuleVersion( ) const override;

	virtual _void			OutputString( _LOG type, AStringPtr string, AStringPtr file_name = "", _dword line_number = 0 ) override;
	virtual _void			OutputString( _LOG type, WStringPtr string, WStringPtr file_name = L"", _dword line_number = 0 ) override;

	virtual _void			HandleEvent( EventBase& event ) override;
};

//----------------------------------------------------------------------------
// TModule Implementation
//----------------------------------------------------------------------------

template< typename Type >
TModule< Type >::TModule( WStringPtr name, const Version& version )
{
	mModuleName		= name;
	mModuleVersion	= version;
}

template< typename Type >
TModule< Type >::~TModule( )
{
}

template< typename Type >
_ubool TModule< Type >::ResetResources( )
{
	return _true;
}

template< typename Type >
_void TModule< Type >::UnloadResources( )
{

}

template< typename Type >
WStringPtr TModule< Type >::GetModuleName( ) const
{
	return mModuleName;
}

template< typename Type >
const Version& TModule< Type >::GetModuleVersion( ) const
{
	return mModuleVersion;
}

template< typename Type >
_void TModule< Type >::OutputString( _LOG type, AStringPtr string, AStringPtr file_name, _dword line_number )
{
	WString string_unicode;
	string_unicode.FromString( string );

	WString filename_unicode;
	filename_unicode.FromString( file_name );

	OutputString( type, string_unicode, filename_unicode, line_number );
}

template< typename Type >
_void TModule< Type >::OutputString( _LOG type, WStringPtr string, WStringPtr file_name, _dword line_number )
{
	// Notify all observers when we are outputting string
	EventOutputString event;
	event.mType			= type;
	event.mCategory		= mModuleName; // Use the module name as LOG category
	event.mString		= string;
	event.mFileName		= file_name;
	event.mLineNumber	= line_number;
	this->NotifyObservers( this, event );
}

template< typename Type >
_void TModule< Type >::HandleEvent( EventBase& event )
{
}

}