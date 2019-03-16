//! @file     GraphicGeometryBuilder.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

static const _word s1TrianglsIndexBuffer[] = { 0, 2, 1 };
static const _word s2TrianglsIndexBuffer[] = { 0, 3, 1, 1, 3, 2 };
static const _word s4TrianglsIndexBuffer[] = { 0, 2, 1, 0, 4, 2, 2, 3, 1, 2, 4, 3 };

//----------------------------------------------------------------------------
// GraphicGeometryBuilder Implementation
//----------------------------------------------------------------------------

GraphicGeometryBuilder::GraphicGeometryBuilder( IGraphicScene* scene )
	: mViewports( Viewport::cNull )
{
	mLastClientSize = PointU::cZeroPoint;

	mSABUpAxis		= Vector3::cOrigin;
	mSABRightAxis	= Vector3::cOrigin;
	mSABMatrix		= Matrix3::cIdentity;

	mVOBUpAxis		= Vector3::cOrigin;
	mVOBLookAxis	= Vector3::cOrigin;
	mVOBMatrix		= Matrix3::cIdentity;

	mABLookAxis		= Vector3::cOrigin;
	mABUpAxis		= Vector3::cOrigin;
	mABMatrix		= Matrix3::cIdentity;

	mScene			= scene;

	// Update transforms
	EGE_INIT_ARRAY( mLastRHTransformSlots );
	UpdateTransform( _null, _null, _null, _false );
}

GraphicGeometryBuilder::~GraphicGeometryBuilder( )
{
}

_void GraphicGeometryBuilder::AllocVB( GeometryBuildInfo& info, _dword vb_number )
{
	GraphicVertexInfo* vb = (GraphicVertexInfo*) mBufferAllocator->Alloc( vb_number * sizeof( GraphicVertexInfo ) );
	EGE_ASSERT( vb != _null );

	info.mVertexBuffer.CreateInShareMode( vb_number, vb );
}

_void GraphicGeometryBuilder::BuildOverlayVertex( Vector2& lt, Vector2& rt, Vector2& rb, Vector2& lb, const Vector2& position, const Vector2& size, const Vector2* vertex_offsets, const Matrix3& transform )
{
	// Set the basic vertex buffer info
	lt.x = position.x;
	lt.y = position.y;
	rt.x = lt.x + size.x;
	rt.y = lt.y;
	rb.x = rt.x;
	rb.y = lt.y + size.y;
	lb.x = lt.x;
	lb.y = rb.y;

	// Affect by vertex offset
	if ( vertex_offsets != _null )
	{
		lt += vertex_offsets[0];
		rt += vertex_offsets[1];
		rb += vertex_offsets[2];
		lb += vertex_offsets[3];
	}

	// Affect by transform
	lt *= transform;
	rt *= transform;
	rb *= transform;
	lb *= transform;
}

_void GraphicGeometryBuilder::SetOverlay( GraphicVertexInfo* vertex_buffer, const Vector2& position, const Vector2& size, const Vector2* vertex_offsets, const Matrix3& transform, const GraphicUVInfo& uv_info, const Color& color )
{
	// Get position
	Vector2 lt, rt, rb, lb;
	BuildOverlayVertex( lt, rt, rb, lb, position, size, vertex_offsets, transform );

	// Build vertex buffer
	vertex_buffer[0].Init( lt, color, uv_info.mLT.x, uv_info.mLT.y );
	vertex_buffer[1].Init( rt, color, uv_info.mRT.x, uv_info.mRT.y );
	vertex_buffer[2].Init( rb, color, uv_info.mRB.x, uv_info.mRB.y );
	vertex_buffer[3].Init( lb, color, uv_info.mLB.x, uv_info.mLB.y );
}

_void GraphicGeometryBuilder::SetOverlay( GraphicVertexInfo* vertex_buffer, IGraphicTexture2D* sprite, const Vector2& position, const Vector2& size, const Vector2* vertex_offsets, const Matrix3& transform, const GraphicUVInfo& uv_info, const Color& color )
{
	// Build vertex buffer
	Vector2 lt, rt, rb, lb;
	BuildOverlayVertex( lt, rt, rb, lb, position, size, vertex_offsets, transform );

	// Fix UV by sprite
	Vector2 lt_uv = sprite->FixUV( uv_info.mLT );
	Vector2 lb_uv = sprite->FixUV( uv_info.mLB );
	Vector2 rt_uv = sprite->FixUV( uv_info.mRT );
	Vector2 rb_uv = sprite->FixUV( uv_info.mRB );

	// Build vertex buffer
	vertex_buffer[0].Init( lt, color, Color::cWhite, lt_uv.x, lt_uv.y );
	vertex_buffer[1].Init( rt, color, Color::cWhite, rt_uv.x, rt_uv.y );
	vertex_buffer[2].Init( rb, color, Color::cWhite, rb_uv.x, rb_uv.y );
	vertex_buffer[3].Init( lb, color, Color::cWhite, lb_uv.x, lb_uv.y );
}

_void GraphicGeometryBuilder::SetOverlay( GraphicVertexInfo* vertex_buffer, IGraphicTexture2D* sprite, const Triangle2D& vertex_triangle, const Triangle2D& uv_triangle, const Color& color )
{
	// Fix the UV coordinates
	Vector2 fixed_uv1 = sprite->FixUV( uv_triangle.mVector1 );
	Vector2 fixed_uv2 = sprite->FixUV( uv_triangle.mVector2 );
	Vector2 fixed_uv3 = sprite->FixUV( uv_triangle.mVector3 );

	// Build vertex buffer
	vertex_buffer[0].Init( vertex_triangle.mVector1, color, Color::cWhite, fixed_uv1 );
	vertex_buffer[1].Init( vertex_triangle.mVector2, color, Color::cWhite, fixed_uv2 );
	vertex_buffer[2].Init( vertex_triangle.mVector3, color, Color::cWhite, fixed_uv3 );
}

_void GraphicGeometryBuilder::SetPrimitive( GraphicVertexInfo* vertex_buffer, Vector3& lt, Vector3& rt, Vector3& lb, Vector3& rb, const Vector2* vertex_offsets, const Matrix3& sprite_transform, const Matrix3& viewmatrix, const Vector3& position, const Vector3* scaling, const GraphicUVInfo& uv_info, const Color& color )
{
	if ( vertex_offsets != _null )
	{
		lt.x += vertex_offsets[0].x;
		lt.y += vertex_offsets[0].y;
		rt.x += vertex_offsets[1].x;
		rt.y += vertex_offsets[1].y;
		rb.x += vertex_offsets[2].x;
		rb.y += vertex_offsets[2].y;
		lb.x += vertex_offsets[3].x;
		lb.y += vertex_offsets[3].y;
	}

	Matrix3 matrix = sprite_transform * viewmatrix;

	lt *= matrix;
	rt *= matrix;
	lb *= matrix;
	rb *= matrix;

	if ( scaling != _null )
	{
		lt *= *scaling;
		rt *= *scaling;
		lb *= *scaling;
		rb *= *scaling;
	}

	lt += position;
	rt += position;
	lb += position;
	rb += position;

	// Build vertex buffer
	vertex_buffer[0].Init( lt, color, uv_info.mLT.x, uv_info.mLT.y );
	vertex_buffer[1].Init( rt, color, uv_info.mRT.x, uv_info.mRT.y );
	vertex_buffer[2].Init( rb, color, uv_info.mRB.x, uv_info.mRB.y );
	vertex_buffer[3].Init( lb, color, uv_info.mLB.x, uv_info.mLB.y );
}

_void GraphicGeometryBuilder::SetRectangle( GraphicVertexInfo* vertex_buffer, const Vector2& position, const Vector2& lt, const Vector2& rt, const Vector2& lb, const Vector2& rb, const Color& color, const GraphicUVInfo& uv_info, const Matrix3& transform )
{
	Vector2 fixed_lt = ( lt + position ) * transform;
	Vector2 fixed_rt = ( rt + position ) * transform;
	Vector2 fixed_rb = ( rb + position ) * transform;
	Vector2 fixed_lb = ( lb + position ) * transform;

	vertex_buffer[0].Init( fixed_lt, color, Color::cWhite, uv_info.mLT.x, uv_info.mLT.y );
	vertex_buffer[1].Init( fixed_rb, color, Color::cWhite, uv_info.mRB.x, uv_info.mRB.y );
	vertex_buffer[2].Init( fixed_rt, color, Color::cWhite, uv_info.mRT.x, uv_info.mRT.y );

	vertex_buffer[3].Init( fixed_lt, color, Color::cWhite, uv_info.mLT.x, uv_info.mLT.y );
	vertex_buffer[4].Init( fixed_lb, color, Color::cWhite, uv_info.mLB.x, uv_info.mLB.y );
	vertex_buffer[5].Init( fixed_rb, color, Color::cWhite, uv_info.mRB.x, uv_info.mRB.y );
}

