//! @file     GUIModule.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGUI.h"

//----------------------------------------------------------------------------
// GUIModule Implementation
//----------------------------------------------------------------------------

GUIModule::GUIModule( ) : BaseClass( L"GUI", Version( GUI_FILEVER ) )
	, mCreateModelIndex( 0 )
{
	mEnableStretch			= _false;

	mIsUpdateSize			= _false;
	mInitialSize			= Vector2::cOrigin;
	mLastScreenSize			= Vector2::cOrigin;

	mBaseRegion				= RectF::cNull;
	mRegion					= RectF::cNull;

	mRootGUIApplication		= _null;

	mInputRecorder			= _null;

	mGUIProcessor			= &NullGUI::GetInstance( ).GetGUIProcessor( );
	mGUIApplicationNotifier	= &NullGUI::GetInstance( ).GetGUIApplicationNotifier( );

	mAnimationRefCount		= 0;

	m3DUICamera				= Camera( Vector3::cOrigin, -Vector3::cZAxis, Vector3::cYAxis );
	m3DUIViewMatrix			= Matrix4::CreateLookAtRH( m3DUICamera.mPosition, -m3DUICamera.mLook, -m3DUICamera.mUp );
	m3DUIRenderMatrix		= Matrix3::cIdentity;
	m3DUIOffsetMatrix		= Matrix4::cIdentity;
}

GUIModule::~GUIModule( )
{
	Finalize( );

	GetModuleManager( )->UnregisterModule( this );
}

_void GUIModule::UpdateRegion( const Matrix3& transform )
{
	Vector2 lt( mBaseRegion.l, mBaseRegion.t );
	Vector2 rb( mBaseRegion.r, mBaseRegion.b );

	lt *= transform;
	rb *= transform;

	mRegion.l = lt.x;
	mRegion.t = lt.y;
	mRegion.r = rb.x;
	mRegion.b = rb.y;
}

IGUIApplication* GUIModule::GetTopReceiveModal( ) const
{
	for ( _long i = mModalGUIApplications.Number( ) - 1; i >= 0; -- i )
	{
		if ( mModalGUIApplications[i].HasFlags( ModalApplicationInfo::_FLAG_RECEIVE_MESSAGE ) )
			return mModalGUIApplications[i].mApplication.GetPtr( );
	}

	return _null;
}

_void GUIModule::UpdateModals( )
{
	if ( mRootGUIApplication->GetComponentState( )->IsPausing( ) )
		return;

	for ( _dword i = 0; i < mModalGUIApplications.Number( ); ++ i )
	{
		ModalApplicationInfo& model_info = mModalGUIApplications[i];

		// It's popping by animation now
		if ( model_info.HasFlags( ModalApplicationInfo::_FLAG_POPPING_BY_ANIMATION ) )
		{
			IGUIApplication* modal = mModalGUIApplications[i].mApplication;
			EGE_ASSERT( modal != _null );

			if ( modal->GetComponentAnimation( )->GetAniStatus( ) != _ANIMATION_STATUS_STOPPED )
				continue;

			// Remove it
			if ( HideModal( i ) )
				i -= 1;
		}
	}
}

_void GUIModule::RenderModals( IObject* viewport, const Matrix3& transform, const Color& color, const RectF& clip_rect )
{
	if ( mModalGUIApplications.Number( ) == 0 )
		return;

	// Mix color and get world transform
	Color	mixed_color					= mRootGUIApplication->MixColor( color );
	Matrix3 world_transform_forchild	= mRootGUIApplication->GetChildRelativeTransform( ) * transform;

	// Get the clip rect
	RectF fixed_clip_rect;
	if ( mRootGUIApplication->GetComponentState( )->GetAttributes( ).HasFlags( _GUI_ATTRIBUTE_CLIPCHILD ) )
	{
		Matrix3 world_transform	= mRootGUIApplication->GetRelativeTransform( ) * transform;
		fixed_clip_rect = mRootGUIApplication->GetIntersectRect( clip_rect, world_transform );
	}
	else
	{
		fixed_clip_rect = clip_rect;
	}

	// Render modal GUI applications
	for ( _dword i = 0; i < mModalGUIApplications.Number( ); ++ i )
	{
		IGUIApplication* modal = mModalGUIApplications[i].mApplication;
		EGE_ASSERT( modal != _null );

		IGUIComponentState* modal_state = modal->GetComponentState( );
		EGE_ASSERT( modal_state != _null );

		// Show it always
		if ( modal->IsShow( ) == _false )
			modal->Show( _true );

		// Render it
		modal_state->SetModal( _false );
		modal->Render( viewport, world_transform_forchild, mixed_color, fixed_clip_rect, _false, _false );
		modal_state->SetModal( _true );
	}
}

