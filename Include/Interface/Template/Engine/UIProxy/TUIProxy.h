//! @file     TUIProxy.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TUIProxy
//----------------------------------------------------------------------------

template< class InterfaceType, class Type >
class TUIProxy : public InterfaceType
{
protected:
	typedef IUIProxy< Type > BaseInterface;
	typedef typename BaseInterface::_BORDER_FLAG _BORDER_FLAG;

protected:
	//!	The operation flags
	FlagsObject		mOpFlags;

	//!	The border size
	Type			mBorderSize;
	//!	The border flag
	_BORDER_FLAG	mBorderFlag;

	//!	The offset
	Point< Type >	mOffset;
	//!	The current input position
	Point< Type >	mPos;

protected:
	//!	Get the delta pos.
	Point< Type > GetDeltaPos( const Point< Type >& pos ) const;

protected:
	TUIProxy( );
	virtual ~TUIProxy( );

// IUIProxy Interface
public:
	virtual _dword					GetCurOpStatus( ) const override;

	virtual _void					SetBorderSize( Type size ) override;
	virtual Type					GetBorderSize( ) const override;
	virtual _void					SetBorderFlag( _BORDER_FLAG flag ) override;
	virtual _BORDER_FLAG			GetBorderFlag( ) const override;

	virtual _void					SetOffset( const Point< Type >& offset ) override;
	virtual const Point< Type >&	GetOffset( ) const override;

	virtual _ubool					HasBegun( ) const override;
};

//----------------------------------------------------------------------------
// TUIProxy Implementation
//----------------------------------------------------------------------------

template< class InterfaceType, class Type >
TUIProxy< InterfaceType, Type >::TUIProxy( )
{
	mBorderSize	= (Type) 1;
	mBorderFlag	= BaseInterface::_BORDER_FLAG_OUTER;

	mOffset		= Point< Type >::cZeroPoint;
	mPos		= Point< Type >::cZeroPoint;
}

template< class InterfaceType, class Type >
TUIProxy< InterfaceType, Type >::~TUIProxy( )
{
}

template< class InterfaceType, class Type >
Point< Type > TUIProxy< InterfaceType, Type >::GetDeltaPos( const Point< Type >& pos ) const
{
	return pos - mPos;
}

template< class InterfaceType, class Type >
_dword TUIProxy< InterfaceType, Type >::GetCurOpStatus( ) const
{
	return mOpFlags.GetFlags( );
}

template< class InterfaceType, class Type >
_void TUIProxy< InterfaceType, Type >::SetBorderSize( Type size )
{
	mBorderSize = size;
}

template< class InterfaceType, class Type >
Type TUIProxy< InterfaceType, Type >::GetBorderSize( ) const
{
	return mBorderSize;
}

template< class InterfaceType, class Type >
_void TUIProxy< InterfaceType, Type >::SetBorderFlag( _BORDER_FLAG flag )
{
	mBorderFlag = flag;
}

template< class InterfaceType, class Type >
typename TUIProxy< InterfaceType, Type >::_BORDER_FLAG TUIProxy< InterfaceType, Type >::GetBorderFlag( ) const
{
	return mBorderFlag;
}

template< class InterfaceType, class Type >
_void TUIProxy< InterfaceType, Type >::SetOffset( const Point< Type >& offset )
{
	mOffset = offset;
}

template< class InterfaceType, class Type >
const Point< Type >& TUIProxy< InterfaceType, Type >::GetOffset( ) const
{
	return mOffset;
}

template< class InterfaceType, class Type >
_ubool TUIProxy< InterfaceType, Type >::HasBegun( ) const
{
	return mOpFlags.GetFlags( ) != 0;
}

}