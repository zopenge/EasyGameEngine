//! @file     IOperationRecordPerformer.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IOperationRecordPerformer
//----------------------------------------------------------------------------

class IOperationRecordPerformer : public IObject
{
public:
	//!	When perform operation.
	//!	@param		is_undo			True indicates it's undo action.
	//!	@param		key				The key.
	//!	@param		stream_reader	The record stream info.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool OnDo( _ubool is_undo, WStringPtr key, IStreamReader* stream_reader ) PURE;
};

}