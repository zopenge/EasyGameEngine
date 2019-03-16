//! @file     ITransaction.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ITransaction
//----------------------------------------------------------------------------

class ITransaction : public IThreadTask
{
public:
	//!	Get the transaction ID.
	//!	@param		none.
	//!	@return		The transaction ID.
	virtual _dword GetTransactionID( ) const PURE;
};

}