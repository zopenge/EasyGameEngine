//! @file     GUIApplication.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GUIApplication
//----------------------------------------------------------------------------

class GUIApplication : public TGUIContainer< IGUIApplication >
{
public:
	RTTI_CLASS_DECL( GUIApplication, IGUIApplication )

private:
	typedef TGUIContainer< IGUIApplication > BaseClass;

public:
	GUIApplication( );
	virtual ~GUIApplication( );

// IObject Interface
public:
	virtual _void	Tick( _time_t tick, _dword elapse ) override;

// IGUIComponent Interface
public:
	virtual _GUI_TESTPOINT_RESULT_TYPE	PointInControl( const Vector2& position, const Matrix3& transform, Vector2* relative_position ) override;
	virtual _ubool	RegionInControl( const RectF& region, const Matrix3& transform ) override;

	virtual _void	Render( IObject* viewport, const Matrix3& transform, const Color& color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test ) override;

// IGUIObject Interface
public:
	virtual _ubool	IsApplication( ) const override;

	virtual _ubool	DoTick( ) const override;

// IGUIApplication Interface
public:
	virtual _ubool	SetControlModal( WStringPtr name ) override;

	virtual _void	ShowControl( WStringPtr name, _ubool show ) override;
	virtual _void	ShowControlExclusively( WStringPtr name, _ubool skip_model = _true ) override;
	virtual _void	HideAllChildControls( _ubool skip_model = _true ) override;

	virtual _ubool	MoveControl( WStringPtr name, WStringPtr parent_name ) override;
	virtual _ubool	MoveControlToTail( WStringPtr name ) override;
};

//----------------------------------------------------------------------------
// GUIApplication Implementation
//----------------------------------------------------------------------------

}