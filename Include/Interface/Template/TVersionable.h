//! @file     TVersionable.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TVersionable
//----------------------------------------------------------------------------

template< typename Type >
class TVersionable : public Type
{
protected:
	Version	mVersion;

protected:
	TVersionable( );
	virtual ~TVersionable( );

// IVersion Interface
public:
	virtual _void			SetVersion( const Version& version ) override;
	virtual const Version&	GetVersion( ) const override;
};

//----------------------------------------------------------------------------
// TVersionable Implementation
//----------------------------------------------------------------------------

template< typename Type >
TVersionable< Type >::TVersionable( )
{
	mVersion = Version::cZero;
}

template< typename Type >
TVersionable< Type >::~TVersionable( )
{
}

template< typename Type >
_void TVersionable< Type >::SetVersion( const Version& version )
{
	mVersion = version;
}

template< typename Type >
const Version& TVersionable< Type >::GetVersion( ) const
{
	return mVersion;
}

}