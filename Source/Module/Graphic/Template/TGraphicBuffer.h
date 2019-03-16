//! @file     TGraphicBuffer.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TGraphicBuffer
//----------------------------------------------------------------------------

template< typename Type >
class TGraphicBuffer : public INTERFACE_OBJECT_IMPL( Type )
{
public:
	TGraphicBuffer( );
	virtual ~TGraphicBuffer( );

// IGraphicBuffer Interface
public:
};

//----------------------------------------------------------------------------
// TGraphicBuffer Implementation
//----------------------------------------------------------------------------

template< typename Type >
TGraphicBuffer< Type >::TGraphicBuffer( )
{
}

template< typename Type >
TGraphicBuffer< Type >::~TGraphicBuffer( )
{
}

}