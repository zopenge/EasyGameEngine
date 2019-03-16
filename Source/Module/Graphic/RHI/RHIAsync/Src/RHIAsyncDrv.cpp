//! @file     RHIAsyncDrv.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

#ifndef _EGE_DISABLE_RHI_ASYNC_

// Allocate
#define _ALLOC( x ) \
	RHIAsyncCommand##x* cmd = (RHIAsyncCommand##x*) mAllocator->Alloc( sizeof( RHIAsyncCommand##x ) ); \
	cmd->mCommandType = RHIAsyncCommand::_TYPE_##x;
// Begin/End command without waiting
#define _BEGIN_COMMAND( x ) _ALLOC( x );
#define _END_COMMAND( ) 	mAsyncThread->PostCommand( cmd );
// Begin/End command and wait
#define _BEGIN_COMMAND_WAIT( x )			_ALLOC( x ); cmd->mWaitEvent = &mEvent; mEvent.Reset( );
#define _END_COMMAND_WAIT_RETURN_NONE( ) 	mAsyncThread->PostCommand( cmd ); mEvent.Wait( );
#define _END_COMMAND_WAIT_RETURN_VALUE( ) 	_END_COMMAND_WAIT_RETURN_NONE( ); return cmd->mRetValue;
#define _END_COMMAND_WAIT_RETURN_PTR( ) 	_END_COMMAND_WAIT_RETURN_NONE( ); return (_void*) cmd->mRetValue;
#define _END_COMMAND_WAIT_RETURN_OBJECT( ) 	_END_COMMAND_WAIT_RETURN_NONE( ); return IObjectPassRef( cmd->mRetObject.GetPtr( ) );

//----------------------------------------------------------------------------
// RHIAsyncDrvThread Implementation
//----------------------------------------------------------------------------

RHIAsyncDrvThread::RHIAsyncDrvThread( IDynamicRHI* dynamic_rhi )
{
	EGE_ASSERT( dynamic_rhi != _null );

	mDynamicRHI				= dynamic_rhi;

	mCurCommandBufferIndex	= 0;
	mCurCommandBufferNumber	= 0;

	EGE_INIT_ARRAY( mCommands );
}

RHIAsyncDrvThread::~RHIAsyncDrvThread( )
{
}

