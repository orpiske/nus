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
#ifndef NKEYPAIR_HPP_
#define NKEYPAIR_HPP_

/**
\file nkeypair.hpp Struct definition for NKeyPair structure
*/


/**
\struct NKeyPair 
\brief Implements a Key/Pair struture
*/
template<typename T, typename V>
struct NKeyPair { 
	T key;		/*!< Key name */
	V value;	/*!< Key value */
};

#endif // NKEYPAIR_HPP_