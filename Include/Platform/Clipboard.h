//! @file     Clipboard.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// Clipboard
//----------------------------------------------------------------------------

class Clipboard {
 public:
  //! Copy the string to clipboard.
  //! @param string		The string what will be copied.
  //! @return True indicates success false indicates failure.
  static _ubool Copy(WStringPtr string);

  //! Paste the string from clipboard.
  //! @param string		The string what will be pasted.
  //! @return True indicates success false indicates failure.
  static _ubool Paste(WString& string);
};

}  // namespace EGE