//! @file     IGraphicVRDevice.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicVRDevice
//----------------------------------------------------------------------------

class IGraphicVRDevice : public IGraphicScene
{
public:
	//!	Initialize.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Initialize( ) PURE;

	//!	Handle event.
	//!	@param		message		The message info.
	//!	@return		none.
	virtual _void HandleEvent( EventBase& event ) PURE;

	//!	Present to scene.
	//!	@param		none.
	//!	@return		none.
	virtual _void Present( ) PURE;

	//!	Get the eye distance from center.
	//!	@param		index		The eye index, 0 or 1.
	//!	@return		The eye distance.
	virtual _float GetEyeDistance( _dword index ) const PURE;
	//!	Get the eye info.
	//!	@param		index		The eye index, 0 or 1.
	//! @return		The eye info.
	virtual VREyeRHI GetEyeInfo( _dword index ) const PURE;
};

}