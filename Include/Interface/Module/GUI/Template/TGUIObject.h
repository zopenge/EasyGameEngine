//! @file     TGUIObject.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TGUIObject
//----------------------------------------------------------------------------

template< typename Type >
class TGUIObject : public INTERFACE_OBJECT_TREE_IMPL( TResNameObject< TSerializable< TObject< Type > > >, IGUIObject )
{
protected:
	typedef INTERFACE_OBJECT_TREE_IMPL( TResNameObject< TSerializable< TObject< Type > > >, IGUIObject ) TBaseClass;

protected:
	struct UserDataInfo
	{
		_qword	mUserData1;
		_qword	mUserData2;

		UserDataInfo( )
		{
			mUserData1 = 0;
			mUserData2 = 0;
		}
	};

	class TestPoint3DInUIHelper
	{
	public:
		IGUIObject*				mGUIObject;
	public:
		TestPoint3DInUIHelper( )
			: mGUIObject( _null )
		{

		}
		~TestPoint3DInUIHelper( )
		{
			if ( mGUIObject != _null )
				mGUIObject->EndTestPoint3DInUI( );
		}
		_void Begin( IGUIObject* gui_object, const Matrix3& world_transform )
		{
			mGUIObject = gui_object;
			if ( mGUIObject != _null )
				mGUIObject->BeginTestPoint3DInUI( world_transform );
		}
	};

	class Get3DInUIScreenPositionHelper
	{
	private:
		Array< GUI3DInUIInfo >	m3DUIRenderInfoStack;
		Matrix3				m3DUIRenderMatrix;
		Matrix4				m3DUIOffsetMatrix;
		Matrix4				mCurrResultMatrix;
	private:
		_ubool				GetLastRender3DInUIInfo( GUI3DInUIInfo& info );
		_void				Update3DInfo( IObject* viewport, const Matrix3& matrix );
		_void				BeginRender3DInUI( const IGUIObject* gui_object, IObject* viewport, const Matrix3& world_transform );
		Matrix3				Render( const IGUIObject* gui_object, IObject* viewport, const Matrix3& transform, _ubool is_last );
	public:
		Vector2				GetPosition( const IGUIObject* gui_object, IObject* viewport );
	};

protected:
	//!	The user data info
	UserDataInfo*			mUserDataInfo;

	//!	The layer number
	_long					mLayerNumber;

	//!	The component group
	IGUIComponentGroupRef	mGUIComponentGroup;

protected:
	//!	Check whether it's hidden object.
	_ubool IsHidden( ) const;

	//!	Check whether can skip it when it's hidden.
	_ubool CanSkipInHiddenState( const EventBase& event ) const;

	//!	Get the axis transform.
	_void BeginRender3DInUI( IObject* viewport, const Matrix3& world_transform );
	_void EndRender3DInUI( IObject* viewport );

	//!	Output trace/warning/error log.
	_void OutputTraceString( WStringPtr string );
	_void OutputWarningString( WStringPtr string );
	_void OutputErrorString( WStringPtr string );
	_void OutputString( _LOG type, WStringPtr string );

	_ubool ScreenPositionTo3DLocalSpacePosition( const Vector2& origin_position, Vector2& local_pos );

protected:
	TGUIObject( );
	virtual ~TGUIObject( );

// IObject Interface
public:
	virtual IObject*					CloneTo( ) const override;

	virtual _void						Tick( _time_t tick, _dword elapse ) override;

	virtual _void						Uninitialize( ) override;

// IObjectTree Interface
public:
	virtual IObject*					CloneSelfTo( ) const override;

// IUserDataObject Interface
public:
	virtual _void						SetUserData1( _qword userdata ) override;
	virtual _qword						GetUserData1( ) const override;

	virtual _void						SetUserData2( _qword userdata ) override;
	virtual _qword						GetUserData2( ) const override;

// IDynamicResObject Interface
public:
	virtual _void						UnloadResources( _ubool force, _ubool clear_cache ) override;
	virtual _void						ReloadResourcesInBackgroundThread( _ubool lock ) override;
	virtual _void						ReloadResourcesInMainThread( _ubool lock ) override;

	virtual _ubool						AreAllResourcesAvailable( ) const override;
	virtual DwordRange					GetResourcesLoadedProgression( ) const override;

	virtual _void						ImportResource( _dword res_type, WStringPtr res_name ) override;
	virtual _void						ExportResources( IDynamicResObject* cache_obj ) const override;

	virtual _void						LoadDelaySubResource( _dword res_type, WStringPtr res_name ) override;
	virtual _void						LoadDelaySubResources( IDynamicResObject* object, ISerializableNode* node ) const override;

// IShowableObject Interface
public:
	virtual _void						Show( _ubool show ) override;
	virtual _ubool						IsShow( ) const override;

// ISerializable Interface
public:
	virtual _ubool						Import( ISerializableNode* node ) override;
	virtual _ubool						Export( ISerializableNode* node ) const override;

// IGUIComponent Interface
public:
	virtual IGUIObject*					GetGUIObject( ) const override;

	virtual _void						SetSleep( _ubool sleep ) override;
	virtual _ubool						IsSleep( ) const override;

	virtual _GUI_OBJECT_STATE			GetComponentObjStateID( ) const override;
	virtual _void						SetComponentObjStateID( _GUI_OBJECT_STATE state ) override;

	virtual _void						SetComponentSortIndex( _dword index ) override;
	virtual _dword						GetComponentSortIndex( ) const override;

	virtual WStringPtr					GetComponentObjStateName( ) const override;

	virtual _ubool						ImportEvent( ISerializableNode* node, WStringPtr event_name ) override;
	virtual _ubool						ImportEventFromXMLString( WStringPtr xml_string, WStringPtr event_name, _ubool locate_at_first_child = _true ) override;
	virtual _ubool						ExportEvent( ISerializableNode* node, WStringPtr event_name ) const override;
	virtual _ubool						ExportEventToXMLString( WStringPtr root_name, WStringPtr tag_name, WStringPtr event_name, WString& xml_string ) override;

	virtual _ubool						IsResident( ) const override;
	virtual _ubool						IsSupportKeys( ) const override;

	virtual _ubool						DoTick( ) const override;
	virtual _ubool						DoRender( ) const override;
	virtual _ubool						DoAfterChildRender() const override;
	virtual _ubool						DoHandleEvent( ) const override;
	virtual _ubool						DoIsHandleEvent( ) const override;
	virtual _ubool						DoTestRegion( ) const override;
	virtual _ubool						DoExport( ) const override;

	virtual _ubool						IsHandleEvent( _dword event_id ) const override;

	virtual _ubool						HandleEvent( const EventBase& event, const FlagsObject& flags ) override;
	virtual _void						Render( IObject* viewport, const Matrix3& transform, const Color& color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test ) override;
	virtual _void						RenderAfterRootApplication( IObject* viewport, const Matrix3& transform, const Color& color, const RectF& clip_rect ) override;

	virtual _GUI_TESTPOINT_RESULT_TYPE	PointInControl( const Vector2& position, const Matrix3& transform, Vector2* relative_position ) override;
	virtual _ubool						RegionInControl( const RectF& region, const Matrix3& transform ) override;
	virtual _ubool						IsClickableObject( ) const override;
	virtual _void						UpdateClickableState( ) override;
	virtual _ubool						IsCaptureMoveObject( ) const override;

// IGUIComponentGroup Interface
public:
	virtual IGUIComponentColor*			GetComponentColor( ) const override;
	virtual IGUIComponentEventHooker*	GetComponentEventHooker( ) const override;
	virtual IGUIComponentPosition*		GetComponentPosition( ) const override;
	virtual IGUIComponentState*			GetComponentState( ) const override;
	virtual IGUIComponentAnimation*		GetComponentAnimation( ) const override;

	virtual IGUIComponent*				GetComponent( AStringPtr name ) override;
	virtual IGUIComponent*				GetComponent( _GUI_OBJECT_STATE state, AStringPtr name ) override;

	virtual _ubool						HasComponent( AStringPtr name ) const override;
	virtual _ubool						HasComponent( _GUI_OBJECT_STATE state, AStringPtr name ) const override;
	virtual _ubool						HasComponents( const AStringArray& components ) const override;

