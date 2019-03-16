//! @file     IResLoaderFactory.h
//! @author   LiCode
//! @version  
//! @date     2012/05/15
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IResLoaderFactory
//----------------------------------------------------------------------------

class IResLoaderFactory : public IObject
{
public:
	//!	Check whether it's HTTP/HTTPs protocol.
	virtual _ubool IsHTTPProtocol( WStringPtr url ) const PURE;
	//!	Get the HTTP URL.
	virtual WStringR GetHTTPURL( WStringPtr url ) const PURE;

	//!	Create HTTP archive.
	//!	@param		remote_path		The remote path.
	//!	@param		use_whole_path	True indicates use the whole path to access/load resource.
	//!	@return		The archive interface.
	virtual IArchivePassRef CreateHTTPArchive( WStringPtr remote_path, _ubool use_whole_path ) PURE;
};

}