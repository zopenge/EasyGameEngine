//! @file     ShaderFile.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// VSCodeGLSLGenerator
//----------------------------------------------------------------------------

class VSCodeGLSLGenerator : public TShaderCodeGLSLGenerator< TObject< IShaderCodeGenerator > >
{
private:
	typedef TShaderCodeGLSLGenerator< TObject< IShaderCodeGenerator > > BaseClass;

public:
	VSCodeGLSLGenerator( );
	virtual ~VSCodeGLSLGenerator( );

// IShaderCodeGenerator Interface
public:
	virtual _SHADER_CODE_TYPE	GetCodeType( ) const override;

	virtual _ubool				GenerateVarDeclString( _ubool is_embedded_system, const ShaderVarDeclInfo& var_decl, UString& text ) const override;
};

//----------------------------------------------------------------------------
// PSCodeGLSLGenerator
//----------------------------------------------------------------------------

class PSCodeGLSLGenerator : public TShaderCodeGLSLGenerator< TObject< IShaderCodeGenerator > >
{
private:
	typedef TShaderCodeGLSLGenerator< TObject< IShaderCodeGenerator > > BaseClass;

public:
	PSCodeGLSLGenerator( );
	virtual ~PSCodeGLSLGenerator( );

// IShaderCodeGenerator Interface
public:
	virtual _SHADER_CODE_TYPE	GetCodeType( ) const override;

	virtual _ubool				GenerateVarDeclString( _ubool is_embedded_system, const ShaderVarDeclInfo& var_decl, UString& text ) const override;
};

//----------------------------------------------------------------------------
// ShaderFile
//----------------------------------------------------------------------------

class ShaderFile : public TShaderCompiler< INTERFACE_BASEFILE_IMPL( IShaderFile ) >
{
private:
	typedef TShaderCompiler< INTERFACE_BASEFILE_IMPL( IShaderFile ) > BaseClass;

private:
	typedef CallbackFunc< OnProcessIncludeCommand, _ubool, QwordParameters2 > ProcessIncludeCommandFunc;

private:
	//!	The variable declarations
	typedef Array< ShaderVarDeclInfo > VarDeclInfoArray;

	//!	The macro info
	struct MacroInfo
	{
		_ubool			mIsVarying;
		UString			mPrecision;

		UString			mType;
		UString			mDefaultValue;
		UString			mCode;

		UStringArray	mInArgs;
		UStringArray	mOutArgs;

		MacroInfo( )
		{
			mIsVarying	= _false;
		}
	};
	typedef Map< MacroInfo, UString > MacroInfoMap;

	//!	The technique info
	struct TechniqueInfo
	{
		UString	mVSResidentCode;
		UString	mVSFinishCode;
	};

	//!	The render method info
	struct RenderMethodInfo : public TechniqueInfo
	{
		_ubool						mFromIncludeNode;
		UString						mVSCode;
		UString						mPSCode;
		const IShaderCodeGenerator*	mVSCodeGenerator;
		const IShaderCodeGenerator*	mPSCodeGenerator;
		ISerializableNodeRef		mRenderStats;

		//!	The external macros to override default macros
		MacroInfoMap				mExternalMacros;

		RenderMethodInfo( )
		{
			mFromIncludeNode	= _false;
			mVSCodeGenerator	= _null;
			mPSCodeGenerator	= _null;
		}
	};
	typedef Map< RenderMethodInfo, UString > RenderMethodInfoMap;

	//!	The varying variable info
	struct VaryingVarInfo : public ShaderVarDeclInfo
	{
		UString	mExpandCode;
	};
	typedef Array< VaryingVarInfo > VaryingVarInfoArray;

private:
	//!	The version
	Version						mVersion;
	//!	The embedded version
	Version						mEmbeddedVersion;

	//!	The serializable root node
	ISerializableNodeRef		mRootNode;
	//!	The variable declarations
	VarDeclInfoArray			mVarDecls;
	//!	The technique info
	TechniqueInfo				mTechniqueInfo;
	//!	The macros
	MacroInfoMap				mMacros;
	//!	The render methods
	RenderMethodInfoMap			mRenderMethods;

