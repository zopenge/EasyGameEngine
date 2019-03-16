//! @file     D3D11Drv.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// D3D11Methods
//----------------------------------------------------------------------------

EGE_BEGIN_NAMESPACE_2( EGE, D3D11 )

#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) _##FuncName FuncName = _null;
#include "Module/Graphic/RHI/D3D11/Inc/D3D11Methods.h"
#undef DEFINE_FUNC_PTR

EGE_END_NAMESPACE_2( )

//----------------------------------------------------------------------------
// D3D11Drv Implementation
//----------------------------------------------------------------------------

D3D11Drv::D3D11Drv( )
{
	mSupportFeatureLevel	= D3D_FEATURE_LEVEL_9_1;
}

D3D11Drv::~D3D11Drv( )
{
	// Clear state and flush commands
	if ( mDeviceContext.IsValid( ) )
	{
		mDeviceContext->ClearState( );
		mDeviceContext->Flush( );
	}

	// Clear the device
	mDeviceContext.Clear( );
	mDevice.Clear( );

	// Clear the DXGI factory interface
	mDXGIFactory.Clear( );
}

_ubool D3D11Drv::Initialize( )
{
	// Load D3D libraries
	_handle dxgi_dll		= Platform::LoadLibrary( "dxgi.dll" );
	_handle d3d11_dll		= Platform::LoadLibrary( "d3d11.dll" );
	_handle d3dcompiler_dll	= Platform::LoadLibrary( D3DCOMPILER_DLL );
	_handle d3dx11_dll		= Platform::LoadLibrary( D3DX11_DLL );
	if ( dxgi_dll == _null || d3d11_dll == _null || d3dcompiler_dll == _null || d3dx11_dll == _null )
		return _false;

	// Get DXGI functions
	GET_FUNC_PTR( D3D11, dxgi_dll, CreateDXGIFactory1 )
	// Get D3D functions
	GET_FUNC_PTR( D3D11, d3d11_dll, D3D11CreateDevice )
	GET_FUNC_PTR( D3D11, d3d11_dll, D3D11CreateDeviceAndSwapChain )
	// Get D3D compiler functions
	GET_FUNC_PTR( D3D11, d3dcompiler_dll, D3DCompile )
	GET_FUNC_PTR( D3D11, d3dcompiler_dll, D3DPreprocess )
	GET_FUNC_PTR( D3D11, d3dcompiler_dll, D3DGetDebugInfo )
	GET_FUNC_PTR( D3D11, d3dcompiler_dll, D3DReflect )
	GET_FUNC_PTR( D3D11, d3dcompiler_dll, D3DDisassemble )
	// Get D3DX functions
	GET_FUNC_PTR( D3D11, d3dx11_dll, D3DX11CreateTextureFromMemory )
	GET_FUNC_PTR( D3D11, d3dx11_dll, D3DX11GetImageInfoFromMemory )
	GET_FUNC_PTR( D3D11, d3dx11_dll, D3DX11SaveTextureToMemory )
	GET_FUNC_PTR( D3D11, d3dx11_dll, D3DX11SaveTextureToFileW )
	GET_FUNC_PTR( D3D11, d3dx11_dll, D3DX11LoadTextureFromTexture )

	// Initialize the D3D driver type and flags
	D3D_DRIVER_TYPE d3d_driver_type = D3D_DRIVER_TYPE_HARDWARE;
	_dword			d3d_flags		= D3D11_CREATE_DEVICE_SINGLETHREADED;
#ifdef _DEBUG
	d3d_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// Create the DXGI factory
	if ( FAILED( D3D11::CreateDXGIFactory1( __uuidof( IDXGIFactory ), (_void**) &mDXGIFactory.GetRawRef( ) ) ) )
		return _false;

	// Allow selection of NVPerfHUD Adapter (if available)
	RefPtr< IDXGIAdapter > adapter; RefPtr< IDXGIAdapter > dxgi_enum_adapter; _dword adapter_index = 0;
	while ( mDXGIFactory->EnumAdapters( adapter_index, &dxgi_enum_adapter.GetRawRef( ) ) != DXGI_ERROR_NOT_FOUND )
	{
		if ( dxgi_enum_adapter->CheckInterfaceSupport( __uuidof( ID3D11Device ), _null ) == S_OK )
		{
			DXGI_ADAPTER_DESC dxgi_adapter_desc;
			if ( SUCCEEDED( dxgi_enum_adapter->GetDesc( &dxgi_adapter_desc ) ) )
			{
				_ubool is_perfhud = Platform::CompareString( dxgi_adapter_desc.Description, L"NVIDIA PerfHUD", _true ) == 0;

				// Select the first adapter in normal circumstances or the PerfHUD one if it exists.
				if ( adapter_index == 0 || is_perfhud )
					adapter = dxgi_enum_adapter;

				if ( is_perfhud )
					d3d_driver_type = D3D_DRIVER_TYPE_REFERENCE;
			}
		}

		adapter_index ++;
	}

	// The D3D features level
	D3D_FEATURE_LEVEL features[] = 
	{
		D3D_FEATURE_LEVEL_9_1, D3D_FEATURE_LEVEL_9_2, D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_10_0, D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_11_0
	};

	// Creating the D3D device and context
	if ( FAILED( D3D11::D3D11CreateDevice( adapter.GetPtr( ), d3d_driver_type, _null, d3d_flags, features, EGE_ARRAY_NUMBER( features ), D3D11_SDK_VERSION, &mDevice.GetRawRef( ), &mSupportFeatureLevel, &mDeviceContext.GetRawRef( ) ) ) )
		return _false;

	return _true;
}

