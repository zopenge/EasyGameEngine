//! @file     RHIResource.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Common RHI definitions
//----------------------------------------------------------------------------

//!	The (RRT, Render Resource Type)
enum _RENDER_RESOURCE_TYPE
{
	_RRT_NONE,

	//! @name Render state
	//!	@{
	_RRT_RENDER_STATE,
	_RRT_SAMPLER_STATE,
	_RRT_RASTERIZER_STATE,
	_RRT_DEPTH_STATE,
	_RRT_STENCIL_STATE,
	_RRT_BLEND_STATE,
	//! @}

	//! @name Render resource
	//!	@{
	_RRT_VERTEX_SHADER,
	_RRT_PIXEL_SHADER,
	_RRT_BOUND_SHADER,
	_RRT_INDEX_BUFFER,
	_RRT_VERTEX_BUFFER,
	_RRT_VERTEX_DECLARATION,
	_RRT_VERTEX_ARRAY,
	_RRT_SURFACE,
	_RRT_TEXTURE,
	_RRT_TEXTURE_2D,
	_RRT_TEXTURE_CUBE,
	_RRT_FONT,
	//! @}

	//! @name Render viewport
	//!	@{
	_RRT_VIEWPORT,
	//! @}
};

//!	@export_script_enum("EnumSamplerFilter", "Enum of sampler filter type(SF, Sampler Filter)")
enum _SAMPLER_FILTER
{
	//!	@enum("NEAREST", "")
	_SF_NEAREST,
	//!	@enum("LINEAR", "")
	_SF_LINEAR,
};

//!	@export_script_enum("EnumSamplerAddressMode", "The (SAM, Sampler Address Mode)")
enum _SAMPLER_ADDRESS_MODE
{
	//!	@enum("WRAP", "")
	_SAM_WRAP,
	//!	@enum("CLAMP", "")
	_SAM_CLAMP,
	//!	@enum("CLAMP_TO_EDGE", "")
	_SAM_CLAMP_TO_EDGE,
	//!	@enum("MIRROR", "")
	_SAM_MIRROR,
	//!	@enum("REPEAT", "")
	_SAM_REPEAT,
};

//!	@export_script_enum("EnumRasterizerFillMode", "The (RFM, Rasterizer Fill Mode)")
enum _RASTERIZER_FILL_MODE
{
	//!	@enum("POINT", "")
	_RFM_POINT,
	//!	@enum("WIREFRAME", "")
	_RFM_WIREFRAME,
	//!	@enum("SOLID", "")
	_RFM_SOLID
};

//!	@export_script_enum("EnumRasterizerCullMode", "The (RCM, Rasterizer Cull Mode)")
enum _RASTERIZER_CULL_MODE
{
	//!	@enum("NONE", "")
	_RCM_NONE,
	//!	@enum("CW", "")
	_RCM_CW,
	//!	@enum("CCW", "")
	_RCM_CCW
};

//!	@export_script_enum("EnumColorWriteMask", "The (CWM, Color Write Mask)")
enum _COLOR_WRITE_MASK
{
	//!	@enum("RED", "")
	_CWM_RED	= 1 << 0,
	//!	@enum("GREEN", "")
	_CWM_GREEN	= 1 << 1,
	//!	@enum("BLUE", "")
	_CWM_BLUE	= 1 << 2,
	//!	@enum("ALPHA", "")
	_CWM_ALPHA	= 1 << 3,

	//!	@enum("RGB", "")
	_CWM_RGB	= _CWM_RED | _CWM_GREEN | _CWM_BLUE,
	//!	@enum("RGBA", "")
	_CWM_RGBA	= _CWM_RGB | _CWM_ALPHA,
};

//!	@export_script_enum("EnumCompareFunction", "The (CF, Compare Function)")
enum _COMPARE_FUNCTION
{
	//!	@enum("LESS", "")
	_CF_LESS,
	//!	@enum("LESS_EQUAL", "")
	_CF_LESS_EQUAL,
	//!	@enum("GREATER", "")
	_CF_GREATER,
	//!	@enum("GREATER_EQUAL", "")
	_CF_GREATER_EQUAL,
	//!	@enum("EQUAL", "")
	_CF_EQUAL,
	//!	@enum("NOT_EQUAL", "")
	_CF_NOT_EQUAL,
	//!	@enum("NEVER", "")
	_CF_NEVER,
	//!	@enum("ALWAYS", "")
	_CF_ALWAYS
};

