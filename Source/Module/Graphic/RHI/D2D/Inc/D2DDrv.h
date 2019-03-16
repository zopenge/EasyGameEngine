//! @file     D2DDrv.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// D2DDrv
//----------------------------------------------------------------------------

class D2DDrv : public INTERFACE_OBJECT_IMPL( IDynamicRHI )
{
private:
	//!	The D2D-Factory
	RefPtr< ID2D1Factory >	mD2DFactory;

	//!	The clear color
	D2D1_COLOR_F			mD2DClearColor;

public:
	D2DDrv( );
	virtual ~D2DDrv( );

public:
	//!	Get the D2D-Factory
	EGE_GET_ACCESSOR( ID2D1Factory*, D2DFactory )
	//!	Get the clear color
	EGE_GET_ACCESSOR_CONST( const D2D1_COLOR_F&, D2DClearColor )
	
public:
	//!	D2D Translation.
	static D2D1_COLOR_F TranslateD2DColorF( const Color& color );
	static D2D1_RECT_F	TranslateD2DRectF( const RectI& rect );
	static D2D1_RECT_F	TranslateD2DRectF( const RectF& rect );

public:
	// The RHI methods are defined as virtual functions.
	#define DEFINE_RHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Interface/Module/Graphic/RHIMethods.h"
	#undef DEFINE_RHIMETHOD
};

}

//----------------------------------------------------------------------------
// D2DMethods
//----------------------------------------------------------------------------

EGE_BEGIN_NAMESPACE_2( EGE, D2D )

#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) typedef Ret (WINAPI *_##FuncName) Args;
#include "Module/Graphic/RHI/D2D/Inc/D2DMethods.h"
#undef DEFINE_FUNC_PTR

#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) extern _##FuncName FuncName;
#include "Module/Graphic/RHI/D2D/Inc/D2DMethods.h"
#undef DEFINE_FUNC_PTR

EGE_END_NAMESPACE_2( )