//! @file     ShaderParser.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ShaderParser
//----------------------------------------------------------------------------

class ShaderParser
{
private:
	//!	The max level number
	enum { _MAX_LEVEL_NUMBER = 32 };

private:
	AString	mCode;

private:
	_ubool Load( AStringPtr code, _dword level );

public:
	ShaderParser( );
	~ShaderParser( );

public:
	//!	Load shader code.
	//!	@param		code	The shader code.
	//!	@return		True indicates success false indicates failure.
	_ubool Load( AStringPtr code );

	//! Get the shader code with expand all '#include' commands.
	//!	@param		none.
	//!	@return		The shader code.
	AStringPtr GetShaderCode( ) const;
};

//----------------------------------------------------------------------------
// ShaderParser Implementation
//----------------------------------------------------------------------------

}