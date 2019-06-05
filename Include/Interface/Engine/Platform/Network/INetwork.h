#pragma once

namespace EGE {

/// <summary>
/// The network interface.
/// </summary>
class INetwork : public IObject {
public:
	//!	The network status
	enum class State {
		OFFLINE,
		VIA_LAN,
		VIA_MODEM,
		VIA_WWAN,
		VIA_WIFI,
	};

public:
	//!	Get the network state.
	//!	@param		none.
	//! @return		The network state.
	virtual State GetState() const PURE;

	//!	Get MAC address.
	//!	@param		mac_address		The MAC address.
	//! @return		True indicates success false indicates failure.
	virtual _ubool GetMACAddress(WString& mac_address) const PURE;
	//!	Get network card name.
	//!	@param		name			The network card name.
	//! @return		True indicates success false indicates failure.
	virtual _ubool GetNetworkCardName(WString& name) const PURE;

	//!	Get local IP addresses.
	//!	@param		none.
	//!	@return		The IP addresses.
	virtual Array<IPAddress> GetLocalIPAddresses() const PURE;
	//!	Get remote IP address.
	//!	@param		url	The url address.
	//!	@return		The IP address.
	virtual IPAddress GetRemoteIPAddress(WStringPtr url) const PURE;
};

} // namespace EGE