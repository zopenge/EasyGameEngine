//! @file     GDIResources.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TGDITexture
//----------------------------------------------------------------------------

template< _RENDER_RESOURCE_TYPE ResourceType >
class TGDITexture : public TDynamicRHIResource< ResourceType >
{
protected:
	//! The GDI texture resource
	Gdiplus::GpBitmap*	mResource;
	//!	The GDI texture lock bitmap data
	Gdiplus::BitmapData mBitmapData;

	//!	The pixel format
	_PIXEL_FORMAT		mPixelFormat;
	//!	The GDI texture size
	PointU				mSize;

protected:
	//!	Convert resource lock flag to GDI type.
	_dword ConvertResLockFlag2GDI( _RESOURCE_LOCK_FLAG flag ) const
	{
		switch ( flag )
		{
			case _RLF_READ_ONLY:	return Gdiplus::ImageLockModeRead;
			case _RLF_WRITE_ONLY:	return Gdiplus::ImageLockModeWrite;
			case _RLF_READ_WRITE:	return Gdiplus::ImageLockModeRead | Gdiplus::ImageLockModeWrite;
			default:
				return 0;
		}
	}
public:
	TGDITexture( Gdiplus::GpBitmap* resource, _PIXEL_FORMAT format, const PointU& size ) 
		: mResource( resource ), mPixelFormat( format ), mSize( size ) 
	{
	}
	virtual ~TGDITexture( ) 
	{
	}

public:
	//!	Get the GDI texture resource.
	EGE_GET_ACCESSOR_CONST( Gdiplus::GpBitmap*, Resource )
	//!	Get the GDI texture pixel format.
	EGE_GET_ACCESSOR_CONST( _PIXEL_FORMAT, PixelFormat )
	//!	Get the GDI texture size.
	EGE_GET_ACCESSOR_CONST( const PointU&, Size )

public:
	//!	Lock texture.
	_void* Lock( _dword& stride, _RESOURCE_LOCK_FLAG flag )
	{
		// Get the lock mode
		_dword lock_mode = ConvertResLockFlag2GDI( flag );

		// Fill pixel buffer into bitmap
		Gdiplus::GpRect rect( 0, 0, mSize.x, mSize.y );
		if ( GDI::GdipBitmapLockBits( mResource, &rect, lock_mode, gPixelFormats[ mPixelFormat ].mPlatformFormat, &mBitmapData ) != Gdiplus::Ok )
			return _null;

		// Feedback the stride
		stride = mBitmapData.Stride;

		return mBitmapData.Scan0;
	}

	//!	Unlock texture.
	_void Unlock( )
	{
		GDI::GdipBitmapUnlockBits( mResource, &mBitmapData );
	}
};

typedef TGDITexture< _RRT_TEXTURE >		GDITexture;
typedef TGDITexture< _RRT_TEXTURE_2D >	GDITexture2D;

//----------------------------------------------------------------------------
// GDIFont
//----------------------------------------------------------------------------

class GDIFont : public FontRHI
{
private:
	//!	The max font family number
	enum { _MAX_FONT_FAMILY_NUMBER = 1024 };

private:
	//!	The font info
	FontInitializerRHI			mInfo;

	//!	The GDI Font Collection
	Gdiplus::GpFontCollection*	mGDIFontCollection;

	//!	The GDI Font family number
	_dword						mGDIFontFamilyNumber;
	//!	The GDI Font family Array
	Gdiplus::GpFontFamily*		mGDIFontFamilyBuffer[ _MAX_FONT_FAMILY_NUMBER ];

	//!	The GDI Font
	Gdiplus::GpFont*			mGDIFont;
	//!	The GDI string format
	Gdiplus::GpStringFormat*	mGDIStringFormat;

public:
	GDIFont( Gdiplus::GpFontCollection* font, const FontInitializerRHI& info );
	virtual ~GDIFont( );

public:
	//!	Get the font info.
	EGE_GETR_ACCESSOR( FontInitializerRHI, Info )

	//!	Get GDI resources
	EGE_GET_ACCESSOR_CONST( Gdiplus::GpFont*, GDIFont )
	EGE_GET_ACCESSOR_CONST( Gdiplus::GpStringFormat*, GDIStringFormat )

public:
	//!	Initialize.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	_ubool Initialize( );
};

}