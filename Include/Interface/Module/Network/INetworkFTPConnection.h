//! @file     INetworkFTPConnection.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// INetworkFTPConnectionNotifier
//----------------------------------------------------------------------------

class INetworkFTPConnectionNotifier : public IObject
{
public:
	//!	When upload file completed.
	//!	@param		local_filename	The local absolute file name.
	//!	@param		remote_filename	The remote relative file name.
	//!	@return		none.
	virtual _void OnUploadFileCompleted( WStringPtr local_filename, WStringPtr remote_filename ) PURE;
};

//----------------------------------------------------------------------------
// INetworkFTPConnection
//----------------------------------------------------------------------------

class INetworkFTPConnection : public INetworkConnection
{
public:
	//!	Set the FTP notifier.
	//!	@param		notifier	The FTP notifier.
	//! @return		none.
	virtual _void SetFTPNotifier( INetworkFTPConnectionNotifier* notifier ) PURE;
	//!	Get the FTP notifier.
	//!	@param		none.
	//! @return		The FTP notifier.
	virtual INetworkFTPConnectionNotifier* GetFTPNotifier( ) PURE;

	//!	Set the user name.
	//!	@param		username	The user name.
	//! @return		none.
	virtual _void SetUserName( AStringPtr username ) PURE;
	//!	Set the password.
	//!	@param		password	The password.
	//! @return		none.
	virtual _void SetPassword( AStringPtr password ) PURE;

	//!	Upload file.
	//!	@param		local_filename	The local absolute file name.
	//!	@param		remote_filename	The remote relative file name.
	//!	@param		parameters		The user defined parameters.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool UploadFile( WStringPtr local_filename, WStringPtr remote_filename, const QwordParameters4& parameters = QwordParameters4::cNull ) PURE;
};

}