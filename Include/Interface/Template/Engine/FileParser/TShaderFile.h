//! @file     TShaderFile.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TShaderFile
//----------------------------------------------------------------------------

template< class Type >
class TShaderFile : public Type
{
protected:
	//!	The shader code type
	enum _SHADER_CODE_TYPE
	{
		_SHADER_CODE_VS,
		_SHADER_CODE_PS,
	};

protected:
	//!	The shader variable declaration info
	struct ShaderVarDeclInfo
	{
		UString	mQualifier;
		UString	mPrecision;
		UString	mType;
		_dword	mArrayNumber; //! If it's not equal to 0 then indicates it's buffer array
		UString	mName;
		UString	mDefaultValue;

		ShaderVarDeclInfo( )
		{
			mArrayNumber	= 0;
		}
	};

protected:
	//!	The shader type
	_SHADER_TYPE			mShaderType;
	//!	The compile info
	ShaderCompileConfigInfo	mCompileConfigInfo;

	//!	The serializable root node
	ISerializableNodeRef	mRootNode;

protected:
	//!	Translate the main entry name from code type.
	static UStringPtr TranslateMainEntryNameU( _SHADER_CODE_TYPE code_type );
	static WStringPtr TranslateMainEntryNameW( _SHADER_CODE_TYPE code_type );
	//!	Translate the shader code type name from code type.
	static UStringPtr TranslateShaderCodeTypeNameU( _SHADER_CODE_TYPE code_type );
	static WStringPtr TranslateShaderCodeTypeNameW( _SHADER_CODE_TYPE code_type );

protected:
	//!	Generate variables declaration code text.
	_ubool GenerateVariablesDeclText( _dword flags, _SHADER_CODE_TYPE code_type, ISerializableNode* decl_node, UString& text ) const;
	//!	Generate macros code text.
	_ubool GenerateMacrosText( _dword flags, _SHADER_CODE_TYPE code_type, ISerializableNode* macro_node, UString& text ) const;
	//!	Generate macro code text.
	_ubool GenerateMacroText( _dword flags, _SHADER_CODE_TYPE code_type, ISerializableNode* macro_node, UString& text ) const;
	//!	Generate variable code text.
	_ubool GenerateVariableText( _dword flags, _SHADER_CODE_TYPE code_type, ISerializableNode* var_node, UString& text ) const;
	//!	Generate code text.
	_ubool GenerateCodeText( _dword flags, _SHADER_CODE_TYPE code_type, ISerializableNode* code_node, UString& text ) const;
	//!	Generate main entry code text.
	_ubool GenerateMainEntryText( _dword flags, _SHADER_CODE_TYPE code_type, ISerializableNode* main_entry_node, UString& text ) const;

	//!	Generate shader code text.
	_ubool GenerateShaderCodeText( _dword flags, _SHADER_CODE_TYPE code_type, UString& text ) const;

protected:
	//!	When build variable code.
	virtual _ubool OnBuildVariableCode( _dword flags, _SHADER_CODE_TYPE code_type, const ShaderVarDeclInfo& var_decl, UString& text ) const PURE;
	//!	When build main entry.
	virtual _ubool OnBuildMainEntry( _SHADER_CODE_TYPE code_type, UString& text ) const PURE;
	//!	When build return code.
	virtual _ubool OnBuildReturnCode( _SHADER_CODE_TYPE code_type, UStringPtr op_string, UString& text ) const PURE;

protected:
	TShaderFile( _SHADER_TYPE type );
	virtual ~TShaderFile( );

// IBaseFile Interface
public:
	virtual _ubool 							LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 							Unload( ) override;

	virtual _ubool							SaveToStream( IStreamWriter* stream_writer ) const override;

// IShaderCodeGenerator Interface
public:
	virtual _void							SetCompileConfigInfo( const ShaderCompileConfigInfo& config ) override;
	virtual const ShaderCompileConfigInfo&	GetCompileConfigInfo( ) const override;

	virtual _ubool							GenerateVSCodeU( _dword flags, UString& text ) const override;
	virtual _ubool							GenerateVSCodeW( _dword flags, WString& text ) const override;

	virtual _ubool							GeneratePSCodeU( _dword flags, UString& text ) const override;
	virtual _ubool							GeneratePSCodeW( _dword flags, WString& text ) const override;

// IShaderFile Interface
public:
	virtual _SHADER_TYPE					GetShaderType( ) const override;
};

//----------------------------------------------------------------------------
// TShaderFile Implementation
//----------------------------------------------------------------------------

template< class Type >
TShaderFile< Type >::TShaderFile( _SHADER_TYPE type ) : Type( _FF_SHADER )
{
	mShaderType = type;
}

template< class Type >
TShaderFile< Type >::~TShaderFile( )
{

}

template< class Type >
UStringPtr TShaderFile< Type >::TranslateMainEntryNameU( _SHADER_CODE_TYPE code_type )
{
	switch ( code_type )
	{
		case _SHADER_CODE_VS: return "VSMain";
		case _SHADER_CODE_PS: return "PSMain";
		default:
			return "Unknown";
	}
}

