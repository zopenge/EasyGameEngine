//! @file     GLState.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GLSamplerStateInfo
//----------------------------------------------------------------------------

struct GLSamplerStateInfo : public CRCValueBaseInfo
{
	GLenum 	mMagFilter;
	GLenum 	mMinFilter;
	GLenum 	mAddressU;
	GLenum 	mAddressV;
	GLenum 	mAddressW;
	GLint	mTextureCompareMode;

	GLSamplerStateInfo( )
	{
		mMagFilter			= GL_NEAREST;
		mMinFilter			= GL_NEAREST_MIPMAP_LINEAR;
		mAddressU			= GL_REPEAT;
		mAddressV			= GL_REPEAT;
		mAddressW			= GL_REPEAT;
		mTextureCompareMode	= GL_NONE;
	}
	GLSamplerStateInfo( GLenum address_u, GLenum address_v, GLenum address_w )
	{
		mMagFilter			= GL_NEAREST;
		mMinFilter			= GL_NEAREST_MIPMAP_LINEAR;
		mAddressU			= address_u;
		mAddressV			= address_v;
		mAddressW			= address_w;
		mTextureCompareMode	= GL_NONE;
	}
	GLSamplerStateInfo( const GLSamplerStateInfo& info )
	{
		mMagFilter			= info.mMagFilter;
		mMinFilter			= info.mMinFilter;
		mAddressU			= info.mAddressU;
		mAddressV			= info.mAddressV;
		mAddressW			= info.mAddressW;
		mTextureCompareMode	= info.mTextureCompareMode;
	}
};

//----------------------------------------------------------------------------
// GLRasterizerStateInfo
//----------------------------------------------------------------------------

struct GLRasterizerStateInfo : public CRCValueBaseInfo
{
	_ubool	mEnableRedColorWrite;
	_ubool	mEnableGreenColorWrite;
	_ubool	mEnableBlueColorWrite;
	_ubool	mEnableAlphaColorWrite;
	_ubool	mCullModeEnabled;
	GLenum 	mCullMode;

	GLRasterizerStateInfo( )
	{
		mEnableRedColorWrite	= _true;
		mEnableGreenColorWrite	= _true;
		mEnableBlueColorWrite	= _true;
		mEnableAlphaColorWrite	= _true;
		mCullModeEnabled		= _false;
		mCullMode				= GL_NONE;
	}
	GLRasterizerStateInfo( const GLRasterizerStateInfo& info )
	{
		mEnableRedColorWrite	= info.mEnableRedColorWrite;
		mEnableGreenColorWrite	= info.mEnableGreenColorWrite;
		mEnableBlueColorWrite	= info.mEnableBlueColorWrite;
		mEnableAlphaColorWrite	= info.mEnableAlphaColorWrite;
		mCullModeEnabled		= info.mCullModeEnabled;
		mCullMode				= info.mCullMode;
	}
};

//----------------------------------------------------------------------------
// GLDepthStateInfo
//----------------------------------------------------------------------------

struct GLDepthStateInfo : public CRCValueBaseInfo
{
	_ubool	mZEnable;
	_ubool	mZWriteEnable;
	GLenum	mZFunc;

	GLDepthStateInfo( )
	{
		mZEnable		= GL_FALSE;
		mZWriteEnable	= GL_TRUE;
		mZFunc			= GL_LESS;
	}
	GLDepthStateInfo( const GLDepthStateInfo& info )
	{
		mZEnable		= info.mZEnable;
		mZWriteEnable	= info.mZWriteEnable;
		mZFunc			= info.mZFunc;
	}
};

//----------------------------------------------------------------------------
// GLStencilStateInfo
//----------------------------------------------------------------------------