//!	@export_script_enum("EnumStencilOperation", "The (SO, Stencil Operation)")
enum _STENCIL_OPERATION
{
	//!	@enum("KEEP", "")
	_SO_KEEP,
	//!	@enum("ZERO", "")
	_SO_ZERO,
	//!	@enum("REPLACE", "")
	_SO_REPLACE,
	//!	@enum("SATURATED_INCREMENT", "")
	_SO_SATURATED_INCREMENT,
	//!	@enum("SATURATED_DECREMENT", "")
	_SO_SATURATED_DECREMENT,
	//!	@enum("INVERT", "")
	_SO_INVERT,
	//!	@enum("INCREMENT", "")
	_SO_INCREMENT,
	//!	@enum("DECREMENT", "")
	_SO_DECREMENT
};

//!	@export_script_enum("EnumBlendFactor", "The (BF, Blend Factor)")
enum _BLEND_FACTOR
{
	//!	@enum("ZERO", "")
	_BF_ZERO,
	//!	@enum("ONE", "")
	_BF_ONE,
	//!	@enum("SOURCE_COLOR", "")
	_BF_SOURCE_COLOR,
	//!	@enum("INVERSE_SOURCE_COLOR", "")
	_BF_INVERSE_SOURCE_COLOR,
	//!	@enum("SOURCE_ALPHA", "")
	_BF_SOURCE_ALPHA,
	//!	@enum("INVERSE_SOURCE_ALPHA", "")
	_BF_INVERSE_SOURCE_ALPHA,
	//!	@enum("DEST_ALPHA", "")
	_BF_DEST_ALPHA,
	//!	@enum("INVERSE_DEST_ALPHA", "")
	_BF_INVERSE_DEST_ALPHA,
	//!	@enum("DEST_COLOR", "")
	_BF_DEST_COLOR,
	//!	@enum("INVERSE_DEST_COLOR", "")
	_BF_INVERSE_DEST_COLOR
};

//!	The font load flags
enum _FONT_LOAD_FLAGS
{
	_FLF_DEFAULT = 0,
};

//!	The (VET, Vertex Element Type)
enum _VERTEX_ELEMENT_TYPE
{
	_VET_NONE,

	_VET_FLOAT1,
	_VET_FLOAT2,
	_VET_FLOAT3,
	_VET_FLOAT4,
	_VET_UBYTE4,
	_VET_UBYTE4N,
	_VET_COLOR,
	_VET_SHORT2,

	_VET_MAXNUMBER,
};

//!	The (VEU, Vertex Element Usage)
enum _VERTEX_ELEMENT_USAGE
{
	_VEU_NONE,

	_VEU_POSITION,				//!	"cPosition" constant name in shader
	_VEU_TEXTURE_COORDINATE,	//!	"cTexCoords(0~1)" constant name in shader
	_VEU_BLEND_WEIGHT,			//!	"cBlendWeight" constant name in shader
	_VEU_BLEND_INDICES,			//!	"cBlendIndices" constant name in shader
	_VEU_NORMAL,				//!	"cNormal" constant name in shader
	_VEU_COLOR,					//!	"cColor(0~1)" constant name in shader
	_VEU_TANGENT,				//!	"cTangent" constant name in shader

	_VEU_MAXNUMBER,
};

//!	The (PT, Primitive Type)
enum _PRIMITIVE_TYPE
{
	_PT_NONE,
	_PT_POINT_LIST,
	_PT_LINE_LIST,
	_PT_TRIANGLE_LIST,
	_PT_LINE_LOOP,
	_PT_TRIANGLE_STRIP,
	_PT_TRIANGLE_FAN,

	_PT_MAX_NUMBER,
};

//! The (PSR, Pixel Shader Register)
enum _PIXEL_SHADER_REGISTER
{
	_PSR_COLOR_BIAS_FACTOR,				//! Factor applied to the color output from the pixel shader
	_PSR_SCREEN_POSITION_SCALE_BIAS,	//! Converts projection-space XY coordinates to texture-space UV coordinates
	_PSR_MINZ_MAXZ_RATIO,				//! Converts device Z values to clip-space W values
};

//! The (VSR, Vertex Shader Registers)
enum _VERTEX_SHADER_REGISTER
{
	_VSR_VIEW_PROJ_MATRIX,	//! View-projection matrix, transforming from World space to Projection space
	_VSR_VIEW_ORIGIN,		//! World space position of the view's origin (camera position)
};

//! The (RDT, Resource Draw Type)
enum _RESOURCE_DRAW_TYPE
{
	_RDT_TYPE_STATIC	= 0, //! The resource will be uploaded once and drawn many times (e.g. the world).
	_RDT_TYPE_DYNAMIC	= 1, //! The resource will be changed from time to time, but drawn many times more than that.
	_RDT_TYPE_STREAM	= 2, //! The resource will change almost every time it's drawn (e.g. user interface).
};

