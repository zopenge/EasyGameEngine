//! @file     chromeContacts.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// chromeContacts
//----------------------------------------------------------------------------

class chromeContacts : public TObject< IContacts >
{
private:
	ObjInfoArray	mObjects;

public:
	chromeContacts( );
	virtual ~chromeContacts( );

// IContacts Interface
public:
	virtual void Refresh( );

	virtual const ObjInfoArray& GetObjects( ) const override;
};

//----------------------------------------------------------------------------
// chromeContacts Implementation
//----------------------------------------------------------------------------

}