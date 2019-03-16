//! @file     IShaderFile.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IShaderCodeGenerator
//----------------------------------------------------------------------------

class IShaderCodeGenerator : public IObject
{
public:
	//!	Get the shader code type.
	//! @param		none.
	//! @return		The shader code type.
	virtual _SHADER_CODE_TYPE GetCodeType( ) const PURE;

	//!	Get default version.
	//! @param		none.
	//! @return		The version info.
	virtual Version GetDefaultVersion( ) const PURE;

	//!	Get main entry string.
	//! @param		none.
	//! @return		The main entry string.
	virtual UStringPtr GetMainEntryString( ) const PURE;

	//!	Generate version macro definition string.
	//!	@param		version		The version info.
	//!	@return		text		The version macro definition string.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GenerateVersionMacroString( const Version& version, UString& text ) const PURE;
	//!	Generate variable declaration string.
	//! @param		is_embedded_system	True indicate it's embedded system.
	//! @param		var_decl			The variable declaration info.
	//! @param		text				The code text.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GenerateVarDeclString( _ubool is_embedded_system, const ShaderVarDeclInfo& var_decl, UString& text ) const PURE;
	//!	Generate variable declaration string.
	//! @param		is_embedded_system	True indicate it's embedded system.
	//! @param		node				The serializable node.
	//! @param		text				The code text.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GenerateVarDeclString( _ubool is_embedded_system, ISerializableNode* node, UString& text ) const PURE;
	//!	Generate structure declaration string.
	//! @param		is_embedded_system	True indicate it's embedded system.
	//! @param		node				The serializable node.
	//! @param		text				The code text.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GenerateStructDeclString( _ubool is_embedded_system, ISerializableNode* node, UString& text ) const PURE;
};

//----------------------------------------------------------------------------
// IShaderCompiler
//----------------------------------------------------------------------------

template< typename Type >
class IShaderCompiler : public Type
{
public:
	//!	Set the compile config.
	//! @param		config	The compile config info.
	//! @return		none.
	virtual _void SetCompileConfigInfo( const ShaderCompileConfigInfo& config ) PURE;
	//!	Get the compile config.
	//! @param		none.
	//! @return		The compile config info.
	virtual const ShaderCompileConfigInfo& GetCompileConfigInfo( ) const PURE;

	//!	Get the shader generator.
	//!	@param		type	The shader code type.
	//!	@return		The shader generator.
	virtual IShaderCodeGeneratorRef GetCodeGenerator( _SHADER_CODE_TYPE type ) PURE;
};

//----------------------------------------------------------------------------
// IShaderFile
//----------------------------------------------------------------------------

class IShaderFile : public IShaderCompiler< IBaseFile >
{
public:
	//!	Process include command.
	//!	@param		filename	The include file name.
	//!	@return		config		The shader config.
	//!	@return		content		The file content.
	//!	@param		parameters	The user defined parameters.
	//! @return		True indicates success, false indicates failure.
	typedef _ubool (*OnProcessIncludeCommand)( UStringPtr filename, const ShaderCompileConfigInfo& config, UString& content, const QwordParameters2& parameters );

public:
	//!	Set the process include command callback function.
	//!	@param		funcpointer	The function pointer.
	//!	@param		parameters	The user defined parameters.
	//!	@return		none.
	virtual _void SetProcessIncludeCommandFunc( OnProcessIncludeCommand funcpointer, const QwordParameters2& parameters ) PURE;

	//!	Get the render methods name list.
	//!	@param		none.
	//!	@return		The render methods name list.
	virtual UStringArray GetRenderMethodNameList( ) const PURE;
	//!	Get the render methods name list by excluding include files.
	//!	@param		none.
	//!	@return		The render methods name list.
	virtual UStringArray GetRenderMethodNameListByExcludingIncludeNodes( ) const PURE;

	//!	Get the version.
	//! @param		none.
	//! @return		The version info.
	virtual const Version& GetVersion( ) const PURE;
	//!	Get the embedded version.
	//! @param		none.
	//! @return		The embedded version info.
	virtual const Version& GetEmbeddedVersion( ) const PURE;

	//!	Generate shader code (UTF-8).
	//! @param		name		The render method name.
	//! @param		text		The code text.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GenerateCodeU( UStringPtr name, UString& text ) const PURE;
};

}