//! @file     TShaderCodeGenerator.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TShaderCodeGenerator
//----------------------------------------------------------------------------

template< typename Type >
class TShaderCodeGenerator : public Type
{
protected:
	//!	Translate the shader code type name from code type.
	const _chara* TranslateShaderCodeTypeNameU( ) const;

protected:
	//!	Get the stride of variable in bytes.
	virtual _dword GetVariableStride( UStringPtr type ) const PURE;

protected:
	TShaderCodeGenerator( );
	virtual ~TShaderCodeGenerator( );

// IShaderCodeGenerator Interface
public:
};

//----------------------------------------------------------------------------
// TShaderCodeGenerator Implementation
//----------------------------------------------------------------------------

template< typename Type >
TShaderCodeGenerator< Type >::TShaderCodeGenerator( )
{
}

template< typename Type >
TShaderCodeGenerator< Type >::~TShaderCodeGenerator( )
{
}

template< typename Type >
const _chara* TShaderCodeGenerator< Type >::TranslateShaderCodeTypeNameU( ) const
{
	switch ( this->GetCodeType( ) )
	{
		case _SHADER_CODE_VS: return "VertexShader";
		case _SHADER_CODE_PS: return "FragmentShader";
		default:
			return "UnknownShader";
	}
}

}