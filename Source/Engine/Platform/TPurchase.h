//! @file     TPurchase.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TPurchase
//----------------------------------------------------------------------------

template< typename Type >
class TPurchase : public TSerializable< TObject< Type > >
{
protected:
	//!	Use the unique ID as key.
	typedef Map< IPurchase::ItemInfo, WString > ItemInfoMap;

protected:
	IPurchaseNotifierRef	mNotifier;

	ItemInfoMap				mItems;

	IPurchase::AppInfo		mAppInfo;

protected:
	//!	When import item node.
	virtual _ubool OnImportItemNode( ISerializableNode* item_node, IPurchase::ItemInfo& item_info ) { return _true; }

protected:
	TPurchase( );
	virtual ~TPurchase( );

// ISerializable Interface
public:
	virtual _ubool						Import( ISerializableNode* node ) override;
	virtual _ubool						Export( ISerializableNode* node ) const override;

// IPurchase Interface
public:
	virtual _void						SetNotifier( IPurchaseNotifier* notifier ) override;
	virtual IPurchaseNotifier*			GetNotifier( ) override;

	virtual _void						SetAppInfo( const IPurchase::AppInfo& app_info ) override;
	virtual const IPurchase::AppInfo&	GetAppInfo( ) const override;

	virtual _void						AddItem( const IPurchase::ItemInfo& item_info ) override;
	virtual const IPurchase::ItemInfo*	GetItem( WStringPtr id ) const override;
};

//----------------------------------------------------------------------------
// TPurchase Implementation
//----------------------------------------------------------------------------

template< typename Type >
TPurchase< Type >::TPurchase( )
{
	mNotifier = &NullEngine::GetInstance( ).GetPurchaseNotifier( );
}

template< typename Type >
TPurchase< Type >::~TPurchase( )
{

}

template< typename Type >
_ubool TPurchase< Type >::Import( ISerializableNode* node )
{
	if ( node == _null )
		return _false;

	ISerializableNodeRef item_node = node->GetFirstChildNode( );
	if ( item_node.IsValid( ) )
	{
		do
		{
			IPurchase::ItemInfo item_info;

			_ubool ret = _true;
			ret &= item_node->Read( L"id", item_info.mID );
			ret &= item_node->Read( L"name", item_info.mName );
			ret &= item_node->Read( L"desc", item_info.mDesc );
			ret &= item_node->Read( L"rmb", item_info.mPrice );
			if ( ret == _false )
			{
				WLOG_ERROR_2( L"Import 'id: %s, name: %s' item of purchase failed", item_info.mID.Str( ), item_info.mName.Str( ) );
				return _false;
			}

			if ( OnImportItemNode( item_node, item_info ) == _false )
				return _false;

			AddItem( item_info );
		}
		while ( item_node->MoveNext( ) );
	}

	return _true;
}

template< typename Type >
_ubool TPurchase< Type >::Export( ISerializableNode* node ) const
{
	return _true;
}

template< typename Type >
_void TPurchase< Type >::SetNotifier( IPurchaseNotifier* notifier )
{
	if ( notifier == _null )
		mNotifier = &NullEngine::GetInstance( ).GetPurchaseNotifier( );
	else
		mNotifier = notifier;
}

template< typename Type >
IPurchaseNotifier* TPurchase< Type >::GetNotifier( )
{
	return mNotifier;
}

template< typename Type >
_void TPurchase< Type >::SetAppInfo( const IPurchase::AppInfo& app_info )
{
	mAppInfo = app_info;
}

template< typename Type >
const IPurchase::AppInfo& TPurchase< Type >::GetAppInfo( ) const
{
	return mAppInfo;
}

template< typename Type >
_void TPurchase< Type >::AddItem( const IPurchase::ItemInfo& item_info )
{
	mItems[ item_info.mID ] = item_info;
}

template< typename Type >
const IPurchase::ItemInfo* TPurchase< Type >::GetItem( WStringPtr id ) const
{
	return mItems.Search( id );
}

}