_void GUIModule::PushModal( IGUIApplication* application, _ubool receive_message )
{
	application->GetComponentState( )->SetModal( _true );
	mModalGUIApplications.Append( ModalApplicationInfo( application, receive_message ) );
	application->Show( _true );
}

_void GUIModule::GetClickableGUIObjectsFromApp( IGUIObject* object, IGUIApplication* owner, IGUIObjectRefArray& objects ) const
{
	if ( object->GetComponentState( )->IsVisiable( ) == _false )
		return;

	if ( object->IsHandleEvent( _GUI_EVENT_CLICK ) )
	{
		if ( owner != _null )
		{
			if ( object->IsChildOfIt( owner ) )
				objects.Append( object );
		}
		else
		{
			objects.Append( object );
		}
	}

	for ( IGUIObject* child_object = object->FirstChildObject( ); child_object != _null; child_object = child_object->NextObject( ) )
		GetClickableGUIObjectsFromApp( child_object, owner, objects );
}

_ubool GUIModule::TestClickableGUIObject( IGUIApplication* gui_application, const Matrix3& transform, const IGUIObject* object ) const
{
	Vector2 position = object->GetWorldTransform( ).GetTranslationVector( );

	IGUIObject* hit_object = gui_application->TestPoint( position, position, transform, FlagsObject( _GUI_TESTPOINT_CLICKABLE ), _null );
	if ( hit_object != object )
		return _false;

	return _true;
}

_void GUIModule::TestClickableGUIObjects( IGUIApplication* gui_application, const Matrix3& transform, IGUIObjectRefArray& objects ) const
{
	for ( _dword i = 0; i < objects.Number( ); i ++ )
	{
		IGUIObject* object = objects[i];
		EGE_ASSERT( object != _null );

		if ( TestClickableGUIObject( gui_application, transform, object ) == _false )
			objects.RemoveByIndex( i -- );
	}
}

_ubool GUIModule::Initialize( _ubool enable_stretch, const Vector2& size )
{
	WLOG_TRACE( L"Create GUI module ..." );

	gGUIResourceManager	= &mGUIResourceManager;

	mInputRecorder = GetInterfaceFactory( )->CreateInputRecorder( );
	if ( mInputRecorder.IsNull( ) )
		return _false;

	mEnableStretch		= enable_stretch;
	mRootGUIApplication = new GUIApplication( );

	if ( size != Vector2::cOrigin )
	{
		mLastScreenSize = size;
		SetSize( size );
	}

	WLOG_TRACE( L"Create GUI module DONE" );

	return _true;
}

_void GUIModule::Finalize( )
{
	WLOG_TRACE( L"Release GUI module ..." );

	mModalGUIApplications.Clear( _true );
	EGE_RELEASE( mRootGUIApplication );

	WLOG_TRACE( L"Release GUI module DONE" );

	// Clear global modules
	gGUIResourceManager	= &NullGUI::GetInstance( ).GetGUIResourceManager( );
	gGUIModule			= &NullGUI::GetInstance( ).GetGUIModule( );
}

_void GUIModule::Tick( _time_t tick, _dword elapse )
{
	// Update GUI scene size
	if ( mIsUpdateSize )
	{
		mIsUpdateSize = _false;

		SetSize( mInitialSize );
		WLOG_TRACE_2( L"Update GUI client size (%dx%d) by update screen size", (_dword) mLastScreenSize.x, (_dword) mLastScreenSize.y );
	}

	// Update all GUI applications from root
	if ( mRootGUIApplication != _null )
	{
		mRootGUIApplication->Tick( tick, elapse );

		UpdateModals( );
	}	
}

