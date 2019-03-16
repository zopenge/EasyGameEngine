//! @file     EGE_GUI.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

namespace EGE
{

// GUI Interface
REF_OBJECT_DECL(IGUILocationInfo);
REF_OBJECT_DECL(IGUIComponent);
REF_OBJECT_DECL(IGUIComponentEventHooker);
REF_OBJECT_DECL(IGUIComponentPosition);
REF_OBJECT_DECL(IGUIComponentColor);
REF_OBJECT_DECL(IGUIComponentState);
REF_OBJECT_DECL(IGUIComponent3DRender);
REF_OBJECT_DECL(IGUIComponentAnimation);
REF_OBJECT_DECL(IGUIComponentClick);
REF_OBJECT_DECL(IGUIComponentGroup);
REF_OBJECT_DECL(IGUIObject);
REF_OBJECT_DECL(IGUIContainer);
REF_OBJECT_DECL(IGUIApplication);
REF_OBJECT_DECL(IGUIApplicationNotifier);
REF_OBJECT_DECL(IGUIUtils);
REF_OBJECT_DECL(IGUIResourceManager);
REF_OBJECT_DECL(IGUIEventDelegate);
REF_OBJECT_DECL(IGUIProcessor);
REF_OBJECT_DECL(IGUIModule);

typedef Array< IGUIObjectRef, IGUIObject* > IGUIObjectRefArray;

// The global functions declaration
extern "C"
{
//!	When query GUI state enumeration value.
_dword OnQueryGUIStateEnumValue( WStringPtr name, const QwordParameters2& parameters );
//!	When query GUI state enumeration name.
const _charw* OnQueryGUIStateEnumName( _dword value, const QwordParameters2& parameters );
}

}

// Module-GUI Global Files
#include "Interface/Module/GUI/GUIGlobals.h"
#include "Interface/Module/GUI/GUIEvents.h"
using namespace EGE::GUIEvents;

// Module-GUI Interface Files
#include "Interface/Module/GUI/GUIComponent/IGUIComponent.h"
#include "Interface/Module/GUI/GUIComponent/IGUIComponentEventHooker.h"
#include "Interface/Module/GUI/GUIComponent/IGUILocationInfo.h"
#include "Interface/Module/GUI/GUIComponent/IGUIComponentPosition.h"
#include "Interface/Module/GUI/GUIComponent/IGUIComponentColor.h"
#include "Interface/Module/GUI/GUIComponent/IGUIComponentState.h"
#include "Interface/Module/GUI/GUIComponent/IGUIComponent3DRender.h"
#include "Interface/Module/GUI/GUIComponent/IGUIComponentAnimation.h"
#include "Interface/Module/GUI/GUIComponent/IGUIComponentClick.h"
#include "Interface/Module/GUI/GUIComponent/IGUIComponentGroup.h"
#include "Interface/Module/GUI/IGUIObject.h"
#include "Interface/Module/GUI/IGUIContainer.h"
#include "Interface/Module/GUI/IGUIApplication.h"
#include "Interface/Module/GUI/IGUIApplicationNotifier.h"
#include "Interface/Module/GUI/IGUIResourceManager.h"
#include "Interface/Module/GUI/IGUIProcessor.h"
#include "Interface/Module/GUI/IGUIModule.h"
#include "Interface/Module/Entries/EGE_GUIEntry.h"

// Module-GUI Template Files
#include "Interface/Module/GUI/Template/TGUIComponent.h"
#include "Interface/Module/GUI/Template/TGUIObject.h"
#include "Interface/Module/GUI/Template/TGUIControl.h"
#include "Interface/Module/GUI/Template/TGUIContainer.h"