_void RHIAsyncDrvThread::ProcessCommand( RHIAsyncCommand& command )
{	
#define CASE_BEGIN( x ) case RHIAsyncCommand::_TYPE_##x: { RHIAsyncCommand##x& cmd = (RHIAsyncCommand##x&) command;
#define CASE_END( ) } break;

	switch ( command.mCommandType )
	{
		// Main interface
		CASE_BEGIN( Dummy )
		{
		}
		CASE_END( )

		CASE_BEGIN( Initialize )
		{
			cmd.mRetValue = mDynamicRHI->Initialize( );
		}
		CASE_END( )

		CASE_BEGIN( Finalize )
		{
			mDynamicRHI->Finalize( );
		}
		CASE_END( )

		CASE_BEGIN( ResetResources )
		{
			cmd.mRetValue = mDynamicRHI->ResetResources( cmd.mApplication );
		}
		CASE_END( )

		CASE_BEGIN( UnloadResources )
		{
			mDynamicRHI->UnloadResources( );
		}
		CASE_END( )

		// Shader interface
		CASE_BEGIN( CreatePixelShader )
		{
			cmd.mRetObject = mDynamicRHI->CreatePixelShader( cmd.mCode );
		}
		CASE_END( )

		CASE_BEGIN( CreateVertexShader )
		{
			cmd.mRetObject = mDynamicRHI->CreateVertexShader( cmd.mCode );
		}
		CASE_END( )

		CASE_BEGIN( CreateBoundShader )
		{
			cmd.mRetObject = mDynamicRHI->CreateBoundShader( cmd.mVertexShader, cmd.mPixelShader );
		}
		CASE_END( )

		CASE_BEGIN( ActiveUniformBuffer )
		{
			cmd.mRetValue = mDynamicRHI->ActiveUniformBuffer( cmd.mShader, cmd.mType, cmd.mName, cmd.mSize );
		}
		CASE_END( )

		CASE_BEGIN( UpdateUniformBuffer )
		{
			cmd.mRetValue = mDynamicRHI->UpdateUniformBuffer( cmd.mShader, cmd.mLocation, cmd.mBuffer, cmd.mSize );
		}
		CASE_END( )

		CASE_BEGIN( SetUniformPropertyValue )
		{
			cmd.mRetValue = mDynamicRHI->SetUniformPropertyValue( cmd.mShader, cmd.mName, cmd.mValue );
		}
		CASE_END( )

		// Index buffer
		CASE_BEGIN( CreateIndexBuffer )
		{
			cmd.mRetObject = mDynamicRHI->CreateIndexBuffer( cmd.mStride, cmd.mSize, cmd.mBuffer, cmd.mUsageFlags, cmd.mDrawType );
		}
		CASE_END( )

		CASE_BEGIN( UnlockIndexBuffer )
		{
			mDynamicRHI->UnlockIndexBuffer( cmd.mIndexBuffer );
		}
		CASE_END( )

		CASE_BEGIN( UpdateIndexBuffer )
		{
			cmd.mRetValue = mDynamicRHI->UpdateIndexBuffer( cmd.mIndexBuffer, cmd.mOffset, cmd.mSize, cmd.mBuffer, cmd.mDiscard );
		}
		CASE_END( )

		CASE_BEGIN( ResizeIndexBuffer )
		{
			cmd.mRetValue = mDynamicRHI->ResizeIndexBuffer( cmd.mIndexBuffer, cmd.mSize );
		}
		CASE_END( )

		// Vertex buffer
		CASE_BEGIN( CreateVertexBuffer )
		{
			cmd.mRetObject = mDynamicRHI->CreateVertexBuffer( cmd.mStride, cmd.mSize, cmd.mBuffer, cmd.mUsageFlags, cmd.mDrawType );
		}
		CASE_END( )

		CASE_BEGIN( UnlockVertexBuffer )
		{
			mDynamicRHI->UnlockVertexBuffer( cmd.mVertexBuffer );
		}
		CASE_END( )

		CASE_BEGIN( UpdateVertexBuffer )
		{
			cmd.mRetValue = mDynamicRHI->UpdateVertexBuffer( cmd.mVertexBuffer, cmd.mOffset, cmd.mSize, cmd.mBuffer, cmd.mDiscard );
		}
		CASE_END( )

		CASE_BEGIN( ResizeVertexBuffer )
		{
			cmd.mRetValue = mDynamicRHI->ResizeVertexBuffer( cmd.mVertexBuffer, cmd.mSize );
		}
		CASE_END( )

		// Vertex array
		CASE_BEGIN( CreateVertexArray )
		{
			cmd.mRetObject = mDynamicRHI->CreateVertexArray( );
		}
		CASE_END( )

		CASE_BEGIN( BindVertexArray )
		{
			mDynamicRHI->BindVertexArray( cmd.mVertexArray );
		}
		CASE_END( )

		CASE_BEGIN( UnbindVertexArray )
		{
			mDynamicRHI->UnbindVertexArray( );
		}
		CASE_END( )

		CASE_BEGIN( SetVertexArrayDecl )
		{
			cmd.mRetValue = mDynamicRHI->SetVertexArrayDecl( cmd.mVertexArray, cmd.mDeclaration, cmd.mVertexBuffer, cmd.mIndexBuffer );
		}
		CASE_END( )

		// Texture
		CASE_BEGIN( CreateTextureCube )
		{
			cmd.mRetObject = mDynamicRHI->CreateTextureCube( cmd.mResName, cmd.mWidth, cmd.mHeight, cmd.mFormat, cmd.mNumMips, cmd.mFlags, cmd.mPixel, cmd.mResNameTable );
		}
		CASE_END( )

		CASE_BEGIN( CreateTextureCubeFromImageFiles )
		{
			cmd.mRetObject = mDynamicRHI->CreateTextureCubeFromImageFiles( cmd.mResName, cmd.mImageFiles, cmd.mNumMips, cmd.mFlags, cmd.mResNameTable, cmd.mIsAutoRotate );
		}
		CASE_END( )

		CASE_BEGIN( CreateTexture2D )
		{
			cmd.mRetObject = mDynamicRHI->CreateTexture2D( cmd.mResName, cmd.mWidth, cmd.mHeight, cmd.mFormat, cmd.mNumMips, cmd.mFlags, cmd.mPixel );
		}
		CASE_END( )

		CASE_BEGIN( CreateTexture2DFromImageFile )
		{
			cmd.mRetObject = mDynamicRHI->CreateTexture2DFromImageFile( cmd.mResName, cmd.mImageFile, cmd.mNumMips, cmd.mFlags );
		}
		CASE_END( )

		CASE_BEGIN( CreateTexture2DWithMipmaps )
		{
			cmd.mRetObject = mDynamicRHI->CreateTexture2DWithMipmaps( cmd.mResName, cmd.mWidth, cmd.mHeight, cmd.mFormat, cmd.mNumMips, cmd.mFlags, cmd.mPixels );
		}
		CASE_END( )

		CASE_BEGIN( UpdateTexture2D )
		{
			cmd.mRetValue = mDynamicRHI->UpdateTexture2D( cmd.mTexture, cmd.mMipIndex, cmd.mRect, cmd.mPixel );
		}
		CASE_END( )

		CASE_BEGIN( LockTexture2D )
		{
			cmd.mRetValue = (_dword) mDynamicRHI->LockTexture2D( cmd.mTexture, cmd.mMipIndex, *cmd.mStride, cmd.mFlag );
		}
		CASE_END( )

		CASE_BEGIN( UnlockTexture2D )
		{
			mDynamicRHI->UnlockTexture2D( cmd.mTexture, cmd.mMipIndex );
		}
		CASE_END( )

		CASE_BEGIN( ReadTexture2DMipPixel )
		{
			cmd.mRetValue = mDynamicRHI->ReadTexture2DMipPixel( cmd.mTexture, cmd.mMipIndex, cmd.mPixelBuffer );
		}
		CASE_END( )

		// Font
		CASE_BEGIN( CreateFontFromStream )
		{
			cmd.mRetObject = mDynamicRHI->CreateFontFromStream( cmd.mInitializer, cmd.mStreamReader );
		}
		CASE_END( )

		// Surface
		CASE_BEGIN( CreateTargetableSurface )
		{
			cmd.mRetObject = mDynamicRHI->CreateTargetableSurface( cmd.mWidth, cmd.mHeight, cmd.mFormat );
		}
		CASE_END( )

		CASE_BEGIN( CreateTargetableSurfaceFrom2DTexture )
		{
			cmd.mRetObject = mDynamicRHI->CreateTargetableSurface( cmd.mTexture );
		}
		CASE_END( )

		CASE_BEGIN( CreateTargetableSurfaceFromCubeTexture )
		{
			cmd.mRetObject = mDynamicRHI->CreateTargetableSurface( cmd.mTexture );
		}
		CASE_END( )

		// Viewport
		CASE_BEGIN( CreateViewport )
		{
			cmd.mRetObject = mDynamicRHI->CreateViewport( cmd.mAppHandle, cmd.mSize, cmd.mDeviceSize );
		}
		CASE_END( )

		// Render state
		CASE_BEGIN( SetRenderTarget )
		{
			mDynamicRHI->SetRenderTarget( cmd.mRenderTarget, cmd.mDepthStencil );
		}
		CASE_END( )

		CASE_BEGIN( SetBoundShader )
		{
			mDynamicRHI->SetBoundShader( cmd.mShader );
		}
		CASE_END( )

		CASE_BEGIN( SetDepthState )
		{
			mDynamicRHI->SetDepthState( cmd.mState );
		}
		CASE_END( )

		CASE_BEGIN( SetStencilState )
		{
			mDynamicRHI->SetStencilState( cmd.mState );
		}
		CASE_END( )

		CASE_BEGIN( SetBlendState )
		{
			mDynamicRHI->SetBlendState( cmd.mState );
		}
		CASE_END( )

		CASE_BEGIN( SetRasterizerState )
		{
			mDynamicRHI->SetRasterizerState( cmd.mState );
		}
		CASE_END( )

		CASE_BEGIN( SetRasterizerStateImmediate )
		{
			mDynamicRHI->SetRasterizerStateImmediate( *cmd.mInitializer );
		}
		CASE_END( )

		CASE_BEGIN( SetSamplerState )
		{
			mDynamicRHI->SetSamplerState( cmd.mSamplerIndex, cmd.mState, cmd.mTexture, cmd.mForce );
		}
		CASE_END( )

		CASE_BEGIN( SetViewport )
		{
			mDynamicRHI->SetViewport( cmd.mViewport );
		}
		CASE_END( )

		CASE_BEGIN( SetViewportWithRatio )
		{
			mDynamicRHI->SetViewport( cmd.mViewport, cmd.mRatio );
		}
		CASE_END( )

		CASE_BEGIN( SetScissorRect )
		{
			mDynamicRHI->SetScissorRect( cmd.mEnable, &cmd.mRect );
		}
		CASE_END( )

		CASE_BEGIN( BindViewport )
		{
			mDynamicRHI->BindViewport( cmd.mViewport );
		}
		CASE_END( )

		CASE_BEGIN( Present )
		{
			mDynamicRHI->Present( cmd.mViewport, cmd.mClearCaches );
		}
		CASE_END( )

		// Draw
		CASE_BEGIN( Clear )
		{
			mDynamicRHI->Clear( cmd.mClearColor, cmd.mColor, cmd.mClearDepth, cmd.mDepth, cmd.mClearStencil, cmd.mStencil );
		}
		CASE_END( )

		CASE_BEGIN( DrawPoint )
		{
			mDynamicRHI->DrawPoint( cmd.mPosition, cmd.mColor );
		}
		CASE_END( )

		CASE_BEGIN( DrawLine )
		{
			mDynamicRHI->DrawLine( cmd.mStart, cmd.mEnd, cmd.mColorStart, cmd.mColorEnd, cmd.mWidth );
		}
		CASE_END( )

		CASE_BEGIN( DrawRectangleI )
		{
			mDynamicRHI->DrawRectangle( cmd.mRect, cmd.mColor, cmd.mWidth );
		}
		CASE_END( )

		CASE_BEGIN( DrawRectangleF )
		{
			mDynamicRHI->DrawRectangle( cmd.mRect, cmd.mColor, cmd.mWidth );
		}
		CASE_END( )

		CASE_BEGIN( FillRectangleI )
		{
			mDynamicRHI->FillRectangle( cmd.mRect, cmd.mColor );
		}
		CASE_END( )

		CASE_BEGIN( FillRectangleF )
		{
			mDynamicRHI->FillRectangle( cmd.mRect, cmd.mColor );
		}
		CASE_END( )

		CASE_BEGIN( DrawSprite )
		{
			mDynamicRHI->DrawSprite( cmd.mPosition, cmd.mSize, cmd.mTexture, cmd.mColor, cmd.mUV1, cmd.mUV2, cmd.mIsRotate, cmd.mIsRound );
		}
		CASE_END( )

		CASE_BEGIN( DrawText )
		{
			mDynamicRHI->DrawText( cmd.mAlignment, cmd.mRect, cmd.mString, cmd.mFont, cmd.mColor );
		}
		CASE_END( )

		CASE_BEGIN( DrawPrimitive )
		{
			mDynamicRHI->DrawPrimitive( cmd.mType, cmd.mOffset, cmd.mNumber );
		}
		CASE_END( )

		CASE_BEGIN( DrawIndexedPrimitive )
		{
			mDynamicRHI->DrawIndexedPrimitive( cmd.mType, cmd.mStartIndex, cmd.mNumber );
		}
		CASE_END( )

		default:
			EGE_ASSERT( 0 );
			break;
	}
}

