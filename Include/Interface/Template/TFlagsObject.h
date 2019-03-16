//! @file     TFlagsObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TFlagsObject
//----------------------------------------------------------------------------

template< typename Type >
class TFlagsObject : public Type
{
protected:
	FlagsObject	mFlagsObject;

protected:
	TFlagsObject( );
	virtual ~TFlagsObject( );

// IFlagsObject Interface
public:
	virtual _ubool				HasFlags( _dword flags, _ubool match_all = _false ) const override;
	virtual _void				EnableFlags( _dword flags, _ubool enable ) override;
	virtual _void				CombineFlags( _dword flags ) override;
	virtual _void				ClearFlags( _dword flags ) override;

	virtual _void				SetFlags( _dword flags ) override;
	virtual _dword				GetFlags( ) const override;
	virtual const FlagsObject&	GetFlagsObject( ) const override;
};

//----------------------------------------------------------------------------
// TFlagsObject Implementation
//----------------------------------------------------------------------------

template< typename Type >
TFlagsObject< Type >::TFlagsObject( )
{
}

template< typename Type >
TFlagsObject< Type >::~TFlagsObject( )
{
}

template< typename Type >
_ubool TFlagsObject< Type >::HasFlags( _dword flags, _ubool match_all ) const
{
	return mFlagsObject.HasFlags( flags, match_all );
}

template< typename Type >
_void TFlagsObject< Type >::EnableFlags( _dword flags, _ubool enable )
{
	mFlagsObject.EnableFlags( flags, enable );
}

template< typename Type >
_void TFlagsObject< Type >::CombineFlags( _dword flags )
{
	mFlagsObject.CombineFlags( flags );
}

template< typename Type >
_void TFlagsObject< Type >::ClearFlags( _dword flags )
{
	mFlagsObject.ClearFlags( flags );
}

template< typename Type >
_void TFlagsObject< Type >::SetFlags( _dword flags )
{
	mFlagsObject.SetFlags( flags );
}

template< typename Type >
_dword TFlagsObject< Type >::GetFlags( ) const
{
	return mFlagsObject.GetFlags( );
}

template< typename Type >
const FlagsObject& TFlagsObject< Type >::GetFlagsObject( ) const
{
	return mFlagsObject;
}

}