//! @file     D3D11RenderTarget.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// D3D11Surface
//----------------------------------------------------------------------------

class D3D11Surface : public SurfaceRHI
{
public:
	//!	The surface type
	enum _TYPE
	{
		_TYPE_UNKNOWN,
		_TYPE_RENDER_TARGET,
		_TYPE_DEPTH_STENCIL
	};

private:
	//!	The surface type
	_TYPE						mType;
	//!	The surface size
	PointU						mSize;

	//!	The D3D-View resource
	RefPtr< ID3D11View >		mViewResource;
	//! The 2D texture to resolve surface to
	RefPtr< ID3D11Texture2D >	mResolveTargetResource;

	//!	The texture
	Texture2DRHI*				mTexture;

public:
	D3D11Surface( _TYPE type, const PointU& size, ID3D11View* view, ID3D11Texture2D* texture );
	virtual ~D3D11Surface( );

public:
	//!	Get the surface size.
	EGE_GETR_ACCESSOR_CONST( PointU, Size )
	//!	Get the texture.
	EGE_GET_ACCESSOR_CONST( Texture2DRHI*, Texture )

public:
	//!	Get the render target view.
	ID3D11RenderTargetView* GetRenderTargetView( )
	{
		if ( mType != _TYPE_RENDER_TARGET )
			return _null;

		return mViewResource.cast_static< ID3D11RenderTargetView >( );
	}

	//!	Get the depth stencil view.
	ID3D11DepthStencilView* GetDepthStencilView( )
	{
		if ( mType != _TYPE_DEPTH_STENCIL )
			return _null;

		return mViewResource.cast_static< ID3D11DepthStencilView >( );
	}
};

}