_dword RHIAsyncDrvThread::OnRunThread( const QwordParameters2& parameters )
{
	while ( mThreadID != 0 )
	{
		if ( mCurCommandBufferIndex < mCurCommandBufferNumber )
		{
			// Get the first command
			RHIAsyncCommand* command = mCommands[ mCurCommandBufferIndex ++ ];
			EGE_ASSERT( command != _null );

			// Process it
			ProcessCommand( *command );

			// Let the wait operation go
			if ( command->mWaitEvent != _null )
				command->mWaitEvent->Set( );
		}
	}

	return 0;
}

_void RHIAsyncDrvThread::PostCommand( RHIAsyncCommand* command )
{
	EGE_ASSERT( mCurCommandBufferNumber < _MAX_COMMANDS_NUMBER_PRE_CYCLE );

	mCommands[ mCurCommandBufferNumber ++ ] = command;
}

_void RHIAsyncDrvThread::ResetCommandsBuffer( )
{
	// Make sure we do not have something to do
	EGE_ASSERT( mCurCommandBufferIndex == mCurCommandBufferNumber );

	mCurCommandBufferIndex	= 0;
	mCurCommandBufferNumber	= 0;
}

//----------------------------------------------------------------------------
// RHIAsyncDrv Implementation
//----------------------------------------------------------------------------

RHIAsyncDrv::RHIAsyncDrv( IDynamicRHI* dynamic_rhi ) : mDynamicRHI( dynamic_rhi )
{
	mAllocator = GetInterfaceFactory( )->CreateStackAllocator( _MAX_BUFFER_SIZE );

	mEvent.Create( _true, _false );

	mAsyncThread = new RHIAsyncDrvThread( mDynamicRHI );
	mAsyncThread->Create( 99, _false, L"RHIAsyncThread", QwordParameters2::cNull );

	// Add dummy operation
	//_BEGIN_COMMAND( Dummy );
	//_END_COMMAND( );
}

RHIAsyncDrv::~RHIAsyncDrv( )
{
	EGE_DELETE( mAsyncThread );
}

_ubool RHIAsyncDrv::Initialize( )
{
	_BEGIN_COMMAND_WAIT( Initialize );
	_END_COMMAND_WAIT_RETURN_VALUE( );
}

_void RHIAsyncDrv::Finalize( )
{
	_BEGIN_COMMAND_WAIT( Finalize );
	_END_COMMAND_WAIT_RETURN_NONE( );
}

_ubool RHIAsyncDrv::ResetResources( IApplication* application )
{
	_BEGIN_COMMAND_WAIT( ResetResources );
		cmd->mApplication = application;
	_END_COMMAND_WAIT_RETURN_VALUE( );
}

_void RHIAsyncDrv::UnloadResources( )
{
	_BEGIN_COMMAND_WAIT( UnloadResources );
	_END_COMMAND_WAIT_RETURN_NONE( );
}

IResourceManagerRHI* RHIAsyncDrv::GetResourceManager( )
{
	return mDynamicRHI->GetResourceManager( );
}

RenderStatsRHI& RHIAsyncDrv::GetRenderStats( )
{
	return mDynamicRHI->GetRenderStats( );
}

const RenderStatsRHI& RHIAsyncDrv::GetRenderStats( ) const
{
	return mDynamicRHI->GetRenderStats( );
}

_void RHIAsyncDrv::ClearRenderStats( )
{
	mDynamicRHI->ClearRenderStats( );
}

IAllocator* RHIAsyncDrv::GetAllocator( )
{
	return mDynamicRHI->GetAllocator( );
}

_void RHIAsyncDrv::ClearCaches( )
{
	mDynamicRHI->ClearCaches( );
}

_dword RHIAsyncDrv::GetRenderContextsNumber( )
{
	return mDynamicRHI->GetRenderContextsNumber( );
}

_ubool RHIAsyncDrv::IsSupportVAO( )
{
	return mDynamicRHI->IsSupportVAO( );
}

_ubool RHIAsyncDrv::IsSupportInstancedRendering( )
{
	return mDynamicRHI->IsSupportInstancedRendering( );
}

