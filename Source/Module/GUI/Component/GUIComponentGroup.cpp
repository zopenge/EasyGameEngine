//! @file     GUIComponentGroup.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGUI.h"

//----------------------------------------------------------------------------
// GUIComponentGroup Implementation
//----------------------------------------------------------------------------

GUIComponentGroup::GUIComponentGroup( IGUIObject* gui_object ) : BaseClass( gui_object )
	, mTickArray( 0, 1 )
	, mRenderArray( 0, 1 )
	, mAfterChildRenderArray( 0, 1 )
	, mHandleEventArray( 0, 1 )
	, mIsHandleEventArray( 0, 1 )
	, mTestRegionArray( 0, 1 )
	, mComponents( 0, 1 )
{
	mGUIObject = gui_object;

	for ( _dword i = 0; i < _GUI_STATE_MAXNUMBER; i ++ )
		mComponentsWithState[i].Init( 0, 1 );

	CreateInternalComponents( );
}

GUIComponentGroup::~GUIComponentGroup( )
{
}

_void GUIComponentGroup::CreateInternalComponents( )
{
	mComponentColor			= (IGUIComponentColor*) CreateComponent( "GUIComponentColor" );
	mComponentEventHooker	= (IGUIComponentEventHooker*) CreateComponent( "GUIComponentEventHooker" );
	mComponentPosition		= (IGUIComponentPosition*) CreateComponent( "GUIComponentPosition" );
	mComponentState			= (IGUIComponentState*) CreateComponent( "GUIComponentState" );
	mComponentAnimation		= (IGUIComponentAnimation*) CreateComponent( "GUIComponentAnimation" );
}

_void GUIComponentGroup::LocateInternalComponents( )
{
	mComponentColor			= (IGUIComponentColor*) FindComponent( "GUIComponentColor" );
	mComponentEventHooker	= (IGUIComponentEventHooker*) FindComponent( "GUIComponentEventHooker" );
	mComponentPosition		= (IGUIComponentPosition*) FindComponent( "GUIComponentPosition" );
	mComponentState			= (IGUIComponentState*) FindComponent( "GUIComponentState" );
	mComponentAnimation		= (IGUIComponentAnimation*) FindComponent( "GUIComponentAnimation" );
}

_void GUIComponentGroup::ClearQuickAccessComponents( )
{
	mTickArray.Clear( );
	mRenderArray.Clear( );
	mAfterChildRenderArray.Clear();
	mHandleEventArray.Clear( );
	mIsHandleEventArray.Clear( );
	mTestRegionArray.Clear( );
}

_ubool GUIComponentGroup::HasComponent( const GUIComponentWithSortIndexArray& components, IGUIComponent* component )
{
	for ( _dword i = 0; i < components.Number( ); i ++ )
	{
		if ( components[i].mComponent == component )
			return _true;
	}

	return _false;
}

_void GUIComponentGroup::InsertComponentWithSortKey( GUIComponentWithSortIndexArray& components, IGUIComponent* component )
{
	components.InsertAscending( GUIComponentWithSortIndex( components.Number( ), component ) );
}

_void GUIComponentGroup::InsertComponent( GUIComponentPtrArray& components, IGUIComponent* component )
{
	EGE_ASSERT( component != _null );

	// Get the parent state
	_GUI_OBJECT_STATE parent_state = GetParentGUIState( component->GetComponentObjStateID( ) );

	for ( _dword i = 0; i < components.Number( ); i ++ )
	{
		IGUIComponent*& exist_component = components[i];

		if ( exist_component == component )
			return; // Skip for same component

		if ( exist_component->GetClassTypeNameA( ) != component->GetClassTypeNameA( ) )
			continue; // Must be the same type

		// If the existing component is normal state then replace it
		_GUI_OBJECT_STATE exist_component_state = exist_component->GetComponentObjStateID( );
		if ( exist_component_state == _GUI_STATE_NORMAL || exist_component_state == parent_state )
			exist_component = component;

		// It's same type skip to insert it
		return;
	}

	components.Append( component );
}