struct GLStencilStateInfo : public CRCValueBaseInfo
{
	_ubool	mStencilEnable;
	_ubool	mTwoSidedStencilMode;
	GLenum 	mStencilFunc;
	GLenum 	mStencilFail;
	GLenum 	mStencilZFail;
	GLenum 	mStencilPass;
	GLenum 	mCCWStencilFunc;
	GLenum 	mCCWStencilFail;
	GLenum 	mCCWStencilZFail;
	GLenum 	mCCWStencilPass;
	_dword	mStencilReadMask;
	_dword	mStencilWriteMask;
	_dword	mStencilRef;

	GLStencilStateInfo( )
	{
		mStencilEnable			= GL_FALSE;
		mTwoSidedStencilMode	= GL_FALSE;
		mStencilFunc			= GL_ALWAYS;
		mStencilFail			= GL_KEEP;
		mStencilZFail			= GL_KEEP;
		mStencilPass			= GL_KEEP;
		mCCWStencilFunc			= GL_ALWAYS;
		mCCWStencilFail			= GL_KEEP;
		mCCWStencilZFail		= GL_KEEP;
		mCCWStencilPass			= GL_KEEP;
		mStencilReadMask		= 0xFFFFFFFF;
		mStencilWriteMask		= 0xFFFFFFFF;
		mStencilRef				= 0;
	}
	GLStencilStateInfo( const GLStencilStateInfo& info )
	{
		mStencilEnable			= info.mStencilEnable;
		mTwoSidedStencilMode	= info.mTwoSidedStencilMode;
		mStencilFunc			= info.mStencilFunc;
		mStencilFail			= info.mStencilFail;
		mStencilZFail			= info.mStencilZFail;
		mStencilPass			= info.mStencilPass;
		mCCWStencilFunc			= info.mCCWStencilFunc;
		mCCWStencilFail			= info.mCCWStencilFail;
		mCCWStencilZFail		= info.mCCWStencilZFail;
		mCCWStencilPass			= info.mCCWStencilPass;
		mStencilReadMask		= info.mStencilReadMask;
		mStencilWriteMask		= info.mStencilWriteMask;
		mStencilRef				= info.mStencilRef;
	}
};

//----------------------------------------------------------------------------
// GLBlendStateInfo
//----------------------------------------------------------------------------

struct GLBlendStateInfo : public CRCValueBaseInfo
{
	_ubool 		mAlphaBlendEnable;
	GLenum 		mColorSourceBlendFactor;
	GLenum 		mColorDestBlendFactor;

	_ubool		mSeparateAlphaBlendEnable;
	GLenum 		mAlphaSourceBlendFactor;
	GLenum 		mAlphaDestBlendFactor;

	GLBlendStateInfo( )
	{
		mAlphaBlendEnable			= GL_FALSE;
		mColorSourceBlendFactor		= GL_ONE;
		mColorDestBlendFactor		= GL_ZERO;

		mSeparateAlphaBlendEnable	= GL_FALSE;
		mAlphaSourceBlendFactor		= GL_ONE;
		mAlphaDestBlendFactor		= GL_ZERO;
	}
	GLBlendStateInfo( const GLBlendStateInfo& info )
	{
		mAlphaBlendEnable			= info.mAlphaBlendEnable;
		mColorSourceBlendFactor		= info.mColorSourceBlendFactor;
		mColorDestBlendFactor		= info.mColorDestBlendFactor;

		mSeparateAlphaBlendEnable	= info.mSeparateAlphaBlendEnable;
		mAlphaSourceBlendFactor		= info.mAlphaSourceBlendFactor;
		mAlphaDestBlendFactor		= info.mAlphaDestBlendFactor;
	}
};

//----------------------------------------------------------------------------
// GLStateBase
//----------------------------------------------------------------------------

template< typename SelfType, typename Type, typename StateInfo >
class GLStateBase : public Type
{
public:
	StateInfo mInfo;

protected:
	GLStateBase( )
	{

	}
	GLStateBase( const SelfType& state )
	{
		mInfo = state.mInfo;
	}

public:
	_ubool operator == ( const SelfType& state ) const
	{
		return mInfo.IsSame( state.mInfo );
	}
	_ubool operator != ( const SelfType& state ) const
	{
		return !(*this == state);
	}
};

