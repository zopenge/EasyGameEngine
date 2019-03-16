//! @file     IScriptResourceManager.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IScriptResourceManager
//----------------------------------------------------------------------------

class IScriptResourceManager : public IObject
{
public:
	//!	Register the class.
	//! @param		name		The class name.
	//!	@param		desc		The class description.
	//!	@param		size		The class size.
	//! @return		The script class interface.
	virtual IScriptClassRef RegisterClass( AStringPtr name, AStringPtr desc, _dword size ) PURE;
	//!	Get the registered class.
	//! @param		name		The class name.
	//! @return		The script class interface.
	virtual IScriptClassRef GetRegisteredClassByName( AStringPtr name ) const PURE;
	//!	Check whether has the registered class.
	//! @param		name			The class name.
	//! @return		True indicates the registered class is existing.
	virtual _ubool HasRegisteredClass( AStringPtr name ) const PURE;

	//!	Register class function.
	//! @param		name			The class name.
	//!	@param		decl			The function declaration.
	//!	@param		funcpointer		The function pointer.
	//!	@param		desc			The function description.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool RegisterClassFunction( AStringPtr name, AStringPtr decl, const ScriptFuncPtr& funcpointer, AStringPtr desc ) PURE;

	//!	Register behaviour function.
	//!	@param		name		The object type name.
	//!	@param		behaviour	The object behaviour ID.
	//!	@param		funcpointer	The function pointer.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool RegisterBehaviourFunction( AStringPtr name, _SCRIPT_CLASS_BEHAVIOUR behaviour, const ScriptFuncPtr& funcpointer ) PURE;
	//!	Invoke constructor behaviour function.
	//!	@param		object		The object pointer.
	//!	@param		name		The object type name.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool InvokeConstructorBehaviourFunc( _byte*& object, AStringPtr name ) PURE;
	//!	Invoke destructor behaviour function.
	//!	@param		object		The object pointer.
	//!	@param		name		The object type name.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool InvokeDestructorBehaviourFunc( _byte*& object, AStringPtr name ) PURE;
	//!	Invoke copy behaviour function.
	//!	@param		object		The target object pointer.
	//!	@param		from_object	The source object pointer.
	//!	@param		name		The object type name.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool InvokeCopyBehaviourFunc( _byte*& object, const _byte* from_object, AStringPtr name ) PURE;

	//!	Parse native property info.
	//!	@param		declaration			The property declaration.
	//!	@param		offset				The property offset in bytes.
	//!	@param		decl_info			The property declaration info.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ParseNativePropertyInfo( AStringPtr declaration, _dword offset, ScriptPropertyDeclInfo& decl_info ) const PURE;
	//!	Parse native function info.
	//!	@param		declaration			The function declaration.
	//!	@param		funcpointer			The function pointer.
	//!	@param		decl_info			The function declaration info.
	//!	@param		native_func_info	The function native info.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ParseNativeFuncInfo( AStringPtr declaration, const ScriptFuncPtr& funcpointer, ScriptFuncDeclInfo& decl_info, ScriptNativeFuncInfo& native_func_info ) const PURE;

	//!	Create the script virtual machine.
	//!	@param		none.
	//!	@return		The script virtual machine interface.
	virtual IScriptVMPassRef CreateScriptVM( ) PURE;

	//!	Preload module.
	//!	@param		name	The module name.
	//!	@param		code	The script code.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool PreloadModule( AStringPtr name, AStringPtr code ) PURE;
};

}