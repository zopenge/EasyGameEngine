//! @file     WStringStreamReader.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// WStringStreamReader Implementation
//----------------------------------------------------------------------------

WStringStreamReader::WStringStreamReader( WStringPtr string ) : BaseClass( string )
{
}

WStringStreamReader::~WStringStreamReader( )
{
}

IObject* WStringStreamReader::CloneTo( _ubool standalone ) const
{
	return new WStringStreamReader( mString );
}