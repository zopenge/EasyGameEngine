//! @file     TBluetoothAdapter.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TBluetoothAdapter
//----------------------------------------------------------------------------

template< typename Type >
class TBluetoothAdapter : public TObject< Type >
{
protected:
	AString							mName;
	AString							mAddress;

	IBluetoothAdapterNotifierRef	mNotifier;

protected:
	TBluetoothAdapter( );
	virtual ~TBluetoothAdapter( );

// IBluetoothAdapter Interface
public:
	virtual _void							SetNotifier( IBluetoothAdapterNotifier* notifier ) override;
	virtual IBluetoothAdapterNotifierRef	GetNotifier( ) override;

	virtual AStringPtr						GetAddress( ) const override;
	virtual AStringPtr						GetName( ) const override;
};

//----------------------------------------------------------------------------
// TBluetoothAdapter Implementation
//----------------------------------------------------------------------------

template< typename Type >
TBluetoothAdapter< Type >::TBluetoothAdapter( )
{
	mNotifier = &NullEngine::GetInstance( ).GetBluetoothAdapterNotifier( );
}

template< typename Type >
TBluetoothAdapter< Type >::~TBluetoothAdapter( )
{

}

template< typename Type >
_void TBluetoothAdapter< Type >::SetNotifier( IBluetoothAdapterNotifier* notifier )
{
	if ( notifier == _null )
		mNotifier = &NullEngine::GetInstance( ).GetBluetoothAdapterNotifier( );
	else
		mNotifier = notifier;
}

template< typename Type >
IBluetoothAdapterNotifierRef TBluetoothAdapter< Type >::GetNotifier( )
{
	return mNotifier;
}

template< typename Type >
AStringPtr TBluetoothAdapter< Type >::GetAddress( ) const 
{
	return mAddress;
}

template< typename Type >
AStringPtr TBluetoothAdapter< Type >::GetName( ) const 
{
	return mName;
}

}