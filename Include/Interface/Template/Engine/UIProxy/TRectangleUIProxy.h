//! @file     TRectangleUIProxy.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TRectangleUIProxy
//----------------------------------------------------------------------------

template< class InterfaceType, class Type >
class TRectangleUIProxy : public InterfaceType
{
protected:
	typedef IRectangleBaseUIProxy< Type > BaseInterface;

protected:
	//!	The min pos
	Point< Type >	mMinPos;
	//!	The max pos
	Point< Type >	mMaxPos;

	//!	The min size
	Point< Type >	mMinSize;
	//!	The max size
	Point< Type >	mMaxSize;

	//!	The initial position
	Point< Type >	mInitialPos;

	//!	The region
	Rect< Type >	mRect;

protected:
	//!	Check whether it's in left block.
	_ubool IsInLeftBlock( const Point< Type >& pos, const Rect< Type >& inner_rect, const Rect< Type >& outer_rect ) const;
	//!	Check whether it's in top block.
	_ubool IsInTopBlock( const Point< Type >& pos, const Rect< Type >& inner_rect, const Rect< Type >& outer_rect ) const;
	//!	Check whether it's in right block.
	_ubool IsInRightBlock( const Point< Type >& pos, const Rect< Type >& inner_rect, const Rect< Type >& outer_rect ) const;
	//!	Check whether it's in bottom block.
	_ubool IsInBottomBlock( const Point< Type >& pos, const Rect< Type >& inner_rect, const Rect< Type >& outer_rect ) const;

	//!	Limit left by min-pos.
	_void LimitLeftByMinPos( );
	//!	Limit top by min-pos.
	_void LimitTopByMinPos( );
	//!	Limit right by max-pos.
	_void LimitRightByMaxPos( );
	//!	Limit bottom by max-pos.
	_void LimitBottomByMaxPos( );

	//!	Limit left by width.
	_void LimitLeftByWidth( );
	//!	Limit top by height.
	_void LimitTopByHeight( );
	//!	Limit right by width.
	_void LimitRightByWidth( );
	//!	Limit bottom by height.
	_void LimitBottomByHeight( );

protected:
	TRectangleUIProxy( );
	virtual ~TRectangleUIProxy( );

// IRectangleBaseUIProxy Interface
public:
	virtual const Rect< Type >&		GetCurRect( ) const override;
	virtual RectF					GetCurRectF( ) const override;

	virtual _void					SetMinPos( const Point< Type >& pos ) override;
	virtual const Point< Type >&	GetMinPos( ) const override;
	virtual _void					SetMaxPos( const Point< Type >& pos ) override;
	virtual const Point< Type >&	GetMaxPos( ) const override;

	virtual _void					SetMinSize( const Point< Type >& size ) override;
	virtual const Point< Type >&	GetMinSize( ) const override;
	virtual _void					SetMaxSize( const Point< Type >& size ) override;
	virtual const Point< Type >&	GetMaxSize( ) const override;

	virtual _dword					UpdatePos( const Point< Type >& pos ) override;

	virtual _dword					AutoDetectOpStatus( const Point< Type >& pos, const Rect< Type >& rect ) const override;

	virtual _void					Begin( _dword status, const Point< Type >& pos ) override;
	virtual _void					Begin( _dword status, const Point< Type >& pos, const Rect< Type >& rect ) override;
	virtual _void					End( ) override;
};

//----------------------------------------------------------------------------
// TRectangleUIProxy Implementation
//----------------------------------------------------------------------------

template< class InterfaceType, class Type >
TRectangleUIProxy< InterfaceType, Type >::TRectangleUIProxy( )
{
	mMinPos		= Point< Type >::cMinPoint;
	mMaxPos		= Point< Type >::cMaxPoint;

	mMinSize	= Point< Type >::cMinPoint;
	mMaxSize	= Point< Type >::cMaxPoint;

	mInitialPos	= Point< Type >::cZeroPoint;

	mRect		= Rect< Type >::cNull;
}

