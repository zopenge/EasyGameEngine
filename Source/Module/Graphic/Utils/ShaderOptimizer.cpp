//! @file     ShaderOptimizer.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// ShaderOptimizer Implementation
//----------------------------------------------------------------------------

ShaderOptimizer::ShaderOptimizer( )
{
}

ShaderOptimizer::~ShaderOptimizer( )
{
}

_ubool ShaderOptimizer::IsUseVarBySelf( AStringPtr code, AStringPtr var_name ) const
{
	_dword index = StringFormatter::SearchL2R< _chara, AStringPtr >( code, var_name, _true );
	if ( index == -1 )
		return _false;

	code = code.SubString( index + var_name.GetLength( ) );
	if ( StringFormatter::SearchL2R< _chara, AStringPtr >( code, var_name, _true ) == -1 )
		return _false;

	return _true;
}

_ubool ShaderOptimizer::IsSkipShaderCode( _dword line_number, const MacroSectionInfoArray& macro_sections ) const
{
	for ( _dword i = 0; i < macro_sections.Number( ); i ++ )
	{
		const MacroSectionInfo& macro_section = macro_sections[i];

		if ( !macro_section.mMacroEnable && line_number >= macro_section.mStartLineNumber && line_number <= macro_section.mEndLineNumber )
			return _true;
	}

	// Keep it
	return _false;
}

_ubool ShaderOptimizer::IsNumber( _chara ch ) const
{
	if ( ch >= '0' && ch <= '9' )
		return _true;

	return _false;
}

_ubool ShaderOptimizer::IsWord( _chara ch ) const
{
	if ( ch >= 'A' && ch <= 'Z' )
		return _true;

	if ( ch >= 'a' && ch <= 'z' )
		return _true;

	return _false;
}

_ubool ShaderOptimizer::SplitExpression( const AString& expression, _int start, _int end, SubStringIndexArray& sub_string_array, _ubool is_or ) const
{
	_int sub_start = start;
	_int brackets_count = 0;
	for ( _int i = sub_start; i <= end; ++ i )
	{
		if ( expression[i] == '(' )
		{
			brackets_count ++;
		}
		else if ( expression[i]== ')' )
		{
			brackets_count --;
		}
		else
		{
			if ( brackets_count == 0 && i < end )
			{
				_chara dividch = is_or ? '|' : '^';
				if ( expression[i] == dividch && expression[i + 1] == dividch )
				{
					sub_string_array.Append( SubStringIndex( sub_start, i - 1 ) );
					sub_start = i + 2;
				}
			}	
		}
	}

	if ( brackets_count != 0 )
		return _false;

	if ( sub_start > end  )
		return _false;

	sub_string_array.Append( SubStringIndex( sub_start, end ) );

	return _true;
}

_ubool ShaderOptimizer::CheckExpression( const AStringArray& enabled_macros, const AString& expression, _int start, _int end, _ubool& result ) const
{
	if ( (_int)expression.GetLength( ) <= start )
		return _false;

	if ( start > end )
		return _false;

	// check or
	SubStringIndexArray or_token_array;
	if ( SplitExpression( expression, start, end, or_token_array, _true ) == _false )
		return _false;

	if ( or_token_array.Number( ) > 1 )
	{
		result = _false;
		for ( _dword i = 0; i < or_token_array.Number( ); ++ i )
		{
			_ubool ret = _false;
			if ( CheckExpression( enabled_macros, expression, or_token_array[i].mObject1, or_token_array[i].mObject2, ret ) == _false )
				return _false;

			if ( ret )
			{
				result = _true;
				break;
			}
		}
		return _true;
	}
	// check and
	SubStringIndexArray and_token_array;
	if ( SplitExpression( expression, start, end, and_token_array, _false ) == _false )
		return _false;

	if ( and_token_array.Number( ) > 1 )
	{
		result = _true;
		for ( _dword i = 0; i < and_token_array.Number( ); ++ i )
		{
			_ubool ret = _false;
			if ( CheckExpression( enabled_macros, expression, and_token_array[i].mObject1, and_token_array[i].mObject2, ret ) == _false )
				return _false;

			if ( !ret )
			{
				result = _false;
				break;
			}
		}
		return _true;
	}

	// check not
	if ( expression[start] == '!' )
	{
		_ubool ret = _false;
		if ( CheckExpression( enabled_macros, expression, start + 1, end, ret ) == _false )
			return _false;

		result = !ret;
		return _true;
	}
	// check brackets
	else if ( expression[start] == '(' )
	{
		_int sub_start = start + 1;
		_int brackets_count = 0;
		_int right_brackets_index = -1;
		for ( _int i = sub_start; i <= end; ++ i )
		{
			if ( expression[i] == '(' )
			{
				brackets_count ++;
			}
			else if ( expression[i]== ')' )
			{
				if ( brackets_count == 0 )
				{
					right_brackets_index = i;
					break;
				}
				else
				{
					brackets_count --;
				}
			}
		}
		if ( right_brackets_index == -1 )
			return _false;

		return CheckExpression( enabled_macros, expression, sub_start, right_brackets_index - 1, result );
	}
	
	// check value
	AString token = expression.SubString( start, end - start + 1 );
	result = enabled_macros.SearchAscending( token ).IsValid( );
	return _true;
}

