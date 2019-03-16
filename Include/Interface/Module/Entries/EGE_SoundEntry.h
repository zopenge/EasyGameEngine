//! @file     EGE_SoundEntry.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

//! Get the sound resource manager.
DEFINE_IMPORT_FUNC(EGE::ISoundResourceManager*, GetSoundResourceManager, ())
//! Get the sound module.
DEFINE_IMPORT_FUNC(EGE::ISoundModule*, GetSoundModule, ())
//! Get the dynamic sound hardware information.
DEFINE_IMPORT_FUNC(EGE::IDynamicSHI*, GetDynamicSHI, ())

//!	Create the sound module.
DEFINE_IMPORT_FUNC(EGE::_boolean, CreateSoundModule, ())