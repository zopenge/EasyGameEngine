//! @file     chromeEditBox.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// chromeEditBox
//----------------------------------------------------------------------------

class chromeEditBox : public TEditBox< IEditBox >
{
private:
	typedef TEditBox< IEditBox > BaseClass;

public:
	chromeEditBox( );
	virtual ~chromeEditBox( );

// IEditBox Interface
public:
	virtual _ubool	Open( _INPUT_TYPE input_type, _ubool is_password, UStringPtr text = "", UStringPtr default_text = "", _dword max_length = -1 ) override;
	virtual _ubool	Open( _INPUT_TYPE input_type, _ubool is_password, WStringPtr text = L"", WStringPtr default_text = L"", _dword max_length = -1 ) override;
	virtual _void	Close( ) override;
};

//----------------------------------------------------------------------------
// chromeEditBox Implementation
//----------------------------------------------------------------------------

}