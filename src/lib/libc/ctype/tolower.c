/*
 * Copyright(C) 2016 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * This file is part of Nanvix.
 * 
 * Nanvix is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Nanvix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Nanvix. If not, see <http://www.gnu.org/licenses/>.
 */

#include <_ansi.h>
#include <ctype.h>
#if defined (_MB_EXTENDED_CHARSETS_ISO) || defined (_MB_EXTENDED_CHARSETS_WINDOWS)
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>
#include <wchar.h>
#endif

/**
 * @brief Transliterates uppercase characters to lowercase. 
 *
 * @details If @p c represents an uppercase letter, and there exists a
 * corresponding lowercase letter as defined by character type
 * information in the current locale, the result is the corresponding
 * lowercase letter.
 *
 * @param Character to transliterate.
 *
 * @returns Returns the lowercase letter corresponding to the argument
 * passed; otherwise, they returns the argument unchanged.
 */
int tolower(int c)
{
#if defined (_MB_EXTENDED_CHARSETS_ISO) || defined (_MB_EXTENDED_CHARSETS_WINDOWS)
  if ((unsigned char) c <= 0x7f) 
    return isupper (c) ? c - 'A' + 'a' : c;
  else if (c != EOF && MB_CUR_MAX == 1 && isupper (c))
    {
      char s[MB_LEN_MAX] = { c, '\0' };
      wchar_t wc;
      if (mbtowc (&wc, s, 1) >= 0
	  && wctomb (s, (wchar_t) towlower ((wint_t) wc)) == 1)
	c = (unsigned char) s[0];
    }
  return c;
#else
  return isupper(c) ? (c) - 'A' + 'a' : c;
#endif
}