_void GUIComponentGroup::RemoveComponent( GUIComponentWithSortIndexArray& components, IGUIComponent* component )
{
	for ( _dword i = 0; i < components.Number( ); i ++ )
	{
		if ( components[i].mComponent == component )
		{
			components.RemoveByIndex( i );
			return;
		}
	}
}

_void GUIComponentGroup::BindCompnent( IGUIComponent* gui_component, _ubool update_access_component )
{
	// Update access component
	if ( update_access_component )
	{
		UpdateAccessComponent( gui_component );
		UpdateComponentsWithState( gui_component );
	}

	// Insert component
	mComponents.Append( gui_component );
}

IGUIComponent* GUIComponentGroup::CreateComponent( AStringPtr name, _ubool update_access_component )
{
	// We don't have it, so create it
	IGUIComponentRef component = GetInterfaceFactory( )->CreateObjectPassRef< IGUIComponent >( name, mGUIObject );
	if ( component.IsNull( ) )
		return _null;

	// Bind with current GUI object
	BindCompnent( component, update_access_component );

	return component;
}

IGUIComponent* GUIComponentGroup::CloneComponent( const IGUIComponent* src_gui_compnent, _ubool update_access_component )
{
	// Clone component
	IGUIComponentRef component = src_gui_compnent->CloneToPassRef< IGUIComponent >( mGUIObject );
	if ( component.IsNull( ) )
		return _null;

	// Bind with current GUI object
	BindCompnent( component, update_access_component );

	return component;
}

_void GUIComponentGroup::UpdateAccessComponent( IGUIComponent* component )
{
	if ( component->DoTick( ) )
		InsertComponentWithSortKey( mTickArray, component );

	if ( component->DoRender( ) )
		InsertComponentWithSortKey( mRenderArray, component );

	if ( component->DoAfterChildRender( ) )
		InsertComponentWithSortKey( mAfterChildRenderArray, component);

	if ( component->DoHandleEvent( ) )
		InsertComponentWithSortKey( mHandleEventArray, component );

	if ( component->DoIsHandleEvent( ) )
		InsertComponentWithSortKey( mIsHandleEventArray, component );

	if ( component->DoTestRegion( ) )
		InsertComponentWithSortKey( mTestRegionArray, component );
}

_void GUIComponentGroup::RemoveAccessComponent( IGUIComponent* component )
{
	RemoveComponent( mTickArray, component );
	RemoveComponent( mRenderArray, component );
	RemoveComponent( mAfterChildRenderArray, component);
	RemoveComponent( mHandleEventArray, component );
	RemoveComponent( mIsHandleEventArray, component );
	RemoveComponent( mTestRegionArray, component );
}

_void GUIComponentGroup::RebuildAccessComponents( _GUI_OBJECT_STATE state )
{
	ClearQuickAccessComponents( );

	// Use the internal components
	UpdateAccessComponent( mComponentColor );
	UpdateAccessComponent( mComponentEventHooker );
	UpdateAccessComponent( mComponentPosition );
	UpdateAccessComponent( mComponentState );
	UpdateAccessComponent( mComponentAnimation );

	// Get the GUI state index
	_dword index = ConvertGUIState2Index( state );

	// Use the external components
	GUIComponentPtrArray& components = mComponentsWithState[index];
	for ( _dword i = 0; i < components.Number( ); i ++ )
	{
		IGUIComponent* component = components[i];
		EGE_ASSERT( component != _null );

#ifdef _DEBUG
		// If the component is not default status then must match the state type 
		if ( component->GetComponentObjStateID( ) != _GUI_STATE_NORMAL )
		{
			EGE_ASSERT( IsCompatibleGUIState( component->GetComponentObjStateID( ), state ) );
		}
#endif

		UpdateAccessComponent( component );
	}
}

_void GUIComponentGroup::ClearComponentsWithState( )
{
	for ( _dword i = 0; i < _GUI_STATE_MAXNUMBER; i ++ )
		mComponentsWithState[i].Clear( );
}

