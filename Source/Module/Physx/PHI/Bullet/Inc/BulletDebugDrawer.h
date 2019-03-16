//! @file     BulletDebugDrawer.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// BulletDebugDrawer
//----------------------------------------------------------------------------

class BulletDebugDrawer : public btIDebugDraw
{
private:
	//!	The physx renderer
	IPhysxRendererRef	mRenderer;

public:
	BulletDebugDrawer( );
	virtual ~BulletDebugDrawer( );

public:
	EGE_SET_ACCESSOR( IPhysxRenderer*, Renderer )

// btIDebugDraw Interface
public:
	virtual void	reportErrorWarning( const char* warning_string ) override;

	virtual void	setDebugMode( int debug_mode ) override;
	virtual int		getDebugMode( ) const override;

	virtual void	drawLine( const btVector3& from, const btVector3& to, const btVector3& color ) override;
	virtual void	drawContactPoint( const btVector3& pos, const btVector3& normal, btScalar distance, int life_time, const btVector3& color ) override;
	virtual void	draw3dText( const btVector3& location, const char* text_string ) override;
};

}