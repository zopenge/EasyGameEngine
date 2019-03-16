//! @file     IGUIResourceManager.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGUIResourceManager
//----------------------------------------------------------------------------

class IGUIResourceManager : public IObject
{
public:
	//!	Create GUI object.
	//!	@param		template_guiobject	The template gui object.
	//! @param		suffix				The new gui object name's suffix.
	//! @param		parent_guiobject	The new gui object's parent.
	//!	@return		The GUI object interface.
	virtual IGUIObject* CreateGUIObject( IGUIObject* template_guiobject, WStringPtr suffix, IGUIContainer* parent_guiobject, _ubool deep ) PURE;
	//!	Create GUI object.
	//!	@param		template_guiobject	The template gui object.
	//! @param		gui_object_typename	The new gui object's type name.	such as FGUIContainer(static) FGUIContainerForm(button)
	//! @param		suffix				The new gui object name's suffix.
	//! @param		parent_guiobject	The new gui object's parent.
	//!	@return		The GUI object interface.
	virtual IGUIObject* CreateGUIObject( IGUIObject* template_guiobject, WStringPtr gui_object_typename, WStringPtr suffix, IGUIContainer* parent_guiobject, _ubool deep ) PURE;
	//!	Create GUI object from XML string.
	//!	@param		type			The GUI type string.
	//!	@param		xml_string		The XML string.
	//! @param		parent_object	The object's parent.
	//!	@return		The GUI object interface.
	virtual IGUIObject* CreateGUIObjectFromXMLString( WStringPtr type, WStringPtr xml_string, IGUIContainer* parent_object ) PURE;

	//!	Create GUI application.
	//!	@param		parent		The parent container.
	//!	@return		The GUI application interface.
	virtual IGUIApplication* CreateGUIApplication( IGUIContainer* parent ) PURE;
	//!	Create GUI application.
	//!	@param		node		The serializable node.
	//!	@param		parent		The parent container.
	//!	@param		delay_load	True indicates load the GUI resources in delay way.
	//!	@return		The GUI application interface.
	virtual IGUIApplication* CreateGUIApplication( ISerializableNode* node, IGUIContainer* parent, _ubool delay_load ) PURE;
};

}