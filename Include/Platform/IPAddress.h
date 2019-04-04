#pragma once

namespace EGE {

/// <summary>
/// The IP Address.
/// </summary>
class IPAddress {
public:
	static IPAddress cNull;

public:
	//! The address type
	enum _TYPE {
		_TYPE_TCP = 1,
		_TYPE_UDP = 2,
	};

public:
	// IP Address
	union {
		struct
		{
			_dword mIP;
		};

		struct
		{
			_byte mIP1;
			_byte mIP2;
			_byte mIP3;
			_byte mIP4;
		};
	};

	// Type and Port
	_word mType; // TCP/UDP
	_word mPort;

public:
	IPAddress()
	    : mIP(0), mType(0), mPort(0) {
	}

	IPAddress(_word type)
	    : mIP(0), mType(type), mPort(0) {
	}

	IPAddress(_dword ip, _word type, _word port)
	    : mIP(ip), mType(type), mPort(port) {
	}

public:
	//! Compare IP address.
	//! @param address  The address what you want to compare.
	//! @return True indicates both IP address is equal.
	inline _ubool operator==(const IPAddress& address) const {
		return mIP == address.mIP && mType == address.mType && mPort == address.mPort;
	}
	//! Compare IP address.
	//! @param address  The address what you want to compare.
	//! @return True indicates both IP address is not equal.
	inline _ubool operator!=(const IPAddress& address) const {
		return mIP != address.mIP || mType != address.mType || mPort != address.mPort;
	}

	//! Convert IP address to 64-bits value.
	//! @param none.
	//! @return The 64-bits value.
	inline operator _qword() const {
		return *(_qword*)this;
	}

	//! Check whether it's valid.
	//! @param none.
	//! @return True indicates it's valid.
	inline _ubool IsValid() const {
		return mIP != 0;
	}

public:
	//! Set address from string.
	//! @param string  The address string, use 192.168.1.1:8080" etc.
	//! @return The address referenced object.
	IPAddress& FromString(WStringPtr address);
	//! Convert IP address to ANSI string.
	//! @param with_port True indicates with port number.
	//! @return The IP address string.
	IPAddress ToStringA(_ubool with_port) const;
	//! Convert IP address to UTF-16 string.
	//! @param with_port True indicates with port number.
	//! @return The IP address string.
	IPAddress ToStringW(_ubool with_port) const;
};

} // namespace EGE