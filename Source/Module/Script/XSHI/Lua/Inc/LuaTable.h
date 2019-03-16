//! @file     LuaTable.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// LuaTable
//----------------------------------------------------------------------------

template< class Type >
class LuaTable : public LuaObject< Type >
{
protected:
	//!	The meta-table closure function.
	static _long __meta( lua_State* lua_state );

protected:
	//!	The table operation interface declaration.
	typedef _long (LuaTable::*TableOperationFunc)( lua_State* );

protected:
	//!	The table accesses operation proxy ( we wrap it for safe reason ).
	_long __indexProxy( lua_State* lua_state );

	//!	Push the meta-table closure function with table operation.
	_void PushMeta( lua_State* lua_state, TableOperationFunc funcpointer );

protected:
	//!	The table accesses operation.
	virtual _long __index( lua_State* lua_state );
	//!	The table updates operation.
	virtual _long __newindex( lua_State* lua_state );

	//!	The table call function operation.
	virtual _long __call( lua_State* lua_state );
	//!	The table garbage collection operation.
	virtual _long __garbage_collect( lua_State* lua_state );
	//!	The table convert to string operation.
	virtual _long __tostring( lua_State* lua_state );
	//!	The table comparison operation.
	virtual _long __eq( lua_State* lua_state );

// LuaObject Interface
protected:
	virtual _void OnPushImplementation( lua_State* lua_state ) override;

protected:
	LuaTable( );
	virtual ~LuaTable( );
};

//----------------------------------------------------------------------------
// LuaTable Implementation
//----------------------------------------------------------------------------

template< class Type >
LuaTable< Type >::LuaTable( )
{
}

template< class Type >
LuaTable< Type >::~LuaTable( )
{

}

template< class Type >
_long LuaTable< Type >::__meta( lua_State* lua_state )
{
	lua_gettop( lua_state );

	// Get the table self pointer
	LuaTable* table_raw = (LuaTable*) lua_touserdata( lua_state, lua_upvalueindex( 2 ) );
	EGE_ASSERT( table_raw != _null );

	// Get the table operation function pointer
	TableOperationFunc table_operation_func = *(TableOperationFunc*) lua_touserdata( lua_state, lua_upvalueindex( 3 ) );
	EGE_ASSERT( table_operation_func != _null );

	// Call it
	return (table_raw->*table_operation_func)( lua_state );
}

template< class Type >
_long LuaTable< Type >::__indexProxy( lua_State* lua_state )
{
	return __index( lua_state );
}

template< class Type >
_void LuaTable< Type >::PushMeta( lua_State* lua_state, TableOperationFunc funcpointer )
{
	// The top of stack should be a table
	EGE_ASSERT( lua_type( lua_state, -1 ) == LUA_TTABLE );

	// Push the table, self pointer and operation function pointer in order to bind it
	lua_pushvalue( lua_state, -1 ); // copy of table
	lua_pushlightuserdata( lua_state, (_void*) this );
	Platform::MemCpy( lua_newuserdata( lua_state, sizeof( TableOperationFunc ) ), &funcpointer, sizeof( TableOperationFunc ) );

	// Bind the table operation function with "__meta" static function with some userdata
	lua_pushcclosure( lua_state, __meta, 3 );
}

