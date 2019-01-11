//! @file		GraphicSerialization.cpp
//! @author		Deen
//! @copyright	...
//! @version	1.0.0.0
//! @date		2017/09/12

#include "EGEGraphic.h"
namespace EGE
{

_dword OnQueryEnumSamplerFilterEnumCallback( WStringPtr name )
{
	if ( name == L"NEAREST" ) return _SF_NEAREST;
	else if ( name == L"LINEAR" ) return _SF_LINEAR;

	EGE_ASSERT( 0 );
	return -1;
}
WStringPtr OnQueryEnumSamplerFilterEnumCallback( _dword value )
{
	switch ( value )
	{
		case _SF_NEAREST: return L"NEAREST";
		case _SF_LINEAR: return L"LINEAR";
		default:
			break;
	}

	EGE_ASSERT( 0 );
	return L"";
}
_dword OnQueryEnumSamplerAddressModeEnumCallback( WStringPtr name )
{
	if ( name == L"WRAP" ) return _SAM_WRAP;
	else if ( name == L"CLAMP" ) return _SAM_CLAMP;
	else if ( name == L"CLAMP_TO_EDGE" ) return _SAM_CLAMP_TO_EDGE;
	else if ( name == L"MIRROR" ) return _SAM_MIRROR;
	else if ( name == L"REPEAT" ) return _SAM_REPEAT;

	EGE_ASSERT( 0 );
	return -1;
}
WStringPtr OnQueryEnumSamplerAddressModeEnumCallback( _dword value )
{
	switch ( value )
	{
		case _SAM_WRAP: return L"WRAP";
		case _SAM_CLAMP: return L"CLAMP";
		case _SAM_CLAMP_TO_EDGE: return L"CLAMP_TO_EDGE";
		case _SAM_MIRROR: return L"MIRROR";
		case _SAM_REPEAT: return L"REPEAT";
		default:
			break;
	}

	EGE_ASSERT( 0 );
	return L"";
}
_dword OnQueryEnumRasterizerFillModeEnumCallback( WStringPtr name )
{
	if ( name == L"POINT" ) return _RFM_POINT;
	else if ( name == L"WIREFRAME" ) return _RFM_WIREFRAME;
	else if ( name == L"SOLID" ) return _RFM_SOLID;

	EGE_ASSERT( 0 );
	return -1;
}
WStringPtr OnQueryEnumRasterizerFillModeEnumCallback( _dword value )
{
	switch ( value )
	{
		case _RFM_POINT: return L"POINT";
		case _RFM_WIREFRAME: return L"WIREFRAME";
		case _RFM_SOLID: return L"SOLID";
		default:
			break;
	}

	EGE_ASSERT( 0 );
	return L"";
}
_dword OnQueryEnumRasterizerCullModeEnumCallback( WStringPtr name )
{
	if ( name == L"NONE" ) return _RCM_NONE;
	else if ( name == L"CW" ) return _RCM_CW;
	else if ( name == L"CCW" ) return _RCM_CCW;

	EGE_ASSERT( 0 );
	return -1;
}
WStringPtr OnQueryEnumRasterizerCullModeEnumCallback( _dword value )
{
	switch ( value )
	{
		case _RCM_NONE: return L"NONE";
		case _RCM_CW: return L"CW";
		case _RCM_CCW: return L"CCW";
		default:
			break;
	}

	EGE_ASSERT( 0 );
	return L"";
}
_dword OnQueryEnumColorWriteMaskEnumCallback( WStringPtr name )
{
	if ( name == L"RED" ) return _CWM_RED;
	else if ( name == L"GREEN" ) return _CWM_GREEN;
	else if ( name == L"BLUE" ) return _CWM_BLUE;
	else if ( name == L"ALPHA" ) return _CWM_ALPHA;
	else if ( name == L"RGB" ) return _CWM_RGB;
	else if ( name == L"RGBA" ) return _CWM_RGBA;

	EGE_ASSERT( 0 );
	return -1;
}
WStringPtr OnQueryEnumColorWriteMaskEnumCallback( _dword value )
{
	switch ( value )
	{
		case _CWM_RED: return L"RED";
		case _CWM_GREEN: return L"GREEN";
		case _CWM_BLUE: return L"BLUE";
		case _CWM_ALPHA: return L"ALPHA";
		case _CWM_RGB: return L"RGB";
		case _CWM_RGBA: return L"RGBA";
		default:
			break;
	}

	EGE_ASSERT( 0 );
	return L"";
}
_dword OnQueryEnumCompareFunctionEnumCallback( WStringPtr name )
{
	if ( name == L"LESS" ) return _CF_LESS;
	else if ( name == L"LESS_EQUAL" ) return _CF_LESS_EQUAL;
	else if ( name == L"GREATER" ) return _CF_GREATER;
	else if ( name == L"GREATER_EQUAL" ) return _CF_GREATER_EQUAL;
	else if ( name == L"EQUAL" ) return _CF_EQUAL;
	else if ( name == L"NOT_EQUAL" ) return _CF_NOT_EQUAL;
	else if ( name == L"NEVER" ) return _CF_NEVER;
	else if ( name == L"ALWAYS" ) return _CF_ALWAYS;

	EGE_ASSERT( 0 );
	return -1;
}
WStringPtr OnQueryEnumCompareFunctionEnumCallback( _dword value )
{
	switch ( value )
	{
		case _CF_LESS: return L"LESS";
		case _CF_LESS_EQUAL: return L"LESS_EQUAL";
		case _CF_GREATER: return L"GREATER";
		case _CF_GREATER_EQUAL: return L"GREATER_EQUAL";
		case _CF_EQUAL: return L"EQUAL";
		case _CF_NOT_EQUAL: return L"NOT_EQUAL";
		case _CF_NEVER: return L"NEVER";
		case _CF_ALWAYS: return L"ALWAYS";
		default:
			break;
	}

	EGE_ASSERT( 0 );
	return L"";
}
_dword OnQueryEnumStencilOperationEnumCallback( WStringPtr name )
{
	if ( name == L"KEEP" ) return _SO_KEEP;
	else if ( name == L"ZERO" ) return _SO_ZERO;
	else if ( name == L"REPLACE" ) return _SO_REPLACE;
	else if ( name == L"SATURATED_INCREMENT" ) return _SO_SATURATED_INCREMENT;
	else if ( name == L"SATURATED_DECREMENT" ) return _SO_SATURATED_DECREMENT;
	else if ( name == L"INVERT" ) return _SO_INVERT;
	else if ( name == L"INCREMENT" ) return _SO_INCREMENT;
	else if ( name == L"DECREMENT" ) return _SO_DECREMENT;

	EGE_ASSERT( 0 );
	return -1;
}
WStringPtr OnQueryEnumStencilOperationEnumCallback( _dword value )
{
	switch ( value )
	{
		case _SO_KEEP: return L"KEEP";
		case _SO_ZERO: return L"ZERO";
		case _SO_REPLACE: return L"REPLACE";
		case _SO_SATURATED_INCREMENT: return L"SATURATED_INCREMENT";
		case _SO_SATURATED_DECREMENT: return L"SATURATED_DECREMENT";
		case _SO_INVERT: return L"INVERT";
		case _SO_INCREMENT: return L"INCREMENT";
		case _SO_DECREMENT: return L"DECREMENT";
		default:
			break;
	}

	EGE_ASSERT( 0 );
	return L"";
}
_dword OnQueryEnumBlendFactorEnumCallback( WStringPtr name )
{
	if ( name == L"ZERO" ) return _BF_ZERO;
	else if ( name == L"ONE" ) return _BF_ONE;
	else if ( name == L"SOURCE_COLOR" ) return _BF_SOURCE_COLOR;
	else if ( name == L"INVERSE_SOURCE_COLOR" ) return _BF_INVERSE_SOURCE_COLOR;
	else if ( name == L"SOURCE_ALPHA" ) return _BF_SOURCE_ALPHA;
	else if ( name == L"INVERSE_SOURCE_ALPHA" ) return _BF_INVERSE_SOURCE_ALPHA;
	else if ( name == L"DEST_ALPHA" ) return _BF_DEST_ALPHA;
	else if ( name == L"INVERSE_DEST_ALPHA" ) return _BF_INVERSE_DEST_ALPHA;
	else if ( name == L"DEST_COLOR" ) return _BF_DEST_COLOR;
	else if ( name == L"INVERSE_DEST_COLOR" ) return _BF_INVERSE_DEST_COLOR;

	EGE_ASSERT( 0 );
	return -1;
}
WStringPtr OnQueryEnumBlendFactorEnumCallback( _dword value )
{
	switch ( value )
	{
		case _BF_ZERO: return L"ZERO";
		case _BF_ONE: return L"ONE";
		case _BF_SOURCE_COLOR: return L"SOURCE_COLOR";
		case _BF_INVERSE_SOURCE_COLOR: return L"INVERSE_SOURCE_COLOR";
		case _BF_SOURCE_ALPHA: return L"SOURCE_ALPHA";
		case _BF_INVERSE_SOURCE_ALPHA: return L"INVERSE_SOURCE_ALPHA";
		case _BF_DEST_ALPHA: return L"DEST_ALPHA";
		case _BF_INVERSE_DEST_ALPHA: return L"INVERSE_DEST_ALPHA";
		case _BF_DEST_COLOR: return L"DEST_COLOR";
		case _BF_INVERSE_DEST_COLOR: return L"INVERSE_DEST_COLOR";
		default:
			break;
	}

	EGE_ASSERT( 0 );
	return L"";
}

}

