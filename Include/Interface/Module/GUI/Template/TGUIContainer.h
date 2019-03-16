//! @file     TGUIContainer.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TGUIContainer
//----------------------------------------------------------------------------

template< typename Type >
class TGUIContainer : public TGUIObject< Type >
{
protected:
	typedef TGUIObject< Type > GUIObjectBaseClass;

protected:
	//!	The child GUI object info (The layer number as key, sort it from low to high)
	struct ChildGUIObjectInfo
	{
		IGUIObject*	mGUIObject;

		//!	Use the layer number as key.
		operator _long( ) const
			{ return mGUIObject->GetLayerNumber( ); }

		ChildGUIObjectInfo( )
		{
			mGUIObject = _null;
		}
		ChildGUIObjectInfo( IGUIObject* gui_object )
		{
			mGUIObject = gui_object;
		}
	};
	typedef Array< ChildGUIObjectInfo, _long > ChildGUIObjectInfoArray;

protected:
	//!	The child GUI objects
	ChildGUIObjectInfoArray	mChildGUIObjects;

protected:
	//!	Render.
	_void RenderContainer( IObject* viewport, const Matrix3& transform, const Matrix3& world_transform, const Color& color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test);
	//!	Render self and all child controls.
	_void RenderSelfAndChildControls( IObject* viewport, const Matrix3& world_transform, const Matrix3& transform_for_child, const Color& color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test);

protected:
	TGUIContainer( );
	virtual ~TGUIContainer( );

// IObject Interface
public:
	virtual IObject*			CloneTo( ) const override;

	virtual _void				Tick( _time_t tick, _dword elapse ) override;

// IObjectTree Interface
public:
	virtual IObject*			CloneSelfTo( ) const override;

// IDynamicResObject Interface
public:
	virtual _void				UnloadResources( _ubool force, _ubool clear_cache ) override;
	virtual _void				ReloadResourcesInBackgroundThread( _ubool lock ) override;
	virtual _void				ReloadResourcesInMainThread( _ubool lock ) override;

	virtual _ubool				AreAllResourcesAvailable( ) const override;
	virtual DwordRange			GetResourcesLoadedProgression( ) const override;

	virtual _void				ImportResource( _dword res_type, WStringPtr res_name ) override;
	virtual _void				ExportResources( IDynamicResObject* cache_obj ) const override;

	virtual _void				LoadDelaySubResources( IDynamicResObject* object, ISerializableNode* node ) const override;

// ISerializable Interface
public:
	virtual _ubool				Import( ISerializableNode* node ) override;
	virtual _ubool				Export( ISerializableNode* node ) const override;

// IGUIComponentGroup Interface
public:
	virtual _void				Render( IObject* viewport, const Matrix3& transform, const Color& color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test ) override;
	virtual _void				RenderAfterChild( IObject* viewport, const Matrix3& transform, Color color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test ) override;
	virtual _ubool				HandleEvent( const EventBase& event, const FlagsObject& flags ) override;

// IGUIObject Interface
public:
	virtual _ubool 				IsControl( ) const override;
	virtual _ubool 				IsContainer( ) const override;

	virtual IGUIObject*			TestPoint( const Vector2& origin_position, const Vector2& position, const Matrix3& transform, const FlagsObject& flags, Vector2* relative_position ) override;
	virtual IGUIObjectRefArray	TestPointByReturnList( const Vector2& origin_position, const Vector2& position, const Matrix3& transform, const FlagsObject& flags ) override;
	virtual IGUIObject*			GetIntersectObject( const RectF& region, const Matrix3& transform, const FlagsObject& flags ) override;
	virtual _void				ResetControlAnimationInfo( _ubool deep = _false ) override;

// IGUIContainer Interface
public:

	virtual _void				ClearAllChildObjects( ) override;  
	virtual _void				ClearAllChildObjectsExceptForFirst( ) override;
	virtual _void				ClearAllChildObjectsExceptFor( IGUIObject* gui_object ) override;

	virtual IGUIObjectRefArray	GetChildObjects( _ubool recursive ) override;

