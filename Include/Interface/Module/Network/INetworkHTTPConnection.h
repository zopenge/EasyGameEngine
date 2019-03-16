//! @file     INetworkHTTPConnection.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// INetworkHTTPConnection
//----------------------------------------------------------------------------

class INetworkHTTPConnection : public INetworkConnection
{
public:
	//!	Set the SSL key from file.
	//!	@param		filename		The file name.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetSSLKeyFromFile( WStringPtr filename ) PURE;
	//!	Set the SSL certificate from file.
	//!	@param		filename		The file name.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetSSLCertFromFile( WStringPtr filename ) PURE;
	//!	Set the SSL key from stream.
	//!	@param		stream_reader	The stream reader.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetSSLKeyFromStream( IStreamReader* stream_reader ) PURE;
	//!	Set the SSL certificate from stream.
	//!	@param		stream_reader	The stream reader.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetSSLCertFromStream( IStreamReader* stream_reader ) PURE;

	//!	Set the CA certificate from file.
	//!	@param		filename		The file name.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetCACertFromFile( WStringPtr filename ) PURE;
	//!	Set the CA certificate from stream.
	//!	@param		stream_reader	The stream reader.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetCACertFromStream( IStreamReader* stream_reader ) PURE;

	//!	Get.
	//!	@param		url_name		The sub url name.
	//!	@param		data_field		The data field string.
	//!	@param		parameters	The user defined parameters.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Get( AStringPtr url_name, AStringPtr data_field, const QwordParameters4& parameters = QwordParameters4::cNull ) PURE;
	//!	Get with user defined HTTP header list.
	//!	@param		url_name		The sub url name.
	//!	@param		header_list		The HTTP header list.
	//!	@param		data_field		The data field string.
	//!	@param		parameters	The user defined parameters.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Get( AStringPtr url_name, const AStringArray& header_list, AStringPtr data_field, const QwordParameters4& parameters = QwordParameters4::cNull ) PURE;
	//!	Get with no body request.
	//!	@param		url_name		The sub url name.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetWithNoBody( AStringPtr url_name ) PURE;

	//!	Post.
	//!	@param		url_name		The sub url name.
	//!	@param		data_field		The post field string.
	//!	@param		parameters		The user defined parameters.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Post( AStringPtr url_name, AStringPtr data_field, const QwordParameters4& parameters = QwordParameters4::cNull ) PURE;
	//!	Post with user defined HTTP header list.
	//!	@param		url_name		The sub url name.
	//!	@param		header_list		The HTTP header list.
	//!	@param		data_field		The post field string.
	//!	@param		parameters		The user defined parameters.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Post( AStringPtr url_name, const AStringArray& header_list, AStringPtr data_field, const QwordParameters4& parameters = QwordParameters4::cNull ) PURE;
	//!	Post.
	//!	@param		url_name		The sub url name.
	//!	@param		buffer			The buffer data.
	//!	@param		size			The buffer size.
	//!	@param		parameters		The user defined parameters.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Post( AStringPtr url_name, const _byte* buffer, _dword size, const QwordParameters4& parameters = QwordParameters4::cNull ) PURE;
	//!	Post with user defined HTTP header list.
	//!	@param		url_name		The sub url name.
	//!	@param		header_list		The HTTP header list.
	//!	@param		buffer			The buffer data.
	//!	@param		size			The buffer size.
	//!	@param		parameters		The user defined parameters.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Post( AStringPtr url_name, const AStringArray& header_list, const _byte* buffer, _dword size, const QwordParameters4& parameters = QwordParameters4::cNull ) PURE;
};

}