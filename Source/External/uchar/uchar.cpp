/* 	uchar.h - utf-16 helper functions
        Copyright (c) 2001-2004 Mark Weaver
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

#include "uchar/uchar.h"
#include "uchar/inttypes.h"
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(_PLATFORM_IOS_)
#	define EGE_STATIC_ASSERT(B, T) _Static_assert(B, T)
#else
#	define EGE_STATIC_ASSERT(B, T) static_assert(B, T)
#endif

EGE_STATIC_ASSERT(sizeof(uchar) == sizeof(unsigned short), "Check the uchar size");
EGE_STATIC_ASSERT(sizeof(uchar16) == sizeof(unsigned short), "Check the uchar16 size");

#if defined(_PLATFORM_ANDROID_)
#	include <alloca.h>
#	define __STDC_VERSION__ 199901L
#	include <stdlib.h>
#endif

#if !defined(_MSC_VER)

#	define ASCII_SPACE(x)                                                         \
		((x) == ' ' || (x) == '\t' || (x) == '\r' || (x) == '\n' || (x) == '\f' || \
		 (x) == '\v')
#	define ASCII_UPPER(x) ((x) >= 'a' && (x) <= 'z' ? (x) - 'a' + 'A' : (x))
size_t uc_len(const uchar* uc) {
	size_t ncount = 0;
	for (; *uc != UC_NUL; uc++) ++ncount;
	return ncount;
}

uchar* uc_cpy(uchar* dest, const uchar* src) {
	uchar* odest = dest;
	for (; (*dest = *src) != UC_NUL; ++src, ++dest)
		;
	return odest;
}

uchar* uc_dup(const uchar* src) {
	size_t len = sizeof(uchar) * (uc_len(src) + 1);
	uchar* dest = (uchar*)malloc(len);
	if (!dest) return NULL;
	memcpy(dest, src, len);
	return dest;
}

uchar* uc_ncpy(uchar* dest, const uchar* src, size_t n) {
	uchar* odest = dest;
	for (; n > 0 && (*dest = *src) != UC_NUL; ++src, ++dest, --n)
		;
	return odest;
}

int uc_cmp(const uchar* s1, const uchar* s2) {
	int c1, c2;
	do {
		c1 = *s1++;
		c2 = *s2++;
	} while (c1 && c1 == c2);
	return c1 - c2;
}

int uc_ncmp(const uchar* s1, const uchar* s2, size_t n) {
	int c1 = 0, c2 = 0;
	do {
		if (n-- == 0) break;
		c1 = *s1++;
		c2 = *s2++;
	} while (c1 && c1 == c2);
	return c1 - c2;
}

int uc_icmp(const uchar* s1, const uchar* s2) {
	int c1, c2;
	do {
		c1 = ASCII_UPPER(*s1);
		c2 = ASCII_UPPER(*s2);
		++s1;
		++s2;
	} while (c1 && c1 == c2);
	return c1 - c2;
}

int uc_nicmp(const uchar* s1, const uchar* s2, size_t n) {
	int c1 = 0, c2 = 0;
	do {
		if (n-- == 0) break;
		c1 = ASCII_UPPER(*s1);
		c2 = ASCII_UPPER(*s2);
		++s1;
		++s2;
	} while (c1 && c1 == c2);
	return c1 - c2;
}

#endif /* !_MSC_VER */

/* strchr accounting for surrogates */
uchar16* uc_chr(const uchar* s, uchar32 srch) {
	/* easy case? */
	if (srch <= 0xFFFF) {
		/* treating all as single utf-16 values will work reasonably */
		while (*s && *s != srch) ++s;
		return *s ? (uchar*)s : NULL;
	}
	/* no, go through handling surrogates */
	while (*s) {
		/* mark position of match */
		uchar* mark = (uchar*)s;

		/* extract character */
		uchar32 uc = *s++;

		/* handle surrogates, discarding junk */
		if (uc >= 0xD800 && uc <= 0xDFFF) {
			uchar32 uc2;

			if (uc >= 0xDC00 || !*s) /* junk */
				continue;
			uc2 = *s++;
			if (uc2 < 0xDC00 || uc2 > 0xDFFF) /* junk */
				continue;
			uc = (uc & 0x3FF) << 10 | (uc2 & 0x3FF) + 0x10000;
		}

		/* check for match and return marked position */
		if (uc == srch) return mark;
	}
	return NULL;
}