	virtual IGUIObject*			SearchControlByPath( WStringPtr path, _ubool ignorecase ) override;
	virtual IGUIObject*			SearchControlByName( WStringPtr name, _ubool ignorecase ) override;
	virtual IGUIObject*			SearchControlByName( WStringPtr name, _ubool recursive, _ubool ignorecase ) override;
	virtual	IGUIObject*			LocateAtChildAppAndSearchByName( WStringPtr child_app, WStringPtr control_name ) override;

	virtual _ubool				RemoveGUIObjectByName( WStringPtr name, _ubool recursive, _ubool ignorecase ) override;

	virtual IGUIObject*			GetCheckedChildObject( ) override;
	virtual IGUIObjectRefArray	GetCheckedChildObjects( ) override;
};

//----------------------------------------------------------------------------
// TGUIContainer Implementation
//----------------------------------------------------------------------------

template< typename Type >
TGUIContainer< Type >::TGUIContainer( )
{
}

template< typename Type >
TGUIContainer< Type >::~TGUIContainer( )
{
}

template< typename Type >
_void TGUIContainer< Type >::RenderContainer( IObject* viewport, const Matrix3& transform, const Matrix3& world_transform, const Color& color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test)
{
	// Test the root application region
	if ( this->IsApplication( ) == _false && !skip_region_test )
	{
		if ( this->mGUIComponentGroup->RegionInControl( clip_rect, world_transform ) == _false )
			return;
	}

	// Get the attributes
	const FlagsObject& attributes = this->mGUIComponentGroup->GetComponentState( )->GetAttributes( );

	// Get the clip flags
	_ubool clip_child = attributes.HasFlags( _GUI_ATTRIBUTE_CLIPCHILD );
	_ubool clip_self = !attributes.HasFlags( _GUI_ATTRIBUTE_DONT_CLIPSELF );

	RectF self_clip_rect = clip_rect;
	if ( clip_child || in_clip_state )
		self_clip_rect = this->GetIntersectRect( clip_rect, world_transform );

	if ( !clip_self )
		clip_self = in_clip_state && self_clip_rect == clip_rect;

	if ( clip_child && clip_self && self_clip_rect == RectF::cNull )
		return;

	// Get the mix color and transform for child
	Matrix3 world_transform_for_child = this->GetChildRelativeTransform( ) * transform;

	if ( clip_child )
	{
		if ( clip_self )
		{
			GetGUIModule( )->GetProcessor( )->OnPushOverlayScissorRect( viewport, self_clip_rect );
			{
				RenderSelfAndChildControls( viewport, world_transform, world_transform_for_child, color, self_clip_rect, _true, skip_region_test );
			}
			GetGUIModule( )->GetProcessor( )->OnPopOverlayScissorRect( viewport );
		}
		else
		{
			// Get the hooker
			IGUIComponentEventHooker* hooker = this->GetComponentEventHooker( );
			EGE_ASSERT( hooker != _null );

			// Begin to render
			hooker->InvokeBeginRenderFunc( world_transform, color, clip_rect );
			{
				if ( in_clip_state )
					GetGUIModule( )->GetProcessor( )->OnPushOverlayScissorRect( viewport, clip_rect );

				this->mGUIComponentGroup->Render( viewport, world_transform, color, clip_rect, in_clip_state, skip_region_test );

				if ( in_clip_state )
					GetGUIModule( )->GetProcessor( )->OnPopOverlayScissorRect( viewport );

				if ( self_clip_rect != RectF::cNull )
				{
					GetGUIModule( )->GetProcessor( )->OnPushOverlayScissorRect( viewport, self_clip_rect );
					{
						// Render all children
						for ( IGUIObject* child_object = this->FirstChildObject( ); child_object != _null; child_object = child_object->NextObject( ) )
							child_object->Render( viewport, world_transform_for_child, color, self_clip_rect, _true, skip_region_test);
					}
					GetGUIModule( )->GetProcessor( )->OnPopOverlayScissorRect( viewport );
				}

				// render after child component
				{
					if (in_clip_state)
						GetGUIModule()->GetProcessor()->OnPushOverlayScissorRect(viewport, clip_rect);

					this->mGUIComponentGroup->RenderAfterChild(viewport, world_transform, color, clip_rect, in_clip_state, skip_region_test);

					if (in_clip_state)
						GetGUIModule()->GetProcessor()->OnPopOverlayScissorRect(viewport);
				}
				
			}
			hooker->InvokeEndRenderFunc( world_transform, color );
		}
	}
	else
	{
		RenderSelfAndChildControls( viewport, world_transform, world_transform_for_child, color, self_clip_rect, _false, skip_region_test);
	}
}

