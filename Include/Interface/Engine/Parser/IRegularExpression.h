//! @file     IRegularExpression.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IRegularExpression
//----------------------------------------------------------------------------

class IRegularExpression : public IObject
{
public:
	enum _MATCH_OPTION
	{
		_MATCH_CASELESS	= 1 << 0,
	};

public:
	//!	Set the pattern.
	//!	@param		pattern		The pattern string.
	//!	@param		options		The options.
	//! @return		True indicates success false indicates failure.
	virtual _ubool SetPattern( WStringPtr pattern, _dword options = _MATCH_CASELESS ) PURE;
	//!	Get the pattern.
	//!	@param		none.
	//! @return		The pattern string.
	virtual WStringPtr GetPattern( ) const PURE;

	//!	Check whether match ANSI string or not.
	//!	@param		string		The string what to be matched.
	//!	@return		True indicates match successful.
	virtual _ubool Match( AStringPtr string ) const PURE;
	//!	Check whether match UNICODE string or not.
	//!	@param		string		The string what to be matched.
	//!	@return		True indicates match successful.
	virtual _ubool Match( WStringPtr string ) const PURE;
};

}