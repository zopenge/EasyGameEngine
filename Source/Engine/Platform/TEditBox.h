//! @file     TEditBox.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TEditBox
//----------------------------------------------------------------------------

template< typename Type >
class TEditBox : public TObject< Type >
{
protected:
	typedef CallbackFunc< IEditBox::OnCheckCharacter, _ubool, QwordParameters2 > OnCheckCharacterFunc;
	typedef CallbackFunc< IEditBox::OnHandleEvent, _void, QwordParameters2 > OnHandleEventFunc;

public:
	OnCheckCharacterFunc	mCheckCharacterFunc;
	OnHandleEventFunc		mHandleEventFunc;

protected:
	TEditBox( );
	virtual ~TEditBox( );

// IEditBox Interface
public:
	virtual _void	SetCheckCharacterFunc( IEditBox::OnCheckCharacter funcpointer, const QwordParameters2& params ) override;
	virtual _void	SetHandleEventFunc( IEditBox::OnHandleEvent funcpointer, const QwordParameters2& params ) override;
};

//----------------------------------------------------------------------------
// TEditBox Implementation
//----------------------------------------------------------------------------

template< typename Type >
TEditBox< Type >::TEditBox( )
{
}

template< typename Type >
TEditBox< Type >::~TEditBox( )
{

}

template< typename Type >
_void TEditBox< Type >::SetCheckCharacterFunc( IEditBox::OnCheckCharacter funcpointer, const QwordParameters2& params )
{
	mCheckCharacterFunc.Init( funcpointer, params );
}

template< typename Type >
_void TEditBox< Type >::SetHandleEventFunc( IEditBox::OnHandleEvent funcpointer, const QwordParameters2& params )
{
	mHandleEventFunc.Init( funcpointer, params );
}

}