	virtual IGUIComponent*				FindComponent( AStringPtr name ) override;
	virtual const IGUIComponent*		FindComponent( AStringPtr name ) const override;
	virtual IGUIComponent*				FindComponent( _GUI_OBJECT_STATE state, AStringPtr name ) override;
	virtual const IGUIComponent*		FindComponent( _GUI_OBJECT_STATE state, AStringPtr name ) const override;

	virtual IGUIComponent*				CreateComponent( AStringPtr name ) override;
	virtual _ubool						RemoveComponent( _GUI_OBJECT_STATE state, AStringPtr name ) override;
	virtual _ubool						RemoveComponent( AStringPtr name ) override;
	virtual _ubool						RemoveComponent( _GUI_OBJECT_STATE state ) override;
	virtual _void						RemoveAllComponents( ) override;
	virtual _void						RemoveAllExternalComponents( ) override;

	virtual _ubool						MoveUpComponent( _GUI_OBJECT_STATE state, AStringPtr name ) override;
	virtual _ubool						MoveDownComponent( _GUI_OBJECT_STATE state, AStringPtr name ) override;
	virtual _ubool						MoveComponent( _GUI_OBJECT_STATE state, AStringPtr name, _dword index ) override;
	virtual _ubool						MoveComponent( IGUIComponent* component, _dword index ) override;

	virtual _dword						GetComponentsNumber( ) const override;
	virtual _dword						GetComponentsNumber( _GUI_OBJECT_STATE state ) const override;
	virtual IGUIComponent*				GetComponentByIndex( _dword index ) override;
	virtual _dword						GetComponentIndex( IGUIComponent* component ) const override;
	virtual _dword						GetComponentIndex( _GUI_OBJECT_STATE state, AStringPtr name ) const override;

// IGUIObject Interface
public:
	virtual _ubool						IsApplication( ) const override;

	virtual _dword						GetLevelNumber( ) const override;

	virtual _void						SetLayerNumber( _long layer ) override;
	virtual _long						GetLayerNumber( ) const override;

	virtual WString						GetControlPath( ) const override;

	virtual _void						Focus( _ubool focus ) override;

	virtual FlagsObject&				GetStatesEx( ) override;
	virtual const FlagsObject&			GetStatesEx( ) const override;

	virtual FlagsObject&				GetAttributes( ) override;
	virtual const FlagsObject&			GetAttributes( ) const override;

	virtual _void						SetComponentGroup( IGUIComponentGroup* group_component ) override;
	virtual IGUIComponentGroup*			GetComponentGroup( ) override;
	virtual const IGUIComponentGroup*	GetComponentGroup( ) const override;

	virtual IGUIApplication*			GetParentApplication( ) override;
	virtual const IGUIApplication*		GetParentApplication( ) const override;
	virtual _ubool						FindParentObject( IGUIObject* parent ) const override;

	virtual IGUIObject*					TestPoint( const Vector2& origin_position, const Vector2& position, const Matrix3& transform, const FlagsObject& flags, Vector2* relative_position ) override;
	virtual IGUIObjectRefArray			TestPointByReturnList( const Vector2& origin_position, const Vector2& position, const Matrix3& transform, const FlagsObject& flags ) override;
	virtual IGUIObject*					GetIntersectObject( const RectF& region, const Matrix3& transform, const FlagsObject& flags ) override;
	virtual _ubool						Intersect( const RectF& clip_rect, const Matrix3& world_transform ) const override;
	virtual RectF						GetIntersectRect( const RectF& clip_rect, const Matrix3& world_transform ) const override;
	virtual IGUIObjectRefArray			GetIntersectObjects( IGUIContainer* container ) const override;
	virtual _ubool						RelativePointInControl( const Vector2& position ) override;

	virtual Vector2						GetScreenPosition( IObject* viewport, _float* zsort ) const override;
	virtual Matrix3						GetWorldTransform( ) const override;
	virtual Matrix3						GetChildWorldTransform( ) const override;
	virtual Matrix3						GetRelativeTransform( ) const override;
	virtual Matrix3						GetChildRelativeTransform( ) const override;

	virtual _void						GetWorldTransformsFromRoot( Matrix3Array& transforms ) const override;
	virtual _void						GetChildWorldTransformsFromRoot( Matrix3Array& transforms ) const override;

	virtual Color						MixColor( const Color& color ) const override;

	virtual _void						ResetControlAnimationInfo( _ubool deep = _false ) override;
	virtual _void						BeginTestPoint3DInUI( const Matrix3& world_transform ) override;
	virtual _void						EndTestPoint3DInUI( ) override;
};

//----------------------------------------------------------------------------

template< typename Type >
_ubool TGUIObject< Type >::Get3DInUIScreenPositionHelper::GetLastRender3DInUIInfo( GUI3DInUIInfo& info )
{
	if ( this->m3DUIRenderInfoStack.Number( ) == 0 )
		return _false;

	info = this->m3DUIRenderInfoStack.GetTailElement( );
	return _true;
}

template< typename Type >
_void TGUIObject< Type >::Get3DInUIScreenPositionHelper::Update3DInfo( IObject* viewport, const Matrix3& matrix )
{
	this->m3DUIRenderMatrix = matrix;

	Vector2 gui_size = GetGUIModule( )->GetSize( );
	Vector2 viewport_size = GetGUIModule( )->GetProcessor( )->OnGetViewportSize( viewport );
	Vector2 ui_scale( this->m3DUIRenderMatrix.m[0][0], this->m3DUIRenderMatrix.m[1][1] );
	Vector2 view_scale( viewport_size.x == 0.0f ? 0.0f : gui_size.x / viewport_size.x, viewport_size.y == 0.0f ? 0.0f : gui_size.y / viewport_size.y );

	Matrix3 render_rotation_matrix(
		this->m3DUIRenderMatrix.m[0][0], this->m3DUIRenderMatrix.m[0][1], 0.0f,
		this->m3DUIRenderMatrix.m[1][0], this->m3DUIRenderMatrix.m[1][1], 0.0f,
		0.0f, 0.0f, 1.0f
		);
	Vector3 render_offset( this->m3DUIRenderMatrix.m[2][0] * 2.0f / gui_size.x, -this->m3DUIRenderMatrix.m[2][1] * 2.0f / gui_size.y, 0.0f );
	// 
	this->m3DUIOffsetMatrix = Matrix4( ).FromTranslationRotation( render_offset, render_rotation_matrix );
	this->m3DUIOffsetMatrix *= Matrix4( ).Translation( ui_scale.x, -ui_scale.y, 0.0f );
	this->m3DUIOffsetMatrix *= Matrix4( ).Scaling( view_scale.x, view_scale.y, 1.0f );
	this->m3DUIOffsetMatrix *= Matrix4( ).Translation( -1.0f, 1.0f, 0.0f );
}

template< typename Type >
_void TGUIObject< Type >::Get3DInUIScreenPositionHelper::BeginRender3DInUI( const IGUIObject* gui_object, IObject* viewport, const Matrix3& world_transform )
{
	IGUIApplication* gui_application = (IGUIApplication*) gui_object->GetParentApplication( );
	IGUIComponent3DRender* renderer = gui_application->GetComponentT<IGUIComponent3DRender>( );

	GUI3DInUIInfo last_render_info;
	GUI3DInUIInfo curr_render_info;
	_ubool is_first = !this->GetLastRender3DInUIInfo( last_render_info );

	//! result = control tranlsation invert matrix * module scale matrix * control rotation matrix * module rotation matrix( identity ) * module final matrix
	Matrix4 tdui_matrix = gui_object->GetComponentPosition( )->GetRender3DUITransformMatrix( renderer->GetScalingMatrix( ) );
	curr_render_info.mRenderMatrix = world_transform;
	curr_render_info.mTransformMatrix = tdui_matrix;

	Matrix3 render_matrix_inverse = is_first ? this->m3DUIRenderMatrix : last_render_info.mRenderMatrix;
	render_matrix_inverse.Inverse( );
	Matrix3 self_matrix = world_transform * render_matrix_inverse;
	Matrix4 result_matrix;

	if ( is_first )
	{
		Matrix3 origin_mat = render_matrix_inverse * Matrix3::CreateTranslation( -self_matrix.GetTranslationVector( ) );
		curr_render_info.mCenterPosition = renderer->Get3DPosition( self_matrix.GetTranslationVector( ).x, self_matrix.GetTranslationVector( ).y );

		result_matrix = Matrix4::IncreaseDimension( origin_mat );
		result_matrix *= renderer->GetScalingMatrix( );
		result_matrix *= curr_render_info.mTransformMatrix;
	}
	else
	{
		curr_render_info.mCenterPosition = last_render_info.mCenterPosition;

		Matrix4 world_matrix = Matrix4::IncreaseDimension( self_matrix );
		world_matrix.SetTranslationVector( world_matrix.GetTranslationVector( ) * renderer->GetScalingMatrix( ) );
		curr_render_info.mTransformMatrix *= world_matrix * last_render_info.mTransformMatrix;

		result_matrix = Matrix4::IncreaseDimension( Matrix3( world_transform ).Inverse( ) );
		result_matrix *= renderer->GetScalingMatrix( );
		result_matrix *= curr_render_info.mTransformMatrix;
	}

	result_matrix.Translate( curr_render_info.mCenterPosition );
	result_matrix *= renderer->GetViewProjectionMatrix( ) * this->m3DUIOffsetMatrix;
	this->m3DUIRenderInfoStack.Append( curr_render_info );

	this->mCurrResultMatrix = result_matrix;
}

