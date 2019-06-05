#pragma once

namespace EGE {

/// <summary>
/// The file stream writer interface.
/// </summary>
class IFileStreamWriter : public IStreamWriter {
public:
	//!	Get the file name.
	//!	@param		none.
	//!	@return		The file name.
	virtual WStringPtr GetFileName() const PURE;
};

} // namespace EGE