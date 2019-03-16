//! @file     CircleUIProxy.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// CircleUIProxy
//----------------------------------------------------------------------------

class CircleUIProxy : public INTERFACE_CIRCLE_UIPROXY_IMPL( ICircleUIProxy, _long )
{
private:

public:
	CircleUIProxy( );
	virtual ~CircleUIProxy( );
};

}