_ubool ShaderOptimizer::CheckExpression( const AStringArray& enabled_macros, const AString& expression ) const
{
	_ubool ret = _false;
	if ( CheckExpression( enabled_macros, expression, 0, expression.GetLength( ) - 1, ret ) == _false )
		return _false;

	return ret;
}

_void ShaderOptimizer::RemoveUnusedShaderCode( const AStringArray& enabled_macros, AString& code ) const
{
	AStringArray codes;
	StringFormatter::SplitString( code, codes, "\n", " \t" );

	MacroSectionInfoStack macro_sections;
	MacroSectionInfoArray finished_macro_sections;

	for ( _dword i = 0; i < codes.Number( ); i ++ )
	{
		AString& code_line = codes[i];

		if ( code_line.StartsWith( "#if" ) )
		{
			AString macro_names = code_line.SubString( 3 );
			macro_names.RemoveChar( ' ' );
			macro_names.RemoveChar( '\t' );

			MacroSectionInfo macro_section;
			macro_section.mStartLineNumber	= i;
			macro_section.mMacroEnable = CheckExpression( enabled_macros, macro_names );
			macro_section.mMacroCanEnable = !macro_section.mMacroEnable;

			macro_sections.Push( macro_section );

			code_line = "";
		}
		else if ( code_line.StartsWith( "#elif" ) )
		{
			MacroSectionInfo& prev_macro_section	= macro_sections.Top( );
			prev_macro_section.mEndLineNumber		= i - 1;
			_ubool can_enable						= prev_macro_section.mMacroCanEnable;

			finished_macro_sections.Append( prev_macro_section );

			macro_sections.Pop( );

			AString macro_names = code_line.SubString( 5 );
			macro_names.RemoveChar( ' ' );
			macro_names.RemoveChar( '\t' );

			MacroSectionInfo macro_section;
			macro_section.mStartLineNumber	= i;
			macro_section.mMacroEnable = CheckExpression( enabled_macros, macro_names ) && can_enable;
			macro_section.mMacroCanEnable = can_enable && !macro_section.mMacroEnable;

			macro_sections.Push( macro_section );

			code_line = "";
		}
		else if ( code_line.StartsWith( "#else" ) )
		{
			MacroSectionInfo& prev_macro_section	= macro_sections.Top( );
			prev_macro_section.mEndLineNumber		= i - 1;
			_ubool can_enable						= prev_macro_section.mMacroCanEnable;
			finished_macro_sections.Append( prev_macro_section );

			macro_sections.Pop( );

			MacroSectionInfo macro_section;
			macro_section.mStartLineNumber	= i;
			macro_section.mMacroEnable = can_enable;

			macro_sections.Push( macro_section );

			code_line = "";
		}
		else if ( code_line.StartsWith( "#endif" ) )
		{
			MacroSectionInfo& prev_macro_section	= macro_sections.Top( );
			prev_macro_section.mEndLineNumber		= i - 1;
			finished_macro_sections.Append( prev_macro_section );

			macro_sections.Pop( );

			code_line = "";			
		}
	}

	// Rebuild shader code
	code = "";
	for ( _dword i = 0; i < codes.Number( ); i ++ )
	{
		AString code_line = codes[i];

		if ( code_line.IsEmpty( ) || code_line == ";" )
			continue;

		if ( IsSkipShaderCode( i, finished_macro_sections ) )
			continue;

		code += code_line;
		code += "\n";
	}
}

