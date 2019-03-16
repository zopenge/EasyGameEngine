//! @file     GenericID.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GenericID
//----------------------------------------------------------------------------

template< typename Type, _dword _UNIQUE_ID >
class GenericID
{
private:
	Type mID;

public:
	GenericID( );
	GenericID( const Type& id );

public:
	GenericID& operator = ( const Type& id );

	GenericID& operator ++ ( );

	_ubool operator < ( const GenericID& id ) const;
	_ubool operator > ( const GenericID& id ) const;
	_ubool operator != ( const GenericID& id ) const;
	_ubool operator == ( const GenericID& id ) const;
	_ubool operator <= ( const GenericID& id ) const;
	_ubool operator >= ( const GenericID& id ) const;
};

//----------------------------------------------------------------------------
// GenericID Implementation
//----------------------------------------------------------------------------

template< typename Type, _dword _UNIQUE_ID >
GenericID< Type, _UNIQUE_ID >::GenericID( ) : mID( 0 )
{
}

template< typename Type, _dword _UNIQUE_ID >
GenericID< Type, _UNIQUE_ID >::GenericID( const Type& id ) : mID( id )
{
}

template< typename Type, _dword _UNIQUE_ID >
GenericID< Type, _UNIQUE_ID >& GenericID< Type, _UNIQUE_ID >::operator = ( const Type& id )
{
	mID = id;

	return *this;
}

template< typename Type, _dword _UNIQUE_ID >
GenericID< Type, _UNIQUE_ID >& GenericID< Type, _UNIQUE_ID >::operator ++ ( )
{
	mID ++;

	return *this;
}

template< typename Type, _dword _UNIQUE_ID >
_ubool GenericID< Type, _UNIQUE_ID >::operator < ( const GenericID& id ) const
{
	return mID < id.mID;
}

template< typename Type, _dword _UNIQUE_ID >
_ubool GenericID< Type, _UNIQUE_ID >::operator > ( const GenericID& id ) const
{
	return mID > id.mID;
}

template< typename Type, _dword _UNIQUE_ID >
_ubool GenericID< Type, _UNIQUE_ID >::operator != ( const GenericID& id ) const
{
	return mID != id.mID;
}

template< typename Type, _dword _UNIQUE_ID >
_ubool GenericID< Type, _UNIQUE_ID >::operator == ( const GenericID& id ) const
{
	return mID == id.mID;
}

template< typename Type, _dword _UNIQUE_ID >
_ubool GenericID< Type, _UNIQUE_ID >::operator <= ( const GenericID& id ) const
{
	return mID <= id.mID;
}

template< typename Type, _dword _UNIQUE_ID >
_ubool GenericID< Type, _UNIQUE_ID >::operator >= ( const GenericID& id ) const
{
	return mID >= id.mID;
}

}