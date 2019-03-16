//! @file     TDynamicResObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TDynamicResObject
//----------------------------------------------------------------------------

template< typename Type >
class TDynamicResObject : public Type
{
protected:
	TDynamicResObject( );
	virtual ~TDynamicResObject( );

// IDynamicResObject Interface
public:
	virtual _void		UnloadResources( _ubool force, _ubool clear_cache ) override;
	virtual _void		ReloadResourcesInBackgroundThread( WStringPtr options, _ubool lock ) override;
	virtual _void		ReloadResourcesInMainThread( WStringPtr options, _ubool lock ) override;

	virtual _ubool		AreAllResourcesAvailable( ) const override;
	virtual DwordRange	GetResourcesLoadedProgression( ) const override;

	virtual _void		ImportResource( _dword res_type, WStringPtr res_name ) override;
	virtual _void		ExportResources( IDynamicResObject* cache_obj ) const override;

	virtual _void		LoadDelaySubResource( _dword res_type, WStringPtr res_name ) override;
	virtual _void		LoadDelaySubResources( IDynamicResObject* object, ISerializableNode* node ) const override;
};

//----------------------------------------------------------------------------
// TDynamicResObject Implementation
//----------------------------------------------------------------------------

template< typename Type >
TDynamicResObject< Type >::TDynamicResObject( )
{
}

template< typename Type >
TDynamicResObject< Type >::~TDynamicResObject( )
{
}

template< typename Type >
_void TDynamicResObject< Type >::UnloadResources( _ubool force, _ubool clear_cache )
{

}

template< typename Type >
_void TDynamicResObject< Type >::ReloadResourcesInBackgroundThread( WStringPtr options, _ubool lock )
{

}

template< typename Type >
_void TDynamicResObject< Type >::ReloadResourcesInMainThread( WStringPtr options, _ubool lock )
{

}

template< typename Type >
_ubool TDynamicResObject< Type >::AreAllResourcesAvailable( ) const
{
	return _true;
}

template< typename Type >
DwordRange TDynamicResObject< Type >::GetResourcesLoadedProgression( ) const
{
	// 100%
	return DwordRange( 0, 0 );
}

template< typename Type >
_void TDynamicResObject< Type >::ImportResource( _dword res_type, WStringPtr res_name )
{

}

template< typename Type >
_void TDynamicResObject< Type >::ExportResources( IDynamicResObject* cache_obj ) const
{

}

template< typename Type >
_void TDynamicResObject< Type >::LoadDelaySubResource( _dword res_type, WStringPtr res_name )
{

}

template< typename Type >
_void TDynamicResObject< Type >::LoadDelaySubResources( IDynamicResObject* object, ISerializableNode* node ) const
{

}

}