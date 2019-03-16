//! @file     GLInfo.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{
	
//----------------------------------------------------------------------------
// GLInfo
//----------------------------------------------------------------------------

class GLInfo
{
	SINGLETON( GLInfo )

private:
	//!	The GPU shader info
	GPUShaderInfoRHI	mShaderInfo;
	//!	The GPU texture info
	GPUTextureInfoRHI	mTextureInfo;

private:
	//!	Initialize shader info.
	_void InitShaderInfo( );
	//!	Initialize texture info.
	_void InitTextureInfo( );

public:
	EGE_GETR_ACCESSOR_CONST( GPUShaderInfoRHI, ShaderInfo )
	EGE_GETR_ACCESSOR_CONST( GPUTextureInfoRHI, TextureInfo )

public:
	//!	Initialize.
	_void Initialize( );
};

//----------------------------------------------------------------------------
// GLInfo Implementation
//----------------------------------------------------------------------------

}