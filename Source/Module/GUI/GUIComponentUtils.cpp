//! @file     GUIComponentUtils.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGUI.h"

//----------------------------------------------------------------------------
// GUIComponentUtils Implementation
//----------------------------------------------------------------------------

_dword GUIComponentUtils::OnQueryGUIStateEnumValue( WStringPtr name, const QwordParameters2& parameters )
{
	if ( name == L"Normal" )
		return _GUI_STATE_NORMAL;
	else if ( name == L"Focus" )
		return _GUI_STATE_FOCUS;
	else if ( name == L"Hover" )
		return _GUI_STATE_HOVER;
	else if ( name == L"Disable" )
		return _GUI_STATE_DISABLE;
	else if ( name == L"CheckNormal" )
		return _GUI_STATE_CHECKED;
	else if ( name == L"CheckFocus" )
		return _GUI_STATE_CHECKED_FOCUS;
	else if ( name == L"CheckHover" )
		return _GUI_STATE_CHECKED_HOVER;
	else if ( name == L"CheckDisable" )
		return _GUI_STATE_CHECKED_DISABLE;

	return _GUI_STATE_UNKNOWN;
}

const _charw* GUIComponentUtils::OnQueryGUIStateEnumName( _dword value, const QwordParameters2& parameters )
{
	if ( value == _GUI_STATE_NORMAL )
		return L"Normal";
	else if ( value == _GUI_STATE_FOCUS )
		return L"Focus";
	else if ( value == _GUI_STATE_HOVER )
		return L"Hover";
	else if ( value == _GUI_STATE_DISABLE )
		return L"Disable";
	else if ( value == _GUI_STATE_CHECKED)
		return L"CheckNormal";
	else if ( value == _GUI_STATE_CHECKED_FOCUS )
		return L"CheckFocus";
	else if ( value == _GUI_STATE_CHECKED_HOVER )
		return L"CheckHover";
	else if ( value == _GUI_STATE_CHECKED_DISABLE )
		return L"CheckDisable";

	return L"";
}