//! @file		EngineSerialization.cpp
//! @author		Deen
//! @copyright	...
//! @version	1.0.0.0
//! @date		2017/09/12

#include "EGEEngine.h"
namespace EGE
{

_dword OnQueryEncodingEnumCallback( WStringPtr name )
{
	if ( name == L"unknown" ) return _ENCODING_UNKNOWN;
	else if ( name == L"ansi" ) return _ENCODING_ANSI;
	else if ( name == L"utf-8" ) return _ENCODING_UTF8;
	else if ( name == L"utf-16" ) return _ENCODING_UTF16;

	EGE_ASSERT( 0 );
	return -1;
}
WStringPtr OnQueryEncodingEnumCallback( _dword value )
{
	switch ( value )
	{
		case _ENCODING_UNKNOWN: return L"unknown";
		case _ENCODING_ANSI: return L"ansi";
		case _ENCODING_UTF8: return L"utf-8";
		case _ENCODING_UTF16: return L"utf-16";
		default:
			break;
	}

	EGE_ASSERT( 0 );
	return L"";
}
_dword OnQueryPlatformTypeEnumCallback( WStringPtr name )
{
	if ( name == L"Unknown" ) return _PLATFORM_TYPE_UNKNOWN;
	else if ( name == L"Windows" ) return _PLATFORM_TYPE_WINDOWS;
	else if ( name == L"Android" ) return _PLATFORM_TYPE_ANDROID;
	else if ( name == L"IOS" ) return _PLATFORM_TYPE_IOS;
	else if ( name == L"Chrome" ) return _PLATFORM_TYPE_CHROME;

	EGE_ASSERT( 0 );
	return -1;
}
WStringPtr OnQueryPlatformTypeEnumCallback( _dword value )
{
	switch ( value )
	{
		case _PLATFORM_TYPE_UNKNOWN: return L"Unknown";
		case _PLATFORM_TYPE_WINDOWS: return L"Windows";
		case _PLATFORM_TYPE_ANDROID: return L"Android";
		case _PLATFORM_TYPE_IOS: return L"IOS";
		case _PLATFORM_TYPE_CHROME: return L"Chrome";
		default:
			break;
	}

	EGE_ASSERT( 0 );
	return L"";
}
_dword OnQueryAlignmentEnumCallback( WStringPtr name )
{
	if ( name == L"NONE" ) return _ALIGNMENT_NONE;
	else if ( name == L"LEFT" ) return _ALIGNMENT_LEFT;
	else if ( name == L"TOP" ) return _ALIGNMENT_TOP;
	else if ( name == L"RIGHT" ) return _ALIGNMENT_RIGHT;
	else if ( name == L"BOTTOM" ) return _ALIGNMENT_BOTTOM;
	else if ( name == L"HORZ_JUSTIFIED" ) return _ALIGNMENT_HORZ_JUSTIFIED;
	else if ( name == L"VERT_JUSTIFIED" ) return _ALIGNMENT_VERT_JUSTIFIED;
	else if ( name == L"HORZ_CENTER" ) return _ALIGNMENT_HORZ_CENTER;
	else if ( name == L"VERT_CENTER" ) return _ALIGNMENT_VERT_CENTER;
	else if ( name == L"LT" ) return _ALIGNMENT_LEFT_TOP;
	else if ( name == L"CENTER" ) return _ALIGNMENT_CENTER;

	EGE_ASSERT( 0 );
	return -1;
}
WStringPtr OnQueryAlignmentEnumCallback( _dword value )
{
	switch ( value )
	{
		case _ALIGNMENT_NONE: return L"NONE";
		case _ALIGNMENT_LEFT: return L"LEFT";
		case _ALIGNMENT_TOP: return L"TOP";
		case _ALIGNMENT_RIGHT: return L"RIGHT";
		case _ALIGNMENT_BOTTOM: return L"BOTTOM";
		case _ALIGNMENT_HORZ_JUSTIFIED: return L"HORZ_JUSTIFIED";
		case _ALIGNMENT_VERT_JUSTIFIED: return L"VERT_JUSTIFIED";
		case _ALIGNMENT_HORZ_CENTER: return L"HORZ_CENTER";
		case _ALIGNMENT_VERT_CENTER: return L"VERT_CENTER";
		case _ALIGNMENT_LEFT_TOP: return L"LT";
		case _ALIGNMENT_CENTER: return L"CENTER";
		default:
			break;
	}

	EGE_ASSERT( 0 );
	return L"";
}
_dword OnQueryAnimationModeEnumCallback( WStringPtr name )
{
	if ( name == L"ONCE" ) return _ANIMATION_MODE_ONCE;
	else if ( name == L"REPEAT" ) return _ANIMATION_MODE_REPEAT;
	else if ( name == L"PINGPONG" ) return _ANIMATION_MODE_PINGPONG;

	EGE_ASSERT( 0 );
	return -1;
}
WStringPtr OnQueryAnimationModeEnumCallback( _dword value )
{
	switch ( value )
	{
		case _ANIMATION_MODE_ONCE: return L"ONCE";
		case _ANIMATION_MODE_REPEAT: return L"REPEAT";
		case _ANIMATION_MODE_PINGPONG: return L"PINGPONG";
		default:
			break;
	}

	EGE_ASSERT( 0 );
	return L"";
}
_dword OnQueryAnimationDirectionEnumCallback( WStringPtr name )
{
	if ( name == L"FORWARD" ) return _ANIMATION_DIRECTION_FORWARD;
	else if ( name == L"BACKWARD" ) return _ANIMATION_DIRECTION_BACKWARD;

	EGE_ASSERT( 0 );
	return -1;
}
WStringPtr OnQueryAnimationDirectionEnumCallback( _dword value )
{
	switch ( value )
	{
		case _ANIMATION_DIRECTION_FORWARD: return L"FORWARD";
		case _ANIMATION_DIRECTION_BACKWARD: return L"BACKWARD";
		default:
			break;
	}

	EGE_ASSERT( 0 );
	return L"";
}
_dword OnQueryEncryptionTypeEnumCallback( WStringPtr name )
{
	if ( name == L"UNKNOWN" ) return _ENCRYPTION_UNKNOWN;
	else if ( name == L"DES" ) return _ENCRYPTION_DES;
	else if ( name == L"AES" ) return _ENCRYPTION_AES;

	EGE_ASSERT( 0 );
	return -1;
}
WStringPtr OnQueryEncryptionTypeEnumCallback( _dword value )
{
	switch ( value )
	{
		case _ENCRYPTION_UNKNOWN: return L"UNKNOWN";
		case _ENCRYPTION_DES: return L"DES";
		case _ENCRYPTION_AES: return L"AES";
		default:
			break;
	}

	EGE_ASSERT( 0 );
	return L"";
}
_dword OnQueryEnumInterpolatorTypeEnumCallback( WStringPtr name )
{
	if ( name == L"CURRENT" ) return _INTERPOLATOR_CURRENT;
	else if ( name == L"NEXT" ) return _INTERPOLATOR_NEXT;
	else if ( name == L"MIDDLE" ) return _INTERPOLATOR_MIDDLE;
	else if ( name == L"LINEAR" ) return _INTERPOLATOR_LINEAR;
	else if ( name == L"SINE_IN" ) return _INTERPOLATOR_SINE_IN;
	else if ( name == L"SINE_OUT" ) return _INTERPOLATOR_SINE_OUT;
	else if ( name == L"SINE_IN_OUT" ) return _INTERPOLATOR_SINE_INOUT;
	else if ( name == L"SINE_OUT_IN" ) return _INTERPOLATOR_SINE_OUTIN;
	else if ( name == L"QUAD_IN" ) return _INTERPOLATOR_QUAD_IN;
	else if ( name == L"QUAD_OUT" ) return _INTERPOLATOR_QUAD_OUT;
	else if ( name == L"QUAD_IN_OUT" ) return _INTERPOLATOR_QUAD_INOUT;
	else if ( name == L"QUAD_OUT_IN" ) return _INTERPOLATOR_QUAD_OUTIN;
	else if ( name == L"CUBIC_IN" ) return _INTERPOLATOR_CUBIC_IN;
	else if ( name == L"CUBIC_OUT" ) return _INTERPOLATOR_CUBIC_OUT;
	else if ( name == L"CUBIC_IN_OUT" ) return _INTERPOLATOR_CUBIC_INOUT;
	else if ( name == L"CUBIC_OUT_IN" ) return _INTERPOLATOR_CUBIC_OUTIN;
	else if ( name == L"QUART_IN" ) return _INTERPOLATOR_QUART_IN;
	else if ( name == L"QUART_OUT" ) return _INTERPOLATOR_QUART_OUT;
	else if ( name == L"QUART_IN_OUT" ) return _INTERPOLATOR_QUART_INOUT;
	else if ( name == L"QUART_OUT_IN" ) return _INTERPOLATOR_QUART_OUTIN;
	else if ( name == L"QUINT_IN" ) return _INTERPOLATOR_QUINT_IN;
	else if ( name == L"QUINT_OUT" ) return _INTERPOLATOR_QUINT_OUT;
	else if ( name == L"QUINT_IN_OUT" ) return _INTERPOLATOR_QUINT_INOUT;
	else if ( name == L"QUINT_OUT_IN" ) return _INTERPOLATOR_QUINT_OUTIN;
	else if ( name == L"EXPO_IN" ) return _INTERPOLATOR_EXPO_IN;
	else if ( name == L"EXPO_OUT" ) return _INTERPOLATOR_EXPO_OUT;
	else if ( name == L"EXPO_INOUT" ) return _INTERPOLATOR_EXPO_INOUT;
	else if ( name == L"EXPO_OUTIN" ) return _INTERPOLATOR_EXPO_OUTIN;
	else if ( name == L"CIRC_IN" ) return _INTERPOLATOR_CIRC_IN;
	else if ( name == L"CIRC_OUT" ) return _INTERPOLATOR_CIRC_OUT;
	else if ( name == L"CIRC_INOUT" ) return _INTERPOLATOR_CIRC_INOUT;
	else if ( name == L"CIRC_OUTIN" ) return _INTERPOLATOR_CIRC_OUTIN;
	else if ( name == L"ELASTIC_IN" ) return _INTERPOLATOR_ELASTIC_IN;
	else if ( name == L"ELASTIC_OUT" ) return _INTERPOLATOR_ELASTIC_OUT;
	else if ( name == L"ELASTIC_INOUT" ) return _INTERPOLATOR_ELASTIC_INOUT;
	else if ( name == L"ELASTIC_OUTIN" ) return _INTERPOLATOR_ELASTIC_OUTIN;
	else if ( name == L"BACK_IN" ) return _INTERPOLATOR_BACK_IN;
	else if ( name == L"BACK_OUT" ) return _INTERPOLATOR_BACK_OUT;
	else if ( name == L"BACK_INOUT" ) return _INTERPOLATOR_BACK_INOUT;
	else if ( name == L"BACK_OUTIN" ) return _INTERPOLATOR_BACK_OUTIN;
	else if ( name == L"BOUNCE_IN" ) return _INTERPOLATOR_BOUNCE_IN;
	else if ( name == L"BOUNCE_OUT" ) return _INTERPOLATOR_BOUNCE_OUT;
	else if ( name == L"BOUNCE_INOUT" ) return _INTERPOLATOR_BOUNCE_INOUT;
	else if ( name == L"BOUNCE_OUTIN" ) return _INTERPOLATOR_BOUNCE_OUTIN;

	EGE_ASSERT( 0 );
	return -1;
}
WStringPtr OnQueryEnumInterpolatorTypeEnumCallback( _dword value )
{
	switch ( value )
	{
		case _INTERPOLATOR_CURRENT: return L"CURRENT";
		case _INTERPOLATOR_NEXT: return L"NEXT";
		case _INTERPOLATOR_MIDDLE: return L"MIDDLE";
		case _INTERPOLATOR_LINEAR: return L"LINEAR";
		case _INTERPOLATOR_SINE_IN: return L"SINE_IN";
		case _INTERPOLATOR_SINE_OUT: return L"SINE_OUT";
		case _INTERPOLATOR_SINE_INOUT: return L"SINE_IN_OUT";
		case _INTERPOLATOR_SINE_OUTIN: return L"SINE_OUT_IN";
		case _INTERPOLATOR_QUAD_IN: return L"QUAD_IN";
		case _INTERPOLATOR_QUAD_OUT: return L"QUAD_OUT";
		case _INTERPOLATOR_QUAD_INOUT: return L"QUAD_IN_OUT";
		case _INTERPOLATOR_QUAD_OUTIN: return L"QUAD_OUT_IN";
		case _INTERPOLATOR_CUBIC_IN: return L"CUBIC_IN";
		case _INTERPOLATOR_CUBIC_OUT: return L"CUBIC_OUT";
		case _INTERPOLATOR_CUBIC_INOUT: return L"CUBIC_IN_OUT";
		case _INTERPOLATOR_CUBIC_OUTIN: return L"CUBIC_OUT_IN";
		case _INTERPOLATOR_QUART_IN: return L"QUART_IN";
		case _INTERPOLATOR_QUART_OUT: return L"QUART_OUT";
		case _INTERPOLATOR_QUART_INOUT: return L"QUART_IN_OUT";
		case _INTERPOLATOR_QUART_OUTIN: return L"QUART_OUT_IN";
		case _INTERPOLATOR_QUINT_IN: return L"QUINT_IN";
		case _INTERPOLATOR_QUINT_OUT: return L"QUINT_OUT";
		case _INTERPOLATOR_QUINT_INOUT: return L"QUINT_IN_OUT";
		case _INTERPOLATOR_QUINT_OUTIN: return L"QUINT_OUT_IN";
		case _INTERPOLATOR_EXPO_IN: return L"EXPO_IN";
		case _INTERPOLATOR_EXPO_OUT: return L"EXPO_OUT";
		case _INTERPOLATOR_EXPO_INOUT: return L"EXPO_INOUT";
		case _INTERPOLATOR_EXPO_OUTIN: return L"EXPO_OUTIN";
		case _INTERPOLATOR_CIRC_IN: return L"CIRC_IN";
		case _INTERPOLATOR_CIRC_OUT: return L"CIRC_OUT";
		case _INTERPOLATOR_CIRC_INOUT: return L"CIRC_INOUT";
		case _INTERPOLATOR_CIRC_OUTIN: return L"CIRC_OUTIN";
		case _INTERPOLATOR_ELASTIC_IN: return L"ELASTIC_IN";
		case _INTERPOLATOR_ELASTIC_OUT: return L"ELASTIC_OUT";
		case _INTERPOLATOR_ELASTIC_INOUT: return L"ELASTIC_INOUT";
		case _INTERPOLATOR_ELASTIC_OUTIN: return L"ELASTIC_OUTIN";
		case _INTERPOLATOR_BACK_IN: return L"BACK_IN";
		case _INTERPOLATOR_BACK_OUT: return L"BACK_OUT";
		case _INTERPOLATOR_BACK_INOUT: return L"BACK_INOUT";
		case _INTERPOLATOR_BACK_OUTIN: return L"BACK_OUTIN";
		case _INTERPOLATOR_BOUNCE_IN: return L"BOUNCE_IN";
		case _INTERPOLATOR_BOUNCE_OUT: return L"BOUNCE_OUT";
		case _INTERPOLATOR_BOUNCE_INOUT: return L"BOUNCE_INOUT";
		case _INTERPOLATOR_BOUNCE_OUTIN: return L"BOUNCE_OUTIN";
		default:
			break;
	}

	EGE_ASSERT( 0 );
	return L"";
}

}

