//! @file     iosEditBox.h
//! @author   foreven
//! @version  1.0.0.621
//! @date     2013/09/24

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// iosEditBox
//----------------------------------------------------------------------------

class iosEditBox : public TEditBox< IEditBox >
{
private:
	typedef TEditBox< IEditBox > BaseClass;

private:
	struct NSEditBoxViewManager;

public:
	iosEditBox( );
	virtual ~iosEditBox( );
    
private:
    NSEditBoxViewManager*    mNSEditBoxViewManager;

// IEditBox Interface
public:
    virtual _ubool	Open( _INPUT_TYPE input_type, UStringPtr text = "", UStringPtr default_text = "", _dword max_length = -1, const RectF& region = RectF::cNull ) override;
	virtual _ubool	Open( _INPUT_TYPE input_type, WStringPtr text = L"", WStringPtr default_text = L"", _dword max_length = -1, const RectF& region = RectF::cNull ) override;

	virtual _void	Close( ) override;
	virtual _void	Commit( ) override;
};

//----------------------------------------------------------------------------
// iosEditBox Implementation
//----------------------------------------------------------------------------

}
