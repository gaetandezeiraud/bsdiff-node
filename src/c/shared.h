/*
**	MIT License
**
**	Copyright (c) 2018-2019 Exoway
**
**	Permission is hereby granted, free of charge, to any person obtaining a copy
**	of this software and associated documentation files (the "Software"), to deal
**	in the Software without restriction, including without limitation the rights
**	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
**	copies of the Software, and to permit persons to whom the Software is
**	furnished to do so, subject to the following conditions:
**
**	The above copyright notice and this permission notice shall be included in all
**	copies or substantial portions of the Software.
**
**	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
**	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
**	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
**	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
**	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
**	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
**	SOFTWARE.
**
*/

#ifndef SHARED_H
#define SHARED_H

#include "bzlib.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <io.h>
	#include "../err.h"

	typedef unsigned char u_char;
	typedef signed int ssize_t;

	#define OPEN_FLAGS O_RDONLY|O_BINARY|O_NOINHERIT
	#define OPEN_FLAGS_CREATE O_CREAT|O_TRUNC|O_WRONLY|O_BINARY
	#define FOPEN_READ_FLAGS "rb"
	#define FOPEN_WRITE_FLAGS "wb"
#else
    #include <unistd.h>
    #include <err.h>

	#define OPEN_FLAGS O_RDONLY
	#define OPEN_FLAGS_CREATE O_CREAT|O_TRUNC|O_WRONLY
	#define FOPEN_READ_FLAGS "r"
	#define FOPEN_WRITE_FLAGS "w"
#endif

typedef long long unsigned int size_header;
typedef struct	s_header
{
	char		magic[8];
	size_header		bzctrllen;
	size_header		bzdatalen;
	size_header		newsize;
}				t_header;

#endif
