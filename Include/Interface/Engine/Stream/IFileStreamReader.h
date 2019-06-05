#pragma once

namespace EGE {

/// <summary>
/// The file stream reader interface.
/// </summary>
class IFileStreamReader : public IStreamReader {
public:
	//!	Get the file name.
	//!	@param		none.
	//!	@return		The file name.
	virtual WStringPtr GetFileName() const PURE;
};

} // namespace EGE