//! @file     iosGameCenter.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// iosGameCenter
//----------------------------------------------------------------------------

class iosGameCenter : public TGameCenter< IGameCenter >
{
private:

public:
	iosGameCenter( );
	virtual ~iosGameCenter( );

// IGameCenter Interface
public:
	virtual _ubool IsAvailable( ) const override;
};

//----------------------------------------------------------------------------
// iosGameCenter Implementation
//----------------------------------------------------------------------------

}