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
};

}