//! @file     chromeModule.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// chromeModule
//----------------------------------------------------------------------------

class chromeModule : public INTERFACE_MODULE_IMPL( IModule )
{
private:
	typedef INTERFACE_MODULE_IMPL( IModule ) BaseClass;

private:

public:
	chromeModule( );
	virtual ~chromeModule( );

// IModule Interface
public:
	virtual _void HandleEvent( EventBase& event ) override;
};

}