//int getVerticesCount( int width, int height )
//{
//	return width * height * 3;
//}
//
//int getIndicesCount( int width, int height )
//{
//	return (width*height) + (width - 1)*(height - 2);
//}
//
//float* getVertices( int width, int height ) {
//	if ( vertices ) return vertices;
//
//	vertices = new float[getVerticesCount( width, height )];
//	int i = 0;
//
//	for ( int row = 0; row < height; row++ ) {
//		for ( int col = 0; col < width; col++ ) {
//			vertices[i++] = (float)col;
//			vertices[i++] = 0.0f;
//			vertices[i++] = (float)row;
//		}
//	}
//
//	return vertices;
//}
//
//int* getIndices( int width, int height ) {
//	if ( indices ) return indices;
//
//	indices = new int[getIndices(width, height)];
//	int i = 0;
//
//	for ( int row = 0; row < height - 1; row++ ) {
//		if ( (row & 1) == 0 ) { // even rows
//			for ( int col = 0; col < width; col++ ) {
//				indices[i++] = col + row * width;
//				indices[i++] = col + (row + 1) * width;
//			}
//		}
//		else { // odd rows
//			for ( int col = width - 1; col > 0; col-- ) {
//				indices[i++] = col + (row + 1) * width;
//				indices[i++] = col - 1 + + row * width;
//			}
//		}
//	}
//	if ( (mHeight & 1) && mHeight > 2 ) {
//		indices[i++] = (mHeight - 1) * mWidth;
//	}
//
//	return indices;
//}

_ubool GraphicGeometryBuilder::Initialize( )
{
	mBufferAllocator = GetInterfaceFactory( )->CreateBufferAllocator( 16 KB );
	if ( mBufferAllocator.IsNull( ) )
		return _false;

	mVertexColorEffect = GetGraphicResourceManager( )->CreateEffectFromResName( WSTROBJ( eVertexColor ) );
	if ( mVertexColorEffect.IsNull( ) )
		return _false;

	return _true;
}

_void GraphicGeometryBuilder::ClearCaches( )
{
	mLastClientSize	= PointU::cZeroPoint;

	// Reset caches last index
	mViewports.Reset( );

	// Reset buffer allocator
	mBufferAllocator->Reset( );

	// Update transforms
	UpdateTransform( _null, _null, _null, _false );
}

const Viewport* GraphicGeometryBuilder::GetLastViewport( ) const
{
	return mViewports.GetLastValue( );
}

const Matrix4& GraphicGeometryBuilder::GetLastTransformRH( _TRANSFORM_SLOT slot ) const
{
	return mLastRHTransformSlots[ slot ];
}

_void GraphicGeometryBuilder::UpdateViewport( const Viewport& viewport )
{
	mViewports.Append( viewport );
}

_void GraphicGeometryBuilder::UpdateTransform( const Matrix4* overlay, const Matrix4* ortho_user, const Matrix4* offset, _ubool force_update )
{
	// Get the scene view
	const IGraphicSceneView* scene_view = mScene->GetSceneView( );
	EGE_ASSERT( scene_view != _null );

	// Get the client size
	const PointU& client_size = mScene->GetClientSize( );

	// Get the update parameters
	const PointU* client_size_ptr = mLastClientSize == client_size ? _null : &client_size;

	// Update transform
	_ubool update_transform	= client_size_ptr || overlay || ortho_user || offset || force_update;
	if ( update_transform )
	{
		// Get ortho transform
		Matrix4& ortho = mLastRHTransformSlots[ _TRANSFORM_ORTHO ];
		if ( client_size_ptr != _null )
			ortho = Matrix4::CreateOrthoOffCenterRH( 0.0f, (_float) client_size.x, (_float) client_size.y, 0.0f, 0.0f, 1.0f );

		// Check whether use the observer scene view to render
		IGraphicSceneView* ob_scene_view = scene_view->GetObserverSceneView( );
		if ( ob_scene_view != _null )
			scene_view = ob_scene_view;

		// Update transforms
		if ( offset != _null )
		{
			if ( overlay != _null )
			{
				if ( ortho_user != _null )
					mLastRHTransformSlots[ _TRANSFORM_OVERLAY ] = (*overlay) * (*ortho_user) * (*offset);
				else
					mLastRHTransformSlots[ _TRANSFORM_OVERLAY ] = (*overlay) * ortho * (*offset);
			}
			else
			{
				if ( ortho_user != _null )
					mLastRHTransformSlots[ _TRANSFORM_OVERLAY ]	= (*ortho_user) * (*offset);
				else
					mLastRHTransformSlots[ _TRANSFORM_OVERLAY ]	= ortho * (*offset);
			}

			mLastRHTransformSlots[ _TRANSFORM_VIEW ]	= scene_view->GetViewTransform( ) * (*offset);
			mLastRHTransformSlots[ _TRANSFORM_VP ]		= scene_view->GetViewProjectionTransform( ) * (*offset);
		}
		else
		{
			if ( overlay != _null )
			{
				if ( ortho_user != _null )
					mLastRHTransformSlots[ _TRANSFORM_OVERLAY ] = (*overlay) * (*ortho_user);
				else
					mLastRHTransformSlots[ _TRANSFORM_OVERLAY ] = (*overlay) * ortho;
			}
			else
			{
				if ( ortho_user != _null )
					mLastRHTransformSlots[ _TRANSFORM_OVERLAY ]	= (*ortho_user);
				else
					mLastRHTransformSlots[ _TRANSFORM_OVERLAY ]	= ortho;
			}

			mLastRHTransformSlots[ _TRANSFORM_VIEW ]	= scene_view->GetViewTransform( );
			mLastRHTransformSlots[ _TRANSFORM_VP ]		= scene_view->GetViewProjectionTransform( );
		}
	}

	// Update the last client size
	mLastClientSize = client_size;
}

_void GraphicGeometryBuilder::BuildGeometry( _TRANSFORM_SLOT slot, GeometryBuildInfo& info )
{
	// Get the effect
	IGraphicEffect* effect = info.mEffect;
	EGE_ASSERT( effect != _null );

	// Syn geometry info
	GraphicGeometryInfo& geometry_info	= info.mGeometryInfo;
	geometry_info.mRenderStates			= effect->GetRenderStates( );
	geometry_info.mViewport				= GetLastViewport( );

	// Syn last transform of slot
	effect->SetUBO( ASTROBJ( uMVPTransform ), GetLastTransformRH( slot ), _true );
}

_void GraphicGeometryBuilder::BuildLineGeometry( const Vector2& start, const Vector2& end, const Color& color, _float width, GeometryBuildInfo& info )
{
	// Get the size of VB
	const _dword vb_number = 2;

	// Initialize vertex buffer
	AllocVB( info, vb_number );
	info.mVertexBuffer[0].Init( start, color );
	info.mVertexBuffer[1].Init( end, color );

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_LINE_LIST, width, sizeof( GraphicVertexInfo ), vb_number );
	info.mEffect = mVertexColorEffect;

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_OVERLAY, info );
}

_void GraphicGeometryBuilder::BuildLineGeometry( const Vector2& start, const Vector2& end, const Color& color_start, const Color& color_end, _float width, GeometryBuildInfo& info )
{
	// Get the size of VB
	const _dword vb_number = 2;

	// Initialize vertex buffer
	AllocVB( info, vb_number );
	info.mVertexBuffer[0].Init( start, color_start );
	info.mVertexBuffer[1].Init( end, color_end );

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_LINE_LIST, width, sizeof( GraphicVertexInfo ), vb_number );
	info.mEffect = mVertexColorEffect;

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_OVERLAY, info );
}

_void GraphicGeometryBuilder::BuildLineGeometry( const Vector3& start, const Vector3& end, const Color& color, _float width, GeometryBuildInfo& info )
{
	// Get the size of VB
	const _dword vb_number = 2;

	// Initialize vertex buffer
	AllocVB( info, vb_number );
	info.mVertexBuffer[0].Init( start, color );
	info.mVertexBuffer[1].Init( end, color );

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_LINE_LIST, width, sizeof( GraphicVertexInfo ), vb_number );
	info.mEffect = mVertexColorEffect;

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_VP, info );
}

