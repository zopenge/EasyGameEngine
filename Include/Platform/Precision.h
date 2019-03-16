//! @file     Precision.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// Precision
//----------------------------------------------------------------------------

class Precision {
 private:
  _word mIntPrecision;
  _word mFloatPrecision;

 public:
  Precision();
  Precision(_word int_precision, _word float_precision);

 public:
  EGE_GET_ACCESSOR(_word, IntPrecision)
  EGE_GET_ACCESSOR(_word, FloatPrecision)
  EGE_GET_ACCESSOR_CONST(_word, IntPrecision)
  EGE_GET_ACCESSOR_CONST(_word, FloatPrecision)

 public:
  _void Clear();

  _void EnableIntergerPrecision(_ubool enable, _word precision);
  _void EnableFloatPrecision(_ubool enable, _word precision);

  _ubool IsEnableIntergerPrecision() const;
  _ubool IsEnableFloatPrecision() const;

  WString BuildIntergerValueString(_int value) const;
  WString BuildFloatValueString(_float value) const;
};

//----------------------------------------------------------------------------
// Precision Implementation
//----------------------------------------------------------------------------

}  // namespace EGE