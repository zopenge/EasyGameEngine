//! @file     GUIModule.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GUIModule
//----------------------------------------------------------------------------

class GUIModule : public INTERFACE_MODULE_IMPL( IGUIModule )
{
private:
	typedef INTERFACE_MODULE_IMPL( IGUIModule ) BaseClass;

private:
	//!	The modal GUI application info
	struct ModalApplicationInfo : public FlagsObject
	{
		enum _FLAG
		{
			_FLAG_RECEIVE_MESSAGE		= 1 << 0,
			_FLAG_POPPING_BY_ANIMATION	= 1 << 1,
		};

		IGUIApplicationRef	mApplication;
		 
		ModalApplicationInfo( )
		{
			EnableFlags( _FLAG_RECEIVE_MESSAGE, _true );
		}
		ModalApplicationInfo( IGUIApplication* application, _ubool receive_message )
			: mApplication( application )
		{
			EnableFlags( _FLAG_RECEIVE_MESSAGE, receive_message );
		}
	};

private:
	typedef Array< ModalApplicationInfo > ModalApplicationInfoArray;
	typedef Array< GUI3DInUIInfo > GUI3DInUIInfoArray;

private:
	//!	The ratio of width and height
	_ubool						mIsUpdateSize;
	Vector2						mInitialSize;
	Vector2						mLastScreenSize;
	//!	The base region without any transform
	RectF						mBaseRegion;
	//!	The region what affected by transform when render
	RectF						mRegion;

	//! Enable Stretch
	_ubool						mEnableStretch;

	//!	The input recorder
	IInputRecorderRef			mInputRecorder;

	//!	The root GUI application
	GUIApplication*				mRootGUIApplication;

	//! The modal GUI application
	ModalApplicationInfoArray	mModalGUIApplications;
	_dword						mCreateModelIndex;

	//!	The GUI resource manager
	GUIResourceManager			mGUIResourceManager;
	//!	The GUI renderer
	GUIRenderer					mGUIRenderer;
	//!	The GUI processor
	IGUIProcessorRef			mGUIProcessor;
	//!	The GUI application notifier
	IGUIApplicationNotifierRef	mGUIApplicationNotifier;

	//!	The control animation playing counter
	_dword						mAnimationRefCount;
	//!	The control animation collections playing for debug
	Array< IGUIObject* >		mAnimationGUIObjects;

	Camera						m3DUICamera;
	Matrix3						m3DUIRenderMatrix;
	Matrix4						m3DUIViewMatrix;
	Matrix4						m3DUIOffsetMatrix;
	GUI3DInUIInfoArray			m3DUIRenderInfoStack;
	GUI3DInUIInfoArray			m3DUITestPointInfoStack;

private:
	//!	Root application handle GUI event.
	_ubool RootAppHandleGUIEvent( const EventBase& event, const FlagsObject& flags );

	//!	Handle messages.
	_ubool HandleClientSizeChangedMsg( const MessageClientSizeChanged& msg );
	_ubool HandleKeyUpMsg( const MessageKeyUp& msg );
	_ubool HandleKeyDownMsg( const MessageKeyDown& msg );
	_ubool HandleMouseMoveMsg( const MessageMouseMove& msg );
	_ubool HandleMouseButtonUpMsg( const MessageMouseButtonUp& msg );
	_ubool HandleMouseButtonDownMsg( const MessageMouseButtonDown& msg );
	_ubool HandleMouseButtonDoubleClickMsg( const MessageMouseButtonDoubleClick& msg );
	_ubool HandleMouseWheelMsg( const MessageMouseWheel& msg );
	_ubool HandleTouchMsg( const MessageTouch& msg );
	_ubool HandleEnterBackgroundMsg( const MessageEnterBackground& msg );
	_ubool HandleEnterForegroundMsg( const MessageEnterForeground& msg );

	//!	Update the GUI root region.
	_void UpdateRegion( const Matrix3& transform );

	//!	Get the top receive modal GUI application.
	IGUIApplication* GetTopReceiveModal( ) const;

	//!	Update model control.
	_void UpdateModals( );
	//!	Render modal control.
	_void RenderModals( IObject* viewport, const Matrix3& transform, const Color& color, const RectF& clip_rect );
	//!	Push modal control.
	_void PushModal( IGUIApplication* application, _ubool receive_message );

	//!	Get the clickable GUI objects.
	_void GetClickableGUIObjectsFromApp( IGUIObject* object, IGUIApplication* owner, IGUIObjectRefArray& objects ) const;
	//!	Test clickable GUI object.
	_ubool TestClickableGUIObject( IGUIApplication* gui_application, const Matrix3& transform, const IGUIObject* object ) const;
	//!	Test clickable GUI objects.
	_void TestClickableGUIObjects( IGUIApplication* gui_application, const Matrix3& transform, IGUIObjectRefArray& objects ) const;

	//! Update the 3d info
	_void Update3DInfo( IObject* viewport, const Matrix3& matrix );

