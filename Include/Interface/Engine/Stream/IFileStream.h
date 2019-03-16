//! @file     IFileStream.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IFileStream
//----------------------------------------------------------------------------

template< typename Type >
class IFileStream : public Type
{
public:
	//!	Get the file name.
	//!	@param		none.
	//!	@return		The file name.
	virtual WStringPtr GetFileName( ) const PURE;
};

}