#if !defined(_MSC_VER)

/*
 * Lifted from ucLibc, which is also under the LGPL license.
 *
 * This is the main work fuction which handles both strtol (uflag = 0) and
 * strtoul (uflag = 1).
 */
unsigned long uc_tol_helper(const uchar* str, uchar** endptr, int base,
                            int uflag) {
	unsigned long number = 0;
	unsigned long cutoff;
	uchar* pos = (uchar*)str;
	uchar* fail_char = (uchar*)str;
	int digit, cutoff_digit;
	int negative;

	/* skip leading whitespace */
	while (ASCII_SPACE(*pos)) ++pos;

	/* handle optional sign */
	negative = 0;
	switch (*pos) {
		case '-':
			negative = 1; /* fall through to increment pos */
		case '+':
			++pos;
	}

	if ((base == 16) && (*pos == '0')) { /* handle option prefix */
		++pos;
		fail_char = pos;
		if ((*pos == 'x') || (*pos == 'X')) {
			++pos;
		}
	}

	if (base == 0) { /* dynamic base */
		base = 10; /* default is 10 */
		if (*pos == '0') {
			++pos;
			base -= 2; /* now base is 8 (or 16) */
			fail_char = pos;
			if ((*pos == 'x') || (*pos == 'X')) {
				base += 8; /* base is 16 */
				++pos;
				++fail_char;
			}
		}
	}

	if ((base < 2) || (base > 36)) { /* illegal base */
		goto DONE;
	}

	cutoff = ULONG_MAX / base;
	cutoff_digit = ULONG_MAX - cutoff * base;

	while (1) {
		digit = 40;
		if ((*pos >= '0') && (*pos <= '9')) {
			digit = (*pos - '0');
		} else if (*pos >= 'a') {
			digit = (*pos - 'a' + 10);
		} else if (*pos >= 'A') {
			digit = (*pos - 'A' + 10);
		} else
			break;

		if (digit >= base) {
			break;
		}

		++pos;
		fail_char = pos;

		/* adjust number, with overflow check */
		if ((number > cutoff) || ((number == cutoff) && (digit > cutoff_digit))) {
			number = ULONG_MAX;
			if (uflag) {
				negative = 0; /* since unsigned returns ULONG_MAX */
			}
			errno = ERANGE;
		} else {
			number = number * base + digit;
		}
	}

DONE:
	if (endptr) {
		*endptr = fail_char;
	}

	if (negative) {
		if (!uflag && (number > ((unsigned long)(-(1 + LONG_MIN))) + 1)) {
			errno = ERANGE;
			return (unsigned long)LONG_MIN;
		}
		return (unsigned long)(-((long)number));
	} else {
		if (!uflag && (number > (unsigned long)LONG_MAX)) {
			errno = ERANGE;
			return LONG_MAX;
		}
		return number;
	}
}

unsigned long uc_toul(const uchar* str, uchar** eptr, int base) {
	return uc_tol_helper(str, eptr, base, 1);
}

long uc_tol(const uchar* str, uchar** eptr, int base) {
	return (long)uc_tol_helper(str, eptr, base, 0);
}

int uc_toi(const uchar* str) {
	return (int)uc_tol(str, NULL, 10);
}

/* Not even going to try with this: will just convert to narrow
   and use the CRT
 */
double uc_tod(const uchar* s, uchar** eptr) {
	char *nbuf, *neptr;
	size_t slen, i;
	double ret;

	slen = uc_len(s) + 1;
	nbuf = (char*)alloca(slen);
	if (nbuf == NULL) {
		errno = ENOMEM;
		return 0.0;
	}
	for (i = 0; i < slen; ++i) nbuf[i] = (char)s[i];

	ret = strtod(nbuf, &neptr);
	if (eptr) {
		*eptr = (uchar*)s + (neptr - nbuf);
	}
	return ret;
}