template< typename Type >
Matrix3 TGUIObject< Type >::Get3DInUIScreenPositionHelper::Render( const IGUIObject* gui_object, IObject* viewport, const Matrix3& transform, _ubool is_last )
{
	// Get world transform
	Matrix3 world_transform;
	if ( is_last )
		world_transform = gui_object->GetRelativeTransform( ) * transform;
	else
		world_transform = gui_object->GetChildRelativeTransform( ) * transform;

	_ubool is_ui_3d_object = gui_object->GetAttributes( ).HasFlags( _GUI_ATTRIBUTE_UI3D );
	if ( is_ui_3d_object )
		BeginRender3DInUI( gui_object, viewport, world_transform );

	return world_transform;
}

template< typename Type >
Vector2 TGUIObject< Type >::Get3DInUIScreenPositionHelper::GetPosition( const IGUIObject* gui_object, IObject* viewport )
{
	this->mCurrResultMatrix = Matrix4::cIdentity;
	this->m3DUIRenderInfoStack.Clear( );
	Matrix3 transform = Matrix3::cIdentity;
	Update3DInfo( viewport, transform );

	Array< const IGUIObject* > gui_object_array;
	for ( const IGUIObject* it = gui_object; it != _null; it = it->ParentObject( ) )
		gui_object_array.Append( it );

	for ( _long i = gui_object_array.Number( ) - 1; i >= 0; -- i )
		transform = Render( gui_object_array[i], viewport, transform, i == 0 );

	Matrix4 overlay_matrix = GetGUIModule( )->GetProcessor( )->OnGetViewportOverlayMatrix( viewport );
	Matrix4 offset_matrix = GetGUIModule( )->GetProcessor( )->OnGetViewportOffsetMatrix( viewport );

	Vector3 position = Vector3( transform.GetTranslationVector( ).x, transform.GetTranslationVector( ).y, 0.0f );
	position *= overlay_matrix;
	position *= mCurrResultMatrix;
	position *= offset_matrix;

	Vector2 viewport_size = GetGUIModule( )->GetProcessor( )->OnGetViewportSize( viewport );
	Vector2 screen_pos = Vector2(
		( 1.0f + position.x ) * viewport_size.x * 0.5f,
		( 1.0f - position.y ) * viewport_size.y * 0.5f
	);

	return screen_pos;
}

//----------------------------------------------------------------------------
// TGUIObject Implementation
//----------------------------------------------------------------------------

template< typename Type >
TGUIObject< Type >::TGUIObject( ) : TBaseClass( _null )
{
	mUserDataInfo	= _null;

	mLayerNumber	= 0;

	// Create and bind the component group
	mGUIComponentGroup = GetInterfaceFactory( )->CreateObjectPassRef< IGUIComponentGroup >( L"GUIComponentGroup", this );
	EGE_ASSERT( mGUIComponentGroup.IsValid( ) );

	// Show it as default
	GetComponentState( )->SetVisible( _true, _false, _false );
}

template< typename Type >
TGUIObject< Type >::~TGUIObject( )
{
	EGE_DELETE( mUserDataInfo );

	if ( this->mResName.IsEmpty( ) == _false )
	{
		WLOG_TRACE_1( L"Delete '%s' GUI object", this->mResName.Str( ) );
	}
}

template< typename Type >
_ubool TGUIObject< Type >::IsHidden( ) const
{
	if ( ! mGUIComponentGroup->GetComponentState( )->GetStatesEx( ).HasFlags( _GUI_STATE_EX_SHOW ) )
		return _true;

	return _false;
}

template< typename Type >
_ubool TGUIObject< Type >::CanSkipInHiddenState( const EventBase& event ) const
{
	switch ( event.mEventID )
	{
		case _GUI_EVENT_SHOW:
		case _GUI_EVENT_HIDE:
		case _GUI_EVENT_TOUCH_BEGIN:
		case _GUI_EVENT_TOUCH_MOVE:
		case _GUI_EVENT_TOUCH_END:
		case _GUI_EVENT_CLICK:
		case _GUI_EVENT_SCENE_RESIZE:
		case _GUI_EVENT_PERENT_HSIZE_CHANGED:
		case _GUI_EVENT_PERENT_VSIZE_CHANGED:
		case _GUI_EVENT_HSIZE_CHANGED:
		case _GUI_EVENT_VSIZE_CHANGED:
		case _GUI_EVENT_STATE_CHANGED:
			return _false;

		default:
			return _true;
	}
}

template< typename Type >
_void TGUIObject< Type >::BeginTestPoint3DInUI( const Matrix3& world_transform )
{
	IGUIApplication* gui_application = this->GetParentApplication( );
	IGUIComponent3DRender* renderer = gui_application->GetComponentT<IGUIComponent3DRender>( );

	GUI3DInUIInfo last_render_info;
	GUI3DInUIInfo curr_render_info;
	_ubool is_first = !GetGUIModule( )->GetLastTestPoint3DInUIInfo( last_render_info );

	//! result = control tranlsation invert matrix * module scale matrix * control rotation matrix * module rotation matrix( identity ) * module final matrix
	Matrix4 rotation_matrix = this->GetComponentPosition( )->GetRender3DUITransformMatrix( renderer->GetScalingMatrix( ) );

	if ( is_first )
	{
		curr_render_info.mCenterPosition = renderer->Get3DPosition( world_transform.GetTranslationVector( ).x, world_transform.GetTranslationVector( ).y );

		curr_render_info.mRotationMatrix = rotation_matrix;

		curr_render_info.mTransformMatrix = renderer->GetScalingMatrix( );
		curr_render_info.mTransformMatrix *= curr_render_info.mRotationMatrix;
		curr_render_info.mTransformMatrix.Translate( curr_render_info.mCenterPosition );
	}
	else
	{
		curr_render_info.mCenterPosition = last_render_info.mCenterPosition;

		curr_render_info.mRotationMatrix = rotation_matrix;
		curr_render_info.mRotationMatrix.Translate( Vector3( world_transform.GetTranslationVector( ).x, world_transform.GetTranslationVector( ).y, 0.0f ) * renderer->GetScalingMatrix( ) );
		curr_render_info.mRotationMatrix *= last_render_info.mRotationMatrix;

		curr_render_info.mTransformMatrix = renderer->GetScalingMatrix( );
		curr_render_info.mTransformMatrix *= curr_render_info.mRotationMatrix;
		curr_render_info.mTransformMatrix.Translate( curr_render_info.mCenterPosition );
	}

	GetGUIModule( )->PushTestPoint3DInUIInfo( curr_render_info );
}

template< typename Type >
_void TGUIObject< Type >::EndTestPoint3DInUI( )
{
	GetGUIModule( )->PopTestPoint3DInUIInfo( );
}

