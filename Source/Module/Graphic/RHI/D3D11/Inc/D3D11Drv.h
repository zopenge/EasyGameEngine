//! @file     D3D11Drv.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// D3D11Drv
//----------------------------------------------------------------------------

class D3D11Drv : public INTERFACE_OBJECT_IMPL( IDynamicRHI )
{
private:
	typedef Array< D3D11Viewport* > Viewports;

private:
	//!	The D3D support feature level
	D3D_FEATURE_LEVEL				mSupportFeatureLevel;

	//!	The DXGI-Factory interface
	RefPtr< IDXGIFactory >			mDXGIFactory;

	//!	The D3D-Device
	RefPtr< ID3D11Device >			mDevice;
	//!	The D3D-Device context
	RefPtr< ID3D11DeviceContext >	mDeviceContext;

	//! A list of all viewport RHIs that have been created
	Viewports						mViewports;

public:
	D3D11Drv( );
	virtual ~D3D11Drv( );

public:
	//!	Add viewport.
	//!	@param		viewport	The viewport.
	//!	@return		none.
	_void AddViewport( D3D11Viewport* viewport )
	{
		mViewports.Append( viewport );
	}

public:
	//!	Get the DXGI-Factory interface
	EGE_GET_ACCESSOR( IDXGIFactory*, DXGIFactory )
	//!	Get the D3D-Device
	EGE_GET_ACCESSOR( ID3D11Device*, Device )
	//!	Get the D3D-Device context
	EGE_GET_ACCESSOR( ID3D11DeviceContext*, DeviceContext )

public:
	// The RHI methods are defined as virtual functions.
	#define DEFINE_RHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Interface/Module/Graphic/RHIMethods.h"
	#undef DEFINE_RHIMETHOD
};

}

//----------------------------------------------------------------------------
// D3D11Methods
//----------------------------------------------------------------------------

EGE_BEGIN_NAMESPACE_2( EGE, D3D11 )

#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) typedef Ret (WINAPI *_##FuncName) Args;
#include "Module/Graphic/RHI/D3D11/Inc/D3D11Methods.h"
#undef DEFINE_FUNC_PTR

#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) extern _##FuncName FuncName;
#include "Module/Graphic/RHI/D3D11/Inc/D3D11Methods.h"
#undef DEFINE_FUNC_PTR

EGE_END_NAMESPACE_2( )