// LICENSE: (Please see the file COPYING for details)
//
// NUS - Nemesis Utilities System: A C++ application development framework 
// Copyright (C) 2006, 2008 Otavio Rodolfo Piske
//
//  This file is part of NUS
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation version 2.1
//  of the License.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
#ifndef NMEMUTIL_H
#define NMEMUTIL_H

/**
\file nmemutil.h Memory utilities
*/

#include <cstring>

/**
\brief Concatenate two different areas of memory
\param dest A pointer to the destination
\param pos Position at "dest" where to start the concatenation
\param src A pointer a source
\param len The length, in bytes, of the source
*/
inline void memcat(void *dest, unsigned int pos, const void *src, unsigned int len) {
	memcpy(static_cast<char *>(dest) + pos, src, len);
}

#endif // NMEMUTIL_H
