//! @file     _luaObjResource.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

class _luaModule;

//----------------------------------------------------------------------------
// _luaObjResource
//----------------------------------------------------------------------------

class _luaObjResource
{
private:
	//!	The module
	_luaModule*	mModule;
	//!	The class name
	AStringObj	mName;

	//!	The class not inherit from IObject, use new/delete to allocate and free
	_byte*		mWrapClass;
	//!	The class inherit from IObject, use new/Release() to allocate and free
	IObjectRef	mWrapObject;

public:
	_luaObjResource( );
	~_luaObjResource( );

public:
	//!	Get the module.
	EGE_GET_ACCESSOR( _luaModule*, Module )
	//!	Get the wrap class.
	EGE_GET_ACCESSOR( _byte*, WrapClass )
	//!	Get the wrap object.
	EGE_GET_ACCESSOR( IObject*, WrapObject )

public:
	//!	Get the wrap object.
	_void* GetWrappedObject( );

	//! Initialize resource instance.
	_ubool InitInstance( );
	//!	Free resource instance.
	_void FreeInstance( );

	//!	Create class resource.
	_ubool CreateClassResource( );
};

//----------------------------------------------------------------------------
// _luaObjResource Implementation
//----------------------------------------------------------------------------

inline _void* _luaObjResource::GetWrappedObject( )
{
	return mWrapClass ? mWrapClass : (_byte*) mWrapObject.GetPtr( );
}

}