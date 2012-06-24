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
#ifndef NCOLORDEFS_H
#define NCOLORDEFS_H

/**
\file ncolordefs.h Color definitions for systems that support it
*/

#if !defined(WIN32)

#define BLACK "\x1B[00;30m"
#define RED "\x1B[00;31m"
#define GREEN "\x1B[00;32m"
#define BROWN "\x1B[00;33m"
#define BLUE "\x1B[00;34m"
#define MAGENTA "\x1B[00;35m"
#define CYAN "\x1B[00;36m"
#define WHITE "\x1B[00;37m"

#define LIGHT_BLACK "\x1B[01;30m"
#define LIGHT_RED "\x1B[01;31m"
#define LIGHT_GREEN "\x1B[01;32m"
#define LIGHT_BROWN "\x1B[01;33m"
#define LIGHT_BLUE "\x1B[01;34m"
#define LIGHT_MAGENTA "\x1B[01;35m"
#define LIGHT_CYAN "\x1B[01;36m"
#define LIGHT_WHITE "\x1B[01;37m"

#define BG_BLACK "\x1B[02;40m"
#define BG_RED "\x1B[02;41m"
#define BG_GREEN "\x1B[02;42m"
#define BG_BROWN "\x1B[02;43m"
#define BG_BLUE "\x1B[02;44m"
#define BG_MAGENTA "\x1B[02;45m"
#define BG_CYAN "\x1B[02;46m"
#define BG_WHITE "\x1B[02;47m"

#define RESET "\x1B[00m"

#else 

#define BLACK ""
#define RED ""
#define GREEN ""
#define BROWN ""
#define BLUE ""
#define MAGENTA ""
#define CYAN ""
#define WHITE ""

#define LIGHT_BLACK ""
#define LIGHT_RED ""
#define LIGHT_GREEN ""
#define LIGHT_BROWN ""
#define LIGHT_BLUE ""
#define LIGHT_MAGENTA ""
#define LIGHT_CYAN  ""
#define LIGHT_WHITE ""

#define BG_BLACK ""
#define BG_RED ""
#define BG_GREEN ""
#define BG_BROWN ""
#define BG_BLUE ""
#define BG_MAGENTA ""
#define BG_CYAN  ""
#define BG_WHITE ""

#define RESET ""

#endif // WIN32

#endif // NCOLORDEFS_H
