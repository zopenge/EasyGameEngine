#include "EGEEngine.h"

iosTrackingCenterTapjoy::iosTrackingCenterTapjoy( UStringPtr app_id, UStringPtr app_secret_key )
	: mAppID( app_id )
	, mAppSecretKey( app_secret_key )
{
}

iosTrackingCenterTapjoy::~iosTrackingCenterTapjoy( )
{
}

_void iosTrackingCenterTapjoy::Start( )
{
//	[Tapjoy requestTapjoyConnect:[NSString stringWithUTF8String:mAppID.Str( )] secretKey:[NSString stringWithUTF8String:mAppSecretKey.Str( )] options:@{ TJC_OPTION_ENABLE_LOGGING : @(YES) } ];
}