template< typename Type >
_void TGUIObject< Type >::BeginRender3DInUI( IObject* viewport, const Matrix3& world_transform )
{
	IGUIApplication* gui_application = this->GetParentApplication( );
	IGUIComponent3DRender* renderer = gui_application->GetComponentT<IGUIComponent3DRender>( );

	GUI3DInUIInfo last_render_info;
	GUI3DInUIInfo curr_render_info;
	_ubool is_first = !GetGUIModule( )->GetLastRender3DInUIInfo( last_render_info );

	//! result = control tranlsation invert matrix * module scale matrix * control rotation matrix * module rotation matrix( identity ) * module final matrix
	Matrix4 tdui_matrix = this->GetComponentPosition( )->GetRender3DUITransformMatrix( renderer->GetScalingMatrix( ) );
	curr_render_info.mRenderMatrix = world_transform;
	curr_render_info.mTransformMatrix = tdui_matrix;

	Matrix3 render_matrix_inverse = is_first ? GetGUIModule( )->Get3DUIRenderMatrix( ) : last_render_info.mRenderMatrix;
	render_matrix_inverse.Inverse( );
	Matrix3 self_matrix = world_transform * render_matrix_inverse;
	Matrix4 result_matrix;

	if ( is_first )
	{
		Matrix3 origin_mat = render_matrix_inverse * Matrix3::CreateTranslation( -self_matrix.GetTranslationVector( ) );
		curr_render_info.mCenterPosition = renderer->Get3DPosition( self_matrix.GetTranslationVector( ).x, self_matrix.GetTranslationVector( ).y );

		result_matrix = Matrix4::IncreaseDimension( origin_mat );
		result_matrix *= renderer->GetScalingMatrix( );
		result_matrix *= curr_render_info.mTransformMatrix;
	}
	else
	{
		curr_render_info.mCenterPosition = last_render_info.mCenterPosition;

		Matrix4 world_matrix = Matrix4::IncreaseDimension( self_matrix );
		world_matrix.SetTranslationVector( world_matrix.GetTranslationVector( ) * renderer->GetScalingMatrix( ) );
		curr_render_info.mTransformMatrix *= world_matrix * last_render_info.mTransformMatrix;

		result_matrix = Matrix4::IncreaseDimension( Matrix3( world_transform ).Inverse( ) );
		result_matrix *= renderer->GetScalingMatrix( );
		result_matrix *= curr_render_info.mTransformMatrix;
	}

	result_matrix.Translate( curr_render_info.mCenterPosition );
	result_matrix *= renderer->GetViewProjectionMatrix( ) * GetGUIModule( )->Get3DUIOffsetMatrix( );
	GetGUIModule( )->PushRender3DInUIInfo( curr_render_info );
	GetGUIModule( )->GetProcessor( )->OnPushUserOrthoTransform( viewport, result_matrix );
}

template< typename Type >
_void TGUIObject< Type >::EndRender3DInUI( IObject* viewport )
{
	GetGUIModule( )->PopRender3DInUIInfo( );
	GetGUIModule( )->GetProcessor( )->OnPopUserOrthoTransform( viewport );
}

template< typename Type >
_void TGUIObject< Type >::OutputTraceString( WStringPtr string )
{
	OutputString( _LOG_TRACE, string );
}

template< typename Type >
_void TGUIObject< Type >::OutputWarningString( WStringPtr string )
{
	OutputString( _LOG_WARNING, string );
}

template< typename Type >
_void TGUIObject< Type >::OutputErrorString( WStringPtr string )
{
	OutputString( _LOG_ERROR, string );
}

template< typename Type >
_void TGUIObject< Type >::OutputString( _LOG type, WStringPtr string )
{
	MODULE_OUTPUT_WSTRING_4( type, L"%s, TypeName: %s, ObjectName: %s, ResourceName: %s", 
		string.Str( ), this->GetObjectTypeName( ).Str( ), this->GetResName( ).Str( ), this->GetResourceName( ).Str( ) );
}

template< typename Type >
IObject* TGUIObject< Type >::CloneTo( ) const
{
	return CloneSelfTo( );
}

template< typename Type >
_void TGUIObject< Type >::Tick( _time_t tick, _dword elapse )
{
	// It's pausing
	if ( mGUIComponentGroup->GetComponentState( )->GetStatesEx( ).HasFlags( _GUI_STATE_EX_PAUSING ) )
		return;

	// Invoke Tick Function
	GetComponentEventHooker( )->InvokeTickFunc( elapse );

	// Update all components
	mGUIComponentGroup->Tick( tick, elapse );
}

template< typename Type >
_void TGUIObject< Type >::Uninitialize( )
{
	TBaseClass::Uninitialize( );

	// Remove the link from parent
	if ( this->mParentObject != _null )
		this->mParentObject->RemoveChildObject( this );
}

template< typename Type >
IObject* TGUIObject< Type >::CloneSelfTo( ) const
{
	IGUIObject* gui_object = (IGUIObject*)GetInterfaceFactory( )->CreateObject( this->GetClassTypeNameW( ) );
	if ( gui_object == _null )
		return _null;

	gui_object->SetResName( this->GetResName( ) );
	gui_object->SetLayerNumber( GetLayerNumber( ) );

	gui_object->Show( IsShow( ) );
	gui_object->SetSleep( IsSleep( ) );

	gui_object->SetUserData1( GetUserData1( ) );
	gui_object->SetUserData2( GetUserData2( ) );

	// Clone component group
	IGUIComponentGroupPassRef component_group = mGUIComponentGroup->CloneToPassRef< IGUIComponentGroup >( gui_object );
	EGE_ASSERT( component_group.IsValid( ) );

	// Bind component group
	gui_object->SetComponentGroup( component_group.GetPtr( ) );

	// Update GUI object states
	gui_object->UpdateClickableState( );

	return gui_object;
}

template< typename Type >
_void TGUIObject< Type >::SetUserData1( _qword userdata )
{
	if ( mUserDataInfo == _null )
		mUserDataInfo = new UserDataInfo( );

	mUserDataInfo->mUserData1 = userdata;
}

template< typename Type >
_qword TGUIObject< Type >::GetUserData1( ) const
{
	if ( mUserDataInfo == _null )
		return 0;

	return mUserDataInfo->mUserData1;
}

template< typename Type >
_void TGUIObject< Type >::SetUserData2( _qword userdata )
{
	if ( mUserDataInfo == _null )
		mUserDataInfo = new UserDataInfo( );

	mUserDataInfo->mUserData2 = userdata;
}

template< typename Type >
_qword TGUIObject< Type >::GetUserData2( ) const
{
	if ( mUserDataInfo == _null )
		return 0;

	return mUserDataInfo->mUserData2;
}

template< typename Type >
_void TGUIObject< Type >::UnloadResources( _ubool force, _ubool clear_cache )
{
	mGUIComponentGroup->UnloadResources( force, clear_cache );
}

template< typename Type >
_void TGUIObject< Type >::ReloadResourcesInBackgroundThread( _ubool lock )
{
	mGUIComponentGroup->ReloadResourcesInBackgroundThread( lock );
}

template< typename Type >
_void TGUIObject< Type >::ReloadResourcesInMainThread( _ubool lock )
{
	mGUIComponentGroup->ReloadResourcesInMainThread( lock );
}

template< typename Type >
_ubool TGUIObject< Type >::AreAllResourcesAvailable( ) const
{
	return mGUIComponentGroup->AreAllResourcesAvailable( );
}

template< typename Type >
DwordRange TGUIObject< Type >::GetResourcesLoadedProgression( ) const
{
	return mGUIComponentGroup->GetResourcesLoadedProgression( );
}

template< typename Type >
_void TGUIObject< Type >::ImportResource( _dword res_type, WStringPtr res_name )
{
	mGUIComponentGroup->ImportResource( res_type, res_name );
}

template< typename Type >
_void TGUIObject< Type >::ExportResources( IDynamicResObject* cache_obj ) const
{
	mGUIComponentGroup->ExportResources( cache_obj );
}

template< typename Type >
_void TGUIObject< Type >::Show( _ubool show )
{
	mGUIComponentGroup->GetComponentState( )->SetVisible( show );
}

template< typename Type >
_ubool TGUIObject< Type >::IsShow( ) const
{
	return mGUIComponentGroup->GetComponentState( )->GetStatesEx( ).HasFlags( _GUI_STATE_EX_SHOW );
}

