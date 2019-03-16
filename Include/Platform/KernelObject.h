//! @file     KernelObject.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// KernelObject
//----------------------------------------------------------------------------

//! This class is base class of all kernel object.
class KernelObject
{
	NO_COPY_OPERATIONS( KernelObject )

protected:
	//! The kernel object handle.
	_handle	mObjectHandle;

public:
	//! Constructor, create a kernel object attach to the object handle.
	//! @param		objecthandle	The kernel object handle.
	KernelObject( _handle objecthandle = _null );
	//! Destructor, delete the object and close the handle.
	//! @param		none
	~KernelObject( );

public:
	//! Type conversion, get the kernel object handle.
	//! @param		none
	//! @return		The object handle.
	inline operator _handle ( ) const;

public:
	//! Check the object handle whether it is valid.
	//!	@param		none.
	//!	@return		True indicates it's valid, false indicates it's invalid.
	_ubool IsValid( ) const;

	//! Close the object handle, decrements its reference count, and if the count is 0, then the kernel object is deleted.
	//! @param		none.
	//!	@return		none.
	_void Close( );
};

//----------------------------------------------------------------------------
// KernelObject Implementation
//----------------------------------------------------------------------------

KernelObject::operator _handle ( ) const
{
	return mObjectHandle;
}

}