_dword ShaderOptimizer::SearchTokenInCode( AStringPtr code, AStringPtr token ) const
{
	AStringPtr sub_code = code;
	_dword curr_index = 0;
	while ( _true )
	{
		_dword search_index = sub_code.SearchL2R( token );
		if ( search_index != - 1 )
		{
			_chara char_next = sub_code[search_index + token.GetLength( )];
			if ( !IsNumber( char_next ) && !IsWord( char_next ) && char_next != '_' )
			{
				if ( search_index == 0 )
				{
					return curr_index + search_index;
				}
				else
				{
					_chara char_prev = sub_code[search_index - 1];
					if ( !IsWord( char_prev ) && char_prev != '_' )
						return curr_index + search_index;
				}
			}
			curr_index += search_index + token.GetLength( );
			sub_code = sub_code.SubString( search_index + token.GetLength( ) );
		}
		else
		{
			break;
		}
	}
	
	return -1;
}

_ubool ShaderOptimizer::RemoveUnusedVaryingVars( AString& code, const AStringArray& unused_vs_var_codes ) const
{
	_ubool removed = _false;

	AStringArray codes;
	StringFormatter::SplitString( code, codes, "\n", " \t" );

	code = "";
	for ( _dword i = 0; i < codes.Number( ); i ++ )
	{
		AStringPtr code_line = codes[i];

		_ubool skip = _false;
		for ( _dword j = 0; j < unused_vs_var_codes.Number( ); j ++ )
		{
			_dword search_index = SearchTokenInCode( code_line, unused_vs_var_codes[j] );
			if ( search_index != -1 )
			{
				skip = _true;
				break;
			}
		}

		if ( skip )
		{
			removed = _true;
			continue;
		}

		code += code_line;
		code += "\n";
	}

	return removed;
}

_ubool ShaderOptimizer::RemoveUnusedVaryingVars( AString& vs_code, AString& ps_code ) const
{
	// Get the VS main function content
	_dword	vs_main_begin_index	= vs_code.SearchL2R( '{' );
	_dword	vs_main_end_index	= vs_code.SearchR2L( '}' );
	AString vs_content			= vs_code.SubString( vs_main_begin_index, vs_main_end_index - vs_main_begin_index );
	vs_content.TrimRight( "{}" );

	// Get the PS main function content
	_dword	ps_main_begin_index	= ps_code.SearchL2R( '{' );
	_dword	ps_main_end_index	= ps_code.SearchR2L( '}' );
	AString ps_content			= ps_code.SubString( ps_main_begin_index, ps_main_end_index - ps_main_begin_index );
	ps_content.TrimRight( "{}" );

	AStringArray vs_codes;
	StringFormatter::SplitString( vs_code, vs_codes, "\n", " \t" );

	AStringArray unused_var_codes;
	for ( _dword i = 0; i < vs_codes.Number( ); i ++ )
	{
		AString vs_code_line = vs_codes[i];

		if ( vs_code_line.StartsWith( "varying " ) == _false )
			continue;

		// Parse the varying variable declaration
		_dword index = vs_code_line.SearchR2L( ' ' );
		EGE_ASSERT( index != -1 );

		// Get the variable name
		AString var_name = vs_code_line.SubString( index + 1 );
		var_name.TrimRight( " \t;" );

		// Check whether it's use in vs/ps code
		if ( SearchTokenInCode( ps_content, var_name ) == -1 )
		{
			if ( IsUseVarBySelf( vs_content, var_name ) == _false )
				unused_var_codes.InsertAscending( var_name );
		}
	}

	// Remove unused varying variables
	_ubool removed = _false;
	removed |= RemoveUnusedVaryingVars( vs_code, unused_var_codes );
	removed |= RemoveUnusedVaryingVars( ps_code, unused_var_codes );

	return removed;
}

