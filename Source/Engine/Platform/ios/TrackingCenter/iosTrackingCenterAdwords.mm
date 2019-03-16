#include "EGEEngine.h"

iosTrackingCenterAdwords::iosTrackingCenterAdwords( UStringPtr conversion_id, UStringPtr label )
	: mConversionId( conversion_id )
	, mLabel( label )
{
}

iosTrackingCenterAdwords::~iosTrackingCenterAdwords( )
{
}

_void iosTrackingCenterAdwords::Start( )
{
//	[GoogleConversionPing pingWithConversionId:[NSString stringWithUTF8String:mConversionId.Str( )] label:[NSString stringWithUTF8String:mLabel.Str( )] value:@"1" isRepeatable:NO];
}