_void GUIComponentGroup::UpdateDefaultComponentsWithState( )
{
	for ( _dword i = 0; i < mComponents.Number( ); i ++ )
	{
		IGUIComponent* component = mComponents[i];
		EGE_ASSERT( component != _null );

		if ( component->IsResident( ) )
			continue;

		UpdateComponentsWithState( component );
	}
}

_void GUIComponentGroup::UpdateComponentsWithState( IGUIComponent* component )
{
	// Skip for internal component
	if ( component->IsResident( ) )
		return;

	// Get the state of component
	_GUI_OBJECT_STATE state = component->GetComponentObjStateID( );
	EGE_ASSERT( state != _GUI_STATE_UNKNOWN );

	// Use the normal as default for all other components
	if ( state == _GUI_STATE_NORMAL )
	{
		for ( _dword i = 0; i < _GUI_STATE_MAXNUMBER; i ++ )
			InsertComponent( mComponentsWithState[i], component );
	}
	// Just update the component
	else
	{
		// Get the index by GUI state
		_dword index = ConvertGUIState2Index( state );

		// Update with the parent state components
		_GUI_OBJECT_STATE parent_state = GetParentGUIState( state );
		if ( parent_state != state )
		{
			_dword base_index = ConvertGUIState2Index( parent_state );
			for ( _dword i = 0; i < mComponentsWithState[base_index].Number( ); i ++ )
			{
				IGUIComponent* base_component = mComponentsWithState[base_index][i];
				EGE_ASSERT( base_component != _null );

				InsertComponent( mComponentsWithState[index], base_component );
			}
		}

		// Update the self component state
		InsertComponent( mComponentsWithState[index], component );
	}
}

_void GUIComponentGroup::RemoveComponentsWithState( IGUIComponent* component )
{
	// Remove components with all states
	for ( _dword i = 0; i < _GUI_STATE_MAXNUMBER; i ++ )
	{
		for ( _dword j = 0; j < mComponentsWithState[i].Number( ); j ++ )
		{
			IGUIComponent* external_component = mComponentsWithState[i][j];

			if ( external_component == component )
				mComponentsWithState[i].RemoveByIndex( j -- );
		}
	}

	// Get the default state components
	_dword index = ConvertGUIState2Index( _GUI_STATE_NORMAL );
	GUIComponentPtrArray& default_components = mComponentsWithState[index];

	// Refresh the default states
	for ( _dword i = 0; i < default_components.Number( ); i ++ )
	{
		IGUIComponent* external_component = default_components[ i ];
		EGE_ASSERT( external_component != _null );

		UpdateComponentsWithState( external_component );
	}
}

_GUI_OBJECT_STATE GUIComponentGroup::GetComponentStateFromNode( ISerializableNode* node )
{
	EGE_ASSERT( node != _null );

	_GUI_OBJECT_STATE state = _GUI_STATE_NORMAL;
	node->ReadEnum( L"gui_state", (_dword&)state, _false, OnQueryGUIStateEnumValue );

	return state;
}

IGUIComponent* GUIComponentGroup::GetComponent( _GUI_OBJECT_STATE state, AStringPtr name, _ubool update )
{
	for ( _dword i = 0; i < mComponents.Number( ); ++ i )
	{
		IGUIComponent* component = mComponents[i];
		EGE_ASSERT( component != _null );

		if ( component->GetClassTypeNameA( ) != name )
			continue;

		if ( component->IsResident( ) )
			return component;

		if ( component->GetComponentObjStateID( ) == state )
			return component;
	}

	// Create new one
	IGUIComponent* component = CreateComponent( name, _false );
	if ( component == _null )
		return _null;

	// Set the state of component
	component->SetComponentObjStateID( state );

	// Update it
	if ( update )
	{
		// Update component with state
		if ( component->IsResident( ) == _false )
			UpdateComponentsWithState( component );

		RebuildAccessComponents( GetComponentState( )->GetState( ) );
	}

	return component;
}

_ubool GUIComponentGroup::GetAllComponents( GUIComponentWithKeyArray& components ) const
{
	_dword order = 0;

	for ( _dword i = 0; i < mComponents.Number( ); i ++ )
	{
		const IGUIComponent* component = mComponents[i];
		EGE_ASSERT( component != _null );

		components.InsertAscending( GUIComponentWithKey( order ++, component ) );
	}

	return _true;
}

