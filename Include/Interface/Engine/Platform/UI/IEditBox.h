//! @file     IEditBox.h
//! @author   LiCode
//! @version  1.0.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IEditBox
//----------------------------------------------------------------------------

class IEditBox : public IObject
{
public:
	//!	The event type.
	enum _EVENT_TYPE
	{
		_EVENT_OPEN,
		_EVENT_HIDE,
		_EVENT_CANCEL,
		_EVENT_RETURN,
	};

	//!	The input type.
	enum _INPUT_TYPE
	{
		_INPUT_TYPE_NORMAL,
		_INPUT_TYPE_URL,
		_INPUT_TYPE_NUMBER_PAD,
		_INPUT_TYPE_PHONE_PAD,
		_INPUT_TYPE_EMAIL_ADDRESS,
		_INPUT_TYPE_PASSWORD,
	};

public:
	//!	When check character.
	//!	@param		char_code	The character code in UTF-16.
	//!	@param		parameters	The user defined parameters.
	//!	@return		True indicates it's valid character, otherwise it's invalid character.
	typedef _ubool (*OnCheckCharacter)( _charw char_code, const QwordParameters2& parameters );

	//!	When handle event.
	//!	@param		type		The event type, @see IEditBox::_EVENT_TYPE.
	//!	@return		string		The edit box string.
	//!	@param		parameters	The user defined parameters.
	//! @return		True indicates success, false indicates failure.
	typedef _ubool (*OnHandleEvent)( _EVENT_TYPE type, UStringPtr string, const QwordParameters2& parameters );

public:
	//!	Set the check character callback function.
	//!	@param		funcpointer	The function pointer.
	//!	@param		parameters	The user defined parameters.
	//!	@return		none.
	virtual _void SetCheckCharacterFunc( OnCheckCharacter funcpointer, const QwordParameters2& parameters ) PURE;
	//!	Set the handle event callback function.
	//!	@param		funcpointer	The function pointer.
	//!	@param		parameters	The user defined parameters.
	//!	@return		none.
	virtual _void SetHandleEventFunc( OnHandleEvent funcpointer, const QwordParameters2& parameters ) PURE;

	//!	Open with initial text in UTF-8 format.
	//!	@param		input_type		The input type.
	//!	@param		text			The initial text string.
	//!	@param		max_length		The max length of string, -1 indicates unlimited.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Open( _INPUT_TYPE input_type, UStringPtr text = "", UStringPtr defaulttext = "", _dword max_length = -1, const RectF& region = RectF::cNull ) PURE;
	//!	Open with initial text in UTF-16 format.
	//!	@param		input_type		The input type.
	//!	@param		text			The initial text string.
	//!	@param		max_length		The max length of string, -1 indicates unlimited.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Open( _INPUT_TYPE input_type, WStringPtr text = L"", WStringPtr defaulttext = L"", _dword max_length = -1, const RectF& region = RectF::cNull ) PURE;
	//!	Close.
	//!	@param		none.
	//!	@return		none.
	virtual _void Close( ) PURE;
	virtual _void Commit( ) PURE;
};

}