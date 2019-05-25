//! @file     ITransactionManager.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ITransactionManager
//----------------------------------------------------------------------------

class ITransactionManager : public IObserver
{
public:
	//!	Create.
	//!	@param		thread_number	The thread worker number.
	//!	@param		name			The thread pool name.
	//! @return		True indicates success false indicates failure.
	virtual _ubool Create( _dword thread_number, WStringPtr name = L"" ) PURE;
	//!	Close.
	//!	@param		none.
	//!	@return		none.
	virtual _void Close( ) PURE;

	//!	Start to process transactions what had been added.
	//!	@param		none.
	//! @return		True indicates success false indicates failure.
	virtual _ubool Start( ) PURE;
	//!	Stop to process transactions.
	//!	@param		none.
	//! @return		True indicates success false indicates failure.
	virtual _ubool Stop( ) PURE;

	//!	Get the thread number.
	//!	@param		none.
	//!	@return		The thread number.
	virtual _dword GetThreadNumber( ) const PURE;

	//!	Add transaction.
	//!	@param		transaction		The transaction.
	//!	@param		depend			The depend transaction.
	//!	@param		features		The features of transaction.
	//!	@param		timeout			The timeout of task in milliseconds.
	//!	@param		params		The user defined params.
	//! @return		True indicates success false indicates failure.
	virtual _ubool AddTransaction( ITransaction* transaction, ITransaction* depend, _dword features, _dword timeout = -1, const QwordParameters2& params = QwordParameters2::cNull ) PURE;
};

}