_void GUIComponentGroup::Tick( _time_t tick, _dword elapse )
{
	for ( _dword i = 0; i < mTickArray.Number( ); ++ i )
		mTickArray[i].mComponent->Tick( tick, elapse );
}

_void GUIComponentGroup::UnloadResources( _ubool force, _ubool clear_cache )
{
	for ( _dword i = 0; i < mHandleEventArray.Number( ); ++ i )
		mHandleEventArray[i].mComponent->UnloadResources( force, clear_cache );
}

_void GUIComponentGroup::ReloadResourcesInBackgroundThread( _ubool lock )
{
	for ( _dword i = 0; i < mHandleEventArray.Number( ); ++ i )
		mHandleEventArray[i].mComponent->ReloadResourcesInBackgroundThread( lock );
}

_void GUIComponentGroup::ReloadResourcesInMainThread( _ubool lock )
{
	for ( _dword i = 0; i < mHandleEventArray.Number( ); ++ i )
		mHandleEventArray[i].mComponent->ReloadResourcesInMainThread( lock );
}

_ubool GUIComponentGroup::AreAllResourcesAvailable( ) const
{
	for ( _dword i = 0; i < mHandleEventArray.Number( ); ++ i )
	{
		if ( mHandleEventArray[i].mComponent->AreAllResourcesAvailable( ) == _false )
			return _false;
	}

	return _true;
}

DwordRange GUIComponentGroup::GetResourcesLoadedProgression( ) const
{
	DwordRange progression;
	for ( _dword i = 0; i < mHandleEventArray.Number( ); ++ i )
		progression += mHandleEventArray[i].mComponent->GetResourcesLoadedProgression( );

	return progression;
}

_void GUIComponentGroup::ExportResources( IDynamicResObject* cache_obj ) const
{
	for ( _dword i = 0; i < mHandleEventArray.Number( ); ++ i )
		mHandleEventArray[i].mComponent->ExportResources( cache_obj );
}

_void GUIComponentGroup::LoadDelaySubResources( IDynamicResObject* object, ISerializableNode* node ) const
{
	if ( node == _null )
		return;

	for ( ISerializableNodeRef child = node->GetFirstChildNode( ); child->HasObject( ); child->MoveNext( ) )
	{
		// Get the node name as component name
		WString component_name = child->GetNodeName( );
		if ( component_name == L"Child" )
			continue; // Some reserved name could be skipped

		// Create/Get GUI component by name
		IGUIComponentRef component = GetInterfaceFactory( )->CreateObjectPassRef< IGUIComponent >( component_name, mGUIObject );
		if ( component.IsValid( ) )
			component->LoadDelaySubResources( object, child );
	}
}

IObject* GUIComponentGroup::CloneTo( _void* arguments ) const
{
	// Get the argument as GUI object type
	IGUIObject* gui_object = (IGUIObject*) arguments;
	EGE_ASSERT( gui_object != _null );

	// Create component group
	GUIComponentGroup* component_group = new GUIComponentGroup( gui_object );
	component_group->CopyFrom( this );

	// Clear all components
	component_group->RemoveAllComponents( );

	// Clone the resident components
	for ( _dword i = 0; i < mComponents.Number( ); ++ i )
	{
		const IGUIComponent* src_component = mComponents[i];

		if ( src_component->IsResident( ) == _false )
			continue;

		IGUIComponent* component = component_group->CloneComponent( src_component, _false );
		EGE_ASSERT( component != _null );
	}

	component_group->LocateInternalComponents( );

	// Clone external components
	for ( _dword i = 0; i < mComponents.Number( ); ++ i )
	{
		const IGUIComponent* src_component = mComponents[i];

		if ( src_component->IsResident( ) )
			continue;

		IGUIComponent* component = component_group->CloneComponent( src_component, _false );
		EGE_ASSERT( component != _null );
	}

	// Update the default components with state
	component_group->UpdateDefaultComponentsWithState( );

	// Rebuild access components
	component_group->RebuildAccessComponents( GetComponentState( )->GetState( ) );

	return component_group;
}

