#pragma once

namespace EGE {

/// <summary>
/// The value precision.
/// </summary>
class Precision {
private:
	_word mIntPrecision;
	_word mFloatPrecision;

public:
	Precision();
	Precision(_word int_precision, _word float_precision);

public:
	_void Clear();

	_void EnableIntergerPrecision(_ubool enable, _word precision);
	_void EnableFloatPrecision(_ubool enable, _word precision);

	_ubool IsEnableIntergerPrecision() const;
	_ubool IsEnableFloatPrecision() const;

	WString BuildIntergerValueString(_int value) const;
	WString BuildFloatValueString(_float value) const;
};

} // namespace EGE