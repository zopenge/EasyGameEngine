//! @file     EGE_Platform.h
//! @author   LiCode
//! @version  1.0.0.702
//! @date     2011/02/15
//! Copyright ...

#pragma once

//----------------------------------------------------------------------------
// String Format Macros
//----------------------------------------------------------------------------

// ANSI string format
#define FORMAT_ASTRING_1( format, p1 )														AString( ).Format( format, p1 ).Str( )
#define FORMAT_ASTRING_2( format, p1, p2 )													AString( ).Format( format, p1, p2 ).Str( )
#define FORMAT_ASTRING_3( format, p1, p2, p3 )												AString( ).Format( format, p1, p2, p3 ).Str( )
#define FORMAT_ASTRING_4( format, p1, p2, p3, p4 )											AString( ).Format( format, p1, p2, p3, p4 ).Str( )
#define FORMAT_ASTRING_5( format, p1, p2, p3, p4, p5 )										AString( ).Format( format, p1, p2, p3, p4, p5 ).Str( )
#define FORMAT_ASTRING_6( format, p1, p2, p3, p4, p5, p6 )									AString( ).Format( format, p1, p2, p3, p4, p5, p6 ).Str( )
#define FORMAT_ASTRING_7( format, p1, p2, p3, p4, p5, p6, p7 )								AString( ).Format( format, p1, p2, p3, p4, p5, p6, p7 ).Str( )
#define FORMAT_ASTRING_8( format, p1, p2, p3, p4, p5, p6, p7, p8 )							AString( ).Format( format, p1, p2, p3, p4, p5, p6, p7, p8 ).Str( )
#define FORMAT_ASTRING_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 )						AString( ).Format( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ).Str( )
#define FORMAT_ASTRING_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 )				AString( ).Format( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ).Str( )
#define FORMAT_ASTRING_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 )			AString( ).Format( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ).Str( )
#define FORMAT_ASTRING_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 )		AString( ).Format( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ).Str( )
#define FORMAT_ASTRING_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 )	AString( ).Format( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ).Str( )

// UTF-16 string format
#define FORMAT_WSTRING_1( format, p1 )														WString( ).Format( format, p1 ).Str( )
#define FORMAT_WSTRING_2( format, p1, p2 )													WString( ).Format( format, p1, p2 ).Str( )
#define FORMAT_WSTRING_3( format, p1, p2, p3 )												WString( ).Format( format, p1, p2, p3 ).Str( )
#define FORMAT_WSTRING_4( format, p1, p2, p3, p4 )											WString( ).Format( format, p1, p2, p3, p4 ).Str( )
#define FORMAT_WSTRING_5( format, p1, p2, p3, p4, p5 )										WString( ).Format( format, p1, p2, p3, p4, p5 ).Str( )
#define FORMAT_WSTRING_6( format, p1, p2, p3, p4, p5, p6 )									WString( ).Format( format, p1, p2, p3, p4, p5, p6 ).Str( )
#define FORMAT_WSTRING_7( format, p1, p2, p3, p4, p5, p6, p7 )								WString( ).Format( format, p1, p2, p3, p4, p5, p6, p7 ).Str( )
#define FORMAT_WSTRING_8( format, p1, p2, p3, p4, p5, p6, p7, p8 )							WString( ).Format( format, p1, p2, p3, p4, p5, p6, p7, p8 ).Str( )
#define FORMAT_WSTRING_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 )						WString( ).Format( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ).Str( )
#define FORMAT_WSTRING_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 )				WString( ).Format( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ).Str( )
#define FORMAT_WSTRING_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 )			WString( ).Format( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ).Str( )
#define FORMAT_WSTRING_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 )		WString( ).Format( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ).Str( )
#define FORMAT_WSTRING_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 )	WString( ).Format( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ).Str( )

//----------------------------------------------------------------------------
// Platform Configure
//----------------------------------------------------------------------------

// Windows Platform
#if defined _PLATFORM_WINDOWS_
	
	#include "Platform/OS/windows/Win32Headers.h"
	#include "Platform/OS/windows/Win32Macros.h"

