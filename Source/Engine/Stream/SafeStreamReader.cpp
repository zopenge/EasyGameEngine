//! @file     SafeStreamReader.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// SafeStreamReader Implementation
//----------------------------------------------------------------------------

SafeStreamReader::SafeStreamReader( IStreamReader* stream_reader )
{
	mStreamReader = stream_reader;
}

SafeStreamReader::~SafeStreamReader( )
{
}

IObject* SafeStreamReader::CloneTo( _ubool standalone ) const
{
	IStreamReaderRef stream_reader = mStreamReader->CloneToPassRef< IStreamReader >( standalone );
	if ( stream_reader.IsNull( ) )
		return _null;

	return new SafeStreamReader( stream_reader );
}

_STREAM_TYPE SafeStreamReader::GetType( ) const
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->GetType( );
}

_STREAM_SHARE_MODE SafeStreamReader::GetShareMode( ) const
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->GetShareMode( );
}

_dword SafeStreamReader::GetSize( ) const
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->GetSize( );
}

_dword SafeStreamReader::GetOffset( ) const
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->GetOffset( );
}

_dword SafeStreamReader::Seek( _SEEK flag, _int distance )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->Seek( flag, distance );
}

_dword SafeStreamReader::SeekByArrangedValueFromBegin( _dword value )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->SeekByArrangedValueFromBegin( value );
}

_void SafeStreamReader::SetEndian( _ENDIAN endian )
{
	LockOwner lock_owner( mLocker );

	mStreamReader->SetEndian( endian );
}

_ENDIAN SafeStreamReader::GetEndian( ) const
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->GetEndian( );
}

_dword SafeStreamReader::GetRemainBytes( ) const
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->GetRemainBytes( );
}

const _byte* SafeStreamReader::GetBuffer( )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->GetBuffer( );
}

_ubool SafeStreamReader::ReachEnd( ) const
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->ReachEnd( );
}

_dword SafeStreamReader::PeekBuffer( _void* buffer, _dword size )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->PeekBuffer( buffer, size );
}

_dword SafeStreamReader::PeekBuffer( _void* buffer, _dword size, _dword offset )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->PeekBuffer( buffer, size, offset );
}

_dword SafeStreamReader::ReadBuffer( _void* buffer, _dword size )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->ReadBuffer( buffer, size );
}

_dword SafeStreamReader::ReadTiny( _tiny& data )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->ReadTiny( data );
}

_dword SafeStreamReader::ReadShort( _short& data )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->ReadShort( data );
}

_dword SafeStreamReader::ReadLong( _int& data )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->ReadLong( data );
}

_dword SafeStreamReader::ReadByte( _byte& data )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->ReadByte( data );
}

_dword SafeStreamReader::ReadWord( _word& data )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->ReadWord( data );
}

_dword SafeStreamReader::ReadDword( _dword& data )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->ReadDword( data );
}

_dword SafeStreamReader::ReadQword( _qword& data )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->ReadQword( data );
}

_dword SafeStreamReader::ReadFloat( _float& data )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->ReadFloat( data );
}

_dword SafeStreamReader::ReadDouble( _double& data )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->ReadDouble( data );
}

_dword SafeStreamReader::ReadString( AString& string )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->ReadString( string );
}

_dword SafeStreamReader::ReadString( UString& string )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->ReadString( string );
}

_dword SafeStreamReader::ReadString( WString& string )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->ReadString( string );
}

_dword SafeStreamReader::ReadLine( AString& string )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->ReadLine( string );
}

_dword SafeStreamReader::ReadLine( UString& string )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->ReadLine( string );
}

_dword SafeStreamReader::ReadLine( WString& string )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->ReadLine( string );
}

_dword SafeStreamReader::ReadLine( _ENCODING encode_type, AString& string )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->ReadLine( encode_type, string );
}

_dword SafeStreamReader::ReadLine( _ENCODING encode_type, UString& string )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->ReadLine( encode_type, string );
}

_dword SafeStreamReader::ReadLine( _ENCODING encode_type, WString& string )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->ReadLine( encode_type, string );
}

_dword SafeStreamReader::ReadEncodeType( _ENCODING& encode_type )
{
	LockOwner lock_owner( mLocker );

	return mStreamReader->ReadEncodeType( encode_type );
}