//! @file     TGraphicLight.h
//! @author   LiCode
//! @version  1.1
//! @date     2015.06
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TGraphicLight
//----------------------------------------------------------------------------

template< typename Type >
class TGraphicLight : public INTERFACE_OBJECT_IMPL( Type )
{
protected:
	Vector3	mPosition;
	_float	mRange;
	_ubool	mEnableAttenuation;
	_float	mAttenuation;
	Vector4	mColor;

protected:
	_void CopyFrom( const TGraphicLight* src_object );

public:
	TGraphicLight( );
	virtual ~TGraphicLight( );

public:
	virtual _void					SetPosition( const Vector3& position ) override;
	virtual _void					SetRange( _float range ) override;
	virtual _void					EnableAttenuation( _ubool enable ) override;
	virtual _void					SetAttenuation( _float att ) override;
	virtual _void					SetLDRColor( const Color& color ) override;
	virtual _void					SetHDRColor( const Vector4& color ) override;

	virtual const Vector3&			GetPosition( ) const override;
	virtual _float					GetRange( ) const override;
	virtual _ubool					IsEnableAttenuation( ) const override;
	virtual _float					GetAttenuation( ) const override;
	virtual const Vector4&			GetHDRColor( ) const override;
	virtual Color					GetLDRColor( ) const override;
};

//----------------------------------------------------------------------------
// TGraphicLight Implementation
//----------------------------------------------------------------------------

template< typename Type >
TGraphicLight< Type >::TGraphicLight( )
{
	mPosition			= Vector3::cOrigin;
	mRange				= 100.0f;
	mEnableAttenuation	= _false;
	mAttenuation		= 0.0f;
	mColor				= Vector4::cIdentity;
}

template< typename Type >
TGraphicLight< Type >::~TGraphicLight( )
{
}

template< typename Type >
_void TGraphicLight< Type >::CopyFrom( const TGraphicLight* src_object )
{
	mPosition			= src_object->mPosition;
	mRange				= src_object->mRange;
	mEnableAttenuation	= src_object->mEnableAttenuation;
	mAttenuation		= src_object->mAttenuation;
	mColor				= src_object->mColor;
}

template< typename Type >
_void TGraphicLight< Type >::SetPosition( const Vector3& position )
{
	mPosition = position;
}

template< typename Type >
_void TGraphicLight< Type >::SetRange( _float range )
{
	mRange = range;
}

template< typename Type >
_void TGraphicLight< Type >::EnableAttenuation( _ubool enable )
{
	mEnableAttenuation = enable;
}

template< typename Type >
_void TGraphicLight< Type >::SetAttenuation( _float att )
{
	mAttenuation = att;
}

template< typename Type >
_void TGraphicLight< Type >::SetHDRColor( const Vector4& color )
{
	mColor = color;
}

template< typename Type >
_void TGraphicLight< Type >::SetLDRColor( const Color& color )
{
	mColor.x = color.Red( );
	mColor.y = color.Green( );
	mColor.z = color.Blue( );
	mColor.w = color.Alpha( );
}

template< typename Type >
const Vector3& TGraphicLight< Type >::GetPosition( ) const
{
	return mPosition;
}

template< typename Type >
_float TGraphicLight< Type >::GetRange( ) const
{
	return mRange;
}

template< typename Type >
_ubool TGraphicLight< Type >::IsEnableAttenuation( ) const
{
	return mEnableAttenuation;
}

template< typename Type >
_float TGraphicLight< Type >::GetAttenuation( ) const
{
	return mAttenuation;
}

template< typename Type >
const Vector4& TGraphicLight< Type >::GetHDRColor( ) const
{
	return mColor;
}

template< typename Type >
Color TGraphicLight< Type >::GetLDRColor( ) const
{
	return Color( 
		Math::Clamp( mColor.x, 0.0f, 1.0f ),
		Math::Clamp( mColor.y, 0.0f, 1.0f ),
		Math::Clamp( mColor.z, 0.0f, 1.0f ),
		Math::Clamp( mColor.w, 0.0f, 1.0f )
		);
}

}