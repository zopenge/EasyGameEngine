//! @file     BitStreamReader.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// BitStreamReader Implementation
//----------------------------------------------------------------------------

BitStreamReader::BitStreamReader( const _byte* buffer, _dword size, _STREAM_SHARE_MODE share_mode ) 
	: BaseClass( (_byte*) buffer, size, share_mode )
{
}

BitStreamReader::~BitStreamReader( )
{
}

IObject* BitStreamReader::CloneTo( _ubool standalone ) const
{
	_STREAM_SHARE_MODE share_mode;
	if ( standalone )
		share_mode = _STREAM_SHARE_MODE_NONE;
	else
		share_mode = _STREAM_SHARE_MODE_READ_ONLY;

	// We always use none-sharing mode to clone
	return new BitStreamReader( mBuffer, mSize, share_mode );
}

_dword BitStreamReader::GetRemainBytes( ) const
{ 
	return mSize - ( mPointer - mBuffer ); 
}

_ubool BitStreamReader::ReachEnd( ) const
{ 
	return (_dword) ( mPointer - mBuffer ) == mSize; 
}

const _byte* BitStreamReader::GetBuffer( )
{
	return mBuffer;
}

_dword BitStreamReader::PeekBuffer( _void* buffer, _dword size )
{
	if ( buffer == _null )
		return 0;

	_dword read_size = Math::Min< _dword >( GetRemainBytes( ), size );
	EGE_MEM_CPY( buffer, mPointer, read_size );

	return read_size;
}

_dword BitStreamReader::PeekBuffer( _void* buffer, _dword size, _dword offset )
{
	if ( buffer == _null )
		return 0;

	_dword read_size = Math::Min< _dword >( size, mSize - offset );
	EGE_MEM_CPY( buffer, mBuffer + offset, read_size );

	return read_size;
}

_dword BitStreamReader::ReadBuffer( _void* buffer, _dword size )
{
	if ( ReadBitsStream( buffer, size * 8 ) == _false )
		return 0;

	return size;
}

_dword BitStreamReader::ReadTiny( _tiny& data )
{
	if ( ReadBitsStream( data, 8 ) == _false )
		return 0;

	return sizeof( _tiny );
}

_dword BitStreamReader::ReadShort( _short& data )
{
	if ( ReadBitsStream( data, 16 ) == _false )
		return 0;

	return sizeof( _short );
}

_dword BitStreamReader::ReadLong( _int& data )
{
	if ( ReadBitsStream( data, 32 ) == _false )
		return 0;

	return sizeof( _int );
}

_dword BitStreamReader::ReadByte( _byte& data )
{
	if ( ReadBitsStream( data, 8 ) == _false )
		return 0;

	return sizeof( _byte );
}

_dword BitStreamReader::ReadWord( _word& data )
{
	if ( ReadBitsStream( data, 16 ) == _false )
		return 0;

	return sizeof( _word );
}

_dword BitStreamReader::ReadDword( _dword& data )
{
	if ( ReadBitsStream( data, 32 ) == _false )
		return 0;

	return sizeof( _dword );
}

_dword BitStreamReader::ReadQword( _qword& data )
{
	if ( ReadBitsStream( data, 64 ) == _false )
		return 0;

	return sizeof( _qword );
}

_dword BitStreamReader::ReadFloat( _float& data )
{
	if ( ReadBitsStream( data, 32 ) == _false )
		return 0;

	return sizeof( _float );
}

_dword BitStreamReader::ReadDouble( _double& data )
{
	if ( ReadBitsStream( data ) == _false )
		return 0;

	return sizeof( _double );
}

_ubool BitStreamReader::ReadBitsStream( _void* buffer, _dword bitsnumber )
{
	if ( mBitOffset == 0 && ( bitsnumber % 8 == 0 ) )
	{
		if ( ReadBuffer( buffer, bitsnumber / 8 ) == 0 )
			return _false;
	}
	else
	{
		if ( buffer == _null || bitsnumber == 0 )
			return _false;

		// Get the buffer pointer
		_dword* pointer = (_dword*) buffer;

		// Read the buffer
		while ( bitsnumber > 0 )
		{
			_dword readbitsnumber = Math::Min< _dword >( 32, bitsnumber );
			if ( ReadBitsStream( *pointer, readbitsnumber ) == _false )
				return _false;

			// Update the buffer pointer
			pointer ++;

			// Update the bits number
			bitsnumber -= readbitsnumber;
		}
	}

	return _true;
}

