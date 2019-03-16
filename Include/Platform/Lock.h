//! @file     Lock.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// Lock
//----------------------------------------------------------------------------

//! This class represents a critical section object, used for threads
//! synchronization in a process.
class Lock {
 private:
  //! The critical section object handle.
  _handle mSectionHandle;

 public:
  //! Constructor, create a critical section and initialize it.
  //! @param		none
  Lock() {
    mSectionHandle = Platform::InitializeCriticalSection();
    EGE_ASSERT(mSectionHandle != _null);
  }
  Lock(const Lock&) {
    mSectionHandle = Platform::InitializeCriticalSection();
    EGE_ASSERT(mSectionHandle != _null);
  }

  //! Destructor, delete the critical section.
  //! @param		none
  ~Lock() { Platform::DeleteCriticalSection(mSectionHandle); }

 public:
  const Lock& operator=(const Lock&) {
    // Do nothing at all, just keep the handle for critical section
    return *this;
  }

  //! Waits for ownership of the critical section, returns when the calling
  //! thread is granted ownership.
  //! @param		none
  _void Enter() const {
#ifdef _DEBUG
    _dword lock_time = 0;
    if (Platform::IsMainThread()) lock_time = Platform::GetCurrentTickCount();
#endif

    Platform::EnterCriticalSection(mSectionHandle);

#ifdef _DEBUG
    if (lock_time != 0) {
      _dword tickcount = Platform::GetCurrentTickCount();
      _dword elapse = tickcount - lock_time;
      EGE_ASSERT(elapse <= 500);
    }
#endif
  }

  //! Releases ownership of the critical section.
  //! @param		none
  _void Leave() const { Platform::LeaveCriticalSection(mSectionHandle); }
};

//----------------------------------------------------------------------------
// LockOwner
//----------------------------------------------------------------------------

//! This class maintain the ownership of a critical section object, it will
//! obtain & release ownership in constructor & destructor.
class LockOwner {
  NO_COPY_OPERATIONS(LockOwner);

 private:
  //! The critical section object that maintains.
  const Lock& mLock;

 public:
  //! Constructor, obtain ownership of the critical section.
  //! @param		lock		The lock to be owned.
  LockOwner(const Lock& lock) : mLock(lock) { mLock.Enter(); }
  //! Destructor, release ownership of the critical section.
  //! @param		none
  ~LockOwner() { mLock.Leave(); }
};

}  // namespace EGE