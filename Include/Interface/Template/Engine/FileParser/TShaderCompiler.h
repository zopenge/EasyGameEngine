//! @file     TShaderCompiler.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TShaderCompiler
//----------------------------------------------------------------------------

template< typename Type >
class TShaderCompiler : public Type
{
protected:
	//!	The compile info
	ShaderCompileConfigInfo	mCompileConfigInfo;

	//!	The generators
	IShaderCodeGeneratorRef	mCodeGenerators[ _SHADER_CODE_MAXNUMBER ];

protected:
	TShaderCompiler( );
	virtual ~TShaderCompiler( );

// IShaderCompiler Interface
public:
	virtual _void							SetCompileConfigInfo( const ShaderCompileConfigInfo& config ) override;
	virtual const ShaderCompileConfigInfo&	GetCompileConfigInfo( ) const override;

	virtual IShaderCodeGeneratorRef			GetCodeGenerator( _SHADER_CODE_TYPE type ) override;
};

//----------------------------------------------------------------------------
// TShaderCompiler Implementation
//----------------------------------------------------------------------------

template< typename Type >
TShaderCompiler< Type >::TShaderCompiler( )
{
}

template< typename Type >
TShaderCompiler< Type >::~TShaderCompiler( )
{

}

template< typename Type >
_void TShaderCompiler< Type >::SetCompileConfigInfo( const ShaderCompileConfigInfo& config )
{
	mCompileConfigInfo = config;
}

template< typename Type >
const ShaderCompileConfigInfo& TShaderCompiler< Type >::GetCompileConfigInfo( ) const
{
	return mCompileConfigInfo;
}

template< typename Type >
IShaderCodeGeneratorRef TShaderCompiler< Type >::GetCodeGenerator( _SHADER_CODE_TYPE type )
{
	if ( type >= _SHADER_CODE_MAXNUMBER )
		return _null;

	return mCodeGenerators[ type ];
}

}