//! @file     GUINullClasses.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NullGUIApplicationNotifier
//----------------------------------------------------------------------------

class NullGUIApplicationNotifier : public INTERFACE_OBJECT_IMPL( IGUIApplicationNotifier )
{
public:
	NullGUIApplicationNotifier( ) { }
	virtual ~NullGUIApplicationNotifier( ) { }

// IGUIApplicationNotifier Interface
public:
	virtual _ubool	OnAfterLoad( IGUIApplication* application ) { return _true; }

	virtual _void	OnBeforeUnload( IGUIApplication* application ) { }

	virtual _ubool	OnHandleEvent( IGUIApplication* application, const EventBase& event, const FlagsObject& flags ) { return _false; }
};

//----------------------------------------------------------------------------
// NullGUIResourceManager
//----------------------------------------------------------------------------

class NullGUIResourceManager : public INTERFACE_OBJECT_IMPL( IGUIResourceManager )
{
public:
	NullGUIResourceManager( ) { }
	virtual ~NullGUIResourceManager( ) { }

// IGUIResourceManager Interface
public:
	virtual _void					RegisterExclusiveComponentName( WStringPtr name_pattern ) { }
	virtual _ubool					GetExclusiveComponentName( WStringPtr name, Array< WString >& name_list ) const { return _false; }

	virtual IGUIObjectPassRef		CreateGUIObject( WStringPtr type_name ) { return _null; }
	virtual IGUIComponentPassRef	CreateGUIComponent( WStringPtr name, IGUIObject* object ) { return _null; }

	virtual IGUIObject*				CreateGUIObject( IGUIObject* template_guiobject, WStringPtr suffix, IGUIContainer* parent_guiobject, _ubool deep ) { return _null; }
	virtual IGUIObject*				CreateGUIObject( IGUIObject* template_guiobject, WStringPtr guiobject_typename, WStringPtr suffix, IGUIContainer* parent_guiobject, _ubool deep ) { return _null; }
	virtual IGUIObject*				CreateGUIObjectFromXMLString( WStringPtr type, WStringPtr xml_string, IGUIContainer* parent_object ) { return _null; }

	virtual IGUIApplication* 		CreateGUIApplication( IGUIContainer* parent ) { return _null; }
	virtual IGUIApplication* 		CreateGUIApplication( ISerializableNode* node, IGUIContainer* parent, _ubool delay_load ) { return _null; }
};

//----------------------------------------------------------------------------
// NullGUIProcessor
//----------------------------------------------------------------------------

class NullGUIProcessor : public TObject< IGUIProcessor >{
public:
	NullGUIProcessor( ) { }
	virtual ~NullGUIProcessor( ) { }

// IGUIProcessor Interface
public:
	virtual const Matrix4&	OnGetOrthoMatrix( IObject* viewport ) const { return Matrix4::cIdentity; }
	virtual const Matrix4&	OnGetViewMatrix( IObject* viewport ) const { return Matrix4::cIdentity; }
	virtual Vector2			OnGetViewportSize( IObject* viewport ) const { return Vector2::cIdentity; }
	virtual const Matrix4&	OnGetViewProjectionMatrix( IObject* viewport ) const { return Matrix4::cIdentity; }
	virtual Vector2			OnConvert3DTo2D( IObject* viewport, const Vector3& pos, _float* zsort ) const { return Vector2::cOrigin; }
	virtual Matrix4			OnGetViewportOverlayMatrix( IObject* viewport ) const { return Matrix4::cIdentity; }
	virtual Matrix4			OnGetViewportOffsetMatrix( IObject* viewport ) const { return Matrix4::cIdentity; }

	virtual _void			OnPushUserOrthoTransform( IObject* viewport, const Matrix4& transform ) { }
	virtual _void			OnPopUserOrthoTransform( IObject* viewport ) { }

	virtual _void			OnPushOverlayScissorRect( IObject* viewport, const RectF& rect ) { }
	virtual _void			OnPopOverlayScissorRect( IObject* viewport ) { }