_ubool BitStreamReader::ReadBitsStream( _tiny& value, _dword bitsnumber )
{
	_dword valuetemp = 0;
	if ( ReadBitsStream( valuetemp, bitsnumber ) == _false )
		return _false;

	value = (_tiny) valuetemp;

	return _true;
}

_ubool BitStreamReader::ReadBitsStream( _byte& value, _dword bitsnumber )
{
	_dword valuetemp = 0;
	if ( ReadBitsStream( valuetemp, bitsnumber ) == _false )
		return _false;

	value = (_byte) valuetemp;

	return _true;
}

_ubool BitStreamReader::ReadBitsStream( _word& value, _dword bitsnumber )
{
	_dword valuetemp = 0;
	if ( ReadBitsStream( valuetemp, bitsnumber ) == _false )
		return _false;

	value = (_word) valuetemp;

	return _true;
}

_ubool BitStreamReader::ReadBitsStream( _short& value, _dword bitsnumber )
{
	_int valuetemp = 0;
	if ( ReadBitsStream( valuetemp, bitsnumber ) == _false )
		return _false;

	value = (_short) valuetemp;

	return _true;
}

_ubool BitStreamReader::ReadBitsStream( _int& value, _dword bitsnumber )
{
	_dword valuetemp = 0;
	if ( ReadBitsStream( valuetemp, bitsnumber ) == _false )
		return _false;

	// Check the negative flag
	if ( valuetemp >> ( bitsnumber - 1 ) )
	{
		valuetemp &= ~( 1 << ( bitsnumber - 1 ) );

		value = - (_int) valuetemp;
	}
	else
	{
		value = (_int) valuetemp;
	}

	return _true;
}

_ubool BitStreamReader::ReadBitsStream( _dword& value, _dword bitsnumber )
{
	value = 0;

	_dword totalbits = mBitOffset + bitsnumber;

	for ( _dword index = 0; mBitOffset < totalbits; index ++, mBitOffset ++ )
	{
		if ( mBitOffset != 0 && mBitOffset % 8 == 0 )
			Seek( _SEEK_CURRENT, 1 );

		value |= ( ( ( *mPointer << ( mBitOffset % 8 ) ) & 0x80 ) >> 7 ) << ( bitsnumber - index - 1 );
	}

	// Jump to the next byte
	if ( mBitOffset != 0 && mBitOffset % 8 == 0 )
		Seek( _SEEK_CURRENT, 1 );

	// Update the offset-bits
	mBitOffset %= 8;

	return _true;
}

_ubool BitStreamReader::ReadBitsStream( _qword& value, _dword bitsnumber )
{
	value = 0;

	_dword totalbits = mBitOffset + bitsnumber;

	for ( _dword index = 0; mBitOffset < totalbits; index ++, mBitOffset ++ )
	{
		if ( mBitOffset != 0 && mBitOffset % 8 == 0 )
			Seek( _SEEK_CURRENT, 1 );

		value |= ( ( ( _qword( *mPointer ) << ( mBitOffset % 8 ) ) & 0x80 ) >> 7 ) << ( bitsnumber - index - 1 );
	}

	// Jump to the next byte
	if ( mBitOffset != 0 && mBitOffset % 8 == 0 )
		Seek( _SEEK_CURRENT, 1 );

	// Update the offset-bits
	mBitOffset %= 8;

	return _true;
}

_ubool BitStreamReader::ReadBitsStream( _float& value, _dword bitsnumber )
{
	_dword valuetemp = 0;
	if ( ReadBitsStream( valuetemp, bitsnumber ) == _false )
		return _false;

	if ( bitsnumber == 16 )
	{
		// The high 8 bits represent the number before the decimal point, and the low 16 bits represent the number after the decimal point
		_byte hiword = (_byte)( valuetemp >> 8 );
		_byte loword = valuetemp & 0xFF;

		value = hiword + (_float) loword / 256.0f;
	}
	else
	{
		// The high 16 bits represent the number before the decimal point, and the low 16 bits represent the number after the decimal point
		_word hiword = valuetemp >> 16;
		_word loword = valuetemp & 0xFFFF;

		value = hiword + (_float) loword / 65536.0f;
	}

	return _true;
}

_ubool BitStreamReader::ReadBitsStream( _double& value )
{
	_dword hidword = 0, lodword = 0;
	if ( ReadBitsStream( hidword, 32 ) == _false || ReadBitsStream( lodword, 32 ) == _false )
		return _false;

	value = hidword + (_double) lodword / 4294967295.0;

	return _true;
}