template< typename Type >
_ubool TGUIObject< Type >::Import( ISerializableNode* node )
{
	if ( node == _null )
		return _false;

	// The node name must match the object type name
	if ( node->GetNodeName( ) != this->GetClassTypeNameW( ) )
	{
		WLOG_ERROR_2( L"The serializable node's name '%s' not match to '%s' GUI object when import", 
			node->GetNodeName( ).Str( ), this->GetClassTypeNameW( ).Str( ) );

		return _false;
	}

	// Read the object info
	node->Read( L"name", this->mResName );
	node->Read( L"layer", this->mLayerNumber );

	// Import the components
	if ( mGUIComponentGroup->Import( node ) == _false )
		return _false;

	// Update component click
	UpdateClickableState( );

	return _true;
}

template< typename Type >
_ubool TGUIObject< Type >::Export( ISerializableNode* node ) const
{
	if ( node == _null )
		return _false;

	// The node name must match the object type name
	if ( node->GetNodeName( ) != this->GetClassTypeNameW( ) )
	{
		WLOG_ERROR_2( L"The serializable node's name '%s' not match to '%s' GUI object when export", 
			node->GetNodeName( ).Str( ), this->GetClassTypeNameW( ).Str( ) );

		return _false;
	}

	// Write the object info
	node->Write( L"name", this->mResName );

	// Export the components
	return mGUIComponentGroup->Export( node );
}

template< typename Type >
_void TGUIObject< Type >::LoadDelaySubResource( _dword res_type, WStringPtr res_name )
{
	mGUIComponentGroup->LoadDelaySubResource( res_type, res_name );
}

template< typename Type >
_void TGUIObject< Type >::LoadDelaySubResources( IDynamicResObject* object, ISerializableNode* node ) const
{
	mGUIComponentGroup->LoadDelaySubResources( object, node );
}

template< typename Type >
IGUIObject* TGUIObject< Type >::GetGUIObject( ) const
{
	EGE_ASSERT( 0 );
	return _null;
}

template< typename Type >
_void TGUIObject< Type >::SetSleep( _ubool sleep )
{
	mGUIComponentGroup->SetSleep( sleep );
}

template< typename Type >
_ubool TGUIObject< Type >::IsSleep( ) const
{
	return mGUIComponentGroup->IsSleep( );
}

template< typename Type >
_GUI_OBJECT_STATE TGUIObject< Type >::GetComponentObjStateID( ) const
{
	return mGUIComponentGroup->GetComponentObjStateID( );
}

template< typename Type >
_void TGUIObject< Type >::SetComponentObjStateID( _GUI_OBJECT_STATE state )
{
	mGUIComponentGroup->SetComponentObjStateID( state );
}

template< typename Type >
WStringPtr TGUIObject< Type >::GetComponentObjStateName( ) const
{
	return mGUIComponentGroup->GetComponentObjStateName( );
}

template< typename Type >
_ubool TGUIObject< Type >::ImportEvent( ISerializableNode* node, WStringPtr event_name )
{
	return mGUIComponentGroup->ImportEvent( node, event_name );
}

template< typename Type >
_ubool TGUIObject< Type >::ImportEventFromXMLString( WStringPtr xml_string, WStringPtr event_name, _ubool locate_at_first_child )
{
	return mGUIComponentGroup->ImportEventFromXMLString( xml_string, event_name, locate_at_first_child );
}

template< typename Type >
_ubool TGUIObject< Type >::ExportEvent( ISerializableNode* node, WStringPtr event_name ) const
{
	return mGUIComponentGroup->ExportEvent( node, event_name );
}

template< typename Type >
_ubool TGUIObject< Type >::ExportEventToXMLString( WStringPtr root_name, WStringPtr tag_name, WStringPtr event_name, WString& xml_string )
{
	return mGUIComponentGroup->ExportEventToXMLString( root_name, tag_name, event_name, xml_string );
}

template< typename Type >
_void TGUIObject< Type >::SetComponentSortIndex( _dword index )
{
	mGUIComponentGroup->SetComponentSortIndex( index );
}

template< typename Type >
_dword TGUIObject< Type >::GetComponentSortIndex( ) const
{
	return mGUIComponentGroup->GetComponentSortIndex( );
}

template< typename Type >
_ubool TGUIObject< Type >::IsResident( ) const
{
	return _false;
}

template< typename Type >
_ubool TGUIObject< Type >::IsSupportKeys( ) const
{
	return _false;
}

template< typename Type >
_ubool TGUIObject< Type >::DoTick( ) const
{
	if ( this->ParentObject( ) == _null )
		return _true;

	// It's pausing
	if ( mGUIComponentGroup->GetComponentState( )->GetStatesEx( ).HasFlags( _GUI_STATE_EX_PAUSING ) )
		return _false;

	return this->ParentObject( )->DoTick( );
}

template< typename Type >
_ubool TGUIObject< Type >::DoRender( ) const
{
	return _false;
}

template< typename Type >
_ubool TGUIObject< Type >::DoAfterChildRender() const
{
	return _false;
}

template< typename Type >
_ubool TGUIObject< Type >::DoHandleEvent( ) const
{
	return _false;
}

template< typename Type >
_ubool TGUIObject< Type >::DoIsHandleEvent( ) const
{
	return _false;
}

template< typename Type >
_ubool TGUIObject< Type >::DoTestRegion( ) const
{
	return _false;
}

template< typename Type >
_ubool TGUIObject< Type >::DoExport( ) const
{
	return _false;
}

template< typename Type >
_ubool TGUIObject< Type >::IsHandleEvent( _dword event_id ) const
{
	return mGUIComponentGroup->IsHandleEvent( event_id );
}

template< typename Type >
_ubool TGUIObject< Type >::HandleEvent( const EventBase& event, const FlagsObject& flags )
{
	// Skip for hidden object
	if ( IsHidden( ) && CanSkipInHiddenState( event ) )
		return _true; // Skip to pass the event

	// Let the parent object capture the event first
	if ( flags.HasFlags( _GUI_MESSAGE_DELIVER_PARENT ) )
	{
		// Make sure the control is not dropping
		if ( mGUIComponentGroup->GetComponentState( )->GetStatesEx( ).HasFlags( _GUI_STATE_EX_DROPPING ) == _false )
		{
			IGUIObject* parent_object = this->ParentObject( );
			if ( parent_object )
			{
				// Skip deliver to child
				FlagsObject skip_deliver_to_child( flags );
				skip_deliver_to_child.ClearFlags( _GUI_MESSAGE_DELIVER_CHILD );

				// Let the parent object to handle event
				if ( parent_object->HandleEvent( event, skip_deliver_to_child ) )
					return _true;
			}
		}
	}

	// Handle all components
	if ( mGUIComponentGroup->HandleEvent( event, flags ) )
		return _true; // Skip all default handle event procession

	// Continue to pass the event
	return _false;
}

template< typename Type >
_void TGUIObject< Type >::Render( IObject* viewport, const Matrix3& transform, const Color& color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test )
{
	// Skip for hidden object
	if ( IsHidden( ) )
		return;

	// It's delay render object
	if ( mGUIComponentGroup->GetComponentState( )->GetStatesEx( ).HasFlags( _GUI_STATE_EX_DELAY_RENDER ) )
	{
		GetGUIModule( )->AddDelayRenderGUIObject( this, transform, color, clip_rect );
		return;
	}
	
	// Get the attributes
	const FlagsObject& attributes = this->mGUIComponentGroup->GetComponentState( )->GetAttributes( );
	if ( attributes.HasFlags( _GUI_ATTRIBUTE_SCENE3D ) )
		return;
	
	// Get world transform
	Matrix3 world_transform = this->GetRelativeTransform( ) * transform;

	// Get the clip flags
	_ubool clip_child = attributes.HasFlags( _GUI_ATTRIBUTE_CLIPCHILD ) && !attributes.HasFlags( _GUI_ATTRIBUTE_DONT_CLIPSELF );

	// Fix the clip rect
	RectF fixed_clip_rect;
	if ( clip_child )
	{
		fixed_clip_rect = this->GetIntersectRect( clip_rect, world_transform );
		if ( fixed_clip_rect == RectF::cNull )
			return;
	}

	// Get the axis transform
	_ubool is_ui_3d_object = attributes.HasFlags( _GUI_ATTRIBUTE_UI3D );
	if ( is_ui_3d_object )
		BeginRender3DInUI( viewport, world_transform );

	// Get the hooker
	IGUIComponentEventHooker* hooker = GetComponentEventHooker( );
	EGE_ASSERT( hooker != _null );

	// Get the mix color
	Color mixed_color = MixColor( color );

	// Render by clip child objects
	if ( clip_child )
	{
		// Begin to render
		GetGUIModule( )->GetProcessor( )->OnPushOverlayScissorRect( viewport, fixed_clip_rect );
		{
			hooker->InvokeBeginRenderFunc( world_transform, mixed_color, fixed_clip_rect );
			{
				this->mGUIComponentGroup->Render( viewport, world_transform, mixed_color, fixed_clip_rect, in_clip_state, skip_region_test );
			}
			hooker->InvokeEndRenderFunc( world_transform, mixed_color );
		}
		GetGUIModule( )->GetProcessor( )->OnPopOverlayScissorRect( viewport );
	}
	// Render without scissor rect
	else
	{
		// Begin to render
		hooker->InvokeBeginRenderFunc( world_transform, mixed_color, clip_rect );
		{
			this->mGUIComponentGroup->Render( viewport, world_transform, mixed_color, clip_rect, in_clip_state, skip_region_test );
		}
		hooker->InvokeEndRenderFunc( world_transform, mixed_color );
	}

	if ( is_ui_3d_object )
		EndRender3DInUI( viewport );

	hooker->InvokeAfterRenderFunc( world_transform, mixed_color );
}

