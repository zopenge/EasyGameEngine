
#pragma once

namespace EGE
{
	typedef Array<IAnimationKeyFrameRef>			AnimationKeyFrameArray;

	class IAnimationInfo : public ITAnimationInfo< IAnimationInfo, IAnimationKeyFrame >
	{

	};
}