// IOS Platform
#elif defined _PLATFORM_IOS_

	#include "Platform/OS/ios/IOSHeaders.h"

// OSX Platform
#elif defined _PLATFORM_OSX_

// Android Platform
#elif defined _PLATFORM_ANDROID_

// Chrome Platform
#elif defined _PLATFORM_CHROME_

#endif

// Platform Independent Files
#include "Platform/Maths.h"
#include "Platform/CRC.h"
#include "Platform/Platform.h"

// Template classes are dependent on the platform files
#include "Template/RawString.h"
#include "Template/ConstString.h"
#include "Template/MutableString.h"
#include "Template/MutableStringR.h"

//----------------------------------------------------------------------------
// Helpful Functions
//----------------------------------------------------------------------------

namespace EGE
{

typedef Array< _word > WordArray;
typedef Array< _dword > DwordArray;
typedef Array< _qword > QwordArray;
typedef Array< _int > IntArray;
typedef Array< _large > LargeArray;
typedef Array< _float > FloatArray;
typedef Array< _double > DoubleArray;
typedef Stack< _word > WordStack;
typedef Stack< _dword > DwordStack;

typedef RawString< _chara, _ENCODING_ANSI > 		ARawString;
typedef RawString< _chara, _ENCODING_UTF8 > 		URawString;
typedef RawString< _charw, _ENCODING_UTF16 > 		WRawString;

typedef ConstString< _chara, _ENCODING_ANSI > 		AStringPtr;
typedef ConstString< _chara, _ENCODING_UTF8 > 		UStringPtr;
typedef ConstString< _charw, _ENCODING_UTF16 > 		WStringPtr;

typedef MutableString< _chara, _ENCODING_ANSI >		AString;
typedef MutableString< _chara, _ENCODING_UTF8 >		UString;
typedef MutableString< _charw, _ENCODING_UTF16 >	WString;

typedef MutableStringR< _chara, _ENCODING_ANSI >	AStringR;
typedef MutableStringR< _chara, _ENCODING_UTF8 >	UStringR;
typedef MutableStringR< _charw, _ENCODING_UTF16 >	WStringR;

typedef Array< AString > AStringArray;
typedef Array< UString > UStringArray;
typedef Array< WString > WStringArray;

typedef Map< AString, AString > AStringMap;
typedef Map< UString, UString > UStringMap;
typedef Map< WString, WString > WStringMap;

typedef BitArray< 1 > OneBitArray;

typedef Queue< AString > AStringQueue;
typedef Queue< UString > UStringQueue;
typedef Queue< WString > WStringQueue;

// AString
inline AString operator + ( AString& str1, _chara character )
{
	AString string( str1 );
	string += character;

	return string;
}

inline AString operator + ( const _chara* str1, const AString& str2 )
{
	AString string( str1 );
	string += str2;

	return string;
}

inline AString operator + ( const AString& str1, const _chara* str2 )
{
	AString string( str1 );
	string += str2;

	return string;
}

inline AString operator + ( const AString& str1, const AString& str2 )
{
	AString string( str1 );
	string += str2;

	return string;
}

// UString
inline UString operator + ( UString& str1, _chara character )
{
	UString string( str1 );
	string += character;

	return string;
}

inline UString operator + ( const _chara* str1, const UString& str2 )
{
	UString string( str1 );
	string += str2;

	return string;
}

inline UString operator + ( const UString& str1, const _chara* str2 )
{
	UString string( str1 );
	string += str2;

	return string;
}

inline UString operator + ( const UString& str1, const UString& str2 )
{
	UString string( str1 );
	string += str2;

	return string;
}

// WString
inline WString operator + ( WString& str1, _charw character )
{
	WString string( str1 );
	string += character;

	return string;
}

inline WString operator + ( const _charw* str1, const WString& str2 )
{
	WString string( str1 );
	string += str2;

	return string;
}

inline WString operator + ( const WString& str1, const _charw* str2 )
{
	WString string( str1 );
	string += str2;

	return string;
}

inline WString operator + ( const WString& str1, const WString& str2 )
{
	WString string( str1 );
	string += str2;

	return string;
}

//!	Copy string in safe way.
template< _dword _BUFFER_LENGTH, typename CharType >
CharType* SafeCopyString( CharType (&to)[ _BUFFER_LENGTH ], const CharType* from )
{
	return Platform::CopyString( to, from, _BUFFER_LENGTH - 1 );
}

//!	Compare key.
template< typename Key >
inline _int CompareKeyInMap( const Key& key1, const Key& key2 )
{
	if ( key1 > key2 )
		return 1;
	else if ( key1 == key2 )
		return 0;
	else
		return -1;
}

template<>
inline _int CompareKeyInMap< _int >( const _int& key1, const _int& key2 )
{
	return key1 - key2;
}
template<>
inline _int CompareKeyInMap< _dword >( const _dword& key1, const _dword& key2 )
{
	return (_int)(key1 - key2);
}

template<>
inline _int CompareKeyInMap< AString >( const AString& key1, const AString& key2 )
{
	return key1.Compare( key2, _false );
}
template<>
inline _int CompareKeyInMap< WString >( const WString& key1, const WString& key2 )
{
	return key1.Compare( key2, _false );
}

template<>
inline MutableString< _chara, _ENCODING_ANSI >& MutableString< _chara, _ENCODING_ANSI >::FormatBytes( _qword bytes )
{
	if ( bytes >= 1 GB )
		Format( "%3.2f GB", (_float)bytes / (_float)1 GB );
	else if ( bytes >= 1 MB )
		Format( "%3.2f MB", (_float)bytes / (_float)1 MB );
	else
		Format( "%3.2f KB", (_float)bytes / (_float)1 KB );

	return *this;
}

template<>
inline MutableString< _chara, _ENCODING_UTF8 >& MutableString< _chara, _ENCODING_UTF8 >::FormatBytes( _qword bytes )
{
	if ( bytes >= 1 GB )
		Format( "%3.2f GB", (_float)bytes / (_float)1 GB );
	else if ( bytes >= 1 MB )
		Format( "%3.2f MB", (_float)bytes / (_float)1 MB );
	else
		Format( "%3.2f KB", (_float)bytes / (_float)1 KB );

	return *this;
}

template<>
inline MutableString< _charw, _ENCODING_UTF16 >& MutableString< _charw, _ENCODING_UTF16 >::FormatBytes( _qword bytes )
{
	if ( bytes >= 1 GB )
		Format( L"%3.2f GB", (_float)bytes / (_float)1 GB );
	else if ( bytes >= 1 MB )
		Format( L"%3.2f MB", (_float)bytes / (_float)1 MB );
	else
		Format( L"%3.2f KB", (_float)bytes / (_float)1 KB );

	return *this;
}

template<>
inline MutableString< _chara, _ENCODING_ANSI >& MutableString< _chara, _ENCODING_ANSI >::FormatCurrency( _qword currency )
{
	// Max value 4294967295 => 4,294,967,295

	_dword a = (_dword)(currency / 1000000000);
	_dword b = (_dword)(( currency % 1000000000 ) / 1000000);
	_dword c = (_dword)(( currency % 1000000 ) / 1000);
	_dword d = (_dword)(currency % 1000);

	if ( a > 0 )
		Format( "%d,%.3d,%.3d,%.3d", a, b, c, d );
	else if ( b > 0 )
		Format( "%d,%.3d,%.3d", b, c, d );
	else if ( c > 0 )
		Format( "%d,%.3d", c, d );
	else
		Format( "%d", d );

	return *this;
}

template<>
inline MutableString< _chara, _ENCODING_UTF8 >& MutableString< _chara, _ENCODING_UTF8 >::FormatCurrency( _qword currency )
{
	// Max value 4294967295 => 4,294,967,295

	_dword a = (_dword)(currency / 1000000000);
	_dword b = (_dword)(( currency % 1000000000 ) / 1000000);
	_dword c = (_dword)(( currency % 1000000 ) / 1000);
	_dword d = (_dword)(currency % 1000);

	if ( a > 0 )
		Format( "%d,%.3d,%.3d,%.3d", a, b, c, d );
	else if ( b > 0 )
		Format( "%d,%.3d,%.3d", b, c, d );
	else if ( c > 0 )
		Format( "%d,%.3d", c, d );
	else
		Format( "%d", d );

	return *this;
}

template<>
inline MutableString< _charw, _ENCODING_UTF16 >& MutableString< _charw, _ENCODING_UTF16 >::FormatCurrency( _qword currency )
{
	// Max value 4294967295 => 4,294,967,295

	_dword a = (_dword)(currency / 1000000000);
	_dword b = (_dword)(( currency % 1000000000 ) / 1000000);
	_dword c = (_dword)(( currency % 1000000 ) / 1000);
	_dword d = (_dword)(currency % 1000);

	if ( a > 0 )
		Format( L"%d,%.3d,%.3d,%.3d", a, b, c, d );
	else if ( b > 0 )
		Format( L"%d,%.3d,%.3d", b, c, d );
	else if ( c > 0 )
		Format( L"%d,%.3d", c, d );
	else
		Format( L"%d", d );

	return *this;
}

template<>
inline MutableString< _chara, _ENCODING_ANSI >& MutableString< _chara, _ENCODING_ANSI >::FormatTime( _qword millisecond )
{
	_dword hourunit = 60 * 60 * 1000, minuteunit = 60 * 1000, secondunit = 1000;

	_dword hours	= (_dword)(millisecond / hourunit);
	_dword minutes	= (_dword)(( millisecond - hours * hourunit ) / minuteunit);
	_dword seconds	= (_dword)(( millisecond - hours * hourunit - minutes* minuteunit ) / secondunit);

	Format( "%.2d:%.2d:%.2d", hours, minutes, seconds );

	return *this;
}

template<>
inline MutableString< _chara, _ENCODING_UTF8 >& MutableString< _chara, _ENCODING_UTF8 >::FormatTime( _qword millisecond )
{
	_dword hourunit = 60 * 60 * 1000, minuteunit = 60 * 1000, secondunit = 1000;

	_dword hours = (_dword)(millisecond / hourunit);
	_dword minutes = (_dword)((millisecond - hours * hourunit) / minuteunit);
	_dword seconds = (_dword)((millisecond - hours * hourunit - minutes* minuteunit) / secondunit);

	Format( "%.2d:%.2d:%.2d", hours, minutes, seconds );

	return *this;
}

template<>
inline MutableString< _charw, _ENCODING_UTF16 >& MutableString< _charw, _ENCODING_UTF16 >::FormatTime( _qword millisecond )
{
	_dword hourunit = 60 * 60 * 1000, minuteunit = 60 * 1000, secondunit = 1000;

	_dword hours = (_dword)(millisecond / hourunit);
	_dword minutes = (_dword)((millisecond - hours * hourunit) / minuteunit);
	_dword seconds = (_dword)((millisecond - hours * hourunit - minutes* minuteunit) / secondunit);

	Format( L"%.2d:%.2d:%.2d", hours, minutes, seconds );

	return *this;
}

}

