#pragma once

namespace EGE
{

	template< typename Type, typename KeyFrame >
	class ITAnimationInfo : public ISerializable
	{
	protected:
		typedef	RefPtr< KeyFrame >					KeyFrameRef;
		typedef Array< KeyFrameRef >				KeyFrameArray;

	public:
		virtual WStringPtr							GetName( ) const PURE;
		virtual _ANIMATION_MODE						GetAnimationMode( ) const PURE;
		virtual _ANIMATION_DIRECTION				GetAnimationDirection( ) const PURE;
		virtual KeyFrameRef							GetKeyFrameByTime( _dword time ) const PURE;
		virtual KeyFrameRef							GetKeyFrameByTimeLowerBound( _dword time ) const PURE;
		virtual KeyFrameRef							GetKeyFrameByTimeUpperBound( _dword time ) const PURE;
		virtual KeyFrameRef							PrevKeyFrame( KeyFrame* keyframe ) const PURE;
		virtual KeyFrameRef							NextKeyFrame( KeyFrame* keyframe ) const PURE;
		virtual const KeyFrameArray&				GetKeyFrameArray( ) const PURE;

		virtual _void								SetName( WStringPtr name ) PURE;
		virtual _void								SetAnimationMode( _ANIMATION_MODE mode ) PURE;
		virtual _void								SetAnimationDirection( _ANIMATION_DIRECTION dirction ) PURE;
		virtual _ubool								AddKeyFrame( KeyFrame* keyframe ) PURE;
		virtual _void								ClearKeyFrames( ) PURE;
		virtual _void								RemoveKeyFrameByIndex( _dword index ) PURE;
		virtual _ubool								RemoveKeyFrameByTime( _dword time ) PURE;

		virtual _ubool								CloneFrom( const Type* srctrack ) PURE;
	};

}