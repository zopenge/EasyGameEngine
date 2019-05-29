#pragma once

namespace EGE {

/// <summary>
/// The filler.
/// </summary>
class IFiller : public IObject {
public:
	//!	Get the image size.
	//!	@param		none.
	//!	@return		The image size.
	virtual const PointU& GetSize() const PURE;
	//!	Get the area area size.
	//!	@param		none.
	//!	@return		The area size.
	virtual _dword GetAreaSize() const PURE;
	//!	Get the free area size.
	//!	@param		none.
	//!	@return		The free area size.
	virtual _dword GetFreeAreaSize() const PURE;

	//!	Set the space.
	//!	@param		space	The space in pixel between images.
	//!	@return		none.
	virtual _void SetSpace(const PointU& space) PURE;
	//!	Get the space.
	//!	@param		none.
	//!	@return		The space in pixel between images.
	virtual const PointU& GetSpace() const PURE;

	//!	Clear all items.
	//!	@param		none.
	//! @return		none.
	virtual _void ClearAllItems() PURE;
	//!	Add item.
	//!	@param		size	The image size.
	//!	@param		rect	The image region in filler.
	//! @return		The item index.
	virtual _dword AddItem(const PointU& size, RectU& rect) PURE;
	//!	Free item.
	//!	@param		item	The item index.
	//! @return		none.
	virtual _void FreeItem(_dword index) PURE;
};

} // namespace EGE