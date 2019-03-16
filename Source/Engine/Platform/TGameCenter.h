//! @file     TGameCenter.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TGameCenter
//----------------------------------------------------------------------------

template< typename Type >
class TGameCenter : public TObject< Type >
{
protected:

protected:
	TGameCenter( );
	virtual ~TGameCenter( );

// IGameCenter Interface
public:
};

//----------------------------------------------------------------------------
// TGameCenter Implementation
//----------------------------------------------------------------------------

template< typename Type >
TGameCenter< Type >::TGameCenter( )
{

}

template< typename Type >
TGameCenter< Type >::~TGameCenter( )
{

}

}