_void GUIModule::HandleMessage( MessageBase& message )
{
	if ( mRootGUIApplication == _null )
		return;

	switch ( message.mMsgID )
	{
		// The client size changed
		case _MESSAGE_CLIENT_SIZE_CHANGED:
		{
			HandleClientSizeChangedMsg( HandledMessage< MessageClientSizeChanged >( message ) );
		}
		break;

		// The key is up
		case _MESSAGE_KEY_UP:
		{
			HandleKeyUpMsg( HandledMessage< MessageKeyUp >( message ) );
		}
		break;

		// The key is down
		case _MESSAGE_KEY_DOWN:
		{
			HandleKeyDownMsg( HandledMessage< MessageKeyDown >( message ) );
		}
		break;

		// The mouse is moving
		case _MESSAGE_MOUSE_MOVE:
		{
			HandleMouseMoveMsg( HandledMessage< MessageMouseMove >( message ) );
		}
		break;

		// The mouse button is up
		case _MESSAGE_MOUSE_BUTTON_UP:
		{
			HandleMouseButtonUpMsg( HandledMessage< MessageMouseButtonUp >( message ) );
		}
		break;

		// The mouse button is down
		case _MESSAGE_MOUSE_BUTTON_DOWN:
		{
			HandleMouseButtonDownMsg( HandledMessage< MessageMouseButtonDown >( message ) );
		}
		break;

		// The mouse button double click
		case _MESSAGE_MOUSE_BUTTON_DOUBLE_CLICK:
		{
			HandleMouseButtonDoubleClickMsg( HandledMessage< MessageMouseButtonDoubleClick >( message ) );
		}
		break;

		// The mouse wheel scrolling
		case _MESSAGE_MOUSE_WHEEL:
		{
			HandleMouseWheelMsg( HandledMessage< MessageMouseWheel >( message ) );
		}
		break;

		// The touch pad message
		case _MESSAGE_TOUCH:
		{
			HandleTouchMsg( HandledMessage< MessageTouch >( message ) );
		}
		break;

		// Enter foreground
		case _MESSAGE_ENTER_FOREGROUND:
		{
			HandleEnterForegroundMsg( HandledMessage< MessageEnterForeground >( message ) );
		}
		break;

		// Enter background
		case _MESSAGE_ENTER_BACKGROUND:
		{
			HandleEnterBackgroundMsg( HandledMessage< MessageEnterBackground >( message ) );
		}
		break;

		default:
			break;
	}
}

_void GUIModule::SetProcessor( IGUIProcessor* processor )
{
	if ( processor == _null )
		mGUIProcessor = &NullGUI::GetInstance( ).GetGUIProcessor( );
	else
		mGUIProcessor = processor;
}

IGUIProcessor* GUIModule::GetProcessor( )
{
	return mGUIProcessor;
}

_void GUIModule::SetApplicationNotifier( IGUIApplicationNotifier* notifier )
{
	if ( notifier == _null )
		mGUIApplicationNotifier = &NullGUI::GetInstance( ).GetGUIApplicationNotifier( );
	else
		mGUIApplicationNotifier = notifier;
}

IGUIApplicationNotifier* GUIModule::GetApplicationNotifier( )
{
	return mGUIApplicationNotifier;
}

IGUIApplication* GUIModule::GetRootApplication( )
{
	return mRootGUIApplication;
}

IInputRecorder* GUIModule::GetInputRecorder( )
{
	return mInputRecorder;
}

_void GUIModule::ReleaseAllInput( )
{
	const Array< IInputRecordTraceRef >& inputtrace_array = mInputRecorder->GetValidRecordTraces( );
	for ( _dword i = 0; i < inputtrace_array.Number( ); ++ i )
	{
		IInputRecordTrace* trace = inputtrace_array[i].GetPtr( );
		if ( trace == _null )
			continue;

		const InputRecordInfoArray& inputrecord_array = trace->GetInputRecords( );
		if ( inputrecord_array.Number( ) == 0 )
			continue;
		
		const InputRecordInfo& last_input_info = inputrecord_array.GetTailElement( );

		GUIEventTouchEnd gui_event;
		gui_event.mLocation		= last_input_info.GetPosition( );
		gui_event.mTimestamp	= last_input_info.mTimeStamp;
		gui_event.mTouchId		= trace->GetChannelID( );

		// Get the record and let the capture control handle this message
		IGUIObject* gui_object = trace->GetObject( ).cast_static< IGUIObject >( );
		if ( gui_object != _null )
		{
			gui_object->HandleEvent( gui_event, FlagsObject( _GUI_MESSAGE_DELIVER_PARENT ) );
		}
		else
		{
			// Let the user to handle it
			GetGUIModule( )->GetApplicationNotifier( )->OnHandleEvent( mRootGUIApplication, gui_event, FlagsObject( ) );
		}
	}
	
	mInputRecorder->ClearInput( );
}

_void GUIModule::EnableStretch( _ubool enable )
{
	mEnableStretch = enable;
}

_ubool GUIModule::IsStretch( ) const
{
	return mEnableStretch;
}

