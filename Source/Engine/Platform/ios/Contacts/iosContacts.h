//! @file     iosContacts.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// iosContacts
//----------------------------------------------------------------------------

class iosContacts : public TObject< IContacts >
{
private:
	ObjInfoArray	mObjects;

public:
	iosContacts( );
	virtual ~iosContacts( );

// IContacts Interface
public:
    virtual void Refresh( ) override;
	virtual const ObjInfoArray& GetObjects( ) const override;
};

//----------------------------------------------------------------------------
// iosContacts Implementation
//----------------------------------------------------------------------------

}