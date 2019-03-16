//! @file     _pySystem.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _pySystem
//----------------------------------------------------------------------------

class _pySystem : public _t_scriptSystem< _scriptSystem >
{
private:

private:
	//!	Load python libraries.
	_ubool LoadLibraries( );

public:
	_pySystem( );
	virtual ~_pySystem( );

// IObject Interface
public:
	virtual _void				Tick( _dword limited_elapse, _dword elapse ) override;

// _scriptSystem Interface
public:
	virtual _ubool				Initialize( ) override;

	virtual _scriptModuleRef	CreateScriptModule( AStringPtr name, AStringPtr desc ) override;

	virtual _scriptVMPassRef	CreateScriptVM( ) override;
};

}