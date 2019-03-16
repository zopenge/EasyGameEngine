//! @file     ShaderFile.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

#ifndef _EGE_DISABLE_SHADER_FILE_

//----------------------------------------------------------------------------
// VSCodeGLSLGenerator Implementation
//----------------------------------------------------------------------------

VSCodeGLSLGenerator::VSCodeGLSLGenerator( )
{
}

VSCodeGLSLGenerator::~VSCodeGLSLGenerator( )
{
}

_SHADER_CODE_TYPE VSCodeGLSLGenerator::GetCodeType( ) const
{
	return _SHADER_CODE_VS;
}

_ubool VSCodeGLSLGenerator::GenerateVarDeclString( _ubool is_embedded_system, const ShaderVarDeclInfo& var_decl, UString& text ) const
{
	// Skip texture sampler in VS
	if ( var_decl.mType == "sampler2D" || var_decl.mType == "sampler2DShadow" || var_decl.mType == "samplerCube" )
		return _true;

	return BaseClass::GenerateVarDeclString( is_embedded_system, var_decl, text );
}

//----------------------------------------------------------------------------
// PSCodeGLSLGenerator Implementation
//----------------------------------------------------------------------------

PSCodeGLSLGenerator::PSCodeGLSLGenerator( )
{
}

PSCodeGLSLGenerator::~PSCodeGLSLGenerator( )
{
}

_SHADER_CODE_TYPE PSCodeGLSLGenerator::GetCodeType( ) const
{
	return _SHADER_CODE_PS;
}

_ubool PSCodeGLSLGenerator::GenerateVarDeclString( _ubool is_embedded_system, const ShaderVarDeclInfo& var_decl, UString& text ) const
{
	// Skip attribute variables in PS
	if ( var_decl.mQualifier == "attribute" )
		return _true;

	return BaseClass::GenerateVarDeclString( is_embedded_system, var_decl, text );
}

//----------------------------------------------------------------------------
// ShaderFile Implementation
//----------------------------------------------------------------------------

ShaderFile::ShaderFile( )
{
	mVersion			= Version::cZero;
	mEmbeddedVersion	= Version::cZero;
}

ShaderFile::~ShaderFile( )
{

}

_ubool ShaderFile::HasVaryingVariable( const VaryingVarInfoArray& vars, UStringPtr var_name )
{
	for ( _dword i = 0; i < vars.Number( ); i ++ )
	{
		if ( vars[i].mName == var_name )
			return _true;
	}

	return _false;
}

_ubool ShaderFile::FixVaryingVar( VaryingVarInfoArray& vars )
{
	for ( _int i = (_int)vars.Number( ) - 1; i >= 0; i -- )
	{
		VaryingVarInfo depend_var_info = vars[i];

		for ( _int j = i - 1; j >= 0; j -- )
		{
			const VaryingVarInfo& var_info = vars[j];

			if ( var_info.mExpandCode.IsEmpty( ) )
				continue;

			if ( var_info.mExpandCode.SearchL2R( depend_var_info.mName ) != -1 )
			{
				vars.RemoveByIndex( i );
				vars.Insert( depend_var_info, j );

				return _true;
			}
		}
	}

	return _false;
}

const ShaderFile::MacroInfo* ShaderFile::GetMacroInfo( const MacroInfoMap& external_macros, UStringPtr macro_name ) const
{
	// Get the external macro info
	const MacroInfo* macro_info = external_macros.Search( macro_name );
	if ( macro_info != _null )
		return macro_info;

	// Get the macro info
	macro_info = mMacros.Search( macro_name );
	if ( macro_info != _null )
		return macro_info;

	ALOG_ERROR_1( "The '%s' macro name is not existing", macro_name.Str( ) );
	return _null;
}

_void ShaderFile::ParseMacroArguments( ISerializableNode* macro_node, WStringPtr prefix_name, UStringArray& arguments ) const
{
	_dword index = 0;

	while ( _true )
	{
		WString key_name = FORMAT_WSTRING_2( L"%s%d", prefix_name.Str( ), index ++ );

		UString argument_name;
		if ( macro_node->Read( key_name, argument_name ) == _false )
			break;

		arguments.Append( argument_name );
	}
}

