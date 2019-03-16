//! @file     TMessageBox.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TMessageBox
//----------------------------------------------------------------------------

template< typename Type >
class TMessageBox : public TObject< Type >
{
protected:
	IMessageBoxNotifierRef	mNotifier;

protected:
	TMessageBox( );
	virtual ~TMessageBox( );

// IMessageBox Interface
public:
	virtual _void					SetNotifier( IMessageBoxNotifier* notifier ) override;
	virtual IMessageBoxNotifier*	GetNotifier( ) override;
};

//----------------------------------------------------------------------------
// TMessageBox Implementation
//----------------------------------------------------------------------------

template< typename Type >
TMessageBox< Type >::TMessageBox( )
{
	mNotifier = &NullEngine::GetInstance( ).GetMessageBoxNotifier( );
}

template< typename Type >
TMessageBox< Type >::~TMessageBox( )
{

}

template< typename Type >
_void TMessageBox< Type >::SetNotifier( IMessageBoxNotifier* notifier )
{
	if ( notifier == _null )	
		mNotifier = &NullEngine::GetInstance( ).GetMessageBoxNotifier( );
	else
		mNotifier = notifier;
}

template< typename Type >
IMessageBoxNotifier* TMessageBox< Type >::GetNotifier( )
{
	return mNotifier;
}

}