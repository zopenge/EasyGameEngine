//! @file     JNIClasses.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// J2CArray
//----------------------------------------------------------------------------

class J2CArray : public TObject< IJ2CArray >
{
private:
	_dword	mSize;
	_byte*	mBuffer;

public:
	J2CArray( jbyteArray buffer );
	virtual ~J2CArray( );

// IJ2CArray Interface
public:
	virtual _dword			GetSize( ) const override;

	virtual const _byte*	GetBuffer( ) const override;
};

//----------------------------------------------------------------------------
// C2JArray
//----------------------------------------------------------------------------

class C2JArray : public TObject< IC2JArray >
{
private:
	_dword		mSize;
	jbyteArray	mJBuffer;

public:
	C2JArray( _dword size );
	C2JArray( _dword size, const _byte* buffer );
	virtual ~C2JArray( );

// IC2JArray Interface
public:
	virtual _dword		GetSize( ) const override;

	virtual jbyteArray	ToJArray( ) const override;

	virtual _void		ReadBuffer( _dword offset, _dword size, _byte* buffer ) override;
};

//----------------------------------------------------------------------------
// J2CString
//----------------------------------------------------------------------------

class J2CString : public TObject< IJ2CString >
{
private:
	jstring			mJString;
	const _chara*	mUTF8String;

public:
	J2CString( jstring string );
	virtual ~J2CString( );

// IJ2CString Interface
public:
	virtual AStringR	ToStringA( ) const override;
	virtual UStringR	ToStringU( ) const override;
	virtual WStringR	ToStringW( ) const override;
};

//----------------------------------------------------------------------------
// C2JString
//----------------------------------------------------------------------------

class C2JString : public TObject< IC2JString >
{
private:
	jstring	mJString;

public:
	C2JString( const _chara* string );
	C2JString( const _charw* string );
	C2JString( AStringPtr string );
	C2JString( UStringPtr string );
	C2JString( WStringPtr string );
	C2JString( const AStringR& string );
	C2JString( const UStringR& string );
	C2JString( const WStringR& string );
	C2JString( const AStringObj& string );
	C2JString( const UStringObj& string );
	C2JString( const WStringObj& string );
	virtual ~C2JString( );

// IC2JString Interface
public:
	virtual jstring ToJString( ) const override;
};

//----------------------------------------------------------------------------
// C2JStringMap
//----------------------------------------------------------------------------

class C2JStringMap : public TObject< IC2JStringMap >
{
private:
	jobject	mJMapObject;

public:
	C2JStringMap( );
	C2JStringMap( const Map< UString, UString >& map_object );
	virtual ~C2JStringMap( );

// IC2JStringMap Interface
public:
	virtual jobject ToJMapObject( ) const override;
};

}