_void D3D11Drv::Finalize( )
{
}

_ubool D3D11Drv::ResetResources( IApplication* application )
{
	return _true;
}

_void D3D11Drv::UnloadResources( )
{
}

IResourceManagerRHI* D3D11Drv::GetResourceManager( )
{
	return _null;
}

RenderStatsRHI& D3D11Drv::GetRenderStats( )
{
	static RenderStatsRHI sRenderStatsRHI; 
	return sRenderStatsRHI;
}

const RenderStatsRHI& D3D11Drv::GetRenderStats( ) const
{
	static RenderStatsRHI sRenderStatsRHI; 
	return sRenderStatsRHI;
}

_void D3D11Drv::ClearRenderStats( )
{

}

IAllocator* D3D11Drv::GetAllocator( )
{
	return _null;
}

_void D3D11Drv::ClearCaches( )
{

}

_dword D3D11Drv::GetRenderContextsNumber( )
{
	return 1;
}

_ubool D3D11Drv::HandleEvent( EventBase& event )
{
	return _false;
}

_ubool D3D11Drv::IsBlockEvent( _dword event_id, _ubool& is_async )
{
	return _false;
}

_ubool D3D11Drv::IsSupportVAO( )
{
	return _false;
}

_ubool D3D11Drv::IsSupportInstancedRendering( )
{
	return _false;
}

PointU D3D11Drv::GetOVRFovTextureSize( _dword index )
{
	return PointU::cZeroPoint;
}

_void D3D11Drv::SetOVRRenderTargetTexID( _dword index, _dword tex_id, const PointU& tex_size )
{
}

_void D3D11Drv::SynOVRDeviceRegion( )
{
}

const OVREyeRHI& D3D11Drv::GetOVREyeInfo( _dword index )
{
	static OVREyeRHI sGraphicOVREyeInfo; 
	return sGraphicOVREyeInfo;
}

VertexDeclarationRHIPassRef D3D11Drv::CreateVertexDeclaration( const VertexElementRHIArray& elements )
{
	return _null;
}

_dword D3D11Drv::GetVertexDeclarationVertexType( VertexDeclarationRHI* declaration )
{
	return 0;
}

_dword D3D11Drv::GetVertexDeclarationStride( VertexDeclarationRHI* declaration )
{
	return 0;
}

const VertexElementRHIArray& D3D11Drv::GetVertexDeclarationDefine( VertexDeclarationRHI* declaration )
{
	static VertexElementRHIArray sNull;
	return sNull;
}

IndexBufferRHIPassRef D3D11Drv::CreateIndexBuffer( _dword stride, _dword size, const _byte* buffer, _dword usage_flags, _RESOURCE_DRAW_TYPE draw_type )
{
	return _null;
}

_void* D3D11Drv::LockIndexBuffer( IndexBufferRHI* indexbuffer, _dword offset, _dword size, _RESOURCE_LOCK_FLAG flag )
{
	return _null;
}

_void D3D11Drv::UnlockIndexBuffer( IndexBufferRHI* indexbufferRHI )
{
}

_dword D3D11Drv::GetIndexBufferStride( IndexBufferRHI* indexbuffer )
{
	return 0;
}

_dword D3D11Drv::GetIndexBufferSize( IndexBufferRHI* indexbuffer )
{
	return 0;
}

_ubool D3D11Drv::UpdateIndexBuffer( IndexBufferRHI* index_buffer, _dword offset, _dword size, const _byte* buffer, _ubool discard )
{
	return _false;
}

_ubool D3D11Drv::ResizeIndexBuffer( IndexBufferRHI* index_buffer, _dword size )
{
	return _false;
}

_dword D3D11Drv::GetIndexBufferResID( IndexBufferRHI* index_buffer )
{
	return 0;
}

VertexBufferRHIPassRef D3D11Drv::CreateVertexBuffer( _dword stride, _dword size, const _byte* buffer, _dword usage_flags, _RESOURCE_DRAW_TYPE draw_type )
{
	return _null;
}

_void* D3D11Drv::LockVertexBuffer( VertexBufferRHI* vertexbuffer, _dword offset, _dword size, _RESOURCE_LOCK_FLAG flag )
{
	return _null;
}

_void D3D11Drv::UnlockVertexBuffer( VertexBufferRHI* vertexbuffer )
{
}

_dword D3D11Drv::GetVertexBufferStride( VertexBufferRHI* vertexbuffer )
{
	return 0;
}

_dword D3D11Drv::GetVertexBufferSize( VertexBufferRHI* vertexbuffer )
{
	return 0;
}

_ubool D3D11Drv::UpdateVertexBuffer( VertexBufferRHI* vertexbuffer, _dword offset, _dword size, const _byte* buffer, _ubool discard )
{
	return _true;
}

_ubool D3D11Drv::ResizeVertexBuffer( VertexBufferRHI* vertexbuffer, _dword size )
{
	return _false;
}

_dword D3D11Drv::GetVertexBufferResID( VertexBufferRHI* vertexbuffer )
{
	return 0;
}