_ubool ShaderOptimizer::DeclareUnusedVaryingVarsAsLocal( AString& vs_code, const AString& ps_code ) const
{
	// Get the VS main function content
	_dword	vs_main_begin_index	= vs_code.SearchL2R( '{' );
	_dword	vs_main_end_index	= vs_code.SearchR2L( '}' );
	AString vs_content			= vs_code.SubString( vs_main_begin_index, vs_main_end_index - vs_main_begin_index );
	vs_content.TrimRight( "{}" );

	// Get the PS main function content
	_dword	ps_main_begin_index	= ps_code.SearchL2R( '{' );
	_dword	ps_main_end_index	= ps_code.SearchR2L( '}' );
	AString ps_content			= ps_code.SubString( ps_main_begin_index, ps_main_end_index - ps_main_begin_index );
	ps_content.TrimRight( "{}" );

	AStringArray vs_codes;
	StringFormatter::SplitString( vs_code, vs_codes, "\n", " \t" );

	AStringArray decl_as_local_vars;
	for ( _dword i = 0; i < vs_codes.Number( ); i ++ )
	{
		AString vs_code_line = vs_codes[i];

		if ( vs_code_line.StartsWith( "varying " ) == _false )
			continue;

		AStringArray var_array;
		StringFormatter::SplitString( vs_code_line, var_array, " ", " \t;" );
		if ( var_array.Number( ) < 3 )
			continue;

		AString var_type = var_array[var_array.Number( ) - 2];
		AString var_name = var_array[var_array.Number( ) - 1];

		// Check whether it's use in vs/ps code
		if ( SearchTokenInCode( ps_content, var_name ) == -1 )
		{
			decl_as_local_vars.InsertAscending( var_name );
		}
	}

	// Remove unused varying variables
	return DeclareUnusedVaryingVarsAsLocal( vs_code, decl_as_local_vars, _true );
}

_ubool ShaderOptimizer::DeclareUnusedVaryingVarsAsLocal( AString& code, const AStringArray& decl_as_local_vars, _ubool is_vs_code ) const
{
	_ubool removed = _false;

	AStringArray codes;
	StringFormatter::SplitString( code, codes, "\n", " \t" );

	code = "";
	for ( _dword i = 0; i < codes.Number( ); i ++ )
	{
		AString& code_line = codes[i];

		if ( code_line.StartsWith( "varying " ) )
		{
			// Get the varying variable name
			AString var_type, var_name;
			StringFormatter::ParseString( code_line.Str( ), "varying %s %s", var_type, var_name );
			var_name.TrimRight( " \t;" );

			if ( decl_as_local_vars.SearchAscending( var_name ).IsValid( ) )
			{
				if ( is_vs_code )
					code_line.Remove( 0, 8 );
				else
					continue;
			}
		}

		code += code_line;
		code += "\n";
	}

	return removed;
}

