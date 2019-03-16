//! @file     TFileStream.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TFileStream
//----------------------------------------------------------------------------

template< typename Type >
class TFileStream : public Type
{
protected:
	//!	The file handle
	File	mFile;

	//!	The file name
	WString	mFileName;

protected:
	TFileStream( );
	virtual ~TFileStream( );

// IObject Interface
public:
	virtual _void			Uninitialize( ) override;

// IStream Interface
public:
	virtual _STREAM_TYPE	GetType( ) const override;

	virtual _dword 			GetOffset( ) const override;

	virtual _dword 			Seek( _SEEK flag, _int distance ) override;
	virtual _dword			SeekByArrangedValueFromBegin( _dword value ) override;

// IFileStream Interface
public:
	virtual WStringPtr		GetFileName( ) const override;
};

//----------------------------------------------------------------------------
// TFileStream Implementation
//----------------------------------------------------------------------------

template< typename Type >
TFileStream< Type >::TFileStream( )
{
}

template< typename Type >
TFileStream< Type >::~TFileStream( )
{
}

template< typename Type >
_void TFileStream< Type >::Uninitialize( )
{
	mFile.Close( );
}

template< typename Type >
_STREAM_TYPE TFileStream< Type >::GetType( ) const
{
	return _STREAM_TYPE_FILE;
}

template< typename Type >
_dword TFileStream< Type >::GetOffset( ) const
{ 
	return mFile.GetOffset( );
}

template< typename Type >
_dword TFileStream< Type >::Seek( _SEEK flag, _int distance )
{
	return mFile.Seek( flag, distance );
}

template< typename Type >
_dword TFileStream< Type >::SeekByArrangedValueFromBegin( _dword value )
{
	_dword offset = GetOffset( );

	if ( offset % value != 0 )
		Seek( _SEEK_BEGIN, (_int)Math::UpperArrange( offset, value ) );

	return GetOffset( );
}

template< typename Type >
WStringPtr TFileStream< Type >::GetFileName( ) const
{
	return mFileName;
}

}