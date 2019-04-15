#pragma once

namespace EGE {

/// <summary>
/// The base event data.
/// </summary>
struct BaseEventData {
};

/// <summary>
/// The observable object.
/// </summary>
class IObservable : public IObject {
public:
	//!	Register observer.
	//!	@param		observer	The observer.
	//!	@return		none.
	virtual _void RegisterObserver(IObserver* observer) PURE;
	//!	Unregister observer.
	//!	@param		observer	The observer.
	//!	@return		none.
	virtual _void UnregisterObserver(IObserver* observer) PURE;

	//!	Notify all observers.
	//!	@param		generator	The event generator.
	//!	@param		event		The event info.
	//!	@return		none.
	virtual _void NotifyObservers(const IObservable* generator, const BaseEventData& event) PURE;
};

} // namespace EGE