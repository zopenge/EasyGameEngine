//! @file     TImageFiller.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TImageFiller
//----------------------------------------------------------------------------

template< typename Type >
class TImageFiller : public Type
{
protected:
	// The filler image size
	PointU	mSize;
	// The space between images in pixel
	PointU	mSpace;

	// The free area
	_dword	mFreeArea;

protected:
	//!	When add image by the region.
	//!	@param		width		The image region width.
	//!	@param		height		The image region height.
	//!	@param		rect		The image region in filler.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool OnAddImage( _dword width, _dword height, RectU& rect ) PURE;
	//!	When free image by the region.
	//!	@param		rect		The image region in filler.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool OnFreeImage( const RectU& rect ) PURE;

protected:
	TImageFiller( const PointU& size, const PointU& space );
	virtual ~TImageFiller( );

// ITImageFiller Interface
public:
	virtual const PointU&	GetSize( ) const override;
	virtual _dword			GetAreaSize( ) const override;
	virtual _dword			GetFreeAreaSize( ) const override;
	virtual _float			GetFillRate( ) const override;

	virtual _void			SetSpace( const PointU& space ) override;
	virtual const PointU&	GetSpace( ) const override;

	virtual _void			ClearAllImages( ) override;
	virtual _ubool			AddImage( const PointU& size, RectU& rect ) override;
	virtual _ubool			AddImage( const PointU& size, RectI& rect ) override;

	virtual _ubool			FreeImage( const RectU& rect ) override;
	virtual _ubool			FreeImage( const RectI& rect ) override;
};

//----------------------------------------------------------------------------
// TImageFiller Implementation
//----------------------------------------------------------------------------

template< typename Type >
TImageFiller< Type >::TImageFiller( const PointU& size, const PointU& space )
{
	mSize		= size;
	mSpace		= space;
	mFreeArea	= size.x * size.y;
}

template< typename Type >
TImageFiller< Type >::~TImageFiller( )
{
}

template< typename Type >
const PointU& TImageFiller< Type >::GetSize( ) const
{
	return mSize;
}

template< typename Type >
_dword TImageFiller< Type >::GetAreaSize( ) const
{
	return mSize.x * mSize.y;
}

template< typename Type >
_dword TImageFiller< Type >::GetFreeAreaSize( ) const
{
	return mFreeArea;
}

template< typename Type >
_float TImageFiller< Type >::GetFillRate( ) const
{
	return 1.0f - EGE_RATIO( mFreeArea, mSize.x * mSize.y );
}

template< typename Type >
_void TImageFiller< Type >::SetSpace( const PointU& space )
{
	mSpace = space;
}

template< typename Type >
const PointU& TImageFiller< Type >::GetSpace( ) const
{
	return mSpace;
}

template< typename Type >
_void TImageFiller< Type >::ClearAllImages( )
{
	// Clear the used area
	mFreeArea = mSize.x * mSize.y;
}

template< typename Type >
_ubool TImageFiller< Type >::AddImage( const PointU& size, RectU& rect )
{
	if ( size.x == 0 || size.y == 0 )
		return _false;

	// Get the space size
	PointU space( size.x == mSize.x ? 0 : mSpace.x, size.y == mSize.y ? 0 : mSpace.y );

	// Fix the size with space
	_dword width	= size.x + space.x * 2;
	_dword height	= size.y + space.y * 2;

	// Test the free area size
	if ( GetFreeAreaSize( ) < width * height )
		return _false;

	// Fill image by the operation and feedback the left-top position of region image in operation
	if ( OnAddImage( width, height, rect ) == _false )
		return _false;

	// Here we should cut the space before feedbacking the region
	rect.Deflate( space.x, space.y );

	// Decrease the free area
	EGE_ASSERT( mFreeArea >= width * height );
	mFreeArea -= width * height;

	return _true;
}

template< typename Type >
_ubool TImageFiller< Type >::AddImage( const PointU& size, RectI& rect )
{
	RectU _rect;
	if ( AddImage( size, _rect ) == _false )
		return _false;

	rect.l = (_int)_rect.l;
	rect.t = (_int)_rect.t;
	rect.r = (_int)_rect.r;
	rect.b = (_int)_rect.b;

	return _true;
}

template< typename Type >
_ubool TImageFiller< Type >::FreeImage( const RectU& rect )
{
	return OnFreeImage( rect );
}

template< typename Type >
_ubool TImageFiller< Type >::FreeImage( const RectI& rect )
{
	RectU _rect;
	_rect.l = rect.l;
	_rect.t = rect.t;
	_rect.r = rect.r;
	_rect.b = rect.b;

	return FreeImage( _rect );
}

}