template< class Type >
_long LuaTable< Type >::__index( lua_State* lua_state )
{
	// First we try to find the LUA class from cache table
	lua_pushvalue( lua_state, 2 ); // key
	lua_rawget( lua_state, lua_upvalueindex( 1 ) );
	if ( lua_isnil( lua_state, -1 ) ) 
	{
		// The cache table has not LUA class info
		lua_pop( lua_state, 1 ); // remove nil
	}
	else
	{
		// We found it, and the top of stack is LUA class now
		return 1;
	}

	// It must be a name of class
	EGE_ASSERT( lua_type( lua_state, 2 ) == LUA_TSTRING );

	// Get the LUA class
	const _chara* class_name = lua_tostring( lua_state, 2 );
	EGE_ASSERT( class_name != _null );

	// Search for the LUA class by name
	LuaObject< Type >* lua_class = (LuaObject< Type >*) (ClassXSHI*) gDynamicXSHI->GetClassByName( class_name );
	if ( lua_class == _null )
	{
		luaL_error( lua_state, "The '%s' class is not existing", class_name );
		return -1;
	}

	// Push implementation
	lua_class->Push( lua_state );

	// Save to cache table
	lua_pushvalue( lua_state, 2 ); // key
	lua_pushvalue( lua_state, -2 ); // returned value
	lua_rawset( lua_state, lua_upvalueindex( 1 ) );

	return 1;
}

template< class Type >
_long LuaTable< Type >::__newindex( lua_State* lua_state )
{
	luaL_error( lua_state, "__newindex meta-method not implemented" );
	return 0;
}

template< class Type >
_long LuaTable< Type >::__call( lua_State* lua_state )
{
	luaL_error( lua_state, "__call meta-method not implemented" );
	return 0;
}

template< class Type >
_long LuaTable< Type >::__garbage_collect( lua_State* lua_state )
{
	luaL_error( lua_state, "__gc meta-method not implemented" );
	return 0;
}

template< class Type >
_long LuaTable< Type >::__tostring( lua_State* lua_state )
{
	//SLB_DEBUG_CALL;
	//SLB_DEBUG_STACK(10,L,"Table::__tostring (%p)",this);
	//int top = lua_gettop(L);
	//lua_pushfstring(L, "Table(%p) [%s] with keys:", this, typeInfo().name());
	//for(Elements::iterator i = _elements.begin(); i != _elements.end(); ++i)
	//{
	//	lua_pushfstring(L, "\n\t%s -> %p [%s]",i->first.c_str(), i->second.get(), i->second->typeInfo().name());
	//}
	//lua_concat(L, lua_gettop(L) - top);

	lua_pushfstring( lua_state, "unknown" );
	return 1;
}

template< class Type >
_long LuaTable< Type >::__eq( lua_State* lua_state )
{
	// Always return false in the base class
	lua_pushboolean( lua_state, _false );
	return 1;
}

template< class Type >
_void LuaTable< Type >::OnPushImplementation( lua_State* lua_state )
{
	// Create table and its meta-table
	lua_newtable( lua_state ); // an NEW empty table
	lua_newtable( lua_state ); // and its metatable

	// Set the metatable (empty) to the table to avoid calling __gc on the table itself. This is new in lua 5.2
	lua_pushvalue( lua_state, -1 );
	lua_setmetatable( lua_state, -3 ); // set table's meta-table

	// Create the cache table
	lua_newtable( lua_state );

	// "__indexCache" 
	//lua_pushvalue(L, -1); 
	//lua_setfield(L, -3, "__indexCache");

	// The meta-table index
	const _long meta_table_index = -3;

	// "__index"
	PushMeta( lua_state, &LuaTable::__indexProxy );
	lua_setfield( lua_state, meta_table_index, "__index" );
	// "__newindex"
	PushMeta( lua_state, &LuaTable::__newindex );
	lua_setfield( lua_state, meta_table_index, "__newindex" );
	// "__tostring"
	PushMeta( lua_state, &LuaTable::__tostring );
	lua_setfield( lua_state, meta_table_index, "__tostring" );
	// "__call"
	PushMeta( lua_state, &LuaTable::__call );
	lua_setfield( lua_state, meta_table_index, "__call" );
	// "__gc"
	PushMeta( lua_state, &LuaTable::__garbage_collect );
	lua_setfield( lua_state, meta_table_index, "__gc" );
	// "__eq"
	PushMeta( lua_state, &LuaTable::__eq );
	lua_setfield( lua_state, meta_table_index, "__eq" );

	// Remove the cache table and meta-table
	lua_pop( lua_state, 2 ); 
}

}