//! @file     ALAPI.mm
//! @author   LiCode
//! @version  1.1.1.804
//! @date     2011/03/10
//! Copyright ...

#include "EGESound.h"

//----------------------------------------------------------------------------
// AL-Device Implementation
//----------------------------------------------------------------------------

_void NS_ALDeviceSuspend( )
{
    float version = [[[UIDevice currentDevice] systemVersion] floatValue];
    if (version < 7.0)
    {
        AudioSessionSetActive( NO );
    }
	else
	{
		NSError* err = nil;
		[[AVAudioSession sharedInstance] setActive:NO error:&err];
		if ( err != nil )
			NSLog(@"Set audio session NO failed(%@)", err.localizedDescription);
	}
}

_void NS_ALDeviceResume( )
{
    float version = [[[UIDevice currentDevice] systemVersion] floatValue];
    if (version < 7.0)
    {
        _dword category = kAudioSessionCategory_AmbientSound;
        AudioSessionSetProperty( kAudioSessionProperty_AudioCategory, sizeof( category ), &category );
        AudioSessionSetActive( YES );
    }
	else
	{
		NSError* err = nil;
		
		[[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryAmbient error:&err];
		if ( err != nil )
			NSLog(@"Set audio session category failed(%@)", err.localizedDescription);
		
		[[AVAudioSession sharedInstance] setActive:YES error:&err];
		if ( err != nil )
			NSLog(@"Set audio session YES failed(%@)", err.localizedDescription);
	}
}