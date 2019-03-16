//! @file     winGameCenter.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// winGameCenter
//----------------------------------------------------------------------------

class winGameCenter : public TGameCenter< IGameCenter >
{
private:

public:
	winGameCenter( );
	virtual ~winGameCenter( );

// IGameCenter Interface
public:
	virtual _ubool IsAvailable( ) const override;
};

//----------------------------------------------------------------------------
// winGameCenter Implementation
//----------------------------------------------------------------------------

}