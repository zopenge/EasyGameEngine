//! @file     INetworkRemoteLogger.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// INetworkRemoteLogger
//----------------------------------------------------------------------------

class INetworkRemoteLogger : public IEnable< IFlagsObject< ILogger > >
{
public:
	//!	The flags
	enum _FLAG
	{
		_FLAG_USE_ZLIB_COMPRESSION		= 1 << 0, //! Use zlib to compress data
		_FLAG_DISABLE_COMBINATION		= 1 << 1, //! Disable combination
		_FLAG_SEND_WITH_FRAME_NUMBER	= 1 << 2, //! Send log with frame nunber
	};

public:
	//!	Connect to remote server.
	//!	@param		remote_address	The remote address.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool Connect( WStringPtr remote_address ) PURE;

	//!	Set the max send size in bytes.
	//!	@param		size	The max size in bytes, -1 indicates unlimited.
	//!	@return		none.
	virtual _void SetMaxSendSize( _dword size ) PURE;
	//!	Get the max send size in bytes.
	//!	@param		none.
	//!	@return		The max size in bytes.
	virtual _dword GetMaxSendSize( ) const PURE;

	//!	Stop.
	//!	@param		none.
	//!	@return		none.
	virtual _void Stop( ) PURE;

	//!	Set FPS.
	//!	@param		fps		The fps.
	//!	@return		none.
	virtual _void SetFPS( _float fps ) PURE;
	//!	Set memory usage.
	//!	@param		cur_mem_size	The current memory usage size.
	//!	@param		total_mem_size	The total memory size.
	//!	@return		none.
	virtual _void SetMemSize( _dword cur_mem_size, _dword total_mem_size ) PURE;
	//!	Set GPU memory usage.
	//!	@param		cur_mem_size	The current memory usage size.
	//!	@param		total_mem_size	The total memory size.
	//!	@return		none.
	virtual _void SetGPUMemSize( _dword cur_mem_size, _dword total_mem_size ) PURE;
};

}