//! @file     GraphicFilter.h
//! @author   LiCode
//! @version  1.0
//! @date     2015.6
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicFilter
//----------------------------------------------------------------------------

class GraphicFilter : public TObject< IGraphicFilter >
{
public:
	GraphicFilter( );
	virtual ~GraphicFilter( );

// IGraphicFilter Interface
public:
	virtual _void ProcessBlurEffect( IGraphicCanvas* canvas, const PointF& step_size, IGraphicSurface* surface ) override;
};

}