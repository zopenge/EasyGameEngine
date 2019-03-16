//! @file     _curlDataList.cpp
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#include "EGENetwork.h"

#if (_USE_CRUL_SDK == 1)

//----------------------------------------------------------------------------
// _curlDataList Implementation
//----------------------------------------------------------------------------

_curlDataList::_curlDataList( )
{
	mURLList = _null;
}

_curlDataList::~_curlDataList( )
{
	if ( mURLList != _null )
		::curl_slist_free_all( mURLList );
}

_void _curlDataList::Append( AStringPtr string )
{
	mURLList = ::curl_slist_append( mURLList, string.Str( ) );  
}

_void _curlDataList::Append( AStringPtr type, AStringPtr value )
{
	return Append( FORMAT_ASTRING_2( "%s: %s", type.Str( ), value.Str( ) ) );
}

_void _curlDataList::Append( const AStringArray& string_list )
{
	for ( _dword i = 0; i < string_list.Number( ); i ++ )
		Append( string_list[i] );
}

#endif