_void GUIModule::SetSize( const Vector2& size )
{
	// Set the initial size
	mInitialSize = size;

	// Set the size and position of root GUI application
	if ( mEnableStretch )
	{
		Ratio ratio( mInitialSize.x, mInitialSize.y );
		ratio.UpdateSize( mLastScreenSize.x, mLastScreenSize.y );

		Vector2 new_size = Vector2::cOrigin;
		if ( ratio.mScale != 0.0f )
		{
			new_size.x = mLastScreenSize.x / ratio.mScale;
			new_size.y = mLastScreenSize.y / ratio.mScale;
		}

		mRootGUIApplication->GetComponentPosition( )->SetScale( Vector2( ratio.mScale, ratio.mScale ) );
		mRootGUIApplication->GetComponentPosition( )->SetLogicSizeH( new_size.x );
		mRootGUIApplication->GetComponentPosition( )->SetLogicSizeV( new_size.y );
		mRootGUIApplication->GetComponentPosition( )->SetLogicPositionH( mLastScreenSize.x * 0.5f );
		mRootGUIApplication->GetComponentPosition( )->SetLogicPositionV( mLastScreenSize.y * 0.5f );

		// Update region
		mBaseRegion = RectF( ).InitWithSize( 0, 0, mLastScreenSize.x, mLastScreenSize.y );
	}
	else
	{
		mRootGUIApplication->GetComponentPosition( )->SetLogicSizeH( size.x );
		mRootGUIApplication->GetComponentPosition( )->SetLogicSizeV( size.y );
		mRootGUIApplication->GetComponentPosition( )->SetLogicPositionH( size.x * 0.5f );
		mRootGUIApplication->GetComponentPosition( )->SetLogicPositionV( size.y * 0.5f );

		// Update region
		mBaseRegion = RectF( ).InitWithSize( 0, 0, size.x, size.y );
	}

	GUIEventSceneResize gui_event;
	RootAppHandleGUIEvent( gui_event, FlagsObject( _GUI_MESSAGE_DELIVER_CHILD ) );
}

const Vector2& GUIModule::GetSize( ) const
{
	return mInitialSize;
}

_void GUIModule::SetLastScreenSize( const Vector2& size )
{
	mLastScreenSize = size;

	SetSize( mInitialSize );
	WLOG_TRACE_2( L"Update GUI client size (%dx%d) by update last screen size", (_dword) mLastScreenSize.x, (_dword) mLastScreenSize.y );
}

const Vector2& GUIModule::GetLastScreenSize( ) const
{
	return mLastScreenSize;
}

_void GUIModule::SetScaleUISize( const Vector2& gui_size, const Vector2& screen_size )
{
	if ( mInitialSize == gui_size && mLastScreenSize == screen_size )
		return;

	mInitialSize	= gui_size;
	mLastScreenSize = screen_size;

	_float scale_x = 1.0f;
	_float scale_y = 1.0f;
	if ( mLastScreenSize.x != 0.0f )
		scale_x = mLastScreenSize.x / mInitialSize.x;
	if ( mLastScreenSize.y != 0.0f )
		scale_y = mLastScreenSize.y / mInitialSize.y;

	mRootGUIApplication->GetComponentPosition( )->SetScale( Vector2( scale_x, scale_y ) );

	mRootGUIApplication->GetComponentPosition( )->SetLogicSizeH( mInitialSize.x );
	mRootGUIApplication->GetComponentPosition( )->SetLogicSizeV( mInitialSize.y );
	mRootGUIApplication->GetComponentPosition( )->SetLogicPositionH( mLastScreenSize.x * 0.5f );
	mRootGUIApplication->GetComponentPosition( )->SetLogicPositionV( mLastScreenSize.y * 0.5f );

	// Update region
	mBaseRegion = RectF( ).InitWithSize( 0, 0, mLastScreenSize.x, mLastScreenSize.y );

	GUIEventSceneResize gui_event;
	RootAppHandleGUIEvent( gui_event, FlagsObject( _GUI_MESSAGE_DELIVER_CHILD ) );
}

const RectF& GUIModule::GetRegionF( ) const
{
	return mRegion;
}

_void GUIModule::AddDelayRenderGUIObject( IGUIObject* object, const Matrix3& transform, const Color& color, const RectF& clip_rect )
{
	mGUIRenderer.AddDelayRenderGUIObject( object, transform, color, clip_rect );
}

