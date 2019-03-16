#include "EGEEngine.h"

AnimationKeyFrame::AnimationKeyFrame( )
	: mKeyTime( 0 )
	, mOffset( 0.0f, 0.0f )
	, mScale( 1.0f, 1.0f )
	, mRotation( 0.0f )
	, mColor( Color::cWhite )
	, mZSort( 0 )
{

}

AnimationKeyFrame::~AnimationKeyFrame( )
{

}

_ubool AnimationKeyFrame::CloneFrom( const IAnimationKeyFrame* srcframe )
{
	if ( srcframe == _null )
		return _false;

	mKeyTime = srcframe->GetKeyTime( );
	mOffset = srcframe->GetOffset( );
	mScale = srcframe->GetScale( );
	mRotation = srcframe->GetRotation( );
	mColor = srcframe->GetColor( );
	mZSort = srcframe->GetZSort( );
	mOffsetXInterpolator = srcframe->GetOffsetXInterpolator( );
	mOffsetYInterpolator = srcframe->GetOffsetYInterpolator( );
	mScaleXInterpolator = srcframe->GetScaleXInterpolator( );
	mScaleYInterpolator = srcframe->GetScaleYInterpolator( );
	mRotationInterpolator = srcframe->GetRotationInterpolator( );
	mColorInterpolator = srcframe->GetColorInterpolator( );

	return _true;
}

_float AnimationKeyFrame::GetKeyTime( ) const
{
	return mKeyTime;
}

Vector2 AnimationKeyFrame::GetOffset( ) const
{
	return mOffset;
}

Vector2 AnimationKeyFrame::GetScale( ) const
{
	return mScale;
}

_float AnimationKeyFrame::GetRotation( ) const
{
	return mRotation;
}

Color AnimationKeyFrame::GetColor( ) const
{
	return mColor;
}

_qword AnimationKeyFrame::GetZSort( ) const
{
	return mZSort;
}

IInterpolatorRef AnimationKeyFrame::GetOffsetXInterpolator( ) const
{
	return mOffsetXInterpolator;
}

IInterpolatorRef AnimationKeyFrame::GetOffsetYInterpolator( ) const
{
	return mOffsetYInterpolator;
}

IInterpolatorRef AnimationKeyFrame::GetScaleYInterpolator( ) const
{
	return mScaleXInterpolator;
}

IInterpolatorRef AnimationKeyFrame::GetScaleXInterpolator( ) const
{
	return mScaleYInterpolator;
}

IInterpolatorRef AnimationKeyFrame::GetRotationInterpolator( ) const
{
	return mRotationInterpolator;
}

IInterpolatorRef AnimationKeyFrame::GetColorInterpolator( ) const
{
	return mColorInterpolator;
}

_void AnimationKeyFrame::SetKeyTime( _float time )
{
	mKeyTime = time;
}

_void AnimationKeyFrame::SetOffset( const Vector2& offset )
{
	mOffset = offset;
}

_void AnimationKeyFrame::SetScale( const Vector2& scale )
{
	mScale = scale;
}

_void AnimationKeyFrame::SetRotation( _float rotation )
{
	mRotation = rotation;
}

_void AnimationKeyFrame::SetColor( const Color& color )
{
	mColor = color;
}

_void AnimationKeyFrame::SetZSort( _qword zsort )
{
	mZSort = zsort;
}

_void AnimationKeyFrame::SetOffsetXInterpolator( const IInterpolatorRef& ipl )
{
	mOffsetXInterpolator = ipl;
}

_void AnimationKeyFrame::SetOffsetYInterpolator( const IInterpolatorRef& ipl )
{
	mOffsetYInterpolator = ipl;
}

_void AnimationKeyFrame::SetScaleXInterpolator( const IInterpolatorRef& ipl )
{
	mScaleXInterpolator = ipl;
}

_void AnimationKeyFrame::SetScaleYInterpolator( const IInterpolatorRef& ipl )
{
	mScaleYInterpolator = ipl;
}

_void AnimationKeyFrame::SetRotationInterpolator( const IInterpolatorRef& ipl )
{
	mRotationInterpolator = ipl;
}

_void AnimationKeyFrame::SetColorInterpolator( const IInterpolatorRef& ipl )
{
	mColorInterpolator = ipl;
}

_ubool AnimationKeyFrame::Import( ISerializableNode* node )
{
	if ( !node )
		return _false;

	if ( node->Read( L"time", mKeyTime ) == _false )
		return _false;

	if ( node->Read( L"offsetx", mOffset.x ) == _false )
		return _false;

	if ( node->Read( L"offsety", mOffset.y ) == _false )
		return _false;

	if ( node->Read( L"scalex", mScale.x ) == _false )
		return _false;

	if ( node->Read( L"scaley", mScale.y ) == _false )
		return _false;

	if ( node->Read( L"rotation", mRotation ) == _false )
		return _false;

	if ( node->Read( L"color", mColor ) == _false )
		return _false;

	if ( node->Read( L"zsort", mZSort ) == _false )
		return _false;


	WString iplname;
	if ( node->Read( L"ipl_offsetx", iplname ) == _false )
		return _false;
	mOffsetXInterpolator = GetResourceFactory( )->CreateInterpolator( iplname );

	if ( node->Read( L"ipl_offsety", iplname ) == _false )
		return _false;
	mOffsetYInterpolator = GetResourceFactory( )->CreateInterpolator( iplname );

	if ( node->Read( L"ipl_scalex", iplname ) == _false )
		return _false;
	mScaleXInterpolator = GetResourceFactory( )->CreateInterpolator( iplname );

	if ( node->Read( L"ipl_scaley", iplname ) == _false )
		return _false;
	mScaleYInterpolator = GetResourceFactory( )->CreateInterpolator( iplname );

	if ( node->Read( L"ipl_rotation", iplname ) == _false )
		return _false;
	mRotationInterpolator = GetResourceFactory( )->CreateInterpolator( iplname );

	if ( node->Read( L"ipl_color", iplname ) == _false )
		return _false;
	mColorInterpolator = GetResourceFactory( )->CreateInterpolator( iplname );

	return _true;
}

_ubool AnimationKeyFrame::Export( ISerializableNode* node ) const
{
	if ( !node )
		return _false;

	if ( node->Write( L"time", mKeyTime ) == _false )
		return _false;

	if ( node->Write( L"offsetx", mOffset.x ) == _false )
		return _false;

	if ( node->Write( L"offsety", mOffset.y ) == _false )
		return _false;

	if ( node->Write( L"scalex", mScale.x ) == _false )
		return _false;

	if ( node->Write( L"scaley", mScale.y ) == _false )
		return _false;

	if ( node->Write( L"rotation", mRotation ) == _false )
		return _false;

	if ( node->Write( L"color", mColor ) == _false )
		return _false;

	if ( node->Write( L"zsort", mZSort ) == _false )
		return _false;

	if ( node->Write( L"ipl_offsetx", mOffsetXInterpolator->GetName( ) ) == _false )
		return _false;

	if ( node->Write( L"ipl_offsety", mOffsetYInterpolator->GetName( )  ) == _false )
		return _false;

	if ( node->Write( L"ipl_scalex", mScaleXInterpolator->GetName( )  ) == _false )
		return _false;

	if ( node->Write( L"ipl_scaley", mScaleYInterpolator->GetName( )  ) == _false )
		return _false;

	if ( node->Write( L"ipl_rotation", mRotationInterpolator->GetName( )  ) == _false )
		return _false;

	if ( node->Write( L"ipl_color", mColorInterpolator->GetName( )  ) == _false )
		return _false;

	return _true;
}