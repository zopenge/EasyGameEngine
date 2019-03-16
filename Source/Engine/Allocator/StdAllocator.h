//! @file     StdAllocator.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// StdAllocator
//----------------------------------------------------------------------------

class StdAllocator : public TAllocator< INTERFACE_OBJECT_IMPL( IAllocator ) >
{
private:
	typedef TAllocator< INTERFACE_OBJECT_IMPL( IAllocator ) > BaseClass;

public:
	StdAllocator( _dword arrange_size );
	virtual ~StdAllocator( );

// IAllocator Interface
public:
	virtual _void	Cleanup( ) override;

	virtual _ubool	CanAlloc( _dword size ) const override;

	virtual _byte*	Alloc( _dword size ) override;
	virtual _byte*	ReAlloc( _void* pointer, _dword size ) override;
	virtual _void	Free( _void* pointer ) override;
	virtual _void	FreeAll( ) override;
};

}