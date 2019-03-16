//! @file     TXYPosUIProxy.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TXYPosUIProxy
//----------------------------------------------------------------------------

template< class InterfaceType, class Type >
class TXYPosUIProxy : public InterfaceType
{
protected:
	typedef IXYPosBaseUIProxy< Type > BaseInterface;

protected:
	//!	The center block size
	Type			mCenterBlockSize;
	//!	The length
	Point< Type >	mLength;

	//!	The min position
	Point< Type >	mMinPos;
	//!	The max position
	Point< Type >	mMaxPos;

	//!	The delta position
	Point< Type >	mDeltaPos;

protected:
	//!	Limit x-pos.
	_void LimitXPos( );
	//!	Limit y-pos.
	_void LimitYPos( );

protected:
	TXYPosUIProxy( );
	virtual ~TXYPosUIProxy( );

// IXYPosBaseUIProxy Interface
public:
	virtual const Point< Type >&	GetCurPos( ) const override;
	virtual const Point< Type >&	GetCurDeltaPos( ) const override;

	virtual _void					SetCenterBlockSize( Type size ) override;
	virtual Type					GetCenterBlockSize( ) const override;

	virtual _void					SetLength( const Point< Type >& length ) override;
	virtual const Point< Type >&	GetLength( ) const override;

	virtual _void					SetMinPos( const Point< Type >& pos ) override;
	virtual const Point< Type >&	GetMinPos( ) const override;
	virtual _void					SetMaxPos( const Point< Type >& pos ) override;
	virtual const Point< Type >&	GetMaxPos( ) const override;

	virtual _dword					UpdatePos( const Point< Type >& pos ) override;

	virtual _dword					AutoDetectOpStatus( const Point< Type >& initial_pos, const Point< Type >& pos ) const override;

	virtual _void					Begin( _dword status, const Point< Type >& pos ) override;
	virtual _void					End( ) override;
};

//----------------------------------------------------------------------------
// TXYPosUIProxy Implementation
//----------------------------------------------------------------------------

template< class InterfaceType, class Type >
TXYPosUIProxy< InterfaceType, Type >::TXYPosUIProxy( )
{
	mCenterBlockSize	= (Type)0;

	mLength				= Point< Type >::cMinPoint;

	mMinPos				= Point< Type >::cMinPoint;
	mMaxPos				= Point< Type >::cMaxPoint;

	mDeltaPos			= Point< Type >::cZeroPoint;
}

template< class InterfaceType, class Type >
TXYPosUIProxy< InterfaceType, Type >::~TXYPosUIProxy( )
{
}

template< class InterfaceType, class Type >
_void TXYPosUIProxy< InterfaceType, Type >::LimitXPos( )
{
	this->mPos.x = Math::Clamp( this->mPos.x, mMinPos.x, mMaxPos.x );
}

template< class InterfaceType, class Type >
_void TXYPosUIProxy< InterfaceType, Type >::LimitYPos( )
{
	this->mPos.y = Math::Clamp( this->mPos.y, mMinPos.y, mMaxPos.y );
}

template< class InterfaceType, class Type >
const Point< Type >& TXYPosUIProxy< InterfaceType, Type >::GetCurPos( ) const
{
	return this->mPos;
}

template< class InterfaceType, class Type >
const Point< Type >& TXYPosUIProxy< InterfaceType, Type >::GetCurDeltaPos( ) const
{
	return mDeltaPos;
}

template< class InterfaceType, class Type >
_void TXYPosUIProxy< InterfaceType, Type >::SetCenterBlockSize( Type size )
{
	mCenterBlockSize = size;
}

template< class InterfaceType, class Type >
Type TXYPosUIProxy< InterfaceType, Type >::GetCenterBlockSize( ) const
{
	return mCenterBlockSize;
}

template< class InterfaceType, class Type >
_void TXYPosUIProxy< InterfaceType, Type >::SetLength( const Point< Type >& length )
{
	mLength = length;
}

template< class InterfaceType, class Type >
const Point< Type >& TXYPosUIProxy< InterfaceType, Type >::GetLength( ) const
{
	return mLength;
}