_void GraphicGeometryBuilder::BuildLineGeometry( const Vector3& start, const Vector3& end, const Color& color_start, const Color& color_end, _float width, GeometryBuildInfo& info )
{
	// Get the size of VB
	const _dword vb_number = 2;

	// Initialize vertex buffer
	AllocVB( info, vb_number );
	info.mVertexBuffer[0].Init( start, color_start );
	info.mVertexBuffer[1].Init( end, color_end );

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_LINE_LIST, width, sizeof( GraphicVertexInfo ), vb_number );
	info.mEffect = mVertexColorEffect;

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_VP, info );
}

_void GraphicGeometryBuilder::BuildLinesGeometry( const Line2DArray& lines, const Color& color, _float width, GeometryBuildInfo& info )
{
	// Get the size of VB
	const _dword vb_number = lines.Number( ) * 2;

	// Initialize vertex buffer
	AllocVB( info, vb_number );
	for ( _dword i = 0; i < lines.Number( ); i ++ )
	{
		const Line2D& line = lines[i];

		info.mVertexBuffer[i * 2].Init( line.mPoints[0], color );
		info.mVertexBuffer[i * 2 + 1].Init( line.mPoints[1], color );
	}

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_LINE_LIST, width, sizeof( GraphicVertexInfo ), vb_number );
	info.mEffect = mVertexColorEffect;

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_OVERLAY, info );
}

_void GraphicGeometryBuilder::BuildLinesGeometry( const Line3DArray& lines, const Color& color, _float width, GeometryBuildInfo& info )
{
	// Get the size of VB
	const _dword vb_number = lines.Number( ) * 2;

	// Initialize vertex buffer
	AllocVB( info, vb_number );
	for ( _dword i = 0; i < lines.Number( ); i ++ )
	{
		const Line3D& line = lines[i];

		info.mVertexBuffer[i * 2].Init( line.mPoints[0], color );
		info.mVertexBuffer[i * 2 + 1].Init( line.mPoints[1], color );
	}

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_LINE_LIST, width, sizeof( GraphicVertexInfo ), vb_number );
	info.mEffect = mVertexColorEffect;

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_VP, info );
}

_void GraphicGeometryBuilder::BuildRectGeometry( const RectF& rect, const Color& color, GeometryBuildInfo& info )
{
	// Build vertex position
	Vector2 lt, rt, rb, lb;
	ConvertRectToVertex( lt, rt, rb, lb, rect );

	// Get the size of VB
	const _dword vb_number = 4;

	// Initialize vertex buffer
	AllocVB( info, vb_number );
	info.mVertexBuffer[0].Init( lt, color );
	info.mVertexBuffer[1].Init( rt, color );
	info.mVertexBuffer[2].Init( rb, color );
	info.mVertexBuffer[3].Init( lb, color );

	// Initialize index buffer
	info.mIndexBuffer.CreateInShareMode( EGE_ARRAY_NUMBER( s2TrianglsIndexBuffer ), s2TrianglsIndexBuffer );

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_TRIANGLE_LIST, 1.0f, sizeof( GraphicVertexInfo ), vb_number );
	info.mGeometryInfo.mIBONumber	= EGE_ARRAY_NUMBER( s2TrianglsIndexBuffer );
	info.mEffect					= mVertexColorEffect;

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_OVERLAY, info );
}

_void GraphicGeometryBuilder::BuildRectGeometry( const RectF& rect, const Matrix3& transform, const Color& color, GeometryBuildInfo& info )
{
	// Build vertex position
	Vector2 lt, rt, rb, lb;
	ConvertRectToVertex( lt, rt, rb, lb, rect );

	// Update vertex position with transform
	lt *= transform;
	rt *= transform;
	rb *= transform;
	lb *= transform;

	// Get the size of VB
	const _dword vb_number = 4;

	// Initialize vertex buffer
	AllocVB( info, vb_number );
	info.mVertexBuffer[0].Init( lt, color );
	info.mVertexBuffer[1].Init( rt, color );
	info.mVertexBuffer[2].Init( rb, color );
	info.mVertexBuffer[3].Init( lb, color );

	// Initialize index buffer
	info.mIndexBuffer.CreateInShareMode( EGE_ARRAY_NUMBER( s2TrianglsIndexBuffer ), s2TrianglsIndexBuffer );

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_TRIANGLE_LIST, 1.0f, sizeof( GraphicVertexInfo ), vb_number );
	info.mGeometryInfo.mIBONumber	= EGE_ARRAY_NUMBER( s2TrianglsIndexBuffer );
	info.mEffect					= mVertexColorEffect;

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_OVERLAY, info );
}

_void GraphicGeometryBuilder::BuildRectLineGeometry( const RectF& rect, const Color& color, _float width, GeometryBuildInfo& info )
{
	// Build vertex position
	Vector2 lt, rt, rb, lb;
	ConvertRectToVertex( lt, rt, rb, lb, rect );

	// Get the size of VB
	const _dword vb_number = 4;

	// Initialize vertex buffer
	AllocVB( info, vb_number );
	info.mVertexBuffer[0].Init( lt, color );
	info.mVertexBuffer[1].Init( rt, color );
	info.mVertexBuffer[2].Init( rb, color );
	info.mVertexBuffer[3].Init( lb, color );

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_LINE_LOOP, width, sizeof( GraphicVertexInfo ), vb_number );
	info.mEffect = mVertexColorEffect;

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_OVERLAY, info );
}

_void GraphicGeometryBuilder::BuildTrianglesGeometry( const TriangleArray& triangles, const Color& color, GeometryBuildInfo& info )
{
	// Get the size of VB
	const _dword vb_number = triangles.Number( ) * 3;

	// Initialize vertex buffer
	AllocVB( info, vb_number );
	for ( _dword i = 0; i < triangles.Number( ); ++ i )
	{
		info.mVertexBuffer[i * 3 + 0].Init( triangles[i].mVector1, color );
		info.mVertexBuffer[i * 3 + 1].Init( triangles[i].mVector2, color );
		info.mVertexBuffer[i * 3 + 2].Init( triangles[i].mVector3, color );
	}

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_TRIANGLE_LIST, 1.0f, sizeof( GraphicVertexInfo ), vb_number );
	info.mEffect = mVertexColorEffect;

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_VP, info );
}

_void GraphicGeometryBuilder::BuildTrianglesGeometry( const Triangle2DArray& triangles, const Color& color, GeometryBuildInfo& info )
{
	// Get the size of VB
	const _dword vb_number = triangles.Number( ) * 3;

	// Initialize vertex buffer
	AllocVB( info, vb_number );

	// Build vertex buffer
	GraphicVertexInfo* vertex_buffer = info.mVertexBuffer;
	for ( _dword i = 0; i < triangles.Number( ); i ++  )
	{
		vertex_buffer[i * 3 + 0].Init( triangles[i].mVector1, color );
		vertex_buffer[i * 3 + 1].Init( triangles[i].mVector2, color );
		vertex_buffer[i * 3 + 2].Init( triangles[i].mVector3, color );
	}

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_TRIANGLE_LIST, 1.0f, sizeof( GraphicVertexInfo ), vb_number );
	info.mEffect = mVertexColorEffect;

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_OVERLAY, info );
}

_void GraphicGeometryBuilder::BuildTrianglesLineGeometry( const Triangle2DArray& triangles, const Color& color, _float width, GeometryBuildInfo& info )
{
	// Get the size of VB
	const _dword vb_number = triangles.Number( ) * 6;

	// Initialize vertex buffer
	AllocVB( info, vb_number );

	// Build vertex buffer
	GraphicVertexInfo* vertex_buffer = info.mVertexBuffer;
	for ( _dword i = 0; i < triangles.Number( ); i ++ )
	{
		vertex_buffer[i * 6 + 0].Init( triangles[i].mVector1, color ); vertex_buffer[i * 6 + 1].Init( triangles[i].mVector2, color );
		vertex_buffer[i * 6 + 2].Init( triangles[i].mVector2, color ); vertex_buffer[i * 6 + 3].Init( triangles[i].mVector3, color );
		vertex_buffer[i * 6 + 4].Init( triangles[i].mVector3, color ); vertex_buffer[i * 6 + 5].Init( triangles[i].mVector1, color );
	}

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_LINE_LIST, width, sizeof( GraphicVertexInfo ), vb_number );
	info.mEffect = mVertexColorEffect;

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_OVERLAY, info );
}