_void ShaderFile::ParseMacroInfo( ISerializableNode* macro_node, MacroInfo& macro_info ) const
{
	macro_node->Read( L"varying", macro_info.mIsVarying );
	macro_node->Read( L"precision", macro_info.mPrecision );
	macro_node->Read( L"type", macro_info.mType );
	macro_node->Read( L"default", macro_info.mDefaultValue );

	ParseMacroArguments( macro_node, L"in", macro_info.mInArgs );
	ParseMacroArguments( macro_node, L"out", macro_info.mOutArgs );

	ISerializableNodeRef code_node = macro_node->GetChildNodeByName( L"Code" );
	if ( code_node.IsValid( ) )
		macro_info.mCode = code_node->GetTextU( );
}

_void ShaderFile::ParseVarDeclInfo( ISerializableNode* var_decl_node, ShaderVarDeclInfo& var_decl_info ) const
{
	var_decl_node->Read( L"qualifier", var_decl_info.mQualifier );
	var_decl_node->Read( L"precision", var_decl_info.mPrecision );
	var_decl_node->Read( L"type", var_decl_info.mType );
	var_decl_node->Read( L"name", var_decl_info.mName );
	var_decl_node->Read( L"default", var_decl_info.mDefaultValue );
	var_decl_node->Read( L"array_number", var_decl_info.mArrayNumber );
}

_ubool ShaderFile::ImportIncludeNodes( ISerializableNode* shader_node )
{
	ISerializableNodeRef include_node = shader_node->GetChildNodeByName( L"Include" );
	if ( include_node.IsValid( ) )
	{
		do 
		{
			UString filename;
			if ( include_node->Read( L"name", filename ) == _false )
				return _false;

			UString code_string;
			if ( mProcessIncludeCommandFunc.InvokeR( filename, mCompileConfigInfo, code_string ) == _false )
				return _false;

			ISerializableNodeRef root_node = GetInterfaceFactory( )->CreateMarkupLangSerializableNode( code_string );
			if ( root_node.IsNull( ) )
				return _false;

			// Import variable declarations
			ISerializableNodeRef decl_node = root_node->GetChildNodeByName( L"Declaration" );
			if ( decl_node.IsValid( ) )
			{
				ISerializableNodeRef var_decl_node = decl_node->GetFirstChildNode( );
				if ( var_decl_node.IsValid( ) )
				{
					do 
					{
						ShaderVarDeclInfo var_decl_info;
						ParseVarDeclInfo( var_decl_node, var_decl_info );

						mVarDecls.Append( var_decl_info );

					} while ( var_decl_node->MoveNext( ) );
				}
			}

			// Import macros
			ISerializableNodeRef macros_node = root_node->GetChildNodeByName( L"Macros" );
			if ( macros_node.IsValid( ) )
			{
				ISerializableNodeRef macro_node = macros_node->GetFirstChildNode( );
				if ( macro_node.IsValid( ) )
				{
					do 
					{
						UString macro_name;
						macro_node->Read( L"name", macro_name );

						MacroInfo macro_info;
						ParseMacroInfo( macro_node, macro_info );

						mMacros[ macro_name ] = macro_info;

					} while ( macro_node->MoveNext( ) );
				}
			}

			// Import technique info and render methods
			ISerializableNodeRef shader_node = root_node->GetChildNodeByName( L"Shader" );
			if ( shader_node.IsValid( ) )
			{
				ISerializableNodeRef technique_node = shader_node->GetChildNodeByName( L"Technique" );
				if ( technique_node.IsValid( ) )
				{
					if ( ImportTechniqueNodes( technique_node, _true ) == _false )
						return _false;
				}
			}

		} while ( include_node->MoveNext( L"Include" ) );
	}
		
	return _true;
}

