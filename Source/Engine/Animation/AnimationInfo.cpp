#include "EGEEngine.h"


AnimationInfo::AnimationInfo( )
{

}

AnimationInfo::~AnimationInfo( )
{

}

IAnimationKeyFramePassRef AnimationInfo::_NewKeyFrame( )
{
	return GetInterfaceFactory( )->CreateAnimationKeyFrame( );
}