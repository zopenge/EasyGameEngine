/*  inttypes.h - attempt at portable integer types

 Copyright (C) 2001 Mark Weaver
 Written by Mark Weaver <mark@npsl.co.uk>

 Part of the libalgo library.
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Library General Public
 License as published by the Free Software Foundation; either
 version 2 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Library General Public License for more details.

 You should have received a copy of the GNU Library General Public
 License along with this library; if not, write to the
 Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 Boston, MA  02111-1307, USA.
*/

/*! \file inttypes.h
    \brief "Portable" integer types, as C99 <stdint.h>.  <stdint.h>
    is preferred where available.
 */

#ifndef libalgo_inttypes_h
#define libalgo_inttypes_h

#if defined(__GNUC__)
#include <stdint.h>

#define DECLARE_INT64(x) x##LL
#define DECLARE_UINT64(x) x##ULL

#elif defined(_MSC_VER)
/* MSC definitions */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAVE_INTTYPES
#define HAVE_INTTYPES

#ifndef HAVE_UINT64_T
#define HAVE_UINT64_T
typedef unsigned __int64 uint64_t;
#endif

#ifndef HAVE_UINT32_T
#define HAVE_UINT32_T
typedef unsigned int uint32_t;
#endif

#ifndef HAVE_UINT16_T
#define HAVE_UINT16_T
typedef unsigned short uint16_t;
#endif

#ifndef HAVE_UINT8_T
#define HAVE_UINT8_T
typedef unsigned char uint8_t;
#endif

#ifndef HAVE_INT64_T
#define HAVE_INT64_T
typedef __int64 int64_t;
#endif

#ifndef HAVE_INT32_T
#define HAVE_INT32_T
typedef int int32_t;
#endif

#ifndef HAVE_INT16_T
#define HAVE_INT16_T
typedef short int16_t;
#endif

#ifndef HAVE_INT8_T
#define HAVE_INT8_T
typedef char int8_t;
#endif

#define DECLARE_INT64(x) x##I64
#define DECLARE_UINT64(x) x##UI64

#endif /* HAVE_INTTYPES */

#ifdef __cplusplus
} /* extern "C" */
#endif

#else /* elif defined(_MSC_VER) */
#error Unsupported compiler
#endif

#endif /* libalgo_inttypes_h */
