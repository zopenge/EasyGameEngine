//! @file     IBitStreamReader.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IBitStreamReader
//----------------------------------------------------------------------------

class IBitStreamReader : public IBitStream< IStreamReader >
{
public:
	//!	Read the buffer data.
	//!	@param		buffer			The buffer data.
	//!	@param		bitsnumber		The total bits number.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadBitsStream( _void* buffer, _dword bitsnumber ) PURE;
	//!	Read bits stream.
	//!	@param		value			The value.
	//!	@param		bitsnumber		The total bits number.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadBitsStream( _tiny& value, _dword bitsnumber ) PURE;
	//!	Read bits stream.
	//!	@param		value			The value.
	//!	@param		bitsnumber		The total bits number.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadBitsStream( _byte& value, _dword bitsnumber ) PURE;
	//!	Read bits stream.
	//!	@param		value			The value.
	//!	@param		bitsnumber		The total bits number.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadBitsStream( _word& value, _dword bitsnumber ) PURE;
	//!	Read bits stream.
	//!	@param		value			The value.
	//!	@param		bitsnumber		The total bits number.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadBitsStream( _short& value, _dword bitsnumber ) PURE;
	//!	Read bits stream.
	//!	@param		value			The value.
	//!	@param		bitsnumber		The total bits number.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadBitsStream( _int& value, _dword bitsnumber ) PURE;
	//!	Read bits stream.
	//!	@param		value			The value.
	//!	@param		bitsnumber		The total bits number.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadBitsStream( _dword& value, _dword bitsnumber ) PURE;
	//!	Read bits stream.
	//!	@param		value			The value.
	//!	@param		bitsnumber		The total bits number.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadBitsStream( _qword& value, _dword bitsnumber ) PURE;
	//!	Read bits stream.
	//!	@param		value			The value.
	//!	@param		bitsnumber		The total bits number.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadBitsStream( _float& value, _dword bitsnumber ) PURE;
	//!	Read bits stream.
	//!	@param		value			The value.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReadBitsStream( _double& value ) PURE;
};

}