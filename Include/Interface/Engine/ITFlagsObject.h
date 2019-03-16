//! @file     ITFlagsObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ITFlagsObject
//----------------------------------------------------------------------------

template< typename Type >
class ITFlagsObject : public Type
{
public:
	//!	Check whether has the specified flags or not.
	//!	@param		flags		The flags would be checked.
	//!	@param		match_all	True indicates must match all flags.
	//!	@return		True indicates has this flag.
	virtual _ubool HasFlags( _dword flags, _ubool match_all = _false ) const PURE;
	//!	Enable/Disable flag.
	//!	@param		flags		The flags would be checked.
	//!	@param		enable		True indicates enable it.
	//!	@return		none.
	virtual _void EnableFlags( _dword flags, _ubool enable ) PURE;
	//!	Combine flags.
	//!	@param		flags		The flags would be combined.
	//!	@return		none.
	virtual _void CombineFlags( _dword flags ) PURE;
	//!	Clear flags.
	//!	@param		flags		The flags would be cleared.
	//!	@return		none.
	virtual _void ClearFlags( _dword flags ) PURE;

	//!	Set the flags.
	//!	@param		flags		The flags.
	//!	@return		none.
	virtual _void SetFlags( _dword flags ) PURE;
	//!	Get the flags.
	//!	@param		none.
	//!	@return		The flags.
	virtual _dword GetFlags( ) const PURE;
	//!	Get the flags object.
	//!	@param		none.
	//!	@return		The flags object.
	virtual const FlagsObject& GetFlagsObject( ) const PURE;
};

}