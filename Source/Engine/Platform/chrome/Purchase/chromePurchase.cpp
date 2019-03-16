//! @file     MobileSMSPurchase.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// MobileSMSPurchase Implementation
//----------------------------------------------------------------------------

MobileSMSPurchase::MobileSMSPurchase( )
{
}

MobileSMSPurchase::~MobileSMSPurchase( )
{
}

_ubool MobileSMSPurchase::OnImportItemNode( ISerializableNode* item_node, IPurchase::ItemInfo& item_info )
{
	_ubool ret = _true;
	ret &= item_node->Read( L"cmgindex", item_info.mPayCode );

	_ubool is_repeated = _false;
	if ( item_node->Read( L"cmgisrepeated", is_repeated ) )
		item_info.EnableFlags( _ITEM_FLAG_IS_REPEATED, is_repeated );

	return ret;
}