_ubool ShaderFile::ImportRenderMethodNode( ISerializableNode* render_method_node, _ubool from_include_node )
{
	UString name;
	if ( render_method_node->Read( L"name", name ) == _false || name.IsEmpty( ) )
		return _false;

	RenderMethodInfo render_method_info;
	render_method_info.mFromIncludeNode	= from_include_node;
	render_method_info.mVSCodeGenerator	= mCodeGenerators[ _SHADER_CODE_VS ];
	render_method_info.mPSCodeGenerator	= mCodeGenerators[ _SHADER_CODE_PS ];
	render_method_info.mRenderStats		= render_method_node->GetChildNodeByName( L"RenderStats" );

	// Read external macros 
	ISerializableNodeRef macros_node = render_method_node->GetChildNodeByName( L"Macros" );
	if ( macros_node.IsValid( ) )
	{
		ISerializableNodeRef macro_node = macros_node->GetFirstChildNode( );
		if ( macro_node.IsValid( ) )
		{
			do 
			{
				UString macro_name;
				macro_node->Read( L"name", macro_name );

				MacroInfo macro_info;
				ParseMacroInfo( macro_node, macro_info );

				render_method_info.mExternalMacros[ macro_name ] = macro_info;

			} while ( macro_node->MoveNext( ) );
		}
	}

	// Read VS resident code
	ISerializableNodeRef vs_resident_code_node = render_method_node->GetChildNodeByName( L"VSResidentCode" );
	if ( vs_resident_code_node.IsValid( ) )
		render_method_info.mVSResidentCode = vs_resident_code_node->GetTextU( );

	// Read VS finish code
	ISerializableNodeRef vs_finish_code_node = render_method_node->GetChildNodeByName( L"VSFinishCode" );
	if ( vs_finish_code_node.IsValid( ) )
		render_method_info.mVSFinishCode = vs_finish_code_node->GetTextU( );

	// Read VS code
	ISerializableNodeRef vs_code_node = render_method_node->GetChildNodeByName( L"VSCode" );
	if ( vs_code_node.IsValid( ) )
		render_method_info.mVSCode = vs_code_node->GetTextU( );

	// Read PS code
	ISerializableNodeRef ps_code_node = render_method_node->GetChildNodeByName( L"PSCode" );
	if ( ps_code_node.IsValid( ) )
		render_method_info.mPSCode = ps_code_node->GetTextU( );

	// Inherit from parent node
	UString inherit;
	if ( render_method_node->Read( L"inherit", inherit ) )
	{
		const RenderMethodInfo* inherit_render_method_info = mRenderMethods.Search( inherit );
		if ( inherit_render_method_info == _null )
			return _false;

		if ( inherit_render_method_info->mVSCode.IsEmpty( ) == _false )
			render_method_info.mVSCode = inherit_render_method_info->mVSCode;

		if ( inherit_render_method_info->mPSCode.IsEmpty( ) == _false )
			render_method_info.mPSCode = inherit_render_method_info->mPSCode;

		if ( inherit_render_method_info->mRenderStats.IsValid( ) )
			render_method_info.mRenderStats	= inherit_render_method_info->mRenderStats;
	}

	mRenderMethods[ name ] = render_method_info;

	return _true;
}

_ubool ShaderFile::ImportTechniqueNodes( ISerializableNode* technique_node, _ubool from_include_node )
{
	// Read VS resident code
	ISerializableNodeRef vs_resident_code_node = technique_node->GetChildNodeByName( L"VSResidentCode" );
	if ( vs_resident_code_node.IsValid( ) )
		mTechniqueInfo.mVSResidentCode = vs_resident_code_node->GetTextU( );

	// Read VS finish code
	ISerializableNodeRef vs_finish_code_node = technique_node->GetChildNodeByName( L"VSFinishCode" );
	if ( vs_finish_code_node.IsValid( ) )
		mTechniqueInfo.mVSFinishCode = vs_finish_code_node->GetTextU( );

	// Import render methods
	ISerializableNodeRef render_method_node = technique_node->GetChildNodeByName( L"RenderMethod" );
	if ( render_method_node.IsValid( ) )
	{
		do 
		{
			if ( ImportRenderMethodNode( render_method_node, from_include_node ) == _false )
				return _false;

		} while ( render_method_node->MoveNext( L"RenderMethod" ) );
	}

	return _true;
}

_ubool ShaderFile::GetFirstMacroText( const UString& text, UString& macro_text ) const
{
	_dword start_index = text.SearchL2R( "$" );
	if ( start_index == -1 )
		return _false;

	_int bracket_counter = 0;
	_dword index = start_index + 1;

	while ( _true )
	{
		_chara code = text[ index ++ ];
		if ( code == 0 )
		{
			ALOG_ERROR_2( "'%s' text is not valid macro text(index: %d)", text.Str( ), index - 1 );
			return _false;
		}

		if ( code == '(' )
		{
			bracket_counter ++;
		}
		else if ( code == ')' )
		{
			bracket_counter --;
			if ( bracket_counter == 0 )
				break;
		}
	}

	_dword length = index - start_index;

	macro_text = text.SubString( start_index, length );

	return _true;
}

