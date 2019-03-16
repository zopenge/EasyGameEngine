//! @file     GraphicSharedViewport.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicSharedViewport Implementation
//----------------------------------------------------------------------------

GraphicSharedViewport::GraphicSharedViewport( IGraphicViewport* viewport )
{
	mViewport = viewport;
}

GraphicSharedViewport::~GraphicSharedViewport( )
{
}

_void GraphicSharedViewport::BindViewport( )
{
	mViewport->Bind( );
}

_void GraphicSharedViewport::BindViewport( ) const
{
	// Do nothing at all, just want to use the macro code
}

_void GraphicSharedViewport::Present( )
{
	// Flush main viewport
	GetGraphicViewport( )->FlushBuffers( );

	// Present
	Bind( );

	mViewport->Present( );
}