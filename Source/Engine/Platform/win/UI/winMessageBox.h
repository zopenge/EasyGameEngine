//! @file     winMessageBox.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// winMessageBox
//----------------------------------------------------------------------------

class winMessageBox : public TMessageBox< IMessageBox >
{
public:
	winMessageBox( );
	virtual ~winMessageBox( );

// IMessageBox Interface
public:
	virtual _void	Show( WStringPtr title, WStringPtr content, WStringPtr yes_text, WStringPtr no_text, _MESSAGE_BOX_TYPE type ) override;
};

//----------------------------------------------------------------------------
// winMessageBox Implementation
//----------------------------------------------------------------------------

}