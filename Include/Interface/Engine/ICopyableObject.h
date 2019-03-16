//! @file     ICopyableObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ICopyableObject
//----------------------------------------------------------------------------

template< typename CopyInterfaceType, typename Type >
class ICopyableObject : public Type
{
public:
	//!	Copy from other resource.
	//!	@param		src_object	The source resource.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool CopyFrom( const CopyInterfaceType* src_object ) PURE;
};

}