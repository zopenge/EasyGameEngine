//! @file     ISoundSourceCallback.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ISoundSourceCallback
//----------------------------------------------------------------------------

class ISoundSourceCallback
{
public:
	//!	When play sound.
	//!	@param		parameters	The user defined parameters.
	//!	@return		none.
	virtual _void OnPlay( const QwordParameters2& parameters ) PURE;
	//!	When stop sound.
	//!	@param		parameters	The user defined parameters.
	//!	@return		none.
	virtual _void OnStop( const QwordParameters2& parameters ) PURE;
	//!	When resume sound.
	//!	@param		parameters	The user defined parameters.
	//!	@return		none.
	virtual _void OnResume( const QwordParameters2& parameters ) PURE;
	//!	When pause sound.
	//!	@param		parameters	The user defined parameters.
	//!	@return		none.
	virtual _void OnPause( const QwordParameters2& parameters ) PURE;
};

}