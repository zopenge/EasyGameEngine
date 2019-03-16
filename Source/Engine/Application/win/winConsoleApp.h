//! @file     winConsoleApp.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// winConsoleApp
//----------------------------------------------------------------------------

class winConsoleApp : public INTERFACE_APPLICATION_IMPL( IConsoleApp )
{
private:
	typedef INTERFACE_APPLICATION_IMPL( IConsoleApp ) BaseClass;

public:
	winConsoleApp( );
	virtual ~winConsoleApp( );

// IApplication Interface
public:
	virtual _APPLICATION_TYPE	GetApplicationType( ) const override;
	virtual _handle				GetApplicationHandle( ) const override;
	virtual _handle				GetApplicationLayerHandle( ) const override;

	virtual _void 				Show( ) override;
	virtual _void 				Hide( ) override;

	virtual _int				Run( IAppDelegate* app_delegate, ICommandLineParser* cmd_parser ) override;
};

}