_void GUIModule::AddDelayRenderGUIComponent( IGUIComponent* object, const Matrix3& transform, const Color& color, const RectF& clip_rect )
{
	mGUIRenderer.AddDelayRenderGUIComponent( object, transform, color, clip_rect );
}

_void GUIModule::AddPreRenderInSceneGUIObject( IGUIObject* object, const Matrix3& transform, _float zsort )
{
	mGUIRenderer.AddPreRenderInSceneGUIObject( object, transform, zsort );
}

_void GUIModule::AddPreRenderInSceneGUIObject( IGUIObject* object, const Matrix4& transform, _float zsort )
{
	mGUIRenderer.AddPreRenderInSceneGUIObject( object, transform, zsort );
}

_void GUIModule::Render( IObject* viewport )
{
	Render( viewport, Vector2::cOrigin, Vector2::cIdentity, Color::cWhite );
}

_void GUIModule::Render( IObject* viewport, const Vector2& pos, const Vector2& scale, const Color& color )
{
	m3DUIRenderInfoStack.Clear( );

	Matrix3 transform( pos, scale, 0.0f );

	Update3DInfo( viewport, transform );
	UpdateRegion( transform );

	mGUIRenderer.RenderPreObject( viewport );

	Vector2 viewport_size = mGUIProcessor->OnGetViewportSize( viewport );
	RectF clip_rect( 0.0f, 0.0f, viewport_size.x, viewport_size.y );

	//IGUIComponentPosition* root_position_component = mRootGUIApplication->GetComponentPosition( );
	//Vector2 root_pos	= root_position_component->GetLogicPosition( );
	//Vector2 root_size	= (root_position_component->GetLogicSize( ) / 2.0f) * root_position_component->GetScale( );

	//RectF clip_rect = mRegion; 
	//clip_rect.l += root_pos.x - root_size.x;
	//clip_rect.r += root_pos.x - root_size.x;
	//clip_rect.t += root_pos.y - root_size.y;
	//clip_rect.b += root_pos.y - root_size.y;

	mRootGUIApplication->Render( viewport, transform, color, clip_rect, _false, _false );

	RenderModals( viewport, transform, color, clip_rect );

	mGUIRenderer.RenderDelayObject( viewport );
}

IGUIApplication* GUIModule::CreateTempModalUI( WStringPtr app_name )
{
	IGUIObject* it = mRootGUIApplication->SearchControlByName( app_name, _false, _false );
	if ( it == _null )
		return _null;

	return CreateTempModalUI( static_cast<IGUIApplication*>( it ) );
}

IGUIApplication* GUIModule::CreateTempModalUI( IGUIApplication* template_ui )
{
	if ( template_ui == _null )
		return _null;

	WString res_name = template_ui->GetResName( ) + L"_TEMPLATE_" + WString( ).FromValue( mCreateModelIndex );
	IGUIApplication* ui = (IGUIApplication*)GetGUIResourceManager( )->CreateGUIObject( template_ui, L"", mRootGUIApplication, _true );
	ui->SetResName( res_name );
	ui->GetComponentState( )->SetTempModal( _true );
	mCreateModelIndex += 1;
	return ui;
}

IGUIApplication* GUIModule::ShowModal( IGUIApplication* application, _ubool receive_message, _ubool create_new_ui )
{
	if ( application == _null )
		return _null;

	IGUIApplication* ui = application;
	if ( create_new_ui )
	{
		ui = CreateTempModalUI( ui );
	}
	else
	{
		if ( ui->ParentObject( ) != mRootGUIApplication )
			return _null;
	}	

	PushModal( ui, receive_message );

	return ui;
}

IGUIApplication* GUIModule::ShowModal( WStringPtr app_name, _ubool receive_message, _ubool create_new_ui )
{
	IGUIObject* it = mRootGUIApplication->SearchControlByName( app_name, _false, _false );
	if ( it == _null )
		return _null;

	IGUIApplication* modal = static_cast<IGUIApplication*>( it );
	if ( create_new_ui )
		modal = CreateTempModalUI( modal );

	PushModal( modal, receive_message );

	return modal;
}

IGUIApplication* GUIModule::ShowModalWithAnimation( WStringPtr app_name, WStringPtr ani_name, _ubool pause_input, _ubool receive_message, _ubool create_new_ui )
{
	IGUIObject* it = mRootGUIApplication->SearchControlByName( app_name, _false, _false );
	if ( it == _null )
		return _null;

	return ShowModalWithAnimation( static_cast<IGUIApplication*>( it ), ani_name, pause_input, receive_message, create_new_ui );
}

