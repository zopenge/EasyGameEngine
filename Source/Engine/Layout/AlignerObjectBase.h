//! @file     AlignerObjectBase.h
//! @author   
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// AlignerObjectBase
//----------------------------------------------------------------------------

class AlignerObjectBase
{
protected:
	_float	mWidth;
	_float	mHeight;
	_float	mBaseLineHeight;
	_float	mBottom;

protected:
	_void Clear( )
	{
		mWidth			= 0.0f;
		mHeight			= 0.0f;
		mBaseLineHeight	= 0.0f;
		mBottom			= 0.0f;
	}

protected:
	AlignerObjectBase( )
	{
		Clear( );
	}
	~AlignerObjectBase( )
	{

	}

public:
	//! Access block width.
	EGE_GET_SET_ACCESSOR( _float, Width )
	//! Access block height.
	EGE_GET_SET_ACCESSOR( _float, Height )
	//! Access block base line height.
	EGE_GET_SET_ACCESSOR( _float, BaseLineHeight )
	//! Access block bottom height.
	EGE_GET_SET_ACCESSOR( _float, Bottom )
};

}