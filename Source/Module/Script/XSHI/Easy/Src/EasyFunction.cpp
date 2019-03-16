//! @file     EasyFunction.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

//----------------------------------------------------------------------------
// EasyDrv-Function Implementation
//----------------------------------------------------------------------------

_ubool EasyDrv::RegisterGlobalFunction( const NativeFunctionDefXSHI& def )
{
	return _true;
}

_dword EasyDrv::GetGlobalFunctionNumber( ) const
{
	return 0;
}

FunctionXSHIRef EasyDrv::GetGlobalFunctionByIndex( _dword index ) const
{
	return _null;
}

const NativeFunctionInfoXSHI& EasyDrv::GetFunctionInfo( FunctionXSHI* function ) const
{
	DYNAMIC_CAST_EASYRESOURCE( Function, function );

	return easy_function->GetFunctionInfo( );
}

//----------------------------------------------------------------------------
// EasyFunction Implementation
//----------------------------------------------------------------------------

EasyFunction::EasyFunction( )
{

}

EasyFunction::~EasyFunction( )
{

}