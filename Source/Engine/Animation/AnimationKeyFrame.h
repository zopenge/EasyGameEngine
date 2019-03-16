
#pragma once

namespace EGE
{
	class AnimationKeyFrame : public INTERFACE_OBJECT_IMPL( IAnimationKeyFrame )
	{
	private:
		typedef INTERFACE_OBJECT_IMPL( IAnimationKeyFrame ) BaseClass;

	public:
		AnimationKeyFrame( );
		virtual ~AnimationKeyFrame( );

		// IAnimationKeyFrame Interface
	public:
		virtual _float								GetKeyTime( ) const override;
		virtual Vector2								GetOffset( ) const override;
		virtual Vector2								GetScale( ) const override;
		virtual _float								GetRotation( ) const override;
		virtual Color								GetColor( ) const override;
		virtual _qword								GetZSort( ) const override;
		virtual IInterpolatorRef					GetOffsetXInterpolator( ) const override;
		virtual IInterpolatorRef					GetOffsetYInterpolator( ) const override;
		virtual IInterpolatorRef					GetScaleXInterpolator( ) const override;
		virtual IInterpolatorRef					GetScaleYInterpolator( ) const override;
		virtual IInterpolatorRef					GetRotationInterpolator( ) const override;
		virtual IInterpolatorRef					GetColorInterpolator( ) const override;

		virtual _void								SetKeyTime( _float time ) override;
		virtual _void								SetOffset( const Vector2& offset ) override;
		virtual _void								SetScale( const Vector2& scale ) override;
		virtual _void								SetRotation( _float rotation ) override;
		virtual _void								SetColor( const Color& color ) override;
		virtual _void								SetZSort( _qword zsort ) override;
		virtual _void								SetOffsetXInterpolator( const IInterpolatorRef& ipl ) override;
		virtual _void								SetOffsetYInterpolator( const IInterpolatorRef& ipl ) override;
		virtual _void								SetScaleXInterpolator( const IInterpolatorRef& ipl ) override;
		virtual _void								SetScaleYInterpolator( const IInterpolatorRef& ipl ) override;
		virtual _void								SetRotationInterpolator( const IInterpolatorRef& ipl ) override;
		virtual _void								SetColorInterpolator( const IInterpolatorRef& ipl ) override;	

		virtual _ubool								CloneFrom( const IAnimationKeyFrame* srcframe ) override;
		// IFSerializableObject Interface
	public:
		virtual _ubool								Import( ISerializableNode* node ) override;
		virtual _ubool								Export( ISerializableNode* node ) const override;

	protected:
		_float										mKeyTime;
		Vector2										mOffset;
		Vector2										mScale;
		_float										mRotation;
		Color										mColor;
		_qword										mZSort;
		IInterpolatorRef							mOffsetXInterpolator;
		IInterpolatorRef							mOffsetYInterpolator;
		IInterpolatorRef							mScaleXInterpolator;
		IInterpolatorRef							mScaleYInterpolator;
		IInterpolatorRef							mRotationInterpolator;
		IInterpolatorRef							mColorInterpolator;
	};
}