PointU RHIAsyncDrv::GetOVRFovTextureSize( _dword index )
{
	return mDynamicRHI->GetOVRFovTextureSize( index );
}

_void RHIAsyncDrv::SetOVRRenderTargetTexID( _dword index, _dword tex_id, const PointU& tex_size )
{
	mDynamicRHI->SetOVRRenderTargetTexID( index, tex_id, tex_size );
}

_void RHIAsyncDrv::SynOVRDeviceRegion( )
{
	mDynamicRHI->SynOVRDeviceRegion( );
}

const OVREyeRHI& RHIAsyncDrv::GetOVREyeInfo( _dword index )
{
	return mDynamicRHI->GetOVREyeInfo( index );
}

SamplerStateRHIPassRef RHIAsyncDrv::CreateSamplerState( const SamplerStateInitializerRHI& initializer )
{
	return mDynamicRHI->CreateSamplerState( initializer );
}

RasterizerStateRHIPassRef RHIAsyncDrv::CreateRasterizerState( const RasterizerStateInitializerRHI& initializer )
{
	return mDynamicRHI->CreateRasterizerState( initializer );
}

DepthStateRHIPassRef RHIAsyncDrv::CreateDepthState( const DepthStateInitializerRHI& initializer )
{
	return mDynamicRHI->CreateDepthState( initializer );
}

StencilStateRHIPassRef RHIAsyncDrv::CreateStencilState( const StencilStateInitializerRHI& initializer )
{
	return mDynamicRHI->CreateStencilState( initializer );
}

BlendStateRHIPassRef RHIAsyncDrv::CreateBlendState( const BlendStateInitializerRHI& initializer )
{
	return mDynamicRHI->CreateBlendState( initializer );
}

SamplerStateInitializerRHI RHIAsyncDrv::GetSamplerState( const SamplerStateRHI* state ) const
{
	return mDynamicRHI->GetSamplerState( state );
}

RasterizerStateInitializerRHI RHIAsyncDrv::GetRasterizerState( const RasterizerStateRHI* state ) const
{
	return mDynamicRHI->GetRasterizerState( state );
}

DepthStateInitializerRHI RHIAsyncDrv::GetDepthState( const DepthStateRHI* state ) const
{
	return mDynamicRHI->GetDepthState( state );
}

StencilStateInitializerRHI RHIAsyncDrv::GetStencilState( const StencilStateRHI* state ) const
{
	return mDynamicRHI->GetStencilState( state );
}

BlendStateInitializerRHI RHIAsyncDrv::GetBlendState( const BlendStateRHI* state ) const
{
	return mDynamicRHI->GetBlendState( state );
}

const ShaderCompileConfigInfo& RHIAsyncDrv::GetShaderCompileConfigInfo( )
{
	return mDynamicRHI->GetShaderCompileConfigInfo( );
};

PixelShaderRHIPassRef RHIAsyncDrv::CreatePixelShader( AStringPtr code )
{
	_BEGIN_COMMAND_WAIT( CreatePixelShader );
		cmd->mCode = code;
	_END_COMMAND_WAIT_RETURN_OBJECT( );
}

VertexShaderRHIPassRef RHIAsyncDrv::CreateVertexShader( AStringPtr code )
{
	_BEGIN_COMMAND_WAIT( CreateVertexShader );
		cmd->mCode = code;
	_END_COMMAND_WAIT_RETURN_OBJECT( );
}

BoundShaderRHIPassRef RHIAsyncDrv::CreateBoundShader( VertexShaderRHI* vertexshader, PixelShaderRHI* pixelshader )
{
	_BEGIN_COMMAND_WAIT( CreateBoundShader );
		cmd->mVertexShader	= vertexshader;
		cmd->mPixelShader	= pixelshader;
	_END_COMMAND_WAIT_RETURN_OBJECT( );
}

PixelShaderRHI* RHIAsyncDrv::GetPixelShader( BoundShaderRHI* shader ) 
{
	return mDynamicRHI->GetPixelShader( shader );
}

VertexShaderRHI* RHIAsyncDrv::GetVertexShader( BoundShaderRHI* shader ) 
{
	return mDynamicRHI->GetVertexShader( shader );
}

_ubool RHIAsyncDrv::GetPixelShaderCode( PixelShaderRHI* ps, AString& code )
{
	return mDynamicRHI->GetPixelShaderCode( ps, code );
}

_ubool RHIAsyncDrv::GetVertexShaderCode( VertexShaderRHI* vs, AString& code )
{
	return mDynamicRHI->GetVertexShaderCode( vs, code );
}

_dword RHIAsyncDrv::GetShaderResourceID( const BoundShaderRHI* shader ) const
{
	return mDynamicRHI->GetShaderResourceID( shader );
}

VertexDeclarationRHIPassRef RHIAsyncDrv::CreateVertexDeclaration( const VertexElementRHIArray& elements )
{
	return mDynamicRHI->CreateVertexDeclaration( elements );
}

_dword RHIAsyncDrv::GetVertexDeclarationVertexType( VertexDeclarationRHI* declaration )
{
	return mDynamicRHI->GetVertexDeclarationVertexType( declaration );
}

_dword RHIAsyncDrv::GetVertexDeclarationStride( VertexDeclarationRHI* declaration )
{
	return mDynamicRHI->GetVertexDeclarationStride( declaration );
}

const VertexElementRHIArray& RHIAsyncDrv::GetVertexDeclarationDefine( VertexDeclarationRHI* declaration )
{
	return mDynamicRHI->GetVertexDeclarationDefine( declaration );
}

_dword RHIAsyncDrv::ActiveUniformBuffer( BoundShaderRHI* shader, _UNIFORM_BUFFER_DATA_TYPE type, AStringPtr name, _dword size )
{
	_BEGIN_COMMAND_WAIT( ActiveUniformBuffer );
		cmd->mShader	= shader;
		cmd->mType		= type;
		cmd->mName		= name;
		cmd->mSize		= size;
	_END_COMMAND_WAIT_RETURN_VALUE( );
}

_ubool RHIAsyncDrv::UpdateUniformBuffer( BoundShaderRHI* shader, _dword location, const _void* buffer, _dword size )
{
	_BEGIN_COMMAND( UpdateUniformBuffer );
		cmd->mShader	= shader;
		cmd->mLocation	= location;
		cmd->mBuffer	= buffer;
		cmd->mSize		= size;
	_END_COMMAND( );

	return _true;
}

_ubool RHIAsyncDrv::SetUniformPropertyValue( BoundShaderRHI* shader, AStringPtr name, _long value )
{
	_BEGIN_COMMAND_WAIT( SetUniformPropertyValue );
		cmd->mShader	= shader;
		cmd->mName		= name;
		cmd->mValue		= value;
	_END_COMMAND_WAIT_RETURN_VALUE( );
}

