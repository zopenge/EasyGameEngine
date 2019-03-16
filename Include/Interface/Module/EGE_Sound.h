//! @file     EGE_Sound.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

namespace EGE
{

// Sound Interface
REF_OBJECT_DECL(IDynamicSHI);
REF_OBJECT_DECL(ISoundRecorderNotifier);
REF_OBJECT_DECL(ISoundRecorder);
REF_OBJECT_DECL(ISoundRecognizer);
REF_OBJECT_DECL(ISoundSource);
REF_OBJECT_DECL(ISoundSourceManager);
REF_OBJECT_DECL(ISoundModule);

}

// Module-Sound Interface Files
#include "Interface/Module/Sound/SHIResource.h"
#include "Interface/Module/Sound/SoundGlobals.h"
#include "Interface/Module/Sound/ISoundRecorder.h"
#include "Interface/Module/Sound/ISoundRecognizer.h"
#include "Interface/Module/Sound/ISoundSourceCallback.h"
#include "Interface/Module/Sound/ISoundSource.h"
#include "Interface/Module/Sound/ISoundResourceManager.h"
#include "Interface/Module/Sound/ISoundModule.h"
#include "Interface/Module/Entries/EGE_SoundEntry.h"