_void ShaderOptimizer::BuildEnabledMacros( const GraphicEffectInitializer& initializer, AStringArray& enable_macros ) const
{
	// Check enable functions
	{
		// The macro values and names table
		static const _GRAPHIC_EFFECT_FUNCTION	macro_values[]	= { GEF_TABLE( GEF_ENUM ) };
		static const AStringPtr					macro_names[]	= { GEF_TABLE( GEF_NAME ) };

		// Check enabled functions one by one
		for ( _dword i = 0; i < EGE_ARRAY_NUMBER( macro_values ); i ++ )
		{
			if ( initializer.mEnabledFunctions.HasFlags( 1 << i ) )
				enable_macros.InsertAscending( macro_names[i] );
		}
	}

	// Check enable light slot functions
	{
		// The macro values and names table
		static const _GRAPHIC_EFFECT_LIGHT_SLOT_FUNCTION	macro_values[]	= { GELSF_TABLE( GELSF_ENUM ) };
		static const AStringPtr								macro_names[]	= { GELSF_TABLE( GELSF_NAME ) };

		// Check enabled functions one by one in slot
		for ( _dword i = 0; i < _GLS_MAX_NUMBER; i ++ )
		{
			_dword flags = initializer.mEnabledLightSlotFunctions[i];

			for ( _dword j = 0; j < EGE_ARRAY_NUMBER( macro_names ); j ++ )
			{
				if ( flags & macro_values[j] )
				{
					AString macro_name = FORMAT_ASTRING_2( "%s%d", macro_names[j].Str( ), i );
					enable_macros.InsertAscending( macro_name );
				}
			}
		}
	}

	// Check color operations
	{
		_GRAPHIC_COLOR_OPERATION color_operations[] =
		{
			initializer.mDiffuseMapColorOperation,
			initializer.mMirrorOperation,
		};

		static AStringPtr color_key_names[] =
		{
			"_DIFFUSE_MAP_COLOR_",
			"_MIRROR_",
		};
		static AStringPtr color_operation_names[] =
		{
			"",
			"OPERATION_ADD_",
			"OPERATION_SUB_",
			"OPERATION_MUL_",
			"OPERATION_MIX_",
			"OPERATION_RANGE_",
			"OPERATION_GREY_",
			"OPERATION_ORIGIN_",
			"OPERATION_COLOR_DODGE_",
		};

		for ( _dword i = 0; i < EGE_ARRAY_NUMBER( color_operations ); i ++ )
		{
			AStringPtr name = color_operation_names[color_operations[i]];
			if ( name.IsEmpty( ) )
				continue;

			AString macro_name = color_key_names[i] + name;
			enable_macros.InsertAscending( macro_name );
		}
	}
}

_ubool ShaderOptimizer::BuildShaderCodeText( ISerializableNode* root, WStringPtr node_name, AString& shader_code ) const
{
	ISerializableNodeRef shader_node = root->GetChildNodeByName( node_name );
	if ( shader_node.IsNull( ) )
		return _false;

	// Get the version text
	AString version_text;
	if ( shader_node->Read( L"version", version_text ) == _false )
		return _false;

	// Get the shader text
	AString shader_text = shader_node->GetTextA( );

	// Build shader code text
	shader_code = version_text + "\n" + shader_text;

	return _true;
}

_ubool ShaderOptimizer::ReadOptimizedShaderCodeText( ISerializableNode* root, WStringPtr node_name, AString& shader_code ) const
{
	ISerializableNodeRef shader_node = root->GetChildNodeByName( node_name );
	if ( shader_node.IsNull( ) )
		return _false;

	// Build shader code text
	shader_code = shader_node->GetTextA( );

	return _true;
}

_ubool ShaderOptimizer::CheckVaryingVariablesNumber( AStringPtr ps_code ) const
{
#ifdef _DEBUG
	// Copy shader code
	AString ps_code_tmp = ps_code;

	// The varying variables size in bytes
	_dword varying_vars_size = 0;

	while ( _true )
	{
		_dword index = ps_code_tmp.SearchL2R( "varying " );
		if ( index == -1 )
			break;

		_dword type_index = ps_code_tmp.SubString( index + 8 ).SearchL2R( " " );
		if ( type_index == -1 )
			break;

		// Get the variable type
		AString var_type = ps_code_tmp.SubString( index + 8, type_index );
		
		// Update the total varying variables size
		if ( var_type == "float" )
			varying_vars_size += sizeof( _float );
		else if ( var_type == "vec2" )
			varying_vars_size += sizeof( _float ) * 2;
		else if ( var_type == "vec3" )
			varying_vars_size += sizeof( _float ) * 3;
		else if ( var_type == "vec4" )
			varying_vars_size += sizeof( _float ) * 4;

		// Continue to find varying variable
		ps_code_tmp = ps_code_tmp.SubString( index + 8 );
	}

	// Get the shader compile config info
	const ShaderCompileConfigInfo& config = gDynamicRHI->GetShaderCompileConfigInfo( );

	// Get the max varying variables size in bytes
	const _dword cMaxVaryingVariablesSize = config.mMaxVaryingVectorsNumber * sizeof( Vector4 );
	if ( cMaxVaryingVariablesSize < varying_vars_size )
	{
		WLOG_ERROR_2( L"The varying variables size is out of range( cur: %d, max: %d )", varying_vars_size, cMaxVaryingVariablesSize );
		EGE_ASSERT( _false );
		return _false;
	}
#endif

	return _true;
}

