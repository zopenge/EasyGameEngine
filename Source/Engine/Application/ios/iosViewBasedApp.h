//! @file     iosViewBasedApp.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// iosViewBasedApp
//----------------------------------------------------------------------------

class iosViewBasedApp : public INTERFACE_VIEWBASED_APP_IMPL( IViewBasedApp )
{
private:
	typedef INTERFACE_VIEWBASED_APP_IMPL( IViewBasedApp ) BaseClass;

private:
	//!	The NSApplication handle.
	_handle	mNSAppHandle;

public:
	iosViewBasedApp( _handle ns_app_handle );
	virtual ~iosViewBasedApp( );

// IObserver Interface
public:
	virtual _void						Notify( const EventBase& event, const IObject* object, const IObservable* generator ) override;

// IApplication Interface
public:
	virtual _handle						GetApplicationHandle( ) const override;
	virtual _handle						GetApplicationLayerHandle( ) const override;

	virtual _void 						Show( ) override;
	virtual _void 						Hide( ) override;

	virtual _int						Run( IAppDelegate* app_delegate, const ICommandLineParser* cmd_parser ) override;

// IViewBasedApp Interface
public:
	virtual _ubool						SetIcon( _dword id, IStreamReader* stream_reader ) override;

	virtual _void 						Center( ) override;
	virtual _void						Move( _int delta_x, _int delta_y ) override;

	virtual _void 						SetPos( _dword x, _dword y ) override;
	virtual PointI						GetPos( ) const override;
	virtual _void 						SetSize( _dword width, _dword height ) override;
	virtual PointU						GetSize( ) const override;
	virtual RectI 						GetRect( ) const override;
	virtual _void 						SetClientSize( _dword width, _dword height, _int* deltawidth = _null, _int* deltaheight = _null ) override;
    virtual RectU                       GetClientRectU( ) const override;

	virtual _dword						GetAttributes( ) const override;
	virtual _void						SetAttributes( _dword attributes ) override;

	virtual _VIEWBASED_APP_ORIENTATION	GetOrientation( ) const override;

	virtual _void 						SetCapture( ) override;
	virtual _void 						ReleaseCapture( ) override;
};

}
