//! @file     TelecomSMSPurchase.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TelecomSMSPurchase
//----------------------------------------------------------------------------

class TelecomSMSPurchase : public TAndroidPurchase< IPurchase >
{
// TPurchase Interface
private:
	virtual _ubool OnImportItemNode( ISerializableNode* item_node, IPurchase::ItemInfo& item_info ) override;

public:
	TelecomSMSPurchase( );
	virtual ~TelecomSMSPurchase( );

// IPurchase Interface
public:
};

}