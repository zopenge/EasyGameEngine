//! @file     TInputDevice.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TInputDevice
//----------------------------------------------------------------------------

template< typename Type >
class TInputDevice : public TNameObject< Type >
{
protected:
	//!	The input device type
	_DEVICE	mType;

protected:
	TInputDevice( _DEVICE type );
	virtual ~TInputDevice( );

// IInputDevice Interface
public:
	virtual _DEVICE	GetType( ) const override;
};

//----------------------------------------------------------------------------
// TInputDevice Implementation
//----------------------------------------------------------------------------

template< typename Type >
TInputDevice< Type >::TInputDevice( _DEVICE type ) : mType( type )
{

}

template< typename Type >
TInputDevice< Type >::~TInputDevice( )
{
}

template< typename Type >
_DEVICE TInputDevice< Type >::GetType( ) const
{
	return mType;
}

}