template< typename Type >
_void TGUIContainer< Type >::RenderSelfAndChildControls( IObject* viewport, const Matrix3& world_transform, const Matrix3& transform_for_child, const Color& color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test)
{
	// Get the hooker
	IGUIComponentEventHooker* hooker = this->GetComponentEventHooker( );
	EGE_ASSERT( hooker != _null );

	// Begin to render
	hooker->InvokeBeginRenderFunc( world_transform, color, clip_rect );
	{
		this->mGUIComponentGroup->Render( viewport, world_transform, color, clip_rect, in_clip_state, skip_region_test );

		// Render all children
		for ( IGUIObject* child_object = this->FirstChildObject( ); child_object != _null; child_object = child_object->NextObject( ) )
			child_object->Render( viewport, transform_for_child, color, clip_rect, in_clip_state, skip_region_test );

		this->mGUIComponentGroup->RenderAfterChild(viewport, world_transform, color, clip_rect, in_clip_state, skip_region_test);
	}
	hooker->InvokeEndRenderFunc( world_transform, color );
}

template< typename Type >
IObject* TGUIContainer< Type >::CloneTo( ) const
{
	IGUIObject* gui_object = (IGUIObject*) CloneSelfTo( );
	if ( gui_object == _null )
		return _null;

	for ( IGUIObject* child_gui_object = this->mFirstChildObject; child_gui_object != _null; child_gui_object = child_gui_object->NextObject( ) )
	{
		IGUIObject* cloned_child_gui_object = (IGUIObject*) child_gui_object->CloneTo( );
		if ( cloned_child_gui_object == _null )
			return _null;

		gui_object->InsertChildObject( cloned_child_gui_object );
	}

	return gui_object;
}

template< typename Type >
_void TGUIContainer< Type >::Tick( _time_t tick, _dword elapse )
{
	// It's pausing
	if ( this->mGUIComponentGroup->GetComponentState( )->GetStatesEx( ).HasFlags( _GUI_STATE_EX_PAUSING ) )
		return;

	GUIObjectBaseClass::Tick( tick, elapse );

	// Update all children
	for ( IGUIObject* child_object = this->FirstChildObject( ); child_object != _null; child_object = child_object->NextObject( ) )
		child_object->Tick( tick, elapse );
}

template< typename Type >
IObject* TGUIContainer< Type >::CloneSelfTo( ) const
{
	return GUIObjectBaseClass::CloneSelfTo( );
}

template< typename Type >
_void TGUIContainer< Type >::UnloadResources( _ubool force, _ubool clear_cache )
{
	GUIObjectBaseClass::UnloadResources( force, clear_cache );

	for ( IGUIObject* child = this->FirstChildObject( ); child != _null; child = child->NextObject( ) )
		child->UnloadResources( force, clear_cache );
}

template< typename Type >
_void TGUIContainer< Type >::ReloadResourcesInBackgroundThread( _ubool lock )
{
	GUIObjectBaseClass::ReloadResourcesInBackgroundThread( lock );

	for ( IGUIObject* child = this->FirstChildObject( ); child != _null; child = child->NextObject( ) )
		child->ReloadResourcesInBackgroundThread( lock );
}

template< typename Type >
_void TGUIContainer< Type >::ReloadResourcesInMainThread( _ubool lock )
{
	GUIObjectBaseClass::ReloadResourcesInMainThread( lock );

	for ( IGUIObject* child = this->FirstChildObject( ); child != _null; child = child->NextObject( ) )
		child->ReloadResourcesInMainThread( lock );
}

