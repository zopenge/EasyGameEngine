//! @file     GUIResourceManager.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGUI.h"

//----------------------------------------------------------------------------
// GUIResourceManager Implementation
//----------------------------------------------------------------------------

GUIResourceManager::GUIResourceManager( )
{
	// Register internal components
	RTTI_CLASS_WITH_ARGUMENTS_IMPL( GUIComponentAnimation );
	RTTI_CLASS_WITH_ARGUMENTS_IMPL( GUIComponentColor );
	RTTI_CLASS_WITH_ARGUMENTS_IMPL( GUIComponentPosition );
	RTTI_CLASS_WITH_ARGUMENTS_IMPL( GUIComponentState );
	RTTI_CLASS_WITH_ARGUMENTS_IMPL( GUIComponentEventHooker );
	RTTI_CLASS_WITH_ARGUMENTS_IMPL( GUIComponent3DRender );
	RTTI_CLASS_WITH_ARGUMENTS_IMPL( GUIComponentClick );
	RTTI_CLASS_WITH_ARGUMENTS_IMPL( GUIComponentGroup );

	// Register internal controls
	RTTI_CLASS_IMPL( GUIApplication );
}

GUIResourceManager::~GUIResourceManager( )
{
}

IGUIObject* GUIResourceManager::CreateGUIObject( IGUIObject* template_guiobject, WStringPtr suffix, IGUIContainer* parent_guiobject, _ubool deep )
{
	if ( template_guiobject == _null )
		return _null;

	IGUIObject* new_guiobject = (IGUIObject*) template_guiobject->CloneSelfTo( );
	if ( new_guiobject == _null )
		return _null;

	new_guiobject->SetResName( template_guiobject->GetResName( ) + suffix );

	if ( parent_guiobject != _null )
		parent_guiobject->InsertChildObject( new_guiobject );

	if ( deep )
	{
		if ( template_guiobject->IsContainer( ) )
		{
			IGUIContainer* new_guicontainer = (IGUIContainer*)new_guiobject;
			for ( IGUIObject* it = template_guiobject->FirstChildObject( ); it != _null; it = it->NextObject( ) )
                CreateGUIObject( it, suffix, new_guicontainer, deep );
		}
	}
	
	return new_guiobject;
}

IGUIObject* GUIResourceManager::CreateGUIObject( IGUIObject* template_guiobject, WStringPtr gui_object_typename, WStringPtr suffix, IGUIContainer* parent_guiobject, _ubool deep )
{
	if ( template_guiobject == _null )
		return _null;

	IGUIObject* new_guiobject = (IGUIObject*) template_guiobject->CloneSelfTo( );
	if ( new_guiobject == _null )
		return _null;

	new_guiobject->SetResName( template_guiobject->GetResName( ) + suffix );

	if ( parent_guiobject != _null )
		parent_guiobject->InsertChildObject( new_guiobject );

	if ( deep )
	{
		if ( new_guiobject->IsContainer( ) )
		{
			IGUIContainer* new_guicontainer = (IGUIContainer*) new_guiobject;
			for ( IGUIObject* it = template_guiobject->FirstChildObject( ); it != _null; it = it->NextObject( ) )
				CreateGUIObject( it, suffix, new_guicontainer, deep );
		}
	}

	return new_guiobject;
}

IGUIObject* GUIResourceManager::CreateGUIObjectFromXMLString( WStringPtr type, WStringPtr xml_string, IGUIContainer* parent_object )
{
	IGUIObject* gui_object = (IGUIObject*) GetInterfaceFactory( )->CreateObject( type );
	if ( gui_object == _null )
		return _null;

	if ( gui_object->ImportFromXMLString( xml_string ) == _false )
		return _null;

	if ( parent_object != _null )
		parent_object->InsertChildObject( gui_object );

	return gui_object;
}

IGUIApplication* GUIResourceManager::CreateGUIApplication( IGUIContainer* parent )
{
	// Create and import GUI application
	GUIApplication* application = new GUIApplication( );

	// Insert into parent container
	if ( parent != _null )
		parent->InsertChildObject( application );

	// Tell outside the application has been loaded ( take care of referenced count for multiple-thread )
	IGUIApplicationNotifierRef notifier = GetGUIModule( )->GetApplicationNotifier( );
	if ( notifier->OnAfterLoad( application ) == _false )
		{ EGE_RELEASE( application ); return _null; }

	return application;
}

IGUIApplication* GUIResourceManager::CreateGUIApplication( ISerializableNode* node, IGUIContainer* parent, _ubool delay_load )
{
	// Create and import GUI application
	GUIApplication* application = new GUIApplication( );

	// Set the delay load flag
	application->GetComponentState( )->DelayLoad( delay_load );

	// Import GUI application
	if ( application->Import( node ) == _false )
		{ EGE_RELEASE( application ); return _null; }

	// Insert into parent container
	if ( parent != _null )
		parent->InsertChildObject( application );

	// Tell outside the application has been loaded ( take care of referenced count for multiple-thread )
	IGUIApplicationNotifierRef notifier = GetGUIModule( )->GetApplicationNotifier( );
	if ( notifier->OnAfterLoad( application ) == _false )
		{ EGE_RELEASE( application ); return _null; }

	return application;
}
