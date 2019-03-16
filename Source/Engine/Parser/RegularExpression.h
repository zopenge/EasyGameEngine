//! @file     RegularExpression.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// RegularExpression
//----------------------------------------------------------------------------

class RegularExpression : public INTERFACE_OBJECT_IMPL( IRegularExpression )
{
private:
	//!	The match options
	_dword	mOptions;

	//!	The PCRE context handle
	_handle	mPCREContext;
	//!	The PCRE extra for speedup matching
	_handle	mPCREExtra;
	//!	The PCRE pattern string
	WString	mPCREPatternString;

private:
	//!	Clear PCRE context.
	_void Clear( );

public:
	RegularExpression( );
	virtual ~RegularExpression( );

// IRegularExpression Interface
public:
	virtual _ubool		SetPattern( WStringPtr pattern, _dword options = _MATCH_CASELESS ) override;
	virtual WStringPtr	GetPattern( ) const override;

	virtual _ubool 		Match( AStringPtr string ) const override;
	virtual _ubool 		Match( WStringPtr string ) const override;
};

}