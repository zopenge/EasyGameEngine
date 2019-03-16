//! @file     ResCaches.cpp
//! @author   LiCode
//! @version  
//! @date     2012/05/15
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// ResCaches Implementation
//----------------------------------------------------------------------------

ResCaches::ResCaches( )
{
}

ResCaches::~ResCaches( )
{
}

_void ResCaches::Clear( )
{
	mCaches.Clear( );
}

_void ResCaches::SetDefaultResObj( IResObject* res_obj )
{
	if ( res_obj == _null )
		return;

	_dword res_type = res_obj->GetInterfaceTypeID( );

	mDefaultResObjects[res_type][res_obj->GetResName( )] = res_obj;

	if ( mDefaultResObjectsOfType.HasKey( res_type ) == _false )
		mDefaultResObjectsOfType[res_type] = res_obj;
}

_void ResCaches::SetDefaultResObjOfType( IResObject* res_obj )
{
	if ( res_obj == _null )
		return;

	mDefaultResObjectsOfType[res_obj->GetInterfaceTypeID( )] = res_obj;
}

IResObject*	ResCaches::GetDefaultResObj( _dword res_type, const WStringObj& res_name )
{
	return mDefaultResObjects[res_type][res_name];
}

IResObject*	ResCaches::GetDefaultResObjOfType( _dword res_type )
{
	return mDefaultResObjectsOfType[res_type];
}

_ubool ResCaches::HasResObject( _dword res_type, const WStringObj& res_name ) const
{
	const IResObjectRefMapWithName* res_with_names = mCaches.Search( res_type );
	if ( res_with_names == _null )
		return _false;

	if ( res_with_names->HasKey( res_name ) == _false )
		return _false;

	return _true;
}

_void ResCaches::AddResObject( IResObject* res_obj )
{
	if ( res_obj == _null )
		return;

	_dword				res_type = res_obj->GetInterfaceTypeID( );
	const WStringObj&	res_name = res_obj->GetResName( );

	mCaches[res_type][res_name] = res_obj;
}

_void ResCaches::RemoveResObject( _dword res_type, const WStringObj& res_name )
{
	IResObjectRefMapWithName* res_with_names = mCaches.Search( res_type );
	if ( res_with_names == _null )
		return;

	res_with_names->Remove( res_name );
}

IResObject* ResCaches::GetResObject( _dword res_type, const WStringObj& res_name )
{
	IResObject* res_obj = mCaches[res_type][res_name];
	if ( res_obj == _null )
		return _null;

	return res_obj;
}

Array< IResObjectRef > ResCaches::GetResObjCaches( _dword res_type ) const
{
	Array< IResObjectRef > res_objs;

	const IResObjectRefMapWithName* res_with_names = mCaches.Search( res_type );
	if ( res_with_names != _null )
	{
		for ( IResObjectRefMapWithName::Iterator it = res_with_names->GetHeadIterator( ); it.IsValid( ); ++ it )
			res_objs.Append( it.GetObject( ) );
	}

	return res_objs;
}
