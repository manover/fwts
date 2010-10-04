/*
 * Copyright (C) 2010 Canonical
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "fwts.h"

static char *format_line(char *start, const char *end, const int width)
{
	int maxlen;
	char *buffer;
	char *bufptr;

	maxlen = end - start;
	if (maxlen < width)
		maxlen = width;

	if ((bufptr = buffer = calloc(1, maxlen + 1)) == NULL)
		return NULL;

	while (*start && start < end)
		*bufptr++ = *start++;

	*bufptr = '\0';

	return buffer;
}

static char *format_remove_multiple_spaces(char *text)
{
	char *buffer;
	char *bufptr1, *bufptr2;

	if ((bufptr1 = bufptr2 = buffer = strdup(text)) == NULL)
		return NULL;

	while (*bufptr1) {
		if (isspace(*bufptr1)) {
			while (*bufptr1 && isspace(*bufptr1))
				bufptr1++;
			*bufptr2++ = ' ';
		}
		else
			*bufptr2++ = *bufptr1++;
	}
	*bufptr2 = '\0';

	return buffer;
}

fwts_list *fwts_format_text(char *text, const int width)
{
	int linelen = 0;
	char *lastspace = NULL;
	char *tidied_text;
	char *linestart;
	char *textptr;
	char *tmp;

	fwts_list *list;

	if ((list = fwts_text_list_init()) == NULL)
		return NULL;

	if ((textptr = tidied_text = format_remove_multiple_spaces(text)) == NULL) {
		fwts_list_free(list, free);
		return NULL;
	}
	
	linestart = tidied_text;

	while (*textptr) {
		if (isspace(*textptr) || 
		    ((lastspace != NULL) && (*(textptr-1) != '/') && (*textptr == '/')) ||
		    (*textptr == ':') || 
		    (*textptr == ';') || 
		    (*textptr == ','))
			lastspace = textptr;

		if (linelen >= width)
			if (lastspace != NULL) {
				if ((tmp = format_line(linestart, lastspace, width)) == NULL) {
					fwts_text_list_free(list);
					return NULL;
				}
				fwts_text_list_append(list, tmp);
				free(tmp);

				
				linestart = lastspace + ((isspace(*lastspace)) ? 1 : 0);
				linelen = textptr - linestart;
				lastspace = NULL;
			}

		textptr++;
		linelen++;
	}
	if ((tmp = format_line(linestart, textptr, width)) == NULL) {
		fwts_text_list_free(list);
		return NULL;
	}
	fwts_text_list_append(list, tmp);
	free(tmp);
	free(tidied_text);
	
	return list;
}
