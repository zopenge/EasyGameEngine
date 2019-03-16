//! @file     BulletDebugDrawer.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

#if (_PHYSX_USE_BULLET_ == 1)

//----------------------------------------------------------------------------
// BulletDebugDrawer Implementation
//----------------------------------------------------------------------------

BulletDebugDrawer::BulletDebugDrawer( )
{
}

BulletDebugDrawer::~BulletDebugDrawer( )
{

}

void BulletDebugDrawer::reportErrorWarning( const char* warning_string )
{
	ALOG_ERROR( warning_string );
}

void BulletDebugDrawer::setDebugMode( int debug_mode )
{
	mRenderer->SetDebugMode( (_dword) debug_mode );
}

int	BulletDebugDrawer::getDebugMode( ) const
{
	return mRenderer->GetDebugMode( );
}

void BulletDebugDrawer::drawLine( const btVector3& from, const btVector3& to, const btVector3& color )
{
	mRenderer->DrawLine( BulletHelper::BTVec3ToVec3( from ), BulletHelper::BTVec3ToVec3( to ), BulletHelper::BTVec3ToColor( color ) );
}

void BulletDebugDrawer::drawContactPoint( const btVector3& pos, const btVector3& normal, btScalar distance, int life_time, const btVector3& color )
{
	btVector3 to = pos + normal * distance;

	drawLine( pos, to, color );
}

void BulletDebugDrawer::draw3dText( const btVector3& location, const char* text_string )
{
	mRenderer->DrawText( BulletHelper::BTVec3ToVec3( location ), text_string );
}

#endif