//! Flags used for targetable surface creation
enum _TARGETABLE_SURFACE_CREATE_FLAGS
{
	// Without this the surface may simply be an alias for the texture's memory. Note that you must still resolve the surface.
    _TSCF_DEDICATED		= 1 << 0,
	// Surface must support reading.
	_TSCF_READABLE		= 1 << 1,
	// Surface will be only written to one time, in case that helps the platform
	_TSCF_WRITE_ONCE	= 1 << 2,
	// Surface will be created as multisampled.
	_TSCF_MULTISAMPLE	= 1 << 3,
};

//!	The flag determine how to update uniform buffer
enum _UNIFORM_BUFFER_DATA_TYPE
{
	_UBDT_UNKNOWN,

	_UBDT_BOOL,
	_UBDT_LONG,
	_UBDT_VEC1,
	_UBDT_VEC2,
	_UBDT_VEC3,
	_UBDT_VEC4,
	_UBDT_MATRIX_3x3,
	_UBDT_MATRIX_4x4,
	_UBDT_BUFFER,
};

//!	The cube-texture sub-face type
enum _CUBE_TEX_SUBFACE_TYPE
{
	_CUBE_TEX_SUBFACE_POS_X,	//! clockwise 270 degree
	_CUBE_TEX_SUBFACE_NEG_X,	//! clockwise 90 degree
	_CUBE_TEX_SUBFACE_POS_Y,	//! clockwise 180 degree
	_CUBE_TEX_SUBFACE_NEG_Y,	//! clockwise 0 degree
	_CUBE_TEX_SUBFACE_POS_Z,	//! clockwise 90 degree
	_CUBE_TEX_SUBFACE_NEG_Z,	//! clockwise 90 degree		
	_CUBE_TEX_SUBFACE_NUMBER,
};

//----------------------------------------------------------------------------
// The RHI resource types
//----------------------------------------------------------------------------

#define ENUM_RHI_RESOURCE_TYPES(EnumerationMacro)								\
	EnumerationMacro(RenderState, _RRT_RENDER_STATE, _RRT_NONE)					\
	EnumerationMacro(SamplerState, _RRT_SAMPLER_STATE, _RRT_RENDER_STATE)		\
	EnumerationMacro(RasterizerState, _RRT_RASTERIZER_STATE, _RRT_RENDER_STATE)	\
	EnumerationMacro(DepthState, _RRT_DEPTH_STATE, _RRT_RENDER_STATE)			\
	EnumerationMacro(StencilState, _RRT_STENCIL_STATE, _RRT_RENDER_STATE)		\
	EnumerationMacro(BlendState, _RRT_BLEND_STATE, _RRT_RENDER_STATE)			\
	EnumerationMacro(VertexShader, _RRT_VERTEX_SHADER, _RRT_NONE)				\
	EnumerationMacro(PixelShader, _RRT_PIXEL_SHADER, _RRT_NONE)					\
	EnumerationMacro(BoundShader, _RRT_BOUND_SHADER, _RRT_NONE)					\
	EnumerationMacro(IndexBuffer, _RRT_INDEX_BUFFER, _RRT_NONE)					\
	EnumerationMacro(VertexBuffer, _RRT_VERTEX_BUFFER, _RRT_NONE)				\
	EnumerationMacro(VertexDeclaration, _RRT_VERTEX_DECLARATION, _RRT_NONE)		\
	EnumerationMacro(VertexArray, _RRT_VERTEX_ARRAY, _RRT_NONE)					\
	EnumerationMacro(Surface, _RRT_SURFACE, _RRT_NONE)							\
	EnumerationMacro(Texture, _RRT_TEXTURE, _RRT_NONE)							\
	EnumerationMacro(Texture2D, _RRT_TEXTURE_2D, _RRT_TEXTURE)					\
	EnumerationMacro(TextureCube, _RRT_TEXTURE_CUBE, _RRT_TEXTURE)				\
	EnumerationMacro(Font, _RRT_FONT, _RRT_NONE)								\
	EnumerationMacro(Viewport, _RRT_VIEWPORT, _RRT_NONE)