template< typename Type >
_void TGUIObject< Type >::RenderAfterRootApplication( IObject* viewport, const Matrix3& transform, const Color& color, const RectF& clip_rect )
{

}

template< typename Type >
_GUI_TESTPOINT_RESULT_TYPE TGUIObject< Type >::PointInControl( const Vector2& position, const Matrix3& transform, Vector2* relative_position )
{
	// Test self
	_GUI_TESTPOINT_RESULT_TYPE ret = mGUIComponentGroup->PointInControl( position, transform, relative_position );
	return ret;
}

template< typename Type >
_ubool TGUIObject< Type >::RegionInControl( const RectF& region, const Matrix3& transform )
{
	// Build the world transform
	Matrix3 world_transform = GetRelativeTransform( ) * transform;

	// Test self
	if ( mGUIComponentGroup->RegionInControl( region, world_transform ) == _false )
		return _false;

	return _true;
}

template< typename Type >
_ubool TGUIObject< Type >::IsCaptureMoveObject( ) const
{
	return _false;
}

template< typename Type >
_ubool TGUIObject< Type >::IsClickableObject( ) const
{
	return _false;
}

template< typename Type >
_void TGUIObject< Type >::UpdateClickableState( )
{
	if ( !this->IsClickableObject( ) )
		return;

	_ubool enable_click = _false;
	for ( _dword i = 1; i < _GUI_STATE_MAXNUMBER; ++ i )
	{
		if ( mGUIComponentGroup->GetComponentsNumber( (_GUI_OBJECT_STATE) i ) != 0 
			|| mGUIComponentGroup->HasComponent("FGUIComponentParticlePlayerGroup")
			|| mGUIComponentGroup->HasComponent("FGUIComponentScript")
			|| mGUIComponentGroup->HasComponent("FGUIComponentSound"))
		{
			enable_click = _true;
			break;
		}
	}
	
	if ( enable_click )
	{
		if ( !mGUIComponentGroup->HasComponent( "GUIComponentClick" ) )
			mGUIComponentGroup->CreateComponent( "GUIComponentClick" );
	}
	else
	{
		if ( mGUIComponentGroup->HasComponent( "GUIComponentClick" ) )
			mGUIComponentGroup->RemoveComponent( "GUIComponentClick" );
	}
}

template< typename Type >
IGUIComponentColor* TGUIObject< Type >::GetComponentColor( ) const
{
	return mGUIComponentGroup->GetComponentColor( );
}

template< typename Type >
IGUIComponentEventHooker* TGUIObject< Type >::GetComponentEventHooker( ) const
{
	return mGUIComponentGroup->GetComponentEventHooker( );
}

template< typename Type >
IGUIComponentPosition* TGUIObject< Type >::GetComponentPosition( ) const
{
	return mGUIComponentGroup->GetComponentPosition( );
}

template< typename Type >
IGUIComponentState* TGUIObject< Type >::GetComponentState( ) const
{
	return mGUIComponentGroup->GetComponentState( );
}

template< typename Type >
IGUIComponentAnimation* TGUIObject< Type >::GetComponentAnimation( ) const
{
	return mGUIComponentGroup->GetComponentAnimation( );
}

template< typename Type >
IGUIComponent* TGUIObject< Type >::GetComponent( AStringPtr name )
{
	return mGUIComponentGroup->GetComponent( name );
}

template< typename Type >
IGUIComponent* TGUIObject< Type >::GetComponent( _GUI_OBJECT_STATE state, AStringPtr name )
{
	IGUIComponent* component = mGUIComponentGroup->GetComponent( state, name );
	if ( state != _GUI_STATE_NORMAL )
		UpdateClickableState( );
	return component;
}

template< typename Type >
_ubool TGUIObject< Type >::HasComponent( AStringPtr name ) const
{
	return mGUIComponentGroup->HasComponent( name );
}

template< typename Type >
_ubool TGUIObject< Type >::HasComponent( _GUI_OBJECT_STATE state, AStringPtr name ) const
{
	return mGUIComponentGroup->HasComponent( state, name );
}

template< typename Type >
_ubool TGUIObject< Type >::HasComponents( const AStringArray& components ) const
{
	return mGUIComponentGroup->HasComponents( components );
}

template< typename Type >
IGUIComponent* TGUIObject< Type >::FindComponent( AStringPtr name )
{
	return mGUIComponentGroup->FindComponent( name );
}

template< typename Type >
const IGUIComponent* TGUIObject< Type >::FindComponent( AStringPtr name ) const
{
	return mGUIComponentGroup->FindComponent( name );
}

template< typename Type >
IGUIComponent* TGUIObject< Type >::FindComponent( _GUI_OBJECT_STATE state, AStringPtr name )
{
	return mGUIComponentGroup->FindComponent( state, name );
}

template< typename Type >
const IGUIComponent* TGUIObject< Type >::FindComponent( _GUI_OBJECT_STATE state, AStringPtr name ) const
{
	return mGUIComponentGroup->FindComponent( state, name );
}

template< typename Type >
IGUIComponent* TGUIObject< Type >::CreateComponent( AStringPtr name )
{
	return mGUIComponentGroup->CreateComponent( name );
}

template< typename Type >
_ubool TGUIObject< Type >::RemoveComponent( _GUI_OBJECT_STATE state, AStringPtr name )
{
	_ubool ret = mGUIComponentGroup->RemoveComponent( state, name );
	if ( state != _GUI_STATE_NORMAL )
		UpdateClickableState( );
	return ret;
}

template< typename Type >
_ubool TGUIObject< Type >::RemoveComponent( AStringPtr name )
{
	return mGUIComponentGroup->RemoveComponent( name );
}

template< typename Type >
_ubool TGUIObject< Type >::RemoveComponent( _GUI_OBJECT_STATE state )
{
	_ubool ret = mGUIComponentGroup->RemoveComponent( state );
	if ( state != _GUI_STATE_NORMAL )
		UpdateClickableState( );
	return ret;
}

template< typename Type >
_void TGUIObject< Type >::RemoveAllComponents( )
{
	mGUIComponentGroup->RemoveAllComponents( );
	UpdateClickableState( );
}

template< typename Type >
_void TGUIObject< Type >::RemoveAllExternalComponents( )
{
	mGUIComponentGroup->RemoveAllExternalComponents( );
	UpdateClickableState( );
}

template< typename Type >
_ubool TGUIObject< Type >::MoveUpComponent( _GUI_OBJECT_STATE state, AStringPtr name )
{
	return mGUIComponentGroup->MoveUpComponent( state, name );
}

template< typename Type >
_ubool TGUIObject< Type >::MoveDownComponent( _GUI_OBJECT_STATE state, AStringPtr name )
{
	return mGUIComponentGroup->MoveDownComponent( state, name );
}