//----------------------------------------------------------------------------
// GLSamplerState
//----------------------------------------------------------------------------

class GLSamplerState : public GLStateBase< GLSamplerState, SamplerStateRHI, GLSamplerStateInfo >
{
private:
	typedef GLStateBase< GLSamplerState, SamplerStateRHI, GLSamplerStateInfo > BaseClass;

public:
	GLSamplerState( )
	{
	}
	GLSamplerState( const GLSamplerState& state ) : BaseClass( state )
	{
	}
};

//----------------------------------------------------------------------------
// GLRasterizerState
//----------------------------------------------------------------------------

class GLRasterizerState : public GLStateBase< GLRasterizerState, RasterizerStateRHI, GLRasterizerStateInfo >
{
private:
	typedef GLStateBase< GLRasterizerState, RasterizerStateRHI, GLRasterizerStateInfo > BaseClass; 

public:
	GLRasterizerState( )
	{
	}
	GLRasterizerState( const GLRasterizerState& state ) : BaseClass( state )
	{
	}
};

//----------------------------------------------------------------------------
// GLDepthState
//----------------------------------------------------------------------------

class GLDepthState : public GLStateBase< GLDepthState, DepthStateRHI, GLDepthStateInfo >
{
private:
	typedef GLStateBase< GLDepthState, DepthStateRHI, GLDepthStateInfo > BaseClass;

public:
	GLDepthState( )
	{
	}
	GLDepthState( const GLDepthState& state ) : BaseClass( state )
	{
	}
};

//----------------------------------------------------------------------------
// GLStencilState
//----------------------------------------------------------------------------

class GLStencilState : public GLStateBase< GLStencilState, StencilStateRHI, GLStencilStateInfo >
{
private:
	typedef GLStateBase< GLStencilState, StencilStateRHI, GLStencilStateInfo > BaseClass;

public:
	GLStencilState( )
	{
	}
	GLStencilState( const GLStencilState& state ) : BaseClass( state )
	{
	}
};

//----------------------------------------------------------------------------
// GLBlendState
//----------------------------------------------------------------------------

class GLBlendState : public GLStateBase< GLBlendState, BlendStateRHI, GLBlendStateInfo >
{
private:
	typedef GLStateBase< GLBlendState, BlendStateRHI, GLBlendStateInfo > BaseClass;

public:
	GLBlendState( )
	{
	}
	GLBlendState( const GLBlendState& state ) : BaseClass( state )
	{
	}
};

//----------------------------------------------------------------------------
// GLTextureStage
//----------------------------------------------------------------------------

struct GLTextureStage
{
	GLenum					mTarget;
	GLuint					mResource;
	const SamplerStateRHI*	mState;

	_void Clear( )
	{
		mTarget		= GL_NONE;
		mResource	= 0;

		mState		= _null;
	}

	GLTextureStage( )
	{
		Clear( );
	}
};
typedef RawArray< GLTextureStage, 32 > GLTextureStageRawArray; // Max textures number : 32 ... I think that's enough ...

//----------------------------------------------------------------------------
// GLVertexElement
//----------------------------------------------------------------------------

struct GLVertexElement
{
	_dword 	mType;
	_byte	mOffset;
	_byte	mUsage;
	_byte	mStride;
	_byte	mNormalized;

	_ubool operator > ( const GLVertexElement& element ) const
	{
		if ( mOffset > element.mOffset )
			return _true;

		return _false;
	}

	_ubool operator < ( const GLVertexElement& element ) const
	{
		if ( mOffset < element.mOffset )
			return _true;

		return _false;
	}

	GLVertexElement( )
	{
		mType		= 0;
		mUsage		= 0;
		mOffset		= 0;
		mStride		= 0;
		mNormalized	= 0;
	}
};
typedef Array< GLVertexElement > GLVertexElementArray;

