//! @file     _luaObjResource.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_LUA_ == 1)

//----------------------------------------------------------------------------
// _luaObjResource Implementation
//----------------------------------------------------------------------------

_luaObjResource::_luaObjResource( )
{
	mModule		= _null;
	mWrapClass	= _null;
}

_luaObjResource::~_luaObjResource( )
{
	FreeInstance( );
}

_ubool _luaObjResource::InitInstance( )
{
	return _true;
}

_void _luaObjResource::FreeInstance( )
{
	// It's class not inherit from IObject
	if ( mWrapClass != _null )
	{
		EGE_ASSERT( mWrapObject.IsNull( ) );

		// Call destructor to release it
		GetScriptResourceManager( )->InvokeDestructorBehaviourFunc( mWrapClass, mName.Str( ) );
	}
	// It's object inherit from IObject
	else if ( mWrapObject.IsValid( ) )
	{
		EGE_ASSERT( mWrapClass == _null );

		// Call Release( ) to decrease referenced counter
		mWrapObject.Clear( );
	}
}

_ubool _luaObjResource::CreateClassResource( )
{
	FreeInstance( );

	return GetScriptResourceManager( )->InvokeConstructorBehaviourFunc( mWrapClass, mName.Str( ) );
}

#endif