float uc_tof(const uchar* s, uchar** eptr) {
	char *nbuf, *neptr;
	size_t slen, i;
	double ret;

	slen = uc_len(s) + 1;
	nbuf = (char*)alloca(slen);
	if (nbuf == NULL) {
		errno = ENOMEM;
		return 0.0;
	}
	for (i = 0; i < slen; ++i) nbuf[i] = (char)s[i];

	ret = strtof(nbuf, &neptr);
	if (eptr) {
		*eptr = (uchar*)s + (neptr - nbuf);
	}
	return ret;
}

#	define F_LEFT 1 /* left alignment */
#	define F_PRINT_SIGN 2 /* always print sign */
#	define F_PRINT_BLANK 4 /* print blank in front of positive number */
#	define F_ZERO_PAD 8 /* zero pad */
#	define F_PREFIX 16 /* for oxX prefix the number with 0, 0x, 0X */
#	define F_NEGATIVE 32 /* number is negative */
#	define F_OCTAL 64 /* octal - force leading zero */

#	define F_LONG 1024 /* long modifier */
#	define F_SHORT 2048 /* short modifier */
#	define F_LONGLONG 4096 /* long long (int64_t) modifier */

/* 'Safe' isdigit implementation (avoids issues with negative/non ASCII char
 * values) */
#	define IS_DIGIT(x) ((x) >= UC_0 && (x) <= UC_9)

static uchar null_string[] = {UC_LEFT_PAREN, UC_n, UC_u, UC_l,
                              UC_l, UC_RIGHT_PAREN, UC_NUL};
static char nnull_string[] = "(null)";

#	define UCFT_STRING 0
#	define UCFT_FILE 1
#	define UCFT_INFINITE ((size_t)-1)

typedef struct uchar_format_target_s {
	union {
		FILE* fp;
		uchar* outp;
	} u;
	int type;
	size_t remaining; /* remaining uchars or UCFT_INFINITE */
	size_t written; /* chars `written', or that would have been written
                                       if remaining was exceeded */
} uchar_format_target;

#	define uchar_format_target_output(ucf, buf, n)                                   \
		(ucf)->written += n; /* pseudo-count */                                       \
		if ((ucf)->type == UCFT_FILE) {                                               \
			if ((ucf)->remaining == UCFT_INFINITE) {                                  \
				size_t i;                                                             \
				for (i = 0; i < (n); ++i) fputc((buf)[i], (ucf)->u.fp);               \
			} else {                                                                  \
				size_t i;                                                             \
				for (i = 0; i < (n) && (ucf)->remaining > 0; ++i, --(ucf)->remaining) \
					fputc((buf)[i], (ucf)->u.fp);                                     \
			}                                                                         \
		} else {                                                                      \
			if ((ucf)->remaining == UCFT_INFINITE) {                                  \
				size_t i;                                                             \
				for (i = 0; i < (n); ++i, --(ucf)->remaining)                         \
					*((ucf)->u.outp++) = (buf)[i];                                    \
			} else {                                                                  \
				size_t i;                                                             \
				for (i = 0; i < (n) && (ucf)->remaining > 0; ++i, --(ucf)->remaining) \
					*((ucf)->u.outp++) = (buf)[i];                                    \
			}                                                                         \
		}

