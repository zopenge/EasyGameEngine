//! @file     GLSLProgramCache.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLSLProgramCache Implementation
//----------------------------------------------------------------------------

GLSLProgramCache::GLSLProgramCache( )
{

}

GLSLProgramCache::~GLSLProgramCache( )
{

}

_void GLSLProgramCache::Clear( )
{
	mCaches.Clear( );
}

GLSLProgram* GLSLProgramCache::GetGLSLProgram( GLVertexShader* vertexshader, GLPixelShader* pixelshader )
{
	// Build the GLSL program key
	_qword key = ((_qword)( vertexshader->GetResource( ) ) << 32 ) | ((_qword) pixelshader->GetResource( ));
//	_qword key = ((_qword)( vertexshader->GetCode( ).GetCRCValue( ) ) << 32 ) | ((_qword) pixelshader->GetCode( ).GetCRCValue( ));

	// Search for existing GLSL program object
	GLSLProgramData* old_cache = mCaches.Search( key );
	if ( old_cache != _null )
		return old_cache->mGLSLProgram;

	// Create GLSL program object with render target and depth stencil target
	GLSLProgramData& cache	= mCaches[ key ];
	cache.mVertexShader 	= vertexshader;
	cache.mPixelShader		= pixelshader;
	cache.mGLSLProgram.SetPtr( new GLSLProgram( ) );
	if ( cache.mGLSLProgram->Link( vertexshader, pixelshader ) == _false )
		return _null;

	return cache.mGLSLProgram;
}

_void GLSLProgramCache::ReleaseGLSLProgram( GLSLProgram* program )
{
	for ( GLSLProgramDataMap::Iterator it = mCaches.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		GLSLProgramData& cache = ( (GLSLProgramDataMap::PairType&) it ).mObject2;

		if ( cache.mGLSLProgram == program )
		{
			if ( cache.mGLSLProgram->GetRefCount( ) == 1 )
				mCaches.Remove( it );
			else
				cache.mGLSLProgram->Release( );

			break;
		}
	}
}