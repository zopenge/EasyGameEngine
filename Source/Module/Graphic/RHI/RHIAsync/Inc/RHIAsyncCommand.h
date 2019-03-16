//! @file     RHIAsyncCommand.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{
	
#define RHI_ASYNC_COMMAND_BEGIN( x ) struct RHIAsyncCommand##x : public RHIAsyncCommand {
#define RHI_ASYNC_COMMAND_END( ) };

//----------------------------------------------------------------------------
// RHIAsyncCommand
//----------------------------------------------------------------------------

struct RHIAsyncCommand
{
	enum _TYPE
	{
		_TYPE_Unknown,

		// Dummy operation to ignore IF command
		_TYPE_Dummy,

		// Main interface
		_TYPE_Initialize,
		_TYPE_Finalize,
		_TYPE_ResetResources,
		_TYPE_UnloadResources,
		// Shader interface
		_TYPE_CreatePixelShader,
		_TYPE_CreateVertexShader,
		_TYPE_CreateBoundShader,
		_TYPE_ActiveUniformBuffer,
		_TYPE_UpdateUniformBuffer,
		_TYPE_SetUniformPropertyValue,
		// Index buffer
		_TYPE_CreateIndexBuffer,
		_TYPE_UnlockIndexBuffer,
		_TYPE_UpdateIndexBuffer,
		_TYPE_ResizeIndexBuffer,
		// Vertex buffer
		_TYPE_CreateVertexBuffer,
		_TYPE_UnlockVertexBuffer,
		_TYPE_UpdateVertexBuffer,
		_TYPE_ResizeVertexBuffer,
		// Vertex array
		_TYPE_CreateVertexArray,
		_TYPE_BindVertexArray,
		_TYPE_SetVertexArrayDecl,
		_TYPE_UnbindVertexArray,
		// Texture
		_TYPE_CreateTextureCube,
		_TYPE_CreateTextureCubeFromImageFiles,
		_TYPE_CreateTexture2D,
		_TYPE_CreateTexture2DFromImageFile,
		_TYPE_CreateTexture2DWithMipmaps,
		_TYPE_UpdateTexture2D,
		_TYPE_LockTexture2D,
		_TYPE_UnlockTexture2D,
		_TYPE_ReadTexture2DMipPixel,
		// Font
		_TYPE_CreateFontFromStream,
		// Surface
		_TYPE_CreateTargetableSurface,
		_TYPE_CreateTargetableSurfaceFrom2DTexture,
		_TYPE_CreateTargetableSurfaceFromCubeTexture,
		// Viewport
		_TYPE_CreateViewport,
		// Render state
		_TYPE_SetRenderTarget,
		_TYPE_SetBoundShader,
		_TYPE_SetDepthState,
		_TYPE_SetStencilState,
		_TYPE_SetBlendState,
		_TYPE_SetRasterizerState,
		_TYPE_SetRasterizerStateImmediate,
		_TYPE_SetSamplerState,
		_TYPE_SetViewport,
		_TYPE_SetViewportWithRatio,
		_TYPE_SetScissorRect,
		_TYPE_BindViewport,
		_TYPE_Present,
		// Draw
		_TYPE_Clear,
		_TYPE_DrawPoint,
		_TYPE_DrawLine,
		_TYPE_DrawRectangleI,
		_TYPE_DrawRectangleF,
		_TYPE_FillRectangleI,
		_TYPE_FillRectangleF,
		_TYPE_DrawSprite,
		_TYPE_DrawText,
		_TYPE_DrawPrimitive,
		_TYPE_DrawIndexedPrimitive,
	};

	_TYPE			mCommandType;

	EventObject*	mWaitEvent;

	_dword			mRetValue;
	IObjectPassRef	mRetObject;
};

//----------------------------------------------------------------------------
// Main interface
//----------------------------------------------------------------------------

RHI_ASYNC_COMMAND_BEGIN( Dummy )
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( Initialize )
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( Finalize )
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( ResetResources )
	IApplicationRef mApplication;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( UnloadResources )
RHI_ASYNC_COMMAND_END( )

//----------------------------------------------------------------------------
// Shader interface
//----------------------------------------------------------------------------

