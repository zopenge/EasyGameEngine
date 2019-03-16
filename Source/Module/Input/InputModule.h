//! @file     InputModule.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// InputModule
//----------------------------------------------------------------------------

class InputModule : public INTERFACE_MODULE_IMPL( IInputModule )
{
private:
	typedef INTERFACE_MODULE_IMPL( IInputModule ) BaseClass;

private:

public:
	InputModule( );
	virtual ~InputModule( );

public:
	//!	Initialize.
	_ubool Initialize( _handle app_handle );
	//!	Finalize.
	_void Finalize( );

// IObject Interface
public:
	virtual _void	Tick( _time_t tick, _dword elapse ) override;

// IModule Interface
public:
	virtual _void	HandleMessage( MessageBase& message ) override;
};

}