	virtual _ubool			OnAppendGUIObjectAnimation( IGUIObject* gui_object, _dword delay, WStringPtr res_name ) { return _false; }
};

//----------------------------------------------------------------------------
// NullGUIModule
//----------------------------------------------------------------------------

class NullGUIModule : public INTERFACE_MODULE_IMPL( IGUIModule )
{
private:
	typedef INTERFACE_MODULE_IMPL( IGUIModule ) BaseClass;

public:
	NullGUIModule( ) : BaseClass( L"", Version::cZero ) { }
	virtual ~NullGUIModule( ) { }

// IGUIModule Interface
public:
	virtual _void						SetProcessor( IGUIProcessor* processor ) { }
	virtual IGUIProcessor*				GetProcessor( ) { return _null; }

	virtual _void						SetApplicationNotifier( IGUIApplicationNotifier* notifier ) {}
	virtual IGUIApplicationNotifier*	GetApplicationNotifier( ) { return _null; }

	virtual IGUIApplication*			GetRootApplication( ) { return _null; }
	virtual IInputRecorder*				GetInputRecorder( ) { return _null; }
	virtual _void						ReleaseAllInput( ) { }

	virtual _void						EnableStretch( _ubool enable ) { }
	virtual _ubool						IsStretch( ) const { return _false; }

	virtual _void						SetScaleUISize( const Vector2& gui_size, const Vector2& screen_size ) { }

	virtual _void						SetSize( const Vector2& size ) { }
	virtual const Vector2&				GetSize( ) const { return Vector2::cOrigin; }

	virtual _void						SetLastScreenSize( const Vector2& size ) { }
	virtual const Vector2&				GetLastScreenSize( ) const { return Vector2::cOrigin; }

	virtual const RectF&				GetRegionF( ) const { return RectF::cNull; }

	virtual _void						AddPreRenderInSceneGUIObject( IGUIObject* object, const Matrix3& transform, _float zsort ) { }
	virtual _void						AddPreRenderInSceneGUIObject( IGUIObject* object, const Matrix4& transform, _float zsort ) { }
	virtual _void						AddDelayRenderGUIObject( IGUIObject* object, const Matrix3& transform, const Color& color, const RectF& clip_rect ) { }
	virtual _void						AddDelayRenderGUIComponent( IGUIComponent* object, const Matrix3& transform, const Color& color, const RectF& clip_rect ) { }
	virtual _void						Render( IObject* viewport ) { }
	virtual _void						Render( IObject* viewport, const Vector2& pos, const Vector2& scale, const Color& color ) { }

	virtual _dword						PauseInputRecorder( ) { return 0; }
	virtual _dword						ResumeInputRecorder( ) { return 0; }

	virtual _ubool						OpenEditBox( IGUIObject* object ) { return _true; }

	virtual _void						ShowUIApplication( WStringPtr app_name, _ubool show ) { }
	virtual _void						ShowUIApplicationOnly( WStringPtr app_name ) { }
	virtual _void						HideAllUIApplication( ) { }

	virtual _ubool						MoveUIApplication( WStringPtr app_name, WStringPtr target_appname ) { return _false; }
	virtual _ubool						MoveUIApplicationToEnd( WStringPtr app_name ) { return _false; }

