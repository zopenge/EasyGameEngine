//! @file     GLConstantBuffer.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

class GLBoundShader;

//----------------------------------------------------------------------------
// GLConstantBuffer
//----------------------------------------------------------------------------

class GLConstantBuffer
{
private:
	//!	The chunk of constant buffer
	struct Chunk
	{
		_dword	mOffset;
		_dword	mSize;
		_byte	mBuffer[64];

		Chunk( _dword offset = -1, _dword size = 0 )
		{
			mOffset	= offset;
			mSize	= size;
		}
	};
	typedef FixedArray< Chunk, _UNIFORM_BUFFER_MAXNUMBER > ChunkArray;

private:
	//!	The chunks
	ChunkArray	mChunks;

public:
	GLConstantBuffer( );
	~GLConstantBuffer( );

public:
	//! Update the buffer.
	//!	@param		slot		The buffer slot.
	//!	@param		offset		The buffer offset.
	//!	@param		size		The buffer size.
	//!	@param		buffer		The buffer data.
	//!	@return		none.
	_void Update( _dword slot, _dword offset, _dword size, const _byte* buffer );

	//!	Update the uniform buffers of bound shader.
	//!	@param		shader		The bound shader.
	//!	@return		none.
	_void UpdateUniforms( GLBoundShader* shader );
};

}