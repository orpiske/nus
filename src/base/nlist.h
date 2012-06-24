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
#ifndef NLIST_H
#define NLIST_H

/**
\file nlist.h NList header
*/

// Holy shit! Try to avoid this: 
// error C2373: 'NList<T>::constBegin' : redefinition; different type modifiers
//
// Am I doing something wrong ?

#ifdef _MSC_VER
 #define NLISTITERATOR_CONST typename const NList<T>::iterator
#else
 #define NLISTITERATOR_CONST typename NList<T>::const_iterator
#endif

#include "ndefs.h"
#include "nlistnode.h"
#include "nlist.hpp"

#undef NLISTITERATOR_CONST

#endif // NLIST_H