template< class InterfaceType, class Type >
TRectangleUIProxy< InterfaceType, Type >::~TRectangleUIProxy( )
{
}

template< class InterfaceType, class Type >
_ubool TRectangleUIProxy< InterfaceType, Type >::IsInLeftBlock( const Point< Type >& pos, const Rect< Type >& inner_rect, const Rect< Type >& outer_rect ) const
{
	if ( pos.x > inner_rect.l || pos.x < outer_rect.l )
		return _false;

	if ( pos.y < outer_rect.t || pos.y > outer_rect.b )
		return _false;

	return _true;
}

template< class InterfaceType, class Type >
_ubool TRectangleUIProxy< InterfaceType, Type >::IsInTopBlock( const Point< Type >& pos, const Rect< Type >& inner_rect, const Rect< Type >& outer_rect ) const
{
	if ( pos.y > inner_rect.t || pos.y < outer_rect.t )
		return _false;

	if ( pos.x < outer_rect.l || pos.x > outer_rect.r )
		return _false;

	return _true;
}

template< class InterfaceType, class Type >
_ubool TRectangleUIProxy< InterfaceType, Type >::IsInRightBlock( const Point< Type >& pos, const Rect< Type >& inner_rect, const Rect< Type >& outer_rect ) const
{
	if ( pos.x > outer_rect.r || pos.x < inner_rect.r )
		return _false;

	if ( pos.y < outer_rect.t || pos.y > outer_rect.b )
		return _false;

	return _true;
}

template< class InterfaceType, class Type >
_ubool TRectangleUIProxy< InterfaceType, Type >::IsInBottomBlock( const Point< Type >& pos, const Rect< Type >& inner_rect, const Rect< Type >& outer_rect ) const
{
	if ( pos.y > outer_rect.b || pos.y < inner_rect.b )
		return _false;

	if ( pos.x < outer_rect.l || pos.x > outer_rect.r )
		return _false;

	return _true;
}

template< class InterfaceType, class Type >
_void TRectangleUIProxy< InterfaceType, Type >::LimitLeftByMinPos( )
{
	mRect.l = Math::Max< Type >( mMinPos.x, mRect.l );
}

template< class InterfaceType, class Type >
_void TRectangleUIProxy< InterfaceType, Type >::LimitTopByMinPos( )
{
	mRect.t = Math::Max< Type >( mMinPos.y, mRect.t );
}

template< class InterfaceType, class Type >
_void TRectangleUIProxy< InterfaceType, Type >::LimitRightByMaxPos( )
{
	mRect.r = Math::Min< Type >( mMaxPos.x, mRect.r );
}

template< class InterfaceType, class Type >
_void TRectangleUIProxy< InterfaceType, Type >::LimitBottomByMaxPos( )
{
	mRect.b = Math::Min< Type >( mMaxPos.y, mRect.b );
}

template< class InterfaceType, class Type >
_void TRectangleUIProxy< InterfaceType, Type >::LimitLeftByWidth( )
{
	Type width = Math::Clamp( mRect.GetWidth( ), mMinSize.x, mMaxSize.x );
	mRect.l = mRect.r - width;
}

template< class InterfaceType, class Type >
_void TRectangleUIProxy< InterfaceType, Type >::LimitTopByHeight( )
{
	Type height = Math::Clamp( mRect.GetHeight( ), mMinSize.y, mMaxSize.y );
	mRect.t = mRect.b - height;
}

template< class InterfaceType, class Type >
_void TRectangleUIProxy< InterfaceType, Type >::LimitRightByWidth( )
{
	Type width = Math::Clamp( mRect.GetWidth( ), mMinSize.x, mMaxSize.x );
	mRect.r = mRect.l + width;
}

template< class InterfaceType, class Type >
_void TRectangleUIProxy< InterfaceType, Type >::LimitBottomByHeight( )
{
	Type height = Math::Clamp( mRect.GetHeight( ), mMinSize.y, mMaxSize.y );
	mRect.b = mRect.t + height;
}