_ubool GUIComponentGroup::Import( ISerializableNode* node )
{
	if ( node == _null )
		return _false;

	// Update the default components with state
	UpdateDefaultComponentsWithState( );

	// Import components
	for ( ISerializableNodeRef child = node->GetFirstChildNode( ); child->HasObject( ); child->MoveNext( ) )
	{
		// Get the node name as component name
		AString component_name = AString( ).FromString( child->GetNodeName( ) );
		if ( component_name == "Child" )
			continue; // Some reserved name could be skipped

		// Get the component state
		_GUI_OBJECT_STATE component_state = GetComponentStateFromNode( child );

		// Create/Get GUI component by name
		IGUIComponent* component = GetComponent( component_state, component_name, _false );
		if ( component == _null )
			continue; // That could be null, because we can use some custom tag

		// Import it
		if ( component->Import( child ) == _false )
		{
			WLOG_ERROR_2( L"Import '%s:%s' GUI component failed", mGUIObject->GetResName( ).Str( ), component_name.Str( ) );
			return _false;
		}

		EGE_ASSERT( component->GetComponentObjStateID( ) == component_state );

		UpdateComponentsWithState( component );
	}

	RebuildAccessComponents( GetComponentState( )->GetState( ) );

	return _true;
}

_ubool GUIComponentGroup::Export( ISerializableNode* node ) const
{
	if ( node == _null )
		return _false;

	GUIComponentWithKeyArray components;
	if ( GetAllComponents( components ) == _false )
		return _false;

	for ( _dword i = 0; i < components.Number( ); i ++ )
	{
		const IGUIComponent* component = components[i].mComponent;

		if ( component->DoExport( ) )
		{
			ISerializableNodeRef component_node = node->InsertChildNode( component->GetClassTypeNameW( ), L"", _false );
			if ( component_node.IsNull( ) )
				return _false;

			if ( component->Export( component_node ) == _false )
				return _false;
		}
	}

	return _true;
}

_ubool GUIComponentGroup::IsHandleEvent( _dword event_id ) const
{
	for ( _dword i = 0; i < mIsHandleEventArray.Number( ); ++ i )
	{
		if ( mIsHandleEventArray[i].mComponent->IsHandleEvent( event_id ) )
			return _true;
	}

	return _false;
}

_ubool GUIComponentGroup::HandleEvent( const EventBase& event, const FlagsObject& flags )
{
	if ( event.mEventID == _GUI_EVENT_STATE_CHANGED )
		RebuildAccessComponents( GetComponentState( )->GetState( ) );

	_ubool result = _false;
	for ( _dword i = 0; i < mHandleEventArray.Number( ); ++ i )
	{
		IGUIComponent* component = mHandleEventArray[i].mComponent;

		if ( component->HandleEvent( event, flags ) )
			result = _true;
	}

	return result;
}

_void GUIComponentGroup::Render( IObject* viewport, const Matrix3& transform, const Color& color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test)
{
	for (_dword i = 0; i < mRenderArray.Number(); ++i)
	{
		IGUIComponent* component = mRenderArray[i].mComponent;
		EGE_ASSERT( component != _null );

		if ( component->IsSleep( ) )
			continue;

		component->Render(viewport, transform, color, clip_rect, in_clip_state, skip_region_test);
	}
}

_void GUIComponentGroup::RenderAfterChild(IObject* viewport, const Matrix3& transform, Color color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test)
{
	for (_dword i = 0; i < mAfterChildRenderArray.Number(); ++i)
		mAfterChildRenderArray[i].mComponent->RenderAfterChild(viewport, transform, color, clip_rect, in_clip_state, skip_region_test);
}

_GUI_TESTPOINT_RESULT_TYPE GUIComponentGroup::PointInControl( const Vector2& position, const Matrix3& transform, Vector2* relative_position )
{
	// Test the position first
	_GUI_TESTPOINT_RESULT_TYPE ret = mComponentPosition->PointInControl( position, transform, relative_position );

	for ( _dword i = 0; i < mTestRegionArray.Number( ); ++ i )
	{
		IGUIComponent* component = mTestRegionArray[i].mComponent;

		if ( component == mComponentPosition )
			continue;

		_GUI_TESTPOINT_RESULT_TYPE component_ret = component->PointInControl( position, transform, relative_position );
		if ( component_ret != _GTRT_IN )
			ret = component_ret;
	}

	return ret;
}