_ubool ShaderOptimizer::IsEmbeddedSystem( _GRAPHIC_EMBEDDED_SYSTEM embedded_system ) const
{
	// Check whether it's embedded system
	_ubool is_embedded_system = _false;
	switch ( embedded_system )
	{
		case _EMBEDDED_SYSTEM_UNKNOWN:
			is_embedded_system = RenderUtils::IsEmbeddedSystem( );
			break;

		case _EMBEDDED_SYSTEM_YES:
			is_embedded_system = _true;
			break;

		case _EMBEDDED_SYSTEM_NO:
			is_embedded_system = _false;
			break;

		default:
			break;
	}

	return is_embedded_system;
}

WStringPtr ShaderOptimizer::GetPSNodeName( _GRAPHIC_EMBEDDED_SYSTEM embedded_system ) const
{
	if ( IsEmbeddedSystem( embedded_system ) )
		return L"EmbeddedPS";
	else
		return L"PS";
}

WStringPtr ShaderOptimizer::GetVSNodeName( _GRAPHIC_EMBEDDED_SYSTEM embedded_system ) const
{
	if ( IsEmbeddedSystem( embedded_system ) )
		return L"EmbeddedVS";
	else
		return L"VS";
}

_ubool ShaderOptimizer::ExportTechniqueCodeInXMLFormat( _GRAPHIC_EMBEDDED_SYSTEM embedded_system, AStringPtr vs_code, AStringPtr ps_code, const GraphicRenderStateInfo& render_state_info, WString& xml_string ) const
{
	ISerializableNodeRef root = GetInterfaceFactory( )->CreateXMLSerializableNode( L"<Root>\n</Root>" );
	if ( root.IsNull( ) )
		return _false;

	WString ps_code_utf16 = WString( ).FromString( ps_code );
	WString vs_code_utf16 = WString( ).FromString( vs_code );
	root->InsertChildNode( ShaderOptimizer::GetInstance( ).GetPSNodeName( embedded_system ), ps_code_utf16, _false );
	root->InsertChildNode( ShaderOptimizer::GetInstance( ).GetVSNodeName( embedded_system ), vs_code_utf16, _false );

	if ( RenderStateSerializer::ExportRenderStates( root, render_state_info ) == _false )
		return _false;

	xml_string = root->DumpToString( );

	return _true;
}

GraphicShaderSerializeInfo ShaderOptimizer::ExportTechniqueCodeInXMLFormat( _GRAPHIC_EMBEDDED_SYSTEM embedded_system, AStringPtr vs_code, AStringPtr ps_code, const GraphicRenderStateInfo& render_state_info ) const
{
	GraphicShaderSerializeInfo info;

	ISerializableNodeRef root = GetInterfaceFactory( )->CreateXMLSerializableNode( L"<Root>\n</Root>" );
	if ( root.IsNull( ) )
		return info;

	WString ps_code_utf16 = WString( ).FromString( ps_code );
	WString vs_code_utf16 = WString( ).FromString( vs_code );
	ISerializableNodeRef ps_node = root->InsertChildNode( ShaderOptimizer::GetInstance( ).GetPSNodeName( embedded_system ), ps_code_utf16, _false );
	ISerializableNodeRef vs_node = root->InsertChildNode( ShaderOptimizer::GetInstance( ).GetVSNodeName( embedded_system ), vs_code_utf16, _false );

	if ( RenderStateSerializer::ExportRenderStates( root, render_state_info ) == _false )
		return info;

	info.mBaseInfoNode = root;
	info.mVSShaderCodeNode = vs_node;
	info.mPSShaderCodeNode = ps_node;

	return info;
}

