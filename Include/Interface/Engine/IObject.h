//! @file     IObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IObject
//----------------------------------------------------------------------------

class IObject
{
public:
	//!	Get the interface type ID.
	//!	@param		none.
	//!	@return		The interface type name.
	virtual _dword GetInterfaceTypeID( ) const PURE;
	//!	Get the interface type name.
	//!	@param		none.
	//!	@return		The interface type name.
	virtual const AStringObj& GetInterfaceTypeNameA( ) const PURE;
	//!	Get the interface type name.
	//!	@param		none.
	//!	@return		The interface type name.
	virtual const WStringObj& GetInterfaceTypeNameW( ) const PURE;

	//!	Get the class type ID.
	//!	@param		none.
	//!	@return		The class type ID.
	virtual _dword GetClassTypeID( ) const PURE;
	//!	Get the class type name.
	//!	@param		none.
	//!	@return		The class type name.
	virtual const AStringObj& GetClassTypeNameA( ) const PURE;
	//!	Get the class type name.
	//!	@param		none.
	//!	@return		The class type name.
	virtual const WStringObj& GetClassTypeNameW( ) const PURE;

	//!	Clone self and all sub-items.
	//!	@param		standalone	True indicates create in standalone mode.
	//!	@return		The new object.
	virtual IObject* CloneTo( _ubool standalone ) const PURE;
	//!	Clone self and all sub-items with arguments.
	//!	@param		arguments	The arguments.
	//!	@param		standalone	True indicates create in standalone mode.
	//!	@return		The new object.
	virtual IObject* CloneTo( _void* arguments, _ubool standalone ) const PURE;

	//!	Copy from other.
	//!	@param		obj			The object.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool CopyFrom( const IObject* obj ) PURE;

	//!	Update.
	//! @param		limited_elapse	The millisecond time of the animation update interval.
	//! @param		elapse			The millisecond time of the update interval.
	//! @return		none.
	virtual _void Tick( _dword limited_elapse, _dword elapse ) PURE;
	//!	Update by frame.
	//! @param		frame		The frame number, starts from 1.
	//! @return		none.
	virtual _void FrameTick( _dword frame ) PURE;

	//!	Delete without garbage collector.
	//!	@param		none.
	//!	@return		none.
	virtual _void DeleteThis( ) PURE;
	//!	Uninitialize.
	//!	@remark		We should it to unload some resources before delete.
	//!	@param		none.
	//!	@return		none.
	virtual _void Uninitialize( ) PURE;

	//!	Get the reference count.
	//!	@param		none.
	//!	@return		The reference count.
	virtual _dword GetRefCount( ) const PURE;
	//!	Increments the reference count for an interface on an object. This method should be called for every new copy of a pointer to an interface on an object.
	//!	@param		none.
	//!	@return		The new reference count. This value is intended to be used only for test purposes.
	virtual _dword AddRef( ) PURE;
	//!	Decrements the reference count for an interface on an object.
	//!	@param		none.
	//!	@return		The new reference count. This value is intended to be used only for test purposes.
	virtual _dword Release( ) PURE;

public:
	//!	Clone self and all sub-items as pass referenced pointer.
	//!	@param		standalone	True indicates create in standalone mode.
	//!	@return		The new object as pass referenced pointer.
	template< typename Type >
	PassRefPtr< Type > CloneToPassRef( _ubool standalone ) const
	{
		Type* object = (Type*) CloneTo( standalone );
		return object;
	}
	//!	Clone self and all sub-items as pass referenced pointer with arguments.
	//!	@param		arguments	The arguments.
	//!	@param		standalone	True indicates create in standalone mode.
	//!	@return		The new object as pass referenced pointer.
	template< typename Type >
	PassRefPtr< Type > CloneToPassRef( _void* arguments, _ubool standalone ) const
	{
		Type* object = (Type*)CloneTo( arguments, standalone );
		return object;
	}
};

//----------------------------------------------------------------------------
// IObject
//----------------------------------------------------------------------------

}