_ubool GUIComponentGroup::RegionInControl( const RectF& region, const Matrix3& transform )
{
	for ( _dword i = 0; i < mTestRegionArray.Number( ); ++ i )
	{
		IGUIComponent* component = mTestRegionArray[i].mComponent;

		if ( component->RegionInControl( region, transform ) )
			return _true;
	}

	return _false;
}

IGUIComponentColor* GUIComponentGroup::GetComponentColor( ) const
{
	return mComponentColor;
}

IGUIComponentEventHooker* GUIComponentGroup::GetComponentEventHooker( ) const
{
	return mComponentEventHooker;
}

IGUIComponentPosition* GUIComponentGroup::GetComponentPosition( ) const
{
	return mComponentPosition;
}

IGUIComponentState* GUIComponentGroup::GetComponentState( ) const
{
	return mComponentState;
}

IGUIComponentAnimation* GUIComponentGroup::GetComponentAnimation( ) const
{
	return mComponentAnimation;
}

IGUIComponent* GUIComponentGroup::GetComponent( AStringPtr name )
{
	IGUIComponent* component = GetComponent( _GUI_STATE_NORMAL, name, _true );
	if ( component == _null )
		return _null;

	return component;
}

IGUIComponent* GUIComponentGroup::GetComponent( _GUI_OBJECT_STATE state, AStringPtr name )
{
	IGUIComponent* component = GetComponent( state, name, _true );
	if ( component == _null )
		return _null;

	return component;
}

_ubool GUIComponentGroup::HasComponent( AStringPtr name ) const
{
	return HasComponent( _GUI_STATE_NORMAL, name );
}

_ubool GUIComponentGroup::HasComponent( _GUI_OBJECT_STATE state, AStringPtr name ) const
{
	for ( _dword i = 0; i < mComponents.Number( ); ++ i )
	{
		const IGUIComponent* component = mComponents[i];
		EGE_ASSERT( component != _null );

		if ( component->GetComponentObjStateID( ) == state && component->GetClassTypeNameA( ) == name )
			return _true;
	}

	return _false;
}

_ubool GUIComponentGroup::HasComponents( const AStringArray& components ) const
{
	if ( components.Number( ) == 0 )
		return _true;

	for ( _dword i = 0; i < components.Number( ); i ++ )
	{
		if ( this->HasComponent( components[i] ) )
			return _true;
	}

	return _false;
}

IGUIComponent* GUIComponentGroup::FindComponent( AStringPtr name )
{
	return FindComponent( _GUI_STATE_NORMAL, name );
}

const IGUIComponent* GUIComponentGroup::FindComponent( AStringPtr name ) const
{
	return FindComponent( _GUI_STATE_NORMAL, name );
}

IGUIComponent* GUIComponentGroup::FindComponent( _GUI_OBJECT_STATE state, AStringPtr name )
{
	for ( _dword i = 0; i < mComponents.Number( ); ++ i )
	{
		IGUIComponent* component = mComponents[i];
		EGE_ASSERT( component != _null );

		if ( component->GetComponentObjStateID( ) == state && component->GetClassTypeNameA( ) == name )
			return component;
	}

	return _null;
}

const IGUIComponent* GUIComponentGroup::FindComponent( _GUI_OBJECT_STATE state, AStringPtr name ) const
{
	for ( _dword i = 0; i < mComponents.Number( ); ++ i )
	{
		const IGUIComponent* component = mComponents[i];
		EGE_ASSERT( component != _null );

		if ( component->GetComponentObjStateID( ) == state && component->GetClassTypeNameA( ) == name )
			return component;
	}

	return _null;
}

IGUIComponent* GUIComponentGroup::CreateComponent( AStringPtr name )
{
	return CreateComponent( name, _true );
}

