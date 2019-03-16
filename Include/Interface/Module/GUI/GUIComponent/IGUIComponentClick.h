//! @file     IGUIComponentClick.h
//! @author   Foreven
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGUIComponentClick
//----------------------------------------------------------------------------

class IGUIComponentClick : public IGUIComponent
{
public:
	CLASS_NAME_DECL( IGUIComponentClick )

public:
	//!	Click.
	//!	@param		none.
	//!	@return		none.
	virtual	_void Click( ) PURE;
};

}