static int uchar_format(uchar_format_target* target, const uchar* fmt,
                        va_list vap) {
	int i, radix;
	uchar* strarg;
	char* nstrarg;
	unsigned int num;
	uint64_t num64;
	uchar charg, padch;
	int prefixlen;
	int hexadd;
	int zerostr = 0;

	/* Ensure strings are terminated if possible */
	if (target->type == UCFT_STRING) {
		if (target->remaining == 0) {
			zerostr = 1;
		} else {
			--target->remaining;
		}
	}

	while (*fmt) {
		int flags = 0;
		int width = -1, prec = -1;

		/* copy through */
		if (*fmt != UC_PERCENT) {
			const uchar* st = fmt;
			size_t n;

			/* find end of the plain string portion */
			do {
				fmt++;
			} while (*fmt != UC_PERCENT && *fmt != UC_NUL);

			/* copy it */
			n = fmt - st;
			uchar_format_target_output(target, st, n);

			/* stop if done */
			if (*fmt == UC_NUL) break;

			/* drop through to process format spec. */
		}

		/* The format is %[flags][width][.precision]type
        type is the type code
            width or precision are digits or *, * => read from argument list
            modifiers are any of:
                     +   print sign even for positive numbers
                    ' '  (blank) - print space in front of positive numbers,
       ignored with + -	 left justify 0	 pad with 0 #	 bizarre
     */

		/* suck out flags */
		++fmt;
		while (1) {
			/* A '+' overrides a blank if both are used */
			if (*fmt == UC_PLUS) {
				flags = (flags & ~F_PRINT_BLANK) | F_PRINT_SIGN;
			} else if (*fmt == UC_SPACE) {
				if (!(flags & F_PRINT_SIGN)) flags |= F_PRINT_BLANK;
				/* a '-' overrides a '0' if both are given */
			} else if (*fmt == UC_MINUS) {
				flags = (flags & ~F_ZERO_PAD) | F_LEFT;
			} else if (*fmt == UC_0) {
				if (!(flags & F_LEFT)) flags |= F_ZERO_PAD;
			} else if (*fmt == UC_HASH) {
				flags |= F_PREFIX;
			} else
				break;
			++fmt;
		}
		/* now width, precision */
		if (*fmt == UC_STAR) {
			width = va_arg(vap, int);
			if (width < 0) { /* negative width means left alignment */
				flags |= F_LEFT;
				width = -width;
			}
			++fmt;
		} else {
			width = 0;
			while (IS_DIGIT(*fmt)) width = width * 10 + *fmt++ - UC_0;
		}
		if (*fmt == UC_DOT) {
			++fmt;
			if (*fmt == UC_STAR) {
				prec = va_arg(vap, int);
				/* negative prec gives prec of zero */
				if (prec < 0) prec = 0;
				++fmt;
			} else {
				/* note: dot with no number gives prec of 0,
           which is correct */
				prec = 0;
				while (IS_DIGIT(*fmt)) prec = prec * 10 + *fmt++ - UC_0;
			}
		}

		/* check the modifier (ll = i64, l = nothing (long), h = short (string) */
		switch (*fmt) {
			case UC_l:
				++fmt;
				if (*fmt == UC_l) {
					++fmt;
					flags |= F_LONGLONG;
					break;
				}
				flags |= F_LONG;
				break;
			case UC_h:
				++fmt;
				flags |= F_SHORT;
				break;
		}

		/* finally the type */
		switch (*fmt++) {
			/* character data; set up as a string with precision of 1 */
			case UC_c:
				charg = (uchar)va_arg(vap, int);
				strarg = &charg;
				prec = 1;
				goto COMMON_STRING;

			case UC_s: {
				if (flags & F_SHORT) {
					int arglen;
					char* p;

					p = nstrarg = va_arg(vap, char*);

					/* print NULL as (null), with prec determining number of
             characters printed */
					if (p == NULL) {
						nstrarg = nnull_string;
						prec = prec == -1 || prec > 6 ? 6 : prec;

						/* only compute arglen up to prec characters as the string may
               not be null terminated */
					} else {
						i = prec == -1 ? INT_MAX : prec;
						while (i-- && *p) ++p;
						arglen = p - nstrarg;

						/* no precedence, print all of it */
						if (prec == -1 || prec > arglen) prec = arglen;
					}
				} else {
					int arglen;
					uchar* p;

					p = strarg = va_arg(vap, uchar*);

					/* print NULL as (null), with prec determining number of
             characters printed */
					if (p == NULL) {
						strarg = null_string;
						prec = prec == -1 || prec > 6 ? 6 : prec;

						/* only compute arglen up to prec characters as the string may
               not be null terminated */
					} else {
						i = prec == -1 ? INT_MAX : prec;
						while (i-- && *p) ++p;
						arglen = p - strarg;

						/* no precedence, print all of it */
						if (prec == -1 || prec > arglen) prec = arglen;
					}
				}

				/* fall through to COMMON_STRING */
			}

			COMMON_STRING : {
				int maxlen, pad;

				maxlen = prec > width ? prec : width;

				pad = width - prec;

				padch = (flags & F_ZERO_PAD) && !(flags & F_LEFT) ? UC_0 : UC_SPACE;
				if (!(flags & F_LEFT)) {
					while (pad-- > 0) {
						uchar_format_target_output(target, &padch, 1);
					}
				}

				if (flags & F_SHORT) {
					while (prec-- > 0) {
						uchar u = (uchar) * (nstrarg++);
						uchar_format_target_output(target, &u, 1);
					}
				} else {
					while (prec-- > 0) {
						uchar_format_target_output(target, strarg, 1);
						++strarg;
					}
				}

				if (flags & F_LEFT) {
					while (pad-- > 0) {
						uchar_format_target_output(target, &padch, 1);
					}
				}
				break;
			}

			case UC_u:
				if (flags & F_LONGLONG)
					num64 = va_arg(vap, uint64_t);
				else
					num = va_arg(vap, unsigned int);
				radix = 10;
				flags &= ~(F_PREFIX | F_PRINT_SIGN | F_PRINT_BLANK);
				prefixlen = 0;
				goto COMMON_INT;

			case UC_d:
			case UC_i: {
				if (flags & F_LONGLONG) {
					int64_t intarg = va_arg(vap, int64_t);
					if (intarg < 0) {
						flags |= F_NEGATIVE;
						num64 = (uint64_t)-intarg;
					} else
						num64 = (uint64_t)intarg;
				} else {
					int intarg = va_arg(vap, int);
					if (intarg < 0) {
						flags |= F_NEGATIVE;
						num = (unsigned)-intarg;
					} else
						num = intarg;
				}
				radix = 10;
				flags &= ~F_PREFIX;
				prefixlen = 0;
				goto COMMON_INT;
			}

			case UC_x:
				hexadd = UC_a - UC_9 - 1;
				goto COMMON_HEX;

			case UC_X:
				hexadd = UC_A - UC_9 - 1;
				goto COMMON_HEX;

			case UC_p: {
				num64 = (uint64_t)va_arg(vap, void*);
				flags |= F_LONGLONG;
				hexadd = UC_A - UC_9 - 1;
				prec = 2 * sizeof(void*);
				goto COMMON_HEX_WITH_NUM;
			}

			COMMON_HEX:
				if (flags & F_LONGLONG)
					num64 = va_arg(vap, uint64_t);
				else
					num = va_arg(vap, unsigned int);

			COMMON_HEX_WITH_NUM:
				radix = 16;
				/* special case: zero => no prefix */
				if (((flags & F_LONGLONG) && num64 == 0) ||
				    (!(flags & F_LONGLONG) && num == 0))
					flags &= ~F_PREFIX;
				flags &= ~(F_PRINT_SIGN | F_PRINT_BLANK);
				prefixlen = (flags & F_PREFIX) ? 2 : 0;
				goto COMMON_INT;

			case UC_o: {
				if (flags & F_LONGLONG)
					num64 = va_arg(vap, uint64_t);
				else
					num = va_arg(vap, unsigned int);
				radix = 8;
				if (flags & F_PREFIX) flags |= F_OCTAL;
				flags &= ~(F_PRINT_SIGN | F_PRINT_BLANK | F_PREFIX);
				prefixlen = 0;
				/* fall through to COMMON_INT */
			}

			COMMON_INT : {
				int numlen = 0, maxlen, pad, nzpad;
				uchar numbuf[64], *p = numbuf + 63;

				/* Note the weird special cases:
           - If zero is printed with an explicit precision of zero then
           nothing is output for the number portion.
           - There is no prefix for a hex number if the result is zero.

           Case #2 is handled by COMMON_HEX_WITH_NUM.
     */
				*p = UC_NUL;

				if (flags & F_LONGLONG) {
					uint64_t cvt = num64;

					if (!(prec == 0 && cvt == 0)) {
						do {
							++numlen;
							*--p = (uchar)(cvt % radix) + UC_0;
							if (*p > UC_9) *p += hexadd;
							cvt = cvt / radix;
						} while (cvt > 0);
					}
				} else {
					unsigned int cvt = num;

					if (!(prec == 0 && cvt == 0)) {
						do {
							++numlen;
							*--p = (uchar)(cvt % radix) + UC_0;
							if (*p > UC_9) *p += hexadd;
							cvt = cvt / radix;
						} while (cvt > 0);
					}
				}

				numlen = numbuf + 63 - p;

				/* The precision specifies the minimum number of digits to be
           printed. If the number of digits in the argument is less than
           precision, the output value is padded on the left with zeros.
           The value is not truncated when the number of digits exceeds
           precision.
           If a precision is given with '0', the precision is ignored.
     */

				/* default precision is 1 for COMMON_INT case */
				if (prec == -1) prec = 1;
				/* explicit precision => no zero padding */
				else
					flags &= ~F_ZERO_PAD;

				/* number of zero pad characters */
				nzpad = prec - numlen;
				if (nzpad < 0) nzpad = 0;

				/* if no leading zero and we need one for octal, account for that */
				if ((flags & F_OCTAL) && *p != UC_0 && nzpad <= 0) {
					*--p = UC_0;
					++numlen;
				}

				/* and compute # of pad characters */
				pad = width - numlen - nzpad -
				      !!(flags & (F_NEGATIVE | F_PRINT_SIGN | F_PRINT_BLANK)) -
				      prefixlen;

				/* if padding with zeros, transfer the pad */
				if (flags & F_ZERO_PAD) {
					nzpad += pad;
					pad = 0;
				}

				/* for the number part we a minimum of prec characters, but if
           the number is longer we print the whole of it */
				maxlen = numlen < prec ? prec : numlen;

				/* account for the sign or blank */
				if ((flags & F_NEGATIVE) || (flags & F_PRINT_SIGN) ||
				    (flags & F_PRINT_BLANK))
					++maxlen;

				/* account for the prefix */
				maxlen += prefixlen;

				/* print a minimum of `width' characters */
				if (maxlen < width) maxlen = width;

				/* left padding if needed */
				if (!(flags & F_LEFT)) {
					static const uchar uc_space = UC_SPACE;
					while (pad-- > 0) {
						uchar_format_target_output(target, &uc_space, 1);
					}
				}

				/* sign or blank */
				if (flags & F_NEGATIVE) {
					static const uchar uc_minus = UC_MINUS;
					uchar_format_target_output(target, &uc_minus, 1);
				} else if (flags & F_PRINT_SIGN) {
					static const uchar uc_plus = UC_PLUS;
					uchar_format_target_output(target, &uc_plus, 1);
				} else if (flags & F_PRINT_BLANK) {
					static const uchar uc_space = UC_SPACE;
					uchar_format_target_output(target, &uc_space, 1);
				}

				/* add prefix if required */
				if (flags & F_PREFIX) {
					uchar prefix[2] = {UC_0, (uchar)(hexadd + UC_9 + UC_X - UC_A + 1)};
					uchar_format_target_output(target, prefix, 2);
				}

				/* zeroes */
				{
					static const uchar uc_zero = UC_0;
					while (nzpad-- > 0) {
						uchar_format_target_output(target, &uc_zero, 1);
					}
				}

				/* number */
				while (*p) {
					uchar_format_target_output(target, p, 1);
					p++;
				}

				/* right padding if needed */
				if (flags & F_LEFT) {
					static const uchar uc_space = UC_SPACE;
					while (pad-- > 0) {
						uchar_format_target_output(target, &uc_space, 1);
					}
				}
				break;
			}

			/* this is horribly inefficient because it grows the buffer to accomodate
         the maximum length string - yeuch!
       */
			case UC_f: {
				/* max # of zeroes is 308 as DBL_MAX = 1.7976931348623158e+308
           so max size is 308 zeroes + "-1." + 1 for luck = 312 + prec
         */
				int maxlen, numlen;
				char fmtstr[12], *p = fmtstr, *fmtbuf;

				if (prec == -1) prec = 6; /* default prec if unspecified */
				maxlen = 312 + prec;

				if (maxlen < width) maxlen = width;

				fmtbuf = (char*)alloca(maxlen + 1); /* +1 for sprintf NULL */

				*p++ = '%';
				if (flags & F_LEFT) *p++ = '-';
				if (flags & F_PRINT_SIGN) *p++ = '+';
				if (flags & F_PRINT_BLANK) *p++ = ' ';
				if (flags & F_PREFIX) *p++ = '#';
				if (flags & F_ZERO_PAD) *p++ = '0';
				strcpy(p, "*.*f");

				numlen = sprintf(fmtbuf, fmtstr, width, prec, va_arg(vap, double));

				/* copy and widen -- these are all numbers so the code points are the
         * same */
				for (; numlen-- > 0;) {
					uchar uc = (uchar) * (fmtbuf++);
					uchar_format_target_output(target, &uc, 1);
				}
				break;
			}

			/* This is not too bad at all - we will overallocate by just a few
         characters at worst, and we could get rid of that if we were bothered
         with a few tests.
         Note that 'g' works because it always chooses the most compact form -
         i.e. it can't be longer than 'e', so picking a buffer to acommodate 'e'
         will work just fine.  The buffer might be larger than required though
         if we could use 'f' (e.g. where num=1.0).  Again, we are not worried
         about the 8 character overallocate, since this is the buffer
         granularity anyway.
       */
			case UC_e:
			case UC_E:
			case UC_g:
			case UC_G: {
				/* form is [+-]? d.d *e [+-] ddd

           so, max = sign+1 digit+1 '.'+prec+1 'e'+1 [+-] + 3 digits
                   = 8+prec
         */
				int maxlen, numlen;
				char fmtstr[12], *p = fmtstr, *fmtbuf;

				if (prec == -1) prec = 6; /* default prec if unspecified */
				maxlen = 8 + prec;
				if (maxlen < width) maxlen = width;

				fmtbuf = (char*)alloca(maxlen + 1); /* +1 for sprintf NULL */

				*p++ = '%';
				if (flags & F_LEFT) *p++ = '-';
				if (flags & F_PRINT_SIGN) *p++ = '+';
				if (flags & F_PRINT_BLANK) *p++ = ' ';
				if (flags & F_PREFIX) *p++ = '#';
				if (flags & F_ZERO_PAD) *p++ = '0';
				*p++ = '*';
				*p++ = '.';
				*p++ = '*';
				*p++ = (char)*(fmt - 1);
				*p++ = '\0';

				numlen = sprintf(fmtbuf, fmtstr, width, prec, va_arg(vap, double));

				/* copy and widen -- these are all numbers so the code points are the
         * same */
				for (; numlen-- > 0;) {
					uchar uc = (uchar) * (fmtbuf++);
					uchar_format_target_output(target, &uc, 1);
				}
				break;
			}

			default: {
				/* pass through rubbish, or % character */
				uchar_format_target_output(target, (fmt - 1), 1);
				break;
			}
		}
	}

	if (target->type == UCFT_STRING) {
		if (!zerostr) {
			static const uchar nul = UC_NUL;
			/* recoup the hidden character so we always get a NUL terminator */
			target->remaining++;
			uchar_format_target_output(target, &nul, 1);
			--target->written;
		}
	}
	return target->written;
}