template< typename Type >
_ubool TGUIObject< Type >::MoveComponent( _GUI_OBJECT_STATE state, AStringPtr name, _dword index )
{
	return mGUIComponentGroup->MoveComponent( state, name, index );
}

template< typename Type >
_ubool TGUIObject< Type >::MoveComponent( IGUIComponent* component, _dword index )
{
	return mGUIComponentGroup->MoveComponent( component, index );
}

template< typename Type >
_dword TGUIObject< Type >::GetComponentsNumber( ) const
{
	return mGUIComponentGroup->GetComponentsNumber( );
}

template< typename Type >
_dword TGUIObject< Type >::GetComponentsNumber( _GUI_OBJECT_STATE state ) const
{
	return mGUIComponentGroup->GetComponentsNumber( state );
}

template< typename Type >
IGUIComponent* TGUIObject< Type >::GetComponentByIndex( _dword index )
{
	return mGUIComponentGroup->GetComponentByIndex( index );
}

template< typename Type >
_dword TGUIObject< Type >::GetComponentIndex( IGUIComponent* component ) const
{
	return mGUIComponentGroup->GetComponentIndex( component );
}

template< typename Type >
_dword TGUIObject< Type >::GetComponentIndex( _GUI_OBJECT_STATE state, AStringPtr name ) const
{
	return mGUIComponentGroup->GetComponentIndex( state, name );
}

template< typename Type >
_ubool TGUIObject< Type >::IsApplication( ) const
{
	return _false;
}

template< typename Type >
_dword TGUIObject< Type >::GetLevelNumber( ) const
{
	_dword level = 0;
	for ( const IGUIObject* parent_object = this->mParentObject; parent_object != _null; parent_object = parent_object->ParentObject( ) )
		level ++;

	return level;
}

template< typename Type >
_void TGUIObject< Type >::SetLayerNumber( _long layer )
{
	mLayerNumber = layer;
}

template< typename Type >
_long TGUIObject< Type >::GetLayerNumber( ) const
{
	return mLayerNumber;
}

template< typename Type >
WString TGUIObject< Type >::GetControlPath( ) const
{
	WString control_path = this->GetResName( );

	for ( const IGUIObject* parent = this->mParentObject; parent != _null; parent = parent->ParentObject( ) )
	{
		if ( parent->GetResName( ).IsEmpty( ) )
		{
			// The middle parent object must have resource name
			if ( parent->ParentObject( ) != _null )
				return WString( L"" );
		}
		else
		{
			control_path = parent->GetResName( ) + L"/" + control_path;
		}
	}

	return control_path;
}

template< typename Type >
_void TGUIObject< Type >::Focus( _ubool focus )
{
	_GUI_OBJECT_STATE state = mGUIComponentGroup->GetComponentState( )->GetState( );

	// Focus on
	if ( focus )
	{
		switch ( state )
		{
			case _GUI_STATE_NORMAL:
				mGUIComponentGroup->GetComponentState( )->SetState( _GUI_STATE_FOCUS );
				break;

			case _GUI_STATE_CHECKED:
				mGUIComponentGroup->GetComponentState( )->SetState( _GUI_STATE_CHECKED_FOCUS );
				break;

			default:
				return;
		}

		HandleEvent( GUIEventFocusOn( ), FlagsObject( ) );
	}
	// Focus off
	else
	{
		switch ( state )
		{
			case _GUI_STATE_FOCUS:
				mGUIComponentGroup->GetComponentState( )->SetState( _GUI_STATE_NORMAL );
				break;

			case _GUI_STATE_CHECKED_FOCUS:
				mGUIComponentGroup->GetComponentState( )->SetState( _GUI_STATE_CHECKED );
				break;

			default:
				return;
		}

		HandleEvent( GUIEventFocusOff( ), FlagsObject( ) );
	}
}

template< typename Type >
FlagsObject& TGUIObject< Type >::GetStatesEx( )
{
	return mGUIComponentGroup->GetComponentState( )->GetStatesEx( );
}

template< typename Type >
const FlagsObject& TGUIObject< Type >::GetStatesEx( ) const
{
	return mGUIComponentGroup->GetComponentState( )->GetStatesEx( );
}

template< typename Type >
FlagsObject& TGUIObject< Type >::GetAttributes( )
{
	return this->mGUIComponentGroup->GetComponentState( )->GetAttributes( );
}

template< typename Type >
const FlagsObject& TGUIObject< Type >::GetAttributes( ) const
{
	return this->mGUIComponentGroup->GetComponentState( )->GetAttributes( );
}

template< typename Type >
_void TGUIObject< Type >::SetComponentGroup( IGUIComponentGroup* group_component )
{
	EGE_ASSERT( group_component != _null );

	mGUIComponentGroup = group_component;
}

template< typename Type >
IGUIComponentGroup* TGUIObject< Type >::GetComponentGroup( )
{
	return mGUIComponentGroup;
}

template< typename Type >
const IGUIComponentGroup* TGUIObject< Type >::GetComponentGroup( ) const
{
	return mGUIComponentGroup;
}

template< typename Type >
IGUIApplication* TGUIObject< Type >::GetParentApplication( )
{
	for ( IGUIObject* object = this; object != _null; object = object->ParentObject( ) )
	{
		if ( object->IsApplication( ) )
			return static_cast< IGUIApplication* >( object );
	}

	// We should never reach here, because the root application will be the last choice for this function
	EGE_ASSERT( _false );
	return _null;
}

template< typename Type >
const IGUIApplication* TGUIObject< Type >::GetParentApplication( ) const
{
	for ( const IGUIObject* object = this; object != _null; object = object->ParentObject( ) )
	{
		if ( object->IsApplication( ) )
			return static_cast< const IGUIApplication* >( object );
	}

	// We should never reach here, because the root application will be the last choice for this function
	EGE_ASSERT( _false );
	return _null;
}

template< typename Type >
_ubool TGUIObject< Type >::FindParentObject( IGUIObject* parent ) const
{
	for ( const IGUIObject* object = this; object != _null; object = object->ParentObject( ) )
	{
		if ( object == parent )
			return _true;
	}
	return _false;
}

template< typename Type >
_ubool TGUIObject< Type >::ScreenPositionTo3DLocalSpacePosition( const Vector2& origin_position, Vector2& local_pos )
{
	GUI3DInUIInfo curr_render_info;
	if ( GetGUIModule( )->GetLastTestPoint3DInUIInfo( curr_render_info ) == _false )
		return _false;

	IGUIApplication* gui_application = this->GetParentApplication( );
	IGUIComponent3DRender* renderer = gui_application->GetComponentT<IGUIComponent3DRender>( );
	
	Vector2 gui_size = GetGUIModule( )->GetSize( );
	Ray ray = Ray::GetPickRay( origin_position.x, origin_position.y, gui_size.x, gui_size.y, GetGUIModule( )->Get3DUIViewMatrix( ), renderer->GetProjectionMatrix( ) );

	Plane plane = Plane::cXYPlane * curr_render_info.mTransformMatrix;

	// Get the pick positions of near plane
	_float distance = 0.0f;
	if ( Intersection::RayVSPlane( ray, plane, &distance ) == _false )
		return _false;

	Vector3	pick_pos = ray.mOrigin + ray.mDirection * distance;
	pick_pos *= Matrix4( curr_render_info.mTransformMatrix ).Inverse( );

	local_pos.x = pick_pos.x;
	local_pos.y = pick_pos.y;

	return _true;
}

template< typename Type >
IGUIObject* TGUIObject< Type >::TestPoint( const Vector2& origin_position, const Vector2& position, const Matrix3& transform, const FlagsObject& flags, Vector2* relative_position )
{
	if ( IsHidden( ) )
		return _null;

	if ( flags.HasFlags( _GUI_TESTPOINT_CLICKABLE ) )
	{
		if ( IsHandleEvent( _GUI_EVENT_TOUCH_BEGIN ) == _false )
			return _null;
	}

	TestPoint3DInUIHelper test_point_helper;

	Vector2 local_position = position;
	Matrix3 matrix_self = this->GetRelativeTransform( ) * transform;

	_ubool is_ui_3d_object = this->mGUIComponentGroup->GetComponentState( )->GetAttributes( ).HasFlags( _GUI_ATTRIBUTE_UI3D );

	if ( is_ui_3d_object )
	{
		test_point_helper.Begin( this, matrix_self );
		if ( this->ScreenPositionTo3DLocalSpacePosition( origin_position, local_position ) == _false )
			return _null;
		matrix_self = Matrix3::cIdentity;
	}

	if ( PointInControl( local_position, matrix_self, relative_position ) == _GTRT_OUT )
		return _null;
	
	return this;
}

