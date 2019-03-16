//! @file     GraphicVertexDeclaration.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicVertexDeclaration Implementation
//----------------------------------------------------------------------------

GraphicVertexDeclaration::GraphicVertexDeclaration( )
{
	mVertexType = 0;
}

GraphicVertexDeclaration::~GraphicVertexDeclaration( )
{
}

_VERTEX_ELEMENT_TYPE GraphicVertexDeclaration::GetElementType( WStringPtr type )
{
	static WStringPtr sTypeString[ _VET_MAXNUMBER ] = 
	{
		L"",
		L"float1",
		L"float2",
		L"float3",
		L"float4",
		L"ubyte4",
		L"ubyte4n",
		L"color",
		L"short2",
	};

	for ( _dword i = 0; i < _VET_MAXNUMBER; i ++ )
	{
		if ( type == sTypeString[i] )
			return (_VERTEX_ELEMENT_TYPE) i;
	}

	return _VET_NONE;
}

_dword GraphicVertexDeclaration::GetElementTypeSize( _VERTEX_ELEMENT_TYPE type )
{
	switch ( type )
	{
		case _VET_FLOAT1:	return sizeof( _float );
		case _VET_FLOAT2:	return sizeof( _float ) * 2;
		case _VET_FLOAT3:	return sizeof( _float ) * 3;
		case _VET_FLOAT4:	return sizeof( _float ) * 4;
		case _VET_UBYTE4:	return sizeof( _byte ) * 4;
		case _VET_UBYTE4N:	return sizeof( _byte ) * 4;
		case _VET_COLOR:	return sizeof( _dword );
		case _VET_SHORT2:	return sizeof( _short ) * 2;
		default:
			return 0;
	}
}

_VERTEX_ELEMENT_USAGE GraphicVertexDeclaration::GetElementUsage( WStringPtr usage )
{
	static WStringPtr sUsageString[ _VEU_MAXNUMBER ] = 
	{
		L"",
		L"position",
		L"uv",
		L"blend_weight",
		L"blend_indices",
		L"normal",
		L"color",
		L"tangent",
	};

	for ( _dword i = 0; i < _VEU_MAXNUMBER; i ++ )
	{
		if ( usage == sUsageString[i] )
			return (_VERTEX_ELEMENT_USAGE) i;
	}

	return _VEU_NONE;
}

_ubool GraphicVertexDeclaration::Initialize( _dword vertex_type )
{
	if ( vertex_type == 0 )
		return _false;

	mVertexType = vertex_type;

	// The elements of vertex
	VertexElementRHIArray vertex_elements;

	// Start to build elements of vertex
	_dword index = 0, offset = 0;
	for ( _dword vertex_type_temp = vertex_type; vertex_type_temp != 0; vertex_type_temp >>= 1 )
	{
		// Get the vertex type by masking
		_dword type = vertex_type & ( 1 << (index ++) );
		if ( type == 0 )
			continue;

		// Build element of vertex declaration
		VertexElementRHI vertex_element;
		vertex_element.mOffset	= offset;

		// Set type and usage
		switch ( type )
		{
			case _GVT_POS:
				vertex_element.mType	= _VET_FLOAT3;
				vertex_element.mUsage	= _VEU_POSITION;
				break;

			case _GVT_COLOR0:
				vertex_element.mType		= _VET_COLOR;
				vertex_element.mUsage		= _VEU_COLOR;
				vertex_element.mUsageIndex	= 0;
				break;

			case _GVT_COLOR1:
				vertex_element.mType		= _VET_COLOR;
				vertex_element.mUsage		= _VEU_COLOR;
				vertex_element.mUsageIndex	= 1;
				break;

			case _GVT_NORMAL:
				vertex_element.mType	= _VET_FLOAT3;
				vertex_element.mUsage	= _VEU_NORMAL;
				break;

			case _GVT_UV1:
				vertex_element.mType		= _VET_FLOAT2;
				vertex_element.mUsage		= _VEU_TEXTURE_COORDINATE;
				vertex_element.mUsageIndex	= 0;
				break;

			case _GVT_UV2:
				vertex_element.mType		= _VET_FLOAT2;
				vertex_element.mUsage		= _VEU_TEXTURE_COORDINATE;
				vertex_element.mUsageIndex	= 1;
				break;

			case _GVT_BONE_INDICES:
				vertex_element.mType	= _VET_UBYTE4;
				vertex_element.mUsage	= _VEU_BLEND_INDICES;
				break;

			case _GVT_BONE_WEIGHT:
				vertex_element.mType	= _VET_FLOAT4;
				vertex_element.mUsage	= _VEU_BLEND_WEIGHT;
				break;

			case _GVT_TANGENT:
				vertex_element.mType	= _VET_FLOAT4;
				vertex_element.mUsage	= _VEU_TANGENT;
				break;

			default:
				EGE_ASSERT( 0 );
				break;
		}

		// Append vertex element
		vertex_elements.Append( vertex_element );

		// Update offset
		offset += GetElementTypeSize( vertex_element.mType );
	}

	// Create vertex declaration resource
	mVertexDeclRHI = gDynamicRHI->CreateVertexDeclaration( vertex_elements );
	if ( mVertexDeclRHI.IsNull( ) )
		return _false;

	return _true;
}

_ubool GraphicVertexDeclaration::Initialize( VertexDeclarationRHI* vertex_decl )
{
	if ( vertex_decl == _null )
		return _false;

	_dword vertex_type = gDynamicRHI->GetVertexDeclarationVertexType( vertex_decl );
	if ( vertex_type == 0 )
		return _false;

	mVertexDeclRHI	= vertex_decl;
	mVertexType		= vertex_type;

	return _true;
}

_dword GraphicVertexDeclaration::GetVertexType( ) const
{
	return mVertexType;
}

_dword GraphicVertexDeclaration::GetStride( ) const
{
	return gDynamicRHI->GetVertexDeclarationStride( mVertexDeclRHI.GetPtr( ) );
}

_dword GraphicVertexDeclaration::GetElementOffset( _VERTEX_ELEMENT_USAGE usage, _dword usage_index ) const
{
	// Get vertex declaration define
	const VertexElementRHIArray& vertex_decl_define = GetDynamicRHI( )->GetVertexDeclarationDefine( mVertexDeclRHI.GetPtr( ) );

	// Get offset of element
	for ( _dword i = 0; i < vertex_decl_define.Number( ); i ++ )
	{
		if ( vertex_decl_define[i].mUsage == usage && vertex_decl_define[i].mUsageIndex == usage_index )
			return vertex_decl_define[i].mOffset;
	}

	return -1;
}

VertexDeclarationRHI* GraphicVertexDeclaration::GetResource( )
{
	return mVertexDeclRHI;
}