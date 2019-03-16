//! @file     GraphicGlobals.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicClearBuffersInfo Implementation
//----------------------------------------------------------------------------

_void GraphicClearBuffersInfo::Reset( )
{
	mIsClearColor	= _false;
	mIsClearDepth	= _false;
	mIsClearStencil	= _false;
	mClearColor		= Color::cNull;
	mClearDepth		= 1.0f;
	mClearStencil	= 0;
}

GraphicClearBuffersInfo::GraphicClearBuffersInfo( )
{
	Reset( );
}

//----------------------------------------------------------------------------
// GraphicUniformBuffer Implementation
//----------------------------------------------------------------------------

GraphicUniformBuffer::GraphicUniformBuffer( )
{
	mBuffer = _null;
}

GraphicUniformBuffer::GraphicUniformBuffer( _UNIFORM_BUFFER_DATA_TYPE type, _dword location, _dword size, const AStringObj& name )
	: UniformBufferRHI( type, location, size, name )
{
	mBuffer = _null;
}

//----------------------------------------------------------------------------
// GraphicUVInfo Implementation
//----------------------------------------------------------------------------

Vector2 GraphicUVInfo::GetMin( ) const
{
	_float min_x = Math::Min( mLT.x, Math::Min( mLB.x, Math::Min( mRT.x, mRB.x ) ) );
	_float min_y = Math::Min( mLT.y, Math::Min( mLB.y, Math::Min( mRT.y, mRB.y ) ) );

	return Vector2( min_x, min_y );
}

Vector2 GraphicUVInfo::GetMax( ) const
{
	_float max_x = Math::Max( mLT.x, Math::Max( mLB.x, Math::Max( mRT.x, mRB.x ) ) );
	_float max_y = Math::Max( mLT.y, Math::Max( mLB.y, Math::Max( mRT.y, mRB.y ) ) );

	return Vector2( max_x, max_y );
}

Vector2 GraphicUVInfo::GetRange( ) const
{
	return GetMax( ) - GetMin( );
}

GraphicUVInfo::GraphicUVInfo( )
{
	mLT = Vector2( 0.0f, 0.0f );
	mLB = Vector2( 0.0f, 1.0f );
	mRT = Vector2( 1.0f, 0.0f );
	mRB = Vector2( 1.0f, 1.0f );
}

GraphicUVInfo::GraphicUVInfo( const Vector2& uv1, const Vector2& uv2 )
{
	mLT = uv1;
	mLB = Vector2( uv1.x, uv2.y );
	mRT = Vector2( uv2.x, uv1.y );
	mRB = uv2;
}

GraphicUVInfo::GraphicUVInfo( const Vector2& lt_uv, const Vector2& lb_uv, const Vector2& rt_uv, const Vector2& rb_uv )
{
	mLT = lt_uv;
	mLB = lb_uv;
	mRT = rt_uv;
	mRB = rb_uv;
}

//----------------------------------------------------------------------------
// GraphicMaskUVInfo Implementation
//----------------------------------------------------------------------------

GraphicMaskUVInfo::GraphicMaskUVInfo( )
{
	mIsRotate = _false;
}

GraphicMaskUVInfo::GraphicMaskUVInfo( _ubool is_rotate, const GraphicUVInfo& uv_info )
{
	mIsRotate				= is_rotate;
	(GraphicUVInfo&)(*this)	= uv_info;
}

//----------------------------------------------------------------------------
// GraphicVertexInfo Implementation
//----------------------------------------------------------------------------

_void GraphicVertexInfo::Init( const Vector2& pos, _dword color )
{
	mPosition.x		= pos.x;
	mPosition.y		= pos.y;
	mPosition.z		= 0.0f;
	mColor			= color;
	mSecondaryColor	= Color::cWhite;
	mUV1			= Vector2::cOrigin;
}

