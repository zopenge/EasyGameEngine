#include "EGEPlatform.h"

_ubool Platform::Initialize() {
	if (anyPlatform::Initialize() == _false)
		return _false;

#if (_USE_NEON_ == 1)
	enable_runfast();
#endif

	return _true;
}

_void Platform::Finalize() {
	// Finalize platform
	anyPlatform::Finalize();
}