IndexBufferRHIPassRef RHIAsyncDrv::CreateIndexBuffer( _dword stride, _dword size, const _byte* buffer, _dword usage_flags, _RESOURCE_DRAW_TYPE draw_type )
{
	_BEGIN_COMMAND_WAIT( CreateIndexBuffer );
		cmd->mStride		= stride;
		cmd->mSize			= size;
		cmd->mBuffer		= buffer;
		cmd->mUsageFlags	= usage_flags;
		cmd->mDrawType		= draw_type;
	_END_COMMAND_WAIT_RETURN_OBJECT( );
}

_void* RHIAsyncDrv::LockIndexBuffer( IndexBufferRHI* indexbuffer, _dword offset, _dword size, _RESOURCE_LOCK_FLAG flag )
{
	return mDynamicRHI->LockIndexBuffer( indexbuffer, offset, size, flag );
}

_void RHIAsyncDrv::UnlockIndexBuffer( IndexBufferRHI* indexbuffer )
{
	_BEGIN_COMMAND_WAIT( UnlockIndexBuffer );
		cmd->mIndexBuffer	= indexbuffer;
	_END_COMMAND_WAIT_RETURN_NONE( );
}

_dword RHIAsyncDrv::GetIndexBufferStride( IndexBufferRHI* indexbuffer )
{
	return mDynamicRHI->GetIndexBufferStride( indexbuffer );
}

_dword RHIAsyncDrv::GetIndexBufferSize( IndexBufferRHI* indexbuffer )
{
	return mDynamicRHI->GetIndexBufferSize( indexbuffer );
}

_ubool RHIAsyncDrv::UpdateIndexBuffer( IndexBufferRHI* index_buffer, _dword offset, _dword size, const _byte* buffer, _ubool discard )
{
	_BEGIN_COMMAND_WAIT( UpdateIndexBuffer );
		cmd->mIndexBuffer	= index_buffer;
		cmd->mOffset		= offset;
		cmd->mSize			= size;
		cmd->mBuffer		= buffer;
		cmd->mDiscard		= discard;
	_END_COMMAND_WAIT_RETURN_NONE( );

	return _true;
}

_ubool RHIAsyncDrv::ResizeIndexBuffer( IndexBufferRHI* index_buffer, _dword size )
{
	_BEGIN_COMMAND_WAIT( ResizeIndexBuffer );
		cmd->mIndexBuffer	= index_buffer;
		cmd->mSize			= size;
	_END_COMMAND_WAIT_RETURN_VALUE( );
}

_dword RHIAsyncDrv::GetIndexBufferResID( IndexBufferRHI* index_buffer )
{
	return mDynamicRHI->GetIndexBufferResID( index_buffer );
}

VertexBufferRHIPassRef RHIAsyncDrv::CreateVertexBuffer( _dword stride, _dword size, const _byte* buffer, _dword usage_flags, _RESOURCE_DRAW_TYPE draw_type )
{
	_BEGIN_COMMAND_WAIT( CreateVertexBuffer );
		cmd->mStride		= stride;
		cmd->mSize			= size;
		cmd->mBuffer		= buffer;
		cmd->mUsageFlags	= usage_flags;
		cmd->mDrawType		= draw_type;
	_END_COMMAND_WAIT_RETURN_OBJECT( );
}

_void* RHIAsyncDrv::LockVertexBuffer( VertexBufferRHI* vertexbuffer, _dword offset, _dword size, _RESOURCE_LOCK_FLAG flag )
{
	return mDynamicRHI->LockVertexBuffer( vertexbuffer, offset, size, flag );
}

_void RHIAsyncDrv::UnlockVertexBuffer( VertexBufferRHI* vertexbuffer )
{
	_BEGIN_COMMAND( UnlockVertexBuffer );
		cmd->mVertexBuffer	= vertexbuffer;
	_END_COMMAND( );
}

_dword RHIAsyncDrv::GetVertexBufferStride( VertexBufferRHI* vertexbuffer )
{
	return mDynamicRHI->GetVertexBufferStride( vertexbuffer );
}

_dword RHIAsyncDrv::GetVertexBufferSize( VertexBufferRHI* vertexbuffer )
{
	return mDynamicRHI->GetVertexBufferSize( vertexbuffer );
}

_ubool RHIAsyncDrv::UpdateVertexBuffer( VertexBufferRHI* vertexbuffer, _dword offset, _dword size, const _byte* buffer, _ubool discard )
{
	_BEGIN_COMMAND_WAIT( UpdateVertexBuffer );
		cmd->mVertexBuffer	= vertexbuffer;
		cmd->mOffset		= offset;
		cmd->mSize			= size;
		cmd->mBuffer		= buffer;
		cmd->mDiscard		= discard;
	_END_COMMAND_WAIT_RETURN_NONE( );

	return _true;
}

_ubool RHIAsyncDrv::ResizeVertexBuffer( VertexBufferRHI* vertexbuffer, _dword size )
{
	_BEGIN_COMMAND( ResizeVertexBuffer );
		cmd->mVertexBuffer	= vertexbuffer;
		cmd->mSize			= size;
	_END_COMMAND( );

	return _true;
}

_dword RHIAsyncDrv::GetVertexBufferResID( VertexBufferRHI* vertexbuffer )
{
	return mDynamicRHI->GetVertexBufferResID( vertexbuffer );
}

VertexArrayRHIPassRef RHIAsyncDrv::CreateVertexArray( )
{
	_BEGIN_COMMAND_WAIT( CreateVertexArray );
	_END_COMMAND_WAIT_RETURN_OBJECT( );
}

_void RHIAsyncDrv::BindVertexArray( VertexArrayRHI* vertex_array )
{
	_BEGIN_COMMAND( BindVertexArray );
		cmd->mVertexArray = vertex_array;
	_END_COMMAND( );
}

_void RHIAsyncDrv::UnbindVertexArray( )
{
	_BEGIN_COMMAND( UnbindVertexArray );
	_END_COMMAND( );
}

_ubool RHIAsyncDrv::SetVertexArrayDecl( VertexArrayRHI* vertex_array, VertexDeclarationRHI* declaration, VertexBufferRHI* vbo, IndexBufferRHI* ibo )
{
	_BEGIN_COMMAND( SetVertexArrayDecl );
		cmd->mVertexArray	= vertex_array;
		cmd->mDeclaration	= declaration;
		cmd->mVertexBuffer	= vbo;
		cmd->mIndexBuffer	= ibo;
	_END_COMMAND( );

	return _true;
}

