//! @file     IIOSPlatform.h
//! @author   LiCode
//! @version  1.0.0.547
//! @date     2011/01/07
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IIOSPlatform
//----------------------------------------------------------------------------

class IIOSPlatform : public IPlatform
{
public:
    virtual IIAPManagerPassRef      CreateIAPManager( ) PURE;
    
    virtual _void                   RegisterForPushNotification( ) PURE;
};

}
