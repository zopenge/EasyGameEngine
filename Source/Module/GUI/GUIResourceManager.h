//! @file     GUIResourceManager.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GUIResourceManager
//----------------------------------------------------------------------------

class GUIResourceManager : public INTERFACE_OBJECT_IMPL( IGUIResourceManager )
{
public:
	GUIResourceManager( );
	virtual ~GUIResourceManager( );

// IGUIResourceManager Interface
public:
	virtual IGUIObject*				CreateGUIObject( IGUIObject* template_guiobject, WStringPtr suffix, IGUIContainer* parent_guiobject, _ubool deep ) override;
	virtual IGUIObject*				CreateGUIObject( IGUIObject* template_guiobject, WStringPtr gui_object_typename, WStringPtr suffix, IGUIContainer* parent_guiobject, _ubool deep ) override;
	virtual IGUIObject*				CreateGUIObjectFromXMLString( WStringPtr type, WStringPtr xml_string, IGUIContainer* parent_object ) override;

	virtual IGUIApplication*		CreateGUIApplication( IGUIContainer* parent ) override;
	virtual IGUIApplication*		CreateGUIApplication( ISerializableNode* node, IGUIContainer* parent, _ubool delay_load ) override;
};

}