
#pragma once

namespace EGE
{
	class IAnimationUpdater : public ITAnimationUpdater< IAnimationUpdater, IAnimationInfo >
	{
	public:
		//----------------------------------------------------------------------------
		// AnimationUpdateData
		//----------------------------------------------------------------------------
		struct AnimationUpdateData
		{
		public:
			Vector2*	mResultOffset;
			Vector2*	mResultScale;
			_float*		mResultRotation;
			Color*		mResultColor;
			_qword*		mResultZsort;
		public:
			AnimationUpdateData( )
				: mResultOffset( _null )
				, mResultScale( _null )
				, mResultRotation( _null )
				, mResultColor( _null )
				, mResultZsort( _null )
			{

			}

			AnimationUpdateData( Vector2* offset, Vector2* scale, _float* rotation, Color* color, _qword* zsort )
				: mResultOffset( offset )
				, mResultScale( scale )
				, mResultRotation( rotation )
				, mResultColor( color )
				, mResultZsort( zsort )
			{

			}
		};
	};
}