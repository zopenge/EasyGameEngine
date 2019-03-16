//! @file     IGUIModule.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGUIModule
//----------------------------------------------------------------------------

class IGUIModule : public IModule
{
public:
	//!	Set GUI processor.
	//!	@param		processor		The processor.
	//!	@return		none.
	virtual _void SetProcessor( IGUIProcessor* processor ) PURE;
	//!	Get GUI processor.
	//!	@param		none.
	//!	@return		The processor.
	virtual IGUIProcessor* GetProcessor( ) PURE;

	//!	Set GUI application notifier.
	//!	@param		notifier		The notifier.
	//!	@return		none.
	virtual _void SetApplicationNotifier( IGUIApplicationNotifier* notifier ) PURE;
	//!	Get GUI application notifier.
	//!	@param		none.
	//!	@return		The application notifier.
	virtual IGUIApplicationNotifier* GetApplicationNotifier( ) PURE;

	//!	Get the root application.
	//!	@param		none.
	//!	@return		The GUI Application interface.
	virtual IGUIApplication* GetRootApplication( ) PURE;
	//!	Get the input record.
	//!	@param		none.
	//!	@return		The input record interface.
	virtual IInputRecorder* GetInputRecorder( ) PURE;
	//!	Release all current input records.
	//!	@param		none.
	//!	@return		none.
	virtual _void ReleaseAllInput( ) PURE;

	//!	Enable/Disable stretch.
	//!	@param		enable		True indicates enable stretch.
	//!	@return		none.
	virtual _void EnableStretch( _ubool enable ) PURE;
	//!	Check whether enable stretch.
	//!	@param		none.
	//!	@return		True indicates enable stretch.
	virtual _ubool IsStretch( ) const PURE;

	virtual _void SetScaleUISize( const Vector2& gui_size, const Vector2& screen_size ) PURE;
	//!	Set GUI client size.
	//!	@remark		The GUI module will keep the ratio of the initial size.
	//!	@param		size		The client size.
	//!	@return		none.
	virtual _void SetSize( const Vector2& size ) PURE;
	//!	Get GUI client size.
	//!	@param		none.
	//!	@return		The client size.
	virtual const Vector2& GetSize( ) const PURE;

	//!	Set the last screen size.
	//!	@param		size		The last screen size.
	//!	@return		none.
	virtual _void SetLastScreenSize( const Vector2& size ) PURE;
	//!	Get the last screen size.
	//!	@param		none.
	//!	@return		The last screen size.
	virtual const Vector2& GetLastScreenSize( ) const PURE;

	//!	Get the region.
	//!	@param		none.
	//!	@return		The region.
	virtual const RectF& GetRegionF( ) const PURE;

	//!	Add pre render GUI object in scene.
	//!	@remark		When render finished, the object will auto remove from delay render queue.
	//!				If you still want to render it by delay way, please call it again.
	//!	@param		object		The GUI object.
	//!	@param		transform	The transform.
	//!	@param		color		The color.
	//!	@param		clip_rect	The clip rect.
	//!	@return		none.
	virtual _void AddPreRenderInSceneGUIObject( IGUIObject* object, const Matrix3& transform, _float zsort ) PURE;
	virtual _void AddPreRenderInSceneGUIObject( IGUIObject* object, const Matrix4& transform, _float zsort ) PURE;
	//!	Add delay render GUI object.
	//!	@remark		When render finished, the object will auto remove from delay render queue.
	//!				If you still want to render it by delay way, please call it again.
	//!	@param		object		The GUI object.
	//!	@param		transform	The transform.
	//!	@param		color		The color.
	//!	@param		clip_rect	The clip rect.
	//!	@return		none.
	virtual _void AddDelayRenderGUIObject( IGUIObject* object, const Matrix3& transform, const Color& color, const RectF& clip_rect ) PURE;
	//!	Add delay render GUI component.
	//!	@remark		When render finished, the object will auto remove from delay render queue.
	//!				If you still want to render it by delay way, please call it again.
	//!	@param		component	The GUI component.
	//!	@param		transform	The transform.
	//!	@param		color		The color.
	//!	@param		clip_rect	The clip rect.
	//!	@return		none.
	virtual _void AddDelayRenderGUIComponent( IGUIComponent* component, const Matrix3& transform, const Color& color, const RectF& clip_rect ) PURE;
	//!	Render.
	//!	@param		viewport	The viewport.
	//!	@return		none.
	virtual _void Render( IObject* viewport ) PURE;
	//!	Render.
	//!	@param		viewport	The viewport.
	//!	@param		pos			The offset.
	//!	@param		scale		The scale.
	//!	@param		color		The color.
	//!	@return		none.
	virtual _void Render( IObject* viewport, const Vector2& pos, const Vector2& scale, const Color& color ) PURE;

