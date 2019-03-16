//! @file     GUIComponentGroup.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GUIComponentGroup
//----------------------------------------------------------------------------

class GUIComponentGroup : public TGUIComponent< IGUIComponentGroup >
{
public:
	RTTI_CLASS_WITH_ARGUMENTS_DECL( GUIComponentGroup, IGUIComponentGroup, IGUIObject* )

public:
	_GUICOMPONENT_ENABLE_TICK( )
	_GUICOMPONENT_ENABLE_RENDER( )
	_GUICOMPONENT_ENABLE_AFTER_CHILD_RENDER( )
	_GUICOMPONENT_ENABLE_HANDLE_EVENT( )
	_GUICOMPONENT_ENABLE_IS_HANDLE_EVENT( )
	_GUICOMPONENT_ENABLE_EXPORT( )

public:
	typedef TGUIComponent< IGUIComponentGroup > BaseClass;

private:
	//!	The GUI component with key.
	struct GUIComponentWithKey
	{
		_dword					mOrder;
		const IGUIComponent*	mComponent;

		operator _qword( ) const
		{
			_qword key = 0;

			// 1. First we sort the state ID (main key)
			key = ((_qword) mComponent->GetComponentObjStateID( )) << 32;

			// 2. Next, we need to sort the component like Import() function (secondary key)
			key |= mOrder;

			return key;
		}

		GUIComponentWithKey( )
		{
			mOrder		= 0;
			mComponent	= _null;
		}
		GUIComponentWithKey( _dword order, const IGUIComponent* component )
		{
			mOrder		= order;
			mComponent	= component;
		}
	};
	typedef Array< GUIComponentWithKey, _qword > GUIComponentWithKeyArray;

	//! The GUI component with sort index.
	struct GUIComponentWithSortIndex
	{
		_dword			mIndex;
		IGUIComponent*	mComponent;

		//!	Use the index and sort index as key.
		operator _dword( ) const
		{
			return ( mComponent->GetComponentSortIndex( ) << 16 ) | ( mIndex & 0xFFFF );
		}

		GUIComponentWithSortIndex( )
		{
			mIndex		= -1;
			mComponent	= _null;
		}
		GUIComponentWithSortIndex( _dword index, IGUIComponent* gui_component )
		{
			mIndex		= index;
			mComponent	= gui_component;
		}
	};
	typedef Array< GUIComponentWithSortIndex, _dword > GUIComponentWithSortIndexArray; 

private:
	//!	The component array.
	typedef Array< IGUIComponentRef > GUIComponentRefArray;
	typedef Array< IGUIComponent* > GUIComponentPtrArray; 

private:
	//!	The quick access components
	IGUIComponentColor*					mComponentColor;
	IGUIComponentEventHooker*			mComponentEventHooker;
	IGUIComponentPosition*				mComponentPosition;
	IGUIComponentState*					mComponentState;
	IGUIComponentAnimation*				mComponentAnimation;

	//!	The kind of components array to process
	GUIComponentWithSortIndexArray		mTickArray;
	GUIComponentWithSortIndexArray		mRenderArray;
	GUIComponentWithSortIndexArray		mAfterChildRenderArray;
	GUIComponentWithSortIndexArray		mHandleEventArray;
	GUIComponentWithSortIndexArray		mIsHandleEventArray;
	GUIComponentWithSortIndexArray		mTestRegionArray;

	//!	The components
	GUIComponentRefArray				mComponents;
	//!	The components with states
	GUIComponentPtrArray				mComponentsWithState[_GUI_STATE_MAXNUMBER];

private:
	//!	Convert GUI state to index.
	_dword ConvertGUIState2Index( _GUI_OBJECT_STATE state ) const;
	//!	Get the parent GUI state.
	_GUI_OBJECT_STATE GetParentGUIState( _GUI_OBJECT_STATE state ) const;
	//!	Check whether it's compatible GUI state.
	_ubool IsCompatibleGUIState( _GUI_OBJECT_STATE state_1, _GUI_OBJECT_STATE state_2 ) const;
	_ubool IsCompatibleGUIState( const IGUIComponent* component_1, const IGUIComponent* component_2 ) const;

	//!	Create internal components.
	_void CreateInternalComponents( );
	//!	Locate internal components.
	_void LocateInternalComponents( );

	//!	Clear quick access components.
	_void ClearQuickAccessComponents( );

	//!	Insert/Remove component.
	_ubool HasComponent( const GUIComponentWithSortIndexArray& components, IGUIComponent* component );
	_void InsertComponentWithSortKey( GUIComponentWithSortIndexArray& components, IGUIComponent* component );
	_void InsertComponent( GUIComponentPtrArray& components, IGUIComponent* component );
	_void RemoveComponent( GUIComponentWithSortIndexArray& components, IGUIComponent* component );
	_void BindCompnent( IGUIComponent* gui_component, _ubool update_access_component );
	IGUIComponent* CreateComponent( AStringPtr name, _ubool update_access_component );
	IGUIComponent* CloneComponent( const IGUIComponent* src_gui_compnent, _ubool update_access_component );