int uc_snprintf(uchar* wcs, size_t maxlen, const uchar* fmt, ...) {
	int ret;
	va_list vap;
	uchar_format_target ucft;

	/* create the format target */
	ucft.type = UCFT_STRING;
	ucft.remaining = maxlen;
	ucft.written = 0;
	ucft.u.outp = wcs;

	/* do the formatting */
	va_start(vap, fmt);
	ret = uchar_format(&ucft, fmt, vap);
	va_end(vap);
	return ret;
}

int uc_vsnprintf(uchar* wcs, size_t maxlen, const uchar* fmt, va_list vap) {
	uchar_format_target ucft;

	/* create the format target */
	ucft.type = UCFT_STRING;
	ucft.remaining = maxlen;
	ucft.written = 0;
	ucft.u.outp = wcs;

	/* do the formatting */
	return uchar_format(&ucft, fmt, vap);
}

int uc_printf(const uchar* fmt, ...) {
	int ret;
	va_list vap;
	uchar_format_target ucft;

	/* create the format target */
	ucft.type = UCFT_FILE;
	ucft.remaining = UCFT_INFINITE;
	ucft.written = 0;
	ucft.u.fp = stdout;

	/* do the formatting */
	va_start(vap, fmt);
	ret = uchar_format(&ucft, fmt, vap);
	va_end(vap);
	return ret;
}