IGUIApplication* GUIModule::ShowModalWithAnimation( IGUIApplication* application, WStringPtr ani_name, _ubool pause_input, _ubool receive_message, _ubool create_new_ui )
{
	if ( application == _null )
		return _null;

	IGUIApplication* modal = application;
	if ( create_new_ui )
		modal = CreateTempModalUI( modal );

	PushModal( modal, receive_message );
	modal->GetComponentAnimation( )->PlayAnimation( 0, ani_name, pause_input, _false );

	return modal;
}

_ubool GUIModule::HideModal( _dword index )
{
	if ( index >= mModalGUIApplications.Number( ) )
		return _false;

	IGUIApplication* ui = mModalGUIApplications[index].mApplication;
	mModalGUIApplications.RemoveByIndex( index );

	if ( ui != _null )
	{
		ui->Show( _false );
		if ( ui->GetComponentState( )->IsTempModal() )
		{
			mRootGUIApplication->RemoveChildObject( ui );
			// Release it
			EGE_RELEASE( ui );
		}
	}

	return _true;
}

_ubool GUIModule::HideModalWithAnimation( _dword index, WStringPtr ani_name )
{
	if ( index >= mModalGUIApplications.Number( ) )
		return _false;

	// Get the top model application info
	ModalApplicationInfo& ui_info = mModalGUIApplications[index];

	// Get the top model application
	IGUIApplication* ui = ui_info.mApplication;

	// Play animation
	ui->GetComponentAnimation( )->PlayAnimation( 0, ani_name, _true, _false );

	// Check whether we can pop it with animation
	if ( ui->GetComponentAnimation( )->GetAniStatus( ) == _ANIMATION_STATUS_PLAYING )
	{
		// Popping
		ui_info.EnableFlags( ModalApplicationInfo::_FLAG_POPPING_BY_ANIMATION, _true );
	}
	else
	{
		// Remove it now
		return HideModal( index );
	}
	return _false;
}

_void GUIModule::HideModal( )
{
	if ( mModalGUIApplications.Number( ) == 0 )
		return;
	
	HideModal( mModalGUIApplications.Number( ) - 1 );
}

_void GUIModule::HideModal( WStringPtr app_name )
{
	for ( _dword i = 0; i < mModalGUIApplications.Number( ); ++ i )
	{
		if ( mModalGUIApplications[i].mApplication->GetResName( ) != app_name )
			continue;

		if ( HideModal( i ) )
			i -= 1;
	}
}

_void GUIModule::HideAllModal( )
{
	for ( _dword i = 0; i < mModalGUIApplications.Number( ); ++ i )
	{
		if ( HideModal( i ) )
			i -= 1;
	}
}

_void GUIModule::HideModal( IGUIApplication* gui_app )
{
	for ( _dword i = 0; i < mModalGUIApplications.Number( ); ++ i )
	{
		if ( mModalGUIApplications[i].mApplication.GetPtr( ) != gui_app )
			continue;

		if( HideModal( i ) )
			i -= 1;
	}
}

_void GUIModule::HideModalWithAnimation( WStringPtr ani_name )
{
	if ( mModalGUIApplications.Number( ) == 0 )
		return;

	HideModalWithAnimation( mModalGUIApplications.Number( ) - 1, ani_name );
}

_void GUIModule::HideModalWithAnimation( WStringPtr app_name, WStringPtr ani_name )
{
	for ( _dword i = 0; i < mModalGUIApplications.Number( ); ++ i )
	{
		if ( mModalGUIApplications[i].mApplication->GetResName( ) != app_name )
			continue;

		if ( HideModalWithAnimation( i, ani_name ) )
			i -= 1;
	}
}

_void GUIModule::HideModalWithAnimation( IGUIApplication* gui_app, WStringPtr ani_name )
{
	for ( _dword i = 0; i < mModalGUIApplications.Number( ); ++ i )
	{
		if ( mModalGUIApplications[i].mApplication.GetPtr( ) != gui_app )
			continue;

		if ( HideModalWithAnimation( i, ani_name ) )
			i -= 1;
	}
}

IGUIApplication* GUIModule::GetTopModal( ) const
{
	if ( mModalGUIApplications.Number( ) == 0 )
		return _null;

	return mModalGUIApplications.GetTailElement( ).mApplication.GetPtr( );
}

