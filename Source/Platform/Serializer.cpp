//! @file     Serializer.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Serializer Implementation
//----------------------------------------------------------------------------

Serializer::Serializer( _byte* buffer, _dword size )
{
 mReadOnly = _true;

 mSize  = size;
 mOffset  = 0;

 mBuffer  = buffer;
}

Serializer::Serializer( _dword size )
{
 mReadOnly = _false;

 mSize  = size;
 mOffset  = 0;

 mBuffer  = _null;

 // Create buffer if needed
 if ( mSize > 0 )
  mBuffer = new _byte[ mSize ];
}

Serializer::~Serializer()
{
 EGE_DELETE_ARRAY( mBuffer );
}

_byte* Serializer::GetBuffer( )
{
 return mBuffer;
}

_dword Serializer::GetSize( ) const
{
 return mSize;
}

_dword Serializer::GetOffset( ) const
{
 return mOffset;
}


_ubool Serializer::IsReadOnly( ) const
{
 return mReadOnly;
}

Serializer& Serializer::operator >> ( AString& v )
{
 if ( mReadOnly )
 {
  _short length = 0; 
  Read( length );
  if ( mOffset + length <= mSize )
  {
   v += AString( (const _chara*)(mBuffer + mOffset), length );
   mOffset += length;
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

 return *this;
}

Serializer& Serializer::operator >> ( _byte& v )
{
 Read( v );
 return *this;
}

Serializer& Serializer::operator >> ( _chara& v )
{
 Read( v );
 return *this;
}

Serializer& Serializer::operator >> ( _charw& v )
{
 Read( v );
 return *this;
}

Serializer& Serializer::operator >> ( _large& v )
{
 Read( v );
 return *this;
}

Serializer& Serializer::operator >> ( _qword& v )
{
 Read( v );
 return *this;
}

Serializer& Serializer::operator >> ( _int& v )
{
 Read( v );
 return *this;
}

Serializer& Serializer::operator >> ( _dword& v )
{
 Read( v );
 return *this;
}

Serializer& Serializer::operator >> ( _short& v )
{
 Read( v );
 return *this;
}

Serializer& Serializer::operator >> ( _word& v )
{
 Read( v );
 return *this;
}

Serializer& Serializer::operator >> ( _float& v )
{
 Read( v );
 return *this;
}

Serializer& Serializer::operator >> ( _double& v )
{
 Read( v );
 return *this;
}

Serializer& Serializer::operator >> ( _ubool& v )
{
 _byte nBool;
 Read( nBool );
 v = ( nBool != 0 );
 return *this;
}

_ubool Serializer::Resize( _dword size )
{
 _byte* new_buffer = new _byte[ size ];
 EGE_MEM_CPY( new_buffer, mBuffer, mSize ) ;

 EGE_DELETE_ARRAY( mBuffer );

 mBuffer = new_buffer;
 mSize = size;

 return _true ;
}

Serializer& Serializer::operator << ( const AString& v )
{
 if ( ! mReadOnly )
 {
  _short length = (_short)( v.GetLength( ) );
  if ( mOffset + sizeof(_short) + length <= mSize || Resize( mOffset + sizeof(_short) + length ) )
  {
   *(_short*)( mBuffer + mOffset ) = length;

   mOffset += sizeof(_short);

   for( _short i = 0; i < length; i ++, mOffset ++ )
    *(_chara*)(mBuffer + mOffset) = v[i];
  }
  else
   EGE_ASSERT( _false );
 }
 else
 {
  EGE_ASSERT( _false );
 }

 return *this;
}

Serializer& Serializer::operator << ( const _byte& v )
{ 
 Write( v );
 return *this;
}

Serializer& Serializer::operator << ( const _chara& v )
{
 Write( v );
 return *this;
}

Serializer& Serializer::operator << ( const _charw& v )
{
 Write( v );
 return *this;
}

Serializer& Serializer::operator << ( const _large& v )
{
 Write( v );
 return *this;
}

Serializer& Serializer::operator << ( const _qword& v )
{
 Write( v );
 return *this;
}

Serializer& Serializer::operator << ( const _int& v )
{
 Write( v );
 return *this;
}

Serializer& Serializer::operator << ( const _dword& v )
{
 Write( v );
 return *this;
}

Serializer& Serializer::operator << ( const _short& v )
{
 Write( v );
 return *this;
}

Serializer& Serializer::operator << ( const _word& v )
{
 Write( v );
 return *this;
}

Serializer& Serializer::operator << ( const _float& v )
{
 Write( v );
 return *this;
}

Serializer& Serializer::operator << ( const _double& v )
{
 Write( v );
 return *this;
}

Serializer& Serializer::operator << ( const _ubool& v )
{
 Write( v );
 return *this;
}