template< _RENDER_RESOURCE_TYPE ResourceType >
class TDynamicRHIResource : public TObject< IObject >
{
protected:
#ifndef _EGE_DISABLE_RHI_STATS_
	//!	The assistant resource alive together
	TDynamicRHIResource*	mAsssistantResource;
#endif

protected:
	TDynamicRHIResource( )
	{
#ifndef _EGE_DISABLE_RHI_STATS_
		mAsssistantResource = _null; 
#endif
	}
	virtual ~TDynamicRHIResource( ) 
	{
#ifndef _EGE_DISABLE_RHI_STATS_
		EGE_RELEASE( mAsssistantResource ); 
#endif
	}

public:
#ifndef _EGE_DISABLE_RHI_STATS_
	EGE_GET_SET_ACCESSOR( TDynamicRHIResource*, AsssistantResource )
#endif
};
#define DEFINE_DYNAMICRHI_REFERENCE_TYPE(Type, ResourceType, ParentResourceType) \
template<> class TDynamicRHIResource< ResourceType > : public TDynamicRHIResource< ParentResourceType > \
{ \
public: \
	virtual _RENDER_RESOURCE_TYPE GetResourceType( ) const { return ResourceType; } \
}; \
typedef TDynamicRHIResource< ResourceType > Type##RHI; \
typedef RefPtr< Type##RHI > Type##RHIRef; \
typedef PassRefPtr< Type##RHI > Type##RHIPassRef;
ENUM_RHI_RESOURCE_TYPES(DEFINE_DYNAMICRHI_REFERENCE_TYPE)
#undef DEFINE_DYNAMICRHI_REFERENCE_TYPE

//----------------------------------------------------------------------------
// The RHI structures
//----------------------------------------------------------------------------

//!	The vertex shader info
struct GPUVertexShaderInfoRHI
{
	//!	The max vertex attributes number
	_dword	mMaxAttributesNumber;
	//!	The max vectors uniform number( not size, just a number of vertex-4 type )
	_dword	mMaxVectorsUniformNumber;

	GPUVertexShaderInfoRHI( )
	{
		mMaxAttributesNumber		= 0;
		mMaxVectorsUniformNumber	= 0;
	}
};

//!	The pixel shader info
struct GPUPixelShaderInfoRHI
{
	//!	The max vectors uniform number( not size, just a number of vertex-4 type )
	_dword	mMaxVectorsUniformNumber;

	GPUPixelShaderInfoRHI( )
	{
		mMaxVectorsUniformNumber = 0;
	}
};

//!	The shader info
struct GPUShaderInfoRHI
{
	//!	The max textures unit number
	_dword					mMaxTexturesUnitNumber;

	//!	The max varying vectors number
	_dword					mMaxVaryingVectorsNumber;
	//!	The max vertex texture image units
	_dword					mMaxVertexTextureImageUnitsNumber;
	//!	The max combined texture image units
	_dword					mMaxCombinedTextureImageUnitsNumber;

	//! The vertex shader configure info
	GPUVertexShaderInfoRHI	mVSInfo;
	//! The pixel shader configure info
	GPUPixelShaderInfoRHI	mPSInfo;

	GPUShaderInfoRHI( )
	{
		mMaxTexturesUnitNumber				= 0;

		mMaxVaryingVectorsNumber			= 0;
		mMaxVertexTextureImageUnitsNumber	= 0;
		mMaxCombinedTextureImageUnitsNumber = 0;
	}
};

//!	The GPU texture info
struct GPUTextureInfoRHI
{
	//!	The max texture size
	_dword	mMaxTextureSize;

	GPUTextureInfoRHI( )
	{
		mMaxTextureSize	= 0;
	}
};

//!	The texture cube with mipmaps info base
struct TextureCubeWithMipmapsRHIBase
{
	WString	mResNames[_CUBE_TEX_SUBFACE_NUMBER];

	_ubool Import( ISerializableNode* node )
	{
		if ( node == _null )
			return _false;

		mResNames[0] = node->GetChildValueByNameW( L"posx", L"res" );
		mResNames[1] = node->GetChildValueByNameW( L"negx", L"res" );
		mResNames[2] = node->GetChildValueByNameW( L"posy", L"res" );
		mResNames[3] = node->GetChildValueByNameW( L"negy", L"res" );
		mResNames[4] = node->GetChildValueByNameW( L"posz", L"res" );
		mResNames[5] = node->GetChildValueByNameW( L"negz", L"res" );

		return _true;
	}

	_ubool Export( ISerializableNode* node ) const
	{
		if ( node == _null )
			return _false;

		node->InsertChildNode( L"posx" )->Write( L"res", mResNames[0] );
		node->InsertChildNode( L"negx" )->Write( L"res", mResNames[1] );
		node->InsertChildNode( L"posy" )->Write( L"res", mResNames[2] );
		node->InsertChildNode( L"negy" )->Write( L"res", mResNames[3] );
		node->InsertChildNode( L"posz" )->Write( L"res", mResNames[4] );
		node->InsertChildNode( L"negz" )->Write( L"res", mResNames[5] );

		return _true;
	}
};

