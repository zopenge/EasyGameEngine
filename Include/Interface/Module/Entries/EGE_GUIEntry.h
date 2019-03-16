//! @file     EGE_GUIEntry.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

//! Get the GUI utils.
DEFINE_IMPORT_FUNC(EGE::IGUIUtils*, GetGUIUtils, ())
//! Get the GUI resource manager.
DEFINE_IMPORT_FUNC(EGE::IGUIResourceManager*, GetGUIResourceManager, ())
//! Get the GUI module.
DEFINE_IMPORT_FUNC(EGE::IGUIModule*, GetGUIModule, ())

//!	Create the GUI module.
DEFINE_IMPORT_FUNC(EGE::_boolean, CreateGUIModule, (EGE::_ubool enable_stretch, const EGE::Vector2& size))