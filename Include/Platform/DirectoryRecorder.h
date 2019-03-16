//! @file     DirectoryRecorder.h
//! @author   LiCode
//! @version  1.1.1.804
//! @date     2011/03/10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// DirectoryRecorder
//----------------------------------------------------------------------------

//! This class represents a directory recorder, used for reset current directory
//! as an old one.
class DirectoryRecorder {
 private:
  //! The old directory, used for set back as current one.
  WString mOldDirectory;

 public:
  //! Constructor, create a directory recorder, save the current directory path.
  //! @param pathname  The path name of new current
  //! directory.
  DirectoryRecorder(WStringPtr directory);
  //! Destructor, set back current directory.
  //! @param none
  ~DirectoryRecorder();
};

}  // namespace EGE
