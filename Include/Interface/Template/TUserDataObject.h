//! @file     TUserDataObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TUserDataObject
//----------------------------------------------------------------------------

template< typename Type >
class TUserDataObject : public Type
{
protected:
	//!	The user data
	_qword	mUserData;

protected:
	TUserDataObject( ) { mUserData = 0; }
	virtual ~TUserDataObject( ) { }

// IUserDataObject Interface
public:
	virtual _void	SetUserData( _qword userdata ) { mUserData = userdata; }
	virtual _qword	GetUserData( ) const { return mUserData; }
};

//----------------------------------------------------------------------------
// TUserDataObject2
//----------------------------------------------------------------------------

template< typename Type >
class TUserDataObject2 : public Type
{
protected:
	//!	The user data
	_qword	mUserData1;
	_qword	mUserData2;

protected:
	TUserDataObject2( ) { mUserData1 = 0; mUserData2 = 0; }
	virtual ~TUserDataObject2( ) { }

// IUserDataObject Interface
public:
	virtual _void	SetUserData1( _qword userdata ) { mUserData1 = userdata; }
	virtual _qword	GetUserData1( ) const { return mUserData1; }

	virtual _void	SetUserData2( _qword userdata ) { mUserData2 = userdata; }
	virtual _qword	GetUserData2( ) const { return mUserData2; }
};

//----------------------------------------------------------------------------
// TDynamicUserDataObject2
//----------------------------------------------------------------------------

template< typename Type >
class TDynamicUserDataObject2 : public Type
{
protected:
	//!	The user data
	struct UserDataInfo
	{
		_qword	mUserData1;
		_qword	mUserData2;

		UserDataInfo( ) 
		{
			mUserData1 = 0; 
			mUserData2 = 0; 
		}
	};

protected:
	UserDataInfo*	mUserDataInfo;

protected:
	TDynamicUserDataObject2( ) 
	{ 
		mUserDataInfo = _null; 
	}
	virtual ~TDynamicUserDataObject2( ) 
	{
		EGE_DELETE( mUserDataInfo ); 
	}

// IUserDataObject Interface
public:
	virtual _void SetUserData1( _qword userdata ) 
	{
		if ( userdata == GetUserData1( ) )
			return;

		if ( mUserDataInfo == _null ) 
			mUserDataInfo = new UserDataInfo( ); 
		
		mUserDataInfo->mUserData1 = userdata; 
	}
	virtual _qword GetUserData1( ) const 
	{
		if ( mUserDataInfo == _null )
			return 0;

		return mUserDataInfo->mUserData1; 
	}

	virtual _void SetUserData2( _qword userdata )
	{
		if ( userdata == GetUserData2( ) )
			return;

		if ( mUserDataInfo == _null )
			mUserDataInfo = new UserDataInfo( );

		mUserDataInfo->mUserData2 = userdata;
	}
	virtual _qword GetUserData2( ) const
	{
		if ( mUserDataInfo == _null )
			return 0;

		return mUserDataInfo->mUserData2;
	}
};

}