//! @file     EasyClass.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

//----------------------------------------------------------------------------
// EasyDrv-Class Implementation
//----------------------------------------------------------------------------

ClassXSHIPassRef EasyDrv::RegisterClass( const ClassDefXSHI& def )
{
	return _null;
}

_ubool EasyDrv::RegisterClassProperty( ClassXSHI* script_class, const ClassPropertyDefXSHI& def )
{
	return _false;
}

_ubool EasyDrv::RegisterClassBehaviour( ClassXSHI* script_class, _XSCRIPT_BEHAVIOUR behaviour, const FuncPtrXSHI& func )
{
	return _true;
}

_dword EasyDrv::GetClassNumber( ) const
{
	return 0;
}

ClassXSHIRef EasyDrv::GetClassByName( AStringPtr name )
{
	return _null;
}

ClassXSHIRef EasyDrv::GetClassByName( WStringPtr name )
{
	return _null;
}