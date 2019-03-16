//! @file     IClonableObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IClonableObject
//----------------------------------------------------------------------------

template< typename CloneInterfaceType, typename Type = CloneInterfaceType >
class IClonableObject : public Type
{
public:
	//!	Create and clone self.
	//!	@param		none.
	//!	@return		The new object.
	virtual PassRefPtr< CloneInterfaceType > CloneTo( ) const PURE;
	//!	Clone from other resource.
	//!	@param		src_object	The source resource.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool CloneFrom( const CloneInterfaceType* src_object ) PURE;
};

}