//! @file     ISoundModule.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ISoundModule
//----------------------------------------------------------------------------

class ISoundModule : public IModule
{
public:
	//!	Enable/Disable options.
	//!	@param		options		The options, @see _SOUND_OPTIONS.
	//!	@param		enable		True indicates enable options, otherwise disable.
	//!	@return		none.
	virtual _void EnableOptions( _dword options, _ubool enable ) PURE;
	//!	Check enable options or not.
	//!	@param		options		The options, @see _SOUND_OPTIONS.
	//!	@return		True indicates these options enabled, otherwise disable.
	virtual _ubool IsEnableOptions( _dword options ) const PURE;
};

}