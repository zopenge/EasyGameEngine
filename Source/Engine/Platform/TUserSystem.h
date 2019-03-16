//! @file     TUserSystem.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TUserSystem
//----------------------------------------------------------------------------

template< typename Type >
class TUserSystem : public TObject< Type >
{
protected:
	IUserSystemNotifierRef	mNotifier;

	WString					mAppID;
	WString					mChannel;

protected:
	TUserSystem( );
	virtual ~TUserSystem( );

// IUserSystem Interface
public:
	virtual _void					SetNotifier( IUserSystemNotifier* notifier ) override;
	virtual IUserSystemNotifierRef	GetNotifier( ) override;

	virtual _ubool					Initialize( WStringPtr app_id, WStringPtr channel ) override;
};

//----------------------------------------------------------------------------
// TUserSystem Implementation
//----------------------------------------------------------------------------

template< typename Type >
TUserSystem< Type >::TUserSystem( )
{
	mNotifier = &NullEngine::GetInstance( ).GetUserSystemNotifier( );
}

template< typename Type >
TUserSystem< Type >::~TUserSystem( )
{

}

template< typename Type >
_void TUserSystem< Type >::SetNotifier( IUserSystemNotifier* notifier )
{
	if ( notifier == _null )
		mNotifier = &NullEngine::GetInstance( ).GetUserSystemNotifier( );
	else
		mNotifier = notifier;
}

template< typename Type >
IUserSystemNotifierRef TUserSystem< Type >::GetNotifier( )
{
	return mNotifier;
}

template< typename Type >
_ubool TUserSystem< Type >::Initialize( WStringPtr app_id, WStringPtr channel )
{
	mAppID		= app_id;
	mChannel	= channel;

	return _true;
}

}