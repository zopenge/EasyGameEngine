#pragma once

namespace EGE {

/// <summary>
/// The garbage collector object.
/// </summary>
class IGarbageCollector : public IObject {
public:
	//!	Release object.
	//!	@param		object		The object.
	//!	@return		none.
	virtual _void ReleaseObject(IObject* object) PURE;
};

} // namespace EGE