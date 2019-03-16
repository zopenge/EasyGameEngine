//! @file     _t_scriptSystem.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _t_scriptSystem
//----------------------------------------------------------------------------

template< typename Type >
class _t_scriptSystem : public TObject< Type >
{
protected:
	//!	The script module list
	typedef Array< _scriptModuleRef > _scriptModuleArray;

protected:
	//!	The script version
	Version				mVersion;

	//!	The total memory size
	_dword				mTotalMemSize;

	//!	The remote address
	Address				mRemoteAddress;

	//!	The module list
	_scriptModuleArray	mModules;

protected:
	_t_scriptSystem( );
	virtual ~_t_scriptSystem( );

// _scriptSystem Interface
public:
	virtual _dword			GetTotalMemSize( ) const override;

	virtual _ubool			SetRemoteDebugger( const Address& address ) override;
	virtual const Address&	GetRemoteDebugger( ) const override;
};

//----------------------------------------------------------------------------
// _t_scriptSystem Implementation
//----------------------------------------------------------------------------

template< typename Type >
_t_scriptSystem< Type >::_t_scriptSystem( )
{
	mVersion		= Version::cZero;

	mTotalMemSize	= 0;

	mRemoteAddress	= Address::cNullAddress;
}

template< typename Type >
_t_scriptSystem< Type >::~_t_scriptSystem( )
{

}

template< typename Type >
_dword _t_scriptSystem< Type >::GetTotalMemSize( ) const
{
	return mTotalMemSize;
}

template< typename Type >
_ubool _t_scriptSystem< Type >::SetRemoteDebugger( const Address& address )
{
	if ( address.IsValid( ) == _false )
		return _false;

	mRemoteAddress = address;

	return _true;
}

template< typename Type >
const Address& _t_scriptSystem< Type >::GetRemoteDebugger( ) const
{
	return mRemoteAddress;
}

}