template< typename Type >
_ubool TGUIContainer< Type >::AreAllResourcesAvailable( ) const
{
	if ( GUIObjectBaseClass::AreAllResourcesAvailable( ) == _false )
		return _false;

	for ( const IGUIObject* child = this->FirstChildObject( ); child != _null; child = child->NextObject( ) )
	{
		if ( child->AreAllResourcesAvailable( ) == _false )
			return _false;
	}

	return _true;
}

template< typename Type >
DwordRange TGUIContainer< Type >::GetResourcesLoadedProgression( ) const
{
	DwordRange progression = GUIObjectBaseClass::GetResourcesLoadedProgression( );

	for ( const IGUIObject* child = this->FirstChildObject( ); child != _null; child = child->NextObject( ) )
		progression += child->GetResourcesLoadedProgression( );

	return progression;
}

template< typename Type >
_void TGUIContainer< Type >::ImportResource( _dword res_type, WStringPtr res_name )
{
	GUIObjectBaseClass::ImportResource( res_type, res_name );
}

template< typename Type >
_void TGUIContainer< Type >::ExportResources( IDynamicResObject* cache_obj ) const
{
	GUIObjectBaseClass::ExportResources( cache_obj );

	for ( const IGUIObject* child = this->FirstChildObject( ); child != _null; child = child->NextObject( ) )
		child->ExportResources( cache_obj );
}

template< typename Type >
_ubool TGUIContainer< Type >::Import( ISerializableNode* node )
{
	// Clear all child objects
	ClearAllChildObjects( );

	if ( GUIObjectBaseClass::Import( node ) == _false )
		return _false;

	// Read the object info
	node->Read( L"name", this->mResName );

	// Import child controls
	ISerializableNodeRef child_node = node->GetChildNodeByName( L"Child" );
	if ( child_node.IsValid( ) )
	{
		ISerializableNodeRef it_node = child_node->GetFirstChildNode( );
		if ( it_node.IsValid( ) )
		{
			do 
			{
				IGUIObject* obj = (IGUIObject*) GetInterfaceFactory( )->CreateObject( it_node->GetNodeName( ) );
				this->InsertChildObject( obj );
				if ( this->GetComponentState( )->IsDelayLoad( ) )
					obj->GetComponentState( )->DelayLoad( _true );

				if ( obj->Import( it_node ) == _false )
				{
					this->RemoveChildObject( obj );
					return _false;
				}
			}
			while ( it_node->MoveNext( ) );
		}
	}

	return _true;
}

template< typename Type >
_ubool TGUIContainer< Type >::Export( ISerializableNode* node ) const
{
	if ( GUIObjectBaseClass::Export( node ) == _false )
		return _false;

	// Read the object info
	if ( node->Write( L"name", this->mResName ) == _false )
		return _false;

	ISerializableNodeRef child_root = node->InsertChildNode( L"Child", L"", _false );

	for ( const IGUIObject* child = this->FirstChildObject( ); child != _null; child = child->NextObject( ) )
	{
		WString child_name = child->GetClassTypeNameW( );
		ISerializableNodeRef child_node = child_root->InsertChildNode( child_name, L"", _false );
		if ( child->Export( child_node ) == _false )
			return _false;
	}

	return _true;
}

template< typename Type >
_void TGUIContainer< Type >::LoadDelaySubResources( IDynamicResObject* object, ISerializableNode* node ) const
{
	GUIObjectBaseClass::LoadDelaySubResources( object, node );

	ISerializableNodeRef child_node = node->GetChildNodeByName( L"Child" );
	if ( child_node.IsValid( ) )
	{
		ISerializableNodeRef it_node = child_node->GetFirstChildNode( );
		if ( it_node.IsValid( ) )
		{
			do
			{
				IGUIObject* obj = (IGUIObject*) GetInterfaceFactory( )->CreateObject( it_node->GetNodeName( ) );
				if ( obj != _null )
					obj->LoadDelaySubResources( object, it_node );

				EGE_RELEASE( obj );
			}
			while ( it_node->MoveNext( ) );
		}
	}
}