_dword RHIAsyncDrv::GetVertexArrayResID( VertexArrayRHI* vertex_array )
{
	return mDynamicRHI->GetVertexArrayResID( vertex_array );
}

const TextureStatsRHI& RHIAsyncDrv::GetTextureStats( )
{
	return mDynamicRHI->GetTextureStats( );
}

TextureCubeRHIPassRef RHIAsyncDrv::CreateTextureCube( WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, _dword flags, const _byte** pixel, WStringPtr* res_name_table )
{
	_BEGIN_COMMAND_WAIT( CreateTextureCube );
		cmd->mResName		= res_name;
		cmd->mWidth			= width;
		cmd->mHeight		= height;
		cmd->mFormat		= format;
		cmd->mNumMips		= nummips;
		cmd->mFlags			= flags;
		cmd->mPixel			= pixel;
		cmd->mResNameTable	= res_name_table;
	_END_COMMAND_WAIT_RETURN_OBJECT( );
}

TextureCubeRHIPassRef RHIAsyncDrv::CreateTextureCubeFromImageFiles( WStringPtr res_name, IImageFile** image_files, _dword nummips, _dword flags, WStringPtr* res_name_table, _ubool auto_rotate )
{
	_BEGIN_COMMAND_WAIT( CreateTextureCubeFromImageFiles );
		cmd->mResName		= res_name;
		cmd->mFlags			= flags;
		cmd->mNumMips		= nummips;
		cmd->mImageFiles	= image_files;
		cmd->mResNameTable	= res_name_table;
		cmd->mIsAutoRotate	= auto_rotate;
	_END_COMMAND_WAIT_RETURN_OBJECT( );
}

const PointU& RHIAsyncDrv::GetTextureCubeSize( TextureCubeRHI* texture ) const
{
	return mDynamicRHI->GetTextureCubeSize( texture );
}

_dword RHIAsyncDrv::GetTextureCubeSizeInBytes( TextureCubeRHI* texture ) const
{
	return mDynamicRHI->GetTextureCubeSizeInBytes( texture );
}

Texture2DRHIPassRef RHIAsyncDrv::CreateTexture2D( WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, _dword flags, const _byte* pixel )
{
	_BEGIN_COMMAND_WAIT( CreateTexture2D );
		cmd->mResName	= res_name;
		cmd->mWidth		= width;
		cmd->mHeight	= height;
		cmd->mFormat	= format;
		cmd->mNumMips	= nummips;
		cmd->mFlags		= flags;
		cmd->mPixel		= pixel;
	_END_COMMAND_WAIT_RETURN_OBJECT( );
}

Texture2DRHIPassRef RHIAsyncDrv::CreateTexture2DFromImageFile( WStringPtr res_name, IImageFile* image_file, _dword nummips, _dword flags )
{
	_BEGIN_COMMAND_WAIT( CreateTexture2DFromImageFile );
		cmd->mResName	= res_name;
		cmd->mImageFile	= image_file;
		cmd->mNumMips	= nummips;
		cmd->mFlags		= flags;
	_END_COMMAND_WAIT_RETURN_OBJECT( );
}

Texture2DRHIPassRef RHIAsyncDrv::CreateTexture2DWithMipmaps( WStringPtr res_name, _dword width, _dword height, _PIXEL_FORMAT format, _dword nummips, _dword flags, const _byte** pixels )
{
	_BEGIN_COMMAND_WAIT( CreateTexture2DWithMipmaps );
		cmd->mResName	= res_name;
		cmd->mWidth		= width;
		cmd->mHeight	= height;
		cmd->mFormat	= format;
		cmd->mNumMips	= nummips;
		cmd->mFlags		= flags;
		cmd->mPixels	= pixels;
	_END_COMMAND_WAIT_RETURN_OBJECT( );
}

_ubool RHIAsyncDrv::UpdateTexture2D( Texture2DRHI* texture, _dword mipindex, const RectU& rect, const _byte* pixel )
{
	_BEGIN_COMMAND_WAIT( UpdateTexture2D );
		cmd->mTexture	= texture;
		cmd->mMipIndex	= mipindex;
		cmd->mRect		= rect;
		cmd->mPixel		= pixel;
	_END_COMMAND_WAIT_RETURN_VALUE( );
}

_void* RHIAsyncDrv::LockTexture2D( Texture2DRHI* texture, _dword mipindex, _dword& stride, _RESOURCE_LOCK_FLAG flag )
{
	_BEGIN_COMMAND_WAIT( LockTexture2D );
		cmd->mTexture	= texture;
		cmd->mMipIndex	= mipindex;
		cmd->mStride	= &stride;
		cmd->mFlag		= flag;
	_END_COMMAND_WAIT_RETURN_PTR( );
}

_void RHIAsyncDrv::UnlockTexture2D( Texture2DRHI* texture, _dword mipindex )
{
	_BEGIN_COMMAND_WAIT( UnlockTexture2D );
		cmd->mTexture	= texture;
		cmd->mMipIndex	= mipindex;
	_END_COMMAND_WAIT_RETURN_NONE( );
}

_ubool RHIAsyncDrv::ReadTexture2DMipPixel( const Texture2DRHI* texture, _dword mipindex, _byte* pixel_buffer )
{
	_BEGIN_COMMAND_WAIT( ReadTexture2DMipPixel );
		cmd->mTexture		= texture;
		cmd->mMipIndex		= mipindex;
		cmd->mPixelBuffer	= pixel_buffer;
	_END_COMMAND_WAIT_RETURN_VALUE( );
}

_dword RHIAsyncDrv::GetTexture2DResID( const Texture2DRHI* texture ) const
{
	return mDynamicRHI->GetTexture2DResID( texture );
}

const PointU& RHIAsyncDrv::GetTexture2DSize( const Texture2DRHI* texture ) const
{
	return mDynamicRHI->GetTexture2DSize( texture );
}

_dword RHIAsyncDrv::GetTexture2DMipNumber( const Texture2DRHI* texture ) const
{
	return mDynamicRHI->GetTexture2DMipNumber( texture );
}

_dword RHIAsyncDrv::GetTexture2DMipSize( const Texture2DRHI* texture, _dword mipindex ) const
{
	return mDynamicRHI->GetTexture2DMipSize( texture, mipindex );
}

_dword RHIAsyncDrv::GetTexture2DStride( const Texture2DRHI* texture, _dword mipindex ) const
{
	return mDynamicRHI->GetTexture2DStride( texture, mipindex );
}

const FlagsObject& RHIAsyncDrv::GetTexture2DFlags( const Texture2DRHI* texture ) const
{
	return mDynamicRHI->GetTexture2DFlags( texture );
}

_PIXEL_FORMAT RHIAsyncDrv::GetTexture2DPixelFormat( const Texture2DRHI* texture ) const
{
	return mDynamicRHI->GetTexture2DPixelFormat( texture );
}

