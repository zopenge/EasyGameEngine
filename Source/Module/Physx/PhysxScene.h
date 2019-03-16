//! @file     PhysxScene.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// PhysxScene
//----------------------------------------------------------------------------

class PhysxScene : public INTERFACE_OBJECT_IMPL( IPhysxScene )
{
private:
	typedef Array< IPhysxBodyRef > PhysxBodyArray;

private:
	//!	The scene resource
	ScenePHIRef			mSceneResource;

	//!	The soft world info
	PhysxSoftWorldInfo*	mSoftWorldInfo;

	//!	The bodies
	PhysxBodyArray		mPhysxBodies;

private:

public:
	PhysxScene( ScenePHI* scene );
	virtual ~PhysxScene( );

public:
	//!	Initialize.
	_ubool Initialize( );

// IObject Interface
public:
	virtual _void					Tick( _dword limited_elapse, _dword elapse ) override;

// IPhysxScene Interface
public:
	virtual IPhysxSoftWorldInfoRef	GetSoftWorldInfo( ) override;

	virtual _void					Render( IPhysxRenderer* renderer ) override;

	virtual _void					AddBody( IPhysxBody* body ) override;
	virtual _void					RemoveBody( IPhysxBody* body ) override;
};

//----------------------------------------------------------------------------
// PhysxScene Implementation
//----------------------------------------------------------------------------

}