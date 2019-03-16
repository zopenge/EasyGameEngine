//! @file     GLEnums.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// The GL enumerations
//----------------------------------------------------------------------------

//!	The OpenGL attribute location index of VAO 
enum _GL_ATTRIBUTE_INDEX
{
	_GL_ATTRI_POSITION,			//!	"cPosition" constant name in shader
	_GL_ATTRI_COLOR0,			//!	"cColor0" constant name in shader
	_GL_ATTRI_COLOR1,			//!	"cColor1" constant name in shader
	_GL_ATTRI_NORMAL,			//!	"cNormal" constant name in shader
	_GL_ATTRI_BLEND_WEIGHT,		//!	"cBlendWeight" constant name in shader
	_GL_ATTRI_BLEND_INDICES,	//!	"cBlendIndices" constant name in shader
	_GL_ATTRI_TEXCOORD0,		//!	"cTexCoords0" constant name in shader
	_GL_ATTRI_TEXCOORD1,		//!	"cTexCoords1" constant name in shader
	_GL_ATTRI_TANGENT,			//!	"cTangent" constant name in shader

	_GL_ATTRI_MAXNUMBER,
};

}