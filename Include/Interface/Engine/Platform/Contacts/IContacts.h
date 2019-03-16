//! @file     IContacts.h
//! @author   LiCode
//! @version  1.0.0.522
//! @date     2011/01/05
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IContacts
//----------------------------------------------------------------------------

class IContacts : public IObject
{
public:
	//!	The item object info
	struct ObjInfo
	{
		WString			mName;
		WStringArray	mPhoneNumbers;

		operator WStringPtr( ) const
			{ return mName; }
	};
	typedef Array< ObjInfo > ObjInfoArray;

public:
	//!	Flush contacts info.
	//!	@param		none.
	//!	@return		True indicates successful.
	virtual void Refresh( )  PURE;

	//!	Get the objects.
	//!	@param		none.
	//!	@return		The objects.
	virtual const ObjInfoArray& GetObjects( ) const PURE;
};

}