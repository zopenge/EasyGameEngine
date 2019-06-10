//! @file     ModuleManager.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// ModuleManager Implementation
//----------------------------------------------------------------------------

ModuleManager::ModuleManager( )
{
	mIsReleasing	= _false;
	mIsLaunchingApp	= _false;
	mHasLoadedApp	= _false;
}

ModuleManager::~ModuleManager( )
{
	// Prevent the dead loop for releasing modules
	mIsReleasing = _true;

	// Clear modules
	for ( _int i = mModules.Number( ) - 1; i >= 0; i -- )
		EGE_RELEASE( mModules[i].mModule );

	// Clear observers
	mObservers.Clear( _true );

	// Delete all messages
	DeleteAllDelayMessages( );
}

_void ModuleManager::DeleteAllDelayMessages( )
{
	for ( _dword i = 0; i < mDelayMessageObjects.Number( ); i ++ )
	{
		EGE_DELETE( mDelayMessageObjects[i] );
	}
}

_ubool ModuleManager::TryeDequeueDelayMessageObject( EventBase*& msg )
{
	LockOwner lock_owner( mLocker );

	if ( mDelayMessageObjects.Dequeue( msg ) == _false )
		return _false;

	return _true;
}

_void ModuleManager::EnqueueMessageObject( EventBase* msg )
{
	LockOwner lock_owner( mLocker );

	mDelayMessageObjects.Enqueue( msg );
}

_void ModuleManager::ProcessEventForSelf( EventBase& event )
{
	switch ( event.mEventID )
	{
		case _EVENT_BEFORE_LAUNCH_APP:
		{
			EventBeforeLaunchApp& ev = (EventBeforeLaunchApp&)event;

			mIsLaunchingApp = _true;
		}
		break;

		case _EVENT_AFTER_LAUNCH_APP:
		{
			EventAfterLaunchApp& ev = (EventAfterLaunchApp&)event;

			mIsLaunchingApp = _false;

			// Show application when finished launching
			if ( GetMainViewBasedApp( ) != _null )
				GetMainViewBasedApp( )->Show( );
		}
		break;

		case _EVENT_AFTER_LOAD_APP:
		{
			EventBeforeLoadApp& ev = (EventBeforeLoadApp&)event;

			mHasLoadedApp = _true;
		}
		break;

		default:
			break;
	}
}

_void ModuleManager::ProcessEventForModules( EventBase& event )
{
	for ( _dword i = 0; i < mModules.Number( ); i ++ )
	{
		IModule* module = mModules[i].mModule;
		if ( module == _null )
			continue; // If we are in the releasing procession, this member could be null

		module->HandleEvent( event );
	}
}

_void ModuleManager::ProcessEventForNotifiers( EventBase& event )
{
	// Notify observers
	NotifyObservers( this, event );

	// Notify delegate
	if ( gAppDelegate != _null && mHasLoadedApp )
		gAppDelegate->OnHandleEvent( event );
}

_void ModuleManager::Tick( _dword limited_elapse, _dword elapse )
{
	// Cleanup GC
	GetGarbageCollector( )->Tick( limited_elapse, elapse );

	// Update modules
	for ( _dword i = 0; i < mModules.Number( ); i ++ )
		mModules[i].mModule->Tick( limited_elapse, elapse );
}

_void ModuleManager::FrameTick( _dword frame )
{
	for ( _dword i = 0; i < mModules.Number( ); i ++ )
		mModules[i].mModule->FrameTick( frame );
}

_dword ModuleManager::Release( )
{
	// We won't let the GC to manage it
	if ( INTERLOCKED_DEC( mRefCount ) == 0 )
	{
		delete this;
		return 0;
	}
	else
	{
		return mRefCount;
	}
}

_ubool ModuleManager::PowerOn( )
{
	if ( BaseClass::PowerOn( ) == _false )
		return _false;

	// Power on all modules
	for ( _dword i = 0; i < mModules.Number( ); i ++ )
	{
		if ( mModules[i].mModule->PowerOn( ) == _false )
			return _false;
	}

	return _true;
}

_void ModuleManager::PowerOff( )
{
	BaseClass::PowerOff( );

	// Power off all modules
	for ( _dword i = 0; i < mModules.Number( ); i ++ )
		mModules[i].mModule->PowerOff( );
}

_ubool ModuleManager::IsLaunchingApp( ) const
{
	return mIsLaunchingApp;
}

_ubool ModuleManager::HasLoadedApp( ) const
{
	return mHasLoadedApp;
}

