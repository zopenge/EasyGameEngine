//! @file     IGUIComponentGroup.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGUIComponentGroup
//----------------------------------------------------------------------------

class IGUIComponentGroup : public IGUIComponent
{
public:
	CLASS_NAME_DECL( IGUIComponentGroup )

public:
	//!	Get color component.
	//!	@param		none.
	//!	@param		The GUI component interface.
	virtual IGUIComponentColor* GetComponentColor( ) const PURE;
	//!	Get event hooker component.
	//!	@param		none.
	//!	@param		The GUI component interface.
	virtual IGUIComponentEventHooker* GetComponentEventHooker( ) const PURE;
	//!	Get position component.
	//!	@param		none.
	//!	@param		The GUI component interface.
	virtual IGUIComponentPosition* GetComponentPosition( ) const PURE;
	//!	Get state component.
	//!	@param		none.
	//!	@param		The GUI component interface.
	virtual IGUIComponentState* GetComponentState( ) const PURE;
	//!	Get animation component.
	//!	@param		none.
	//!	@param		The GUI component interface.
	virtual IGUIComponentAnimation* GetComponentAnimation( ) const PURE;

	//!	Get component by name.
	//!	@remark		It will auto create component if it's not existing.
	//!	@param		name	The component's name.
	//!	@return		The GUI component interface.
	virtual IGUIComponent* GetComponent( AStringPtr name ) PURE;
	//!	Get component by name and object state.
	//!	@remark		It will auto create component if it's not existing.
	//!	@param		state	The object state.
	//!	@param		name	The component's name.
	//!	@return		The GUI component interface.
	virtual IGUIComponent* GetComponent( _GUI_OBJECT_STATE state, AStringPtr name ) PURE;

	//!	Check whether has component.
	//!	@param		name	The component's name.
	//!	@return		True indicates has specified component.
	virtual _ubool HasComponent( _GUI_OBJECT_STATE state, AStringPtr name ) const PURE;
	//!	Check whether has component.
	//!	@param		state	The object state.
	//!	@param		name	The component's name.
	//!	@return		True indicates has specified component.
	virtual _ubool HasComponent( AStringPtr name ) const PURE;

	//!	Check whether has component or not.
	virtual _ubool HasComponents( const AStringArray& components ) const PURE;

	//!	Find component by name.
	//!	@remark		Just find it, never create it.
	//!	@param		name	The component's name.
	//!	@return		The GUI component interface.
	virtual IGUIComponent* FindComponent( AStringPtr name ) PURE;
	//!	Find component by name.
	//!	@remark		Just find it, never create it.
	//!	@param		name	The component's name.
	//!	@return		The GUI component interface.
	virtual const IGUIComponent* FindComponent( AStringPtr name ) const PURE;
	//!	Find component by name.
	//!	@remark		Just find it, never create it.
	//!	@param		state	The object state.
	//!	@param		name	The component's name.
	//!	@return		The GUI component interface.
	virtual IGUIComponent* FindComponent( _GUI_OBJECT_STATE state, AStringPtr name ) PURE;
	//!	Find component by name.
	//!	@remark		Just find it, never create it.
	//!	@param		state	The object state.
	//!	@param		name	The component's name.
	//!	@return		The GUI component interface.
	virtual const IGUIComponent* FindComponent( _GUI_OBJECT_STATE state, AStringPtr name ) const PURE;

	//!	Create component by name.
	//!	@param		name	The component's name.
	//!	@return		The GUI component interface.
	virtual IGUIComponent* CreateComponent( AStringPtr name ) PURE;
	//!	Remove component by name.
	//!	@param		state	The object state.
	//!	@param		name	The component's name.
	//!	@return		True indicates remove successful.
	virtual _ubool RemoveComponent( _GUI_OBJECT_STATE state, AStringPtr name ) PURE;
	//!	Remove component by name with all states.
	//!	@param		name	The component's name.
	//!	@return		True indicates remove successful.
	virtual _ubool RemoveComponent( AStringPtr name ) PURE;
	//!	Remove component by state.
	//!	@param		state	The object state.
	//!	@return		True indicates remove successful.
	virtual _ubool RemoveComponent( _GUI_OBJECT_STATE state ) PURE;
	//!	Remove all components.
	//!	@param		none.
	//!	@return		none.
	virtual _void RemoveAllComponents( ) PURE;
	//!	Remove all external components.
	//!	@param		none.
	//!	@return		none.
	virtual _void RemoveAllExternalComponents( ) PURE;

