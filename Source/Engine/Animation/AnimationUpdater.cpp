#include "EGEEngine.h"

AnimationUpdater::AnimationUpdater( )
{

}

AnimationUpdater::~AnimationUpdater( )
{

}

IAnimationInfoPassRef AnimationUpdater::_NewInfo( )
{
	return GetInterfaceFactory( )->CreateAnimationInfo( );
}