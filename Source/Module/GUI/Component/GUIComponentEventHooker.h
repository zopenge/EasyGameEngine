//! @file     GUIComponentEventHooker.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GUIComponentEventHooker
//----------------------------------------------------------------------------

class GUIComponentEventHooker : public TGUIComponent< IGUIComponentEventHooker >
{
public:
	RTTI_CLASS_WITH_ARGUMENTS_DECL( GUIComponentEventHooker, IGUIComponentEventHooker, IGUIObject* )

public:
	_GUICOMPONENT_ENABLE_HANDLE_EVENT( )

private:
	typedef TGUIComponent< IGUIComponentEventHooker > BaseClass;

private:
	//!	The internal event hooker info
	template< typename EventType >
	struct GUIEventInternalHookerInfo : public GUIEventHookerInfo
	{
		EventType	mEvent;
	};

private:
	//!	Hooker callback function ( use GUI event ID as key )
	typedef Map< GUIEventHookerInfo, _dword > GUIEventHookerMap;

	//!	The internal hooker info
	typedef GUIEventInternalHookerInfo< GUIEventUpdate >		GUIEventUpdateHookerInfo;
	typedef GUIEventInternalHookerInfo< GUIEventRenderBegin >	GUIEventRenderBeginHookerInfo;
	typedef GUIEventInternalHookerInfo< GUIEventRenderEnd >		GUIEventRenderEndHookerInfo;
	typedef GUIEventInternalHookerInfo< GUIEventAfterRender >	GUIEventAfterRenderHookerInfo;

private:
	//!	The internal event to speed up
	GUIEventUpdateHookerInfo*		mGUIEventUpdate;
	GUIEventRenderBeginHookerInfo*	mGUIEventRenderBegin;
	GUIEventRenderEndHookerInfo*	mGUIEventRenderEnd;
	GUIEventAfterRenderHookerInfo*	mGUIEventAfterRender;

	//!	The hooker callback functions map
	GUIEventHookerMap				mGUIEventHookerMap;

private:
	//!	Register internal event.
	template< typename EventType >
	_void RegisterInternalEvent( EventType*& event_info, _dword event_id, const GUIEventHooker& hooker, const QwordParameters2& parameters );

public:
	GUIComponentEventHooker( IGUIObject* gui_object );
	virtual ~GUIComponentEventHooker( );

// IObject Interface
public:
	virtual IObject*					CloneTo( _void* arguments ) const override;

// ISerializable Interface
public:
	virtual _ubool						Import( ISerializableNode* node ) override;
	virtual _ubool						Export( ISerializableNode* node ) const override;

// IGUIComponent Interface
public:
	virtual _ubool						IsResident( ) const override;

	virtual _ubool						HandleEvent( const EventBase& event, const FlagsObject& flags ) override;

	virtual _ubool						IsHandleEvent( _dword event_id ) const override;

// IGUIComponentEventHooker Interface
public:
	virtual _void						ClearAllHookerFunc( _ubool deep ) override;

	virtual _void						RegisterHookerFunc( _dword event_id, const GUIEventHooker& hooker, const QwordParameters2& parameters ) override;
	virtual _void						UnregisterHookerFunc( _dword event_id ) override;

	virtual _ubool						InvokeStateChangedFunc( _GUI_OBJECT_STATE prev_state ) override;

	virtual _ubool						InvokeTickFunc( _dword elapse ) override;

	virtual _ubool						InvokeBeginRenderFunc( const Matrix3& transform, const Color& color, const RectF& clip_rect ) override;
	virtual _ubool						InvokeEndRenderFunc( const Matrix3& transform, const Color& color ) override;
	virtual _ubool						InvokeAfterRenderFunc( const Matrix3& transform, const Color& color ) override;

	virtual const GUIEventHookerInfo*	GetHookerFunc( _dword event_id ) const override;
};

//----------------------------------------------------------------------------
// GUIComponentEventHooker Implementation
//----------------------------------------------------------------------------

}