GraphicShaderSerializeInfo ShaderOptimizer::ExportTechniqueCodeInXMLFormat( const GraphicEffectInitializer& initializer, const GraphicShaderInitializer& shader_initializer ) const
{
	AString name, vs_code, ps_code;
	GraphicRenderStateInfo render_state_info;
	if ( OptimizeShaderCode( initializer, shader_initializer, name, vs_code, ps_code, render_state_info ) == _false )
		return GraphicShaderSerializeInfo( );

	return ExportTechniqueCodeInXMLFormat( initializer.mEmbeddedSystem, vs_code, ps_code, render_state_info );
}

_ubool ShaderOptimizer::OptimizeShaderCode( _GRAPHIC_EMBEDDED_SYSTEM embedded_system, ISerializableNode* vs_node, ISerializableNode* ps_node, AString& vs_code, AString& ps_code ) const
{
	if ( vs_node == _null || ps_node == _null )
		return _false;

	// Get the VS and PS node name
	WStringPtr vs_node_name = ShaderOptimizer::GetInstance( ).GetVSNodeName( embedded_system );
	WStringPtr ps_node_name = ShaderOptimizer::GetInstance( ).GetPSNodeName( embedded_system );

	// Read the optimized PS code
	if ( ReadOptimizedShaderCodeText( ps_node, ps_node_name, ps_code ) == _false )
		return _false;

	// Read the optimized VS code
	if ( ReadOptimizedShaderCodeText( vs_node, vs_node_name, vs_code ) == _false )
		return _false;

	// Check the varying variables number
	if ( CheckVaryingVariablesNumber( ps_code ) == _false )
		return _false;

	return _true;
}

_ubool ShaderOptimizer::OptimizeShaderCode( const GraphicEffectInitializer& initializer, ISerializableNode* vs_node, ISerializableNode* ps_node, AString& vs_code, AString& ps_code ) const
{
	if ( vs_node == _null || ps_node == _null )
		return _false;

	// Read the optimized shader code
	if ( initializer.mFlags.HasFlags( GraphicEffectInitializer::_FLAG_HAS_OPTIMIZED ) )
	{
		if ( OptimizeShaderCode( initializer.mEmbeddedSystem, vs_node, ps_node, vs_code, ps_code ) == _false )
			return _false;
	}
	// Build the dynamic shader code 
	else
	{
		// Get the VS and PS node name
		WStringPtr vs_node_name = ShaderOptimizer::GetInstance( ).GetVSNodeName( initializer.mEmbeddedSystem );
		WStringPtr ps_node_name = ShaderOptimizer::GetInstance( ).GetPSNodeName( initializer.mEmbeddedSystem );

		// Build enabled macros
		AStringArray enabled_macros;
		BuildEnabledMacros( initializer, enabled_macros );

		// Build PS shader code text
		if ( BuildShaderCodeText( ps_node, ps_node_name, ps_code ) == _false )
			return _false;

		// Build VS shader code text
		if ( BuildShaderCodeText( vs_node, vs_node_name, vs_code ) == _false )
			return _false;

		// Check whether it's embedded system
		_ubool is_embedded_system = IsEmbeddedSystem( initializer.mEmbeddedSystem );

		// Optimize shader code
		if ( ShaderOptimizer::GetInstance( ).OptimizeGLSLCode( enabled_macros, is_embedded_system, vs_code, ps_code ) == _false )
			return _false;

		// Check the varying variables number
		if ( CheckVaryingVariablesNumber( ps_code ) == _false )
			return _false;
	}

	return _true;
}

