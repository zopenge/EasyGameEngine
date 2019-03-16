//! @file     D2DResources.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TD2DTexture
//----------------------------------------------------------------------------

template< _RENDER_RESOURCE_TYPE ResourceType >
class TD2DTexture : public TDynamicRHIResource< ResourceType >
{
protected:
	//! The D2D texture resource
	RefPtr< ID2D1Bitmap >	mResource;

	//!	The GDI texture size
	PointU					mSize;

public:
	TD2DTexture( ID2D1Bitmap* resource, const PointU& size ) 
		: mResource( resource ), mSize( size ) {}

	virtual ~TD2DTexture( ) {}

public:
	//!	Get the D2D texture resource
	EGE_GET_ACCESSOR( ID2D1Bitmap*, Resource )
	//!	Get the D2D texture size.
	EGE_GET_ACCESSOR_CONST( const PointU&, Size )
};

typedef TD2DTexture< _RRT_TEXTURE >		D2DTexture;
typedef TD2DTexture< _RRT_TEXTURE_2D >	D2DTexture2D;

//----------------------------------------------------------------------------
// D2DFont
//----------------------------------------------------------------------------

class D2DFont : public FontRHI
{
public:
	D2DFont( );
	virtual ~D2DFont( );
};

}