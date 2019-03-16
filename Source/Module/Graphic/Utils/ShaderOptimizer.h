//! @file     ShaderOptimizer.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ShaderOptimizer
//----------------------------------------------------------------------------

class ShaderOptimizer
{
	SINGLETON( ShaderOptimizer )

private:
	//!	The macro section info
	struct MacroSectionInfo
	{
		_ubool	mMacroCanEnable;
		_ubool	mMacroEnable;
		_dword	mStartLineNumber; // Start from 0
		_dword	mEndLineNumber;

		MacroSectionInfo( )
		{
			mMacroCanEnable = _true;
			mMacroEnable = _false;
			mStartLineNumber = 0;
			mEndLineNumber = 0;
		}
	};
	typedef Stack< MacroSectionInfo > MacroSectionInfoStack;
	typedef Array< MacroSectionInfo > MacroSectionInfoArray;

	typedef Pair< _int, _int >	SubStringIndex;
	typedef Array< SubStringIndex >	SubStringIndexArray;

private:
	//!	Check whether use variable by self.
	_ubool IsUseVarBySelf( AStringPtr code, AStringPtr var_name ) const;
	//!	Check whether skip specific shader code by line number.
	_ubool IsSkipShaderCode( _dword line_number, const MacroSectionInfoArray& macro_sections ) const;

	_ubool IsNumber( _chara ch ) const;
	_ubool IsWord( _chara ch ) const;
	_ubool SplitExpression( const AString& expression, _int start, _int end, SubStringIndexArray& sub_string_array, _ubool is_or ) const;
	_ubool CheckExpression( const AStringArray& enabled_macros, const AString& expression, _int start, _int end, _ubool& result ) const;
	_ubool CheckExpression( const AStringArray& enabled_macros, const AString& expression ) const;
	//!	Remove unused shader code.
	_void RemoveUnusedShaderCode( const AStringArray& enabled_macros, AString& code ) const;
	//!	Remove unused varying variables.
	_dword SearchTokenInCode( AStringPtr code, AStringPtr token ) const;
	_ubool RemoveUnusedVaryingVars( AString& vs_code, AString& ps_code ) const;
	_ubool RemoveUnusedVaryingVars( AString& code, const AStringArray& unused_vs_var_codes ) const;
	_ubool DeclareUnusedVaryingVarsAsLocal( AString& vs_code, const AString& ps_code ) const;
	_ubool DeclareUnusedVaryingVarsAsLocal( AString& code, const AStringArray& decl_as_local_vars, _ubool is_vs_code ) const;

	//!	Build enabled macros.
	_void BuildEnabledMacros( const GraphicEffectInitializer& initializer, AStringArray& enable_macros ) const;
	//!	Build shader code text.
	_ubool BuildShaderCodeText( ISerializableNode* root, WStringPtr node_name, AString& shader_code ) const;
	//!	Read optimized code text.
	_ubool ReadOptimizedShaderCodeText( ISerializableNode* root, WStringPtr node_name, AString& shader_code ) const;

	//!	Check the varying variables number.
	_ubool CheckVaryingVariablesNumber( AStringPtr ps_code ) const;

	//!	Check whether it's embedded system.
	_ubool IsEmbeddedSystem( _GRAPHIC_EMBEDDED_SYSTEM embedded_system ) const;

public:
	//!	Get the PS node name.
	//!	@param		embedded_system		The embedded system.
	//!	@return		The node name.
	WStringPtr GetPSNodeName( _GRAPHIC_EMBEDDED_SYSTEM embedded_system ) const;
	//!	Get the VS node name.
	//!	@param		embedded_system		The embedded system.
	//!	@return		The node name.
	WStringPtr GetVSNodeName( _GRAPHIC_EMBEDDED_SYSTEM embedded_system ) const;

	//!	Export technique code as XML string with specified render state info.
	//!	@param		embedded_system		The embedded system.
	//!	@param		vs_code				The vertex shader code.
	//!	@param		ps_code				The pixel shader code.
	//!	@param		render_state_info	The render state info.
	//!	@param		xml_string			The XML string.
	//!	@return		True indicates success false indicates failure.
	_ubool ExportTechniqueCodeInXMLFormat( _GRAPHIC_EMBEDDED_SYSTEM embedded_system, AStringPtr vs_code, AStringPtr ps_code, const GraphicRenderStateInfo& render_state_info, WString& xml_string ) const;
	//!	Export technique code as XML string with specified render state info.
	//!	@param		embedded_system		The embedded system.
	//!	@param		vs_code				The vertex shader code.
	//!	@param		ps_code				The pixel shader code.
	//!	@param		render_state_info	The render state info.
	//!	@return		True indicates success false indicates failure.
	GraphicShaderSerializeInfo ExportTechniqueCodeInXMLFormat( _GRAPHIC_EMBEDDED_SYSTEM embedded_system, AStringPtr vs_code, AStringPtr ps_code, const GraphicRenderStateInfo& render_state_info ) const;
	//!	Export technique code as XML string with specified render state info.
	//!	@param		initializer			The initializer.
	//!	@param		shader_initializer	The shader initializer.
	//!	@return		True indicates success false indicates failure.
	GraphicShaderSerializeInfo ExportTechniqueCodeInXMLFormat( const GraphicEffectInitializer& initializer, const GraphicShaderInitializer& shader_initializer ) const;

