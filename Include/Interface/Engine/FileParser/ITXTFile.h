//! @file     ITXTFile.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ITXTFile
//----------------------------------------------------------------------------

class ITXTFile : public IBaseFile
{
public:
	//!	Get the encode type.
	//!	@param		none.
	//!	@return		The encode type.
	virtual _ENCODING GetEncodeType( ) const PURE;

	//!	Read all text characters into string.
	//!	@param		string			The string would store all text file characters.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadString( WString& string ) PURE;

	//!	Read the single line string in ANSI mode.
	//!	@param		string			The ANSI string.
	//!	@param		linenumber		The line number of it.
	//! @return		True indicates still has text need to read, otherwise indicates finished reading all texts.
	virtual _ubool ReadLine( AString& string, _dword* linenumber = _null ) PURE;
	//!	Read the single line string in UNICODE mode.
	//!	@param		string			The UNICODE string.
	//!	@param		linenumber		The line number of it.
	//! @return		True indicates still has text need to read, otherwise indicates finished reading all texts.
	virtual _ubool ReadLine( WString& string, _dword* linenumber = _null ) PURE;

	//!	Jump to the specific line.
	//!	@param		linenumber		The line number.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool JumpToLine( _dword linenumber ) PURE;
};

}