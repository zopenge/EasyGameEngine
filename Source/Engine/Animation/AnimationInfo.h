
#pragma once

namespace EGE
{
	class AnimationInfo : public TAnimationInfo< IAnimationInfo, IAnimationKeyFrame >
	{
	private:
		typedef TAnimationInfo< IAnimationInfo, IAnimationKeyFrame >	BaseClass;

	public:
		AnimationInfo( );
		virtual ~AnimationInfo( );

	protected:
		virtual IAnimationKeyFramePassRef								_NewKeyFrame( ) override;
	};
}