_void GUIModule::PauseAllModal( )
{
	for ( _dword i = 0; i < mModalGUIApplications.Number( ); ++ i )
		mModalGUIApplications[i].mApplication->GetComponentState( )->Pause( _true );
}

_void GUIModule::ResumeAllModal( )
{
	for ( _dword i = 0; i < mModalGUIApplications.Number( ); ++ i )
		mModalGUIApplications[i].mApplication->GetComponentState( )->Pause( _false );
}

_ubool GUIModule::IsShowingModal( ) const
{
	for ( _dword i = 0; i < mModalGUIApplications.Number( ); ++ i )
	{
		if ( !mModalGUIApplications[i].HasFlags( ModalApplicationInfo::_FLAG_POPPING_BY_ANIMATION ) )
			return _true;
	}

	return _false;
}

_ubool GUIModule::IsControlClickable( const IGUIObject* object ) const
{
	if ( object == _null )
		return _false;

	if ( object->GetComponentState( )->IsVisiable( ) == _false )
		return _false;

	if ( object->IsHandleEvent( _GUI_EVENT_CLICK ) == _false )
		return _false;

	if ( mInputRecorder->IsPausingInput( ) )
		return _false;

	// The testing result
	_ubool result = _false;

	// Get the top modal application
	IGUIApplicationRef modal_application = GetTopReceiveModal( );

	// Test all clickables by top modal application
	if ( modal_application.IsValid( ) )
	{
		// Get the modal GUI's state
		IGUIComponentState* modal_state = modal_application->GetComponentState( );
		EGE_ASSERT( modal_state != _null );

		// Build the world transform
		Matrix3 child_world_transform = mRootGUIApplication->GetChildWorldTransform( );

		modal_state->SetModal( _false );
		result = TestClickableGUIObject( modal_application, child_world_transform, object );
		modal_state->SetModal( _true );
	}
	else
	{
		result = TestClickableGUIObject( mRootGUIApplication, Matrix3::cIdentity, object );
	}

	return result;
}

_void GUIModule::GetClickableGUIObjects( IGUIObjectRefArray& objects )
{
	if ( mInputRecorder->IsPausingInput( ) )
		return;

	// Get the top modal application
	IGUIApplicationRef modal_application = GetTopReceiveModal( );

	// Get all clickable objects
	GetClickableGUIObjectsFromApp( mRootGUIApplication, modal_application, objects );

	// Test all clickable by top modal application
	if ( modal_application.IsValid( ) )
	{
		// Get the modal GUI's state
		IGUIComponentState* modal_state = modal_application->GetComponentState( );
		EGE_ASSERT( modal_state != _null );

		// Build the world transform
		Matrix3 child_world_transform = mRootGUIApplication->GetChildWorldTransform( );

		modal_state->SetModal( _false );
		TestClickableGUIObjects( modal_application, child_world_transform, objects );
		modal_state->SetModal( _true );
	}
	else
	{
		TestClickableGUIObjects( mRootGUIApplication, Matrix3::cIdentity, objects );
	}
}

_ubool GUIModule::IsAnimation( )
{
	return mAnimationRefCount != 0;
}

_dword GUIModule::StartAnimation( IGUIObject* gui_object )
{
#ifdef _DEBUG
	mAnimationGUIObjects.InsertAscending( gui_object );
#endif

	++ mAnimationRefCount;
	return mAnimationRefCount;
}

_dword GUIModule::EndAnimation( IGUIObject* gui_object )
{
#ifdef _DEBUG
	mAnimationGUIObjects.RemoveAscending( gui_object );
#endif

	if ( mAnimationRefCount == 0 )
		return mAnimationRefCount;

	-- mAnimationRefCount;
	return mAnimationRefCount;
}

const Camera& GUIModule::Get3DUICamera( ) const
{
	return m3DUICamera;
}

const Matrix3& GUIModule::Get3DUIRenderMatrix( ) const
{
	return m3DUIRenderMatrix;
}

const Matrix4& GUIModule::Get3DUIViewMatrix( ) const
{
	return m3DUIViewMatrix;
}

const Matrix4& GUIModule::Get3DUIOffsetMatrix( ) const
{
	return m3DUIOffsetMatrix;
}

