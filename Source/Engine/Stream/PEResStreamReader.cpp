//! @file     PEResStreamReader.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// PEResStreamReader Implementation
//----------------------------------------------------------------------------

PEResStreamReader::PEResStreamReader( )
{
	mResource	= _null;
	mBuffer		= _null;
	mSize		= 0;
}

PEResStreamReader::~PEResStreamReader( )
{
	if ( mResource != _null )
	{
		Platform::FreeResource( _null, mResource );
		mResource = _null;
	}
}

_ubool PEResStreamReader::Initialize( _handle resource, _dword size )
{
	mResource	= resource;
	mSize		= size;

	// Lock resource
	mBuffer = (_byte*) Platform::LockResource( mResource );
	if ( mBuffer == _null )
		return _false;

	// Create stream reader
	mStreamReader = GetInterfaceFactory( )->CreateMemStreamReader( mBuffer, mSize, _STREAM_SHARE_MODE_READ_ONLY );
	if ( mStreamReader.IsNull( ) )
		return _false;

	return _true;
}

_STREAM_TYPE PEResStreamReader::GetType( ) const
{
	return mStreamReader->GetType( );
}

_STREAM_SHARE_MODE PEResStreamReader::GetShareMode( ) const
{
	return mStreamReader->GetShareMode( );
}

_dword PEResStreamReader::GetSize( ) const
{
	return mStreamReader->GetSize( );
}

_dword PEResStreamReader::GetOffset( ) const
{
	return mStreamReader->GetOffset( );
}

const _byte* PEResStreamReader::GetBuffer( )
{
	return mStreamReader->GetBuffer( );
}

_dword PEResStreamReader::Seek( _SEEK flag, _int distance )
{
	return mStreamReader->Seek( flag, distance );
}

_dword PEResStreamReader::SeekByArrangedValueFromBegin( _dword value )
{
	return mStreamReader->SeekByArrangedValueFromBegin( value );
}

_void PEResStreamReader::SetEndian( _ENDIAN endian )
{
	mStreamReader->SetEndian( endian );
}

_ENDIAN PEResStreamReader::GetEndian( ) const
{
	return mStreamReader->GetEndian( );
}

IObject* PEResStreamReader::CloneTo( _ubool standalone ) const
{
	_STREAM_SHARE_MODE share_mode;
	if ( standalone )
		share_mode = _STREAM_SHARE_MODE_NONE;
	else
		share_mode = _STREAM_SHARE_MODE_READ_ONLY;

	PEResStreamReader* stream_reader = new PEResStreamReader( );

	// Create file stream reader
	stream_reader->mStreamReader = GetInterfaceFactory( )->CreateMemStreamReader( mBuffer, mSize, share_mode );
	if ( stream_reader->mStreamReader.IsNull( ) )
		{ EGE_RELEASE( stream_reader ); return _null; }

	return stream_reader;
}

_dword PEResStreamReader::GetRemainBytes( ) const
{
	return mStreamReader->GetRemainBytes( );
}

_ubool PEResStreamReader::ReachEnd( ) const
{
	return mStreamReader->ReachEnd( );
}

_dword PEResStreamReader::PeekBuffer( _void* buffer, _dword size )
{
	return mStreamReader->PeekBuffer( buffer, size );
}

_dword PEResStreamReader::PeekBuffer( _void* buffer, _dword size, _dword offset )
{
	return mStreamReader->PeekBuffer( buffer, size, offset );
}

_dword PEResStreamReader::ReadBuffer( _void* buffer, _dword size )
{
	return mStreamReader->ReadBuffer( buffer, size );
}

_dword PEResStreamReader::ReadTiny( _tiny& data )
{
	return mStreamReader->ReadTiny( data );
}

_dword PEResStreamReader::ReadShort( _short& data )
{
	return mStreamReader->ReadShort( data );
}

_dword PEResStreamReader::ReadLong( _int& data )
{
	return mStreamReader->ReadLong( data );
}

_dword PEResStreamReader::ReadByte( _byte& data )
{
	return mStreamReader->ReadByte( data );
}

_dword PEResStreamReader::ReadWord( _word& data )
{
	return mStreamReader->ReadWord( data );
}

_dword PEResStreamReader::ReadDword( _dword& data )
{
	return mStreamReader->ReadDword( data );
}

_dword PEResStreamReader::ReadQword( _qword& data )
{
	return mStreamReader->ReadQword( data );
}

_dword PEResStreamReader::ReadFloat( _float& data )
{
	return mStreamReader->ReadFloat( data );
}

_dword PEResStreamReader::ReadDouble( _double& data )
{
	return mStreamReader->ReadDouble( data );
}

_dword PEResStreamReader::ReadString( AString& string )
{
	return mStreamReader->ReadString( string );
}

_dword PEResStreamReader::ReadString( UString& string )
{
	return mStreamReader->ReadString( string );
}

_dword PEResStreamReader::ReadString( WString& string )
{
	return mStreamReader->ReadString( string );
}