// Platform Files
#include "Platform/PlatformGlobal.h"
#include "Platform/KeyCodes.h"
#include "Platform/FlagsObject.h"
#include "Platform/UID.h"
#include "Platform/StringFormatter.h"
#include "Platform/Path.h"
#include "Platform/Interpolation.h"
#include "Platform/Random.h"
#include "Platform/MD5.h"
#include "Platform/Color.h"
#include "Platform/Expression.h"
#include "Platform/Time.h"
#include "Platform/Timer.h"
#include "Platform/FPSTimer.h"
#include "Platform/Ratio.h"
#include "Platform/Precision.h"
#include "Platform/Address.h"
#include "Platform/Version.h"
#include "Platform/Variable.h"
#include "Platform/KernelObject.h"
#include "Platform/SyncObject.h"
#include "Platform/Lock.h"
#include "Platform/Thread.h"
#include "Platform/PersistenceThread.h"
#include "Platform/Pipe.h"
#include "Platform/CallStack.h"
#include "Platform/Memory.h"
#include "Platform/Clipboard.h"
#include "Platform/File.h"
#include "Platform/FileMapping.h"
#include "Platform/FileSystem.h"
#include "Platform/FileFinder.h"
#include "Platform/DirectoryRecorder.h"
#include "Platform/TempDir.h"
#include "Platform/DebugSymbol.h"
#include "Platform/Library.h"
#include "Platform/Quaternion.h"
#include "Platform/EulerAngles.h"
#include "Platform/Vector2.h"
#include "Platform/Vector3.h"
#include "Platform/Vector4.h"
#include "Platform/Matrix2.h"
#include "Platform/Matrix3.h"
#include "Platform/Matrix3x4.h"
#include "Platform/Matrix4.h"
#include "Platform/Matrix4Adjustor.h"
#include "Platform/OrientedBox2D.h"
#include "Platform/Triangle2D.h"
#include "Platform/Polygon2D.h"
#include "Platform/Box.h"
#include "Platform/AxisAlignedBox.h"
#include "Platform/Plane.h"
#include "Platform/Frustum.h"
#include "Platform/Triangle.h"
#include "Platform/Sphere.h"
#include "Platform/Ray.h"
#include "Platform/Viewport.h"
#include "Platform/Camera.h"
#include "Platform/Intersection.h"
#include "Platform/Camera2D.h"
#include "Platform/Transform2D.h"
#include "Platform/Transform3D.h"
#include "Platform/Serializer.h"
#include "Platform/DeferredProcessor.h"
#include "Platform/ValueEncoder.h"

