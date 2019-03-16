//! @file     TCircleUIProxy.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TCircleUIProxy
//----------------------------------------------------------------------------

template< class InterfaceType, class Type >
class TCircleUIProxy : public InterfaceType
{
protected:
	typedef ICircleBaseUIProxy< Type > BaseInterface;

protected:
	//!	The delta radian
	_float			mDeltaRadian;

	//!	The initial pos
	Point< Type >	mInitialPos;

protected:
	TCircleUIProxy( );
	virtual ~TCircleUIProxy( );

// IXYPosBaseUIProxy Interface
public:
	virtual _float	GetDeltaRadian( ) const override;

	virtual _dword	UpdatePos( const Point< Type >& pos ) override;

	virtual _dword	AutoDetectOpStatus( const Point< Type >& initial_pos, Type radius, const Point< Type >& pos ) const override;

	virtual _void	Begin( _dword status, const Point< Type >& initial_pos, const Point< Type >& pos ) override;
	virtual _void	End( ) override;
};

//----------------------------------------------------------------------------
// TCircleUIProxy Implementation
//----------------------------------------------------------------------------

template< class InterfaceType, class Type >
TCircleUIProxy< InterfaceType, Type >::TCircleUIProxy( )
{
	mDeltaRadian	= 0.0f;

	mInitialPos		= Point< Type >::cZeroPoint;
}

template< class InterfaceType, class Type >
TCircleUIProxy< InterfaceType, Type >::~TCircleUIProxy( )
{
}

template< class InterfaceType, class Type >
_float TCircleUIProxy< InterfaceType, Type >::GetDeltaRadian( ) const
{
	return mDeltaRadian;
}

template< class InterfaceType, class Type >
_dword TCircleUIProxy< InterfaceType, Type >::UpdatePos( const Point< Type >& pos )
{
	// Get the current operation flag
	_dword cur_op_flags = this->GetCurOpStatus( );

	// Update radian with operation flag
	switch ( cur_op_flags )
	{
		case BaseInterface::_OP_STATUS_NONE:
		{
			// Nothing to do ...
		}
		break;

		case BaseInterface::_OP_STATUS_ROTATING:
		{
			// Calculate the delta radian
			Vector2 v1( (_float) this->mPos.x - (_float) mInitialPos.x, (_float) this->mPos.y - (_float) mInitialPos.y );
			Vector2 v2( (_float) pos.x - (_float) mInitialPos.x, (_float) pos.y - (_float) mInitialPos.y );
			mDeltaRadian = Vector2::Radian( v1, v2 );

			// Update the current position
			Point< Type > delta_pos = this->GetDeltaPos( pos );
			this->mPos += delta_pos;
		}
		break;

		default:
			break;
	}

	return cur_op_flags;
}

template< class InterfaceType, class Type >
_dword TCircleUIProxy< InterfaceType, Type >::AutoDetectOpStatus( const Point< Type >& initial_pos, Type radius, const Point< Type >& pos ) const
{
	// Get the distance from current position to initial position
	Type length = ( pos - initial_pos ).Magnitude( );
	
	// Get the selected range by radius and border size
	Type min_dis = (Type) 0;
	Type max_dis = (Type) 0;
	if ( this->GetBorderFlag( ) == BaseInterface::_BORDER_FLAG_INNER )
	{
		min_dis = radius - this->GetBorderSize( );
		max_dis = radius;
	}
	else if ( this->GetBorderFlag( ) == BaseInterface::_BORDER_FLAG_OUTER )
	{
		min_dis = radius;
		max_dis = radius + this->GetBorderSize( );
	}
	else if ( this->GetBorderFlag( ) == BaseInterface::_BORDER_FLAG_BOTH_INNER_AND_OUTER )
	{
		min_dis = radius - (this->GetBorderSize( ) / ((Type) 2));
		max_dis = radius + (this->GetBorderSize( ) / ((Type) 2));
	}

	// Test position
	if ( length >= min_dis && length <= max_dis )
		return BaseInterface::_OP_STATUS_ROTATING;

	return BaseInterface::_OP_STATUS_NONE;
}

template< class InterfaceType, class Type >
_void TCircleUIProxy< InterfaceType, Type >::Begin( _dword status, const Point< Type >& initial_pos, const Point< Type >& pos )
{
	this->mOpFlags		= status;

	this->mDeltaRadian	= 0.0f;

	this->mInitialPos	= initial_pos;
	this->mPos			= pos;
}

template< class InterfaceType, class Type >
_void TCircleUIProxy< InterfaceType, Type >::End( )
{
	this->mOpFlags.Clear( );

	this->mDeltaRadian	= 0.0f;

	this->mPos			= Point< Type >::cZeroPoint;
	this->mInitialPos	= Point< Type >::cZeroPoint;
}

}