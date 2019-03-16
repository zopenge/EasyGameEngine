//! @file		EngineSerialization.h
//! @author		Deen
//! @copyright	...
//! @version	1.0.0.0
//! @date		2017/09/12

namespace EGE
{

_dword OnQueryEncodingEnumCallback( WStringPtr name );
WStringPtr OnQueryEncodingEnumCallback( _dword value );
_dword OnQueryPlatformTypeEnumCallback( WStringPtr name );
WStringPtr OnQueryPlatformTypeEnumCallback( _dword value );
_dword OnQueryAlignmentEnumCallback( WStringPtr name );
WStringPtr OnQueryAlignmentEnumCallback( _dword value );
_dword OnQueryAnimationModeEnumCallback( WStringPtr name );
WStringPtr OnQueryAnimationModeEnumCallback( _dword value );
_dword OnQueryAnimationDirectionEnumCallback( WStringPtr name );
WStringPtr OnQueryAnimationDirectionEnumCallback( _dword value );
_dword OnQueryEncryptionTypeEnumCallback( WStringPtr name );
WStringPtr OnQueryEncryptionTypeEnumCallback( _dword value );
_dword OnQueryEnumInterpolatorTypeEnumCallback( WStringPtr name );
WStringPtr OnQueryEnumInterpolatorTypeEnumCallback( _dword value );

}

