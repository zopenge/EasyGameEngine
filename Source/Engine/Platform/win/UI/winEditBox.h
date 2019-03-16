//! @file     winEditBox.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// winEditBox
//----------------------------------------------------------------------------

class winEditBox : public TEditBox< IEditBox >
{
private:
	typedef TEditBox< IEditBox > BaseClass;

public:
	winEditBox( );
	virtual ~winEditBox( );

// IEditBox Interface
public:
	virtual _ubool	Open( _INPUT_TYPE input_type, UStringPtr text = "", UStringPtr defaulttext = "", _dword max_length = -1, const RectF& region = RectF::cNull ) override;
	virtual _ubool	Open( _INPUT_TYPE input_type, WStringPtr text = L"", WStringPtr defaulttext = L"", _dword max_length = -1, const RectF& region = RectF::cNull ) override;
	virtual _void	Close( ) override;
	virtual _void	Commit( ) override;
};

//----------------------------------------------------------------------------
// winEditBox Implementation
//----------------------------------------------------------------------------

}