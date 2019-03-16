//! @file     MemStreamReader.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// MemStreamReader Implementation
//----------------------------------------------------------------------------

MemStreamReader::MemStreamReader( const _byte* buffer, _dword size, _STREAM_SHARE_MODE share_mode ) 
	: BaseClass( (_byte*) buffer, size, share_mode )
{
}

MemStreamReader::~MemStreamReader( )
{
}

IObject* MemStreamReader::CloneTo( _ubool standalone ) const
{
	if ( standalone )
	{
		return new MemStreamReader( mBuffer, mSize, _STREAM_SHARE_MODE_NONE );
	}
	else
	{
		return new MemStreamReader( mBuffer, mSize, _STREAM_SHARE_MODE_READ_ONLY );
	}
}

_dword MemStreamReader::GetRemainBytes( ) const
{ 
	return mSize - ( mPointer - mBuffer ); 
}

const _byte* MemStreamReader::GetBuffer( )
{
	return mBuffer;
}

_ubool MemStreamReader::ReachEnd( ) const
{ 
	return (_dword) ( mPointer - mBuffer ) == mSize; 
}

_dword MemStreamReader::PeekBuffer( _void* buffer, _dword size )
{
	if ( buffer == _null )
		return 0;

	_dword read_size = Math::Min< _dword >( GetRemainBytes( ), size );
	EGE_MEM_CPY( buffer, mPointer, read_size );

	return read_size;
}

_dword MemStreamReader::PeekBuffer( _void* buffer, _dword size, _dword offset )
{
	if ( buffer == _null )
		return 0;

	_dword read_size = Math::Min< _dword >( size, mSize - offset );
	EGE_MEM_CPY( buffer, mBuffer + offset, read_size );

	return read_size;
}

_dword MemStreamReader::ReadBuffer( _void* buffer, _dword size )
{
    _dword remainbytes = GetRemainBytes( );
    if ( remainbytes < size )
        size = remainbytes;

	EGE_MEM_CPY( buffer, mPointer, size );
	mPointer += size;

	return size;
}

_dword MemStreamReader::ReadTiny( _tiny& data )
{
	return ReadValue( data );
}

_dword MemStreamReader::ReadShort( _short& data )
{
	_dword size = ReadValue( data );
	if ( size == 0 )
		return 0;

	if ( GetEndian( ) != Platform::GetEndianType( ) )
		data = Math::BSwap16( data );

	return size;
}

_dword MemStreamReader::ReadLong( _int& data )
{
	_dword size = ReadValue( data );
	if ( size == 0 )
		return 0;

	if ( GetEndian( ) != Platform::GetEndianType( ) )
		data = (_int)Math::BSwap32( data );

	return size;
}

_dword MemStreamReader::ReadByte( _byte& data )
{
	return ReadValue( data );
}

_dword MemStreamReader::ReadWord( _word& data )
{
	_dword size = ReadValue( data );
	if ( size == 0 )
		return 0;

	if ( GetEndian( ) != Platform::GetEndianType( ) )
		data = Math::BSwap16( data );

	return size;
}

_dword MemStreamReader::ReadDword( _dword& data )
{
	_dword size = ReadValue( data );
	if ( size == 0 )
		return 0;

	if ( GetEndian( ) != Platform::GetEndianType( ) )
		data = Math::BSwap32( data );

	return size;
}

_dword MemStreamReader::ReadQword( _qword& data )
{
	_dword size = ReadValue( data );
	if ( size == 0 )
		return 0;

	if ( GetEndian( ) != Platform::GetEndianType( ) )
		Math::BSwap64( data );

	return size;
}

_dword MemStreamReader::ReadFloat( _float& data )
{
	_dword size = ReadValue( data );
	if ( size == 0 )
		return 0;

	if ( GetEndian( ) != Platform::GetEndianType( ) )
		Math::BSwapFloat( data );

	return size;
}

_dword MemStreamReader::ReadDouble( _double& data )
{
	_dword size = ReadValue( data );
	if ( size == 0 )
		return 0;

	if ( GetEndian( ) != Platform::GetEndianType( ) )
		Math::BSwapDouble( data );

	return size;
}