//! @file     chromePlatform.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform NACL Functions Implementation
//----------------------------------------------------------------------------

#ifdef NACL

extern "C"
{

// _strdup() function is not existing in NACL mode
char* _strdup(const char *str)
{
	size_t len;
	char *newstr;

	if(!str)
		return (char *)_null;

	len = strlen(str);

	if(len >= ((size_t)-1) / sizeof(char))
		return (char *)_null;

	newstr = (char*)malloc((len+1)*sizeof(char));
	if(!newstr)
		return (char *)_null;

	memcpy(newstr,str,(len+1)*sizeof(char));

	return newstr;
}

// ftime() function is not existing in NACL mode
int ftime( struct timeb *tbp )
{
	struct timezone tz;
	struct timeval t;

	if (gettimeofday(&t, &tz) < 0)
		return (-1);
	
	tbp->millitm = t.tv_usec / 1000;
	tbp->time = t.tv_sec;
	tbp->timezone = tz.tz_minuteswest;
	tbp->dstflag = tz.tz_dsttime;
	
	return (0);
}

}

#endif

//----------------------------------------------------------------------------
// Platform Implementation
//----------------------------------------------------------------------------

_ubool Platform::Initialize( )
{
	// Initialize platform
	if ( anyPlatform::Initialize( ) == _false )
		return _false;

	return _true;
}

_void Platform::Finalize( )
{
	// Finalize platform
	anyPlatform::Finalize( );
}
