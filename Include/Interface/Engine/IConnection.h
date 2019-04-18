#pragma once

namespace EGE {

/// <summary>
/// The connection what can observe.
/// </summary>
class IConnection : public IObservable {
public:
	//!	Get the connection state.
	//!	@param		none.
	//!	@return		The connection state.
	virtual ConnectionState GetState() const PURE;

	//!	Check whether it's connecting or not.
	//!	@param		none.
	//!	@return		True indicates it's connecting.
	virtual _ubool IsConnecting() const PURE;
	//!	Check whether has connected or not.
	//!	@param		none.
	//!	@return		True indicates had connected.
	virtual _ubool IsConnected() const PURE;
	//!	Check whether connection has lost or not.
	//!	@param		none.
	//!	@return		True indicates the connection has lost.
	virtual _ubool IsConnectionLost() const PURE;
};

} // namespace EGE