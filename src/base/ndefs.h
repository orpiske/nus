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
#ifndef NDEFS_H
#define NDEFS_H

#if defined (_MSC_VER) 
# define _CRT_SECURE_NO_DEPRECATE 1
# define _CRT_SECURE_NO_WARNINGS 1
#endif // defined (_MSC_VER)

#if defined(NLIB_SHARED) && defined(WIN32)
# define DllDeclSpec __declspec( dllexport ) /*!< Export/linkage declaration used in Windows for exporting symbols */
#else
#  define DllDeclSpec /*!< Export/linkage declaration used in Windows for exporting symbols */
#endif // !defined(NLIB_SHARED) && defined(WIN32)


/**
\see See http://msdn2.microsoft.com/en-us/library/dabb5z75.aspx for details
*/

#include <cassert>
#include "errdefs.h"


/**
\file ndefs.h Basic definitions for the library
*/


/**
\brief The size of a kilobyte
*/
#define KB 1024

/**
\brief The size of a megabyte
*/
#define MB 1024*KB

/**
\typedef nuint64 
\brief 64bit unsigned long integer
*/
typedef unsigned long long int nuint64;

/**
\typedef nint64 
\brief 64bit signed long integer
*/
typedef long long int nint64;

/**
\typedef nuint32
\brief 32bit unsigned integer
*/
typedef unsigned int nuint32;

/**
\typedef nint32
\brief 32bit signed integer
*/
typedef int nint32;

/**
\typedef nuint16
\brief 16bit unsigned short integer
*/
typedef unsigned short int nuint16;

/**
\typedef nint16
\brief 16bit signed short integer
*/
typedef short int nint16;

#endif // NDEFS_H