template< class InterfaceType, class Type >
const Rect< Type >& TRectangleUIProxy< InterfaceType, Type >::GetCurRect( ) const
{
	return mRect;
}

template< class InterfaceType, class Type >
RectF TRectangleUIProxy< InterfaceType, Type >::GetCurRectF( ) const
{
	return RectF( (_float) mRect.l, (_float) mRect.t, (_float) mRect.r, (_float) mRect.b );
}

template< class InterfaceType, class Type >
_void TRectangleUIProxy< InterfaceType, Type >::SetMinPos( const Point< Type >& pos )
{
	mMinPos = pos;
}

template< class InterfaceType, class Type >
const Point< Type >& TRectangleUIProxy< InterfaceType, Type >::GetMinPos( ) const 
{
	return mMinPos;
}

template< class InterfaceType, class Type >
_void TRectangleUIProxy< InterfaceType, Type >::SetMaxPos( const Point< Type >& pos )
{
	mMaxPos = pos;
}

template< class InterfaceType, class Type >
const Point< Type >& TRectangleUIProxy< InterfaceType, Type >::GetMaxPos( ) const
{
	return mMaxPos;
}

template< class InterfaceType, class Type >
_void TRectangleUIProxy< InterfaceType, Type >::SetMinSize( const Point< Type >& size )
{
	mMinSize = size;
}

template< class InterfaceType, class Type >
const Point< Type >& TRectangleUIProxy< InterfaceType, Type >::GetMinSize( ) const 
{
	return mMinSize;
}

template< class InterfaceType, class Type >
_void TRectangleUIProxy< InterfaceType, Type >::SetMaxSize( const Point< Type >& size )
{
	mMaxSize = size;
}

template< class InterfaceType, class Type >
const Point< Type >& TRectangleUIProxy< InterfaceType, Type >::GetMaxSize( ) const
{
	return mMaxSize;
}