//----------------------------------------------------------------------------
// GLVertexAttributeCache
//----------------------------------------------------------------------------

struct GLVertexAttributeCache
{
	//!	True indicates enable the vertex attribute/declaration
	_byte	mIsEnabled;

	//!	True indicates normalized it
	_byte	mNormalized;
	//!	The vertex attribute cache info
	_word	mVBO;
	_word 	mType;
	_word 	mUsage;
	_word 	mOffset;
	_word 	mStride;

	GLVertexAttributeCache( ) 
	{
		mIsEnabled	= _false;

		mVBO		= 0;
		mType		= 0;
		mUsage		= 0;
		mOffset		= 0;
		mStride		= 0;
		mNormalized = _false;
	}
};

//----------------------------------------------------------------------------
// GLStateCache
//----------------------------------------------------------------------------

struct GLCachedState
{
	//!	The render state
	GLRasterizerStateInfo*	mRasterizerState;
	GLDepthStateInfo*		mDepthState;
	GLStencilStateInfo*		mStencilState;
	GLBlendStateInfo*		mBlendState;

	//!	The clear color
	Color*					mClearColor;
	//!	The depth clear value
	_float*					mClearDepth;
	//!	The stencil clear value
	_dword*					mClearStencil;

	//!	The line width
	_float					mLineWidth;

	//!	The viewport size
	PointU					mViewportOffset;
	PointU					mViewportSize;

	//!	The texture stage
	_dword					mActiveTextureIndex;
	GLTextureStageRawArray	mTextures;

	//!	The current GLSL program resource
	GLuint					mCurProgram; // GLSL shader
	//!	The current buffers
	GLuint					mCurFBO; // Frame Buffer Object
	GLuint					mCurRBO; // Render Buffer Object
	GLuint					mCurVBO; // Vertex Buffer Object
	GLuint 					mCurIBO; // Index Buffer Object
	GLuint 					mCurVAO; // Vertex Array Object

	//!	The current vertex array
	VertexArrayRHI*			mPendingVAO;
	//!	The current vertex buffer
	VertexBufferRHI*		mPendingVBO;
	//!	The current index buffer
	IndexBufferRHI*			mPendingIBO;

	//!	The current buffer set
	GLuint 					mReadBufferSet;
	GLuint 					mDrawBufferSet;

	//!	The vertex attribute cache
	GLVertexAttributeCache	mVertexAttributeCache[ _GL_ATTRI_MAXNUMBER ];

	//!	Clear cached state
	_void Clear( )
	{
		EGE_DELETE( mRasterizerState );
		EGE_DELETE( mDepthState );
		EGE_DELETE( mStencilState );
		EGE_DELETE( mBlendState );

		EGE_DELETE( mClearColor );
		EGE_DELETE( mClearDepth );
		EGE_DELETE( mClearStencil );

		mLineWidth			= 0.0f;

		mViewportOffset		= PointU::cZeroPoint;
		mViewportSize		= PointU::cZeroPoint;

		mActiveTextureIndex	= -1;
		for ( _dword i = 0; i < mTextures.Number( ); i ++ )
			mTextures[i].Clear( );

		mCurProgram			= 0;
		mCurFBO				= 0;
		mCurRBO				= 0;
		mCurVBO				= 0;
		mCurIBO				= 0;
		mCurVAO				= 0;

		mPendingVAO			= _null;
		mPendingVBO			= _null;
		mPendingIBO			= _null;

		mReadBufferSet 		= GL_BACK;
		mDrawBufferSet 		= GL_BACK;

		EGE_INIT_ARRAY( mVertexAttributeCache );
	}

	GLCachedState( )
	{
		mRasterizerState	= _null;
		mDepthState			= _null;
		mStencilState 		= _null;
		mBlendState 		= _null;

		mClearColor			= _null;
		mClearDepth			= _null;
		mClearStencil		= _null;

		Clear( );
	}
	~GLCachedState( )
	{

	}
};

}