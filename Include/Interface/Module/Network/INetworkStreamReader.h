//! @file     INetworkStreamReader.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// INetworkStreamReaderNotifier
//----------------------------------------------------------------------------

class INetworkStreamReaderNotifier : public IObject
{
public:
	//!	When reading.
	//!	@param		read_size		The current read size in bytes.
	//!	@param		total_read_size	The total read size in bytes.
	//!	@return		none.
	virtual _void OnReading( _dword read_size, _dword total_read_size ) PURE;
};

//----------------------------------------------------------------------------
// INetworkStreamReader
//----------------------------------------------------------------------------

class INetworkStreamReader : public IStreamReader
{
public:
	//!	Set the notifier.
	//!	@param		notifier	The notifier.
	//! @return		none.
	virtual _void SetNotifier( INetworkStreamReaderNotifier* notifier ) PURE;
	//!	Get the notifier.
	//!	@param		none.
	//! @return		The notifier.
	virtual INetworkStreamReaderNotifier* GetNotifier( ) PURE;

	//!	Get the MIME content type.
	//!	@param		none.
	//!	@return		The MIME content type.
	virtual _NETWORK_MIME_CONTENT_TYPE GetMIMEContentType( ) const PURE;
};

}