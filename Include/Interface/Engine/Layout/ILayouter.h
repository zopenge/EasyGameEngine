#pragma once

namespace EGE {

/// <summary>
/// The layouter interface.
/// </summary>
class ILayouter: public IObject {
public:
	//!	Set margin size.
	//!	@param		size	The margin size will plus to all children.
	//!	@return.
	virtual _void SetMarginSize(const Vector2& size) PURE;
	//!	Get margin size.
	//!	@param		none.
	//!	@return		The margin size will plus to all children.
	virtual const Vector2& GetMarginSize() const PURE;

	//!	Align all children.
	//!	@param		type	The align type.
	//! @return		none.
	virtual _void Align(AlignType type) PURE;
};

} // namespace EGE