_ubool ShaderFile::ReplaceOptionalSectionText( _ubool is_embedded_system, UString& text ) const
{
	const _ubool enable_optional_section = is_embedded_system;

	while ( _true )
	{
		_dword index = text.SearchL2R( "${" );
		if ( index == -1 )
			break;

		_dword end_index = text.SubString( index ).SearchL2R( "}$" );
		if ( end_index == -1 )
		{
			// Not match '${}$'
			ALOG_ERROR_1( "Match '}$' macro sub string in '%s' failed", text.SubString( index ).Str( ) );
			return _false;
		}

		const _ubool is_not_optional = index == 0 ? _false : text[index - 1] == '!';

		// Enable text
		if ( enable_optional_section ^ is_not_optional )
		{
			text.Remove( index + end_index, 2 );
			text.Remove( index, 2 );
		}
		// Disable text
		else
		{
			text.RemoveByRange( index, index + end_index + 1 );
		}

		// Remove '!' character
		if ( is_not_optional )
			text.Remove( index - 1, 1 );
	}

	return _true;
}

_void ShaderFile::ReplaceMacroArguments( const MacroInfo* macro_info, const UStringArray& arguments, UString& text ) const
{
	UStringArray args = macro_info->mInArgs;
	args += macro_info->mOutArgs;

	for ( _dword i = 0; i < args.Number( ); i ++ )
	{
		UString		arg_key		= UString( "@" ) + args[i];
		UStringPtr	arg_value	= arguments[i];

		text.ReplaceAll( arg_key, arg_value );
	}
}

_ubool ShaderFile::ReplaceMacroText( const MacroInfo* macro_info, UStringPtr macro_name, UStringPtr arguments_text, _ubool is_embedded_system, UString& text, VaryingVarInfoArray& varying_vars ) const
{
	// Get and parse arguments
	UStringArray arguments; 
	StringFormatter::SplitString( arguments_text, arguments, ",", " \t" );

	// Check arguments number
	_dword total_arguments_number = macro_info->mInArgs.Number( ) + macro_info->mOutArgs.Number( );
	if ( arguments.Number( ) != total_arguments_number )
	{
		ALOG_ERROR_3( "The '%s' macro's arguments it not match(now:%d, required:%d)", macro_name.Str( ), arguments.Number( ), total_arguments_number );
		return _false;
	}

	// It's variable declaration macro
	if ( macro_info->mIsVarying )
	{
		// Skip to the duplicated variable
		if ( HasVaryingVariable( varying_vars, macro_name ) == _false )
		{
			VaryingVarInfo var_info;
			var_info.mQualifier		= "varying";
			var_info.mPrecision		= macro_info->mPrecision;
			var_info.mType			= macro_info->mType;
			var_info.mName			= macro_name;
			var_info.mDefaultValue	= macro_info->mDefaultValue;
			var_info.mArrayNumber	= 0;
			var_info.mExpandCode	= macro_info->mCode;

			// Update expand code string
			if ( var_info.mExpandCode.IsEmpty( ) == _false )
			{
				// Replace arguments
				if ( arguments.Number( ) != 0 )
					ReplaceMacroArguments( macro_info, arguments, var_info.mExpandCode );

				// Update name macro
				var_info.mExpandCode.ReplaceAll( "#name", macro_name );
			}

			// Add varying variable
			varying_vars.Append( var_info );
		}

		// Feedback text
		text = macro_name;
	}
	else
	{
		// Get the macro code
		UString macro_code = macro_info->mCode;

		// Replace '${}' section
		if ( ReplaceOptionalSectionText( is_embedded_system, macro_code ) == _false )
		{
			ALOG_ERROR_1( "The '%s' macro's '${}' is not match", macro_name.Str( ) );
			return _false;
		}

		// Replace arguments
		if ( macro_code.IsEmpty( ) == _false )
		{
			// Remove the 'in:' and 'out:' helpful text
			for ( _dword i = 0; i < arguments.Number( ); i ++ )
			{
				UString& argument = arguments[i];

				if ( argument.StartsWith( "in:" ) )
					argument.Remove( 0, 3 );
				else if ( argument.StartsWith( "out:" ) )
					argument.Remove( 0, 4 );
			}

			// Replace arguments
			if ( arguments.Number( ) != 0 )
				ReplaceMacroArguments( macro_info, arguments, macro_code );

			// Feedback text
			text = macro_code;
		}
	}

	return _true;
}

