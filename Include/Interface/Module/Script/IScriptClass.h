//! @file     IScriptClass.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IScriptClass
//----------------------------------------------------------------------------

class IScriptClass : public IObject
{
public:
	//!	Register enumeration value.
	//!	@param		name			The enumeration name.
	//!	@param		value			The enumeration value.
	//!	@param		desc			The enumeration description.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool RegisterEnumValue( AStringPtr name, _dword value, AStringPtr desc ) PURE;
	//!	Register the property of class.
	//! @param		decl			The property declaration.
	//! @param		offset			The property offset in bytes.
	//! @param		desc			The property description.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool RegisterProperty( AStringPtr decl, _dword offset, AStringPtr desc ) PURE;

	//!	Get the class declaration info.
	//!	@param		none.
	//!	@return		The class declaration info.
	virtual const ScriptClassDeclInfo& GetDeclInfo( ) const PURE;

	//!	Register native function.
	//!	@param		decl			The function declaration.
	//!	@param		funcpointer		The function pointer.
	//!	@param		desc			The function description.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool RegisterFunction( AStringPtr decl, const ScriptFuncPtr& funcpointer, AStringPtr desc ) PURE;
};

}