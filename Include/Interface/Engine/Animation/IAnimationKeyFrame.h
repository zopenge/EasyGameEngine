
#pragma once

namespace EGE
{
	class IAnimationKeyFrame : public ISerializable
	{
	public:
		virtual _float								GetKeyTime( ) const PURE;
		virtual Vector2								GetOffset( ) const PURE;
		virtual Vector2								GetScale( ) const PURE;
		virtual _float								GetRotation( ) const PURE;
		virtual Color								GetColor( ) const PURE;
		virtual _qword								GetZSort( ) const PURE;
		virtual IInterpolatorRef					GetOffsetXInterpolator( ) const PURE;
		virtual IInterpolatorRef					GetOffsetYInterpolator( ) const PURE;
		virtual IInterpolatorRef					GetScaleXInterpolator( ) const PURE;
		virtual IInterpolatorRef					GetScaleYInterpolator( ) const PURE;
		virtual IInterpolatorRef					GetRotationInterpolator( ) const PURE;
		virtual IInterpolatorRef					GetColorInterpolator( ) const PURE;

		virtual _void								SetKeyTime( _float time ) PURE;
		virtual _void								SetOffset( const Vector2& offset ) PURE;
		virtual _void								SetScale( const Vector2& scale ) PURE;
		virtual _void								SetRotation( _float rotation ) PURE;
		virtual _void								SetColor( const Color& color ) PURE;
		virtual _void								SetZSort( _qword zsort ) PURE;
		virtual _void								SetOffsetXInterpolator( const IInterpolatorRef& ipl ) PURE;
		virtual _void								SetOffsetYInterpolator( const IInterpolatorRef& ipl ) PURE;
		virtual _void								SetScaleXInterpolator( const IInterpolatorRef& ipl ) PURE;
		virtual _void								SetScaleYInterpolator( const IInterpolatorRef& ipl ) PURE;
		virtual _void								SetRotationInterpolator( const IInterpolatorRef& ipl ) PURE;
		virtual _void								SetColorInterpolator( const IInterpolatorRef& ipl ) PURE;

		virtual _ubool								CloneFrom( const IAnimationKeyFrame* srcframe ) PURE;

	};
}