template< class Type >
WStringPtr TShaderFile< Type >::TranslateMainEntryNameW( _SHADER_CODE_TYPE code_type )
{
	switch ( code_type )
	{
		case _SHADER_CODE_VS: return L"VSMain";
		case _SHADER_CODE_PS: return L"PSMain";
		default:
			return L"Unknown";
	}
}

template< class Type >
UStringPtr TShaderFile< Type >::TranslateShaderCodeTypeNameU( _SHADER_CODE_TYPE code_type )
{
	switch ( code_type )
	{
		case _SHADER_CODE_VS: return "VertexShader";
		case _SHADER_CODE_PS: return "FragmentShader";
		default:
			return "UnknownShader";
	}
}

template< class Type >
WStringPtr TShaderFile< Type >::TranslateShaderCodeTypeNameW( _SHADER_CODE_TYPE code_type )
{
	switch ( code_type )
	{
		case _SHADER_CODE_VS: return L"VertexShader";
		case _SHADER_CODE_PS: return L"FragmentShader";
		default:
			return L"UnknownShader";
	}
}

template< class Type >
_ubool TShaderFile< Type >::GenerateVariablesDeclText( _dword flags, _SHADER_CODE_TYPE code_type, ISerializableNode* decl_node, UString& text ) const
{
	// Locate at the variables declaration section in XML file
	ISerializableNodeRef var_node = decl_node->GetChildNode( L"Variable" );
	if ( var_node.IsValid( ) )
	{
		// Build variables
		do
		{
			// Generate the variable string
			UString variable_string;
			if ( GenerateVariableText( flags, code_type, var_node, variable_string ) == _false )
				return _false;

			// Update the shader code for variables declaration
			text += variable_string;
			text += "\n";

		} while ( var_node->MoveNext( L"Variable" ) );
	}

	return _true;
}

template< class Type >
_ubool TShaderFile< Type >::GenerateMacrosText( _dword flags, _SHADER_CODE_TYPE code_type, ISerializableNode* macro_node, UString& text ) const
{
	// Locate at the macro section in XML file
	ISerializableNodeRef node = macro_node->GetChildNode( L"Macro" );
	if ( node.IsValid( ) )
	{
		// Build macro
		do
		{
			// Generate the macro string
			UString macro_string;
			if ( GenerateMacroText( flags, code_type, node, macro_string ) == _false )
				return _false;

			// Update the shader code for macro
			text += macro_string;
			text += "\n";

		} while ( macro_node->MoveNext( L"Macro" ) );
	}

	return _true;
}

template< class Type >
_ubool TShaderFile< Type >::GenerateMacroText( _dword flags, _SHADER_CODE_TYPE code_type, ISerializableNode* macro_node, UString& text ) const
{
	// Read the attribute info
	UString name, args;
	macro_node->Read( L"name", name );
	macro_node->Read( L"args", args );

	// Build code
	UString code;
	if ( GenerateCodeText( flags, code_type, macro_node->GetChildNode( L"Code" ).GetPtr( ), code ) == _false )
		return _false;

	// Use the macro return line code
	code.ReplaceAll( "\n", "\\\n", _false ); 
	// Remove the tail unused characters
	code.TrimRight( "\\\n" );

	// Build whole define text
	_chara string_buffer[8192];
	Platform::FormatStringBuffer( string_buffer, 8192, "#define %s(%s)\\\n%s\n", 
		name.Str( ), args.Str( ), code.Str( ) );

	text = string_buffer;

	return _true;
}

template< class Type >
_ubool TShaderFile< Type >::GenerateVariableText( _dword flags, _SHADER_CODE_TYPE code_type, ISerializableNode* var_node, UString& text ) const
{
	ShaderVarDeclInfo var_decl;

	// Read the attribute info
	var_node->Read( L"qualifier", var_decl.mQualifier );
	var_node->Read( L"precision", var_decl.mPrecision );
	var_node->Read( L"type", var_decl.mType );
	var_node->Read( L"array_number", var_decl.mArrayNumber );
	var_node->Read( L"name", var_decl.mName );
	var_node->Read( L"default_value", var_decl.mDefaultValue);

	// Build the variable string
	return OnBuildVariableCode( flags, code_type, var_decl, text );
}

template< class Type >
_ubool TShaderFile< Type >::GenerateCodeText( _dword flags, _SHADER_CODE_TYPE code_type, ISerializableNode* code_node, UString& text ) const
{
	// Walk all sub-elements to generate code string
	ISerializableNodeRef sub_node = code_node->GetFirstChildNode( ); 
	if ( sub_node.IsValid( ) )
	{
		do 
		{
			WString node_name = sub_node->GetNodeName( );

			// It's variable
			if ( node_name.IsEqual( L"Variable", _true ) )
			{
				UString variable_string;
				if ( GenerateVariableText( flags, code_type, sub_node, variable_string ) == _false )
					return _false;

				text += variable_string;
				text += "\n";
			}
			// It's text
			else if ( node_name.IsEqual( L"Text", _true ) )
			{
				text += UString( ).FromString( sub_node->GetTextU( ) );
			}

		} while ( sub_node->MoveNext( ) );
	}

	return _true;
}

