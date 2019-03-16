//! @file     TShaderCodeGLSLGenerator.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TShaderCodeGLSLGenerator
//----------------------------------------------------------------------------

template< typename Type >
class TShaderCodeGLSLGenerator : public TShaderCodeGenerator< Type >
{
// TShaderCodeGenerator Interface
protected:
	virtual _dword		GetVariableStride( UStringPtr type ) const override;

protected:
	TShaderCodeGLSLGenerator( );
	virtual ~TShaderCodeGLSLGenerator( );

// IShaderCodeGenerator Interface
public:
	virtual Version		GetDefaultVersion( ) const override;

	virtual UStringPtr	GetMainEntryString( ) const override;

	virtual _ubool		GenerateVersionMacroString( const Version& version, UString& text ) const override;
	virtual _ubool		GenerateVarDeclString( _ubool is_embedded_system, const ShaderVarDeclInfo& var_decl, UString& text ) const override;
	virtual _ubool		GenerateVarDeclString( _ubool is_embedded_system, ISerializableNode* node, UString& text ) const override;
	virtual _ubool		GenerateStructDeclString( _ubool is_embedded_system, ISerializableNode* node, UString& text ) const override;
};

//----------------------------------------------------------------------------
// TShaderCodeGLSLGenerator Implementation
//----------------------------------------------------------------------------

template< typename Type >
TShaderCodeGLSLGenerator< Type >::TShaderCodeGLSLGenerator( )
{
}

template< typename Type >
TShaderCodeGLSLGenerator< Type >::~TShaderCodeGLSLGenerator( )
{
}

template< typename Type >
Version TShaderCodeGLSLGenerator< Type >::GetDefaultVersion( ) const
{
	// We use GLSL 1.0 as default shader version
	return Version( 1, 0, 0, 0 );
}

template< typename Type >
_dword TShaderCodeGLSLGenerator< Type >::GetVariableStride( UStringPtr type ) const
{
	if ( type == "float" )
		return sizeof( _float );
	else if ( type == "vec2" )
		return sizeof( Vector2 );
	else if ( type == "vec3" )
		return sizeof( Vector3 );
	else if ( type == "vec4" )
		return sizeof( Vector4 );
	else if ( type == "ivec2" )
		return 2 * sizeof( _dword );
	else if ( type == "ivec3" )
		return 3 * sizeof( _dword );
	else if ( type == "ivec4" )
		return 4 * sizeof( _dword );
	else if ( type == "mat3" )
		return sizeof( Matrix3 );
	else if ( type == "mat4" )
		return sizeof( Matrix4 );

	return 0;
}

template< typename Type >
UStringPtr TShaderCodeGLSLGenerator< Type >::GetMainEntryString( ) const
{
	// All GLSL shader code use the main() entry
	return "void main()";
}

template< typename Type >
_ubool TShaderCodeGLSLGenerator< Type >::GenerateVersionMacroString( const Version& version, UString& text ) const
{
	text = FORMAT_ASTRING_1( "#version %.3d", version.GetMajorVersion( ) * 100 + version.GetMinorVersion( ) * 10 );

	return _true;
}

template< typename Type >
_ubool TShaderCodeGLSLGenerator< Type >::GenerateVarDeclString( _ubool is_embedded_system, const ShaderVarDeclInfo& var_decl, UString& text ) const
{
	// Get the qualifier string
	UStringPtr qualifier_string		= var_decl.mQualifier;
	UStringPtr precision_string		= var_decl.mPrecision;
	UStringPtr type_string			= var_decl.mType;
	UStringPtr name_string			= var_decl.mName;
	UStringPtr default_value_string = var_decl.mDefaultValue;

	// The code string text
	_chara string[1024];

	// It's embedded system
	if ( is_embedded_system && (!precision_string.IsEmpty( )) )
	{
		Platform::FormatStringBuffer( string, 1024, "%s %s %s %s", 
			qualifier_string.Str( ), precision_string.Str( ), type_string.Str( ), name_string.Str( ) );
	}
	// It's standard GL
	else
	{
		Platform::FormatStringBuffer( string, 1024, "%s %s %s", 
			qualifier_string.Str( ), type_string.Str( ), name_string.Str( ) );
	}

	// Append the array number if provided
	if ( var_decl.mArrayNumber != 0 )
	{
		Platform::AppendString( string, "[" );
		Platform::AppendString( string, UString( ).FromValue( var_decl.mArrayNumber, 10 ).Str( ) );
		Platform::AppendString( string, "]" );
	}

	// Append the default value if provided
	if ( default_value_string.IsEmpty( ) == _false )
	{
		Platform::AppendString( string, "=" );
		Platform::AppendString( string, default_value_string.Str( ) );
	}

	// Complete variable declaration string building
	text = Platform::AppendString( string, ";" );

	return _true;
}

template< typename Type >
_ubool TShaderCodeGLSLGenerator< Type >::GenerateVarDeclString( _ubool is_embedded_system, ISerializableNode* node, UString& text ) const
{
	if ( node == _null )
		return _false;

	// Read the attribute info
	ShaderVarDeclInfo var_decl;
	node->Read( L"qualifier", var_decl.mQualifier );
	node->Read( L"precision", var_decl.mPrecision );
	node->Read( L"type", var_decl.mType );
	node->Read( L"array_number", var_decl.mArrayNumber );
	node->Read( L"name", var_decl.mName );
	node->Read( L"default_value", var_decl.mDefaultValue);

	// Build the variable string
	return GenerateVarDeclString( is_embedded_system, var_decl, text );
}

template< typename Type >
_ubool TShaderCodeGLSLGenerator< Type >::GenerateStructDeclString( _ubool is_embedded_system, ISerializableNode* node, UString& text ) const
{
	if ( node == _null )
		return _false;

	// Get the structure name
	UString struct_name;
	if ( node->Read( L"name", struct_name ) == _false )
		return _false;

	// Begin to build structure
	text += "struct " + struct_name + "\n{\n";

	// Build members
	ISerializableNodeRef child_node = node->GetFirstChildNode( );
	if ( child_node.IsValid( ) )
	{
		do
		{
			// Get the child node name
			WString node_name = child_node->GetNodeName( );

			// The code string
			UString code_string;

			// It's variable
			if ( node_name == L"Variable" )
			{
				// Generate the variable string
				if ( GenerateVarDeclString( is_embedded_system, child_node, code_string ) == _false )
					return _false;
			}
			// Unknown tag
			else
			{
				ALOG_ERROR_1( "Unknown '%s' node tag to generate shader's structure declaration", node_name.Str( ) );
				return _false;
			}

			// Update the shader code string
			if ( code_string.IsEmpty( ) == _false )
			{
				text += code_string;
				text += "\n";
			}

		} while ( child_node->MoveNext( ) );
	}

	// End to build structure
	text += "};\n";

	return _true;
}

}