//! @file     EGE_Network.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

namespace EGE
{

// Network Interface
REF_OBJECT_DECL(INetworkOperation);
REF_OBJECT_DECL(INetworkStreamReaderNotifier);
REF_OBJECT_DECL(INetworkStreamReader);
REF_OBJECT_DECL(INetworkConnectionThread);
REF_OBJECT_DECL(INetworkConnectionNotifier);
REF_OBJECT_DECL(INetworkConnection);
REF_OBJECT_DECL(INetworkBluetoothConnection);
REF_OBJECT_DECL(INetworkTCPConnection);
REF_OBJECT_DECL(INetworkUDPConnection);
REF_OBJECT_DECL(INetworkHTTPConnection);
REF_OBJECT_DECL(INetworkFTPConnectionNotifier);
REF_OBJECT_DECL(INetworkFTPConnection);
REF_OBJECT_DECL(INetworkNamedPipeConnection);
REF_OBJECT_DECL(INetworkProtoBufConnectionNotifier);
REF_OBJECT_DECL(INetworkProtoBufTCPConnection);
REF_OBJECT_DECL(INetworkProtoBufHTTPConnection);
REF_OBJECT_DECL(INetworkProtoBufNamedPipeConnection);
REF_OBJECT_DECL(INetworkStationNotifier);
REF_OBJECT_DECL(INetworkStation);
REF_OBJECT_DECL(INetworkResourceManager);
REF_OBJECT_DECL(INetworkModule);

}

// Network global files
#include "Interface/Module/Network/NetworkGlobals.h"

// Network Template files
#include "Interface/Module/Network/Template/TNetworkOperation.h"

// Module-Network Interface Files
#include "Interface/Module/Network/INetworkOperation.h"
#include "Interface/Module/Network/INetworkStreamReader.h"
#include "Interface/Module/Network/INetworkConnection.h"
#include "Interface/Module/Network/INetworkBluetoothConnection.h"
#include "Interface/Module/Network/INetworkTCPConnection.h"
#include "Interface/Module/Network/INetworkUDPConnection.h"
#include "Interface/Module/Network/INetworkHTTPConnection.h"
#include "Interface/Module/Network/INetworkFTPConnection.h"
#include "Interface/Module/Network/INetworkNamedPipeConnection.h"
#include "Interface/Module/Network/INetworkProtoBufConnection.h"
#include "Interface/Module/Network/INetworkStation.h"
#include "Interface/Module/Network/INetworkConnectionThread.h"
#include "Interface/Module/Network/INetworkResourceManager.h"
#include "Interface/Module/Network/INetworkModule.h"
#include "Interface/Module/Entries/EGE_NetworkEntry.h"