_ubool GUIComponentGroup::RemoveComponent( _GUI_OBJECT_STATE state, AStringPtr name )
{
	for ( _dword i = 0; i < mComponents.Number( ); ++ i )
	{
		IGUIComponent* component = mComponents[i];
		EGE_ASSERT( component != _null );

		// Skip the internal component
		if ( component->IsResident( ) )
			continue;

		if ( component->GetComponentObjStateID( ) != state )
			continue;
		
		if ( component->GetClassTypeNameA( ) != name )
			continue;

		RemoveComponentsWithState( component );
		mComponents.RemoveByIndex( i );

		RebuildAccessComponents( state );

		return _true;
	}

	return _false;
}

_ubool GUIComponentGroup::RemoveComponent( AStringPtr name )
{
	_ubool removed = _false;

	for ( _dword i = 0; i < _GUI_STATE_MAXNUMBER; i ++ )
		removed |= RemoveComponent( (_GUI_OBJECT_STATE)i, name );

	return removed;
}

_ubool GUIComponentGroup::RemoveComponent( _GUI_OBJECT_STATE state )
{
	_ubool removed = _false;

	for (_int i = mComponents.Number() - 1; i >= 0; i--)
	{
		IGUIComponent* component = mComponents[i];
		EGE_ASSERT( component != _null );

		// Skip the internal component
		if ( component->IsResident( ) )
			continue;

		if ( component->GetComponentObjStateID( ) != state )
			continue;

		if ( component->GetClassTypeNameA() == "FGUIComponentParticlePlayerGroup"
			|| component->GetClassTypeNameA() == "FGUIComponentScript"
			|| component->GetClassTypeNameA() == "FGUIComponentSound")
			continue;

		RemoveComponentsWithState(component);
		mComponents.RemoveByIndex(i);
		removed = _true;
	}

	if ( removed )
		RebuildAccessComponents( state );

	return removed;
}

_void GUIComponentGroup::RemoveAllComponents( )
{
	ClearQuickAccessComponents( );
	ClearComponentsWithState( );

	mComponents.Clear( );
}

_void GUIComponentGroup::RemoveAllExternalComponents( )
{
	ClearQuickAccessComponents( );
	ClearComponentsWithState( );

	for ( _dword i = 0; i < mComponents.Number( ); i ++ )
	{
		if ( mComponents[i]->IsResident( ) )
			continue;

		mComponents.RemoveByIndex( i -- );
	}
}

_ubool GUIComponentGroup::MoveUpComponent( _GUI_OBJECT_STATE state, AStringPtr name )
{
	//  The first component can not move up
	for ( _dword i = 1; i < mComponents.Number( ); i ++ )
	{
		IGUIComponentRef component = mComponents[i];

		// The resident component can not move
		if ( component->IsResident( ) )
			continue;

		if ( component->GetComponentObjStateID( ) != state )
			continue;

		if ( component->GetClassTypeNameA( ) != name )
			continue;

		RemoveComponentsWithState( component );

		// Insert it with testing the same state
		mComponents.RemoveByIndex( i );
		for ( _long j = (_long)i - 1; j >= 0; j -- )
		{
			if ( mComponents[j]->GetComponentObjStateID( ) != state )
				continue;

			mComponents.Insert( component, j );
			break;
		}

		ClearComponentsWithState( );
		UpdateDefaultComponentsWithState( );
		RebuildAccessComponents( state );

		return _true;
	}

	return _false;
}

_ubool GUIComponentGroup::MoveDownComponent( _GUI_OBJECT_STATE state, AStringPtr name )
{
	// The last component can not move up
	for ( _long i = (_long)mComponents.Number( ) - 2; i >= 0; i -- )
	{
		IGUIComponentRef component = mComponents[i];

		// The resident component can not move
		if ( component->IsResident( ) )
			continue;

		if ( component->GetComponentObjStateID( ) != state )
			continue;

		if ( component->GetClassTypeNameA( ) != name )
			continue;

		RemoveComponentsWithState( component );

		// Insert it with testing the same state
		_ubool has_inserted = _false;
		mComponents.RemoveByIndex( i );
		for ( _dword j = (_dword)i + 2; j < mComponents.Number( ); j ++ )
		{
			if ( mComponents[j]->GetComponentObjStateID( ) != state )
				continue;

			has_inserted = _true;
			mComponents.Insert( component, j );
			break;
		}

		if ( !has_inserted )
			mComponents.Append( component );

		// Update states
		ClearComponentsWithState( );
		UpdateDefaultComponentsWithState( );
		RebuildAccessComponents( state );

		return _true;
	}

	return _false;
}

