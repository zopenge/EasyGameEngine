//! @file     IDecoder.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IDecoder
//----------------------------------------------------------------------------

class IDecoder : public IObject
{
public:
	//!	Process buffer.
	//!	@param		size	The buffer size.
	//!	@param		buffer	The buffer data.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ProcessBuffer( _dword size, const _byte* buffer ) PURE;

	//!	Get the processed buffer data size.
	//!	@param		none.
	//!	@return		The processed buffer data size.
	virtual _dword GetProcessedBufferSize( ) const PURE;
	//!	Get the processed buffer data.
	//!	@param		none.
	//!	@return		The processed buffer data.
	virtual const _byte* GetProcessedBufferData( ) const PURE;
	//!	Get the processed stream reader.
	//!	@param		none.
	//!	@return		The processed stream reader.
	virtual IStreamReaderPassRef GetProcessedStreamReader( ) const PURE;
};

}