_void GraphicVertexInfo::Init( const Vector2& pos, _dword color, const Vector2& uv )
{
	mPosition.x		= pos.x;
	mPosition.y		= pos.y;
	mPosition.z		= 0.0f;
	mColor			= color;
	mSecondaryColor	= Color::cWhite;
	mUV1			= uv;
}

_void GraphicVertexInfo::Init( const Vector2& pos, _dword color, _dword secondary_color, const Vector2& uv )
{
	mPosition.x		= pos.x;
	mPosition.y		= pos.y;
	mPosition.z		= 0.0f;
	mColor			= color;
	mSecondaryColor	= secondary_color;
	mUV1			= uv;
}

_void GraphicVertexInfo::Init( const Vector2& pos, _dword color, _float u, _float v )
{
	mPosition.x		= pos.x;
	mPosition.y		= pos.y;
	mPosition.z		= 0.0f;
	mColor			= color;
	mSecondaryColor	= Color::cWhite;
	mUV1.x			= u;
	mUV1.y			= v;
}

_void GraphicVertexInfo::Init( const Vector2& pos, _dword color, _dword secondary_color, _float u, _float v )
{
	mPosition.x		= pos.x;
	mPosition.y		= pos.y;
	mPosition.z		= 0.0f;
	mColor			= color;
	mSecondaryColor	= secondary_color;
	mUV1.x			= u;
	mUV1.y			= v;
}

_void GraphicVertexInfo::Init( const Vector3& pos, _dword color )
{
	mPosition		= pos;
	mColor			= color;
	mSecondaryColor	= Color::cWhite;
	mUV1			= Vector2::cOrigin;
}

_void GraphicVertexInfo::Init( const Vector3& pos, _dword color, const Vector2& uv )
{
	mPosition		= pos;
	mColor			= color;
	mSecondaryColor	= Color::cWhite;
	mUV1			= uv;
}

_void GraphicVertexInfo::Init( const Vector3& pos, _dword color, _float u, _float v )
{
	mPosition		= pos;
	mColor			= color;
	mSecondaryColor	= Color::cWhite;
	mUV1.x			= u;
	mUV1.y			= v;
}

//----------------------------------------------------------------------------
// RenderableStatesInfo Implementation
//----------------------------------------------------------------------------

_ubool GraphicRenderStateInfo::IsEqual( const GraphicRenderStateInfo& info ) const
{
	if ( gDynamicRHI->IsSameBlendState( mBlendState, info.mBlendState ) == _false )
		return _false;

	if ( gDynamicRHI->IsSameDepthState( mDepthState, info.mDepthState ) == _false )
		return _false;

	if ( gDynamicRHI->IsSameStencilState( mStencilState, info.mStencilState ) == _false )
		return _false;

	if ( gDynamicRHI->IsSameRasterizerState( mRasterizerState, info.mRasterizerState ) == _false )
		return _false;

	if ( mSamplerStates.Number( ) != info.mSamplerStates.Number( ) )
		return _false;

	for ( SamplerStateRHIRefMap::Iterator it = mSamplerStates.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		const SamplerStateRHIRef* sample_state = info.mSamplerStates.Search( it.GetKey( ) );
		if ( sample_state == _null )
			return _false;

		if ( gDynamicRHI->IsSameSamplerState( it.GetObject( ), *sample_state ) == _false )
			return _false;
	}

	return _true;
}

//----------------------------------------------------------------------------
// GraphicGeometryInfo Implementation
//----------------------------------------------------------------------------

_void GraphicGeometryInfo::Init( _PRIMITIVE_TYPE type, _float weight, _dword vb_stride, _dword vb_number )
{
	mPrimitiveType	= type;

	mWeight			= weight;

	mVBStride		= vb_stride;
	mVBOffset		= -1;
	mVBSize			= vb_number * vb_stride;

	mIBOStartIndex	= 0;
	mIBONumber		= 0;

	mViewport		= _null;

	mUBOCRCValue	= 0;
	mUBONumber		= 0;
	mUBOs			= _null;
}

