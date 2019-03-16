//! @file     TBluetoothDevice.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TBluetoothDevice
//----------------------------------------------------------------------------

template< typename Type >
class TBluetoothDevice : public TObject< Type >
{
protected:
	AString	mName;
	AString	mAddress;

protected:
	TBluetoothDevice( );
	virtual ~TBluetoothDevice( );

// IBluetoothDevice Interface
public:
	virtual AStringPtr	GetAddress( ) const override;
	virtual AStringPtr	GetName( ) const override;
};

//----------------------------------------------------------------------------
// TBluetoothDevice Implementation
//----------------------------------------------------------------------------

template< typename Type >
TBluetoothDevice< Type >::TBluetoothDevice( )
{

}

template< typename Type >
TBluetoothDevice< Type >::~TBluetoothDevice( )
{

}

template< typename Type >
AStringPtr TBluetoothDevice< Type >::GetAddress( ) const 
{
	return mAddress;
}

template< typename Type >
AStringPtr TBluetoothDevice< Type >::GetName( ) const 
{
	return mName;
}

}