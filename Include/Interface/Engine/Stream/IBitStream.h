//! @file     IBitStream.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IBitStream
//----------------------------------------------------------------------------

template< typename Type >
class IBitStream : public Type
{
public:
	//!	Seek padded section data.
	//!	@param		none.
	//!	@return		none.
	virtual _void SeekPaddedSection( ) PURE;
	//!	Seek bits.
	//!	@param		bits	The bits number.
	//!	@return		none.
	virtual _void SeekBits( _dword bits ) PURE;
};

}