	_ubool HideModal( _dword index );
	_ubool HideModalWithAnimation( _dword index, WStringPtr ani_name );

public:
	GUIModule( );
	virtual ~GUIModule( );

public:
	//!	Initialize.
	_ubool Initialize( _ubool enable_stretch, const Vector2& size );
	//!	Finalize.
	_void Finalize( );

// IObject Interface
public:
	virtual _void						Tick( _time_t tick, _dword elapse ) override;

// IModule Interface
public:
	virtual _void						HandleMessage( MessageBase& message ) override;

// IGUIModule Interface
public:
	virtual _void						SetProcessor( IGUIProcessor* processor ) override;
	virtual IGUIProcessor*				GetProcessor( ) override;

	virtual _void						SetApplicationNotifier( IGUIApplicationNotifier* notifier ) override;
	virtual IGUIApplicationNotifier*	GetApplicationNotifier( ) override;

	virtual IGUIApplication*			GetRootApplication( ) override;
	virtual IInputRecorder*				GetInputRecorder( ) override;
	virtual _void						ReleaseAllInput( ) override;

	virtual _void						EnableStretch( _ubool enable ) override;
	virtual _ubool						IsStretch( ) const override;

	virtual _void						SetScaleUISize( const Vector2& gui_size, const Vector2& screen_size ) override;

	virtual _void						SetSize( const Vector2& size ) override;
	virtual const Vector2&				GetSize( ) const override;

	virtual _void						SetLastScreenSize( const Vector2& size ) override;
	virtual const Vector2&				GetLastScreenSize( ) const override;

	virtual const RectF&				GetRegionF( ) const override;

	virtual _void						AddPreRenderInSceneGUIObject( IGUIObject* object, const Matrix3& transform, _float zsort ) override;
	virtual _void						AddPreRenderInSceneGUIObject( IGUIObject* object, const Matrix4& transform, _float zsort ) override;
	virtual _void						AddDelayRenderGUIObject( IGUIObject* object, const Matrix3& transform, const Color& color, const RectF& clip_rect ) override;
	virtual _void						AddDelayRenderGUIComponent( IGUIComponent* object, const Matrix3& transform, const Color& color, const RectF& clip_rect ) override;
	virtual _void						Render( IObject* viewport ) override;
	virtual _void						Render( IObject* viewport, const Vector2& pos, const Vector2& scale, const Color& color ) override;

	virtual IGUIApplication*			ShowModal( WStringPtr app_name, _ubool receive_message = _true, _ubool create_new_ui = _false ) override;
	virtual IGUIApplication*			ShowModal( IGUIApplication* application, _ubool receive_message = _true, _ubool create_new_ui = _false ) override;
	virtual IGUIApplication*			ShowModalWithAnimation( WStringPtr app_name, WStringPtr ani_name, _ubool pause_input, _ubool receive_message = _true, _ubool create_new_ui = _false ) override;
	virtual IGUIApplication*			ShowModalWithAnimation( IGUIApplication* application, WStringPtr ani_name, _ubool pause_input = _true, _ubool receive_message = _true, _ubool create_new_ui = _false ) override;
	virtual _void						HideModal( ) override;
	virtual _void						HideModal( WStringPtr app_name ) override;
	virtual _void						HideModal( IGUIApplication* gui_app ) override;
	virtual _void						HideAllModal( ) override;
	virtual _void						HideModalWithAnimation( WStringPtr ani_name ) override;
	virtual _void						HideModalWithAnimation( WStringPtr app_name, WStringPtr ani_name ) override;
	virtual _void						HideModalWithAnimation( IGUIApplication* gui_app, WStringPtr ani_name ) override;
	virtual IGUIApplication*			GetTopModal( ) const override;
	virtual _void						PauseAllModal( ) override;
	virtual _void						ResumeAllModal( ) override;
	virtual IGUIApplication*			CreateTempModalUI( WStringPtr app_name ) override;
	virtual IGUIApplication*			CreateTempModalUI( IGUIApplication* template_ui ) override;
	virtual _ubool						IsShowingModal( ) const override;

	virtual _ubool						IsControlClickable( const IGUIObject* object ) const override;
	virtual _void						GetClickableGUIObjects( IGUIObjectRefArray& objects ) override;

	virtual _ubool						IsAnimation( ) override;
	virtual _dword						StartAnimation( IGUIObject* gui_object ) override;
	virtual _dword						EndAnimation( IGUIObject* gui_object ) override;

	virtual const Camera&				Get3DUICamera( ) const override;
	virtual const Matrix3&				Get3DUIRenderMatrix( ) const override;
	virtual const Matrix4&				Get3DUIViewMatrix( ) const override;
	virtual const Matrix4&				Get3DUIOffsetMatrix( ) const override;

	virtual _ubool						GetLastRender3DInUIInfo( GUI3DInUIInfo& info ) override;
	virtual _void						PushRender3DInUIInfo( const GUI3DInUIInfo& info ) override;
	virtual _void						PopRender3DInUIInfo( ) override;

	virtual _ubool						GetLastTestPoint3DInUIInfo( GUI3DInUIInfo& info ) override;
	virtual _void						PushTestPoint3DInUIInfo( const GUI3DInUIInfo& info ) override;
	virtual _void						PopTestPoint3DInUIInfo( ) override;

	virtual IGUIObjectRefArray			FilterControl( const IGUIObjectRefArray& objects ) const override;
	virtual IGUIObjectRefArray			FilterContainer( const IGUIObjectRefArray& objects ) const override;
	virtual IGUIObjectRefArray			FilterComponents( const IGUIObjectRefArray& objects, AStringPtr components = "" ) const override;
};

}