template< class InterfaceType, class Type >
_void TXYPosUIProxy< InterfaceType, Type >::SetMinPos( const Point< Type >& pos )
{
	mMinPos = pos;
}

template< class InterfaceType, class Type >
const Point< Type >& TXYPosUIProxy< InterfaceType, Type >::GetMinPos( ) const
{
	return mMinPos;
}

template< class InterfaceType, class Type >
_void TXYPosUIProxy< InterfaceType, Type >::SetMaxPos( const Point< Type >& pos )
{
	mMaxPos = pos;
}

template< class InterfaceType, class Type >
const Point< Type >& TXYPosUIProxy< InterfaceType, Type >::GetMaxPos( ) const
{
	return mMaxPos;
}

template< class InterfaceType, class Type >
_dword TXYPosUIProxy< InterfaceType, Type >::UpdatePos( const Point< Type >& pos )
{
	// Get the current operation flag
	_dword cur_op_flags = this->GetCurOpStatus( );

	// Update position with operation flag
	switch ( cur_op_flags )
	{
		case BaseInterface::_OP_STATUS_NONE:
		{
			// Nothing to do ...
		}
		break;

		case BaseInterface::_OP_STATUS_X_CHANGING:
		{
			Point< Type > delta_pos = this->GetDeltaPos( pos );
			this->mPos.x += delta_pos.x;

			mDeltaPos.x = delta_pos.x;
			mDeltaPos.y = (Type)0;

			LimitXPos( );
		}
		break;

		case BaseInterface::_OP_STATUS_Y_CHANGING:
		{
			Point< Type > delta_pos = this->GetDeltaPos( pos );
			this->mPos.y += delta_pos.y;

			mDeltaPos.x = (Type)0;
			mDeltaPos.y = delta_pos.y;

			LimitYPos( );
		}
		break;

		case BaseInterface::_OP_STATUS_POS_CHANGING:
		{
			Point< Type > delta_pos = this->GetDeltaPos( pos );
			this->mPos += delta_pos;

			mDeltaPos = delta_pos;

			LimitXPos( );
			LimitYPos( );
		}
		break;

		default:
			break;
	}

	return cur_op_flags;
}

template< class InterfaceType, class Type >
_dword TXYPosUIProxy< InterfaceType, Type >::AutoDetectOpStatus( const Point< Type >& initial_pos, const Point< Type >& pos ) const
{
	// The rectangles
	Rect< Type > x_rect		= Rect< Type >( ).InitWithSize( initial_pos.x, initial_pos.y, mLength.x, 1 );
	Rect< Type > y_rect		= Rect< Type >( ).InitWithSize( initial_pos.x, initial_pos.y, 1, mLength.y );
	Rect< Type > xy_rect	= Rect< Type >( ).InitWithSize( initial_pos.x, initial_pos.y, mCenterBlockSize, mCenterBlockSize );

	// Fix the rectangles with border size
	x_rect.Inflate( this->GetBorderSize( ), this->GetBorderSize( ) );
	y_rect.Inflate( this->GetBorderSize( ), this->GetBorderSize( ) );

	// Test position
	if ( xy_rect.PointInRect( pos ) )
		return BaseInterface::_OP_STATUS_POS_CHANGING;
	else if ( x_rect.PointInRect( pos ) )
		return BaseInterface::_OP_STATUS_X_CHANGING;
	else if ( y_rect.PointInRect( pos ) )
		return BaseInterface::_OP_STATUS_Y_CHANGING;

	return BaseInterface::_OP_STATUS_NONE;
}

template< class InterfaceType, class Type >
_void TXYPosUIProxy< InterfaceType, Type >::Begin( _dword status, const Point< Type >& pos )
{
	this->mOpFlags	= status;
	this->mPos		= pos;
	this->mDeltaPos	= Point< Type >::cZeroPoint;
}

template< class InterfaceType, class Type >
_void TXYPosUIProxy< InterfaceType, Type >::End( )
{
	this->mOpFlags.Clear( );

	this->mPos		= Point< Type >::cZeroPoint;
	this->mDeltaPos	= Point< Type >::cZeroPoint;
}

}