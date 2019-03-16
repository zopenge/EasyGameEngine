//! @file     GLSLProgramCache.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GLSLProgramCache
//----------------------------------------------------------------------------

class GLSLProgramCache
{
	SINGLETON( GLSLProgramCache )

private:
	typedef RefPtr< GLSLProgram > GLSLProgramRef;

private:
	//!	The GLSL program data
	struct GLSLProgramData
	{
		GLSLProgramRef	mGLSLProgram;
		GLVertexShader*	mVertexShader;
		GLPixelShader*	mPixelShader;

		GLSLProgramData( GLVertexShader* vertexshader = _null, GLPixelShader* pixelshader = _null )
			: mVertexShader( vertexshader ), mPixelShader( pixelshader ) {}
	};
	typedef Map< GLSLProgramData, _qword > GLSLProgramDataMap;

private:
	//!	The cache data
	GLSLProgramDataMap	mCaches;

public:
	//!	Clear all cache.
	//!	@param		none.
	//!	@return		none.
	_void Clear( );

	//!	Get the GLSL program.
	//!	@param		vertexshader	The vertex shader.
	//!	@param		pixelshader		The pixel shader.
	//!	@return		The GLSL program object.
	GLSLProgram* GetGLSLProgram( GLVertexShader* vertexshader, GLPixelShader* pixelshader );
	//!	Release GLSL program.
	//!	@param		program			The GLSL program.
	//!	@return		none.
	_void ReleaseGLSLProgram( GLSLProgram* program );
};

//----------------------------------------------------------------------------
// GLSLProgramCache Implementation
//----------------------------------------------------------------------------

}