//! @file     ScriptModule.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ScriptModule
//----------------------------------------------------------------------------

class ScriptModule : public INTERFACE_MODULE_IMPL( IScriptModule )
{
private:
	typedef INTERFACE_MODULE_IMPL( IScriptModule ) BaseClass;

private:
	//!	The internal script module
	_scriptSystemPassRef	mInternalScriptSystem;

	//!	The resource manager
	ScriptResourceManager	mResourceManager;

private:
	//!	Initialize internal script module.
	_ubool InitInternalScriptModule( _SCRIPT type );

public:
	ScriptModule( );
	virtual ~ScriptModule( );

public:
	//!	Initialize.
	_ubool Initialize( _SCRIPT type );
	//!	Finalize.
	_void Finalize( );

// IObject Interface
public:
	virtual _void			Tick( _dword limited_elapse, _dword elapse ) override;

// IModule Interface
public:
	virtual _void			HandleEvent( EventBase& event ) override;

// IScriptModule Interface
public:
	virtual _dword			GetTotalMemSize( ) const override;

	virtual _ubool			SetRemoteDebugger( const Address& address ) override;
	virtual const Address&	GetRemoteDebugger( ) const override;
};

}