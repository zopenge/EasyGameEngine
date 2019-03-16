//! @file     TWithLastErrorObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TWithLastErrorObject
//----------------------------------------------------------------------------

template< typename Type >
class TWithLastErrorObject : public Type
{
protected:
	//!	The last error ID
	_dword	mLastErrorID;

protected:
	TWithLastErrorObject( );
	virtual ~TWithLastErrorObject( );

// IWithLastErrorObject Interface
public:
	virtual _void	SetLastErrorID( _dword errorid ) override;
	virtual _dword	GetLastErrorID( ) override;
};

//----------------------------------------------------------------------------
// TWithLastErrorObject Implementation
//----------------------------------------------------------------------------

template< typename Type >
TWithLastErrorObject< Type >::TWithLastErrorObject( )
{
	mLastErrorID = 0;
}

template< typename Type >
TWithLastErrorObject< Type >::~TWithLastErrorObject( )
{
}

template< typename Type >
_void TWithLastErrorObject< Type >::SetLastErrorID( _dword errorid )
{
	mLastErrorID = errorid;
}

template< typename Type >
_dword TWithLastErrorObject< Type >::GetLastErrorID( )
{
	_dword last_error_id = mLastErrorID;
	mLastErrorID = 0;

	return last_error_id;
}

}