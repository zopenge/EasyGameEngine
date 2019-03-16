//! @file     TMediaFile.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{
	
//----------------------------------------------------------------------------
// TMediaFile
//----------------------------------------------------------------------------

template< typename Type >
class TMediaFile : public INTERFACE_BASEFILE_IMPL( Type )
{
protected:

protected:
	TMediaFile( );
	virtual ~TMediaFile( );

// IMediaFile Interface
public:
};

//----------------------------------------------------------------------------
// TMediaFile Implementation
//----------------------------------------------------------------------------

template< typename Type >
TMediaFile< Type >::TMediaFile( )
{
}

template< typename Type >
TMediaFile< Type >::~TMediaFile( )
{

}

}