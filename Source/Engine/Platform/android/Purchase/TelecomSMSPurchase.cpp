//! @file     TelecomSMSPurchase.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// TelecomSMSPurchase Implementation
//----------------------------------------------------------------------------

TelecomSMSPurchase::TelecomSMSPurchase( )
{
}

TelecomSMSPurchase::~TelecomSMSPurchase( )
{
}

_ubool TelecomSMSPurchase::OnImportItemNode( ISerializableNode* item_node, IPurchase::ItemInfo& item_info )
{
	_ubool ret = _true;
	ret &= item_node->Read( L"ctindex_carrier", item_info.mPayCode );

	return ret;
}