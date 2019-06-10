#pragma once

namespace EGE {

/// <summary>
/// The java->C/C++ array interface.
/// </summary>
class IJ2CArray : public IObject {
public:
	virtual _dword GetSize() const PURE;

	virtual const _byte* GetBuffer() const PURE;
};

/// <summary>
/// The C/C++->java array interface.
/// </summary>
class IC2JArray : public IObject {
public:
	virtual _dword GetSize() const PURE;

	virtual jbyteArray ToJArray() const PURE;

	virtual _void ReadBuffer(_dword offset, _dword size, _byte* buffer) PURE;
};

/// <summary>
/// The java->C/C++ string interface.
/// </summary>
class IJ2CString : public IObject {
public:
	virtual AString ToStringA() const PURE;
	virtual UString ToStringU() const PURE;
	virtual WString ToStringW() const PURE;
};

/// <summary>
/// The C/C++->java string interface.
/// </summary>
class IC2JString : public IObject {
public:
	virtual jstring ToJString() const PURE;
};

/// <summary>
/// The C/C++->java string map interface.
/// </summary>
class IC2JStringMap : public IObject {
public:
	virtual jobject ToJMapObject() const PURE;
};

// JAVA<->C/++ bridge elements declarations
REF_OBJECT_DECL(IJ2CArray);
REF_OBJECT_DECL(IC2JArray);
REF_OBJECT_DECL(IJ2CString);
REF_OBJECT_DECL(IC2JString);
REF_OBJECT_DECL(IC2JStringMap);

/// <summary>
/// The android platform interface.
/// </summary>
class IAndroidPlatform : public IPlatform {
public:
	//!	Get the JNI env handle.
	//!	@param		none.
	//!	@return		The JNI env handle.
	virtual JNIEnv* GetJNIEnv() PURE;

	//!	Convert array to HEX string.
	//!	@param		buffer		The array buffer.
	//!	@return		The HEX string.
	virtual AString ByteArray2HexString(jbyteArray buffer) PURE;

	// Create JNI object.
	//!	@param		path		The class path.
	//!	@return		The JNI object interface.
	virtual IInvokerPassRef CreateJNIObject(AStringPtr path) PURE;

	//!	Create J->C array.
	//!	@param		buffer		The buffer data.
	//!	@return		The J->C array interface.
	virtual IJ2CArrayPassRef CreateJ2CArray(jbyteArray buffer) PURE;
	//!	Create C->J array.
	//!	@param		size		The buffer size.
	//!	@param		buffer		The buffer data.
	//!	@return		The C->J array interface.
	virtual IC2JArrayPassRef CreateC2JArray(_dword size, const _byte* buffer) PURE;

	//!	Convert J->C string.
	//!	@param		string		The J string.
	//!	@return		The string.
	virtual AString ToStringA(jstring string) PURE;
	//!	Convert J->C string.
	//!	@param		string		The J string.
	//!	@return		The string.
	virtual UString ToStringU(jstring string) PURE;
	//!	Convert J->C string.
	//!	@param		string		The J string.
	//!	@return		The string.
	virtual WString ToStringW(jstring string) PURE;

	//!	Create J->C string.
	//!	@param		string		The J string.
	//!	@return		The J->C array interface.
	virtual IJ2CStringPassRef CreateJ2CString(jstring string) PURE;
	//!	Create C->J string.
	//!	@param		string		The C string.
	//!	@return		The C->J array interface.
	virtual IC2JStringPassRef CreateC2JString(AStringPtr string) PURE;
	//!	Create C->J string.
	//!	@param		string		The C string.
	//!	@return		The C->J array interface.
	virtual IC2JStringPassRef CreateC2JString(UStringPtr string) PURE;
	//!	Create C->J string.
	//!	@param		string		The C string.
	//!	@return		The C->J array interface.
	virtual IC2JStringPassRef CreateC2JString(WStringPtr string) PURE;
	//!	Create C->J string.
	//!	@param		string		The C string.
	//!	@return		The C->J array interface.
	virtual IC2JStringPassRef CreateC2JString(const AStringObj& string) PURE;
	//!	Create C->J string.
	//!	@param		string		The C string.
	//!	@return		The C->J array interface.
	virtual IC2JStringPassRef CreateC2JString(const UStringObj& string) PURE;
	//!	Create C->J string.
	//!	@param		string		The C string.
	//!	@return		The C->J array interface.
	virtual IC2JStringPassRef CreateC2JString(const WStringObj& string) PURE;

	//!	Create C->J string map.
	//!	@param		map_object	The C UTF-8 string map.
	//!	@return		The C->J map interface.
	virtual IC2JStringMapPassRef CreateC2JStringMap(const Map<UString, UString>& map_object) PURE;
};

} // namespace EGE
