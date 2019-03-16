//! @file     JNIClasses.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// J2CArray Implementation
//----------------------------------------------------------------------------

J2CArray::J2CArray( jbyteArray buffer )
{
	EGE_ASSERT( buffer != _null );

	mSize = androidJNI::GetInstance( ).GetJNIEnv( )->GetArrayLength( buffer );
	if ( mSize != 0 )
	{
		mBuffer = new _byte[ mSize ];
		EGE_MEM_CPY( mBuffer, androidJNI::GetInstance( ).GetJNIEnv( )->GetByteArrayElements( buffer, _null ), mSize );
	}
}

J2CArray::~J2CArray( )
{
	EGE_DELETE_ARRAY( mBuffer );
}

_dword J2CArray::GetSize( ) const
{
	return mSize;
}

const _byte* J2CArray::GetBuffer( ) const
{
	return mBuffer;
}

//----------------------------------------------------------------------------
// C2JArray Implementation
//----------------------------------------------------------------------------

C2JArray::C2JArray( _dword size )
{
	EGE_ASSERT( size != 0 );

	mSize		= size;
	mJBuffer	= androidJNI::GetInstance( ).GetJNIEnv( )->NewByteArray( size );
	EGE_ASSERT( mJBuffer != _null );
}

C2JArray::C2JArray( _dword size, const _byte* buffer )
{
	EGE_ASSERT( size != 0 );
	EGE_ASSERT( buffer != _null );

	mSize		= size;
	mJBuffer	= androidJNI::GetInstance( ).GetJNIEnv( )->NewByteArray( size );
	EGE_ASSERT( mJBuffer != _null );

	androidJNI::GetInstance( ).GetJNIEnv( )->SetByteArrayRegion( mJBuffer, 0, size, (const jbyte*)buffer );
}

C2JArray::~C2JArray( )
{
	androidJNI::GetInstance( ).GetJNIEnv( )->DeleteLocalRef( mJBuffer );
}

_dword C2JArray::GetSize( ) const
{
	return mSize;
}

jbyteArray C2JArray::ToJArray( ) const
{
	return mJBuffer;
}

_void C2JArray::ReadBuffer( _dword offset, _dword size, _byte* buffer )
{
	if ( size == 0 || buffer == _null )
		return;

	androidJNI::GetInstance( ).GetJNIEnv( )->GetByteArrayRegion( mJBuffer, offset, size, (jbyte*)buffer );
}

//----------------------------------------------------------------------------
// J2CString Implementation
//----------------------------------------------------------------------------

J2CString::J2CString( jstring string ) 
{
	mJString	= string;

	mUTF8String	= androidJNI::GetInstance( ).GetJNIEnv( )->GetStringUTFChars( string, _null );
	EGE_ASSERT( mUTF8String != _null );
}

J2CString::~J2CString( )
{
	androidJNI::GetInstance( ).GetJNIEnv( )->ReleaseStringUTFChars( mJString, mUTF8String );
}

AStringR J2CString::ToStringA( ) const
{
	return AString( ).FromString( _ENCODING_UTF8, mUTF8String );
}

UStringR J2CString::ToStringU( ) const
{
	return mUTF8String;
}

WStringR J2CString::ToStringW( ) const
{
	return WString( ).FromString( _ENCODING_UTF8, mUTF8String );
}

//----------------------------------------------------------------------------
// C2JString Implementation
//----------------------------------------------------------------------------

C2JString::C2JString( const _chara* string )
{
	mJString = androidJNI::GetInstance( ).GetJNIEnv( )->NewStringUTF( string );
	EGE_ASSERT( mJString != _null );
}

C2JString::C2JString( const _charw* string )
{
	mJString = androidJNI::GetInstance( ).GetJNIEnv( )->NewStringUTF( UString( ).FromString( _ENCODING_UTF16, string ).Str( ) );
	EGE_ASSERT( mJString != _null );
}

C2JString::C2JString( AStringPtr string )
{
	mJString = androidJNI::GetInstance( ).GetJNIEnv( )->NewStringUTF( string.Str( ) );
	EGE_ASSERT( mJString != _null );
}

C2JString::C2JString( UStringPtr string )
{
	mJString = androidJNI::GetInstance( ).GetJNIEnv( )->NewStringUTF( string.Str( ) );
	EGE_ASSERT( mJString != _null );
}

C2JString::C2JString( WStringPtr string )
{
	mJString = androidJNI::GetInstance( ).GetJNIEnv( )->NewStringUTF( UString( ).FromString( string ).Str( ) );
	EGE_ASSERT( mJString != _null );
}

C2JString::C2JString( const AStringR& string )
{
	mJString = androidJNI::GetInstance( ).GetJNIEnv( )->NewStringUTF( ((const AString&)string).Str( ) );
	EGE_ASSERT( mJString != _null );
}

C2JString::C2JString( const UStringR& string )
{
	mJString = androidJNI::GetInstance( ).GetJNIEnv( )->NewStringUTF( ((const UString&)string).Str( ) );
	EGE_ASSERT( mJString != _null );
}

C2JString::C2JString( const WStringR& string )
{
	mJString = androidJNI::GetInstance( ).GetJNIEnv( )->NewStringUTF( UString( ).FromString( (const WString&)string ).Str( ) );
	EGE_ASSERT( mJString != _null );
}

C2JString::C2JString( const AStringObj& string )
{
	mJString = androidJNI::GetInstance( ).GetJNIEnv( )->NewStringUTF( string.Str( ) );
	EGE_ASSERT( mJString != _null );
}

C2JString::C2JString( const UStringObj& string )
{
	mJString = androidJNI::GetInstance( ).GetJNIEnv( )->NewStringUTF( string.Str( ) );
	EGE_ASSERT( mJString != _null );
}

C2JString::C2JString( const WStringObj& string )
{
	mJString = androidJNI::GetInstance( ).GetJNIEnv( )->NewStringUTF( UString( ).FromString( _ENCODING_UTF16, string.Str( ) ).Str( ) );
	EGE_ASSERT( mJString != _null );
}

C2JString::~C2JString( )
{
	androidJNI::GetInstance( ).GetJNIEnv( )->DeleteLocalRef( mJString );
}

jstring C2JString::ToJString( ) const
{
	return mJString;
}

//----------------------------------------------------------------------------
// C2JStringMap Implementation
//----------------------------------------------------------------------------

C2JStringMap::C2JStringMap( )
{
	mJMapObject	= androidJNI::GetInstance( ).CreateHashMapObject( );
}

C2JStringMap::C2JStringMap( const Map< UString, UString >& map_object )
{
	mJMapObject	= androidJNI::GetInstance( ).CreateHashMapObject( map_object );
}

C2JStringMap::~C2JStringMap( )
{
	androidJNI::GetInstance( ).GetJNIEnv( )->DeleteLocalRef( mJMapObject );
}

jobject C2JStringMap::ToJMapObject( ) const
{
	return mJMapObject;
}
