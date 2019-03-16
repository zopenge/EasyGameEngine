//! @file     IGUIComponentEventHooker.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGUIComponentEventHooker
//----------------------------------------------------------------------------

class IGUIComponentEventHooker : public IGUIComponent
{
public:
	CLASS_NAME_DECL( IGUIComponentEventHooker )

public:
	//!	The hooker event info
	struct GUIEventHookerInfo
	{
		GUIEventHooker		mHooker;
		QwordParameters2	mParameters;

		GUIEventHookerInfo( )
		{
			mParameters	= QwordParameters2::cNull;
		}
	};

public:
	//!	Clear all event hooker callback functions.
	//!	@param		none.
	//!	@return		none.
	virtual _void ClearAllHookerFunc( _ubool deep ) PURE;

	//!	Register event hooker callback function.
	//! @param		event_id	The GUI event id.
	//! @param		hooker		The GUI event hooker.
	//! @param		parameters	The user defined parameters.
	//! @return		none.
	virtual _void RegisterHookerFunc( _dword event_id, const GUIEventHooker& hooker, const QwordParameters2& parameters ) PURE;
	//!	Unregister event hooker callback function.
	//! @param		event_id	The GUI event id.
	//! @return		none.
	virtual _void UnregisterHookerFunc( _dword event_id ) PURE;

	//!	When state changed.
	//! @param		prev_state	The previous state.
	//! @return		True indicates the user has handled it.
	virtual _ubool InvokeStateChangedFunc( _GUI_OBJECT_STATE prev_state ) PURE;

	//!	When update.
	//! @param		elapse		The elapsed time in milliseconds.
	//! @return		True indicates the user has handled it.
	virtual _ubool InvokeTickFunc( _dword elapse ) PURE;

	//!	When begin to render.
	//!	@param		transform	The GUI object world transform.
	//! @return		True indicates the user has handled it.
	virtual _ubool InvokeBeginRenderFunc( const Matrix3& transform, const Color& color, const RectF& clip_rect ) PURE;
	//!	When end to render.
	//!	@param		transform	The GUI object world transform.
	//! @return		True indicates the user has handled it.
	virtual _ubool InvokeEndRenderFunc( const Matrix3& transform, const Color& color ) PURE;

	virtual _ubool InvokeAfterRenderFunc( const Matrix3& transform, const Color& color ) PURE;

	//! Get event hooker callback function
	//! @param		event_id	The GUI event id;
	//! @return		the function
	virtual const GUIEventHookerInfo* GetHookerFunc( _dword event_id ) const PURE;

};

}