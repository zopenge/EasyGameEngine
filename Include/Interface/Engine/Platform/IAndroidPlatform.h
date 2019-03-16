//! @file     IAndroidPlatform.h
//! @author   LiCode
//! @version  1.0.0.547
//! @date     2011/01/07
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IJ2CArray
//----------------------------------------------------------------------------

class IJ2CArray : public IObject
{
public:
	virtual _dword GetSize( ) const PURE;

	virtual const _byte* GetBuffer( ) const PURE;
};

//----------------------------------------------------------------------------
// IC2JArray
//----------------------------------------------------------------------------

class IC2JArray : public IObject
{
public:
	virtual _dword GetSize( ) const PURE;

	virtual jbyteArray ToJArray( ) const PURE;

	virtual _void ReadBuffer( _dword offset, _dword size, _byte* buffer ) PURE;
};

//----------------------------------------------------------------------------
// IJ2CString
//----------------------------------------------------------------------------

class IJ2CString : public IObject
{
public:
	virtual AStringR ToStringA( ) const PURE;
	virtual UStringR ToStringU( ) const PURE;
	virtual WStringR ToStringW( ) const PURE;
};

//----------------------------------------------------------------------------
// IC2JString
//----------------------------------------------------------------------------

class IC2JString : public IObject
{
public:
	virtual jstring ToJString( ) const PURE;
};

//----------------------------------------------------------------------------
// IC2JStringMap
//----------------------------------------------------------------------------

class IC2JStringMap : public IObject
{
public:
	virtual jobject ToJMapObject( ) const PURE;
};

//----------------------------------------------------------------------------
// IAndroidPlatform
//----------------------------------------------------------------------------

class IAndroidPlatform : public IPlatform
{
public:
	//!	Get the JNI env handle.
	//!	@param		none.
	//!	@return		The JNI env handle.
	virtual JNIEnv* GetJNIEnv( ) PURE;

	//!	Convert array to HEX string.
	//!	@param		buffer		The array buffer.
	//!	@return		The HEX string.
	virtual AStringR ByteArray2HexString( jbyteArray buffer ) PURE;

	// Create JNI object.
	//!	@param		path		The class path.
	//!	@return		The JNI object interface.
	virtual IInvokerPassRef CreateJNIObject( AStringPtr path ) PURE;

	//!	Create J->C array.
	//!	@param		buffer		The buffer data.
	//!	@return		The J->C array interface.
	virtual IJ2CArrayPassRef CreateJ2CArray( jbyteArray buffer ) PURE;
	
	//!	Create C->J array.
	//!	@param		size		The buffer size.
	//!	@param		buffer		The buffer data.
	//!	@return		The C->J array interface.
	virtual IC2JArrayPassRef CreateC2JArray( _dword size, const _byte* buffer ) PURE;

	//!	Convert J->C string.
	//!	@param		string		The J string.
	//!	@return		The string.
	virtual AStringR ToStringA( jstring string ) PURE;
	//!	Convert J->C string.
	//!	@param		string		The J string.
	//!	@return		The string.
	virtual UStringR ToStringU( jstring string ) PURE;
	//!	Convert J->C string.
	//!	@param		string		The J string.
	//!	@return		The string.
	virtual WStringR ToStringW( jstring string ) PURE;
	//!	Create J->C string.
	//!	@param		string		The J string.
	//!	@return		The J->C array interface.
	virtual IJ2CStringPassRef CreateJ2CString( jstring string ) PURE;

	//!	Create C->J string.
	//!	@param		string		The C string.
	//!	@return		The C->J array interface.
	virtual IC2JStringPassRef CreateC2JString( AStringPtr string ) PURE;
	//!	Create C->J string.
	//!	@param		string		The C string.
	//!	@return		The C->J array interface.
	virtual IC2JStringPassRef CreateC2JString( UStringPtr string ) PURE;
	//!	Create C->J string.
	//!	@param		string		The C string.
	//!	@return		The C->J array interface.
	virtual IC2JStringPassRef CreateC2JString( WStringPtr string ) PURE;
	//!	Create C->J string.
	//!	@param		string		The C string.
	//!	@return		The C->J array interface.
	virtual IC2JStringPassRef CreateC2JString( const AStringObj& string ) PURE;
	//!	Create C->J string.
	//!	@param		string		The C string.
	//!	@return		The C->J array interface.
	virtual IC2JStringPassRef CreateC2JString( const UStringObj& string ) PURE;
	//!	Create C->J string.
	//!	@param		string		The C string.
	//!	@return		The C->J array interface.
	virtual IC2JStringPassRef CreateC2JString( const WStringObj& string ) PURE;

	//!	Create C->J string map.
	//!	@param		map_object	The C UTF-8 string map.
	//!	@return		The C->J map interface.
	virtual IC2JStringMapPassRef CreateC2JStringMap( const Map< UString, UString >& map_object ) PURE;

	//!	Copy file from asset directory.
	//!	@param		source_file_name	The source file name in asset directory.
	//!	@param		target_file_name	The target file name.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool CopyFileFromAssetDir( WStringPtr source_file_name, WStringPtr target_file_name ) PURE;
	//!	Copy directory from asset directory.
	//!	@param		source_dir_name		The source directory name in asset directory.
	//!	@param		target_dir_name		The target directory name.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool CopyDirFromAssetDir( WStringPtr source_dir_name, WStringPtr target_dir_name ) PURE;

	//!	Get signature.
	//!	@param		none.
	//!	@return		The signature.
	virtual AStringR GetSignature( ) PURE;
};

}