_dword RHIAsyncDrv::GetTexture2DSizeInBytes( Texture2DRHI* texture ) const
{
	return mDynamicRHI->GetTexture2DSizeInBytes( texture );
}

SamplerStateInitializerRHI RHIAsyncDrv::GetTexture2DSamplerStateInfo( Texture2DRHI* texture ) const
{
	return mDynamicRHI->GetTexture2DSamplerStateInfo( texture );
}

_void RHIAsyncDrv::LockTexture2DSamplerState( Texture2DRHI* texture, _ubool lock )
{
	return mDynamicRHI->LockTexture2DSamplerState( texture, lock );
}

FontRHIPassRef RHIAsyncDrv::CreateFontFromStream( const FontInitializerRHI& initializer, IStreamReader* stream_reader )
{
	_BEGIN_COMMAND_WAIT( CreateFontFromStream );
		cmd->mInitializer	= initializer;
		cmd->mStreamReader	= stream_reader;
	_END_COMMAND_WAIT_RETURN_OBJECT( );
}

FontRHIPassRef RHIAsyncDrv::CloneFont( const FontRHI* font )
{
	return mDynamicRHI->CloneFont( font );
}

const FontInitializerRHI& RHIAsyncDrv::GetFontInfo( FontRHI* font ) const
{
	return mDynamicRHI->GetFontInfo( font );
}

_float RHIAsyncDrv::GetCharAdvance( FontRHI* font, _dword code ) const
{
	return mDynamicRHI->GetCharAdvance( font, code );
}

_float RHIAsyncDrv::GetCharMaxHeight( FontRHI* font ) const
{
	return mDynamicRHI->GetCharMaxHeight( font );
}

IFontFace* RHIAsyncDrv::GetFontFace( FontRHI* font ) const
{
	return mDynamicRHI->GetFontFace( font );
}

const FontCodeRHI* RHIAsyncDrv::GetFontCode( FontRHI* font, _dword code, _dword stroke_size ) const
{
	return mDynamicRHI->GetFontCode( font, code, stroke_size );
}

_void RHIAsyncDrv::ClearFontCaches( FontRHI* font )
{
	mDynamicRHI->ClearFontCaches( font );
}

SurfaceRHIPassRef RHIAsyncDrv::CreateTargetableSurface( Texture2DRHI* texture )
{
	_BEGIN_COMMAND_WAIT( CreateTargetableSurfaceFrom2DTexture );
		cmd->mTexture = texture;
	_END_COMMAND_WAIT_RETURN_OBJECT( );
}

SurfaceRHIPassRef RHIAsyncDrv::CreateTargetableSurface( TextureCubeRHI* texture )
{
	_BEGIN_COMMAND_WAIT( CreateTargetableSurfaceFromCubeTexture );
		cmd->mTexture = texture;
	_END_COMMAND_WAIT_RETURN_OBJECT( );
}

SurfaceRHIPassRef RHIAsyncDrv::CreateTargetableSurface( _dword width, _dword height, _PIXEL_FORMAT format )
{
	_BEGIN_COMMAND_WAIT( CreateTargetableSurface );
		cmd->mWidth		= width;
		cmd->mHeight	= height;
		cmd->mFormat	= format;
	_END_COMMAND_WAIT_RETURN_OBJECT( );
}

const PointU& RHIAsyncDrv::GetSurfaceSize( SurfaceRHI* surface ) const
{
	return mDynamicRHI->GetSurfaceSize( surface );
}

Texture2DRHI* RHIAsyncDrv::GetSurfaceTexture2D( SurfaceRHI* surface ) const
{
	return mDynamicRHI->GetSurfaceTexture2D( surface );
}

TextureCubeRHI* RHIAsyncDrv::GetSurfaceTextureCube( SurfaceRHI* surface ) const
{
	return mDynamicRHI->GetSurfaceTextureCube( surface );
}

_ubool RHIAsyncDrv::SetSurfaceTextureCubeFaceIndex( SurfaceRHI* surface, _dword index )
{
	return mDynamicRHI->SetSurfaceTextureCubeFaceIndex( surface, index );
}

_dword RHIAsyncDrv::GetSurfaceTextureCubeFaceIndex( SurfaceRHI* surface ) const
{
	return mDynamicRHI->GetSurfaceTextureCubeFaceIndex( surface );
}

ViewportRHIPassRef RHIAsyncDrv::CreateViewport( _handle app_handle, const PointU& size, const PointU& device_size )
{
	_BEGIN_COMMAND_WAIT( CreateViewport );
		cmd->mAppHandle		= app_handle;
		cmd->mSize			= size;
		cmd->mDeviceSize	= device_size;
	_END_COMMAND_WAIT_RETURN_OBJECT( );
}

_ubool RHIAsyncDrv::ResizeViewport( ViewportRHI* viewport, const PointU& size )
{
	return mDynamicRHI->ResizeViewport( viewport, size );
}

const PointU& RHIAsyncDrv::GetViewportSize( ViewportRHI* viewport ) const
{
	return mDynamicRHI->GetViewportSize( viewport );
}

_void RHIAsyncDrv::SetLineWidth( _float width )
{
	mDynamicRHI->SetLineWidth( width );
}

_void RHIAsyncDrv::SetRenderTarget( SurfaceRHI* rendertarget, SurfaceRHI* depthstencil )
{
	_BEGIN_COMMAND( SetRenderTarget );
		cmd->mRenderTarget	= rendertarget;
		cmd->mDepthStencil	= depthstencil;
	_END_COMMAND( );
}

_void RHIAsyncDrv::ReadPixels( const RectU& rect, _PIXEL_FORMAT format, _byte* pixels )
{
	mDynamicRHI->ReadPixels( rect, format, pixels );
}

_void RHIAsyncDrv::SetBoundShader( BoundShaderRHI* shader )
{
	_BEGIN_COMMAND( SetBoundShader );
		cmd->mShader = shader;
	_END_COMMAND( );
}

_void RHIAsyncDrv::SetDepthState( const DepthStateRHI* state )
{
	_BEGIN_COMMAND( SetDepthState );
		cmd->mState = state;
	_END_COMMAND( );
}
 
_void RHIAsyncDrv::SetStencilState( const StencilStateRHI* state )
{
	_BEGIN_COMMAND( SetStencilState );
		cmd->mState = state;
	_END_COMMAND( );
}

_void RHIAsyncDrv::SetBlendState( const BlendStateRHI* state )
{
	_BEGIN_COMMAND( SetBlendState );
		cmd->mState = state;
	_END_COMMAND( );
}
 