template< typename Type >
_void TGUIContainer< Type >::Render( IObject* viewport, const Matrix3& transform, const Color& color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test)
{
	// Skip for hide container
	if ( this->IsHidden( ) )
		return;

	// It's delay render object
	if ( this->mGUIComponentGroup->GetComponentState( )->GetStatesEx( ).HasFlags( _GUI_STATE_EX_DELAY_RENDER ) )
	{
		GetGUIModule( )->AddDelayRenderGUIObject( this, transform, color, clip_rect );
		return;
	}

	// Get the attributes
	const FlagsObject& attributes = this->mGUIComponentGroup->GetComponentState( )->GetAttributes( );

	if ( attributes.HasFlags( _GUI_ATTRIBUTE_SCENE3D ) )
		return;

	// Get world transform
	Matrix3 world_transform	= this->GetRelativeTransform( ) * transform;
	Color	mixed_color		= this->MixColor( color );

	// Get and push the axis transform
	_ubool is_ui_3d_object = attributes.HasFlags( _GUI_ATTRIBUTE_UI3D );
	if ( is_ui_3d_object )
		this->BeginRender3DInUI( viewport, world_transform );

	// Render container
	RenderContainer( viewport, transform, world_transform, mixed_color, clip_rect, in_clip_state, skip_region_test);

	// Pop axis transform
	if ( is_ui_3d_object )
		this->EndRender3DInUI( viewport );

	this->GetComponentEventHooker( )->InvokeAfterRenderFunc( world_transform, mixed_color );
}

template< typename Type >
_void TGUIContainer< Type >::RenderAfterChild(IObject* viewport, const Matrix3& transform, Color color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test)
{
	EGE_ASSERT(0);
}

template< typename Type >
_ubool TGUIContainer< Type >::HandleEvent( const EventBase& event, const FlagsObject& flags )
{
	// Let self to handle event
	if ( GUIObjectBaseClass::HandleEvent( event, flags ) )
		return _true; // Skip all default handle event procession

	// Deliver to child objects
	if ( flags.HasFlags( _GUI_MESSAGE_DELIVER_CHILD ) )
	{
		// Skip deliver to parent
		FlagsObject skip_deliver_to_parent( flags );
		skip_deliver_to_parent.ClearFlags( _GUI_MESSAGE_DELIVER_PARENT );

		// Continue to handle all child controls
		for ( IGUIObject* child_object = this->FirstChildObject( ); child_object != _null; child_object = child_object->NextObject( ) )
			child_object->HandleEvent( event, skip_deliver_to_parent );
	}

	// Continue to pass the event
	return _false;
}

template< typename Type >
_ubool TGUIContainer< Type >::IsControl( ) const
{
	return _false;
}

template< typename Type >
_ubool TGUIContainer< Type >::IsContainer( ) const
{
	return _true;
}