_void GraphicGeometryBuilder::BuildCircleGeometry( const Vector2& center, _float radius, _dword segments, const Color& color, GeometryBuildInfo& info )
{
	const _float increment = 2.0f * Math::cPi / (_float) segments;

	// Get the size of VB
	const _dword vb_number = segments + 2;

	// Initialize vertex buffer
	AllocVB( info, vb_number );

	// Set center vertex
	info.mVertexBuffer[0].mPosition.x = center.x;
	info.mVertexBuffer[0].mPosition.y = center.y;
	info.mVertexBuffer[0].mPosition.z = 0.0f;
	info.mVertexBuffer[0].mColor = color;

	_float theta = 0.0f;
	for ( _dword i = 1; i <= segments + 1; i ++, theta += increment )
	{
		_float theta_sincos[2];
		Math::SinCos( theta, theta_sincos );

		Vector2 pos = center + Vector2( theta_sincos[1], theta_sincos[0] ) * radius;

		info.mVertexBuffer[i].mPosition.x = pos.x;
		info.mVertexBuffer[i].mPosition.y = pos.y;
		info.mVertexBuffer[i].mPosition.z = 0.0f;
		info.mVertexBuffer[i].mColor = color;
	}

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_TRIANGLE_FAN, 1.0f, sizeof( GraphicVertexInfo ), vb_number );
	info.mEffect = mVertexColorEffect;

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_OVERLAY, info );
}

_void GraphicGeometryBuilder::BuildCircleLineGeometry( const Vector2& center, _float radius, _dword segments, const Color& color, GeometryBuildInfo& info )
{
	const _float increment = 2.0f * Math::cPi / (_float) segments;

	_float theta = 0.0f;

	// Get the size of VB
	const _dword vb_number = segments;

	// Initialize vertex buffer
	AllocVB( info, vb_number );
	for ( _dword i = 0; i < (_dword) segments; i ++, theta += increment )
	{
		_float theta_sincos[2];
		Math::SinCos( theta, theta_sincos );

		Vector2 pos = center + Vector2( theta_sincos[1], theta_sincos[0] ) * radius;

		info.mVertexBuffer[i].mPosition.x = pos.x;
		info.mVertexBuffer[i].mPosition.y = pos.y;
		info.mVertexBuffer[i].mPosition.z = 0.0f;
		info.mVertexBuffer[i].mColor = color;
	}

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_LINE_LOOP, 1.0f, sizeof( GraphicVertexInfo ), vb_number );
	info.mEffect = mVertexColorEffect;

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_OVERLAY, info );
}

_void GraphicGeometryBuilder::BuildOrientedBoxGeometry( const OrientedBox2D& box, const Color& color, _float width, GeometryBuildInfo& info )
{
	// Get the size of VB
	const _dword vb_number = 4;

	// Initialize vertex buffer
	AllocVB( info, vb_number );
	info.mVertexBuffer[0].Init( box.mCorner[0], color );
	info.mVertexBuffer[1].Init( box.mCorner[1], color );
	info.mVertexBuffer[2].Init( box.mCorner[2], color );
	info.mVertexBuffer[3].Init( box.mCorner[3], color );

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_LINE_LOOP, width, sizeof( GraphicVertexInfo ), vb_number );
	info.mEffect = mVertexColorEffect;

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_OVERLAY, info );
}

_void GraphicGeometryBuilder::BuildBoxGeometry( const Box& box, const Color& color, GeometryBuildInfo& info )
{
	// Get the size of VB
	const _dword vb_number = 36;

	// Initialize vertex buffer
	AllocVB( info, vb_number );

	// Build vertex buffer
	GraphicVertexInfo* vertex_buffer = info.mVertexBuffer;
	vertex_buffer[0].Init( box.mVectors[0], color ); vertex_buffer[1].Init( box.mVectors[1], color ); vertex_buffer[2].Init( box.mVectors[4], color );
	vertex_buffer[3].Init( box.mVectors[1], color ); vertex_buffer[4].Init( box.mVectors[4], color ); vertex_buffer[5].Init( box.mVectors[5], color );
	vertex_buffer[6].Init( box.mVectors[1], color ); vertex_buffer[7].Init( box.mVectors[3], color ); vertex_buffer[8].Init( box.mVectors[5], color );
	vertex_buffer[9].Init( box.mVectors[3], color ); vertex_buffer[10].Init( box.mVectors[5], color ); vertex_buffer[11].Init( box.mVectors[7], color );
	vertex_buffer[12].Init( box.mVectors[2], color ); vertex_buffer[13].Init( box.mVectors[3], color ); vertex_buffer[14].Init( box.mVectors[6], color );
	vertex_buffer[15].Init( box.mVectors[3], color ); vertex_buffer[16].Init( box.mVectors[6], color ); vertex_buffer[17].Init( box.mVectors[7], color );
	vertex_buffer[18].Init( box.mVectors[0], color ); vertex_buffer[19].Init( box.mVectors[2], color ); vertex_buffer[20].Init( box.mVectors[4], color );
	vertex_buffer[21].Init( box.mVectors[2], color ); vertex_buffer[22].Init( box.mVectors[4], color ); vertex_buffer[23].Init( box.mVectors[6], color );
	vertex_buffer[24].Init( box.mVectors[0], color ); vertex_buffer[25].Init( box.mVectors[1], color ); vertex_buffer[26].Init( box.mVectors[2], color );
	vertex_buffer[27].Init( box.mVectors[1], color ); vertex_buffer[28].Init( box.mVectors[2], color ); vertex_buffer[29].Init( box.mVectors[3], color );
	vertex_buffer[30].Init( box.mVectors[4], color ); vertex_buffer[31].Init( box.mVectors[5], color ); vertex_buffer[32].Init( box.mVectors[6], color );
	vertex_buffer[33].Init( box.mVectors[5], color ); vertex_buffer[34].Init( box.mVectors[6], color ); vertex_buffer[35].Init( box.mVectors[7], color );

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_TRIANGLE_LIST, 1.0f, sizeof( GraphicVertexInfo ), vb_number );
	info.mEffect = mVertexColorEffect;

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_VP, info );
}

_void GraphicGeometryBuilder::BuildBoxLineGeometry( const Box& box, const Color& color, _float width, GeometryBuildInfo& info )
{
	// Get the size of VB
	const _dword vb_number = 24;

	// Initialize vertex buffer
	AllocVB( info, vb_number );

	// Build vertex buffer
	GraphicVertexInfo* vertex_buffer = info.mVertexBuffer;
	vertex_buffer[0].Init( box.mVectors[0], color ); vertex_buffer[1].Init( box.mVectors[1], color );
	vertex_buffer[2].Init( box.mVectors[1], color ); vertex_buffer[3].Init( box.mVectors[3], color );
	vertex_buffer[4].Init( box.mVectors[3], color ); vertex_buffer[5].Init( box.mVectors[2], color );
	vertex_buffer[6].Init( box.mVectors[2], color ); vertex_buffer[7].Init( box.mVectors[0], color );
	vertex_buffer[8].Init( box.mVectors[4], color ); vertex_buffer[9].Init( box.mVectors[5], color );
	vertex_buffer[10].Init( box.mVectors[5], color ); vertex_buffer[11].Init( box.mVectors[7], color );
	vertex_buffer[12].Init( box.mVectors[7], color ); vertex_buffer[13].Init( box.mVectors[6], color );
	vertex_buffer[14].Init( box.mVectors[6], color ); vertex_buffer[15].Init( box.mVectors[4], color );
	vertex_buffer[16].Init( box.mVectors[4], color ); vertex_buffer[17].Init( box.mVectors[0], color );
	vertex_buffer[18].Init( box.mVectors[5], color ); vertex_buffer[19].Init( box.mVectors[1], color );
	vertex_buffer[20].Init( box.mVectors[7], color ); vertex_buffer[21].Init( box.mVectors[3], color );
	vertex_buffer[22].Init( box.mVectors[6], color ); vertex_buffer[23].Init( box.mVectors[2], color );

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_LINE_LIST, width, sizeof( GraphicVertexInfo ), vb_number );
	info.mEffect = mVertexColorEffect;

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_VP, info );
}

