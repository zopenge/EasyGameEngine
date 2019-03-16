//! @file     XYPosFUIProxy.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// XYPosFUIProxy
//----------------------------------------------------------------------------

class XYPosFUIProxy : public INTERFACE_XYPOS_UIPROXY_IMPL( IXYPosFUIProxy, _float )
{
private:

public:
	XYPosFUIProxy( );
	virtual ~XYPosFUIProxy( );
};

}