template< class Type >
_ubool TShaderFile< Type >::GenerateMainEntryText( _dword flags, _SHADER_CODE_TYPE code_type, ISerializableNode* main_entry_node, UString& text ) const
{
	ISerializableNodeRef code_node = main_entry_node->GetChildNode( L"Code" );
	if ( code_node.IsNull( ) )
		return _false;

	// Generate code text
	UString code_text;
	if ( GenerateCodeText( flags, code_type, code_node, code_text ) == _false )
		return _false;

	// Combine the return operation string
	ISerializableNodeRef return_op_node = code_node->GetChildNode( L"ReturnOp" );
	if ( return_op_node.IsValid( ) )
	{
		UString return_op_code_string;
		return_op_code_string.FromString( return_op_node->GetTextU( ) );

		// Build the return code string
		UString ret_code;
		if ( OnBuildReturnCode( code_type, return_op_code_string, ret_code ) == _false )
			return _false;

		code_text += ret_code;
		code_text += "\n";
	}

	// Build the main entry
	UString main_entry;
	if ( OnBuildMainEntry( code_type, main_entry ) == _false )
		return _false;

	// Build whole function text
	text = main_entry + "\n{\n" + code_text + "\n}\n";

	return _true;
}

template< class Type >
_ubool TShaderFile< Type >::GenerateShaderCodeText( _dword flags, _SHADER_CODE_TYPE code_type, UString& text ) const
{
	// The shader code text string
	UString variables_decl_string, macros_string, main_entry_string;

	// Generate variables declaration shader code
	ISerializableNodeRef decl_node = mRootNode->GetChildNode( L"Declaration" );
	if ( decl_node.IsValid( ) && GenerateVariablesDeclText( flags, code_type, decl_node, variables_decl_string ) == _false )
		return _false;

	// Generate macro shader code
	ISerializableNodeRef macro_node = mRootNode->GetChildNode( L"Macros" );
	if ( macro_node.IsValid( ) && GenerateMacrosText( flags, code_type, macro_node, macros_string ) == _false )
		return _false;

	// Generate the code text
	ISerializableNodeRef main_entry_node = mRootNode->GetChildNode( TranslateMainEntryNameW( code_type ) );
	if ( main_entry_node.IsValid( ) && GenerateMainEntryText( flags, code_type, main_entry_node, main_entry_string ) == _false )
		return _false;

	// Build the whole shader code
	text += variables_decl_string;
	text += "\n";
	text += macros_string;
	text += "\n";
	text += main_entry_string;
	text += "\n";

	return _true;
}

template< class Type >
_ubool TShaderFile< Type >::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	// Parse the stream in XML format
	IMarkupLangFileRef xml_file = GetInterfaceFactory( )->ParseXMLFile( stream_reader );
	if ( xml_file.IsNull( ) )
		return _false;

	// Skip for empty XML file
	if ( xml_file->GetRootElement( ) == _null )
		return _false;

	// Create the serializable root node for generating shader code
	mRootNode = GetInterfaceFactory( )->CreateMarkupLangSerializableNode( xml_file->GetRootElement( ), xml_file );
	if ( mRootNode.IsNull( ) )
		return _false;

	return _true;
}

template< class Type >
_void TShaderFile< Type >::Unload( )
{
	mRootNode.Clear( );
}

template< class Type >
_ubool TShaderFile< Type >::SaveToStream( IStreamWriter* stream_writer ) const
{
	return _false;
}

template< class Type >
_void TShaderFile< Type >::SetCompileConfigInfo( const ShaderCompileConfigInfo& config )
{
	mCompileConfigInfo = config;
}

template< class Type >
const ShaderCompileConfigInfo& TShaderFile< Type >::GetCompileConfigInfo( ) const
{
	return mCompileConfigInfo;
}

template< class Type >
_ubool TShaderFile< Type >::GenerateVSCodeU( _dword flags, UString& text ) const
{
	return GenerateShaderCodeText( flags, _SHADER_CODE_VS, text );
}

template< class Type >
_ubool TShaderFile< Type >::GenerateVSCodeW( _dword flags, WString& text ) const
{
	UString text_utf8;
	if ( GenerateVSCodeU( flags, text_utf8 ) == _false )
		return _false;

	text.FromString( text_utf8 );

	return _true;
}

template< class Type >
_ubool TShaderFile< Type >::GeneratePSCodeU( _dword flags, UString& text ) const
{
	return GenerateShaderCodeText( flags, _SHADER_CODE_PS, text );
}

template< class Type >
_ubool TShaderFile< Type >::GeneratePSCodeW( _dword flags, WString& text ) const
{
	UString text_utf8;
	if ( GeneratePSCodeU( flags, text_utf8 ) == _false )
		return _false;

	text.FromString( text_utf8 );

	return _true;
}

template< class Type >
_SHADER_TYPE TShaderFile< Type >::GetShaderType( ) const
{
	return mShaderType;
}

}