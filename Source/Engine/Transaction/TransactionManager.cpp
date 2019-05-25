//! @file     TransactionManager.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// TransactionManager Implementation
//----------------------------------------------------------------------------

TransactionManager::TransactionManager( )
{
}

TransactionManager::~TransactionManager( )
{
	Close( );
}

_void TransactionManager::Notify( const EventBase& event, const IObject* object, const IObservable* generator )
{

}

_ubool TransactionManager::Create( _dword thread_number, WStringPtr name )
{
	return _true;
}

_void TransactionManager::Close( )
{
}

_ubool TransactionManager::Start( )
{
	return _true;
}

_ubool TransactionManager::Stop( )
{
	return _true;
}

_dword TransactionManager::GetThreadNumber( ) const
{
	return 0;
}

_ubool TransactionManager::AddTransaction( ITransaction* transaction, ITransaction* depend, _dword features, _dword timeout, const QwordParameters2& params )
{
	return _true;
}