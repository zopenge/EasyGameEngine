//! @file     GLVertexDeclaration.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLDrv-VertexDeclaration Implementation
//----------------------------------------------------------------------------

VertexDeclarationRHIPassRef GLDrv::CreateVertexDeclaration( const VertexElementRHIArray& elements )
{
	GLVertexDeclaration* vertex_decl = new GLVertexDeclaration( );
	if ( vertex_decl->Initialize( elements ) == _false )
		{ EGE_RELEASE( vertex_decl ); return _null; }

	return vertex_decl;
}

_dword GLDrv::GetVertexDeclarationVertexType( VertexDeclarationRHI* declaration )
{
	DYNAMIC_CAST_GLRESOURCE( VertexDeclaration, declaration );

	return gl_declaration->GetVertexType( );
}

_dword GLDrv::GetVertexDeclarationStride( VertexDeclarationRHI* declaration )
{
	DYNAMIC_CAST_GLRESOURCE( VertexDeclaration, declaration );

	return gl_declaration->GetStride( );
}

const VertexElementRHIArray& GLDrv::GetVertexDeclarationDefine( VertexDeclarationRHI* declaration )
{
	DYNAMIC_CAST_GLRESOURCE( VertexDeclaration, declaration );

	return gl_declaration->GetDefine( );
}

//----------------------------------------------------------------------------
// GLVertexDeclaration Implementation
//----------------------------------------------------------------------------

GLVertexDeclaration::GLVertexDeclaration( )
{
	mStride = 0;
}

GLVertexDeclaration::~GLVertexDeclaration( )
{

}

_ubool GLVertexDeclaration::Initialize( const VertexElementRHIArray& elements )
{
	mDefine = elements;

	for ( _dword index = 0; index < elements.Number( ); index ++ )
	{
		const VertexElementRHI& element = elements[index];

		GLVertexElement gl_element;
		gl_element.mOffset	= (_byte) element.mOffset;

		// The element type
		switch ( element.mType )
		{
			case _VET_FLOAT1:	gl_element.mType = GL_FLOAT; gl_element.mStride = 1; gl_element.mNormalized = _false; mStride += gl_element.mStride * sizeof( _float ); break;
			case _VET_FLOAT2:	gl_element.mType = GL_FLOAT; gl_element.mStride = 2; gl_element.mNormalized = _false; mStride += gl_element.mStride * sizeof( _float ); break;
			case _VET_FLOAT3:	gl_element.mType = GL_FLOAT; gl_element.mStride = 3; gl_element.mNormalized = _false; mStride += gl_element.mStride * sizeof( _float ); break;
			case _VET_FLOAT4:	gl_element.mType = GL_FLOAT; gl_element.mStride = 4; gl_element.mNormalized = _false; mStride += gl_element.mStride * sizeof( _float ); break;
			case _VET_UBYTE4:	gl_element.mType = GL_UNSIGNED_BYTE; gl_element.mStride = 4; gl_element.mNormalized = _false; mStride += gl_element.mStride * sizeof( _byte ); break;
			case _VET_UBYTE4N:	gl_element.mType = GL_UNSIGNED_BYTE; gl_element.mStride = 4; gl_element.mNormalized = _true; mStride += gl_element.mStride * sizeof( _byte ); break;
			case _VET_COLOR:	gl_element.mType = GL_UNSIGNED_BYTE; gl_element.mStride = 4; gl_element.mNormalized = _true; mStride += gl_element.mStride * sizeof( _byte ); break;
			case _VET_SHORT2:	gl_element.mType = GL_SHORT; gl_element.mStride = 2; gl_element.mNormalized = _true; mStride += gl_element.mStride * sizeof( _word ); break;
			default:
				EGE_ASSERT( 0 );
		}

		// The element usage
		switch ( element.mUsage )
		{
			case _VEU_POSITION:				gl_element.mUsage = _GL_ATTRI_POSITION; break;
			case _VEU_TEXTURE_COORDINATE:	EGE_ASSERT( element.mUsageIndex < 8 ); gl_element.mUsage = (_byte)(_GL_ATTRI_TEXCOORD0 + element.mUsageIndex); break;
			case _VEU_BLEND_WEIGHT:			gl_element.mUsage = _GL_ATTRI_BLEND_WEIGHT; break;
			case _VEU_BLEND_INDICES:		gl_element.mUsage = _GL_ATTRI_BLEND_INDICES; break;
			case _VEU_NORMAL:				gl_element.mUsage = _GL_ATTRI_NORMAL; break;
			case _VEU_COLOR:				EGE_ASSERT( element.mUsageIndex < 2 ); gl_element.mUsage = (_byte)(_GL_ATTRI_COLOR0 + element.mUsageIndex); break;
			case _VEU_TANGENT:				gl_element.mUsage = _GL_ATTRI_TANGENT; break;
			default:
				EGE_ASSERT( 0 );
				break;
		}

		// Append it
		mVertexElements.Append( gl_element );
	}

	// Sort the elements by stream then offset
	mVertexElements.SortAscending( );

	return _true;
}

_dword GLVertexDeclaration::GetVertexType( ) const
{
	_dword vertex_type = 0;

	for ( _dword i = 0; i < mVertexElements.Number( ); i ++ )
	{
		const GLVertexElement& gl_element = mVertexElements[i];

		switch ( gl_element.mUsage )
		{
			case _GL_ATTRI_POSITION:		vertex_type |= _GVT_POS; break;
			case _GL_ATTRI_TEXCOORD0:		vertex_type |= _GVT_UV1; break;
			case _GL_ATTRI_TEXCOORD1:		vertex_type |= _GVT_UV2; break;
			case _GL_ATTRI_BLEND_WEIGHT:	vertex_type |= _GVT_BONE_WEIGHT; break;
			case _GL_ATTRI_BLEND_INDICES:	vertex_type |= _GVT_BONE_INDICES; break;
			case _GL_ATTRI_NORMAL:			vertex_type |= _GVT_NORMAL; break;
			case _GL_ATTRI_COLOR0:			vertex_type |= _GVT_COLOR0; break;
			case _GL_ATTRI_COLOR1:			vertex_type |= _GVT_COLOR1; break;
			case _GL_ATTRI_TANGENT:			vertex_type |= _GVT_TANGENT; break;
			default:
				EGE_ASSERT( 0 );
				break;
		};
	}

	return vertex_type;
}