template< class InterfaceType, class Type >
_dword TRectangleUIProxy< InterfaceType, Type >::UpdatePos( const Point< Type >& pos )
{
	// Limit position by min-max bounds
	Point< Type > fixed_pos = pos;
	fixed_pos.x = Math::Clamp( pos.x, mMinPos.x, mMaxPos.x );
	fixed_pos.y = Math::Clamp( pos.y, mMinPos.y, mMaxPos.y );

	// Get the current operation flag
	_dword cur_op_flags = this->GetCurOpStatus( );

	// Update region with operation flag
	switch ( cur_op_flags )
	{
		case BaseInterface::_OP_STATUS_NONE:
		{
			// Nothing to do ...
		}
		break;

		case BaseInterface::_OP_STATUS_X_CHANGING:
		{
			Point< Type > delta_pos = this->GetDeltaPos( fixed_pos );
			mRect.l += delta_pos.x;
			mRect.r += delta_pos.x;

			LimitLeftByMinPos( );
			LimitRightByMaxPos( );
		}
		break;

		case BaseInterface::_OP_STATUS_Y_CHANGING:
		{
			Point< Type > delta_pos = this->GetDeltaPos( fixed_pos );
			mRect.t += delta_pos.y;
			mRect.b += delta_pos.y;

			LimitTopByMinPos( );
			LimitBottomByMaxPos( );
		}
		break;

		case BaseInterface::_OP_STATUS_POS_CHANGING:
		{
			Point< Type > delta_pos = this->GetDeltaPos( fixed_pos );
			Point< Type > size		= mRect.GetSize( );

			// Move to right
			if ( delta_pos.x > 0 )
			{
				mRect.r += delta_pos.x;
				LimitRightByMaxPos( );
				mRect.l  = mRect.r - size.x;
			}
			// Move to left
			else
			{
				mRect.l += delta_pos.x;
				LimitLeftByMinPos( );
				mRect.r  = mRect.l + size.x;
			}

			// Move to bottom
			if ( delta_pos.y > 0 )
			{
				mRect.b += delta_pos.y;
				LimitBottomByMaxPos( );
				mRect.t  = mRect.b - size.y;
			}
			// Move to top
			else
			{
				mRect.t += delta_pos.y;
				LimitTopByMinPos( );
				mRect.b  = mRect.t + size.y;
			}
		}
		break;

		case BaseInterface::_OP_STATUS_WIDTH_CHANGING:
		{
			Point< Type > delta_pos = this->GetDeltaPos( fixed_pos );
			mRect.r += delta_pos.x;

			LimitRightByMaxPos( );
			LimitRightByWidth( );
		}
		break;

		case BaseInterface::_OP_STATUS_HEIGHT_CHANGING:
		{
			Point< Type > delta_pos = this->GetDeltaPos( fixed_pos );
			mRect.b += delta_pos.y;

			LimitBottomByMaxPos( );
			LimitBottomByHeight( );
		}
		break;

		case BaseInterface::_OP_STATUS_MOUSE_DRAGGING:
		{
			Point< Type > delta_pos = this->GetDeltaPos( fixed_pos );

			// InitialPos : Left
			if ( fixed_pos.x > mInitialPos.x )
			{
				mRect.l  = mInitialPos.x;
				mRect.r += delta_pos.x;
				LimitRightByMaxPos( );
			}
			// InitialPos : Right
			else
			{
				mRect.r  = mInitialPos.x;
				mRect.l += delta_pos.x;
				LimitLeftByMinPos( );
			}

			// InitialPos : Top
			if ( fixed_pos.y > mInitialPos.y )
			{
				mRect.t  = mInitialPos.y;
				mRect.b += delta_pos.y;
				LimitBottomByMaxPos( );
			}
			// InitialPos : Right
			else
			{
				mRect.b  = mInitialPos.y;
				mRect.t += delta_pos.y;
				LimitTopByMinPos( );
			}
		}
		break;

		case BaseInterface::_OP_STATUS_SIZE_CHANGING:
		{
			Point< Type > delta_pos = this->GetDeltaPos( fixed_pos );
			mRect.r += delta_pos.x;
			mRect.b += delta_pos.y;

			LimitRightByMaxPos( );
			LimitRightByWidth( );

			LimitBottomByMaxPos( );
			LimitBottomByHeight( );
		}
		break;

		case BaseInterface::_OP_STATUS_X_AND_WIDTH_CHANGING:
		{
			Point< Type > delta_pos = this->GetDeltaPos( fixed_pos );
			mRect.l += delta_pos.x;

			LimitLeftByMinPos( );
			LimitLeftByWidth( );
		}
		break;

		case BaseInterface::_OP_STATUS_Y_AND_HEIGHT_CHANGING:
		{
			Point< Type > delta_pos = this->GetDeltaPos( fixed_pos );
			mRect.t += delta_pos.y;

			LimitTopByMinPos( );
			LimitTopByHeight( );
		}
		break;

		case BaseInterface::_OP_STATUS_X_AND_SIZE_CHANGING:
		{
			Point< Type > delta_pos = this->GetDeltaPos( fixed_pos );
			mRect.l += delta_pos.x;
			mRect.b += delta_pos.y;

			LimitLeftByMinPos( );
			LimitLeftByWidth( );

			LimitBottomByMaxPos( );
			LimitBottomByHeight( );
		}
		break;

		case BaseInterface::_OP_STATUS_Y_AND_SIZE_CHANGING:
		{
			Point< Type > delta_pos = this->GetDeltaPos( fixed_pos );
			mRect.t += delta_pos.y;
			mRect.r += delta_pos.x;

			LimitRightByMaxPos( );
			LimitRightByWidth( );

			LimitTopByMinPos( );
			LimitTopByHeight( );
		}
		break;

		case BaseInterface::_OP_STATUS_POS_AND_SIZE_CHANGING:
		{
			Point< Type > delta_pos = this->GetDeltaPos( fixed_pos );
			mRect.l += delta_pos.x;
			mRect.t += delta_pos.y;

			LimitLeftByMinPos( );
			LimitLeftByWidth( );

			LimitTopByMinPos( );
			LimitTopByHeight( );
		}
		break;

		default:
			break;
	}

	// Update the current position
	this->mPos = fixed_pos;

	return cur_op_flags;
}