	//!	The callback functions
	ProcessIncludeCommandFunc	mProcessIncludeCommandFunc;

private:
	//!	Check whether has varying variable.
	static _ubool HasVaryingVariable( const VaryingVarInfoArray& vars, UStringPtr var_name );
	//!	Fix varying variable by checking depend.
	static _ubool FixVaryingVar( VaryingVarInfoArray& vars );

private:
	//!	Get the macro info.
	const MacroInfo* GetMacroInfo( const MacroInfoMap& external_macros, UStringPtr macro_name ) const;

	//!	Parse the macro input/output arguments.
	_void ParseMacroArguments( ISerializableNode* macro_node, WStringPtr prefix_name, UStringArray& arguments ) const;
	//!	Parse the macro info.
	_void ParseMacroInfo( ISerializableNode* macro_node, MacroInfo& macro_info ) const;
	//!	Parse the variable declaration info.
	_void ParseVarDeclInfo( ISerializableNode* var_decl_node, ShaderVarDeclInfo& var_decl_info ) const;

	//!	Import include nodes.
	_ubool ImportIncludeNodes( ISerializableNode* shader_node );
	//!	Import render method node.
	_ubool ImportRenderMethodNode( ISerializableNode* render_method_node, _ubool from_include_node );
	//!	Import technique nodes.
	_ubool ImportTechniqueNodes( ISerializableNode* technique_node, _ubool from_include_node );

	//!	Get the first macro text.
	_ubool GetFirstMacroText( const UString& text, UString& macro_text ) const;

	//!	Replace optional section text.
	_ubool ReplaceOptionalSectionText( _ubool is_embedded_system, UString& text ) const;
	//!	Replace macro arguments.
	_void ReplaceMacroArguments( const MacroInfo* macro_info, const UStringArray& arguments, UString& text ) const;
	//!	Replace macro text.
	_ubool ReplaceMacroText( const MacroInfo* macro_info, UStringPtr macro_name, UStringPtr arguments_text, _ubool is_embedded_system, UString& text, VaryingVarInfoArray& varying_vars ) const;
	//!	Replace macros text.
	_ubool ReplaceMacrosText( _ubool is_embedded_system, UString& text, VaryingVarInfoArray& varying_vars, const MacroInfoMap& external_macros ) const;

	//!	Generate code text.
	_ubool GenerateCodeText( const MacroInfoMap& external_macros, UStringPtr code, const IShaderCodeGenerator* code_generator, UString& text, VaryingVarInfoArray& varying_vars, _ubool use_default_value, _ubool is_embedded_system, UString& version_text ) const;
	//!	Generate VS code text.
	_ubool GenerateVSCodeText( const RenderMethodInfo* render_method, _ubool is_embedded_system, UString& text, VaryingVarInfoArray& varying_vars, UString& version_text ) const;
	//!	Generate PS code text.
	_ubool GeneratePSCodeText( const RenderMethodInfo* render_method, _ubool is_embedded_system, UString& text, VaryingVarInfoArray& varying_vars, UString& version_text ) const;

	//!	Insert VS and PS XML node.
	_ubool InsertVSAndPSXMLNode( const RenderMethodInfo* render_method, IMarkupLangElement* root, WStringPtr vs_node_name, WStringPtr ps_node_name, _ubool is_embedded_system ) const;

public:
	ShaderFile( );
	virtual ~ShaderFile( );

public:
	//!	Initialize.
	_ubool Initialize( const ShaderCompileConfigInfo& config );

// ISerializable Interface
public:
	virtual _ubool			Import( ISerializableNode* node ) override;
	virtual _ubool			Export( ISerializableNode* node ) const override;

// IBaseFile Interface
public:
	virtual _FILE_FORMAT	GetFileID( ) const override;

	virtual _ubool 			LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 			Unload( ) override;

// IShaderFile Interface
public:
	virtual _void			SetProcessIncludeCommandFunc( OnProcessIncludeCommand funcpointer, const QwordParameters2& parameters ) override;

	virtual UStringArray	GetRenderMethodNameList( ) const override;
	virtual UStringArray	GetRenderMethodNameListByExcludingIncludeNodes( ) const override;

	virtual const Version&	GetVersion( ) const override;
	virtual const Version&	GetEmbeddedVersion( ) const override;

	virtual _ubool			GenerateCodeU( UStringPtr name, UString& text ) const override;
};

}