template< typename Type >
IGUIObject* TGUIContainer< Type >::TestPoint( const Vector2& origin_position, const Vector2& position, const Matrix3& transform, const FlagsObject& flags, Vector2* relative_position )
{
	if ( this->IsHidden( ) )
		return _null;

	typename GUIObjectBaseClass::TestPoint3DInUIHelper test_point_helper;

	// Get the attributes
	const FlagsObject& attributes = this->mGUIComponentGroup->GetComponentState()->GetAttributes();

	_ubool is_ui_3d_object = attributes.HasFlags( _GUI_ATTRIBUTE_UI3D );
	Vector2 local_position = position;
	Matrix3 matrix_self = this->GetRelativeTransform( ) * transform;
	Matrix3 matrix_child = this->GetChildRelativeTransform( ) * transform;
	if ( is_ui_3d_object )
	{
		test_point_helper.Begin( this, matrix_self );
		if ( this->ScreenPositionTo3DLocalSpacePosition( origin_position, local_position ) == _false )
			return _null;
		matrix_self = Matrix3::cIdentity;
		matrix_child = this->GetChildRelativeTransform( ) * this->GetRelativeTransform( ).Inverse( );
	}

	_ubool test_always = flags.HasFlags( _GUI_TESTPOINT_TEST_ALWAYS ) || attributes.HasFlags( _GUI_ATTRIBUTE_TEST_POINT_ALWAYS );
	// Test self
	_GUI_TESTPOINT_RESULT_TYPE test_ret = this->PointInControl( local_position, matrix_self, relative_position );

	switch ( test_ret )
	{
	case _GTRT_IN_AND_CAPTURE:
	{
		// Handle begin event
		if ( flags.HasFlags( _GUI_TESTPOINT_CLICKABLE ) )
		{
			if ( this->IsHandleEvent( _GUI_EVENT_TOUCH_BEGIN ) )
				return this;
		}
		else
		{
			return this;
		}
	}
	break;
	case _GTRT_OUT:
	{
		if ( test_always == _false )
			return _null;
	}
	break;

	default:
		break;
	}

	// Test point with all child objects
	for ( IGUIObject* child_object = this->LastChildObject( ); child_object != _null; child_object = child_object->PrevObject( ) )
	{
		IGUIObject* hit_child_object = child_object->TestPoint( origin_position, local_position, matrix_child, flags, relative_position );
		if ( hit_child_object != _null )
			return hit_child_object;
	}

	if ( test_ret == _GTRT_OUT )
		return _null;

	// Handle begin event
	if ( flags.HasFlags( _GUI_TESTPOINT_CLICKABLE ) )
	{
		if ( this->IsHandleEvent( _GUI_EVENT_TOUCH_BEGIN ) )
			return this;

		return _null;
	}

	return this;
}

template< typename Type >
IGUIObjectRefArray TGUIContainer< Type >::TestPointByReturnList( const Vector2& origin_position, const Vector2& position, const Matrix3& transform, const FlagsObject& flags )
{
	IGUIObjectRefArray objects;

	if ( this->IsHidden( ) )
		return objects;

	typename GUIObjectBaseClass::TestPoint3DInUIHelper test_point_helper;

	// Get the attributes
	const FlagsObject& attributes = this->mGUIComponentGroup->GetComponentState( )->GetAttributes( );

	_ubool is_ui_3d_object = attributes.HasFlags( _GUI_ATTRIBUTE_UI3D );
	Vector2 local_position = position;
	Matrix3 matrix_self = this->GetRelativeTransform( ) * transform;
	Matrix3 matrix_child = this->GetChildRelativeTransform( ) * transform;
	if ( is_ui_3d_object )
	{
		test_point_helper.Begin( this, matrix_self );
		if ( this->ScreenPositionTo3DLocalSpacePosition( origin_position, local_position ) == _false )
			return objects;
		matrix_self = Matrix3::cIdentity;
		matrix_child = this->GetChildRelativeTransform( ) * this->GetRelativeTransform( ).Inverse( );
	}

	// Test self
	_ubool test_always = flags.HasFlags( _GUI_TESTPOINT_TEST_ALWAYS ) || attributes.HasFlags( _GUI_ATTRIBUTE_TEST_POINT_ALWAYS );
	_GUI_TESTPOINT_RESULT_TYPE test_ret = this->PointInControl( local_position, matrix_self, _null );

	switch ( test_ret )
	{
	case _GTRT_IN_AND_CAPTURE:
	{
		// Handle begin event
		if ( flags.HasFlags( _GUI_TESTPOINT_CLICKABLE ) )
		{
			if ( this->IsHandleEvent( _GUI_EVENT_TOUCH_BEGIN ) )
				objects.Append( this );
		}
		else
		{
			objects.Append( this );
		}
		return objects;
	}
	break;
	case _GTRT_OUT:
	{
		if ( test_always == _false )
			return objects;
	}
	break;
	default:
		break;
	}

	// Test point with all child objects
	for ( IGUIObject* child_object = this->LastChildObject( ); child_object != _null; child_object = child_object->PrevObject( ) )
	{
		IGUIObjectRefArray hit_child_objects = child_object->TestPointByReturnList( origin_position, local_position, matrix_child, flags );

		objects += hit_child_objects;
	}

	if ( test_ret == _GTRT_OUT )
		return objects;

	// Handle begin event
	if ( flags.HasFlags( _GUI_TESTPOINT_CLICKABLE ) )
	{
		if ( this->IsHandleEvent( _GUI_EVENT_TOUCH_BEGIN ) )
			objects.Append( this );

		return objects;
	}

	// Hit self
	objects.Append( this );
	return objects;
}