_void GUIModule::Update3DInfo( IObject* viewport, const Matrix3& matrix )
{
	m3DUIRenderMatrix = matrix;

	Vector2 gui_size		= GetSize( );
	Vector2 viewport_size	= mGUIProcessor->OnGetViewportSize( viewport );
	Vector2 ui_scale( m3DUIRenderMatrix.m[0][0], m3DUIRenderMatrix.m[1][1] );
	Vector2 view_scale( viewport_size.x == 0.0f ? 0.0f : gui_size.x / viewport_size.x, viewport_size.y == 0.0f ? 0.0f : gui_size.y / viewport_size.y );

	Matrix3 render_rotation_matrix( 
		m3DUIRenderMatrix.m[0][0],	m3DUIRenderMatrix.m[0][1],	0.0f,
		m3DUIRenderMatrix.m[1][0],	m3DUIRenderMatrix.m[1][1],	0.0f,
		0.0f,						0.0f,					1.0f
		);
	Vector3 render_offset( m3DUIRenderMatrix.m[2][0] * 2.0f / gui_size.x, -m3DUIRenderMatrix.m[2][1] * 2.0f / gui_size.y,	0.0f );
	// 
	m3DUIOffsetMatrix = Matrix4( ).FromTranslationRotation( render_offset, render_rotation_matrix );
	m3DUIOffsetMatrix *= Matrix4( ).Translation( ui_scale.x, -ui_scale.y, 0.0f );
	m3DUIOffsetMatrix *= Matrix4( ).Scaling( view_scale.x, view_scale.y, 1.0f );
	m3DUIOffsetMatrix *= Matrix4( ).Translation( -1.0f, 1.0f, 0.0f );
}

_ubool GUIModule::GetLastRender3DInUIInfo( GUI3DInUIInfo& info )
{
	if ( m3DUIRenderInfoStack.Number( ) == 0 )
		return _false;

	info = m3DUIRenderInfoStack.GetTailElement( );
	return _true;
}

_void GUIModule::PushRender3DInUIInfo( const GUI3DInUIInfo& info )
{
	m3DUIRenderInfoStack.Append( info );
}

_void GUIModule::PopRender3DInUIInfo( )
{
	if ( m3DUIRenderInfoStack.Number( ) == 0 )
		return;

	m3DUIRenderInfoStack.RemoveByIndex( m3DUIRenderInfoStack.Number( ) - 1 );
}

_ubool GUIModule::GetLastTestPoint3DInUIInfo( GUI3DInUIInfo& info )
{
	if ( m3DUITestPointInfoStack.Number( ) == 0 )
		return _false;

	info = m3DUITestPointInfoStack.GetTailElement( );
	return _true;
}

_void GUIModule::PushTestPoint3DInUIInfo( const GUI3DInUIInfo& info )
{
	m3DUITestPointInfoStack.Append( info );
}

_void GUIModule::PopTestPoint3DInUIInfo( )
{
	if ( m3DUITestPointInfoStack.Number( ) == 0 )
		return;

	m3DUITestPointInfoStack.RemoveByIndex( m3DUITestPointInfoStack.Number( ) - 1 );
}

IGUIObjectRefArray GUIModule::FilterControl( const IGUIObjectRefArray& objects ) const
{
	IGUIObjectRefArray filtered_objects;

	for ( _dword i = 0; i < objects.Number( ); i ++ )
	{
		IGUIObject* gui_object = objects[i].GetPtr( );
		if ( gui_object->IsControl( ) )
			continue;

		filtered_objects.Append( gui_object );
	}

	return filtered_objects;
}

IGUIObjectRefArray GUIModule::FilterContainer( const IGUIObjectRefArray& objects ) const
{
	IGUIObjectRefArray filtered_objects;

	for ( _dword i = 0; i < objects.Number( ); i ++ )
	{
		IGUIObject* gui_object = objects[i].GetPtr( );
		if ( gui_object->IsContainer( ) )
			continue;

		filtered_objects.Append( gui_object );
	}

	return filtered_objects;
}

IGUIObjectRefArray GUIModule::FilterComponents( const IGUIObjectRefArray& objects, AStringPtr components ) const
{
	AStringArray components_list;
	StringFormatter::SplitString( components, components_list, "|", " \t" );
	components_list.SortAscending( );

	IGUIObjectRefArray filter_objects;
	for ( _dword i = 0; i < objects.Number( ); i ++ )
	{
		IGUIObject* gui_object = objects[i].GetPtr( );
		if ( gui_object == _null )
		{
			WLOG_ERROR_3( L"Filter (location: %d/%d) GUI components failed with '%s' filter", i, objects.Number( ), components.Str( ) );
			continue;
		}

		if ( gui_object->HasComponents( components_list ) )
			filter_objects.Append( gui_object );
	}

	return filter_objects;
}
