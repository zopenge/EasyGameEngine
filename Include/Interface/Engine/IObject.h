#pragma once

namespace EGE {

/// <summary>
/// The base object interafce.
/// </summary>
class IObject {
public:
	//!	Clone self and all sub-items.
	//!	@param		standalone	True indicates create in standalone mode.
	//!	@return		The new object.
	virtual IObject* CloneTo(_ubool standalone = _false) const PURE;

	//!	Update.
	//! @param		elapse		The millisecond time of the update interval.
	//! @return		none.
	virtual _void Tick(_dword elapse) PURE;

	//!	Delete without garbage collector.
	//!	@param		none.
	//!	@return		none.
	virtual _void DeleteThis() PURE;
	//!	Uninitialize.
	//!	@remark		We should it to unload some resources before delete.
	//!	@param		none.
	//!	@return		none.
	virtual _void Uninitialize() PURE;

	//!	Get the reference count.
	//!	@param		none.
	//!	@return		The reference count.
	virtual _dword GetRefCount() const PURE;
	//!	Increments the reference count for an interface on an object. This method should be called for every new copy of a pointer to an interface on an object.
	//!	@param		none.
	//!	@return		The new reference count. This value is intended to be used only for test purposes.
	virtual _dword AddRef() PURE;
	//!	Decrements the reference count for an interface on an object.
	//!	@param		none.
	//!	@return		The new reference count. This value is intended to be used only for test purposes.
	virtual _dword Release() PURE;

public:
	//!	Clone self and all sub-items as pass referenced pointer.
	//!	@param		standalone	True indicates create in standalone mode.
	//!	@return		The new object as pass referenced pointer.
	template <typename Type>
	PassRefPtr<Type> CloneToPassRef(_ubool standalone = _false) const {
		Type* object = (Type*)CloneTo(standalone);
		return object;
	}
};

} // namespace EGE