	//!	Move component up.
	//!	@param		state	The object state.
	//!	@param		name	The component's name.
	//!	@return		True indicates remove successful.
	virtual _ubool MoveUpComponent( _GUI_OBJECT_STATE state, AStringPtr name ) PURE;
	//!	Move component down.
	//!	@param		state	The object state.
	//!	@param		name	The component's name.
	//!	@return		True indicates remove successful.
	virtual _ubool MoveDownComponent( _GUI_OBJECT_STATE state, AStringPtr name ) PURE;
	//!	Move component.
	//!	@param		state	The object state.
	//!	@param		name	The component's name.
	//!	@param		index	The component's index.
	//!	@return		True indicates remove successful.
	virtual _ubool MoveComponent( _GUI_OBJECT_STATE state, AStringPtr name, _dword index ) PURE;
	//!	Move component.
	//!	@param		component	The component interface.
	//!	@param		index		The component's index.
	//!	@return		True indicates remove successful.
	virtual _ubool MoveComponent( IGUIComponent* component, _dword index ) PURE;

	//!	Get components number.
	//!	@param		none.
	//!	@return		The components number.
	virtual _dword GetComponentsNumber( ) const PURE;
	//!	Get components number.
	//!	@param		state	The object state.
	//!	@return		The components number.
	virtual _dword GetComponentsNumber( _GUI_OBJECT_STATE state ) const PURE;
	//!	Get component by index.
	//!	@param		index	The component's index.
	//!	@return		The component interface.
	virtual IGUIComponent* GetComponentByIndex( _dword index ) PURE;
	//!	Get index of component.
	//!	@param		component	The component interface.
	//!	@return		The component's index.
	virtual _dword GetComponentIndex( IGUIComponent* component ) const PURE;
	//!	Get index of component.
	//!	@param		state	The object state.
	//!	@param		name	The component's name.
	//!	@return		The component's index.
	virtual _dword GetComponentIndex( _GUI_OBJECT_STATE state, AStringPtr name ) const PURE;

protected:
	//!	Get the component name.
	template< typename Type >
	AStringPtr GetComponentNameT( ) const
	{
		AStringPtr class_name = Type::Name( );

		// Make sure the first character is 'I' ( means interface )
		EGE_ASSERT( class_name[0] == 'I' );

		// Get the component without the first character
		return class_name.SubString( 1 );
	}

public:
	//!	Check whether has component by static cast way.
	//!	@param		none.
	//!	@return		True indicates has component.
	template< typename Type >
	_ubool HasComponentT( )
	{
		return HasComponent( GetComponentNameT< Type >( ) );
	}
	//!	Check whether has component by static cast way.
	//!	@param		state	The object state.
	//!	@return		True indicates has component.
	template< typename Type >
	_ubool HasComponentT( _GUI_OBJECT_STATE state )
	{
		return HasComponent( state, GetComponentNameT< Type >( ) );
	}

	//!	Get component by static cast way.
	//!	@param		none.
	//!	@return		The GUI component interface.
	template< typename Type >
	Type* GetComponentT( )
	{
		return (Type*) GetComponent( GetComponentNameT< Type >( ) );
	}
	//!	Get component by static cast way.
	//!	@param		state	The object state.
	//!	@return		The GUI component interface.
	template< typename Type >
	Type* GetComponentT( _GUI_OBJECT_STATE state )
	{
		return (Type*) GetComponent( state, GetComponentNameT< Type >( ) );
	}

	//!	Find component by static cast way.
	//!	@param		none.
	//!	@return		The GUI component interface.
	template< typename Type >
	Type* FindComponentT( )
	{
		return (Type*) FindComponent( GetComponentNameT< Type >( ) );
	}
	//!	Find component by static cast way.
	//!	@param		none.
	//!	@return		The GUI component interface.
	template< typename Type >
	const Type* FindComponentT( ) const
	{
		return (const Type*) FindComponent( GetComponentNameT< Type >( ) );
	}
	//!	Find component by static cast way.
	//!	@param		state	The object state.
	//!	@return		The GUI component interface.
	template< typename Type >
	Type* FindComponentT( _GUI_OBJECT_STATE state )
	{
		return (Type*) FindComponent( state, GetComponentNameT< Type >( ) );
	}
	//!	Find component by static cast way.
	//!	@param		state	The object state.
	//!	@return		The GUI component interface.
	template< typename Type >
	const Type* FindComponentT( _GUI_OBJECT_STATE state ) const
	{
		return (const Type*) FindComponent( state, GetComponentNameT< Type >( ) );
	}

	//!	Create component by static cast way.
	//!	@param		none.
	//!	@return		The GUI component interface.
	template< typename Type >
	Type* CreateComponentT( )
	{
		return (Type*) CreateComponent( GetComponentNameT< Type >( ) );
	}
};

}