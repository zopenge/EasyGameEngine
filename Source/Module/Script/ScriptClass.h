//! @file     ScriptClass.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ScriptClass
//----------------------------------------------------------------------------

class ScriptClass : public TObject< IScriptClass >
{
private:
	//!	The class declaration info
	ScriptClassDeclInfo	mDeclInfo;

	//!	The script module
	_scriptModuleRef	mScriptModule;

public:
	ScriptClass( );
	virtual ~ScriptClass( );

public:
	//!	Initialize.
	_ubool Initialize( AStringPtr name, AStringPtr desc, _dword size );

// IScriptClass Interface
public:
	virtual _ubool						RegisterEnumValue( AStringPtr name, _dword value, AStringPtr desc ) override;
	virtual _ubool						RegisterProperty( AStringPtr decl, _dword offset, AStringPtr desc ) override;

	virtual const ScriptClassDeclInfo&	GetDeclInfo( ) const override;

	virtual _ubool						RegisterFunction( AStringPtr decl, const ScriptFuncPtr& funcpointer, AStringPtr desc ) override;
};

}