_ubool ModuleManager::ResetResources( )
{
	EventBeginResetResources begin_msg;
	ProcessEvent( begin_msg );

	_ubool ret = _true;
	for ( _dword i = 0; i < mModules.Number( ); i ++ )
		ret &= mModules[i].mModule->ResetResources( );

	EventEndResetResources end_msg;
	ProcessEvent( end_msg );

	return ret;
}

_void ModuleManager::UnloadResources( )
{
	EventBeginUnloadResources begin_msg;
	ProcessEvent( begin_msg );

	for ( _dword i = 0; i < mModules.Number( ); i ++ )
		mModules[i].mModule->UnloadResources( );

	EventEndUnloadResources end_msg;
	ProcessEvent( end_msg );
}

_void ModuleManager::RegisterAppDelegate( IAppDelegate* app_delegate )
{
	// Unregister application delegate
	UnregisterObserver( gAppDelegate );
	EGE_RELEASE( gAppDelegate );

	// Update and register application delegate
	gAppDelegate = app_delegate;
	if ( gAppDelegate != _null )
	{
		gAppDelegate->AddRef( );
		RegisterObserver( gAppDelegate );
	}
}

IAppDelegate* ModuleManager::GetRegisteredAppDelegate( )
{
	return gAppDelegate;
}

_void ModuleManager::RegisterModule( IModule* module, _dword priority )
{
	if ( module == _null )
		return;

	// Clone the module
	module->AddRef( );

	// Insert it into array
	mModules.InsertAscending( ModuleInfo( priority, module ) );

	// Register this module to observers
	for ( _dword i = 0; i < mObservers.Number( ); i ++ )
		module->RegisterObserver( mObservers[i] );
}

_void ModuleManager::UnregisterModule( IModule* module )
{
	if ( module == _null )
		return;

	// Unregister this module from observers
	for ( _dword i = 0; i < mObservers.Number( ); i ++ )
		module->UnregisterObserver( mObservers[i] );

	// If it's self releasing then skip to release it
	if ( mIsReleasing == _false )
	{
		// Remove it from array
		for ( _dword i = 0; i < mModules.Number( ); i ++ )
		{
			if ( mModules[i].mModule == module )
			{
				mModules.RemoveByIndex( i );
				break;
			}
		}

		// If the module's referenced counter is 1 then indicates it come from destructor, so skip to call Release( ), otherwise will be dead loop
		if ( module->GetRefCount( ) > 1 )
			module->Release( );
	}
}

_void ModuleManager::OutputString( _LOG type, AStringPtr string, AStringPtr file_name, _dword line_number )
{
	return OutputString( type, "", string, file_name, line_number );
}

_void ModuleManager::OutputString( _LOG type, WStringPtr string, WStringPtr file_name, _dword line_number )
{
	return OutputString( type, L"", string, file_name, line_number );
}

_void ModuleManager::OutputString( _LOG type, AStringPtr module_name, AStringPtr string, AStringPtr file_name, _dword line_number )
{
	_charw module_name_unicode[128];
	Platform::AnsiToUtf16( module_name_unicode, 128, module_name.Str( ) );

	WString string_unicode;
	string_unicode.FromString( string );

	WString filename_unicode;
	filename_unicode.FromString( file_name );

	OutputString( type, module_name_unicode, string_unicode, filename_unicode, line_number );
}

_void ModuleManager::OutputString( _LOG type, WStringPtr module_name, WStringPtr string, WStringPtr file_name, _dword line_number )
{
	if ( string.IsEmpty( ) )
		return;

	// Notify the observers when we are outputting string
	EventOutputString event;
	event.mType			= type;
	event.mCategory		= module_name; // Use the module name as LOG category
	event.mString		= string;
	event.mFileName		= file_name;
	event.mLineNumber	= line_number;

	NotifyObservers( this, event );
}

_void ModuleManager::AddDelayEvent( const EventBase& event )
{
	// Clone message
	EventBase* ev = event.CloneTo( );
	EGE_ASSERT( ev != _null );

	// Append into queue
	EnqueueMessageObject( ev );
}

_void ModuleManager::ProcessDelayEvents( )
{
	EventBase* event = _null;
	while ( TryeDequeueDelayMessageObject( event ) )
	{
		ProcessEvent( *event );
		EGE_DELETE( event );
	}
}

_void ModuleManager::ProcessEvent( EventBase& event )
{
	// If it's self releasing then skip to handle message
	if ( mIsReleasing )
		return;

	// Process event for self
	ProcessEventForSelf( event );

	// Process event for notifiers
	ProcessEventForNotifiers( event );

	// Process event for registered modules
	ProcessEventForModules( event );
}