	//! Show modal GUI application.
	//! @param		application		The application interface.
	//! @param		receive_message	The modal will receive message.
	//! @return		The application interface, it will be null when show modal failed.
	virtual IGUIApplication* ShowModal( IGUIApplication* application, _ubool receive_message = _true, _ubool create_new_ui = _false ) PURE;
	//! Show modal GUI application.
	//! @param		app_name		The application resource name.
	//! @param		receive_message	The modal will receive message.
	//! @return		The application interface, it will be null when show modal failed.
	virtual IGUIApplication* ShowModal( WStringPtr app_name, _ubool receive_message = _true, _ubool create_new_ui = _false ) PURE;
	//! Show modal GUI application by animation.
	//! @param		app_name		The application resource name.
	//! @param		ani_name		The animation name.
	//! @param		pause_input		True indicates it will pause input.
	//! @param		receive_message	True indicates it will receive message.
	//! @return		The application interface, it will be null when show modal failed.
	virtual IGUIApplication* ShowModalWithAnimation( WStringPtr app_name, WStringPtr ani_name, _ubool pause_input = _true, _ubool receive_message = _true, _ubool create_new_ui = _false ) PURE;
	virtual IGUIApplication* ShowModalWithAnimation( IGUIApplication* application, WStringPtr ani_name, _ubool pause_input = _true, _ubool receive_message = _true, _ubool create_new_ui = _false ) PURE;

	//! Pop the top modal.
	//! @param		none.
	//! @return		none.
	virtual _void HideModal( ) PURE;
	//! Remove the modal.
	//! @param		app_name		The application resource name.
	//! @return		none.
	virtual _void HideModal( WStringPtr app_name ) PURE;
	//! Remove the modal.
	//! @param		app_name		The application resource name.
	//! @return		none.
	virtual _void HideModal( IGUIApplication* gui_app ) PURE;
	//! Remove all modal.
	//! @param		none.
	//! @return		none.
	virtual _void HideAllModal( ) PURE;
	//! Pop the top by animation.
	//! @param		ani_name		The animation name.
	//! @return		none.
	virtual _void HideModalWithAnimation( WStringPtr ani_name ) PURE;
	//! Pop the top by animation.
	//! @param		ani_name		The animation name.
	//! @return		none.
	virtual _void HideModalWithAnimation( WStringPtr app_name, WStringPtr ani_name ) PURE;
	//! Pop the top by animation.
	//! @param		ani_name		The animation name.
	//! @return		none.
	virtual _void HideModalWithAnimation( IGUIApplication* gui_app, WStringPtr ani_name ) PURE;
	//! Get the top modal.
	//! @param		none.
	//! @return		The application interface, it will be null when no any modal GUI.
	virtual IGUIApplication* GetTopModal( ) const PURE;
	//! Pause all modal.
	//! @param		none.
	//! @return		none.
	virtual _void PauseAllModal( ) PURE;
	//! Resume all modal.
	//! @param		none.
	//! @return		none.
	virtual _void ResumeAllModal( ) PURE;

	virtual IGUIApplication* CreateTempModalUI( WStringPtr app_name ) PURE;
	virtual IGUIApplication* CreateTempModalUI( IGUIApplication* template_ui ) PURE;
	virtual _ubool IsShowingModal( ) const PURE;

	//!	Check whether the GUI object is clickable.
	//!	@param		object		The GUI object.
	//!	@return		True indicates it's clickable.
	virtual _ubool IsControlClickable( const IGUIObject* object ) const PURE;
	//!	Get the clickable GUI objects.
	//!	@param		objects		The GUI objects.
	//!	@return		none.
	virtual _void GetClickableGUIObjects( IGUIObjectRefArray& objects ) PURE;

	virtual _ubool IsAnimation( ) PURE;
	virtual _dword StartAnimation( IGUIObject* gui_object ) PURE;
	virtual _dword EndAnimation( IGUIObject* gui_object ) PURE;

	virtual const Camera& Get3DUICamera( ) const PURE;
	virtual const Matrix3& Get3DUIRenderMatrix( ) const PURE;
	virtual const Matrix4& Get3DUIViewMatrix( ) const PURE;
	virtual const Matrix4& Get3DUIOffsetMatrix( ) const PURE;

	virtual _ubool GetLastRender3DInUIInfo( GUI3DInUIInfo& info ) PURE;
	virtual _void PushRender3DInUIInfo( const GUI3DInUIInfo& info ) PURE;
	virtual _void PopRender3DInUIInfo( ) PURE;

	virtual _ubool GetLastTestPoint3DInUIInfo( GUI3DInUIInfo& info ) PURE;
	virtual _void PushTestPoint3DInUIInfo( const GUI3DInUIInfo& info ) PURE;
	virtual _void PopTestPoint3DInUIInfo( ) PURE;

	//!	Filter GUI objects by control.
	//!	@param		objects			The GUI objects.
	//!	@return		The GUI objects what is control will be filtered.
	virtual IGUIObjectRefArray FilterControl( const IGUIObjectRefArray& objects ) const PURE;
	//!	Filter GUI objects by container.
	//!	@param		objects			The GUI objects.
	//!	@return		The GUI objects what is container will be filtered.
	virtual IGUIObjectRefArray FilterContainer( const IGUIObjectRefArray& objects ) const PURE;
	//!	Filter GUI objects by component name list.
	//!	@param		objects			The GUI objects.
	//!	@param		components		The components name list what child object must has it, empty string indicates no care about the components, use '|' to split it.
	//!	@return		The GUI objects after filtered.
	virtual IGUIObjectRefArray FilterComponents( const IGUIObjectRefArray& objects, AStringPtr components = "" ) const PURE;
};

}