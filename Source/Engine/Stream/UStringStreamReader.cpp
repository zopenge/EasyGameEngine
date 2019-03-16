//! @file     UStringStreamReader.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// UStringStreamReader Implementation
//----------------------------------------------------------------------------

UStringStreamReader::UStringStreamReader( UStringPtr string ) : BaseClass( string )
{
}

UStringStreamReader::~UStringStreamReader( )
{
}

IObject* UStringStreamReader::CloneTo( _ubool standalone ) const
{
	return new UStringStreamReader( mString );
}