int uc_vprintf(const uchar* fmt, va_list vap) {
	uchar_format_target ucft;

	/* create the format target */
	ucft.type = UCFT_FILE;
	ucft.remaining = UCFT_INFINITE;
	ucft.written = 0;
	ucft.u.fp = stdout;

	/* do the formatting */
	return uchar_format(&ucft, fmt, vap);
}

int uc_fprintf(FILE* fp, const uchar* fmt, ...) {
	int ret;
	va_list vap;
	uchar_format_target ucft;

	/* create the format target */
	ucft.type = UCFT_FILE;
	ucft.remaining = UCFT_INFINITE;
	ucft.written = 0;
	ucft.u.fp = fp;

	/* do the formatting */
	va_start(vap, fmt);
	ret = uchar_format(&ucft, fmt, vap);
	va_end(vap);
	return ret;
}

int uc_vfprintf(FILE* fp, const uchar* fmt, va_list vap) {
	uchar_format_target ucft;

	/* create the format target */
	ucft.type = UCFT_FILE;
	ucft.remaining = UCFT_INFINITE;
	ucft.written = 0;
	ucft.u.fp = fp;

	/* do the formatting */
	return uchar_format(&ucft, fmt, vap);
}

uchar* uc_lwr(uchar* s) {
	/* Does not handle surrogates properly as this may require
     the string to expand
   */
	uchar* p;
	for (p = s; *p; ++p) *p = (uchar)uc_tolower(*p);
	return s;
}

