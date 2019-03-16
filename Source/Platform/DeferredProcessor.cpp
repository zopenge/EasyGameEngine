//! @file     DeferredProcessor.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// DeferredProcessor Implementation
//----------------------------------------------------------------------------

DeferredProcessor::DeferredProcessor( )
{
 Clear( );
}

DeferredProcessor::~DeferredProcessor( )
{

}

_void DeferredProcessor::SetIntervalTime( _dword interval )
{
 mIntervalTime = interval;
}

_void DeferredProcessor::SetFirstDelayTime( _dword delay )
{
 mFirstDelayTime = delay;
}

_void DeferredProcessor::Clear( )
{
 mStatus   = _STATUS_UNKONWN;
 mIntervalTime = -1;
 mFirstDelayTime = -1; 

 mPrevTickcount = 0;
}

_void DeferredProcessor::Reset( )
{
 mStatus = _STATUS_UNKONWN;
}

_ubool DeferredProcessor::Update( )
{
 switch ( mStatus )
 {
  case _STATUS_UNKONWN:
  {
   mStatus   = _STATUS_FIRST_MESSAGE;
   mPrevTickcount = Platform::GetCurrentTickCount( );
  }
  break;

  case _STATUS_FIRST_MESSAGE:
  {
   _dword tickcount = Platform::GetCurrentTickCount( );

   if ( mFirstDelayTime != -1 )
   {
    _dword elapsed_time = tickcount - mPrevTickcount;

    // We are in the first delay range
    if ( mFirstDelayTime > elapsed_time )
     return _false;
   }

   mStatus   = _STATUS_IN_INTERVAL_RANGE;
   mPrevTickcount = tickcount;
  }
  break;

  case _STATUS_IN_INTERVAL_RANGE:
  {
   if ( mIntervalTime != -1 )
   {
    _dword tickcount = Platform::GetCurrentTickCount( );
    _dword elapsed_time = tickcount - mPrevTickcount;

    // Check the interval time
    if ( mIntervalTime > elapsed_time )
     return _false;

    // Process it
    mPrevTickcount = tickcount;
   }
  }
  break;
 }

 return _true;
}
