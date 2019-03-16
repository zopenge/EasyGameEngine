//! @file     MobileSMSPurchase.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// MobileSMSPurchase
//----------------------------------------------------------------------------

class MobileSMSPurchase : public TAndroidPurchase< IPurchase >
{
private:
	//!	The item flags
	enum _ITEM_FLAG
	{
		_ITEM_FLAG_IS_REPEATED = 1 << 0,
	};

// TPurchase Interface
private:
	virtual _ubool OnImportItemNode( ISerializableNode* item_node, IPurchase::ItemInfo& item_info ) override;

public:
	MobileSMSPurchase( );
	virtual ~MobileSMSPurchase( );

// IPurchase Interface
public:
};

}