//! @file     IResLoader.h
//! @author   LiCode
//! @version  
//! @date     2012/05/15
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IResLoader
//----------------------------------------------------------------------------

class IResLoader : public IObject
{
public:
	//!	Check whether it's busy.
	//!	@param		none.
	//!	@return		True indicates it's busy.
	virtual _ubool IsBusy( ) const PURE;

	//!	Check whether group has complete.
	//!	@param		none.
	//!	@return		True indicates has complete.
	virtual _ubool HasComplete( ) const PURE;

	//! Get the factory.
	//!	@param		none.
	//!	@return		The factory.
	virtual IResLoaderFactory* GetFactory( ) PURE;

	//!	Lock.
	//!	@param		none.
	//!	@return		none.
	virtual _void EnterLock( ) PURE;
	//!	Unlock.
	//!	@param		none.
	//!	@return		none.
	virtual _void LeaveLock( ) PURE;

	//!	Start.
	//!	@param		none.
	//! @return		none.
	virtual _void Start( ) PURE;
	//!	Suspend.
	//!	@param		suspend			True indicates suspend it.
	//! @return		none.
	virtual _void Suspend( _ubool suspend ) PURE;

	//!	Set default resource object.
	//!	@param		res_obj			The default resource object.
	//! @return		none.
	virtual _void SetDefaultResObj( IResObject* res_obj ) PURE;
	//!	Set default resource object for type.
	//!	@param		res_obj			The default resource object.
	//! @return		none.
	virtual _void SetDefaultResObjOfType( IResObject* res_obj ) PURE;
	//!	Get default resource object.
	//!	@param		res_type		The resource type.
	//!	@param		res_name		The resource name.
	//! @return		The default resource object.
	virtual IResObject* GetDefaultResObj( _dword res_type, const WStringObj& res_name ) PURE;

	//!	Get cached resource object.
	//!	@param		res_type		The resource type.
	//!	@param		res_name		The resource name.
	//! @return		The resource object.
	virtual IResObjectRef GetCachedResObj( _dword res_type, const WStringObj& res_name ) PURE;

	//!	Create resource object.
	//!	@param		res_type		The resource type.
	//!	@param		res_name		The resource name.
	//! @return		The resource object.
	virtual IResObjectPassRef CreateResObj( _dword res_type, const WStringObj& res_name ) PURE;
	//!	Add resource task.
	//!	@param		res_type		The resource type.
	//!	@param		res_name		The resource name.
	//! @return		True indicates it's existing task.
	virtual _ubool LoadResObj( _dword res_type, const WStringObj& res_name ) PURE;
	//!	Unload resource object.
	//!	@param		res_type		The resource type.
	//!	@param		res_name		The resource name.
	//! @return		none.
	virtual _void UnloadResObj( _dword res_type, const WStringObj& res_name ) PURE;
	//!	Bring resource task up to high priority.
	//!	@param		res_type		The resource type.
	//!	@param		res_name		The resource name.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool BringUpResObj( _dword res_type, const WStringObj& res_name ) PURE;
	//!	Stop all resource objects loading.
	//!	@param		none.
	//! @return		none.
	virtual _void StopAllResObjsLoading( ) PURE;

	//!	Get caches.
	//!	@param		res_type		The resource type.
	//!	@return		The resource object caches.
	virtual Array< IResObjectRef > GetResObjCaches( _dword res_type ) const PURE;

	//!	Get the tasks progression.
	//!	@param		none.
	//!	@return		The tasks progression.
	virtual DwordProgression GetTaskProgression( ) const PURE;

public:
	//!	Create resource object.
	//!	@param		res_name		The resource name.
	//! @return		The resource object.
	template< typename Type >
	PassRefPtr< Type > CreateResObj( const WStringObj& res_name )
	{
		STATIC_ASTROBJ_V( class_name, typeid( Type ).name( ) );

		return CreateResObj( ASTROBJ( class_name ).GetID( ), res_name );
	}

	//!	Get caches.
	//!	@param		res_type		The resource type.
	//!	@return		The resource object caches.
	template< typename Type >
	Array< RefPtr< Type > > GetResObjCaches( ) const
	{
		STATIC_ASTROBJ_V( class_name, typeid( Type ).name( ) );

		Array< IResObjectRef > res_objs = GetResObjCaches( ASTROBJ( class_name ).GetID( ) );

		Array< RefPtr< Type > > to_res_objs;
		to_res_objs.Resize( res_objs.Number( ) );
		for ( _dword i = 0; i < res_objs.Number( ); i ++ )
			to_res_objs.Append( res_objs[i].cast_static< Type >( ) );

		return to_res_objs;
	}
};

}