//!	The texture cube with mipmaps info
struct TextureCubeWithMipmapsRHI : public TextureCubeWithMipmapsRHIBase
{
	IImageFileRef mImageFiles[_CUBE_TEX_SUBFACE_NUMBER];

	//!	Check whether image size is valid.
	_ubool IsImageSizeValid( ) const
	{
		PointU min_size = PointU::cMaxPoint;
		PointU max_size = PointU::cMinPoint;

		for ( _dword i = 0; i < _CUBE_TEX_SUBFACE_NUMBER; i ++ )
		{
			IImageFile* image_file = mImageFiles[i];
			EGE_ASSERT( image_file != _null );

			min_size.x = Math::Min( image_file->GetWidth( ), min_size.x );
			min_size.y = Math::Min( image_file->GetHeight( ), min_size.y );
			max_size.x = Math::Max( image_file->GetWidth( ), max_size.x );
			max_size.y = Math::Max( image_file->GetHeight( ), max_size.y );
		}

		// Each images size must be the same
		if ( min_size != max_size )
			return _false;

		return _true;
	}

	//!	Get the size.
	PointU GetSize( ) const
	{
		EGE_ASSERT( mImageFiles[0].IsValid( ) );

		if ( IsImageSizeValid( ) == _false )
			return PointU::cZeroPoint;

		return PointU( mImageFiles[0]->GetWidth( ), mImageFiles[0]->GetHeight( ) );
	}

	//!	Get the mipmaps level.
	_dword GetMipmapLevel( ) const
	{
		PointU size = GetSize( );

		return Math::GetMipmapLevel( size.x, size.y );
	}
};

//!	The blur color info
struct BlurColorRHI
{
	//!	The blur size
	_dword	mSize;
	//!	The blur factor
	_dword	mFactor;
	//!	The blur color
	Color	mColor;

	BlurColorRHI( )
	{
		mSize		= 0;
		mFactor		= 0;
		mColor		= Color::cNull;
	}
	BlurColorRHI( _dword size, _dword factor, const Color& color )
	{
		mSize		= size;
		mFactor		= factor;
		mColor		= color;
	}
};

//!	The stroke color info
struct StrokeColorRHI
{
	//!	The border size
	_dword	mSize;
	//!	The border color
	Color	mColor;

	StrokeColorRHI( )
	{
		mSize	= 0;
		mColor	= Color::cNull;
	}
	StrokeColorRHI( _dword size, const Color& color )
	{
		mSize	= size;
		mColor	= color;
	}
};

//!	The font color info
struct FontColorRHI
{
	//!	The blur color info
	BlurColorRHI	mBlur;
	//!	The stroke color info
	StrokeColorRHI	mStroke;

	//!	The fill color
	Color			mFillColor;

	FontColorRHI( )
	{
		mFillColor = Color::cNull;
	}
	FontColorRHI( const Color& color )
	{
		mFillColor = color;
	}
	FontColorRHI( const Color& color, const StrokeColorRHI& stroke )
	{
		mFillColor	= color;

		mStroke		= stroke;
	}
	FontColorRHI( const Color& color, const BlurColorRHI& blur )
	{
		mFillColor	= color;

		mBlur		= blur;
	}
	FontColorRHI( const Color& color, const StrokeColorRHI& stroke, const BlurColorRHI& blur )
	{
		mFillColor	= color;

		mStroke		= stroke;
		mBlur		= blur;
	}
};

//!	The font code info
struct FontCodeRHI
{
	//!	The texture index, 0xFFFF indicates failure
	Texture2DRHI*	mTexture;
	//!	The char height in pixel
	_short			mCharHeight;
	//!	The start-x position in UV ( pixel )
	_short			mStartX;
	//!	The start-y position in UV ( pixel )
	_short			mStartY;
	//!	The offset-x position
	_short			mOffsetX;
	//!	The offset-y position
	_short			mOffsetY;
	//!	The X advance in pixel ( for the next character location )
	_short			mAdvanceX;
	//!	The descender in pixel
	_short			mDescender;
	//!	The base line in pixel
	_short			mBaseLine;
	//!	The bitmap top
	_short			mBitmapTop;
	//!	The bitmap width
	_short			mBitmapWidth;
	//!	The bitmap height
	_short			mBitmapHeight;
	//!	The reserved data to arrange 32 bits
	_short			mReserved;

