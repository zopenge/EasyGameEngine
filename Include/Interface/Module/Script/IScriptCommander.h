//! @file     IScriptCommander.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IScriptCommander
//----------------------------------------------------------------------------

class IScriptCommander : public IObject
{
public:
	//!	Read the script string.
	//!	@param		filename	The script file name.
	//!	@param		string		The script string.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadScriptString( AStringPtr filename, AString& string ) PURE;
};

}