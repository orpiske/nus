// LICENSE: (Please see the file COPYING for details)
//
// NUS - Nemesis Utilities System: A C++ application development framework 
// Copyright (C) 2006, 2007 Otavio Rodolfo Piske
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
#ifndef ERRDEFS_H
#define ERRDEFS_H

/**
\file errdefs.h Error definitions declaration file
*/

#if defined(NLIB_SHARED) && defined(WIN32)
# define DllDeclSpec __declspec( dllexport ) /*!< Export/linkage declaration used in Windows for exporting symbols */
#else
#  define DllDeclSpec  /*!< Export/linkage declaration used in Windows for exporting symbols */
#endif // !defined(NLIB_SHARED) && defined(WIN32)

#include <errno.h>

#define N_FILENOTFOUND "File not found"
#define N_ENOMEM "Not enough memory"
#define N_NULL "Null pointer given"
#define N_OUTOFBOUNDS "Out of bounds exception"


/**
\brief Internally used function to handle the errno variable and error descriptions
\note Do not use
*/
DllDeclSpec const char *nerror(int code);

#endif // ERRDEFS_H
