//! @file     GUIComponentUtils.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GUIComponentUtils
//----------------------------------------------------------------------------

class GUIComponentUtils
{
public:
	//!	When query GUI state enumeration value.
	static _dword OnQueryGUIStateEnumValue( WStringPtr name, const QwordParameters2& parameters );
	//!	When query GUI state enumeration name.
	static const _charw* OnQueryGUIStateEnumName( _dword value, const QwordParameters2& parameters );
};

//----------------------------------------------------------------------------
// GUIComponentUtils Implementation
//----------------------------------------------------------------------------

}