	FontCodeRHI( )
	{
		mTexture		= _null;
		mCharHeight		= 0;
		mStartX			= 0;
		mStartY			= 0;
		mOffsetX		= 0;
		mOffsetY		= 0;
		mAdvanceX		= 0;
		mDescender		= 0;
		mBaseLine		= 0;
		mBitmapTop		= 0;
		mBitmapWidth	= 0;
		mBitmapHeight	= 0;
		mReserved		= 0;
	}
};

//!	The font initializer
struct FontInitializerRHI
{
	//!	The face type
	_FONT_FACE_TYPE	mType;
	//!	The font size.
	_dword			mSize;
	//!	The font styles, @see _FONT_STYLE.
	_dword			mStyles;

	//!	Check whether it's valid.
	_ubool IsValid( ) const
	{
		if ( mSize == 0 )
			return _false;

		return _true;
	}

	FontInitializerRHI( )
	{
		mType	= _FONT_FACE_UNKNOWN;
		mSize	= 0;
		mStyles	= 0;
	}
	FontInitializerRHI( _FONT_FACE_TYPE type, _dword size, _dword styles )
	{
		mType	= type;
		mSize	= size;
		mStyles	= styles;
	}
};

//!	The sampler state initializer
struct SamplerStateInitializerRHI
{
	_SAMPLER_FILTER			mFilter;
	_SAMPLER_ADDRESS_MODE 	mAddressU;
	_SAMPLER_ADDRESS_MODE 	mAddressV;
	_SAMPLER_ADDRESS_MODE 	mAddressW;

	SamplerStateInitializerRHI( _SAMPLER_FILTER filter )
	{
		mFilter		= filter;
		mAddressU	= _SAM_REPEAT;
		mAddressV	= _SAM_REPEAT;
		mAddressW	= _SAM_REPEAT;
	}
	SamplerStateInitializerRHI( _SAMPLER_FILTER filter, _SAMPLER_ADDRESS_MODE address_u, _SAMPLER_ADDRESS_MODE address_v, _SAMPLER_ADDRESS_MODE address_w )
	{
		mFilter		= filter;
		mAddressU	= address_u;
		mAddressV	= address_v;
		mAddressW	= address_w;
	}
};

//!	The rasterizer state initializer
struct RasterizerStateInitializerRHI
{
	_ubool					mEnableRedColorWrite;
	_ubool					mEnableGreenColorWrite;
	_ubool					mEnableBlueColorWrite;
	_ubool					mEnableAlphaColorWrite;
	_RASTERIZER_FILL_MODE 	mFillMode;
	_RASTERIZER_CULL_MODE 	mCullMode;

	RasterizerStateInitializerRHI( _RASTERIZER_FILL_MODE fill_mode, _RASTERIZER_CULL_MODE cull_mode )
	{
		mEnableRedColorWrite	= _true;
		mEnableGreenColorWrite	= _true;
		mEnableBlueColorWrite	= _true;
		mEnableAlphaColorWrite	= _true;
		mFillMode				= fill_mode;
		mCullMode				= cull_mode;
	}
	RasterizerStateInitializerRHI( _ubool enable_red_color_write, _ubool enable_green_color_write, _ubool enable_blue_color_write, _ubool enable_alpha_color_write, _RASTERIZER_FILL_MODE fill_mode, _RASTERIZER_CULL_MODE cull_mode )
	{
		mEnableRedColorWrite	= enable_red_color_write;
		mEnableGreenColorWrite	= enable_green_color_write;
		mEnableBlueColorWrite	= enable_blue_color_write;
		mEnableAlphaColorWrite	= enable_alpha_color_write;
		mFillMode				= fill_mode;
		mCullMode				= cull_mode;
	}
};

//!	The depth state initializer
struct DepthStateInitializerRHI
{
	_ubool				mEnableDepthWrite;
	_COMPARE_FUNCTION	mDepthTest;

	DepthStateInitializerRHI( _ubool enable_depth_write, _COMPARE_FUNCTION depth_test )
	{
		mEnableDepthWrite	= enable_depth_write;
		mDepthTest			= depth_test;
	}
};

//!	The stencil state initializer
struct StencilStateInitializerRHI
{
	_ubool				mEnableFrontFaceStencil;
	_COMPARE_FUNCTION	mFrontFaceStencilTest;
	_STENCIL_OPERATION 	mFrontFaceStencilFailStencilOp;
	_STENCIL_OPERATION 	mFrontFaceDepthFailStencilOp;
	_STENCIL_OPERATION 	mFrontFacePassStencilOp;
	_ubool				mEnableBackFaceStencil;
	_COMPARE_FUNCTION	mBackFaceStencilTest;
	_STENCIL_OPERATION 	mBackFaceStencilFailStencilOp;
	_STENCIL_OPERATION 	mBackFaceDepthFailStencilOp;
	_STENCIL_OPERATION 	mBackFacePassStencilOp;
	_dword 				mStencilReadMask;
	_dword 				mStencilWriteMask;
	_dword 				mStencilRef;

