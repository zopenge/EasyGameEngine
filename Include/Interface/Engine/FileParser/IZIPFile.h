#pragma once

namespace EGE {

/// <summary>
/// The ZIP file interface.
/// </summary>
class IZIPFile : public IObject {
public:
	/// <summary>
	/// When walk item.
	/// </summary>
	typedef _ubool (*OnWalkItem)(WStringPtr filename);

public:
	//!	Get the Compression ratio.
	//!	@param		none.
	//!	@return		The compression ratio in [0.0, 1.0].
	virtual _float GetCompressionRatio() const PURE;

	//!	Add file.
	//!	@param		filename	The relative file name in ZIP file.
	//!	@param		stream		The stream reader.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool AddFile(WStringPtr filename, IStreamReader* stream) PURE;
	//!	Check whether has file or not.
	//!	@param		filename	The relative file name in ZIP file.
	//!	@return		True indicates has file.
	virtual _ubool HasFile(WStringPtr filename) const PURE;
	//!	Get file stream.
	//!	@param		filename		The relative file name in ZIP file.
	//!	@return		The file stream.
	virtual IStreamReaderPassRef GetFile(WStringPtr filename) PURE;

	//!	Traverse all items.
	//!	@param		callback	The walk item callback function.
	//!	@return		none.
	virtual _void TraverseItems(OnWalkItem callback, const QwordParams2& params) const PURE;
};

} // namespace EGE