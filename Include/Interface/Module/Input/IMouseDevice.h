//! @file     IMouseDevice.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// MouseData
//----------------------------------------------------------------------------

struct MouseData
{
	PointI		mPosition;
	PointI		mDeltaPosition;

	_boolean	mLButton;
	_boolean	mMButton;
	_boolean	mRButton;
	_boolean	mReserved;

	_long		mWheel;
};

//----------------------------------------------------------------------------
// IMouseDevice
//----------------------------------------------------------------------------

class IMouseDevice : public IInputDevice
{
public:
	//!	Get mouse data.
	//! @param		none.
	//! @return		The data of mouse.
	virtual const MouseData& GetMouseData( ) const PURE;
};

}