_ubool ShaderFile::ReplaceMacrosText( _ubool is_embedded_system, UString& text, VaryingVarInfoArray& varying_vars, const MacroInfoMap& external_macros ) const
{
	// Replace the optional section text
	if ( ReplaceOptionalSectionText( is_embedded_system, text ) == _false )
		return _false;

	// Replace all '$' macro section
	while ( _true )
	{
		// Get the first macro text
		UString first_macro_text;
		if ( GetFirstMacroText( text, first_macro_text ) == _false )
			break; // No any more macros

		// Parse macro text
		UString macro_name, arguments_text;
		if ( StringFormatter::ParseString( first_macro_text.Str( ), "$%s(%s", macro_name, arguments_text ) != 2 )
			return _false;

		// Trim some unused characters
		macro_name.TrimBoth( " \t" );
		arguments_text.TrimBoth( " \t;" );
		arguments_text.Remove( arguments_text.GetLength( ) - 1, 1 ); // ')'

		// Get the macro info
		const MacroInfo* macro_info = GetMacroInfo( external_macros, macro_name );
		if ( macro_info == _null )
		{
			ALOG_ERROR_1( "The '%s' macro name is not existing", macro_name.Str( ) );
			return _false;
		}

		// Replace macro text
		UString macro_code;
		if ( ReplaceMacroText( macro_info, macro_name, arguments_text, is_embedded_system, macro_code, varying_vars ) == _false )
			return _false;

		// Replace the macro text
		text.Replace( first_macro_text, macro_code );
	}

	return _true;
}

_ubool ShaderFile::GenerateCodeText( const MacroInfoMap& external_macros, UStringPtr code, const IShaderCodeGenerator* code_generator, UString& text, VaryingVarInfoArray& varying_vars, _ubool use_default_value, _ubool is_embedded_system, UString& version_text ) const
{
	// Get the shader version
	const Version& version = is_embedded_system ? mEmbeddedVersion : mVersion;

	// #version
	if ( code_generator->GenerateVersionMacroString( version, version_text ) == _false )
		return _false;

	// #variables
	for ( _dword i = 0; i < mVarDecls.Number( ); i ++ )
	{
		const ShaderVarDeclInfo& var_decl_info = mVarDecls[i];

		UString var_decl_text;
		if ( code_generator->GenerateVarDeclString( is_embedded_system, var_decl_info, var_decl_text ) == _false )
			return _false;

		if ( var_decl_text.IsEmpty( ) == _false )
		{
			text += var_decl_text;
			text += "\n";
		}
	}

	// Replace macros text
	UString shader_code = code;
	if ( ReplaceMacrosText( is_embedded_system, shader_code, varying_vars, external_macros ) == _false )
		return _false;

	// Build the expand codes
	for ( _dword i = 0; i < varying_vars.Number( ); i ++ )
	{
		VaryingVarInfo& var_info = varying_vars[i];

		if ( var_info.mExpandCode.IsEmpty( ) )
			continue;

		// Replace macros text
		if ( ReplaceMacrosText( is_embedded_system, var_info.mExpandCode, varying_vars, external_macros ) == _false )
			return _false;
	}

	// Fix varying variables
	while ( FixVaryingVar( varying_vars ) ) { };

	// #varying variables
	UString varying_vars_decl_text;
	for ( _dword i = 0; i < varying_vars.Number( ); i ++ )
	{
		// Only declare so disable default value
		VaryingVarInfo var_info = varying_vars[i];
		var_info.mDefaultValue.Clear( );

		UString var_decl_text;
		if ( code_generator->GenerateVarDeclString( is_embedded_system, var_info, var_decl_text ) == _false )
			return _false;

		varying_vars_decl_text += var_decl_text + "\n";
	}

	// #varying variables declarations
	text += varying_vars_decl_text;

	// #main - begin
	text += code_generator->GetMainEntryString( );
	text += "\n{\n";

	// Add default variables assign
	if ( use_default_value )
	{
		UString vs_varying_vars;
		for ( _dword i = 0; i < varying_vars.Number( ); i ++ )
		{
			const VaryingVarInfo& var_info = varying_vars[i];

			// Update default value by macros
			UString default_value = var_info.mDefaultValue;
			if ( ReplaceOptionalSectionText( is_embedded_system, default_value ) == _false )
				return _false;

			if ( default_value.IsEmpty( ) )
				continue;

			vs_varying_vars += var_info.mName + " = " + default_value + ";\n";
		}

		text += vs_varying_vars;
		text += "\n";
	}

	// Add shader code
	text += shader_code;

	// Add expand code variables assign
	if ( use_default_value )
	{
		for ( _dword i = 0; i < varying_vars.Number( ); i ++ )
		{
			const VaryingVarInfo& var_info = varying_vars[i];

			if ( var_info.mExpandCode.IsEmpty( ) )
				continue;

			text += var_info.mExpandCode;
			text += "\n";
		}
	}

	// #main - end
	text += "\n}\n";

	return _true;
}

