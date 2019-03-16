//! @file     INetworkOperation.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// INetworkOperation
//----------------------------------------------------------------------------

class INetworkOperation : public IActionRecord
{
public:
	//!	Get the operation type.
	//!	@param		none.
	//! @return		The operation type.
	virtual _NETWORK_OPERATION_TYPE GetType( ) const PURE;

	//!	Combine buffer.
	//!	@param		size	The buffer size in bytes.
	//!	@param		buffer	The buffer data.
	//!	@return		True indicates combine successful.
	virtual _ubool CombineBuffer( _dword size, const _byte* buffer ) PURE;

	//!	Remove the processing buffers.
	//!	@param		none.
	//!	@param		none.
	virtual _void RemoveProcessingBuffers( ) PURE;
};

}