template< typename Type >
IGUIObject* TGUIContainer< Type >::GetIntersectObject( const RectF& region, const Matrix3& transform, const FlagsObject& flags )
{
	if ( this->IsHidden( ) )
		return _null;

	// Get the attributes
	const FlagsObject& attributes = this->mGUIComponentGroup->GetComponentState( )->GetAttributes( );

	// Test self
	_ubool test_always = flags.HasFlags( _GUI_TESTPOINT_TEST_ALWAYS ) || attributes.HasFlags( _GUI_ATTRIBUTE_TEST_POINT_ALWAYS );
	_ubool region_incontrol = this->RegionInControl( region, transform );
	if ( region_incontrol == _false )
	{
		if ( test_always == _false )
			return _null;
	}

	// Build the world transform
	Matrix3 world_transform_forchild = this->GetChildRelativeTransform( ) * transform;

	// Test point with all child objects
	for ( IGUIObject* child_object = this->LastChildObject( ); child_object != _null; child_object = child_object->PrevObject( ) )
	{
		IGUIObject* hit_child_object = child_object->GetIntersectObject( region, world_transform_forchild, flags );
		if ( hit_child_object != _null )
			return hit_child_object;
	}

	if ( region_incontrol == _false )
		return _null;

	return this;
}

template< typename Type >
_void TGUIContainer< Type >::ClearAllChildObjects( )
{
	while ( this->FirstChildObject( ) != _null )
	{
		IGUIObject* object = this->FirstChildObject( );
		this->RemoveChildObject( object );

		EGE_RELEASE( object );
	}
}

template< typename Type >
_void TGUIContainer< Type >::ClearAllChildObjectsExceptForFirst( )
{
	if ( this->FirstChildObject( ) == _null )
		return;
	
	IGUIObject* next_object = this->FirstChildObject( )->NextObject( );
	while ( next_object != _null )
	{
		this->RemoveChildObject( next_object );
		EGE_RELEASE( next_object );
		next_object = this->FirstChildObject( )->NextObject( );
	}
}

template< typename Type >
_void TGUIContainer< Type >::ClearAllChildObjectsExceptFor( IGUIObject* gui_object )
{
	Array< IGUIObject* > clear_array;
	for ( IGUIObject* it = this->FirstChildObject( ); it != _null; it = it->NextObject( ) )
	{
		if ( it != gui_object )
			clear_array.Append( it );
	}

	for ( _dword i = 0; i < clear_array.Number( ); ++ i )
	{
		this->RemoveChildObject( clear_array[i] );
		EGE_RELEASE( clear_array[i] );
	}
}

template< typename Type >
IGUIObjectRefArray TGUIContainer< Type >::GetChildObjects( _ubool recursive )
{
	IGUIObjectRefArray objects;

	for ( IGUIObject* object = this->FirstChildObject( ); object != _null; object = object->NextObject( ) )
	{
		objects.Append( object );

		// Keep to search recursively
		if ( recursive && object->IsContainer( ) )
		{
			IGUIObjectRefArray gui_objects = ((IGUIContainer*) object)->GetChildObjects( recursive );

			objects += gui_objects;
		}
	}

	return objects;
}

