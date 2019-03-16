//! @file     TGeometryChunk.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TGeometryChunk
//----------------------------------------------------------------------------

template< typename Type >
class TGeometryChunk : public TSerializable< Type >
{
protected:

protected:
	//!	The version
	Version					mVersion;

	//!	The geometry chunk type
	_GEOMETRY_CHUNK_TYPE	mChunkType;
	//!	The geometry chunk name
	WString					mChunkName;

protected:
	TGeometryChunk( _GEOMETRY_CHUNK_TYPE type, const Version& version );
	virtual ~TGeometryChunk( );

// IGeometryBaseChunk Interface
public:
	virtual _GEOMETRY_CHUNK_TYPE	GetChunkType( ) const override;
	virtual WStringPtr				GetChunkName( ) const override;
};

//----------------------------------------------------------------------------
// TGeometryChunk Implementation
//----------------------------------------------------------------------------

template< typename Type >
TGeometryChunk< Type >::TGeometryChunk( _GEOMETRY_CHUNK_TYPE type, const Version& version )
{
	mChunkType	= type;
	mVersion	= version;
}

template< typename Type >
TGeometryChunk< Type >::~TGeometryChunk( )
{

}

template< typename Type >
_GEOMETRY_CHUNK_TYPE TGeometryChunk< Type >::GetChunkType( ) const
{
	return mChunkType;
}

template< typename Type >
WStringPtr TGeometryChunk< Type >::GetChunkName( ) const
{
	return mChunkName;
}

}