_void RHIAsyncDrv::SetRasterizerState( const RasterizerStateRHI* state )
{
	_BEGIN_COMMAND( SetRasterizerState );
		cmd->mState = state;
	_END_COMMAND( );
}

_void RHIAsyncDrv::SetRasterizerStateImmediate( const RasterizerStateInitializerRHI& initializer )
{
	_BEGIN_COMMAND_WAIT( SetRasterizerStateImmediate );
		cmd->mInitializer = &initializer;
	_END_COMMAND_WAIT_RETURN_NONE( );
}

_void RHIAsyncDrv::SetSamplerState( _dword samplerindex, const SamplerStateRHI* state, TextureRHI* texture, _ubool force )
{
	_BEGIN_COMMAND( SetSamplerState );
		cmd->mSamplerIndex	= samplerindex;
		cmd->mState			= state;
		cmd->mTexture		= texture;
		cmd->mForce			= force;
	_END_COMMAND( );
}

_void RHIAsyncDrv::SetViewport( const Viewport& viewport )
{
	_BEGIN_COMMAND( SetViewport );
		cmd->mViewport	= viewport;
	_END_COMMAND( );
}

_void RHIAsyncDrv::SetViewport( const Viewport& viewport, const Ratio& ratio )
{
	_BEGIN_COMMAND( SetViewportWithRatio );
		cmd->mViewport	= viewport;
		cmd->mRatio		= ratio;
	_END_COMMAND( );
}

_void RHIAsyncDrv::SetScissorRect( _ubool enable, const RectU* rect )
{
	_BEGIN_COMMAND( SetScissorRect );
		cmd->mEnable	= enable;
		cmd->mRect		= rect ? *rect : RectU::cNull;
	_END_COMMAND( );
}

_void RHIAsyncDrv::BindViewport( ViewportRHI* viewport )
{
	_BEGIN_COMMAND( BindViewport );
		cmd->mViewport		= viewport;
	_END_COMMAND( );
}

_void RHIAsyncDrv::Present( ViewportRHI* viewport, _ubool clear_caches )
{
	_BEGIN_COMMAND( Present );
		cmd->mViewport		= viewport;
		cmd->mClearCaches	= clear_caches;
	_END_COMMAND( );

	// Reset the commands buffer
	mAsyncThread->ResetCommandsBuffer( );

	// Clear the allocated buffer
	mAllocator->FreeAll( );
}

_void RHIAsyncDrv::Clear( _ubool clearcolor, const Color& color, _ubool cleardepth, _float depth, _ubool clearstencil, _dword stencil )
{
	_BEGIN_COMMAND( Clear );
		cmd->mClearColor	= clearcolor;
		cmd->mColor			= color;
		cmd->mClearDepth	= cleardepth;
		cmd->mDepth			= depth;
		cmd->mClearStencil	= clearstencil;
		cmd->mStencil		= stencil;
	_END_COMMAND( );
}

_void RHIAsyncDrv::DrawPoint( const Vector2& position, const Color& color )
{
	_BEGIN_COMMAND( DrawPoint );
		cmd->mPosition	= position;
		cmd->mColor		= color;
	_END_COMMAND( );
}

_void RHIAsyncDrv::DrawLine( const Vector2& start, const Vector2& end, const Color& color, _float width )
{
	_BEGIN_COMMAND( DrawLine );
		cmd->mStart			= start;
		cmd->mEnd			= end;
		cmd->mColorStart	= color;
		cmd->mColorEnd		= color;
		cmd->mWidth			= width;
	_END_COMMAND( );
}

_void RHIAsyncDrv::DrawLine( const Vector2& start, const Vector2& end, const Color& color_start, const Color& color_end, _float width )
{
	_BEGIN_COMMAND( DrawLine );
		cmd->mStart			= start;
		cmd->mEnd			= end;
		cmd->mColorStart	= color_start;
		cmd->mColorEnd		= color_end;
		cmd->mWidth			= width;
	_END_COMMAND( );
}

_void RHIAsyncDrv::DrawRectangle( const RectI& rect, const Color& color, _dword width )
{
	_BEGIN_COMMAND( DrawRectangleI );
		cmd->mRect	= rect;
		cmd->mColor	= color;
		cmd->mWidth	= width;
	_END_COMMAND( );
}

_void RHIAsyncDrv::DrawRectangle( const RectF& rect, const Color& color, _float width )
{
	_BEGIN_COMMAND( DrawRectangleF );
		cmd->mRect	= rect;
		cmd->mColor	= color;
		cmd->mWidth	= width;
	_END_COMMAND( );
}

_void RHIAsyncDrv::FillRectangle( const RectI& rect, const Color& color )
{
	_BEGIN_COMMAND( FillRectangleI );
		cmd->mRect	= rect;
		cmd->mColor	= color;
	_END_COMMAND( );
}

_void RHIAsyncDrv::FillRectangle( const RectF& rect, const Color& color )
{
	_BEGIN_COMMAND( FillRectangleF );
		cmd->mRect	= rect;
		cmd->mColor	= color;
	_END_COMMAND( );
}

_void RHIAsyncDrv::DrawSprite( const Vector2& position, const Vector2& size, Texture2DRHI* texture, const Color& color, const Vector2& uv1, const Vector2& uv2, _ubool is_rotate, _ubool is_round )
{
	_BEGIN_COMMAND( DrawSprite );
		cmd->mPosition	= position;
		cmd->mSize		= size;
		cmd->mTexture	= texture;
		cmd->mColor		= color;
		cmd->mUV1		= uv1;
		cmd->mUV2		= uv2;
		cmd->mIsRotate	= is_rotate;
		cmd->mIsRound	= is_round;
	_END_COMMAND( );
}

_void RHIAsyncDrv::DrawText( _dword alignment, const RectF& rect, WStringPtr string, FontRHI* font, const Color& color )
{
	_BEGIN_COMMAND( DrawText );
		cmd->mAlignment	= alignment;
		cmd->mRect		= rect;
		cmd->mString	= string;
		cmd->mFont		= font;
		cmd->mColor		= color;
	_END_COMMAND( );
}

_void RHIAsyncDrv::DrawPrimitive( _PRIMITIVE_TYPE type, _dword offset, _dword number )
{
	_BEGIN_COMMAND( DrawPrimitive );
		cmd->mType		= type;
		cmd->mOffset	= offset;
		cmd->mNumber	= number;
	_END_COMMAND( );
}

_void RHIAsyncDrv::DrawIndexedPrimitive( _PRIMITIVE_TYPE type, _dword start_index, _dword number )
{
	_BEGIN_COMMAND( DrawIndexedPrimitive );
		cmd->mType			= type;
		cmd->mStartIndex	= start_index;
		cmd->mNumber		= number;
	_END_COMMAND( );
}

#endif