//! @file     XYPosUIProxy.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// XYPosUIProxy
//----------------------------------------------------------------------------

class XYPosUIProxy : public INTERFACE_XYPOS_UIPROXY_IMPL( IXYPosUIProxy, _long )
{
private:

public:
	XYPosUIProxy( );
	virtual ~XYPosUIProxy( );
};

}