template< class InterfaceType, class Type >
_dword TRectangleUIProxy< InterfaceType, Type >::AutoDetectOpStatus( const Point< Type >& pos, const Rect< Type >& rect ) const
{
	// The inner and outer rect
	const Rect< Type >* inner_rect = _null;
	const Rect< Type >* outer_rect = _null;

	// Fix the region by offset
	Rect< Type > fixed_rect				= rect + this->mOffset;
	Rect< Type > fixed_rect_with_border	= fixed_rect;
	
	// Fix the border rectangle with flag
	if ( this->mBorderFlag == BaseInterface::_BORDER_FLAG_INNER )
	{
		inner_rect = &fixed_rect_with_border;
		outer_rect = &fixed_rect;

		fixed_rect_with_border.Deflate( this->mBorderSize, this->mBorderSize );
	}
	else
	{
		inner_rect = &fixed_rect;
		outer_rect = &fixed_rect_with_border;

		fixed_rect_with_border.Inflate( this->mBorderSize, this->mBorderSize );
	}

	// LT/X with width/X with size
	if ( IsInLeftBlock( pos, *inner_rect, *outer_rect ) )
	{
		if ( IsInTopBlock( pos, *inner_rect, *outer_rect ) )
			return BaseInterface::_OP_STATUS_POS_AND_SIZE_CHANGING;
		else if ( IsInBottomBlock( pos, *inner_rect, *outer_rect ) )
			return BaseInterface::_OP_STATUS_X_AND_SIZE_CHANGING;
		else
			return BaseInterface::_OP_STATUS_X_AND_WIDTH_CHANGING;
	}
	// RB/Right/Y with size
	else if ( IsInRightBlock( pos, *inner_rect, *outer_rect ) )
	{
		if ( IsInBottomBlock( pos, *inner_rect, *outer_rect ) )
			return BaseInterface::_OP_STATUS_SIZE_CHANGING;
		else if ( IsInTopBlock( pos, *inner_rect, *outer_rect ) )
			return BaseInterface::_OP_STATUS_Y_AND_SIZE_CHANGING;
		else
			return BaseInterface::_OP_STATUS_WIDTH_CHANGING;
	}
	// Y with height
	else if ( IsInTopBlock( pos, *inner_rect, *outer_rect ) )
	{
		return BaseInterface::_OP_STATUS_Y_AND_HEIGHT_CHANGING;
	}
	// Height
	else if ( IsInBottomBlock( pos, *inner_rect, *outer_rect ) )
	{
		return BaseInterface::_OP_STATUS_HEIGHT_CHANGING;
	}
	// Moving/Pos changing
	else if ( outer_rect->PointInRect( pos ) )
	{
		return BaseInterface::_OP_STATUS_POS_CHANGING;
	}
	else
	{
		return BaseInterface::_OP_STATUS_NONE;
	}
}

template< class InterfaceType, class Type >
_void TRectangleUIProxy< InterfaceType, Type >::Begin( _dword status, const Point< Type >& pos )
{
	this->mOpFlags		= status;
	this->mPos			= pos;

	this->mInitialPos	= pos;

	this->mRect.l		= mInitialPos.x;
	this->mRect.t		= mInitialPos.y;
	this->mRect.r		= mInitialPos.x;
	this->mRect.b		= mInitialPos.y;
}

template< class InterfaceType, class Type >
_void TRectangleUIProxy< InterfaceType, Type >::Begin( _dword status, const Point< Type >& pos, const Rect< Type >& rect )
{
	this->mOpFlags		= status;
	this->mPos			= pos;
	this->mRect			= rect;

	this->mInitialPos	= pos;
}

template< class InterfaceType, class Type >
_void TRectangleUIProxy< InterfaceType, Type >::End( )
{
	this->mOpFlags.Clear( );
}

}