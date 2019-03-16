//! @file     ITScrollableObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ITScrollableObject
//----------------------------------------------------------------------------

template< typename Type >
class ITScrollableObject : public Type
{
public:
	//!	Scroll by x-position.
	//!	@param		position	The position.
	//!	@return		none.
	virtual _void ScrollX( _int position ) PURE;
	//!	Scroll by y-position.
	//!	@param		position	The position.
	//!	@return		none.
	virtual _void ScrollY( _int position ) PURE;
	//!	Get the current scroll x-position.
	//!	@param		none.
	//!	@return		The scroll position.
	virtual _int GetScrollPositionX( ) PURE;
	//!	Get the current scroll y-position.
	//!	@param		none.
	//!	@return		The scroll position.
	virtual _int GetScrollPositionY( ) PURE;
	//!	Get the scroll width.
	//!	@param		none.
	//!	@return		The scroll width.
	virtual _int GetScrollWidth( ) PURE;
	//!	Get the scroll height.
	//!	@param		none.
	//!	@return		The scroll height.
	virtual _int GetScrollHeight( ) PURE;
};

}