RHI_ASYNC_COMMAND_BEGIN( CreatePixelShader )
	AStringPtr	mCode;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( CreateVertexShader )
	AStringPtr	mCode;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( CreateBoundShader )
	VertexShaderRHIRef	mVertexShader;
	PixelShaderRHIRef	mPixelShader;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( ActiveUniformBuffer )
	BoundShaderRHIRef			mShader;
	_UNIFORM_BUFFER_DATA_TYPE	mType;
	AStringPtr					mName;
	_dword						mSize;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( UpdateUniformBuffer )
	BoundShaderRHIRef	mShader;
	_dword				mLocation;
	const _void*		mBuffer;
	_dword				mSize;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( SetUniformPropertyValue )
	BoundShaderRHIRef	mShader;
	AString				mName;
	_long				mValue;
RHI_ASYNC_COMMAND_END( )

//----------------------------------------------------------------------------
// Index buffer interface
//----------------------------------------------------------------------------

RHI_ASYNC_COMMAND_BEGIN( CreateIndexBuffer )
	_dword				mStride;
	_dword				mSize;
	const _byte*		mBuffer;
	_dword				mUsageFlags;
	_RESOURCE_DRAW_TYPE	mDrawType;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( UnlockIndexBuffer )
	IndexBufferRHIRef	mIndexBuffer;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( UpdateIndexBuffer )
	IndexBufferRHIRef	mIndexBuffer;
	_dword				mOffset;
	_dword				mSize;
	const _byte*		mBuffer;
	_ubool				mDiscard;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( ResizeIndexBuffer )
	IndexBufferRHIRef	mIndexBuffer;
	_dword				mSize;
RHI_ASYNC_COMMAND_END( )

//----------------------------------------------------------------------------
// Vertex buffer interface
//----------------------------------------------------------------------------

RHI_ASYNC_COMMAND_BEGIN( CreateVertexBuffer )
	_dword				mStride;
	_dword				mSize;
	const _byte*		mBuffer;
	_dword				mUsageFlags;
	_RESOURCE_DRAW_TYPE	mDrawType;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( UnlockVertexBuffer )
	VertexBufferRHIRef	mVertexBuffer;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( UpdateVertexBuffer )
	VertexBufferRHIRef		mVertexBuffer;
	_dword					mOffset;
	_dword					mSize;
	const _byte*			mBuffer;
	_ubool					mDiscard;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( ResizeVertexBuffer )
	VertexBufferRHIRef	mVertexBuffer;
	_dword				mSize;
RHI_ASYNC_COMMAND_END( )

//----------------------------------------------------------------------------
// Vertex array interface
//----------------------------------------------------------------------------

RHI_ASYNC_COMMAND_BEGIN( CreateVertexArray )
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( BindVertexArray )
	VertexArrayRHIRef	mVertexArray;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( SetVertexArrayDecl )
	VertexArrayRHIRef		mVertexArray;
	VertexDeclarationRHIRef	mDeclaration;	
	VertexBufferRHIRef		mVertexBuffer;
	IndexBufferRHIRef		mIndexBuffer;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( UnbindVertexArray )
RHI_ASYNC_COMMAND_END( )

//----------------------------------------------------------------------------
// Texture interface
//----------------------------------------------------------------------------

RHI_ASYNC_COMMAND_BEGIN( CreateTextureCube )
	WString			mResName;
	_dword			mWidth;
	_dword			mHeight;
	_PIXEL_FORMAT	mFormat;
	_dword			mNumMips;
	_dword			mFlags;
	const _byte**	mPixel;
	WStringPtr*		mResNameTable;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( CreateTextureCubeFromImageFiles )
	WString			mResName;
	_dword			mFlags;
	_dword			mNumMips;
	IImageFile**	mImageFiles;
	WStringPtr*		mResNameTable;
	_ubool			mIsAutoRotate;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( CreateTexture2D )
	WString			mResName;
	_dword			mWidth;
	_dword			mHeight;
	_PIXEL_FORMAT	mFormat;
	_dword			mNumMips;
	_dword			mFlags;
	const _byte*	mPixel;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( CreateTexture2DFromImageFile )
	WString			mResName;
	IImageFileRef	mImageFile;
	_dword			mNumMips;
	_dword			mFlags;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( CreateTexture2DWithMipmaps )
	WString			mResName;
	_dword			mWidth;
	_dword			mHeight;
	_PIXEL_FORMAT	mFormat;
	_dword			mNumMips;
	_dword			mFlags;
	const _byte**	mPixels;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( UpdateTexture2D )
	Texture2DRHIRef mTexture;
	_dword			mMipIndex;
	RectU			mRect;
	const _byte*	mPixel;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( LockTexture2D )
	Texture2DRHIRef		mTexture;
	_dword				mMipIndex;
	_dword*				mStride;
	_RESOURCE_LOCK_FLAG mFlag;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( UnlockTexture2D )
	Texture2DRHIRef	mTexture;
	_dword			mMipIndex;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( ReadTexture2DMipPixel )
	const Texture2DRHI*	mTexture;
	_dword				mMipIndex;
	_byte*				mPixelBuffer;