_void GraphicGeometryBuilder::BuildXYAxisGeometry( const Vector2& origin, _float length, _float width, GeometryBuildInfo& info )
{
	// Get the size of VB
	const _dword vb_number = 4;

	// Initialize vertex buffer
	AllocVB( info, vb_number );
	info.mVertexBuffer[0].Init( origin, Color::cRed );  
	info.mVertexBuffer[1].Init( origin + Vector2( length, 0.0f ), Color::cRed );
	info.mVertexBuffer[2].Init( origin, Color::cBlue ); 
	info.mVertexBuffer[3].Init( origin + Vector2( 0.0f, length ), Color::cBlue );

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_LINE_LIST, width, sizeof( GraphicVertexInfo ), vb_number );
	info.mEffect = mVertexColorEffect;

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_OVERLAY, info );
}

_void GraphicGeometryBuilder::BuildXYZAxisGeometry( const Vector3& origin, _float length, _float width, GeometryBuildInfo& info )
{
	// Get the size of VB
	const _dword vb_number = 4;

	// Initialize vertex buffer
	AllocVB( info, vb_number );
	info.mVertexBuffer[0].Init( origin, Color::cRed );
	info.mVertexBuffer[1].Init( origin + Vector3( length, 0.0f, 0.0f ), Color::cRed );
	info.mVertexBuffer[2].Init( origin, Color::cBlue );
	info.mVertexBuffer[3].Init( origin + Vector3( 0.0f, length, 0.0f ), Color::cBlue );
	info.mVertexBuffer[4].Init( origin, Color::cGreen );
	info.mVertexBuffer[5].Init( origin + Vector3( 0.0f, 0.0f, length ), Color::cGreen );

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_LINE_LIST, width, sizeof( GraphicVertexInfo ), vb_number );
	info.mEffect = mVertexColorEffect;

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_VP, info );
}

_void GraphicGeometryBuilder::BuildSphereGeometry( const Vector3& origin, _float radius, _float latitude, _float longitude, GeometryBuildInfo& info )
{
	// Referenced to: http://ozark.hendrix.edu/~burch/cs/490/sched/feb8/ Thanks for open source
	_dword lats			= (_dword) latitude;
	_dword longs		= (_dword) longitude;

	// Get the size of VB
	const _dword vb_number	= lats * longs;

	// Initialize vertex buffer
	AllocVB( info, vb_number );

	// Build vertex buffer
	GraphicVertexInfo* vertex_buffer = info.mVertexBuffer;

	// Build vertices
	for ( _dword i = 0; i <= lats; i ++ )
	{
		_float lat0 = Math::cPi * (-0.5f + (_float) (i - 1) / lats);
		_float lat1 = Math::cPi * (-0.5f + (_float) i / lats);

		_float lat0_sincos[2]; _float lat1_sincos[2]; 
		Math::SinCos( lat0, lat0_sincos );
		Math::SinCos( lat1, lat1_sincos );

		for ( _dword j = 0; j <= longs; j ++ )
		{
			_float lng	= 2 * Math::cPi * (_float) (j - 1) / longs;
			_float yx[2];
			Math::SinCos( lng, yx );

			GraphicVertexInfo& v1 = (*vertex_buffer ++);
			v1.mColor		= Color::cWhite;
			v1.mPosition	= origin + Vector3( yx[1] * lat0_sincos[1], yx[0] * lat0_sincos[1], lat0_sincos[0] );

			GraphicVertexInfo v2 = (*vertex_buffer ++);
			v2.mColor		= Color::cWhite;
			v2.mPosition	= origin + Vector3( yx[1] * lat1_sincos[1], yx[0] * lat1_sincos[1], lat1_sincos[0] );
		}
	}

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_LINE_LOOP, 1.0f, sizeof( GraphicVertexInfo ), vb_number );
	info.mEffect = mVertexColorEffect;

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_VP, info );
}

_void GraphicGeometryBuilder::BuildFrustumGeometry( const Frustum& frustum, const Color& near_plane_color, const Color& far_plane_color, const Color& line_color, _float width, GeometryBuildInfo& info )
{
	// Get the size of VB
	const _dword vb_number = 24;

	// Initialize vertex buffer
	AllocVB( info, vb_number );

	// Build vertex buffer
	GraphicVertexInfo* vertex_buffer = info.mVertexBuffer;

	// Build vertex buffer
	for ( _dword k = 0; k < 4; k ++ )
	{
		vertex_buffer->mPosition	= frustum.mVectors[ k ];
		vertex_buffer->mColor		= near_plane_color;
		vertex_buffer ++;
		vertex_buffer->mPosition	= frustum.mVectors[ ( k + 1 ) % 4 ];
		vertex_buffer->mColor		= near_plane_color;
		vertex_buffer ++;
	}

	for ( _dword k = 0; k < 4; k ++ )
	{
		vertex_buffer->mPosition	= frustum.mVectors[ k + 4 ];
		vertex_buffer->mColor		= far_plane_color;
		vertex_buffer ++;
		vertex_buffer->mPosition	= frustum.mVectors[ ( k + 1 ) % 4 + 4 ];
		vertex_buffer->mColor		= far_plane_color;
		vertex_buffer ++;
	}

	for ( _dword k = 0; k < 4; k ++ )
	{
		vertex_buffer->mPosition	= frustum.mVectors[ k ];
		vertex_buffer->mColor		= line_color;
		vertex_buffer ++;
		vertex_buffer->mPosition	= frustum.mVectors[ k + 4 ];
		vertex_buffer->mColor		= line_color;
		vertex_buffer ++;
	}


	// Initialize geometry
	info.mGeometryInfo.Init( _PT_LINE_LIST, width, sizeof( GraphicVertexInfo ), vb_number );
	info.mEffect = mVertexColorEffect;

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_VP, info );
}

_void GraphicGeometryBuilder::BuildPolygonLineGeometry( const Polygon2D& polygon, const Color& color, _float width, GeometryBuildInfo& info )
{
	// Get the size of VB
	const _dword vb_number = polygon.mVertexArray.Number( );

	// Build vertex buffer
	AllocVB( info, vb_number );
	for ( _dword i = 0; i < polygon.mVertexArray.Number( ); i ++ )
		info.mVertexBuffer[i].Init( polygon.mVertexArray[i], color );

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_LINE_LOOP, width, sizeof( GraphicVertexInfo ), vb_number );
	info.mEffect = mVertexColorEffect;

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_OVERLAY, info );
}

_void GraphicGeometryBuilder::BuildSpriteGeometry( IGraphicTexture2D* sprite, const Vector2* vertex_offsets, const Vector2& offset, const Matrix3& transform, const Vector2& size, const GraphicUVInfo& uv_info, const Color& color, GeometryBuildInfo& info )
{
	// Get the size of VB
	const _dword vb_number = 4;

	// Build vertex buffer
	Vector2 position = (- size / 2.0f) + offset;

	AllocVB( info, vb_number );
	SetOverlay( info.mVertexBuffer, sprite, position, size, vertex_offsets, transform, uv_info, color );

	// Initialize index buffer
	info.mIndexBuffer.CreateInShareMode( EGE_ARRAY_NUMBER( s2TrianglsIndexBuffer ), s2TrianglsIndexBuffer );

	// Build geometry
	info.mGeometryInfo.InitWithIB( _PT_TRIANGLE_LIST, 1.0f, sizeof( GraphicVertexInfo ), vb_number, EGE_ARRAY_NUMBER( s2TrianglsIndexBuffer ) );
	info.mGeometryInfo.mTextures[ ASTROBJ( uDiffuseTex ) ] = sprite->GetResource( );

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_OVERLAY, info );
}

