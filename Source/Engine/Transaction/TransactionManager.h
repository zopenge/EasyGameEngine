//! @file     TransactionManager.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TransactionManager
//----------------------------------------------------------------------------

//! A transaction manager class
class TransactionManager : public INTERFACE_OBSERVER_IMPL( ITransactionManager )
{
private:

// IObserver Interface
private:
	virtual _void 	Notify( const EventBase& event, const IObject* object, const IObservable* generator ) override;

public:
	TransactionManager( );
	virtual ~TransactionManager( );

// ITransactionManager Interface
public:
	virtual _ubool 	Create( _dword thread_number, WStringPtr name = L"" ) override;
	virtual _void 	Close( ) override;

	virtual _ubool 	Start( ) override;
	virtual _ubool 	Stop( ) override;

	virtual _dword	GetThreadNumber( ) const override;

	virtual _ubool	AddTransaction( ITransaction* transaction, ITransaction* depend, _dword features, _dword timeout = -1, const QwordParameters2& parameters = QwordParameters2::cNull ) override;
};

}