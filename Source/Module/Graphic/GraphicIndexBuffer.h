//! @file     GraphicIndexBuffer.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicIndexBuffer
//----------------------------------------------------------------------------

class GraphicIndexBuffer : public TObject< IGraphicIndexBuffer >
{
private:
	//!	The index buffer
	IndexBufferRHIRef	mIndexBuffer;

public:
	GraphicIndexBuffer( IndexBufferRHI* ib );
	virtual ~GraphicIndexBuffer( );

// IGraphicBuffer Interface
public:
	virtual _dword			GetStride( ) const override;
	virtual _dword			GetSize( ) const override;

	virtual _void			Write( _dword offset, _dword size, const _byte* buffer ) override;
	virtual _void			Flush( ) override;

	virtual _byte*			LockBufferData( _dword offset, _dword size ) override;
	virtual _void			UnlockBufferData( ) override;
	virtual const _byte*	GetBufferData( ) override;
};

//----------------------------------------------------------------------------
// GraphicIndexBuffer Implementation
//----------------------------------------------------------------------------

}