RHI_ASYNC_COMMAND_END( )

//----------------------------------------------------------------------------
// Font interface
//----------------------------------------------------------------------------

RHI_ASYNC_COMMAND_BEGIN( CreateFontFromStream )
	FontInitializerRHI	mInitializer;
	IStreamReaderRef	mStreamReader;
RHI_ASYNC_COMMAND_END( )

//----------------------------------------------------------------------------
// Surface interface
//----------------------------------------------------------------------------

RHI_ASYNC_COMMAND_BEGIN( CreateTargetableSurface )
	_dword			mWidth;
	_dword			mHeight;
	_PIXEL_FORMAT	mFormat;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( CreateTargetableSurfaceFrom2DTexture )
	Texture2DRHIRef	mTexture;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( CreateTargetableSurfaceFromCubeTexture )
	TextureCubeRHIRef	mTexture;
RHI_ASYNC_COMMAND_END( )

//----------------------------------------------------------------------------
// Viewport interface
//----------------------------------------------------------------------------

RHI_ASYNC_COMMAND_BEGIN( CreateViewport )
	_handle	mAppHandle;
	PointU	mSize;
	PointU	mDeviceSize;
RHI_ASYNC_COMMAND_END( )

//----------------------------------------------------------------------------
// Render state interface
//----------------------------------------------------------------------------

RHI_ASYNC_COMMAND_BEGIN( SetRenderTarget )
	SurfaceRHIRef mRenderTarget;
	SurfaceRHIRef mDepthStencil;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( SetBoundShader )
	BoundShaderRHIRef mShader;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( SetDepthState )
	const DepthStateRHI* mState;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( SetStencilState )
	const StencilStateRHI* mState;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( SetBlendState )
	const BlendStateRHI* mState;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( SetRasterizerState )
	const RasterizerStateRHI* mState;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( SetRasterizerStateImmediate )
	const RasterizerStateInitializerRHI* mInitializer;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( SetSamplerState )
	_dword					mSamplerIndex;
	const SamplerStateRHI*	mState;
	TextureRHIRef			mTexture;
	_ubool					mForce;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( SetViewport )
	Viewport	mViewport;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( SetViewportWithRatio )
	Viewport	mViewport;
	Ratio		mRatio;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( SetScissorRect )
	_ubool	mEnable;
	RectU	mRect;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( BindViewport )
	ViewportRHI*	mViewport;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( Present )
	ViewportRHI*	mViewport;
	_ubool			mClearCaches;
RHI_ASYNC_COMMAND_END( )

//----------------------------------------------------------------------------
// Draw interface
//----------------------------------------------------------------------------

RHI_ASYNC_COMMAND_BEGIN( Clear )
	_ubool	mClearColor;
	Color	mColor;
	_ubool	mClearDepth;
	_float	mDepth;
	_ubool	mClearStencil;
	_dword	mStencil;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( DrawPoint )
	Vector2	mPosition;
	Color	mColor;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( DrawLine )
	Vector2	mStart;
	Vector2	mEnd;
	Color	mColorStart;
	Color	mColorEnd;
	_float	mWidth;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( DrawRectangleI )
	RectI	mRect;
	Color	mColor;
	_dword	mWidth;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( DrawRectangleF )
	RectF	mRect;
	Color	mColor;
	_float	mWidth;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( FillRectangleI )
	RectI	mRect;
	Color	mColor;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( FillRectangleF )
	RectF	mRect;
	Color	mColor;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( DrawSprite )
	Vector2			mPosition;
	Vector2			mSize;
	Texture2DRHIRef mTexture;
	Color			mColor;
	Vector2			mUV1;
	Vector2			mUV2;
	_ubool			mIsRotate;
	_ubool			mIsRound;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( DrawText )
	_dword			mAlignment;
	RectF			mRect;
	WStringPtr		mString;
	FontRHIRef		mFont;
	Color			mColor;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( DrawPrimitive )
	_PRIMITIVE_TYPE mType;
	_dword			mOffset;
	_dword			mNumber;
RHI_ASYNC_COMMAND_END( )

RHI_ASYNC_COMMAND_BEGIN( DrawIndexedPrimitive )
	_PRIMITIVE_TYPE mType;
	_dword			mStartIndex;
	_dword			mNumber;
RHI_ASYNC_COMMAND_END( )

}