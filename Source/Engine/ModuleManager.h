//! @file     ModuleManager.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ModuleManager
//----------------------------------------------------------------------------

class ModuleManager : public INTERFACE_OBSERVABLE_IMPL( TPowerable< IModuleManager > )
{
private:
	typedef INTERFACE_OBSERVABLE_IMPL( TPowerable< IModuleManager > ) BaseClass;

private:
	//!	The module info
	struct ModuleInfo
	{
		_dword		mPriority;
		IModule*	mModule;

		operator _dword( ) const
			{ return mPriority; }

		ModuleInfo( _dword priority = 0, IModule* module = _null )
			: mPriority( priority ), mModule( module ) { }
	};
	typedef Array< ModuleInfo > ModuleArray;

private:
	typedef Queue< EventBase* > MessageObjectQueue;

private:
	//!	The thread lock
	Lock				mLocker;

	//!	True indicates it's releasing now
	_ubool				mIsReleasing;
	//!	True indicates it's launching now
	_ubool				mIsLaunchingApp;
	//!	True indicates loaded completed now
	_ubool				mHasLoadedApp;

	//!	The registered modules
	ModuleArray			mModules;
	
	//!	The delay message queue
	MessageObjectQueue	mDelayMessageObjects;

private:
	//!	Delete all delay messages.
	_void DeleteAllDelayMessages( );
	//!	Try to dequeue delay message object from queue.
	_ubool TryeDequeueDelayMessageObject( EventBase*& msg );
	//!	Enqueue delay message object into queue.
	_void EnqueueMessageObject( EventBase* msg );

	//! Process event for self.
	_void ProcessEventForSelf( EventBase& event );
	//!	Process event for modules.
	_void ProcessEventForModules( EventBase& event );
	//!	Process event for notifiers.
	_void ProcessEventForNotifiers( EventBase& event );

public:
	ModuleManager( );
	virtual ~ModuleManager( );

// IObject Interface
public:
	virtual _void			Tick( _dword limited_elapse, _dword elapse ) override;
	virtual _void			FrameTick( _dword frame ) override;

	virtual _dword 			Release( ) override;

// IPowerable Interface
public:
	virtual _ubool			PowerOn( ) override;
	virtual _void			PowerOff( ) override;

// IModuleManager Interface
public:
	virtual _ubool			IsLaunchingApp( ) const override;
	virtual _ubool			HasLoadedApp( ) const override;

	virtual _ubool			ResetResources( ) override;
	virtual _void			UnloadResources( ) override;

	virtual _void			RegisterAppDelegate( IAppDelegate* app_delegate ) override;
	virtual IAppDelegate*	GetRegisteredAppDelegate( ) override;

	virtual _void			RegisterModule( IModule* module, _dword priority ) override;
	virtual _void			UnregisterModule( IModule* module ) override;

	virtual _void			OutputString( _LOG type, AStringPtr string, AStringPtr file_name = "", _dword line_number = 0 ) override;
	virtual _void			OutputString( _LOG type, WStringPtr string, WStringPtr file_name = L"", _dword line_number = 0 ) override;
	virtual _void			OutputString( _LOG type, AStringPtr module_name, AStringPtr string, AStringPtr file_name = "", _dword line_number = 0 ) override;
	virtual _void			OutputString( _LOG type, WStringPtr module_name, WStringPtr string, WStringPtr file_name = L"", _dword line_number = 0 ) override;

	virtual _void			AddDelayEvent( const EventBase& event ) override;
	virtual _void			ProcessDelayEvents( ) override;
	virtual _void			ProcessEvent( EventBase& event ) override;
};

}