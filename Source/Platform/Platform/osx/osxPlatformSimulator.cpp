//! @file     iosPlatformSimulator.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Platform Simulator Implementation
//----------------------------------------------------------------------------

#if (_TARGET_OS_SIMULATOR_ == 1)

extern "C" {
    
DIR *opendir$INODE64$UNIX2003(const char * path)
{
    return opendir(path);
}
    
int closedir$UNIX2003(DIR * path)
{
    return closedir(path);
}
    
int fputs$UNIX2003(const char * str, FILE * fp)
{
    return fputs(str, fp);
}
    
FILE *fopen$UNIX2003( const char *filename, const char *mode )
{
    return fopen(filename, mode);
}

size_t fwrite$UNIX2003( const void *a, size_t b, size_t c, FILE *d )
{
    return fwrite(a, b, c, d);
}

char *strerror$UNIX2003( int errnum )
{
    
    return strerror(errnum);
}

DIR *opendir$INODE64(const char * a)
{
    return opendir(a);
}

struct dirent *readdir$INODE64(DIR *dir)
{
    return readdir(dir);
}

int CRYPTO_memcmp(const void * m1, const void * m2, size_t size)
{
    return memcmp(m1, m2, size);
}
    
}

#endif
