#include "EGEEngine.h"

struct iosAccelerometer::AccDelegateHandle
{
public:
	NSAccelerometerDelegate*    mAccDelegate;

public:
	AccDelegateHandle( )
	{
		mAccDelegate = nil;
	}
	~AccDelegateHandle( )
	{
		mAccDelegate = nil;
	}
};

iosAccelerometer::iosAccelerometer( )
	: mAccDelegateHandle( _null )
{
	mAccDelegateHandle					= new AccDelegateHandle;
	mAccDelegateHandle->mAccDelegate	= [NSAccelerometerDelegate alloc];
}

iosAccelerometer::~iosAccelerometer( )
{
	EGE_DELETE( mAccDelegateHandle );
}

_void iosAccelerometer::Initialize( IViewBasedApp* viewbased_app, _float update_interval )
{
	[mAccDelegateHandle->mAccDelegate SetViewbasedApp:viewbased_app];

	[[UIAccelerometer sharedAccelerometer] setUpdateInterval:(update_interval)];
}

_void iosAccelerometer::Enable( )
{
	[[UIAccelerometer sharedAccelerometer] setDelegate:mAccDelegateHandle->mAccDelegate];
}

_void iosAccelerometer::Disable( )
{
	[[UIAccelerometer sharedAccelerometer] setDelegate:nil];
}