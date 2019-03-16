//! @file     NetworkCURL.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NetworkCURL
//----------------------------------------------------------------------------

class NetworkCURL
{
public:
	NetworkCURL( );
	~NetworkCURL( );

public:
	//!	Initialize.
	static _ubool Initialize( );
	//!	Finalize.
	static _void Finalize( );
};

//----------------------------------------------------------------------------
// NetworkCURL Implementation
//----------------------------------------------------------------------------

}