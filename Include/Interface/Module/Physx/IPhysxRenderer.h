//! @file     IPhysxRenderer.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IPhysxRenderer
//----------------------------------------------------------------------------

class IPhysxRenderer : public IObject
{
public:
	//!	Set debug mode.
	//!	@param		mode		The debug mode, @see _PHYSX_DEBUG_DRAWER_FLAG.
	//!	@return		none.
	virtual _void SetDebugMode( _dword mode ) PURE;
	//!	Get debug mode.
	//!	@param		none.
	//!	@return		The debug mode, @see _PHYSX_DEBUG_DRAWER_FLAG.
	virtual const FlagsObject& GetDebugMode( ) const PURE;

	//!	Draw line.
	//!	@param		p1			The point 1.
	//!	@param		p2			The point 2.
	//!	@param		color		The line color.
	//!	@return		none.
	virtual _void DrawLine( const Vector3& p1, const Vector3& p2, const Color& color ) PURE;

	//!	Draw text.
	//!	@param		position	The position
	//!	@param		string		The drawing string.
	//!	@return		none.
	virtual _void DrawText( const Vector3& position, AStringPtr string ) PURE;

	//!	Begin.
	//!	@param		none.
	//!	@return		none.
	virtual _void Begin( ) PURE;
	//!	End.
	//!	@param		none.
	//!	@return		none.
	virtual _void End( ) PURE;
};

}