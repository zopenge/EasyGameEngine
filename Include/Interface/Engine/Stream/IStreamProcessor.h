//! @file     IStreamProcessor.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IStreamProcessorNotifier
//----------------------------------------------------------------------------

class IStreamProcessorNotifier : public IObject
{
public:
	//!	When processing.
	//!	@param		total_size		The total size in bytes what to process.
	//!	@param		offset			The offset in bytes what is being processed.
	//!	@param		processed_size	The size in bytes what is being processed.
	//!	@return		none.
	virtual _void OnProcessing( _dword total_size, _dword offset, _dword processed_size ) PURE;
};

//----------------------------------------------------------------------------
// IStreamProcessor
//----------------------------------------------------------------------------

class IStreamProcessor : public IObject
{
public:
	//!	Set the notifier.
	//!	@param		notifier	The notifier.
	//! @return		none.
	virtual _void SetNotifier( IStreamProcessorNotifier* notifier ) PURE;
	//!	Get the notifier.
	//!	@param		none.
	//! @return		The notifier.
	virtual IStreamProcessorNotifier* GetNotifier( ) PURE;

	//!	Process stream in specified chunk size.
	//!	@param		buffer			The buffer data ( source ).
	//!	@param		size			The size in bytes of reader.
	//!	@param		stream_writer	The stream writer ( target ).
	//!	@param		chunk_size		The each chunk size in bytes to be processed.
	//!	@param		output_size		The output buffer size.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Process( const _byte* buffer, _dword size, IStreamWriter* stream_writer, _dword chunk_size, _dword& output_size ) PURE;
	//!	Process stream in specified chunk size.
	//!	@param		stream_reader	The stream reader ( source ).
	//!	@param		size			The size in bytes of reader.
	//!	@param		stream_writer	The stream writer ( target ).
	//!	@param		chunk_size		The each chunk size in bytes to be processed.
	//!	@param		output_size		The output buffer size.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Process( IStreamReader* stream_reader, _dword size, IStreamWriter* stream_writer, _dword chunk_size, _dword& output_size ) PURE;
};

}