template< typename Type >
IGUIObject*	TGUIContainer< Type >::SearchControlByPath( WStringPtr path, _ubool ignorecase )
{
	if ( path.IsEmpty( ) )
		return _null;

	WStringArray paths;
	StringFormatter::SplitString( path, paths, L"/", L" \t" );

	// Start to search
	IGUIContainer* parent_object = this;
	for ( _dword i = 0; i < paths.Number( ); i ++ )
	{
		IGUIObject* object = parent_object->SearchControlByName( paths[i], ignorecase );
		if ( object == _null )
			break;

		// If it not reach the last one then we must make sure this child object must be a container
		if ( i != paths.Number( ) - 1 )
		{
			if ( object->IsContainer( ) == _false )
				break;

			// Update parent object
			parent_object = (IGUIContainer*) object;
		}
		else
		{
			return object;
		}
	}

	// Found nothing
	return _null;
}

template< typename Type >
IGUIObject* TGUIContainer< Type >::SearchControlByName( WStringPtr name, _ubool ignorecase ) 
{
	if ( this->GetResName( ) == name )
		return this;

	for ( IGUIObject* object = (IGUIObject*) this->FirstChildObject( ); object != _null; object = object->NextObject( ) )
	{
		// Check the object name
		if ( object->GetResName( ).IsEqual( name, ignorecase ) == _false )
			continue;

		return object;
	}

	return _null;
}

template< typename Type >
IGUIObject* TGUIContainer< Type >::SearchControlByName( WStringPtr name, _ubool recursive, _ubool ignorecase ) 
{
	if ( this->GetResName( ) == name )
		return this;

	for ( IGUIObject* object = (IGUIObject*) this->FirstChildObject( ); object != _null; object = object->NextObject( ) )
	{
		// Check the object name
		if ( object->GetResName( ).IsEqual( name, ignorecase ) )
			return object;

		// Keep to search recursively
		if ( recursive && object->IsContainer( ) )
		{
			IGUIObject* gui_object = ((IGUIContainer*) object)->SearchControlByName( name, recursive, ignorecase );
			if ( gui_object != _null )
				return gui_object;
		}
	}

	return _null;
}

template< typename Type >
IGUIObject* TGUIContainer< Type >::LocateAtChildAppAndSearchByName( WStringPtr child_app, WStringPtr control_name ) 
{
	if ( this->GetResName( ) == control_name )
		return this;

	IGUIObject* child = SearchControlByName( child_app, _false, _false );
	if ( child_app.IsEqual( control_name, _false ) )
		return child;

	if ( child != _null && child->IsContainer( ) )
	{
		IGUIContainer* container = (IGUIContainer*)child;

		child = container->SearchControlByName( control_name, _true, _false );
		if ( child != _null )
			return child;
	}

	return _null;
}

template< typename Type >
_ubool TGUIContainer< Type >::RemoveGUIObjectByName( WStringPtr name, _ubool recursive, _ubool ignorecase )
{
	IGUIObject* gui_object = SearchControlByName( name, recursive, ignorecase );
	if ( gui_object == _null )
		return _false;

	// Remove the link
	this->RemoveChildObject( gui_object );

	// Release it
	EGE_RELEASE( gui_object );

	return _true;
}

template< typename Type >
IGUIObject* TGUIContainer< Type >::GetCheckedChildObject( )
{
	for ( IGUIObject* child = this->FirstChildObject( ); child != _null; child = child->NextObject( ) )
	{
		if ( child->GetComponentState( )->IsCheck( ) )
			return child;
	}

	return _null;
}

template< typename Type >
IGUIObjectRefArray TGUIContainer< Type >::GetCheckedChildObjects( )
{
	IGUIObjectRefArray array;

	for ( IGUIObject* child = this->FirstChildObject( ); child != _null; child = child->NextObject( ) )
	{
		if ( child->GetComponentState( )->IsCheck( ) )
			array.Append( child );
	}

	return array;
}

template< typename Type >
_void TGUIContainer< Type >::ResetControlAnimationInfo( _ubool deep )
{
	GUIObjectBaseClass::ResetControlAnimationInfo( deep );

	if ( deep )
	{
		for ( IGUIObject* child = this->FirstChildObject( ); child != _null; child = child->NextObject( ) )
			child->ResetControlAnimationInfo( deep );
	}
}

}