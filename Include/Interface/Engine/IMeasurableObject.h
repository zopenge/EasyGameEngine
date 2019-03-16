//! @file     IMeasurableObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IMeasurableObject
//----------------------------------------------------------------------------

class IMeasurableObject : public IObject
{
public:
	//!	Set the line number.
	//!	@param		number	The line number.
	//!	@return		none.
	virtual _void SetLineNumber( _dword number ) PURE;
	//!	Get the line number.
	//!	@param		none.
	//!	@return		The line number.
	virtual _dword GetLineNumber( ) const PURE;

	//!	Get the region of object.
	//!	@param		none.
	//!	@return		The object region.
	virtual RectF GetRegion( ) const PURE;

	//!	Get the left coordinate of object.
	//!	@param		none.
	//!	@return		The coordinate.
	virtual _float GetLeft( ) const PURE;
	//!	Get the bottom coordinate of object.
	//!	@param		none.
	//!	@return		The coordinate.
	virtual _float GetBottom( ) const PURE;
	//! Get the base line height.
	//! @param		none.
	//! @return		The base line height.
	virtual _float GetBaseLineHeight( ) const PURE;

	//! Get object position.
	//! @param		none.
	//! @return		The object position
	virtual Vector2 GetPosition( ) const PURE;
	//! Set object position.
	//! @param		pos		The position.
	//! @return		none.
	virtual _void SetPosition( const Vector2& pos ) PURE;

	//! Get space between two measurable object.
	//!	@param		none.
	//!	@return		The space contains x or y spaces.
	virtual _float GetSpace( ) const PURE;

	//!	Check whether it's word separator tag.
	//!	@param		none.
	//!	@return		True indicates it's word separator tag.
	virtual _ubool IsWordSeparatorTag( ) const PURE;
	//!	Check whether it's new line tag or not.
	//!	@param		none.
	//!	@return		True indicates it's new line tag, need to start a new line.
	virtual _ubool IsNewLineTag( ) const PURE;
};

}