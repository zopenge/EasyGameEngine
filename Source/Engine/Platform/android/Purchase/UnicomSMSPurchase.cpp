//! @file     UnicomSMSPurchase.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// UnicomSMSPurchase Implementation
//----------------------------------------------------------------------------

UnicomSMSPurchase::UnicomSMSPurchase( )
{
}

UnicomSMSPurchase::~UnicomSMSPurchase( )
{
}

_ubool UnicomSMSPurchase::OnImportItemNode( ISerializableNode* item_node, IPurchase::ItemInfo& item_info )
{
	_ubool ret = _true;
	ret &= item_node->Read( L"cuindex", item_info.mPayCode );

	return ret;
}