uchar* uc_upr(uchar* s) {
	uchar* p;
	for (p = s; *p; ++p) *p = (uchar)uc_toupper(*p);
	return s;
}

uchar* uc_str(const uchar* str, const uchar* search) {
	const uchar* p;

	if (!*search) return (uchar*)str;

	for (p = str; *p; ++p) {
		const uchar *s1 = p, *s2 = search;

		while (*s1 && *s2 && *s1 == *s2) ++s1, ++s2;

		if (!*s2) return (uchar*)p;
	}

	return 0;
}

#endif /* defined(_MSC_VER) */

/* TODO: MSVC surrogates issue */
uchar* uc_istr(const uchar* str, const uchar* search) {
	const uchar* p;
	uchar32 uct, uc1, uc2;

	if (!*search) return (uchar*)str;

	for (p = str; *p; ++p) {
		const uchar *s1 = p, *s2 = search;

		/* no, go through handling surrogates */
		while (*s1 && *s2) {
			/* extract characters */
			uc1 = *s1++;

			/* handle surrogates, treating junk as as single codepoint */
			if (uc1 >= 0xD800 && uc1 <= 0xDBFF && *s1) {
				uct = *s1;
				if (uct >= 0xDC00 && uct <= 0xDFFF) {
					++s1;
					uc1 = (uc1 & 0x3FF) << 10 | (uct & 0x3FF) + 0x10000;
				}
			}

			uc2 = *s2++;
			if (uc2 >= 0xD800 && uc2 <= 0xDC00 && *s2) {
				uct = *s2;
				if (uct >= 0xDC00 && uct <= 0xDFFF) {
					++s2;
					uc2 = (uc2 & 0x3FF) << 10 | (uct & 0x3FF) + 0x10000;
				}
			}

			/* check for match and return marked position
              n.b. surrogate handling is broken under windows anyway, oh well
              it will do for the time being
       */
			if (!(uc_tolower(uc1) == uc_tolower(uc2))) break;

			if (!*s2) return (uchar*)p;
		}
	}

	return 0;
}

/* strrchr accounting for surrogates */
uchar* uc_rchr(const uchar* s, uchar32 srch) {
	const uchar* p = s + uc_len(s);

	/* easy case? */
	if (srch <= 0xFFFF) {
		/* treating all as single utf-16 values will work reasonably */
		while (p > s && p[-1] != srch) --p;
		return p > s ? (uchar*)(p - 1) : NULL;
	}
	/* no, go through handling surrogates */
	while (p > s) {
		/* extract character */
		uchar32 uc = *(--p);

		/* handle surrogates, discarding junk */
		if (uc >= 0xD800 && uc <= 0xDFFF) {
			uchar32 uc2 = uc;

			if (uc2 < 0xDC00 || p == s) continue; /* junk */
			uc = *(--p);

			if (uc >= 0xDC00 || !*s) /* junk */
				continue;
			if (uc < 0xD800 || uc > 0xDBFF) /* junk */
				continue;
			uc = (uc & 0x3FF) << 10 | (uc2 & 0x3FF) + 0x10000;
		}

		/* check for match and return marked position */
		if (uc == srch) return (uchar*)p;
	}
	return NULL;
}