	StencilStateInitializerRHI( )
	{
		mEnableFrontFaceStencil			= _false;
		mFrontFaceStencilTest			= _CF_ALWAYS;
		mFrontFaceStencilFailStencilOp	= _SO_KEEP;
		mFrontFaceDepthFailStencilOp	= _SO_KEEP;
		mFrontFacePassStencilOp			= _SO_KEEP;
		mEnableBackFaceStencil			= _false;
		mBackFaceStencilTest			= _CF_ALWAYS;
		mBackFaceStencilFailStencilOp	= _SO_KEEP;
		mBackFaceDepthFailStencilOp		= _SO_KEEP;
		mBackFacePassStencilOp			= _SO_KEEP;
		mStencilReadMask				= 0xFFFFFFFF;
		mStencilWriteMask				= 0xFFFFFFFF;
		mStencilRef						= 0;
	}
};

//!	The blend state initializer
struct BlendStateInitializerRHI
{
	_ubool			mEnableBlend;
	_BLEND_FACTOR	mColorSourceBlendFactor;
	_BLEND_FACTOR	mColorDestBlendFactor;
	_BLEND_FACTOR	mAlphaSourceBlendFactor;
	_BLEND_FACTOR	mAlphaDestBlendFactor;

	BlendStateInitializerRHI( ) 
	{
		mEnableBlend			= _false;

		mColorSourceBlendFactor	= _BF_ONE;
		mColorDestBlendFactor	= _BF_ZERO;

		mAlphaSourceBlendFactor	= _BF_ONE;
		mAlphaDestBlendFactor	= _BF_ZERO;
	}
};

//!	The vertex element info
struct VertexElementRHI
{
	_dword					mOffset;
	_VERTEX_ELEMENT_TYPE	mType;
	_VERTEX_ELEMENT_USAGE	mUsage;
	_dword					mUsageIndex;

	//!	Check whether it's valid.
	_ubool IsValid( ) const
	{
		if ( mType == _VET_NONE || mType >= _VET_MAXNUMBER )
			return _false;

		if ( mUsage == _VEU_NONE || mUsage >= _VEU_MAXNUMBER )
			return _false;

		if ( mUsageIndex == -1 )
			return _false;

		return _true;
	}

	VertexElementRHI( _dword offset = -1, _VERTEX_ELEMENT_TYPE type = _VET_NONE, _VERTEX_ELEMENT_USAGE usage = _VEU_NONE, _dword usage_index = 0 )
	{
		mOffset		= offset;
		mType		= type;
		mUsage		= usage;
		mUsageIndex	= usage_index;
	}
};
typedef Array< VertexElementRHI > VertexElementRHIArray;

//!	The uniform buffer data
struct UniformBufferRHI
{
	//!	The uniform buffer data type
	_UNIFORM_BUFFER_DATA_TYPE	mType;
	//!	The uniform buffer location, -1 indicates invalid
	_dword						mLocation;
	//!	The uniform buffer size
	_dword						mSize;
	//!	The uniform buffer name
	AStringObj					mName;

	//!	Use the name as key
	operator const AStringObj&( ) const
		{ return mName; }

	UniformBufferRHI( )
	{
		mType		= _UBDT_UNKNOWN;
		mLocation	= -1;
		mSize		= 0;
	}
	UniformBufferRHI( _UNIFORM_BUFFER_DATA_TYPE type, _dword location, _dword size, const AStringObj& name )
	{
		mType		= type;
		mLocation	= location;
		mSize		= size;
		mName		= name;
	}
};
typedef Array< UniformBufferRHI > UniformBufferRHIArray;

//!	The RHI statistics
struct RenderStatsRHI
{
	//!	The render API function call info
	struct APICallInfo
	{
		//!	The API call number
		_dword	mAPICallNumber;

		//!	The scissor state changed number 
		_dword	mScissorStateChangedNumber;
		//!	The scissor rect update number 
		_dword	mScissorRectUpdateNumber;

		//!	The draw primitive call number 
		_dword	mDPNumber;
		//!	The uniform buffer update number 
		_dword	mUBOUpdateNumber;

		//!	The vertex buffer flush call number 
		_dword	mVBFlushNumber;
		//!	The index buffer flush call number 
		_dword	mIBFlushNumber;
	};

