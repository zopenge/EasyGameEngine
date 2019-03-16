#pragma once

namespace EGE
{
	class AnimationUpdater : public TAnimationUpdater< IAnimationUpdater, IAnimationInfo, IAnimationKeyFrame >
	{
	private:
		typedef TAnimationUpdater< IAnimationUpdater, IAnimationInfo, IAnimationKeyFrame >	BaseClass;

	public:
		AnimationUpdater( );
		virtual ~AnimationUpdater( );

	protected:
		virtual IAnimationInfoPassRef							_NewInfo( ) override;
	};
}