	virtual _ubool						SetModal( WStringPtr app_name ) { return _false; }
	virtual IGUIApplication*			ShowModal( WStringPtr app_name, _ubool receive_message, _ubool create_new_ui ) { return _null; }
	virtual IGUIApplication*			ShowModal( IGUIApplication* application, _ubool receive_message, _ubool create_new_ui ) { return _null; }
	virtual IGUIApplication*			ShowModalWithAnimation( WStringPtr app_name, WStringPtr ani_name, _ubool pause_input, _ubool receive_message, _ubool create_new_ui ) { return _null; }
	virtual IGUIApplication*			ShowModalWithAnimation( IGUIApplication* application, WStringPtr ani_name, _ubool pause_input, _ubool receive_message, _ubool create_new_ui ) { return _null; }
	virtual _void						HideModal( ) { }
	virtual _void						HideModal( WStringPtr app_name ) { }
	virtual _void						HideModal( IGUIApplication* gui_app ) { }
	virtual _void						HideAllModal( ) { }
	virtual _void						HideModalWithAnimation( WStringPtr ani_name ) { }
	virtual _void						HideModalWithAnimation( WStringPtr app_name, WStringPtr ani_name ) { }
	virtual _void						HideModalWithAnimation( IGUIApplication* gui_app, WStringPtr ani_name ) { }
	virtual _void						RemoveModal( WStringPtr app_name ) { }
	virtual IGUIApplication*			GetTopModal( ) const { return _null; }
	virtual _void						PauseAllModal( ) { }
	virtual _void						ResumeAllModal( ) { }
	virtual IGUIApplication*			CreateTempModalUI( WStringPtr app_name ) { return _null; }
	virtual IGUIApplication*			CreateTempModalUI( IGUIApplication* template_ui ) { return _null; }
	virtual _ubool						IsShowingModal( ) const { return _false; }

	virtual _ubool						IsControlClickable( const IGUIObject* object ) const { return _false; }
	virtual _void						GetClickableGUIObjects( IGUIObjectRefArray& objects ) { }

	virtual _ubool						IsAnimation( ) { return _false; }
	virtual _dword						StartAnimation( IGUIObject* gui_object ) { return 0; }
	virtual _dword						EndAnimation( IGUIObject* gui_object ) { return 0; }

	virtual const Camera&				Get3DUICamera( ) const { return Camera::cNull; }
	virtual const Matrix3&				Get3DUIRenderMatrix( ) const { return Matrix3::cIdentity; }
	virtual const Matrix4&				Get3DUIViewMatrix( ) const { return Matrix4::cIdentity; }
	virtual const Matrix4&				Get3DUIOffsetMatrix( ) const { return Matrix4::cIdentity; }

	virtual _ubool						GetLastRender3DInUIInfo( GUI3DInUIInfo& info ) { return _false; }
	virtual _void						PushRender3DInUIInfo( const GUI3DInUIInfo& info ) { }
	virtual _void						PopRender3DInUIInfo( ) { }
	virtual _ubool						GetLastTestPoint3DInUIInfo( GUI3DInUIInfo& info ) { return _false; }
	virtual _void						PushTestPoint3DInUIInfo( const GUI3DInUIInfo& info ) { }
	virtual _void						PopTestPoint3DInUIInfo( ) { }

	virtual IGUIObjectRefArray			FilterControl( const IGUIObjectRefArray& objects ) const { return IGUIObjectRefArray( ); }
	virtual IGUIObjectRefArray			FilterContainer( const IGUIObjectRefArray& objects ) const { return IGUIObjectRefArray( ); }
	virtual IGUIObjectRefArray			FilterComponents( const IGUIObjectRefArray& objects, AStringPtr components = "" ) const { return IGUIObjectRefArray( ); }
};

//----------------------------------------------------------------------------
// NullGUI
//----------------------------------------------------------------------------

class NullGUI
{
	SINGLETON( NullGUI )

private:
	NullGUIApplicationNotifier	mGUIApplicationNotifier;
	NullGUIResourceManager		mGUIResourceManager;
	NullGUIProcessor			mGUIProcessor;
	NullGUIModule				mGUIModule;

public:
	EGE_GETR_ACCESSOR( NullGUIApplicationNotifier, GUIApplicationNotifier )
	EGE_GETR_ACCESSOR( NullGUIResourceManager, GUIResourceManager )
	EGE_GETR_ACCESSOR( NullGUIProcessor, GUIProcessor )
	EGE_GETR_ACCESSOR( NullGUIModule, GUIModule )
};

}