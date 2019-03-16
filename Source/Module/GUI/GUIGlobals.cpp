//! @file     GUIGlobals.cpp
//! @author   
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGUI.h"

//----------------------------------------------------------------------------
// GUI-Globals Implementation
//----------------------------------------------------------------------------

GUIAniKeyFrameInfo::GUIAniKeyFrameInfo( IGUIObject* gui_object )
{
	mColor = gui_object->GetComponentColor( )->GetColor( );
	mTransform.mPosition = gui_object->GetComponentPosition( )->GetOffset( );
	mTransform.mScale = gui_object->GetComponentPosition( )->GetScale( );
	mTransform.mRadian = gui_object->GetComponentPosition( )->GetRadian( );
	mAnimationMask.CombineFlags( _GUI_ANIMATION_ALL );
}