_void GraphicGeometryBuilder::BuildSpriteGeometryInMaskMode( IGraphicTexture2D* sprite, const Vector2& offset, const Matrix3& transform, const Vector2& size, const GraphicUVInfo& uv_info, const Color& color, IGraphicTexture2D* mask, const Matrix3& mask_transform, const Vector2& mask_offset, const Vector2& mask_size, const GraphicMaskUVInfo& mask_uv_info, GeometryBuildInfo& info )
{
	// Get the size of VB
	const _dword vb_number = 4;

	// Build vertex buffer
	Vector2 position = (- size / 2.0f) + offset;

	// Build mask position
	Vector2 mask_position = - mask_size / 2.0f;
	mask_position += mask_offset;

	// Build mask vertex buffer
	Vector2 mask_lt, mask_rt, mask_rb, mask_lb;
	BuildOverlayVertex( mask_lt, mask_rt, mask_rb, mask_lb, mask_position, mask_size, _null, mask_transform );

	// Build uniform buffers
	Vector2 mask_pos_x_dir	= mask_rt - mask_lt;
	Vector2 mask_pos_y_dir	= mask_lb - mask_lt;
	if ( mask_uv_info.mIsRotate )
		Math::Swap( mask_pos_x_dir, mask_pos_y_dir );
	Vector2 mask_uv_range	= mask_uv_info.GetRange( );
	Vector2 mask_uv_min		= mask_uv_info.mLT;
	_float	x_length		= mask_pos_x_dir.Magnitude( );
	_float	y_length		= mask_pos_y_dir.Magnitude( );
	mask_pos_x_dir.Normalize( );
	mask_pos_y_dir.Normalize( );

	AllocVB( info, vb_number );
	SetOverlay( info.mVertexBuffer, sprite, position, size, _null, transform, uv_info, color );

	// Initialize index buffer
	info.mIndexBuffer.CreateInShareMode( EGE_ARRAY_NUMBER( s2TrianglsIndexBuffer ), s2TrianglsIndexBuffer );

	// Build geometry
	info.mGeometryInfo.InitWithIB( _PT_TRIANGLE_LIST, 1.0f, sizeof( GraphicVertexInfo ), vb_number, EGE_ARRAY_NUMBER( s2TrianglsIndexBuffer ) );
	info.mGeometryInfo.mTextures[ ASTROBJ( uDiffuseTex ) ]		= sprite->GetResource( );
	info.mGeometryInfo.mTextures[ ASTROBJ( uSpriteMaskTex ) ]	= mask->GetResource( );

	// Update uniform buffers
	info.mEffect->SetUBO( ASTROBJ( uSpriteMaskPosMin ), mask_lt );
	info.mEffect->SetUBO( ASTROBJ( uSpriteMaskPosXDir ), Vector3( mask_pos_x_dir.x, mask_pos_x_dir.y, x_length ) );
	info.mEffect->SetUBO( ASTROBJ( uSpriteMaskPosYDir ), Vector3( mask_pos_y_dir.x, mask_pos_y_dir.y, y_length ) );
	info.mEffect->SetUBO( ASTROBJ( uSpriteMaskUVRange ), mask_uv_range );
	info.mEffect->SetUBO( ASTROBJ( uSpriteMaskUVMin ), mask_uv_min );

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_OVERLAY, info );
}

_void GraphicGeometryBuilder::BuildSpriteGeometryInTriangleMode( IGraphicTexture2D* sprite, const Triangle2D& vertex_triangle, const Triangle2D& uv_triangle, const Color& color, GeometryBuildInfo& info )
{
	// Get the size of VB
	const _dword vb_number = 3;

	// Build vertex buffer
	AllocVB( info, vb_number );
	SetOverlay( info.mVertexBuffer, sprite, vertex_triangle, uv_triangle, color );

	// Initialize index buffer
	info.mIndexBuffer.CreateInShareMode( EGE_ARRAY_NUMBER( s1TrianglsIndexBuffer ), s1TrianglsIndexBuffer );

	// Initialize geometry
	info.mGeometryInfo.InitWithIB( _PT_TRIANGLE_LIST, 1.0f, sizeof( GraphicVertexInfo ), vb_number, EGE_ARRAY_NUMBER( s1TrianglsIndexBuffer ) );
	info.mGeometryInfo.mTextures[ ASTROBJ( uDiffuseTex ) ]	= sprite->GetResource( );

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_OVERLAY, info );
}

_void GraphicGeometryBuilder::BuildSpriteGeometryInTriangleStripeMode( IGraphicTexture2D* sprite, const Vector3* pos_list, const Vector2* uv_list, const Color* color_list, _dword vertices_number, GeometryBuildInfo& info )
{
	// Get the size of VB
	const _dword vb_number = vertices_number;

	// Build vertex buffer
	AllocVB( info, vb_number );
	for ( _dword i = 0; i < vertices_number; i ++ )
	{
		GraphicVertexInfo& vertex = info.mVertexBuffer[i];

		vertex.mPosition = pos_list[i];
		vertex.mColor = color_list[i];
		vertex.mUV1 = uv_list[i];
	}

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_TRIANGLE_STRIP, 1.0f, sizeof( GraphicVertexInfo ), vb_number );
	info.mGeometryInfo.mTextures[ ASTROBJ( uDiffuseTex ) ]	= sprite->GetResource( );

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_VP, info );
}

_void GraphicGeometryBuilder::BuildSpriteGeometryInQuadMode( IGraphicTexture2D* sprite, const Vector3* pos_list, const Vector2* uv_list, const Color* color_list, _dword vertices_number, GeometryBuildInfo& info )
{
	// Get the size of VB
	const _dword vb_number = 6 + 3 * ( vertices_number - 4 );
	EGE_ASSERT( ( vb_number % 3 ) == 0 );

	// Build vertex buffer
	AllocVB( info, vb_number );

	// Get the vertex buffer
	GraphicVertexInfo* vertex_buffer = info.mVertexBuffer;

	// Build the first 6 vertices
	vertex_buffer[0].mPosition = pos_list[0]; vertex_buffer[0].mColor = color_list[0]; vertex_buffer[0].mUV1 = uv_list[0];
	vertex_buffer[1].mPosition = pos_list[1]; vertex_buffer[1].mColor = color_list[1]; vertex_buffer[1].mUV1 = uv_list[1];
	vertex_buffer[2].mPosition = pos_list[2]; vertex_buffer[2].mColor = color_list[2]; vertex_buffer[2].mUV1 = uv_list[2];
	vertex_buffer[3].mPosition = pos_list[0]; vertex_buffer[3].mColor = color_list[0]; vertex_buffer[3].mUV1 = uv_list[0];
	vertex_buffer[4].mPosition = pos_list[2]; vertex_buffer[4].mColor = color_list[2]; vertex_buffer[4].mUV1 = uv_list[2];
	vertex_buffer[5].mPosition = pos_list[3]; vertex_buffer[5].mColor = color_list[3]; vertex_buffer[5].mUV1 = uv_list[3];

	// Build the other vertices
	_dword list_index = 4;
	for ( _dword i = 6; i < vb_number; i += 6, list_index += 2 )
	{
		{
			vertex_buffer[i] = vertex_buffer[i - 1];
			vertex_buffer[i + 1] = vertex_buffer[i - 2];

			GraphicVertexInfo& vertex = vertex_buffer[i + 2];
			vertex.mPosition = pos_list[list_index];
			vertex.mColor = color_list[list_index];
			vertex.mUV1 = uv_list[list_index];
		}

		{
			vertex_buffer[i + 3] = vertex_buffer[i - 1];
			vertex_buffer[i + 4] = vertex_buffer[i + 2];

			GraphicVertexInfo& vertex = vertex_buffer[i + 5];
			vertex.mPosition = pos_list[list_index + 1];
			vertex.mColor = color_list[list_index + 1];
			vertex.mUV1 = uv_list[list_index + 1];
		}
	}

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_TRIANGLE_LIST, 1.0f, sizeof( GraphicVertexInfo ), vb_number );
	info.mGeometryInfo.mTextures[ ASTROBJ( uDiffuseTex ) ]	= sprite->GetResource( );

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_VP, info );
}

