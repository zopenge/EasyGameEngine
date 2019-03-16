//! @file     Serializer.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Serializer
//----------------------------------------------------------------------------

class Serializer
{
protected:
	_ubool	mReadOnly;

	_dword	mSize;
	_dword	mOffset;

	_byte*	mBuffer;

protected:
	//!	Resize.
	_ubool Resize( _dword size );

protected:
	//!	Read/Write.
	template< typename Type >
	_void Read( Type& value );
	template< typename Type >
	_void Write( const Type& value );

public:
	Serializer( _byte* buffer, _dword size );
	Serializer( _dword size );
	~Serializer( );

public:
	//!	Get buffer.
	_byte* GetBuffer( );
	//!	Get size.
	_dword GetSize( ) const;
	//!	Get offset.
	_dword GetOffset( ) const;

	//!	Check whether it's read only.
	_ubool IsReadOnly( ) const;

public:
	// Export
	Serializer& operator >> ( AString& v );
	Serializer& operator >> ( _byte& v );
	Serializer& operator >> ( _chara& v );
	Serializer& operator >> ( _charw& v );
	Serializer& operator >> ( _large& v );
	Serializer& operator >> ( _qword& v );
	Serializer& operator >> ( _int& v );
	Serializer& operator >> ( _dword& v );
	Serializer& operator >> ( _short& v );
	Serializer& operator >> ( _word& v );
	Serializer& operator >> ( _float& v );
	Serializer& operator >> ( _double& v );
	Serializer& operator >> ( _ubool& v );

public:
	// Import
	Serializer& operator << ( const AString& v );
	Serializer& operator << ( const _byte& v );
	Serializer& operator << ( const _chara& v );
	Serializer& operator << ( const _charw& v );
	Serializer& operator << ( const _large& v );
	Serializer& operator << ( const _qword& v );
	Serializer& operator << ( const _int& v );
	Serializer& operator << ( const _dword& v );
	Serializer& operator << ( const _short& v );
	Serializer& operator << ( const _word& v );
	Serializer& operator << ( const _float& v );
	Serializer& operator << ( const _double& v );
	Serializer& operator << ( const _ubool& v );
};

//----------------------------------------------------------------------------
// Serializer Implementation
//----------------------------------------------------------------------------

template< typename Type >
_void Serializer::Read( Type& value )
{
	if ( mReadOnly )
	{
		if ( mOffset + sizeof(Type) <= mSize )
		{
			value = *(Type*)( mBuffer + mOffset ); 
			mOffset += sizeof(Type);
		}
		else
		{
			EGE_ASSERT( _false ); 
		}
	}
	else
	{
		EGE_ASSERT( _false ); 
	}
}

template< typename Type >
_void Serializer::Write( const Type& value )
{
	if ( !mReadOnly )
	{
		if ( mOffset + sizeof(Type) <= mSize || Resize( mSize * 2 ) )
		{
			*(Type*)( mBuffer + mOffset ) = value; 
			mOffset += sizeof(Type);
		}
		else
		{ 
			EGE_ASSERT( _false ); 
		}
	}
	else
	{ 
		EGE_ASSERT( _false ); 
	}
}

}