//! @file     IPhysxScene.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IPhysxScene
//----------------------------------------------------------------------------

class IPhysxScene : public IObject
{
public:
	//!	Get the soft world info.
	//!	@param		none.
	//!	@return		The soft world info.
	virtual IPhysxSoftWorldInfoRef GetSoftWorldInfo( ) PURE;

	//!	Render scene.
	//!	@param		renderer	The physx renderer.
	//!	@return		none.
	virtual _void Render( IPhysxRenderer* renderer ) PURE;

	//!	Add the body and add it into scene.
	//!	@param		body		The body interface.
	//!	@return		none.
	virtual _void AddBody( IPhysxBody* body ) PURE;
	//!	Remove the body from scene.
	//!	@param		body		The body interface.
	//!	@return		none.
	virtual _void RemoveBody( IPhysxBody* body ) PURE;
};

}