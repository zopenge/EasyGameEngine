#pragma once

namespace EGE {

/// <summary>
/// The stream processor notifier.
/// </summary>
class IStreamProcessorNotifier : public IObject {
public:
	//!	When processing.
	//!	@param		total_size		The total size in bytes what to process.
	//!	@param		offset			The offset in bytes what is being processed.
	//!	@param		processed_size	The size in bytes what is being processed.
	//!	@return		none.
	virtual _void OnProcessing(_dword total_size, _dword offset, _dword processed_size) PURE;
};

/// <summary>
/// The stream processor interface.
/// </summary>
class IStreamProcessor : public IObject {
public:
	//!	Set the notifier.
	//!	@param		notifier	The notifier.
	//! @return		none.
	virtual _void SetNotifier(IStreamProcessorNotifier* notifier) PURE;
	//!	Get the notifier.
	//!	@param		none.
	//! @return		The notifier.
	virtual IStreamProcessorNotifier* GetNotifier() PURE;

	//!	Process stream in specified chunk size.
	//!	@param		buffer			The buffer data ( source ).
	//!	@param		size			The size in bytes of reader.
	//!	@param		stream_writer	The stream writer ( target ).
	//!	@param		chunk_size		The each chunk size in bytes to be processed.
	//! @return		The written bytes of stream writer, -1 indicates failure.
	virtual _dword Process(const _byte* buffer, _dword size, IStreamWriter* stream_writer, _dword chunk_size) PURE;
};

} // namespace EGE