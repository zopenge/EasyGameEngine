//! @file     IGUIComponent.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGUIComponent
//----------------------------------------------------------------------------

class IGUIComponent : public ITSerializable< IDynamicResObject >
{
public:
	//!	Get GUI object.
	//!	@param		none.
	//!	@return		The GUI object.
	virtual IGUIObject* GetGUIObject( ) const PURE;

	//!	Make it to sleep or not.
	//!	@param		sleep			True indicates sleep, otherwise keep wake-up.
	//!	@return		none.
	virtual _void SetSleep( _ubool sleep ) PURE;
	//!	Check whether it's sleep or not.
	//!	@param		none.
	//!	@return		True indicates sleep, otherwise keep wake-up.
	virtual _ubool IsSleep( ) const PURE;

	//!	Set the sort index.
	//!	@param		index		The sort index, it will use as key to sort from low to high on components.
	//!	@return		none.
	virtual _void  SetComponentSortIndex( _dword index ) PURE;
	//!	Get the sort index.
	//!	@param		none.
	//!	@return		The sort index.
	virtual _dword GetComponentSortIndex( ) const PURE;

	//!	Get state ID.
	//!	@param		none.
	//!	@return		The state.
	virtual _GUI_OBJECT_STATE GetComponentObjStateID( ) const PURE;
	//!	Set state ID.
	//!	@param		state	The state ID.
	//!	@return		none.
	virtual _void SetComponentObjStateID( _GUI_OBJECT_STATE state ) PURE;

	//!	Get state name.
	//!	@param		none.
	//!	@return		The state.
	virtual WStringPtr GetComponentObjStateName( ) const PURE;

	//!	Import event.
	//!	@param		node		The serializable node.
	//!	@param		event_name	The event name, @see _GUI_EVENT*.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool ImportEvent( ISerializableNode* node, WStringPtr event_name ) PURE;
	//!	Import event.
	//!	@param		xml_string				The XML string.
	//!	@param		event_name				The event name, @see _GUI_EVENT*.
	//!	@param		locate_at_first_child	True indicates locate at first child.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool ImportEventFromXMLString( WStringPtr xml_string, WStringPtr event_name, _ubool locate_at_first_child = _true ) PURE;
	//!	Export event.
	//!	@param		node		The serializable node.
	//!	@param		event_name	The event name, @see _GUI_EVENT*.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool ExportEvent( ISerializableNode* node, WStringPtr event_name ) const PURE;
	//!	Export event to XML string.
	//!	@param		root_name	The root name.
	//!	@param		tag_name	The tag name.
	//!	@param		event_name	The event name, @see _GUI_EVENT*.
	//!	@param		xml_string	The XML string.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool ExportEventToXMLString( WStringPtr root_name, WStringPtr tag_name, WStringPtr event_name, WString& xml_string ) PURE;

	//!	Check whether it's resident component.
	//!	@param		none.
	//!	@return		True indicates it's resident component.
	virtual _ubool IsResident( ) const PURE;
	//!	Check whether it supports keys.
	//!	@param		none.
	//!	@return		True indicates it's resident component.
	virtual _ubool IsSupportKeys( ) const PURE;

	//!	Whether do the tick operation.
	//!	@param		none.
	//!	@return		True indicates do the operation.
	virtual _ubool DoTick( ) const PURE;
	//!	Whether do the render operation.
	//!	@param		none.
	//!	@return		True indicates do the operation.
	virtual _ubool DoRender( ) const PURE;
	//!	Whether do the render operation.
	//!	@param		none.
	//!	@return		True indicates do the operation.
	virtual _ubool DoAfterChildRender() const PURE;
	//!	Whether do the event handle operation.
	//!	@param		none.
	//!	@return		True indicates do the operation.
	virtual _ubool DoHandleEvent( ) const PURE;
	//!	Whether do the check event handle operation.
	//!	@param		none.
	//!	@return		True indicates do the operation.
	virtual _ubool DoIsHandleEvent( ) const PURE;
	//!	Whether do the test region operation.
	//!	@param		none.
	//!	@return		True indicates do the operation.
	virtual _ubool DoTestRegion( ) const PURE;
	//!	Whether do the export operation.
	//!	@param		none.
	//!	@return		True indicates do the operation.
	virtual _ubool DoExport( ) const PURE;

	//! Check whether handle the event or not.
	//!	@param		event_id		The GUI event ID.
	//!	@return		True indicates this event will handle this event( not handle now ).
	virtual _ubool IsHandleEvent( _dword event_id ) const PURE;

	//!	Handle event.
	//!	@param		event		The GUI event info.
	//!	@param		flags		The GUI event flags.
	//!	@return		True indicates this event has been handled.
	virtual _ubool HandleEvent( const EventBase& event, const FlagsObject& flags ) PURE;
	//!	Render.
	//!	@param		viewport		The viewport.
	//!	@param		transform		The transform.
	//!	@param		color			The color.
	//!	@param		clip_rect		The clip rect.
	//!	@param		in_clip_state	True indicates we are in the clip state.
	//!	@return		none.
	virtual _void Render( IObject* viewport, const Matrix3& transform, const Color& color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test ) PURE;
	//!	Render after child.
	//!	@param		viewport		The viewport.
	//!	@param		transform		The transform.
	//!	@param		color			The color.
	//!	@param		clip_rect		The clip rect.
	//!	@param		in_clip_state	True indicates we are in the clip state.
	//!	@return		none.
	virtual _void RenderAfterChild( IObject* viewport, const Matrix3& transform, Color color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test ) PURE;
	//!	Render after all root application render.
	//!	@param		viewport		The viewport.
	//!	@param		transform		The transform.
	//!	@param		color			The color.
	//!	@param		clip_rect		The clip rect.
	//!	@return		none.
	virtual _void RenderAfterRootApplication( IObject* viewport, const Matrix3& transform, const Color& color, const RectF& clip_rect ) PURE;

	//!	Check whether the position is in the region of control.
	//!	@param		position			The position.
	//!	@param		transform			The world transform.
	//!	@param		relative_position	The feedback relative position.
	//!	@return		True indicates the position hits the control with transform.
	virtual _GUI_TESTPOINT_RESULT_TYPE PointInControl( const Vector2& position, const Matrix3& transform, Vector2* relative_position ) PURE;
	//!	Check whether the region hit the region of control.
	//!	@param		region				The region.
	//!	@param		transform			The world transform.
	//!	@return		True indicates the position hits the control with transform.
	virtual _ubool RegionInControl( const RectF& region, const Matrix3& transform ) PURE;
};

}