//! @file     TMarkupLangDeclaration.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TMarkupLangDeclaration
//----------------------------------------------------------------------------

template< typename Type >
class TMarkupLangDeclaration : public Type
{
protected:
	//!	The encoding type
	_ENCODING	mEncodingType;
	//!	The version
	Version		mVersion;

protected:
	TMarkupLangDeclaration( _ENCODING encoding, const Version& version );
	virtual ~TMarkupLangDeclaration( );

// ITMarkupLangDeclaration Interface
public:
	virtual _void			SetVersion( const Version& version ) override;
	virtual const Version&	GetVersion( ) const override;

	virtual _void			SetEncoding( _ENCODING encoding ) override;
	virtual _ENCODING		GetEncoding( ) const override;
};

//----------------------------------------------------------------------------
// TMarkupLangDeclaration Implementation
//----------------------------------------------------------------------------

template< typename Type >
TMarkupLangDeclaration< Type >::TMarkupLangDeclaration( _ENCODING encoding, const Version& version ) 
	: mEncodingType( encoding ), mVersion( version )
{
}

template< typename Type >
TMarkupLangDeclaration< Type >::~TMarkupLangDeclaration( )
{
}

template< typename Type >
_void TMarkupLangDeclaration< Type >::SetVersion( const Version& version )
{
	mVersion = version;
}

template< typename Type >
const Version& TMarkupLangDeclaration< Type >::GetVersion( ) const
{
	return mVersion;
}

template< typename Type >
_void TMarkupLangDeclaration< Type >::SetEncoding( _ENCODING encoding )
{
	mEncodingType = encoding;
}

template< typename Type >
_ENCODING TMarkupLangDeclaration< Type >::GetEncoding( ) const
{
	return mEncodingType;
}

}