_ubool GUIComponentGroup::MoveComponent( _GUI_OBJECT_STATE state, AStringPtr name, _dword index )
{
	if ( index >= mComponents.Number( ) )
		return _false;

	for ( _dword i = 0; i < mComponents.Number( ); i ++ )
	{
		IGUIComponentRef component = mComponents[i];

		// The resident component can not move
		if ( component->IsResident( ) )
			continue;

		if ( component->GetComponentObjStateID( ) != state )
			continue;

		if ( component->GetClassTypeNameA( ) != name )
			continue;

		// Skip for the same index move operation
		if ( i == index )
			break;

		// Start to move
		ClearComponentsWithState( );
		mComponents.RemoveByIndex( i );
		mComponents.Insert( component, index );

		// Update states
		RemoveAllExternalComponents( );
		UpdateDefaultComponentsWithState( );
		RebuildAccessComponents( state );

		return _true;
	}

	return _false;
}

_ubool GUIComponentGroup::MoveComponent( IGUIComponent* component, _dword index )
{
	if ( component == _null || index >= mComponents.Number( ) )
		return _false;

	IGUIComponentRef component_backup = component;
	for ( _dword i = 0; i < mComponents.Number( ); i ++ )
	{
		if ( mComponents[i] != component_backup )
			continue;

		// Skip for the same index move operation
		if ( i == index )
			break;

		// Start to move
		RemoveComponentsWithState( component_backup );
		mComponents.RemoveByIndex( i );
		mComponents.Insert( component_backup, index );

		// Update states
		RemoveAllExternalComponents( );
		UpdateDefaultComponentsWithState( );
		RebuildAccessComponents( component_backup->GetComponentObjStateID( ) );

		return _true;
	}

	return _false;
}

_dword GUIComponentGroup::GetComponentsNumber( ) const
{
	return mComponents.Number( );
}

_dword GUIComponentGroup::GetComponentsNumber( _GUI_OBJECT_STATE state ) const
{
	// Get the default state components
	const GUIComponentPtrArray& default_components = mComponentsWithState[ ConvertGUIState2Index( _GUI_STATE_NORMAL ) ];

	// Feedback the default state components number
	if ( state == _GUI_STATE_NORMAL )
		return default_components.Number( );

	// Get the index of GUI state
	_dword index = ConvertGUIState2Index( state );

	// The number of GUI state components
	_dword number = 0;

	// Other GUI state must exclude he default state to get the real number
	const GUIComponentPtrArray& components = mComponentsWithState[index];
	for ( _dword i = 0; i < components.Number( ); ++ i )
	{
		if ( default_components.Search( components[i] ).IsValid( ) == _false )
			number ++;
	}

	return number;
}

IGUIComponent* GUIComponentGroup::GetComponentByIndex( _dword index )
{
	if ( index >= mComponents.Number( ) )
		return _null;

	return mComponents[ index ];
}

_dword GUIComponentGroup::GetComponentIndex( IGUIComponent* component ) const
{
	for ( _dword i = 0; i < mComponents.Number( ); i ++ )
	{
		if ( mComponents[i] == component )
			return i;
	}

	return -1;
}

_dword GUIComponentGroup::GetComponentIndex( _GUI_OBJECT_STATE state, AStringPtr name ) const
{
	for ( _dword i = 0; i < mComponents.Number( ); i ++ )
	{
		IGUIComponentRef component = mComponents[i];

		if ( component->GetComponentObjStateID( ) != state )
			continue;

		if ( component->GetClassTypeNameA( ) != name )
			continue;

		return i;
	}

	return -1;
}