_void GraphicGeometryBuilder::BuildSpriteGeometryIn3x3Mode( IGraphicTexture2D* sprite, const Vector2& offset, const Vector2& size, const RectU& block_region, const Matrix3& transform, const GraphicUVInfo& uv_info, const Color& color, GeometryBuildInfo& info )
{
	// Get the number of VB
	const _dword vb_number = 9 * 6;

	// Build vertex buffer
	AllocVB( info, vb_number );
	GraphicVertexInfo* vertex_buffer = info.mVertexBuffer;

	// Get the sprite width
	_dword width	= sprite->GetWidth( );
	_dword height	= sprite->GetHeight( );

	// Get the UV
	const Vector2& uv1 = uv_info.mLT;
	const Vector2& uv2 = uv_info.mRB;

	// Get the original sprite size
	_dword original_width	= (_dword)((uv2.x - uv1.x) * (_float)width);
	_dword original_height	= (_dword)((uv2.y - uv1.y) * (_float)height);

	// Build vertex buffer
	Vector2 position = - size / 2.0f + offset;

	// Fix region size
	RectU fixed_block_region = block_region;
	fixed_block_region.r --;
	fixed_block_region.b --;

	// Convert block region to float mode
	RectF block_region_f = ConvertRectU2RectF( fixed_block_region );

	Vector2 block_uv1 = Vector2( uv1.x + EGE_RATIO( fixed_block_region.l, width ), uv1.y + EGE_RATIO( fixed_block_region.t, height ) );
	Vector2 block_uv2 = Vector2( uv2.x - EGE_RATIO( original_width - fixed_block_region.r, width ), uv2.y - EGE_RATIO( original_height - fixed_block_region.b, height ) );

	Vector2 block_lb_size( block_region_f.l, original_height - block_region_f.b );
	Vector2 block_rb_size( original_width - block_region_f.r, block_lb_size.y );

	// LT
	Vector2 lt_lt( 0.0f, 0.0f );
	Vector2 lt_rt( block_region_f.l, lt_lt.y );
	Vector2 lt_rb( lt_rt.x, block_region_f.t );
	Vector2 lt_lb( lt_lt.x, lt_rb.y );

	Vector2 lt_uv1 = sprite->FixUV( Vector2( uv1.x, uv1.y ) );
	Vector2 lt_uv2 = sprite->FixUV( Vector2( block_uv1.x, block_uv1.y ) );

	SetRectangle( vertex_buffer, position, lt_lt, lt_rt, lt_lb, lt_rb, color, GraphicUVInfo( lt_uv1, lt_uv2 ), transform );
	vertex_buffer += 6;

	// LB
	Vector2 lb_lt( 0.0f, size.y - block_lb_size.y );
	Vector2 lb_rt( block_region_f.l, lb_lt.y );
	Vector2 lb_rb( lb_rt.x, size.y );
	Vector2 lb_lb( lb_lt.x, lb_rb.y );

	Vector2 lb_uv1 = sprite->FixUV( Vector2( uv1.x, block_uv2.y ) );
	Vector2 lb_uv2 = sprite->FixUV( Vector2( block_uv1.x, uv2.y ) );

	SetRectangle( vertex_buffer, position, lb_lt, lb_rt, lb_lb, lb_rb, color, GraphicUVInfo( lb_uv1, lb_uv2 ), transform );
	vertex_buffer += 6;

	// RB
	Vector2 rb_lt( size.x - block_rb_size.x, size.y - block_lb_size.y );
	Vector2 rb_rt( size.x, rb_lt.y );
	Vector2 rb_rb( rb_rt.x, size.y );
	Vector2 rb_lb( rb_lt.x, rb_rb.y );

	Vector2 rb_uv1 = sprite->FixUV( Vector2( block_uv2.x, block_uv2.y ) );
	Vector2 rb_uv2 = sprite->FixUV( Vector2( uv2.x, uv2.y ) );

	SetRectangle( vertex_buffer, position, rb_lt, rb_rt, rb_lb, rb_rb, color, GraphicUVInfo( rb_uv1, rb_uv2 ), transform );
	vertex_buffer += 6;

	// RT
	Vector2 rt_lt( size.x - block_rb_size.x, 0.0f );
	Vector2 rt_rt( size.x, rt_lt.y );
	Vector2 rt_rb( rt_rt.x, block_region_f.t );
	Vector2 rt_lb( rt_lt.x, rt_rb.y );

	Vector2 rt_uv1 = sprite->FixUV( Vector2( block_uv2.x, uv1.y ) );
	Vector2 rt_uv2 = sprite->FixUV( Vector2( uv2.x, block_uv1.y ) );

	SetRectangle( vertex_buffer, position, rt_lt, rt_rt, rt_lb, rt_rb, color, GraphicUVInfo( rt_uv1, rt_uv2 ), transform );
	vertex_buffer += 6;

	// LEFT 
	Vector2 l_uv1 = sprite->FixUV( Vector2( uv1.x, block_uv1.y ) );
	Vector2 l_uv2 = sprite->FixUV( Vector2( block_uv1.x, block_uv2.y ) );

	SetRectangle( vertex_buffer, position, lt_lb, lt_rb, lb_lt, lb_rt, color, GraphicUVInfo( l_uv1, l_uv2 ), transform );
	vertex_buffer += 6;

	// RIGHT
	Vector2 r_uv1 = sprite->FixUV( Vector2( block_uv2.x, block_uv1.y ) );
	Vector2 r_uv2 = sprite->FixUV( Vector2( uv2.x, block_uv2.y ) );

	SetRectangle( vertex_buffer, position, rt_lb, rt_rb, rb_lt, rb_rt, color, GraphicUVInfo( r_uv1, r_uv2 ), transform );
	vertex_buffer += 6;

	// TOP
	Vector2 t_uv1 = sprite->FixUV( Vector2( block_uv1.x, uv1.y ) );
	Vector2 t_uv2 = sprite->FixUV( Vector2( block_uv2.x, block_uv1.y ) );

	SetRectangle( vertex_buffer, position, lt_rt, rt_lt, lt_rb, rt_lb, color, GraphicUVInfo( t_uv1, t_uv2 ), transform );
	vertex_buffer += 6;

	// BOTTOM
	Vector2 b_uv1 = sprite->FixUV( Vector2( block_uv1.x, block_uv2.y ) );
	Vector2 b_uv2 = sprite->FixUV( Vector2( block_uv2.x, uv2.y ) );

	SetRectangle( vertex_buffer, position, lb_rt, rb_lt, lb_rb, rb_lb, color, GraphicUVInfo( b_uv1, b_uv2 ), transform );
	vertex_buffer += 6;

	// CENTER
	Vector2 c_uv1 = sprite->FixUV( Vector2( block_uv1.x, block_uv1.y ) );
	Vector2 c_uv2 = sprite->FixUV( Vector2( block_uv2.x, block_uv2.y ) );

	SetRectangle( vertex_buffer, position, lt_rb, rt_lb, lb_rt, rb_lt, color, GraphicUVInfo( c_uv1, c_uv2 ), transform );
	vertex_buffer += 6;

	// Initialize geometry
	info.mGeometryInfo.Init( _PT_TRIANGLE_LIST, 1.0f, sizeof( GraphicVertexInfo ), vb_number );
	info.mGeometryInfo.mTextures[ ASTROBJ( uDiffuseTex ) ]	= sprite->GetResource( );

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_OVERLAY, info );
}

_void GraphicGeometryBuilder::BuildScreenAlignedBillboardGeometry( IGraphicTexture2D* sprite, const Matrix4& view_transform, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color, GeometryBuildInfo& info )
{
	// Calculate the camera info
	Vector3 up_axis = view_transform.GetUpVector( );
	Vector3 right_axis = view_transform.GetRightVector( );

	if ( up_axis != mSABUpAxis || right_axis != mSABRightAxis )
	{
		mSABUpAxis = up_axis;
		mSABRightAxis = right_axis;
		mSABMatrix = Matrix3( ).FromRotation( Quaternion( ).Rotation( Vector3::cXAxis, Vector3::cYAxis, mSABRightAxis, mSABUpAxis ) );
	}

	Vector3 lt( -0.5f, 0.5f, 1.0f );
	Vector3 rt( 0.5f, 0.5f, 1.0f );
	Vector3 lb( -0.5f, -0.5f, 1.0f );
	Vector3 rb( 0.5f, -0.5f, 1.0f );

	// Get the size of VB
	const _dword vb_number = 4;

	// Build vertex buffer
	AllocVB( info, vb_number );
	SetPrimitive( info.mVertexBuffer, lt, rt, lb, rb, vertex_offsets, transform, mSABMatrix, position, _null, uv_info, color );

	// Initialize index buffer
	info.mIndexBuffer.CreateInShareMode( EGE_ARRAY_NUMBER( s2TrianglsIndexBuffer ), s2TrianglsIndexBuffer );

	// Initialize geometry
	info.mGeometryInfo.InitWithIB( _PT_TRIANGLE_LIST, 1.0f, sizeof( GraphicVertexInfo ), vb_number, EGE_ARRAY_NUMBER( s2TrianglsIndexBuffer ) );
	info.mGeometryInfo.mTextures[ ASTROBJ( uDiffuseTex ) ]	= sprite->GetResource( );

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_VP, info );
}