_void GraphicGeometryInfo::InitWithIB( _PRIMITIVE_TYPE type, _float weight, _dword vb_stride, _dword vb_number, _dword ib_number )
{
	mPrimitiveType	= type;

	mWeight			= weight;

	mVBStride		= vb_stride;
	mVBOffset		= 0;
	mVBSize			= vb_number * vb_stride;

	mIBOStartIndex	= 0;
	mIBONumber		= ib_number;

	mViewport		= _null;

	mUBOCRCValue	= 0;
	mUBONumber		= 0;
	mUBOs			= _null;
}

_void GraphicGeometryInfo::AppendTexture( const AStringObj& name, Texture2DRHI* texture )
{
	mTextures[ name ] = texture;
}

_ubool GraphicGeometryInfo::CanCombine( const GraphicGeometryInfo& geometry ) const
{
	return CanCombine( geometry, geometry.mVAOResource, geometry.mUBOCRCValue, geometry.mIBOStartIndex );
}

_ubool GraphicGeometryInfo::CanCombine( const GraphicGeometryInfo& geometry, const VertexArrayRHI* vao, _crcvalue ubo_crc_value, _dword ibo_start_index ) const
{
	// The primitive type must be same
	if ( mPrimitiveType != geometry.mPrimitiveType )
		return _false;

	// Check primitive type
	switch ( mPrimitiveType )
	{
		case _PT_POINT_LIST:
		case _PT_LINE_LIST:
			if ( Math::Equal( mWeight, geometry.mWeight ) == _false )
				return _false;
			break;

		case _PT_TRIANGLE_LIST:
			break; // Continue to try to combine it

		// We can't combine the other primitive types
		default:
			return _false;
			break;
	}

	// The viewport is different with last geometry
	if ( mViewport != geometry.mViewport )
		return _false;

	// Check texture cube
	if ( mTextureCube != geometry.mTextureCube )
		return _false;

	// Check for each textures
	if ( mTextures.Number( ) != geometry.mTextures.Number( ) )
		return _false;

	for ( Texture2DRHIRefMap::Iterator it = mTextures.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		const Texture2DRHIRef* texture = geometry.mTextures.Search( it.GetKey( ) );
		if ( texture == _null )
			return _false;

		if ( it.GetObject( ) != *texture )
			return _false;
	}

	// Check VAO
	if ( mVAOResource != vao )
		return _false;

	// If any uniform buffers change then can not combine
	if ( mUBOCRCValue != ubo_crc_value )
		return _false;

	// IBO can not combine with none-IBO geometry
	if ( mIBONumber == 0 )
	{
		if ( geometry.mIBONumber != 0 ) 
			return _false;
	}
	// IBO combine checking
	else
	{
		if ( geometry.mIBONumber == 0 ) 
			return _false;

		if ( mIBOStartIndex + mIBONumber != ibo_start_index )
			return _false;
	}

	// Check whether it's same render states
	if ( mRenderStates.IsEqual( geometry.mRenderStates ) == _false )
		return _false;

	return _true;
}

_dword GraphicGeometryInfo::GetIBSize( ) const
{
	return mIBONumber * sizeof( _word );
}

GraphicGeometryInfo::GraphicGeometryInfo( )
{
	Init( _PT_NONE, 0.0f, 0, 0 );
}

//----------------------------------------------------------------------------
// GraphicMeshGeometryInfo Implementation
//----------------------------------------------------------------------------

GraphicMeshGeometryInfo::GraphicMeshGeometryInfo( )
{
	mRenderDistanceOffset	= 0.0f;

	mColor					= Color::cWhite;
	mModelTransform			= Matrix4::cIdentity;
	mAABox					= AxisAlignedBox::cNullBox;

	mMirrorType				= _GRAPHIC_MIRROR_NONE;
	mMirrorSize				= 0;
	mMirrorReflectType		= 0;
	mMirrorReflectionPlane	= Plane::cXYPlane;
}