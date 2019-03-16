/*  uchar.h - utf-16 character definitions
 Copyright (c) 2001-2008 Mark Weaver
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

/*! \file uchar.h
    \brief Various functions for dealing with (raw) uchar strings -- for a managed
 uchar string, see #ustr.h
 */

#ifndef libalgo_uchar_h
#define libalgo_uchar_h

#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <wctype.h>

#ifdef __cplusplus
extern "C" {
#endif

/* porting section: uchar must be an unsigned 16-bit integer */
#if defined(_MSC_VER) || defined(__GNUC__)
# if defined(_MSC_VER)
  /*! Basic utf-16 unit */
#  if !defined(NO_UCHAR)
   typedef wchar_t  uchar;
#  endif
  /*! utf-16 unit */
  typedef wchar_t  uchar16;
# else
#  if !defined(NO_UCHAR)
   /*! Basic utf-16 unit */
   typedef unsigned short uchar;
#  endif
  /*! utf-16 unit */
  typedef unsigned short uchar16;
# endif
/*! utf-32 unit */
typedef unsigned int uchar32;
/*! utf-8 unit */
typedef unsigned char uchar8;
#else
#error "Unknown compiler/architecture -- please update definitions for uchar"
#endif

/*! Defined a static utf-16 character */
#define uc_static_char(x) L##x
/*! Defined a static utf-16 string */
#define uc_static_string(x) L##x
#define ucs(x)    uc_static_string(x)
 
/*! as strchr - handles surrogates; all platforms */
uchar16 *uc_chr(const uchar16 *src, uchar32 c);
/*! as strrchr - handles surrogates */
uchar16 *uc_rchr(const uchar16 *src, uchar32 c);

#ifdef _MSC_VER
/*! as strncpy */
#define uc_ncpy(x,y,n)  wcsncpy((x),(y),(n))
/*! as strcpy */
#define uc_cpy(x,y)   wcscpy((x),(y))
/*! as strlen */
#define uc_len(x)   wcslen((x))
/*! as strcmp */
#define uc_cmp(x,y)   wcscmp((x),(y))
/*! as strncmp */
#define uc_ncmp(x,y,n)  wcsncmp((x),(y),(n))
/*! as stricmp */
#define uc_icmp(x,y)  _wcsicmp((x),(y))
/*! as strcat */
#define uc_cat(x,y)   wcscat((x),(y))
/*! as strnicmp */
#define uc_nicmp(x,y,n)  _wcsnicmp((x),(y),(n))
#if _MSC_VER >= 1400
#define uc_dup(x)   _wcsdup(x)
#else
/*! as strdup */
#define uc_dup(x)   wcsdup(x)
#endif
/*! as atoi */
#define uc_toi(x)   _wtoi(x)
/*! as strtol */
#define uc_tol(s,e,b)  wcstol((s),(e),(b))
/*! as strtoul */
#define uc_toul(s,e,b)  wcstoul((s),(e),(b))
/*! as strtod */
#define uc_tod(s,e)   wcstod((s),(e))
/*! as strtod */
#define uc_tof(s,e)   ((float)wcstod((s),(e)))
/*! as snprintf */
#define uc_snprintf   _snwprintf
/*! as vsnprintf */
#define uc_vsnprintf  _vsnwprintf
/*! as printf */
#define uc_printf   wprintf
/*! as vprintf */
#define uc_vprintf   vwprintf
/*! as fprintf */
#define uc_fprintf   fwprintf
/*! as vfprintf */
#define uc_vfprintf   vfwprintf
/*! as wcslwr */
#define uc_lwr    _wcslwr
/*! as wcsupr */
#define uc_upr    _wcsupr
/*! as wcsstr */
#define uc_strstr(x,y)  wcsstr((x),(y))
#else
/*! as strlen */
size_t uc_len(const uchar16 *wcs);
/*! as strcpy */
uchar16 *uc_cpy(uchar16 *dst, const uchar16 *src);
/*! as strncpy */
uchar16 *uc_ncpy(uchar16 *dst, const uchar16 *src, size_t n);
/*! as strcmp */
int uc_cmp(const uchar16 *s1, const uchar16 *s2);
/*! as strcmp */
int uc_cmp(const uchar16 *s1, const uchar16 *s2);
/*! as strncmp */
int uc_ncmp(const uchar16 *s1, const uchar16 *s2, size_t n);
/*! as stricmp */
int uc_icmp(const uchar16 *s1, const uchar16 *s2);
/*! as strnicmp */
int uc_nicmp(const uchar16 *s1, const uchar16 *s2, size_t n);
/*! as atoi */
int uc_toi(const uchar16 *s);
/*! as strtod */
double uc_tod(const uchar16 *s, uchar16 **eptr);
/*! as strtof */
float uc_tof(const uchar16 *s, uchar16 **eptr);
/*! as strtol */
long uc_tol(const uchar16 *s, uchar16 **eptr, int base);
/*! as strtoul */
unsigned long uc_toul(const uchar16 *s, uchar16 **eptr, int base);
/*! as snprintf */
int uc_snprintf(uchar16 *wcs, size_t maxlen, const uchar16 *fmt, ...);
/*! as vsnprintf */
int uc_vsnprintf(uchar16 *wcs, size_t maxlen, const uchar16 *fmt, va_list vap);
/*! as printf */
int uc_printf(const uchar16 *fmt, ...);
/*! as vprintf */
int uc_vprintf(const uchar16 *fmt, va_list vap);
/*! as fprintf */
int uc_fprintf(FILE *fp, const uchar16 *fmt, ...);
/*! as vfprintf */
int uc_vfprintf(FILE *fp, const uchar16 *fmt, va_list vap);
/*! as strlwr */
uchar16 *uc_lwr(uchar16 *s);
/*! as strupr */
uchar16 *uc_upr(uchar16 *s);
/*! as strdup */
uchar16 *uc_dup(const uchar16 *s);
#endif

/*! as isalnum */
#define uc_isalnum(x)  iswalnum(x)
/*! as isalpha */
#define uc_isalpha(x)  iswalpha(x)
/*! as isdigit */
#define uc_isdigit(x)  iswdigit(x)
/*! as isspace */
#define uc_isspace(x)  iswspace(x)
/*! as tolower */
#define uc_tolower(x)  towlower(x)
/*! as toupper */
#define uc_toupper(x)  towupper(x)

/*! as strstr */
uchar16 *uc_str(const uchar16 *str, const uchar16 *search);
/*! as strstr, but case insensitive */
uchar16 *uc_istr(const uchar16 *str, const uchar16 *search);

/*! Unicode code points, in utf-32 */
typedef enum uc_chars_e {
 UC_NUL     = 0,
 UC_NULL     = 0,
 UC_BACKSPACE   = 8,
 UC_TAB     = 9,
 UC_LF     = 10,
 UC_VT     = 11,
 UC_FF     = 12,
 UC_CR     = 13,
 UC_SPACE    = 32,
 UC_EXCLAMATION_MARK  = 33,
 UC_DBL_QUOTE   = 34,
 UC_HASH     = 35,
 UC_DOLLAR_SIGN   = 36,
 UC_PERCENT    = 37,
 UC_AMPERSAND   = 38,
 UC_APOSTROPHE   = 39,
 UC_LEFT_PAREN   = 40,
 UC_RIGHT_PAREN   = 41,
 UC_STAR     = 42,
 UC_PLUS     = 43,
 UC_COMMA    = 44,
 UC_MINUS    = 45,
 UC_DOT     = 46,
 UC_SLASH    = 47,
 UC_0     = 48,
 UC_1     = 49,
 UC_2     = 50,
 UC_3     = 51,
 UC_4     = 52,
 UC_5     = 53,
 UC_6     = 54,
 UC_7     = 55,
 UC_8     = 56,
 UC_9     = 57,
 UC_COLON    = 58,
 UC_SEMI_COLON   = 59,
 UC_LT     = 60,
 UC_EQ     = 61,
 UC_GT     = 62,
 UC_QUESTION_MARK  = 63,
 UC_AT_SIGN    = 64,
 UC_A     = 65,
 UC_B     = 66,
 UC_C     = 67,
 UC_D     = 68,
 UC_E     = 69,
 UC_F     = 70,
 UC_G     = 71,
 UC_H     = 72,
 UC_I     = 73,
 UC_J     = 74,
 UC_K     = 75,
 UC_L     = 76,
 UC_M     = 77,
 UC_N     = 78,
 UC_O     = 79,
 UC_P     = 80,
 UC_Q     = 81,
 UC_R     = 82,
 UC_S     = 83,
 UC_T     = 84,
 UC_U     = 85,
 UC_V     = 86,
 UC_W     = 87,
 UC_X     = 88,
 UC_Y     = 89,
 UC_Z     = 90,
 UC_LEFT_SQUARE   = 91,
 UC_BACKSLASH   = 92,
 UC_RIGHT_SQUARE   = 93,
 UC_POWER    = 94,
 UC_UNDERLINE   = 95,
 UC_BACK_QUOTE   = 96,
 UC_a     = 97,
 UC_b     = 98,
 UC_c     = 99,
 UC_d     = 100,
 UC_e     = 101,
 UC_f     = 102,
 UC_g     = 103,
 UC_h     = 104,
 UC_i     = 105,
 UC_j     = 106,
 UC_k     = 107,
 UC_l     = 108,
 UC_m     = 109,
 UC_n     = 110,
 UC_o     = 111,
 UC_p     = 112,
 UC_q     = 113,
 UC_r     = 114,
 UC_s     = 115,
 UC_t     = 116,
 UC_u     = 117,
 UC_v     = 118,
 UC_w     = 119,
 UC_x     = 120,
 UC_y     = 121,
 UC_z     = 122,
 UC_LEFT_CURLY   = 123,
 UC_BAR     = 124,
 UC_RIGHT_CURLY   = 125,
 UC_TILDE    = 126
} uc_chars;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* libalgo_uchar_h */
