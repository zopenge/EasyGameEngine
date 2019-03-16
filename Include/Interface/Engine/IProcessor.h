//! @file     IProcessor.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IProcessor
//----------------------------------------------------------------------------

template< typename Type >
class IProcessor : public Type
{
public:
	//!	Get the state.
	//!	@param		none.
	//! @return		The state of task.
	virtual _PROCESS_STATE GetState( ) const PURE;

	//!	Wait.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Wait( ) PURE;
	//!	Start.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Start( ) PURE;
	//!	Resume.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Resume( ) PURE;
	//!	Suspend.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Suspend( ) PURE;
	//!	Abort.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Abort( ) PURE;
	//!	Finish.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Finish( ) PURE;
};

}