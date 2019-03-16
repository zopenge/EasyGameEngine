//! @file     _networkRequest.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _networkRequest
//----------------------------------------------------------------------------

//class _networkRequest : public FlagsObject
//{
//public:
//	enum _FLAG
//	{
//		//!	Indicates no receive any data from server
//		_FLAG_NO_RECV_DATA	= 1 << 0,
//		//!	Indicates abort operation
//		_FLAG_ABORT			= 1 << 1,
//	};
//
//private:
//	AString					mURLName;
//	INetworkConnection*		mConnection;
//	MemArrayPtr< _byte >	mFieldBuffer;
//	IStreamWriterRef		mRecvBuffer;
//	QwordParameters4		mParameters;
//
//	_ubool IsAbort( ) const
//	{
//		return HasFlags( _FLAG_ABORT );
//	}
//
//	BaseInfo( )
//	{
//		mType			= _TYPE_UNKNOWN;
//		mHTTPConnection = _null;
//		mParameters		= QwordParameters4::cNull;
//	}
//};

}