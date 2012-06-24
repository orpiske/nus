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
#ifndef NSKIPLIST_H
#define NSKIPLIST_H

/**
\file nskiplist.h NSkipList header
*/

#include <climits>

#ifdef _MSC_VER
 #define NSKIPLIST_CONST typename const NSkipList<T>::iterator  /*!< Const iterator type definition */ 
#else
 #define NSKIPLIST_CONST typename NSkipList<T>::const_iterator /*!< Const iterator type definition */ 
#endif

#include "nrand.h"
#include "nexception.h"
#include "noutput.h"

#include "nskipnode.h"
#include "nskiplist.hpp"


#undef NSKIPLIST_CONST

#endif // NSKIPLIST_H
