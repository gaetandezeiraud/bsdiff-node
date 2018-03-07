/*
 * Copyright (C) 2012 Dmitry Marakasov
 *
 * This file is part of tiletool.
 *
 * tiletool is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * tiletool is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with tiletool.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COMPAT_ERR_H
#define COMPAT_ERR_H

#include <stdio.h>
#include <stdlib.h>

#define warn(...) do { fprintf(stderr, __VA_ARGS__); fprintf(stderr, ": %s\n", strerror(errno)); } while (0)
#define warnx(...) do { fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); } while (0)
#define err(eval, ...) do { fprintf(stderr, __VA_ARGS__); fprintf(stderr, ": %s\n", strerror(errno)); return eval; } while (0)
#define errx(eval, ...) do { fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); return eval; } while (0)

#endif