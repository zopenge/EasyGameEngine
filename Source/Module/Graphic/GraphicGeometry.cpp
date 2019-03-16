//! @file     GraphicGeometry.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicGeometry Implementation
//----------------------------------------------------------------------------

GraphicGeometry::GraphicGeometry( )
{
}

GraphicGeometry::~GraphicGeometry( )
{
}

_void GraphicGeometry::Init( IGraphicEffect* effect, const GraphicMeshGeometryInfo& geometry_info )
{
	mEffect			= effect;
	mGeometryInfo	= geometry_info;
}

_void GraphicGeometry::Init( IGraphicVertexArray* vao, IGraphicEffect* effect, const GraphicGeometryInfo& geometry_info, _dword ibo_start_index )
{
	EGE_ASSERT( vao != _null );
	EGE_ASSERT( effect != _null );

	// Set the effect
	mEffect	= effect;

	// Build the last geometry
	mGeometryInfo.mPrimitiveType	= geometry_info.mPrimitiveType;
	mGeometryInfo.mUBOCRCValue		= 0;
	mGeometryInfo.mUBONumber		= 0;
	mGeometryInfo.mUBOs				= _null;
	mGeometryInfo.mWeight			= geometry_info.mWeight;
	mGeometryInfo.mVBStride			= geometry_info.mVBStride;
	mGeometryInfo.mVBOffset			= vao->GetVBOffset( );
	mGeometryInfo.mVBSize			= geometry_info.mVBSize;
	mGeometryInfo.mIBOStartIndex	= ibo_start_index;
	mGeometryInfo.mIBONumber		= geometry_info.mIBONumber;
	mGeometryInfo.mVAOResource		= vao->GetResource( );
	mGeometryInfo.mViewport			= geometry_info.mViewport;
	mGeometryInfo.mRenderStates		= geometry_info.mRenderStates;
	mGeometryInfo.mTextures			= geometry_info.mTextures;
	mGeometryInfo.mTextureCube		= geometry_info.mTextureCube;
}

_void GraphicGeometry::AppendTexture( const AStringObj& name, IGraphicTexture2D* texture )
{
	AppendTexture( name, texture->GetResource( ) );
}

_void GraphicGeometry::AppendTexture( const AStringObj& name, Texture2DRHI* texture )
{
	mGeometryInfo.AppendTexture( name, texture );
}

_ubool GraphicGeometry::CanCombine( const GraphicGeometry& geometry ) const
{
	const GraphicGeometryInfo& geometry_info = geometry.mGeometryInfo;

	return CanCombine( geometry_info, geometry.mEffect, geometry_info.mVAOResource, geometry_info.mIBOStartIndex );
}

_ubool GraphicGeometry::CanCombine( const GraphicGeometryInfo& geometry_info, IGraphicEffect* effect, const VertexArrayRHI* vao, _dword ibo_start_index ) const
{
	// Check whether it's same effect
	if ( mEffect->GetBoundShader( ) != effect->GetBoundShader( ) )
		return _false;

	// Check geometry
	if ( mGeometryInfo.CanCombine( geometry_info, vao, effect->GetUBOCRCValue( ), ibo_start_index ) == _false )
		return _false;

	return _true;
}

_void GraphicGeometry::CombineGeometry( const GraphicGeometryInfo& geometry_info )
{
	// Enlarge VBO
	mGeometryInfo.mVBSize += geometry_info.mVBSize;

	// Enlarge IBO
	mGeometryInfo.mIBONumber += geometry_info.mIBONumber;
}

_float GraphicGeometry::GetDistanceFromCamera( const IGraphicSceneView* scene_view ) const
{
	EGE_ASSERT( scene_view != _null );

	return scene_view->GetDistanceFromCamera( mGeometryInfo.mAABox.CenterVector( ) );
}

_void GraphicGeometry::UpdateMeshUBOs( IGraphicScene* scene )
{
	// Update model color
	mEffect->SetUBO( ASTROBJ( uModelColor ), mGeometryInfo.mColor );

	// Get and update the model transform
	const Matrix4& model_transform = mGeometryInfo.mModelTransform;
	mEffect->SetUBO( ASTROBJ( uModelTransform ), model_transform, _true );

	// Update the view transform
	const Matrix4& view_transform = scene->GetViewTransform( );
	mEffect->SetUBO( ASTROBJ( uViewTransform ), view_transform, _true );

	// Update the projection transform
	const Matrix4& projection_transform = scene->GetVPTransform( );
	mEffect->SetUBO( ASTROBJ( uProjectionTransform ), projection_transform, _true );

	// Update MVP transform
	if ( mEffect->HasUBO( ASTROBJ( uMVPTransform ) ) )
		mEffect->SetUBO( ASTROBJ( uMVPTransform ), model_transform * view_transform * projection_transform, _true );
}

_void GraphicGeometry::UpdateSceneUBOs( IGraphicScene* scene )
{
	EGE_ASSERT( scene != _null );

	// Get the camera
	const Camera& camera = scene->GetSceneView( )->GetCamera( );

	// Update camera info
	mEffect->SetUBO( ASTROBJ( uEyePos ), camera.mPosition );
	mEffect->SetUBO( ASTROBJ( uEyeLookAt ), camera.mLook );
}

_void GraphicGeometry::SaveUBOs( IBufferAllocator* allocator )
{
	EGE_ASSERT( allocator != _null );

	// Syn textures
	mEffect->SynTextures( mGeometryInfo.mTextures );

	// Save UBO CRC value
	mGeometryInfo.mUBOCRCValue = mEffect->GetUBOCRCValue( );

	// Get the active UBOs
	_dword total_size = 0;
	const _byte* from_buffers = mEffect->GetUBOs( mGeometryInfo.mUBONumber, total_size );

	// Check whether need to save UBO buffers
	if ( mGeometryInfo.mUBONumber != 0 )
	{
		EGE_ASSERT( from_buffers != _null );

		// Allocate the modified uniform buffers info
		_byte* to_buffers = allocator->Alloc( total_size );
		EGE_ASSERT( to_buffers != _null );

		// Copy the buffers
		EGE_MEM_CPY( to_buffers, from_buffers, total_size );

		// Save the UBO address
		mGeometryInfo.mUBOs = (GraphicUniformBuffer*) to_buffers;

		// Fix the UBO buffer address
		_byte* start_address = to_buffers + mGeometryInfo.mUBONumber * sizeof( GraphicUniformBuffer );
		for ( _dword i = 0; i < mGeometryInfo.mUBONumber; i ++ )
		{
			mGeometryInfo.mUBOs[i].mBuffer = start_address;

			start_address += mGeometryInfo.mUBOs[i].mSize;
		}
	}
	else
	{
		mGeometryInfo.mUBOs = _null;
	}
}
