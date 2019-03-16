//! @file     GDIDrv.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GDIDrv
//----------------------------------------------------------------------------

class GDIDrv : public INTERFACE_OBJECT_IMPL( IDynamicRHI )
{
private:
	// The GDIPlus token handle
	ULONG_PTR	mGDIToken;

	//!	The GDI clear color
	Color		mGDIClearColor;

private:
	//!	Load the GDI+ library.
	_ubool LoadGDIPlusLibrary( );

public:
	GDIDrv( );
	virtual ~GDIDrv( );

public:
	//!	Get the clear color
	EGE_GET_ACCESSOR_CONST( const Color&, GDIClearColor )

public:
	//! Get the image encoder's CLSID.
	//!	@param		type	The image type.
	//!	@param		clsid	The unique CLSID.
	//!	@return		True indicates successful, otherwise indicates failure.
	static _ubool GetImageEncoderClsid( _FILE_FORMAT type, CLSID& clsid );

public:
	#define DEFINE_RHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Interface/Module/Graphic/RHIMethods.h"
	#undef DEFINE_RHIMETHOD
};

}

//----------------------------------------------------------------------------
// GDIMethods
//----------------------------------------------------------------------------

EGE_BEGIN_NAMESPACE_2( EGE, GDI )

#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) typedef Ret (WINGDIPAPI *_##FuncName) Args;
#include "Module/Graphic/RHI/GDI/Inc/GDIMethods.h"
#undef DEFINE_FUNC_PTR

#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) extern _##FuncName FuncName;
#include "Module/Graphic/RHI/GDI/Inc/GDIMethods.h"
#undef DEFINE_FUNC_PTR

EGE_END_NAMESPACE_2( )