_ubool ShaderOptimizer::OptimizeGLSLCode( const AStringArray& enabled_macros, _ubool is_embedded_system, AString& vs_code, AString& ps_code ) const
{
	AString optimized_vs_code, optimized_ps_code;

	// 1. Remove the unused shader code by macros
	RemoveUnusedShaderCode( enabled_macros, vs_code );
	RemoveUnusedShaderCode( enabled_macros, ps_code );

	// 2. Remove all unused varying vars
	while ( RemoveUnusedVaryingVars( vs_code, ps_code ) ) { }

	// 3. Optimize PS code ( it will removed unused varying variables operation code )
	if ( GLSLOptimizer::GetInstance( ).OptimizePSCode( is_embedded_system, ps_code, optimized_ps_code ) == _false )
		return _false;

	// 4. Declare unused vars as local
	while ( DeclareUnusedVaryingVarsAsLocal( vs_code, optimized_ps_code ) ) { }

	// 5. Optimize VS code
	if ( GLSLOptimizer::GetInstance( ).OptimizeVSCode( is_embedded_system, vs_code, optimized_vs_code ) == _false )
		return _false;

	// 6. Finally we get the optimized GLSL code
	vs_code = optimized_vs_code;
	ps_code = optimized_ps_code;

	// 7. Fit the best size to reduce memory usage
	vs_code.ShrinkToFit( );
	ps_code.ShrinkToFit( );

	return _true;
}

_ubool ShaderOptimizer::OptimizeShaderCode( const GraphicEffectInitializer& initializer, const GraphicShaderInitializer& shader_initializer, AString& vs_code, AString& ps_code ) const
{
	GraphicShaderSerializeInfo info = shader_initializer.ToSerializeInfo( );
	if ( !info.IsValid( ) )
		return _false;

	// Optimize shader code
	if ( OptimizeShaderCode( initializer, info.mVSShaderCodeNode, info.mPSShaderCodeNode, vs_code, ps_code ) == _false )
		return _false;

	return _true;
}

_ubool ShaderOptimizer::OptimizeShaderCode( const GraphicEffectInitializer& initializer, const GraphicShaderInitializer& shader_initializer, AString& name, AString& vs_code, AString& ps_code ) const
{
	GraphicShaderSerializeInfo info = shader_initializer.ToSerializeInfo( );
	if ( !info.IsValid( ) )
		return _false;

	// Read the node name (optional)
	info.mBaseInfoNode->Read( L"name", name );

	// Optimize shader code
	if ( OptimizeShaderCode( initializer, info.mVSShaderCodeNode, info.mPSShaderCodeNode, vs_code, ps_code ) == _false )
		return _false;

	return _true;
}

_ubool ShaderOptimizer::OptimizeShaderCode( const GraphicEffectInitializer& initializer, const GraphicShaderInitializer& shader_initializer, AString& name, AString& vs_code, AString& ps_code, GraphicRenderStateInfo& render_state_info ) const
{
	GraphicShaderSerializeInfo info = shader_initializer.ToSerializeInfo( );
	if ( !info.IsValid( ) )
		return _false;

	// Read the node name (optional)
	info.mBaseInfoNode->Read( L"name", name );

	// Optimize shader code
	if ( OptimizeShaderCode( initializer, info.mVSShaderCodeNode, info.mPSShaderCodeNode, vs_code, ps_code ) == _false )
		return _false;

	// Import render state(could be empty)
	if ( RenderStateSerializer::ImportRenderStates( info.mBaseInfoNode, render_state_info ) == _false )
		return _false;

	return _true;
}

_ubool ShaderOptimizer::OptimizeShaderCode( const GraphicEffectInitializer& initializer, AStringPtr technique_node, AString& vs_code, AString& ps_code ) const
{
	return OptimizeShaderCode( initializer, GraphicShaderAStringInitializer( technique_node ), vs_code, ps_code );
}

_ubool ShaderOptimizer::OptimizeShaderCode( const GraphicEffectInitializer& initializer, AStringPtr technique_node, AString& name, AString& vs_code, AString& ps_code ) const
{
	return OptimizeShaderCode( initializer, GraphicShaderAStringInitializer( technique_node ), name, vs_code, ps_code );
}

_ubool ShaderOptimizer::OptimizeShaderCode( const GraphicEffectInitializer& initializer, AStringPtr technique_node, AString& name, AString& vs_code, AString& ps_code, GraphicRenderStateInfo& render_state_info ) const
{
	return OptimizeShaderCode( initializer, GraphicShaderAStringInitializer( technique_node ), name, vs_code, ps_code, render_state_info );
}