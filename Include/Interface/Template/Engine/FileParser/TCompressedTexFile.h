//! @file     TCompressedTexFile.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TCompressedTexFile
//----------------------------------------------------------------------------

template< typename Type >
class TCompressedTexFile : public Type
{
protected:
	typedef Type TBaseClass;

protected:
	//!	The texture info
	ICompressedTexFile::TextureInfo	mTextureInfo;
	//!	The compressed buffer data
	_byte**							mMipmapsCompressedBufferData;

	//!	The face LOD size of mipmaps
	_dword*							mFaceLODSize;

protected:
	TCompressedTexFile( );
	virtual ~TCompressedTexFile( );

// IBaseFile Interface
public:
	virtual _void									Unload( ) override;

// ICompressedTexFile Interface
public:
	virtual const ICompressedTexFile::TextureInfo&	GetTextureInfo( ) const override;

	virtual const _byte*							GetMipmapsPixelBufferData( _dword mip_index, _dword* width, _dword* height, _dword* image_size ) const override;

	virtual const _byte*							DecodeImagePixel( ) override;
};

//----------------------------------------------------------------------------
// TCompressedTexFile Implementation
//----------------------------------------------------------------------------

template< typename Type >
TCompressedTexFile< Type >::TCompressedTexFile( )
{
	EGE_INIT( mTextureInfo );

	mMipmapsCompressedBufferData	= _null;

	mFaceLODSize					= _null;
}

template< typename Type >
TCompressedTexFile< Type >::~TCompressedTexFile( )
{
}

template< typename Type >
_void TCompressedTexFile< Type >::Unload( )
{
	TBaseClass::Unload( );

	if ( mMipmapsCompressedBufferData != _null )
	{
		for ( _dword i = 0; i < mTextureInfo.mMipmapsNumber; i ++ )
			EGE_DELETE_ARRAY( mMipmapsCompressedBufferData[i] );

		EGE_DELETE_ARRAY( mMipmapsCompressedBufferData );
	}

	EGE_DELETE_ARRAY( mFaceLODSize );

	EGE_INIT( mTextureInfo );
}

template< typename Type >
const ICompressedTexFile::TextureInfo& TCompressedTexFile< Type >::GetTextureInfo( ) const
{
	return mTextureInfo;
}

template< typename Type >
const _byte* TCompressedTexFile< Type >::GetMipmapsPixelBufferData( _dword mip_index, _dword* width, _dword* height, _dword* image_size ) const
{
	if ( mip_index >= mTextureInfo.mMipmapsNumber )
		return _null;

	if ( width != _null )
		*width = MAX(1, this->GetWidth( ) >> mip_index);

	if ( height != _null )
		*height = MAX(1, this->GetHeight( ) >> mip_index);

	if ( image_size != _null )
		*image_size = mFaceLODSize[ mip_index ];

	return mMipmapsCompressedBufferData[ mip_index ];
}

template< typename Type >
const _byte* TCompressedTexFile< Type >::DecodeImagePixel( )
{
	return _null;
}

}