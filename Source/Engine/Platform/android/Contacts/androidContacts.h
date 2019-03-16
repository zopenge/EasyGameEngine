//! @file     androidContacts.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// androidContacts
//----------------------------------------------------------------------------

class androidContacts : public TObject< IContacts >
{
private:
	ObjInfoArray	mObjects;

public:
	androidContacts( );
	virtual ~androidContacts( );

// IContacts Interface
public:
	virtual void Refresh( );

	virtual const ObjInfoArray& GetObjects( ) const override;
};

//----------------------------------------------------------------------------
// androidContacts Implementation
//----------------------------------------------------------------------------

}