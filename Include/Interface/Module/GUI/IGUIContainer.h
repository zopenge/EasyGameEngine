//! @file     IGUIContainer.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGUIContainer
//----------------------------------------------------------------------------

class IGUIContainer : public IGUIObject
{
public:
	//!	Clear all child objects.
	//!	@param		none.
	//!	@return		none.
	virtual _void ClearAllChildObjects( ) PURE;

	//!	Clear all child objects except for the first child.
	//!	@param		none.
	//!	@return		none.
	virtual _void ClearAllChildObjectsExceptForFirst( ) PURE;

	//!	Clear all child objects except for the first child.
	//!	@param		none.
	//!	@return		none.
	virtual _void ClearAllChildObjectsExceptFor( IGUIObject* gui_object ) PURE;

	//!	Get child objects.
	//!	@param		recursive	True indicates search recursively.
	//!	@return		The child objects.
	virtual IGUIObjectRefArray GetChildObjects( _ubool recursive ) PURE;

	//!	Search for the child object by path.
	//!	@param		path		The GUI object path, use '/' as level split.
	//!	@param		ignorecase	True indicates case insensitive when compare.
	//!	@return		The GUI object interface.
	virtual IGUIObject* SearchControlByPath( WStringPtr path, _ubool ignorecase ) PURE;
	//!	Search for the child object by name.
	//!	@param		name		The GUI object name.
	//!	@param		ignorecase	True indicates case insensitive when compare.
	//!	@return		The GUI object interface.
	virtual IGUIObject* SearchControlByName( WStringPtr name, _ubool ignorecase ) PURE;
	//!	Search for the child object by name.
	//!	@param		name		The GUI object name.
	//!	@param		recursive	True indicates search recursively.
	//!	@param		ignorecase	True indicates case insensitive when compare.
	//!	@return		The GUI object interface.
	virtual IGUIObject* SearchControlByName( WStringPtr name, _ubool recursive, _ubool ignorecase ) PURE;
	//!	Locate at the child application and search for the child object by name of it.
	//!	@param		child_app		The child app name.
	//!	@param		control_name	The control name.
	//!	@return		The GUI object interface.
	virtual	IGUIObject* LocateAtChildAppAndSearchByName( WStringPtr child_app, WStringPtr control_name ) PURE;

	//!	Remove control/container by name.
	//!	@remark		Remove the link without caring referenced count.
	//!	@param		name		The GUI object name.
	//!	@param		recursive	True indicates search recursively.
	//!	@param		ignorecase	True indicates case insensitive when compare.
	//!	@return		True indicates remove successful.
	virtual _ubool RemoveGUIObjectByName( WStringPtr name, _ubool recursive, _ubool ignorecase ) PURE;

	virtual IGUIObject* GetCheckedChildObject( ) PURE;
	virtual IGUIObjectRefArray GetCheckedChildObjects( ) PURE;
};

}