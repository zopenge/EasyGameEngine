//! @file     RefObject.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TRefObject
//----------------------------------------------------------------------------

template< typename Type > 
class TRefObject : public Type
{
protected:
	_dword	mRefCount;

protected:
	TRefObject( ) : mRefCount( 1 ) { }
	virtual ~TRefObject( ) { _DEFAULT_ASSERT( mRefCount == 1 ); }

public:
	virtual _dword GetRefCount( ) const { return mRefCount; }
	virtual _dword AddRef( ) { return ++ mRefCount; }
	virtual _dword Release( )
	{
		if ( mRefCount > 1 )
		{
			mRefCount --;
			return mRefCount;
		}
		else
		{
			delete this;
			return 0;
		}
	}
};

//----------------------------------------------------------------------------
// RefObject
//----------------------------------------------------------------------------

class RefObject
{
protected:
	_dword	mRefCount;

protected:
	RefObject( ) : mRefCount( 1 ) 
	{
	}
	virtual ~RefObject( ) 
	{
#ifdef _PLATFORM_WINDOWS_
		EGE_ASSERT( mRefCount == 1 ); 
#else
		_DEFAULT_ASSERT( mRefCount == 1 ); 
#endif
	}

public:
	virtual _dword GetRefCount( ) const { return mRefCount; }
	virtual _dword AddRef( ) { return ++ mRefCount; }
	virtual _dword Release( )
	{
		if ( mRefCount > 1 )
		{
			mRefCount --;
			return mRefCount;
		}
		else
		{
			delete this;
			return 0;
		}
	}
};

}