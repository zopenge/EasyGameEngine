#pragma once

#include <stdlib.h>
#include <locale.h>
#include <limits.h>

#if defined(_PLATFORM_ANDROID_)
#include <sys/sysconf.h>
#elif defined(_PLATFORM_IOS_)
#include <stdlib.h>
#endif

static __inline size_t wcslen_utf16(register const wchar_t *s)
{
	register const wchar_t *rs = s;
	
	while (*rs++ != '\0')
		;
	return (--rs - s);
}

static __inline wchar_t* wcscpy_utf16(register wchar_t *s1, register const wchar_t *s2)
{
	wchar_t  *ret   = s1;
	
	while ((*s1++ = *s2++) != '\0')
		;
	
	return (ret);
}

static __inline wchar_t* wcsncpy_utf16(register wchar_t *s1, register const wchar_t *s2, register size_t len)
{
	wchar_t *ret   = s1;
	
	if (len == 0)
		return (ret);
	
	do {
		if ((*s1++ = *s2++) == '\0')
			break;
	} while (--len > 0);
	
	if (len > 0) {
		while (--len > 0)
			*s1++ = '\0';
	}
	
	return (ret);
}

static __inline wchar_t* wcschr_utf16(register const wchar_t *s, register wchar_t c)
{
	do {
		if (*s == c)
			return ((wchar_t *)s);
	} while (*s++ != '\0');
	
	return (0);
}

static __inline wchar_t* wcsrchr_utf16(register const wchar_t *s, register wchar_t c)
{
	register wchar_t *p = NULL;
	
	do {
		if (*s == c)
			p = (wchar_t *)s;
	} while (*s++ != '\0');
	
	return (p);
}

static __inline wchar_t* wcscat_utf16(register wchar_t *s1, register const wchar_t *s2)
{
	wchar_t  *ret   = s1;
	
	while (*s1++ != '\0')
		;
	s1--;
	while ((*s1++ = *s2++) != '\0')
		;
	return (ret);
}

static __inline size_t wcstombs_utf16(register char *s, register const wchar_t *pwcs, size_t n)
{
	if (n == 0)
	{
		int i = 0;
		for (; pwcs[i] != 0; i ++)
			;

		return i;
	}
	else
	{
		register int i = n;
		while (--i >= 0) {
			if (!(*s++ = (char)*pwcs++))
				break;
		}

		return n - i - 1;
	}
}

static __inline size_t mbstowcs_utf16(register wchar_t *pwcs, register const char *s, size_t n)
{
	register int i = n;
	while (--i >= 0) {
		if (!(*pwcs++ = *s++))
			return n - i - 1;
	}

	return n - i;
}

static __inline int wcscmp_utf16(register const wchar_t  *s1, register const wchar_t  *s2)
{
	if (s1 == s2)
		return (0);
	
	while (*s1 == *s2++) {
		if (*s1++ == '\0')
			return (0);
	}
	
	return (*s1 - *(--s2));
}

static __inline wchar_t* wcsncat_utf16(wchar_t * __restrict s1, const wchar_t * __restrict s2, size_t n)
{
	wchar_t *p;
	wchar_t *q;
	const wchar_t *r;
	
	p = s1;
	while (*p)
		p++;

	q = p;
	r = s2;
	while (*r && n) {
		*q++ = *r++;
		n--;
	}
	
	*q = '\0';
	return s1;
}

static __inline wchar_t* wcstok_utf16(wchar_t * __restrict s, const wchar_t * __restrict delim, wchar_t ** __restrict last)
{
	const wchar_t *spanp;
	wchar_t *tok;
	wchar_t c, sc;
	
	if (s == NULL && (s = *last) == NULL)
		return (NULL);
		
	/*
		0052      * Skip (span) leading delimiters (s += wcsspn(s, delim), sort of).
		0053      */
cont:
	c = *s++;
	for (spanp = delim; (sc = *spanp++) != L'\0';) {
		if (c == sc)
			goto cont;
	}
	
	if (c == L'\0') {   /* no non-delimiter characters */
		*last = NULL;
		return (NULL);
		}
	tok = s - 1;
	
	/*
		0068      * Scan token (scan for delimiters: s += wcscspn(s, delim), sort of).
		0069      * Note that delim must have one NUL; we stop if we see that, too.
		0070      */
	for (;;) {
		c = *s++;
		spanp = delim;
		do {
			if ((sc = *spanp++) == c) {
				if (c == L'\0')
					s = NULL;
				else
					s[-1] = L'\0';
				*last = s;
				return (tok);
			}
		} while (sc != L'\0');
	}

	/* NOTREACHED */
}