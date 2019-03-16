//! @file     GraphicBackSurface.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicBackSurface
//----------------------------------------------------------------------------

class GraphicBackSurface : public TObject< IGraphicBackSurface >
{
private:
	//!	True indicates we are rendering in back surface
	_ubool					mIsRendering;
	//!	The original scene client size
	PointU					mOriginalClientSize;
	//!	The back surface rendering size
	PointU					mRenderingSize;
	//!	The scale of render size
	_float					mRenderingScale;

	//!	The effect
	IGraphicEffectRef		mEffect;

	//!	The clear buffers operation info
	GraphicClearBuffersInfo	mClearBuffersInfo;

	//!	The back surface
	IGraphicCanvasRef		mCanvas;

private:
	//!	Finish rendering.
	_void FinishRendering( );

public:
	GraphicBackSurface( );
	virtual ~GraphicBackSurface( );

public:
	//!	Initialize.
	_ubool Initialize( _dword canvas_width, _dword canvas_height );

// IGraphicBackSurface Interface
public:
	virtual _ubool			IsRendering( ) const override;

	virtual IGraphicCanvas* GetCanvas( ) override;

	virtual PointU			GetSize( ) const override;

	virtual _void			SetPrevClientSize( const PointU& size ) override;

	virtual _void			SetClearBuffersInfo( const GraphicClearBuffersInfo& info ) override;

	virtual _void			SetRenderScale( _float scale ) override;
	virtual _float			GetRenderScale( ) const override;

	virtual _void			BeginRender( IGraphicScene* scene ) override;
	virtual _void			EndRender( ) override;

	virtual _void			RenderToScene( IGraphicScene* scene ) override;
	virtual _void			RenderToScene( IGraphicScene* scene, IGraphicEffect* effect ) override;

	virtual _void			PresentRenderBuffers( ) override;
};

//----------------------------------------------------------------------------
// GraphicBackSurface Implementation
//----------------------------------------------------------------------------

}