template< typename Type >
IGUIObjectRefArray TGUIObject< Type >::TestPointByReturnList( const Vector2& origin_position, const Vector2& position, const Matrix3& transform, const FlagsObject& flags )
{
	IGUIObjectRefArray objects;

	IGUIObjectRef object = TestPoint( origin_position, position, transform, flags, _null );
	if ( object.IsValid( ) )
		objects.Append( object );

	return objects;
}

template< typename Type >
IGUIObject* TGUIObject< Type >::GetIntersectObject( const RectF& region, const Matrix3& transform, const FlagsObject& flags )
{
	if ( IsHidden( ) )
		return _null;

	if ( flags.HasFlags( _GUI_TESTPOINT_CLICKABLE ) )
	{
		if ( IsHandleEvent( _GUI_EVENT_TOUCH_BEGIN ) == _false )
			return _null;
	}

	if ( RegionInControl( region, transform ) == _false )
		return _null;

	return this;
}

template< typename Type >
_ubool TGUIObject< Type >::Intersect( const RectF& clip_rect, const Matrix3& world_transform ) const
{
	Vector2 halfsize = this->GetComponentPosition( )->GetLogicSize( ) * 0.5f;
	Vector2 lt = (-halfsize) * world_transform;
	Vector2 rb = halfsize * world_transform;

	_float l, r;
	if ( lt.x <= rb.x )
	{
		l = lt.x;
		r = rb.x;
	}
	else
	{
		r = lt.x;
		l = rb.x;
	}

	_float t, b;
	if ( lt.y <= rb.y )
	{
		t = lt.y;
		b = rb.y;
	}
	else
	{
		b = lt.y;
		t = rb.y;
	}

	return clip_rect.Intersect( RectF( l, t, r, b ) );
}

template< typename Type >
RectF TGUIObject< Type >::GetIntersectRect( const RectF& clip_rect, const Matrix3& world_transform ) const
{
	Vector2 halfsize = this->GetComponentPosition( )->GetLogicSize( ) * 0.5f;
	Vector2 lt = (-halfsize) * world_transform;
	Vector2 rb = halfsize * world_transform;

	_float l, r;
	if ( lt.x <= rb.x )
	{
		l = lt.x;
		r = rb.x;
	}
	else
	{
		r = lt.x;
		l = rb.x;
	}

	_float t, b;
	if ( lt.y <= rb.y )
	{
		t = lt.y;
		b = rb.y;
	}
	else
	{
		b = lt.y;
		t = rb.y;
	}

	return RectF::Intersect( clip_rect, RectF( l, t, r, b ) );
}

template< typename Type >
IGUIObjectRefArray TGUIObject< Type >::GetIntersectObjects( IGUIContainer* container ) const
{
	IGUIObjectRefArray gui_objects;

	if ( container != _null )
	{
		Vector2 pos			= this->GetWorldTransform( ).GetTranslationVector( );
		Matrix3 transform	= container->ParentObject( ) ? container->ParentObject( )->GetChildWorldTransform( ) : Matrix3::cIdentity;

		// Get the hit GUI objects and remove testing object
		gui_objects = container->TestPointByReturnList( pos, pos, transform, FlagsObject( ) );
		gui_objects.Remove( (IGUIObject*)this );
	}

	return gui_objects;
}

template< typename Type >
_ubool TGUIObject< Type >::RelativePointInControl( const Vector2& position )
{
	return this->PointInControl( position, GetWorldTransform( ), _null ) != _GTRT_OUT;
}

template< typename Type >
Vector2 TGUIObject< Type >::GetScreenPosition( IObject* viewport, _float* zsort ) const
{
	_dword type = 0;	// 0 is default, 1 is render 3d in scene, 2 is render3d in ui
	const IGUIObject* target_gui_object = this;

	for ( const IGUIObject* it = this; it != _null; it = it->ParentObject( ) )
	{
		const FlagsObject& attributes = it->GetAttributes( );

		if ( attributes.HasFlags( _GUI_ATTRIBUTE_SCENE3D ) )
		{
			target_gui_object = it;
			type = 1;
			break;
		}
		else if ( attributes.HasFlags( _GUI_ATTRIBUTE_UI3D ) )
		{
			target_gui_object = it;
			type = 2;
			break;
		}
	}

	switch ( type )
	{
	case 1:
	{
		if ( target_gui_object == this )
		{
			return this->GetComponentPosition( )->GetRenderInSceneScreenPosition( viewport, zsort );
		}
		else
		{
			Matrix3 matrix = this->GetRelativeTransform( );
			for ( const IGUIObject* it = this->ParentObject( ); it != target_gui_object; it = it->ParentObject( ) )
				matrix *= it->GetChildRelativeTransform( );
			matrix *= target_gui_object->GetChildRelativeTransform( );
			
			Vector2 ret = target_gui_object->GetComponentPosition( )->GetRenderInSceneScreenPosition( viewport, zsort );
			return ret + matrix.GetTranslationVector( );
		}
	}
	break;
	case 2:
	{
		Get3DInUIScreenPositionHelper helper;
		return helper.GetPosition( this, viewport );
	}
	break;
	}

	return GetWorldTransform( ).GetTranslationVector( );
}

template< typename Type >
Matrix3 TGUIObject< Type >::GetWorldTransform( ) const
{
	if ( this->mParentObject != _null )
		return this->GetRelativeTransform( ) * this->mParentObject->GetChildWorldTransform( );	
	else
		return this->GetRelativeTransform( );
}

template< typename Type >
Matrix3 TGUIObject< Type >::GetChildWorldTransform( ) const
{
	if ( this->mParentObject != _null )
		return this->GetChildRelativeTransform( ) * this->mParentObject->GetChildWorldTransform( );	
	else
		return this->GetChildRelativeTransform( );
}

template< typename Type >
Matrix3 TGUIObject< Type >::GetRelativeTransform( ) const
{
	return GetComponentPosition( )->GetTransform( );
}

template< typename Type >
Matrix3 TGUIObject< Type >::GetChildRelativeTransform( ) const
{
	return GetComponentPosition( )->GetTransform( );
}

template< typename Type >
_void TGUIObject< Type >::GetWorldTransformsFromRoot( Matrix3Array& transforms ) const
{
	if ( this->mParentObject != _null )
	{
		this->mParentObject->GetChildWorldTransformsFromRoot( transforms );

		for ( _dword i = 0; i < transforms.Number( ); i ++ )
			transforms[i] = this->GetRelativeTransform( ) * transforms[i];
	}
	else
	{
		transforms.Append( this->GetRelativeTransform( ) );
	}
}

template< typename Type >
_void TGUIObject< Type >::GetChildWorldTransformsFromRoot( Matrix3Array& transforms ) const
{
	if ( this->mParentObject != _null )
	{
		this->mParentObject->GetChildWorldTransformsFromRoot( transforms );

		for ( _dword i = 0; i < transforms.Number( ); i ++ )
			transforms[i] = this->GetChildRelativeTransform( ) * transforms[i];
	}
	else
	{
		transforms.Append( this->GetRelativeTransform( ) );
	}
}

template< typename Type >
Color TGUIObject< Type >::MixColor( const Color& color ) const
{
	Color mixed_color = this->GetComponentColor( )->GetColor( );
	if ( mixed_color != Color::cWhite )
		mixed_color *= color;
	else
		mixed_color = color;

	return mixed_color;
}

template< typename Type >
_void TGUIObject< Type >::ResetControlAnimationInfo( _ubool deep )
{
	this->GetComponentAnimation( )->Stop( );
	this->GetComponentColor( )->SetColor( Color::cWhite );
	this->GetComponentPosition( )->SetTransform2D( Transform2D::cZero );
	this->GetComponentPosition( )->SetOffsetZ( 0.0f );
	this->GetComponentPosition( )->SetAnimationXYRotation( 0.0f, 0.0f );
}

}