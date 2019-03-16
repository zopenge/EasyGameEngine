//! @file     TAndroidPurchase.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TAndroidPurchase
//----------------------------------------------------------------------------

template< typename Type >
class TAndroidPurchase : public TPurchase< Type >
{
protected:
	IInvokerRef mPurchaseObject;

protected:
	//!	When initialize.
	virtual _ubool OnInit( const C2JString& j_app_id, const C2JString& j_cp_code, const C2JString& j_cp_id, const C2JString& j_tel_number );
	//!	When pay.
	virtual _ubool OnPay( const IPurchase::ItemInfo* item_info, const C2JString& j_id, const C2JString& j_pay_code, const C2JString& j_desc, const C2JString& j_money );

protected:
	TAndroidPurchase( );
	virtual ~TAndroidPurchase( );

public:
	//!	Initialize.
	_ubool Initialize( );

// IPurchase Interface
public:
	virtual _ubool Pay( WStringPtr id ) override;
};

//----------------------------------------------------------------------------
// TAndroidPurchase Implementation
//----------------------------------------------------------------------------

template< typename Type >
TAndroidPurchase< Type >::TAndroidPurchase( )
{

}

template< typename Type >
TAndroidPurchase< Type >::~TAndroidPurchase( )
{

}

template< typename Type >
_ubool TAndroidPurchase< Type >::OnInit( const C2JString& j_app_id, const C2JString& j_cp_code, const C2JString& j_cp_id, const C2JString& j_tel_number )
{
	mPurchaseObject->CallVoidMethod( "init", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", 
		j_app_id.ToJString( ), j_cp_code.ToJString( ), j_cp_id.ToJString( ), j_tel_number.ToJString( ) );

	return _true;
}

template< typename Type >
_ubool TAndroidPurchase< Type >::OnPay( const IPurchase::ItemInfo* item_info, const C2JString& j_id, const C2JString& j_pay_code, const C2JString& j_desc, const C2JString& j_money )
{
	EGE_ASSERT( item_info != _null );

	mPurchaseObject->CallVoidMethod( "purchase", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V",
		j_id.ToJString( ), j_pay_code.ToJString( ), j_desc.ToJString( ), j_money.ToJString( ) );

	return _true;
}

template< typename Type >
_ubool TAndroidPurchase< Type >::Initialize( )
{
	// Bind JS purchase object
	mPurchaseObject = androidJNI::GetInstance( ).CreateJNIObject( "com/ege/android/AndroidPurchase" );
	if ( mPurchaseObject.IsNull( ) )
		return _false;

	mPurchaseObject->CallVoidMethod( "bind", "(I)V", jint( this ) );

	// Initialize JS purchase object
	C2JString j_app_id( this->mAppInfo.mID );
	C2JString j_cp_code( this->mAppInfo.mCPCode );
	C2JString j_cp_id( this->mAppInfo.mCPID );
	C2JString j_tel_number( this->mAppInfo.mTelNumber );

	return OnInit( j_app_id, j_cp_code, j_cp_id, j_tel_number );
}

template< typename Type >
_ubool TAndroidPurchase< Type >::Pay( WStringPtr id )
{
	const IPurchase::ItemInfo* item_info = this->GetItem( id );
	if ( item_info == _null )
		return _false;

	C2JString j_id( id );
	C2JString j_pay_code( item_info->mPayCode );
	C2JString j_desc( item_info->mDesc );
	C2JString j_money( WString( ).FromValue( item_info->mPrice, 10 ) );

	return OnPay( item_info, j_id, j_pay_code, j_desc, j_money );
}

}