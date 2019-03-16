//! @file     ResCaches.h
//! @author   LiCode
//! @version  
//! @date     2012/05/15
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ResCaches
//----------------------------------------------------------------------------

class ResCaches
{
private:
	//!	The resource object map
	typedef Map< IResObjectRef, WStringObj > IResObjectRefMapWithName;
	typedef Map< IResObjectRefMapWithName, _dword > IResObjectRefMapWithType;
	//!	The resource object array
	typedef Map< IResObjectRef, _dword > IResObjectRefArray;

private:
	IResObjectRefMapWithType	mCaches;

	//!	The default resource objects
	IResObjectRefMapWithType	mDefaultResObjects;
	IResObjectRefArray			mDefaultResObjectsOfType;

public:
	ResCaches( );
	~ResCaches( );

public:
	_void Clear( );

	_void SetDefaultResObj( IResObject* res_obj );
	_void SetDefaultResObjOfType( IResObject* res_obj );
	IResObject*	GetDefaultResObj( _dword res_type, const WStringObj& res_name );
	IResObject*	GetDefaultResObjOfType( _dword res_type );

	_ubool HasResObject( _dword res_type, const WStringObj& res_name ) const;
	_void AddResObject( IResObject* res_obj );
	_void RemoveResObject( _dword res_type, const WStringObj& res_name );
	IResObject* GetResObject( _dword res_type, const WStringObj& res_name );

	Array< IResObjectRef > GetResObjCaches( _dword res_type ) const;
};

//----------------------------------------------------------------------------
// ResCaches Implementation
//----------------------------------------------------------------------------

}