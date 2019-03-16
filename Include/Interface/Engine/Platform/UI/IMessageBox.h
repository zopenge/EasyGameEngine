//! @file     IMessageBox.h
//! @author   LiCode
//! @version  1.0.0.547
//! @date     2011/01/07
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IMessageBoxNotifier
//----------------------------------------------------------------------------

class IMessageBoxNotifier : public IObject
{
public:
	//!	When click button.
	//!	@param		button_id	The button ID.
	//!	@return		none.
	virtual _void OnClickButton( _MESSAGE_BOX_BUTTON_ID button_id ) PURE;
};

//----------------------------------------------------------------------------
// IMessageBox
//----------------------------------------------------------------------------

class IMessageBox : public IObject
{
public:
	//!	Set the notifier.
	//!	@param		notifier		The notifier.
	//!	@return		none.
	virtual _void SetNotifier( IMessageBoxNotifier* notifier ) PURE;
	//!	Get the notifier.
	//!	@param		none.
	//!	@return		The notifier.
	virtual IMessageBoxNotifier* GetNotifier( ) PURE;

	//!	Show the message box.
	//!	@param		title			The title text.
	//!	@param		content			The content text.
	//!	@param		yes_text		The yes button text.
	//!	@param		no_text			The no button text.
	//!	@param		type			The message box type.
	//!	@return		none.
	virtual _void Show( WStringPtr title, WStringPtr content, WStringPtr yes_text, WStringPtr no_text, _MESSAGE_BOX_TYPE type ) PURE;
};

}
