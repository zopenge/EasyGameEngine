#pragma once

namespace EGE {

/// <summary>
/// The (Portable Network Graphics, PNG) file.
/// </summary>
class IPNGFile : public IImageFile {
public:
	//!	Get the background color.
	//!	@param		none.
	//!	@return		The background color.
	virtual const Color& GetBackgroundColor() const PURE;
};

} // namespace EGE