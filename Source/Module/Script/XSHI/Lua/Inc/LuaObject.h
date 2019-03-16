//! @file     LuaObject.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//!	The EGE objects' table
static const _chara* const sLuaObjectsTableName		= "EGE_LUA_Objects";
//!	The EGE references' table
static const _chara* const sLuaRefsTableName		= "EGE_LUA_References";
//!	The object meta-table name
static const _chara* const sLuaObjectMetaTableName	= "EGE_LUA_Object_Meta_Table";

//----------------------------------------------------------------------------
// LuaObject
//----------------------------------------------------------------------------

template< class Type >
class LuaObject : public Type
{
protected:
	//!	When garbage collector called.
	static _long OnGCCallback( lua_State* lua_state );

protected:
	//!	Initialize weak table.
	_void InitWeakTables( lua_State* lua_state );
	//!	Push weak tables.
	_void PushWeakTables( lua_State* lua_state );

	//!	Push meta table.
	_void PushMetaTable( lua_State* lua_state );

protected:
	//!	When push implementation.
	virtual _void OnPushImplementation( lua_State* lua_state ) PURE;

protected:
	LuaObject( );
	virtual ~LuaObject( );

public:
	//!	Push object.
	_void Push( lua_State* lua_state );
};

//----------------------------------------------------------------------------
// LuaObject Implementation
//----------------------------------------------------------------------------

template< class Type >
LuaObject< Type >::LuaObject( )
{
}

template< class Type >
LuaObject< Type >::~LuaObject( )
{

}

template< class Type >
_long LuaObject< Type >::OnGCCallback( lua_State* lua_state )
{
	LuaObject* object = *(LuaObject**) lua_touserdata( lua_state, 1 );
	EGE_ASSERT( object != _null );

	object->Release( );
	return 0;
}

template< class Type >
_void LuaObject< Type >::InitWeakTables( lua_State* lua_state )
{
	LuaStackBackup stack_backup( lua_state );

	// The weakness of a table is controlled by the __mode field of its metatable. 
	// If the __mode field is a string containing the character 'k', the keys in the table are weak. 
	// If __mode contains 'v', the values in the table are weak. 

	// Create a new objects' table
	lua_newtable( lua_state ); 
	// Make it weak(-value)
	lua_newtable( lua_state );
	lua_pushstring( lua_state, "v" );
	lua_setfield( lua_state, -2, "__mode" ); // weak_table[__mode] = "v"
	lua_setmetatable( lua_state, -2 );
	lua_setfield( lua_state, LUA_REGISTRYINDEX, sLuaObjectsTableName ); // Register as global table

	// Create new references' table
	lua_newtable( lua_state );
	// Make it weak(-key)
	lua_newtable( lua_state );
	lua_pushstring( lua_state, "k" );
	lua_setfield( lua_state, -2, "__mode" ); // weak_table[__mode] = "k"
	lua_setmetatable( lua_state, -2 );
	lua_setfield( lua_state, LUA_REGISTRYINDEX, sLuaRefsTableName ); // Register as global table
}

template< class Type >
_void LuaObject< Type >::PushWeakTables( lua_State* lua_state )
{
	// Get the table of objects
	lua_getfield( lua_state, LUA_REGISTRYINDEX, sLuaObjectsTableName );
	if ( lua_isnil( lua_state, -1 ) )
	{
		// We never initialize the weak tables
		lua_pop( lua_state, 1 ); // Remove nil

		// Initialize weak tables
		InitWeakTables( lua_state );

		// Register objects' weak table
		lua_getfield( lua_state, LUA_REGISTRYINDEX, sLuaObjectsTableName );
	}

	// Get reference's weak table
	lua_getfield( lua_state, LUA_REGISTRYINDEX, sLuaRefsTableName );
}

template< class Type >
_void LuaObject< Type >::PushMetaTable( lua_State* lua_state )
{
	// Get or crate a metatable for the reference of this
	if ( luaL_newmetatable( lua_state, sLuaObjectMetaTableName ) )
	{
		// Register the __gc function of this object
		lua_pushcfunction( lua_state, OnGCCallback );
		lua_setfield( lua_state, -2, "__gc" ); // set the gc func of the obj
	}
}

template< class Type >
_void LuaObject< Type >::Push( lua_State* lua_state )
{
	_long top = lua_gettop( lua_state );

	// Push weak tables
	PushWeakTables( lua_state );

	// Top + 1: objects' weak table 
	const _long objects_weak_table_index = top + 1;
	// Top + 2: references' weak table 
	const _long refs_weak_table_index = top + 2;

	// Find the object with our id
	lua_pushlightuserdata( lua_state, (_void*) this );
	lua_rawget( lua_state, objects_weak_table_index );

	// Check whether we push the implementation of this object or not
	if ( lua_isnil( lua_state, -1 ) )
	{
		// We never push the implementation, so need to push it
		lua_pop( lua_state, 1 ); // Remove nil

		// Get the position of user push implementation
		_long obj_pos = lua_gettop( lua_state ) + 1; 

		// Push the user implementation
		OnPushImplementation( lua_state ); // user's object table

		// The user should return one value only always ( return table )
		_long element_number = lua_gettop( lua_state ) - obj_pos + 1;
		if ( element_number == 0 || element_number > 1 ) 
		{
			luaL_error( lua_state, "Error on LuaObject::Push the current stack has %d elements and should have only one.", element_number );
			lua_settop( lua_state, top ); // Pop all elements
			return;
		}

		// Make objects[key] = value
		lua_pushlightuserdata( lua_state, (_void*) this ); // key
		lua_pushvalue( lua_state, obj_pos ); // copy of value
		lua_rawset( lua_state, objects_weak_table_index ); // objects[key] = value ( then pops both key and value )

		// Make refs[key] = meta-table
		lua_pushvalue( lua_state, obj_pos ); // push user's object table as key
		// Create a reference of this object
		*(LuaObject**) lua_newuserdata( lua_state, sizeof( LuaObject* ) ) = this;
		this->AddRef( );

		// Push meta-table of this
		PushMetaTable( lua_state );

		// Set the meta-table of reference object
		lua_setmetatable( lua_state, -2 ); 

		// Make references[obj] = reference
		lua_rawset( lua_state, refs_weak_table_index );

		// Here we should reach the user's object table in the top of stack
		EGE_ASSERT( lua_gettop( lua_state ) == obj_pos );
	}

	// Replace top of stack to the user's object table
	lua_replace( lua_state, objects_weak_table_index );
	lua_settop( lua_state, objects_weak_table_index );
}

}