_ubool ShaderFile::GenerateVSCodeText( const RenderMethodInfo* render_method, _ubool is_embedded_system, UString& text, VaryingVarInfoArray& varying_vars, UString& version_text ) const
{
	UStringPtr vs_resident_code = mTechniqueInfo.mVSResidentCode;
	if ( render_method->mVSResidentCode.IsEmpty( ) == _false )
		vs_resident_code = render_method->mVSResidentCode;

	UStringPtr vs_finish_code = mTechniqueInfo.mVSFinishCode;
	if ( render_method->mVSFinishCode.IsEmpty( ) == _false )
		vs_finish_code = render_method->mVSFinishCode;

	UString vs_code;
	vs_code += vs_resident_code + "\n" + render_method->mVSCode + "\n" + vs_finish_code;

	return GenerateCodeText( render_method->mExternalMacros, vs_code, render_method->mVSCodeGenerator, text, varying_vars, _true, is_embedded_system, version_text );
}

_ubool ShaderFile::GeneratePSCodeText( const RenderMethodInfo* render_method, _ubool is_embedded_system, UString& text, VaryingVarInfoArray& varying_vars, UString& version_text ) const
{
	UString ps_code;
	ps_code += render_method->mPSCode;

	return GenerateCodeText( render_method->mExternalMacros, ps_code, render_method->mPSCodeGenerator, text, varying_vars, _false, is_embedded_system, version_text );
}

_ubool ShaderFile::InsertVSAndPSXMLNode( const RenderMethodInfo* render_method, IMarkupLangElement* root, WStringPtr vs_node_name, WStringPtr ps_node_name, _ubool is_embedded_system ) const
{
	// Generate PS code
	UString ps_code, ps_version_text; VaryingVarInfoArray varying_vars;
	if ( GeneratePSCodeText( render_method, is_embedded_system, ps_code, varying_vars, ps_version_text ) == _false )
		return _false;

	// Generate VS code
	UString vs_code, vs_version_text;
	if ( GenerateVSCodeText( render_method, is_embedded_system, vs_code, varying_vars, vs_version_text ) == _false )
		return _false;

	// Add the precision declaration
	if ( is_embedded_system )
	{
		vs_code = UString( "precision highp float;\n\n" ) + vs_code;
		ps_code = UString( "precision highp float;\n\n" ) + ps_code;
	}

	// Insert shader code
	IMarkupLangElement* vs_code_node = root->InsertChildElementU( vs_node_name, vs_code, _false );
	IMarkupLangElement* ps_code_node = root->InsertChildElementU( ps_node_name, ps_code, _false );
	if ( vs_code_node == _null || ps_code_node == _null )
		return _false;

	// Add version info
	vs_code_node->SetAttributeString( L"version", vs_version_text );
	ps_code_node->SetAttributeString( L"version", ps_version_text );

	return _true;
}

_ubool ShaderFile::Initialize( const ShaderCompileConfigInfo& config )
{
	mCompileConfigInfo = config;

	switch ( mCompileConfigInfo.mShaderType )
	{
		// GLSL 
		case _SHADER_GLSL:
		{
			mCodeGenerators[ _SHADER_CODE_VS ].New< VSCodeGLSLGenerator >( );
			mCodeGenerators[ _SHADER_CODE_PS ].New< PSCodeGLSLGenerator >( );
		}
		break;

		// HLSL
		case _SHADER_HLSL:
		{
			EGE_ASSERT( 0 );
			//mCodeGenerators[ _SHADER_CODE_VS ].New< VSCodeGLSLGenerator >( );
			//mCodeGenerators[ _SHADER_CODE_PS ].New< PSCodeGLSLGenerator >( );
		}
		break;

		default:
		{
			WLOG_ERROR_1( L"Invalid shader compile flags(%d), create shader code generator failed", (_dword)mCompileConfigInfo.mShaderType );
			return _false;
		}
	}

	return _true;
}