	//! Optimize GLSL code.
	//!	@param		enabled_macros		The enabled macros.
	//!	@param		is_embedded_system	True indicates it's embedded system.
	//!	@param		vs_code				The vertex shader code.
	//!	@param		ps_code				The pixel shader code.
	//!	@return		True indicates success false indicates failure.
	_ubool OptimizeGLSLCode( const AStringArray& enabled_macros, _ubool is_embedded_system, AString& vs_code, AString& ps_code ) const;

	//! Optimize shader code.
	//!	@param		embedded_system		The embedded system.
	//!	@param		vs_node				The serializer node for vs shader code.
	//!	@param		ps_node				The serializer node for ps shader code.
	//!	@param		vs_code				The vertex shader code.
	//!	@param		ps_code				The pixel shader code.
	//!	@return		True indicates success false indicates failure.
	_ubool OptimizeShaderCode( _GRAPHIC_EMBEDDED_SYSTEM embedded_system, ISerializableNode* vs_node, ISerializableNode* ps_node, AString& vs_code, AString& ps_code ) const;
	//! Optimize shader code.
	//!	@param		initializer			The initializer.
	//!	@param		vs_node				The serializer node for vs shader code.
	//!	@param		ps_node				The serializer node for ps shader code.
	//!	@param		vs_code				The vertex shader code.
	//!	@param		ps_code				The pixel shader code.
	//!	@return		True indicates success false indicates failure.
	_ubool OptimizeShaderCode( const GraphicEffectInitializer& initializer, ISerializableNode* vs_node, ISerializableNode* ps_node, AString& vs_code, AString& ps_code ) const;
	//! Optimize shader code.
	//!	@param		initializer			The initializer.
	//!	@param		shader_initializer	The shader initializer.
	//!	@param		vs_code				The vertex shader code.
	//!	@param		ps_code				The pixel shader code.
	//!	@return		True indicates success false indicates failure.
	_ubool OptimizeShaderCode( const GraphicEffectInitializer& initializer, const GraphicShaderInitializer& shader_initializer, AString& vs_code, AString& ps_code ) const;
	//! Optimize shader code.
	//!	@param		initializer			The initializer.
	//!	@param		shader_initializer	The shader initializer.
	//! @param		name				The shader name.
	//!	@param		vs_code				The vertex shader code.
	//!	@param		ps_code				The pixel shader code.
	//!	@return		True indicates success false indicates failure.
	_ubool OptimizeShaderCode( const GraphicEffectInitializer& initializer, const GraphicShaderInitializer& shader_initializer, AString& name, AString& vs_code, AString& ps_code ) const;
	//! Optimize shader code.
	//!	@param		initializer			The initializer.
	//!	@param		shader_initializer	The shader initializer.
	//! @param		name				The shader name.
	//!	@param		vs_code				The vertex shader code.
	//!	@param		ps_code				The pixel shader code.
	//!	@param		render_state_info	The render state info.
	//!	@return		True indicates success false indicates failure.
	_ubool OptimizeShaderCode( const GraphicEffectInitializer& initializer, const GraphicShaderInitializer& shader_initializer, AString& name, AString& vs_code, AString& ps_code, GraphicRenderStateInfo& render_state_info ) const;
	//! Optimize shader code.
	//!	@param		initializer			The initializer.
	//!	@param		technique_node		The shader initializer.
	//!	@param		vs_code				The vertex shader code.
	//!	@param		ps_code				The pixel shader code.
	//!	@return		True indicates success false indicates failure.
	_ubool OptimizeShaderCode( const GraphicEffectInitializer& initializer, AStringPtr technique_node, AString& vs_code, AString& ps_code ) const;
	//! Optimize shader code.
	//!	@param		initializer			The initializer.
	//!	@param		technique_node		The shader initializer.
	//! @param		name				The shader name.
	//!	@param		vs_code				The vertex shader code.
	//!	@param		ps_code				The pixel shader code.
	//!	@return		True indicates success false indicates failure.
	_ubool OptimizeShaderCode( const GraphicEffectInitializer& initializer, AStringPtr technique_node, AString& name, AString& vs_code, AString& ps_code ) const;
	//! Optimize shader code.
	//!	@param		initializer			The initializer.
	//!	@param		technique_node		The shader initializer.
	//!	@param		vs_code				The vertex shader code.
	//!	@param		ps_code				The pixel shader code.
	//!	@param		render_state_info	The render state info.
	//!	@return		True indicates success false indicates failure.
	_ubool OptimizeShaderCode( const GraphicEffectInitializer& initializer, AStringPtr technique_node, AString& name, AString& vs_code, AString& ps_code, GraphicRenderStateInfo& render_state_info ) const;
};

//----------------------------------------------------------------------------
// ShaderOptimizer Implementation
//----------------------------------------------------------------------------

}