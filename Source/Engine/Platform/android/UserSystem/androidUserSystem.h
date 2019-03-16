//! @file     androidUserSystem.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// androidUserSystem
//----------------------------------------------------------------------------

class androidUserSystem : public TUserSystem< IUserSystem >
{
private:
	typedef TUserSystem< IUserSystem > BaseClass;

private:
	//!	The java user system interface object
	JNIObject mUserSystemObject;

public:
	androidUserSystem( );
	virtual ~androidUserSystem( );

// IUserSystem Interface
public:
	virtual _ubool	Initialize( WStringPtr app_id, WStringPtr channel ) override;
};

//----------------------------------------------------------------------------
// androidUserSystem Implementation
//----------------------------------------------------------------------------

}