_void GraphicGeometryBuilder::BuildViewpointOrientedBillboardGeometry( IGraphicTexture2D* sprite, const Matrix4& view_transform, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color, GeometryBuildInfo& info )
{
	// Skip the camera translation effect by using the inversed transform
	Matrix4 view_inverse = view_transform;
	view_inverse.Inverse( );

	// Calculate the camera info
	Vector3 up_axis = view_transform.GetUpVector( );
	Vector3 look_axis = view_inverse.GetTranslationVector( ) - position;

	if ( up_axis != mVOBUpAxis || look_axis != mVOBLookAxis )
	{
		mVOBUpAxis = up_axis;
		mVOBLookAxis = look_axis;
		Vector3 right_axis = Vector3::Cross( mVOBUpAxis, mVOBLookAxis ).Normalize( );
		mVOBMatrix = Matrix3( ).FromRotation( Quaternion( ).Rotation( Vector3::cXAxis, Vector3::cYAxis, right_axis, mVOBUpAxis ) );
	}

	Vector3 lt( -0.5f, 0.5f, 1.0f );
	Vector3 rt( 0.5f, 0.5f, 1.0f );
	Vector3 lb( -0.5f, -0.5f, 1.0f );
	Vector3 rb( 0.5f, -0.5f, 1.0f );

	// Get the size of VB
	const _dword vb_number = 4;

	// Build vertex buffer
	AllocVB( info, vb_number );
	SetPrimitive( info.mVertexBuffer, lt, rt, lb, rb, vertex_offsets, transform, mVOBMatrix, position, _null, uv_info, color );

	// Initialize index buffer
	info.mIndexBuffer.CreateInShareMode( EGE_ARRAY_NUMBER( s2TrianglsIndexBuffer ), s2TrianglsIndexBuffer );

	// Initialize geometry
	info.mGeometryInfo.InitWithIB( _PT_TRIANGLE_LIST, 1.0f, sizeof( GraphicVertexInfo ), vb_number, EGE_ARRAY_NUMBER( s2TrianglsIndexBuffer ) );
	info.mGeometryInfo.mTextures[ ASTROBJ( uDiffuseTex ) ]	= sprite->GetResource( );

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_VP, info );
}

_void GraphicGeometryBuilder::BuildAxialBillboardGeometry( IGraphicTexture2D* sprite, const Matrix4& view_transform, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const Vector3* scaling, const Vector3& axis, const GraphicUVInfo& uv_info, const Color& color, GeometryBuildInfo& info )
{
	// Skip the camera translation effect by using the inversed transform
	Matrix4 view_inverse = view_transform;
	view_inverse.Inverse( );

	// Calculate the camera info
	Vector3 up_axis = Vector3( axis ).Normalize( );
	Vector3 look_axis = view_inverse.GetTranslationVector( ) - position;

	if ( up_axis != mABUpAxis || look_axis != mABLookAxis )
	{
		mABUpAxis = up_axis;
		mABLookAxis = look_axis;
		Vector3 right_axis = Vector3::Cross( mABUpAxis, mABLookAxis ).Normalize( );
		mABMatrix = Matrix3( ).FromRotation( Quaternion( ).Rotation( Vector3::cXAxis, Vector3::cYAxis, right_axis, mABUpAxis ) );
	}

	Vector3 lt( -0.5f, 0.5f, 1.0f );
	Vector3 rt( 0.5f, 0.5f, 1.0f );
	Vector3 lb( -0.5f, -0.5f, 1.0f );
	Vector3 rb( 0.5f, -0.5f, 1.0f );

	// Get the size of VB
	const _dword vb_number = 4;

	// Build vertex buffer
	AllocVB( info, vb_number );
	SetPrimitive( info.mVertexBuffer, lt, rt, lb, rb, vertex_offsets, transform, mABMatrix, position, scaling, uv_info, color );

	// Initialize index buffer
	info.mIndexBuffer.CreateInShareMode( EGE_ARRAY_NUMBER( s2TrianglsIndexBuffer ), s2TrianglsIndexBuffer );

	// Initialize geometry
	info.mGeometryInfo.InitWithIB( _PT_TRIANGLE_LIST, 1.0f, sizeof( GraphicVertexInfo ), vb_number, EGE_ARRAY_NUMBER( s2TrianglsIndexBuffer ) );
	info.mGeometryInfo.mTextures[ ASTROBJ( uDiffuseTex ) ]	= sprite->GetResource( );

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_VP, info );
}

_void GraphicGeometryBuilder::BuildRectBillboardGeometry( IGraphicTexture2D* sprite, const Vector2* vertex_offsets, const Matrix3& transform, const Vector3& position, const GraphicUVInfo& uv_info, const Color& color, GeometryBuildInfo& info )
{
	Vector3 lt( -0.5f, -0.5f, 1.0f );
	Vector3 rt( 0.5f, -0.5f, 1.0f );
	Vector3 lb( -0.5f, 0.5f, 1.0f );
	Vector3 rb( 0.5f, 0.5f, 1.0f );

	// Get the size of VB
	const _dword vb_number = 4;

	// Build vertex buffer
	AllocVB( info, vb_number );
	SetPrimitive( info.mVertexBuffer, lt, rt, lb, rb, vertex_offsets, transform, Matrix3::cIdentity, position, _null, uv_info, color );

	// Initialize index buffer
	info.mIndexBuffer.CreateInShareMode( EGE_ARRAY_NUMBER( s2TrianglsIndexBuffer ), s2TrianglsIndexBuffer );

	// Initialize geometry
	info.mGeometryInfo.InitWithIB( _PT_TRIANGLE_LIST, 1.0f, sizeof( GraphicVertexInfo ), vb_number, EGE_ARRAY_NUMBER( s2TrianglsIndexBuffer ) );
	info.mGeometryInfo.mTextures[ ASTROBJ( uDiffuseTex ) ]	= sprite->GetResource( );

	// Build geometry
	BuildGeometry( GraphicGeometryBuilder::_TRANSFORM_VP, info );
}

_void GraphicGeometryBuilder::BuildCharacterGeometry( _dword prev_code, _dword code, FontRHI* font_resource, const FontCodeRHI* font_code, const Color& color, const Vector2& position, const Matrix3& transform, GeometryBuildInfo& info )
{
	// Get the font face
	IFontFace* font_face = GetDynamicRHI( )->GetFontFace( font_resource );
	EGE_ASSERT( font_face != _null );

	// Get the render position
	Vector2 render_pos = position;

	// If it's Thai language then need to check code ( move the tone character down when we don't have upper vowel character )
	if ( Platform::IsToneInThai( (_charw) code ) && ( prev_code != 0 && !Platform::IsUpperVowelInThai( (_charw) prev_code ) ) )
	{
		// Get the font texture
		const FontCodeRHI* vowel_font_code = gDynamicRHI->GetFontCode( font_resource, 0x0E34 );
		if ( vowel_font_code == _null )
			return;

		render_pos.y += vowel_font_code->mCharHeight;
	}

	// Get the amount between characters
	_int amount = font_face->GetAmountBetweenCharacters( prev_code, code );

	// Update the render pos
	render_pos.x += amount;

	// Get the character size and render position
	Vector2 char_size( (_float) font_code->mBitmapWidth, (_float) font_code->mBitmapHeight );
	Vector2 char_pos( render_pos.x + font_code->mOffsetX, render_pos.y + font_code->mOffsetY );

	// Get the UV
	Vector2 uv1 = font_face->GetUV( font_code->mStartX, font_code->mStartY );
	Vector2 uv2 = font_face->GetUV( font_code->mStartX + font_code->mBitmapWidth, font_code->mStartY + font_code->mBitmapHeight );

	// Get the size of VB
	const _dword vb_number = 4;

	// Set the vertex buffer
	AllocVB( info, vb_number );
	SetOverlay( info.mVertexBuffer, char_pos, char_size, _null, transform, GraphicUVInfo( uv1, uv2 ), color );

	// Initialize index buffer
	info.mIndexBuffer.CreateInShareMode( EGE_ARRAY_NUMBER( s2TrianglsIndexBuffer ), s2TrianglsIndexBuffer );

	// Initialize geometry
	info.mGeometryInfo.InitWithIB( _PT_TRIANGLE_LIST, 1.0f, sizeof( GraphicVertexInfo ), 4, EGE_ARRAY_NUMBER( s2TrianglsIndexBuffer ) );
	info.mGeometryInfo.mTextures[ ASTROBJ( uDiffuseTex ) ]	= font_code->mTexture;

	// Build geometry
	BuildGeometry( _TRANSFORM_OVERLAY, info );
}