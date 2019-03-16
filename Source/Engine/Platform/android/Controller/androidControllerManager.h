//! @file     androidControllerManager.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// androidControllerManager
//----------------------------------------------------------------------------

class androidControllerManager : public TControllerManager< IControllerManager >
{
private:
	typedef TControllerManager< IControllerManager > BaseClass;

private:
	JNIObject	mJNIController;

public:
	androidControllerManager( );
	virtual ~androidControllerManager( );

// IControllerManager Interface
public:
	virtual _ubool	Initialize( IViewBasedApp* application ) override;

	virtual _void	Pause( ) override;
	virtual _void	Resume( ) override;
};

}