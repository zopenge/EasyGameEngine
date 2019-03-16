//! @file     _curlDataList.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _curlDataList
//----------------------------------------------------------------------------

class _curlDataList
{
	NO_COPY_OPERATIONS( _curlDataList )

private:
	curl_slist*	mURLList;

public:
	_curlDataList( );
	~_curlDataList( );

public:
	operator curl_slist* ( ) const
		{ return mURLList; }

public:
	_void Append( AStringPtr string );
	_void Append( AStringPtr type, AStringPtr value );
	_void Append( const AStringArray& string_list );
};

}