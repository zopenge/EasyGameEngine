//! @file     Purchase.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// JNI Functions Implementation
//----------------------------------------------------------------------------

JNI_FUNC_4( void, AndroidBasePurchase, OnPurchaseResult, jint op_status, jstring op_desc, jstring item_id, jint purchase )
{
	IPurchase* self_purchase = (IPurchase*) purchase;
	EGE_ASSERT( self_purchase != _null );

	WLOG_TRACE( L"AndroidBasePurchase 1" );

	// Get the item ID string
	WString item_id_string = J2CString( item_id ).ToWString( );
	WLOG_TRACE( L"AndroidBasePurchase 2" );
	// Get the operation description string
	WString op_desc_string = J2CString( op_desc ).ToWString( );
	WLOG_TRACE( L"AndroidBasePurchase 3" );

	// Feedback the purchase result
	switch ( op_status )
	{
		// RESULT_SUCCEEDED
		case 0:
		{
			WLOG_TRACE_2( L"Buy (id: %s) item succeed (%s)", item_id_string.Str( ), op_desc_string.Str( ) );
			self_purchase->GetNotifier( )->OnSucceed( item_id_string );
		}
		break;

		// RESULT_FAILED/RESULT_INVALID_PARAM/RESULT_INVALID_SIMCARD/RESULT_NO_SIMCARD
		case 1:
		case 3:
		case 4:
		case 5:
		{
			WLOG_ERROR_3( L"Buy (id: %s) item failed(%d)(%s)", item_id_string.Str( ), op_status, op_desc_string.Str( ) );
			self_purchase->GetNotifier( )->OnFailed( item_id_string );
		}
		break;

		// RESULT_CANCELED
		case 2:
		{
			WLOG_TRACE_2( L"Buy (id: %s) item cancel (%s)", item_id_string.Str( ), op_desc_string.Str( ) );
			self_purchase->GetNotifier( )->OnCanceled( item_id_string );
		}
		break;

		default:
			break;
	}
}