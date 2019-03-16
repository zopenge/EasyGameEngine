//! @file     ITVersionable.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ITVersionable
//----------------------------------------------------------------------------

template< typename Type >
class ITVersionable : public Type
{
public:
	//!	Set the version.
	//!	@param		version		The version.
	//!	@return		none.
	virtual _void SetVersion( const Version& version ) PURE;
	//!	Get the version.
	//!	@param		none.
	//!	@return		The version.
	virtual const Version& GetVersion( ) const PURE;
};

}