	//!	Update/Remove access components.
	_void UpdateAccessComponent( IGUIComponent* component );
	_void RemoveAccessComponent( IGUIComponent* component );
	//!	Rebuild access components
	_void RebuildAccessComponents( _GUI_OBJECT_STATE state );

	//!	Clear components with state.
	_void ClearComponentsWithState( );
	//!	Update default components with state.
	_void UpdateDefaultComponentsWithState( );
	//!	Update/Remove components with state.
	_void UpdateComponentsWithState( IGUIComponent* component );
	_void RemoveComponentsWithState( IGUIComponent* component );

	//!	Get the component's state from node.
	_GUI_OBJECT_STATE GetComponentStateFromNode( ISerializableNode* node );

	//!	Get or create component.
	IGUIComponent* GetComponent( _GUI_OBJECT_STATE state, AStringPtr name, _ubool update );

	//!	Get the all components with state as key.
	_ubool GetAllComponents( GUIComponentWithKeyArray& components ) const;

public:
	GUIComponentGroup( IGUIObject* gui_object );
	virtual ~GUIComponentGroup( );

// IObject Interface
public:
	virtual IObject*					CloneTo( _void* arguments ) const override;

	virtual _void						Tick( _time_t tick, _dword elapse ) override;

// IDynamicResObject Interface
public:
	virtual _void						UnloadResources( _ubool force, _ubool clear_cache ) override;
	virtual _void						ReloadResourcesInBackgroundThread( _ubool lock ) override;
	virtual _void						ReloadResourcesInMainThread( _ubool lock ) override;

	virtual _ubool						AreAllResourcesAvailable( ) const override;
	virtual DwordRange					GetResourcesLoadedProgression( ) const override;

	virtual _void						ExportResources( IDynamicResObject* cache_obj ) const override;

	virtual _void						LoadDelaySubResources( IDynamicResObject* object, ISerializableNode* node ) const override;

// ISerializable Interface
public:
	virtual _ubool						Import( ISerializableNode* node ) override;
	virtual _ubool						Export( ISerializableNode* node ) const override;

// IGUIComponent Interface
public:
	virtual _ubool						IsHandleEvent( _dword event_id ) const override;

	virtual _ubool						HandleEvent( const EventBase& event, const FlagsObject& flags ) override;
	virtual _void						Render( IObject* viewport, const Matrix3& transform, const Color& color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test ) override;
	virtual _void						RenderAfterChild( IObject* viewport, const Matrix3& transform, Color color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test ) override;

	virtual _GUI_TESTPOINT_RESULT_TYPE	PointInControl( const Vector2& position, const Matrix3& transform, Vector2* relative_position ) override;
	virtual _ubool						RegionInControl( const RectF& region, const Matrix3& transform ) override;

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
};

//----------------------------------------------------------------------------
// GUIComponentGroup Implementation
//----------------------------------------------------------------------------

inline _dword GUIComponentGroup::ConvertGUIState2Index( _GUI_OBJECT_STATE state ) const
{
	return state & 0x000000FF;
}

inline _GUI_OBJECT_STATE GUIComponentGroup::GetParentGUIState( _GUI_OBJECT_STATE state ) const
{
	_GUI_OBJECT_STATE parent_state = (_GUI_OBJECT_STATE) ( ( (_dword) state & 0x0000FF00 ) >> 8 );
	return parent_state;
}

inline _ubool GUIComponentGroup::IsCompatibleGUIState( _GUI_OBJECT_STATE state_1, _GUI_OBJECT_STATE state_2 ) const
{
	_GUI_OBJECT_STATE parent_state_1 = GetParentGUIState( state_1 );
	_GUI_OBJECT_STATE parent_state_2 = GetParentGUIState( state_2 );
	if ( parent_state_1 == _GUI_STATE_NORMAL || parent_state_2 == _GUI_STATE_NORMAL )
		return _true;

	if ( parent_state_1 == parent_state_2 )
		return _true;

	return _false;
}

inline _ubool GUIComponentGroup::IsCompatibleGUIState( const IGUIComponent* component_1, const IGUIComponent* component_2 ) const
{
	EGE_ASSERT( component_1 != _null );
	EGE_ASSERT( component_2 != _null );

	_GUI_OBJECT_STATE state_1 = component_1->GetComponentObjStateID( );
	_GUI_OBJECT_STATE state_2 = component_2->GetComponentObjStateID( );

	return IsCompatibleGUIState( state_1, state_2 );
}

}