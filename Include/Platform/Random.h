#pragma once

namespace EGE {

/// <summary>
/// This class provides random value generation functions.
/// </summary>
class Random {
public:
	Random();
	~Random();

public:
	//! Sets a random starting point.
	//! @param seed  Seed for random-number generation.
	static _void SetGlobalSeed(_dword seed);

	//! Generates a pseudorandom number.
	//! @param none
	//! @return A pseudorandom number.
	static _dword Gen();
	//! Generates a pseudorandom number.
	//! @remark  [0, maxvalue] range.
	//! @param maxvalue The limitation of the random number.
	//! @return A pseudorandom number, from zero to maxvalue.
	static _dword Gen(_dword maxvalue);
	//! Generates a pseudorandom number.
	//! @remark  [minvalue, maxvalue] range.
	//! @param minvalue The limitation of the random number.
	//! @param maxvalue The limitation of the random number.
	//! @return A pseudorandom number, from minvalue to maxvalue.
	static _dword Gen(_dword minvalue, _dword maxvalue);
	//! Generates a pseudorandom number.
	//! @remark  [bounds.mMinValue, bounds.mMaxValue] range.
	//! @param bounds  The value range bounds.
	//! @return A pseudorandom number, from minvalue to maxvalue.
	static _dword Gen(const DwordRange& bounds);
	//! Generates a pseudorandom number.
	//! @remark  [minvalue, maxvalue] range.
	//! @param minvalue The limitation of the random number.
	//! @param maxvalue The limitation of the random number.
	//! @return A pseudorandom number, from minvalue to maxvalue.
	static _float Gen(_float minvalue, _float maxvalue);
	//! Generates a pseudorandom number.
	//! @remark  [bounds.mMinValue, bounds.mMaxValue] range.
	//! @param bounds  The value range bounds.
	//! @return A pseudorandom number, from minvalue to maxvalue.
	static _float Gen(const FloatRange& bounds);
	//! Generates a pseudorandom number.
	//! @remark  [minvalue, maxvalue] range.
	//! @param minvalue The limitation of the random number.
	//! @param maxvalue The limitation of the random number.
	//! @return A pseudorandom number, from minvalue to maxvalue.
	static _double Gen(_double minvalue, _double maxvalue);

	//! Generates a random sign, -1 or 1.
	//! @param none
	//! @return A random sign, -1 or 1.
	static _int GenSign();
	//! Generates a pseudorandom number by system time (UTC).
	//! @param none
	//! @return A pseudorandom number.
	static _dword GenByUTC();

	//! Generates a pseudorandom number.
	//! @param expectation The expectation.
	//! @param variance The variance.
	//! @return A pseudorandom number.
	static _double GenNormalDistributionValue(_double expectation = 0.0f, _double variance = 1.0f);
	//! Generates a pseudorandom number.
	//! @param expectation The expectation.
	//! @param variance The variance.
	//! @param minvalue The limitation of the random number.
	//! @param maxvalue The limitation of the random number.
	//! @return A pseudorandom number.
	static _double GenNormalDistributionValue(_double min_value, _double max_value, _double expectation, _double variance);
};

/// <summary>
/// Linear Congruential Generator
/// </summary>
class LCGRandom {
private:
	_dword mSeed;

public:
	LCGRandom();
	~LCGRandom();

public:
	//! Sets a random starting point.
	//! @param seed  Seed for random-number generation.
	_void SetSeed(_dword seed);

	//! Generates a pseudorandom number.
	//! @param none
	//! @return A pseudorandom number.
	_dword Gen();
	//! Generates a pseudorandom number.
	//! @remark  [0, maxvalue] range.
	//! @param maxvalue The limitation of the random number.
	//! @return A pseudorandom number, from zero to maxvalue.
	_dword Gen(_dword maxvalue);
	//! Generates a pseudorandom number.
	//! @remark  [minvalue, maxvalue] range.
	//! @param minvalue The limitation of the random number.
	//! @param maxvalue The limitation of the random number.
	//! @return A pseudorandom number, from minvalue to maxvalue.
	_dword Gen(_dword minvalue, _dword maxvalue);
	//! Generates a pseudorandom number.
	//! @remark  [bounds.mMinValue, bounds.mMaxValue] range.
	//! @param bounds  The value range bounds.
	//! @return A pseudorandom number, from minvalue to maxvalue.
	_dword Gen(const DwordRange& bounds);
	//! Generates a pseudorandom number.
	//! @remark  [minvalue, maxvalue] range.
	//! @param minvalue The limitation of the random number.
	//! @param maxvalue The limitation of the random number.
	//! @return A pseudorandom number, from minvalue to maxvalue.
	_float Gen(_float minvalue, _float maxvalue);
	//! Generates a pseudorandom number.
	//! @remark  [bounds.mMinValue, bounds.mMaxValue] range.
	//! @param bounds  The value range bounds.
	//! @return A pseudorandom number, from minvalue to maxvalue.
	_float Gen(const FloatRange& bounds);
	//! Generates a pseudorandom number.
	//! @remark  [minvalue, maxvalue] range.
	//! @param minvalue The limitation of the random number.
	//! @param maxvalue The limitation of the random number.
	//! @return A pseudorandom number, from minvalue to maxvalue.
	_double Gen(_double minvalue, _double maxvalue);

	//! Generates a random sign, -1 or 1.
	//! @param none
	//! @return A random sign, -1 or 1.
	_int GenSign();
};

} // namespace EGE