_ubool ShaderFile::Import( ISerializableNode* node )
{
	if ( node == _null )
		return _false;

	// Save the root node
	mRootNode = node;

	// Get the shader node
	ISerializableNodeRef shader_node = mRootNode->GetChildNodeByName( L"Shader" );
	if ( shader_node.IsNull( ) )
		return _false;

	// Read the version
	shader_node->Read( L"version", mVersion );
	shader_node->Read( L"embedded_version", mEmbeddedVersion );

	// Import the include nodes
	if ( ImportIncludeNodes( shader_node ) == _false )
		return _false;

	// Get the technique node
	ISerializableNodeRef technique_node = shader_node->GetChildNodeByName( L"Technique" );
	if ( technique_node.IsNull( ) )
		return _false;

	// Import the technique nodes
	if ( ImportTechniqueNodes( technique_node, _false ) == _false )
		return _false;

	return _true;
}

_ubool ShaderFile::Export( ISerializableNode* node ) const
{
	return _false;
}

_FILE_FORMAT ShaderFile::GetFileID( ) const
{
	return _FF_SHADER;
}

_ubool ShaderFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	// Import it
	ISerializableNodeRef node = GetInterfaceFactory( )->CreateMarkupLangSerializableNode( stream_reader );
	if ( node.IsNull( ) )
		return _false;

	if ( Import( node ) == _false )
		return _false;

	return _true;
}

_void ShaderFile::Unload( )
{
	mVersion			= Version::cZero;
	mEmbeddedVersion	= Version::cZero;

	mRootNode.Clear( );
	mVarDecls.Clear( );
	mTechniqueInfo.mVSFinishCode.Clear( );
	mTechniqueInfo.mVSResidentCode.Clear( );
	mMacros.Clear( );
	mRenderMethods.Clear( );
}

_void ShaderFile::SetProcessIncludeCommandFunc( OnProcessIncludeCommand funcpointer, const QwordParameters2& parameters )
{
	mProcessIncludeCommandFunc.Init( funcpointer, parameters );
}

UStringArray ShaderFile::GetRenderMethodNameList( ) const
{
	UStringArray names;

	for ( RenderMethodInfoMap::Iterator it = mRenderMethods.GetHeadIterator( ); it.IsValid( ); ++ it )
		names.Append( it.GetKey( ) );

	return names;
}

UStringArray ShaderFile::GetRenderMethodNameListByExcludingIncludeNodes( ) const
{
	UStringArray names;

	for ( RenderMethodInfoMap::Iterator it = mRenderMethods.GetHeadIterator( ); it.IsValid( ); ++ it )
	{
		const RenderMethodInfo& render_method_info = it.GetObject( );

		if ( render_method_info.mFromIncludeNode )
			continue;

		names.Append( it.GetKey( ) );
	}

	return names;
}

const Version& ShaderFile::GetVersion( ) const
{
	return mVersion;
}

const Version& ShaderFile::GetEmbeddedVersion( ) const
{
	return mEmbeddedVersion;
}

_ubool ShaderFile::GenerateCodeU( UStringPtr name, UString& text ) const
{
	const RenderMethodInfo* render_method = mRenderMethods.Search( name );
	if ( render_method == _null )
		return _false;

	// Create XML file
	IMarkupLangFileRef xml_file = GetInterfaceFactory( )->CreateXMLFile( L"Root" );
	if ( xml_file.IsNull( ) )
		return _false;

	// Get the root element
	IMarkupLangElement* root = xml_file->GetRootElement( );
	if ( root == _null )
		return _false;

	// Insert render stats
	if ( render_method->mRenderStats.IsValid( ) )
		root->InsertChildElement( render_method->mRenderStats->GetMarkupLangElement( ), _true );

	// Insert VS and PS code
	if ( InsertVSAndPSXMLNode( render_method, root, L"VS", L"PS", _false ) == _false )
		return _false;

	// Insert embedded VS and PS code
	if ( InsertVSAndPSXMLNode( render_method, root, L"EmbeddedVS", L"EmbeddedPS", _true ) == _false )
		return _false;

	// Dump to string
	WString dump_string = root->DumpToString( );

	// Dump text
	text.FromString( dump_string );

	return _true;
}

#endif