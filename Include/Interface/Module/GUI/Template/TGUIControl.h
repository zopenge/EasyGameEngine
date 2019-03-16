//! @file     TGUIControl.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TGUIControl
//----------------------------------------------------------------------------

template< typename Type >
class TGUIControl : public TGUIObject< Type >
{
protected:
	typedef TGUIObject< Type > GUIObjectBaseClass;

protected:
	TGUIControl( );
	virtual ~TGUIControl( );

// IObjectTree Interface
public:
	virtual _void 	RemoveChildObject( IGUIObject* object ) override;
	virtual _void 	InsertChildObject( IGUIObject* object ) override;
	virtual _void	RenderAfterChild(IObject* viewport, const Matrix3& transform, Color color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test) override;

// IGUIObject Interface
public:
	virtual _ubool 	IsControl( ) const override;
	virtual _ubool 	IsContainer( ) const override;
};

//----------------------------------------------------------------------------
// TGUIControl Implementation
//----------------------------------------------------------------------------

template< typename Type >
TGUIControl< Type >::TGUIControl( )
{
}

template< typename Type >
TGUIControl< Type >::~TGUIControl( )
{
}

template< typename Type >
_void TGUIControl< Type >::RemoveChildObject( IGUIObject* object )
{
	EGE_ASSERT2( _false, L"We do not allow the GUI control to remove any child object, please use GUI container" );
}

template< typename Type >
_void TGUIControl< Type >::InsertChildObject( IGUIObject* object )
{
	EGE_ASSERT2( _false, L"We do not allow the GUI control to add any child object, please use GUI container" );
}

template< typename Type >
_void TGUIControl< Type >::RenderAfterChild(IObject* viewport, const Matrix3& transform, Color color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test)
{
	EGE_ASSERT(0);
}

template< typename Type >
_ubool TGUIControl< Type >::IsControl( ) const
{
	return _true;
}

template< typename Type >
_ubool TGUIControl< Type >::IsContainer( ) const
{
	return _false;
}

}