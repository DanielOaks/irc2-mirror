/************************************************************************
 *   IRC - Internet Relay Chat, common/match.c
 *   Copyright (C) 1990 Jarkko Oikarinen
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 1, or (at your option)
 *   any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * $Id: match.c,v 6.1 1991/07/04 21:03:55 gruner stable gruner $
 *
 * $Log: match.c,v $
 * Revision 6.1  1991/07/04  21:03:55  gruner
 * Revision 2.6.1 [released]
 *
 * Revision 6.0  1991/07/04  18:04:49  gruner
 * frozen beta revision 2.6.1
 *
 */

#include "config.h"
#include "common.h"
#include "sys.h"
#include <sys/types.h>

/*
**  Compare if a given string (name) matches the given
**  mask (which can contain wild cards: '*' - match any
**  number of chars, '?' - match any single character.
**
**	return	0, if match
**		1, if no match
*/
int	matches(mask, name)
char	*mask, *name;
    {
	Reg1 u_char m, *msk;
	Reg2 u_char c, *nam;

	msk = (u_char *)mask;
	nam = (u_char *)name;
	for (;; msk++, nam++)
	    {
#ifdef USE_OUR_CTYPE
		m = tolower(*msk);
		c = tolower(*nam);
#else
		m = islower(*msk) ? *msk : tolower(*msk);
		c = islower(*nam) ? *nam : tolower(*nam);
#endif
		if (c == '\0')
			break;
		if (m != '?' && m != c || c == '*')
			break;
	    }
	if (m == '*')
	    {
		for ( ; *msk == '*'; msk++);
		if (*msk == '\0')
			return(0);
		for (; *nam && matches((char *)msk, (char *)nam); nam++);
		return(*nam ? 0 : 1);
	    }
	else
		return ((m == '\0' && c == '\0') ? 0 : 1);
    }
