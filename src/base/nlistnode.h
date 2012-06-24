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
#ifndef NLISTNODE_H
#define NLISTNODE_H

#include <cstdio>

#include "ndefs.h"


/**
\file nlistnode.h Class definition for NListNode
*/


/**
\brief NListNode abstracts the concept of a linked node and is used by NList and 
NSortedList classes. 
\note This class is used internally and should not be used for other means
*/
template<typename T>
struct NListNode {
	NListNode<T> *previous;		/*!< Previous node */
	NListNode<T> *next;		/*!< Next node */
	T data;				/*!< The data stored by the node */

	/**
	\brief Constructs a NListNode object
	*/
	NListNode(void)
	: previous(NULL),
	next(NULL),
	data()
	{

	}
	
	/**
	\brief Copy constructs a NListNode object
	\param rhs The object to be copied
	*/
	NListNode (const NListNode &rhs) { 
	    previous = rhs.previous;
	    next = rhs.next;
	    data = rhs.data;
	}
	
	
	/**
	\brief Copies a NListNode object
	\param rhs The object to be copied
	*/
	NListNode &operator=(const NListNode &rhs) { 
	    previous = rhs.previous;
	    next = rhs.next;
	    data = rhs.data;

	    return *this;
	}
};


#endif // NLISTNODE_H