	//!	The frame number per-second
	_float		mFPS;
	//!	The average frame number per-second
	_float		mAvgFPS;

	//!	The total compressed 2D texture number
	_dword		mTotalCompressedTexture2DNumber;
	//!	The total 2D texture number
	_dword		mTotalTexture2DNumber;
	//!	The total 2D texture memory size
	_dword		mTotalTexture2DMemorySize;

	//!	The total cube texture number
	_dword		mTotalTextureCubeNumber;
	//!	The total cube texture memory size
	_dword		mTotalTextureCubeMemorySize;

	//!	The total index buffer number
	_dword		mTotalIndexBufferNumber;
	//!	The total index buffer memory size
	_dword		mTotalIndexBufferMemorySize;

	//!	The total vertex buffer number
	_dword		mTotalVertexBufferNumber;
	//!	The total vertex buffer memory size
	_dword		mTotalVertexBufferMemorySize;

	//!	The total memory size
	_dword		mTotalMemorySize;

	//!	The vertices number in one render cycle
	_dword		mVerticesNumber;
	//!	The render API function call info in one render cycle
	APICallInfo	mAPICallInfo;

	RenderStatsRHI( ) 
	{
		mFPS							= 0.0f;
		mAvgFPS							= 0.0f;

		mTotalCompressedTexture2DNumber	= 0;
		mTotalTexture2DNumber			= 0;
		mTotalTexture2DMemorySize		= 0;

		mTotalTextureCubeNumber			= 0;
		mTotalTextureCubeMemorySize		= 0;

		mTotalIndexBufferNumber			= 0;
		mTotalIndexBufferMemorySize		= 0;

		mTotalVertexBufferNumber		= 0;
		mTotalVertexBufferMemorySize	= 0;

		mTotalMemorySize				= 0;

		ClearDrawingStats( );
	}

	//!	Clear API call info.
	_void ClearAPICallInfo( )
	{
		mAPICallInfo.mAPICallNumber				= 0;
		mAPICallInfo.mScissorStateChangedNumber	= 0;
		mAPICallInfo.mScissorRectUpdateNumber	= 0;
		mAPICallInfo.mDPNumber					= 0;
		mAPICallInfo.mUBOUpdateNumber			= 0;
		mAPICallInfo.mVBFlushNumber				= 0;
		mAPICallInfo.mIBFlushNumber				= 0;
	}
	//!	Add API call info.
	_void AddAPICallInfo( const RenderStatsRHI::APICallInfo& info )
	{
		mAPICallInfo.mAPICallNumber				+= info.mAPICallNumber;
		mAPICallInfo.mScissorStateChangedNumber	+= info.mScissorStateChangedNumber;
		mAPICallInfo.mScissorRectUpdateNumber	+= info.mScissorRectUpdateNumber;
		mAPICallInfo.mDPNumber					+= info.mDPNumber;
		mAPICallInfo.mUBOUpdateNumber			+= info.mUBOUpdateNumber;
		mAPICallInfo.mVBFlushNumber				+= info.mVBFlushNumber;
		mAPICallInfo.mIBFlushNumber				+= info.mIBFlushNumber;
	}

	//!	Clear drawing stats.
	_void ClearDrawingStats( )
	{
		mVerticesNumber	= 0;

		ClearAPICallInfo( );
	}
};

/// Field Of View (FOV) in tangent of the angle units.
/// As an example, for a standard 90 degree vertical FOV, we would
/// have: { UpTan = tan(90 degrees / 2), DownTan = tan(90 degrees / 2) }.
struct VRFovPortRHI
{
	_float mUpTan;    ///< The tangent of the angle between the viewing vector and the top edge of the field of view.
	_float mDownTan;  ///< The tangent of the angle between the viewing vector and the bottom edge of the field of view.
	_float mLeftTan;  ///< The tangent of the angle between the viewing vector and the left edge of the field of view.
	_float mRightTan; ///< The tangent of the angle between the viewing vector and the right edge of the field of view.

	VRFovPortRHI( )
	{
		mUpTan		= 0.0f;
		mDownTan	= 0.0f;
		mLeftTan	= 0.0f;
		mRightTan	= 0.0f;
	}
};

//!	The graphic VR eye info.
struct VREyeRHI
{
	//!	The eye height
	_float			mHeight;
	//! The recommended optical FOV.
	VRFovPortRHI	mDefaultEyeFov;
	//!	The transform
	Transform3D		mTransform;

	VREyeRHI( )
	{
		mHeight		= 0.0f;
		mTransform	= Transform3D::cZero;
	}
};

}