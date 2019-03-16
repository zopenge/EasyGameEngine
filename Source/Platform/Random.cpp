//! @file     Random.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Random Implementation
//----------------------------------------------------------------------------

Random::Random( )
{

}

Random::~Random( )
{

}

_void Random::SetGlobalSeed( _dword seed )
{
 ::srand( seed );
}

_dword Random::Gen( )
{
 return rand( );
}

_dword Random::Gen( _dword maxvalue )
{
 if ( maxvalue == 0 )
  return 0;

 if( maxvalue == -1 )
  return Gen( );

 return Gen( ) % ( maxvalue + 1 );
}

_dword Random::Gen( _dword minvalue, _dword maxvalue )
{
 if ( maxvalue > minvalue )
  return Gen( maxvalue - minvalue ) + minvalue;
 else if ( maxvalue < minvalue )
  return Gen( minvalue - maxvalue ) + maxvalue;
 else
  return minvalue;
}

_dword Random::Gen( const DwordRange& bounds )
{
 return Gen( bounds.mMinValue, bounds.mMaxValue );
}

_float Random::Gen( _float minvalue, _float maxvalue )
{
 if ( maxvalue > minvalue )
  return Gen( 10000 ) * 0.0001f * ( maxvalue - minvalue ) + minvalue;
 else if ( maxvalue < minvalue )
  return Gen( 10000 ) * 0.0001f * ( minvalue - maxvalue ) + maxvalue;
 else
  return minvalue;
}

_float Random::Gen( const FloatRange& bounds )
{
 return Gen( bounds.mMinValue, bounds.mMaxValue );
}

_double Random::Gen( _double minvalue, _double maxvalue )
{
 if ( maxvalue > minvalue )
  return Gen( 10000 ) * 0.0001 * ( maxvalue - minvalue ) + minvalue;
 else if ( maxvalue < minvalue )
  return Gen( 10000 ) * 0.0001 * ( minvalue - maxvalue ) + maxvalue;
 else
  return minvalue;
}

_int Random::GenSign( )
{
 return Gen( 1 ) == 0 ? -1 : 1;
}

_dword Random::GenByUTC( )
{
 // Get the current system time for random seed
 CalendarTime systemtime;
 Platform::GetSystemTime( systemtime );

 // Convert system to file time
 FileTime filetime;
 Platform::SystemTimeToFileTime( filetime, systemtime );

 // Set the random seed by local time
 SetGlobalSeed( ( ( filetime.mLowDateTime & 0xFFFF ) + systemtime.mMilliseconds ) ^ systemtime.mMilliseconds );

 // Random it
 return Gen( );
}

_double Random::GenNormalDistributionValue( _double expectation, _double variance )
{
 _double rand1 = rand() / ((_double) RAND_MAX);
 if ( rand1 < 1e-100 ) rand1 = 1e-100;
 rand1 = -2.0 * log( rand1 );
 _double rand2 = (rand() / ((double) RAND_MAX)) * Math::c2Pi;

 return expectation + variance * sqrt( rand1 ) * cos( rand2 );
}

_double Random::GenNormalDistributionValue( _double min_value, _double max_value, _double e, _double v )
{
 _double random_value = 0.0f;
 do 
 {
  random_value = GenNormalDistributionValue( e, v );
 } while ( random_value < min_value || random_value > max_value );

 return random_value;
}

//////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// LCGRandom Implementation
//----------------------------------------------------------------------------

LCGRandom::LCGRandom( )
 : mSeed( 0 )
{

}

LCGRandom::~LCGRandom( )
{

}

_void LCGRandom::SetSeed( _dword seed )
{
 mSeed = seed;
 Gen( );
}

_dword LCGRandom::Gen( )
{
 mSeed = ( (_dword) 1103515245ul ) * mSeed + ( (_dword) 12345ul );
 return mSeed;
}

_dword LCGRandom::Gen( _dword maxvalue )
{
 if ( maxvalue == 0 )
  return 0;

 if ( maxvalue == -1 )
  return Gen( );

 return Gen( ) % ( maxvalue + 1 );
}

_dword LCGRandom::Gen( _dword minvalue, _dword maxvalue )
{
 if ( maxvalue > minvalue )
  return Gen( maxvalue - minvalue ) + minvalue;
 else if ( maxvalue < minvalue )
  return Gen( minvalue - maxvalue ) + maxvalue;
 else
  return minvalue;
}

_dword LCGRandom::Gen( const DwordRange& bounds )
{
 return Gen( bounds.mMinValue, bounds.mMaxValue );
}

_float LCGRandom::Gen( _float minvalue, _float maxvalue )
{
 if ( maxvalue > minvalue )
  return Gen( 10000 ) * 0.0001f * ( maxvalue - minvalue ) + minvalue;
 else if ( maxvalue < minvalue )
  return Gen( 10000 ) * 0.0001f * ( minvalue - maxvalue ) + maxvalue;
 else
  return minvalue;
}

_float LCGRandom::Gen( const FloatRange& bounds )
{
 return Gen( bounds.mMinValue, bounds.mMaxValue );
}

_double LCGRandom::Gen( _double minvalue, _double maxvalue )
{
 if ( maxvalue > minvalue )
  return Gen( 10000 ) * 0.0001 * ( maxvalue - minvalue ) + minvalue;
 else if ( maxvalue < minvalue )
  return Gen( 10000 ) * 0.0001 * ( minvalue - maxvalue ) + maxvalue;
 else
  return minvalue;
}

_int LCGRandom::GenSign( )
{
 return Gen( 1 ) == 0 ? -1 : 1;
}