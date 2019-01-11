//! @file		GraphicSerialization.h
//! @author		Deen
//! @copyright	...
//! @version	1.0.0.0
//! @date		2017/09/12

namespace EGE
{

_dword OnQueryEnumSamplerFilterEnumCallback( WStringPtr name );
WStringPtr OnQueryEnumSamplerFilterEnumCallback( _dword value );
_dword OnQueryEnumSamplerAddressModeEnumCallback( WStringPtr name );
WStringPtr OnQueryEnumSamplerAddressModeEnumCallback( _dword value );
_dword OnQueryEnumRasterizerFillModeEnumCallback( WStringPtr name );
WStringPtr OnQueryEnumRasterizerFillModeEnumCallback( _dword value );
_dword OnQueryEnumRasterizerCullModeEnumCallback( WStringPtr name );
WStringPtr OnQueryEnumRasterizerCullModeEnumCallback( _dword value );
_dword OnQueryEnumColorWriteMaskEnumCallback( WStringPtr name );
WStringPtr OnQueryEnumColorWriteMaskEnumCallback( _dword value );
_dword OnQueryEnumCompareFunctionEnumCallback( WStringPtr name );
WStringPtr OnQueryEnumCompareFunctionEnumCallback( _dword value );
_dword OnQueryEnumStencilOperationEnumCallback( WStringPtr name );
WStringPtr OnQueryEnumStencilOperationEnumCallback( _dword value );
_dword OnQueryEnumBlendFactorEnumCallback( WStringPtr name );
WStringPtr OnQueryEnumBlendFactorEnumCallback( _dword value );

}