namespace EGE
{

typedef Range< Vector3 >	Vector3Range;
typedef Range< Color >		ColorRange;

typedef Array< Color >		ColorArray;
typedef Array< Variable >	VariableArray;
typedef Array< Vector2 >	Vector2Array;
typedef Array< Vector3 >	Vector3Array;
typedef Array< Matrix2 >	Matrix2Array;
typedef Array< Matrix3 >	Matrix3Array;
typedef Array< Matrix3x4 >	Matrix3x4Array;
typedef Array< Matrix4 >	Matrix4Array;
typedef Array< Triangle >	TriangleArray;
typedef Array< Triangle2D > Triangle2DArray;

typedef Stack< Matrix3 >	Matrix3Stack;
typedef Stack< Matrix4 >	Matrix4Stack;

//----------------------------------------------------------------------------
// Type converter
//----------------------------------------------------------------------------

template< typename Type >
struct Type2Long
{
	const _int operator( ) ( const Type& element ) const
	{
		return (_int) element;
	}
};

template< typename Type >
struct Type2Dword
{
	const _dword operator( ) ( const Type& element ) const
	{
		return (_dword) element;
	}
};

template< typename Type >
struct Type2Float
{
	const _float operator( ) ( const Type& element ) const
	{
		return (_float) element;
	}
};

template< typename Type >
struct Type2Double
{
	const _double operator( ) ( const Type& element ) const
	{
		return (_double) element;
	}
};

template< typename Type >
struct Type2AStringPtr
{
	const AStringPtr operator( ) ( const Type& element ) const
	{
		return (AStringPtr) element;
	}
};

template< typename Type >
struct Type2UStringPtr
{
	const UStringPtr operator( ) ( const Type& element ) const
	{
		return (UStringPtr) element;
	}
};

template< typename Type >
struct Type2WStringPtr
{
	const WStringPtr operator( ) ( const Type& element ) const
	{
		return (WStringPtr) element;
	}
};

template< typename Type >
struct PtrType2Long
{
	const _int operator( ) ( const Type& element ) const
	{
		return (_int) *element;
	}
};

template< typename Type >
struct PtrType2Dword
{
	const _dword operator( ) ( const Type& element ) const
	{
		return (_dword) *element;
	}
};

template< typename Type >
struct PtrType2Qword
{
	const _qword operator( ) ( const Type& element ) const
	{
		return (_qword) *element;
	}
};

template< typename Type >
struct PtrType2Float
{
	const _float operator( ) ( const Type& element ) const
	{
		return (_float) *element;
	}
};

template< typename Type >
struct PtrType2Double
{
	const _double operator( ) ( const Type& element ) const
	{
		return (_double) *element;
	}
};

template< typename Type >
struct PtrType2AStringPtr
{
	const AStringPtr operator( ) ( const Type& element ) const
	{
		return (AStringPtr) *element;
	}
};

template< typename Type >
struct PtrType2UStringPtr
{
	const UStringPtr operator( ) ( const Type& element ) const
	{
		return (UStringPtr) *element;
	}
};

template< typename Type >
struct PtrType2WStringPtr
{
	const WStringPtr operator( ) ( const Type& element ) const
	{
		return (WStringPtr) *element;
	}
};

//----------------------------------------------------------------------------
// Specified function and class implementation
//----------------------------------------------------------------------------

template<>
struct Compare< AStringPtr > : public BinaryFunction< AStringPtr, AStringPtr >
{
	//!	Process compare operation.
	_int operator( ) ( const AStringPtr& v1, const AStringPtr& v2 ) const
	{
		return Platform::CompareString( v1.Str( ), v2.Str( ) );
	}
};

template<>
struct NotCompare< AStringPtr > : public BinaryFunction< AStringPtr, AStringPtr >
{
	//!	Process compare operation.
	_int operator( ) ( const AStringPtr& v1, const AStringPtr& v2 ) const
	{
		return Platform::CompareString( v1.Str( ), v2.Str( ) ) * -1;
	}
};

template<>
struct Compare< UStringPtr > : public BinaryFunction< UStringPtr, UStringPtr >
{
	//!	Process compare operation.
	_int operator( ) ( const UStringPtr& v1, const UStringPtr& v2 ) const
	{
		return Platform::CompareString( v1.Str( ), v2.Str( ) );
	}
};

template<>
struct NotCompare< UStringPtr > : public BinaryFunction< UStringPtr, UStringPtr >
{
	//!	Process compare operation.
	_int operator( ) ( const UStringPtr& v1, const UStringPtr& v2 ) const
	{
		return Platform::CompareString( v1.Str( ), v2.Str( ) ) * -1;
	}
};

template<>
struct Compare< WStringPtr > : public BinaryFunction< WStringPtr, WStringPtr >
{
	//!	Process compare operation.
	_int operator( ) ( const WStringPtr& v1, const WStringPtr& v2 ) const
	{
		return Platform::CompareString( v1.Str( ), v2.Str( ) );
	}
};

template<>
struct NotCompare< WStringPtr > : public BinaryFunction< WStringPtr, WStringPtr >
{
	//!	Process compare operation.
	_int operator( ) ( const WStringPtr& v1, const WStringPtr& v2 ) const
	{
		return Platform::CompareString( v1.Str( ), v2.Str( ) ) * -1;
	}
};

}

//----------------------------------------------------------------------------
// Platform Configure
//----------------------------------------------------------------------------

// Windows Platform
#if defined _PLATFORM_WINDOWS_
	
// IOS Platform
#elif defined _PLATFORM_IOS_

	// Only work for OBJ-C mode.
	#ifdef __OBJC__
		#include "Platform/OS/ios/NSPlatform.h"
	#endif

	#include "Platform/OS/ios/IOSPlatform.h"

// OSX Platform
#elif defined _PLATFORM_OSX_

// Android Platform
#elif defined _PLATFORM_ANDROID_

// Chrome Platform
#elif defined _PLATFORM_CHROME_

	#include "Platform/OS/chrome/ChromePPAPI.h"
	#include "Platform/OS/chrome/ChromePlatform.h"

#endif
