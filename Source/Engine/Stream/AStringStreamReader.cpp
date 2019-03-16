//! @file     AStringStreamReader.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// AStringStreamReader Implementation
//----------------------------------------------------------------------------

AStringStreamReader::AStringStreamReader( AStringPtr string ) : BaseClass( string )
{
}

AStringStreamReader::~AStringStreamReader( )
{
}

IObject* AStringStreamReader::CloneTo( _ubool standalone ) const
{
	return new AStringStreamReader( mString );
}