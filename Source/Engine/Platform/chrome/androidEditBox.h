//! @file     androidEditBox.h
//! @author   LiCode
//! @version  1.0.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// androidEditBox
//----------------------------------------------------------------------------

class androidEditBox : public TEditBox< IEditBox >
{
private:
	//!	Build parameters.
	_ubool BuildParameters( UString& parameters, _INPUT_TYPE input_type, _ubool is_password, UStringPtr text );

public:
	androidEditBox( );
	virtual ~androidEditBox( );

// IEditBox Interface
public:
	virtual _ubool	Open( _INPUT_TYPE input_type, _ubool is_password, UStringPtr text = "" ) override;
	virtual _void	Close( ) override;
};

//----------------------------------------------------------------------------
// androidEditBox Implementation
//----------------------------------------------------------------------------

}