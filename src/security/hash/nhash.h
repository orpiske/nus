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
#ifndef NHASH_H
#define NHASH_H

/**
\file nhash.h NHash class definition
\see NAbstractHash for examples
*/

#include "ndefs.h"
#include "nstring.h"

/**
\brief NHash is a simple class that abstract the manipulation of criptographic hashes
*/
class DllDeclSpec NHash {
	public:
		/**
		\brief Constructs a NHash object
		\param name The name of the hash
		\param value The value of the hash
		*/
		NHash(const NString name, const NString &value);
		
		/**
		\brief Constructs a NHash object
		\param other Another hash object to be copied
		*/
		NHash(const NHash &other);
		
		/**
		\brief Gets the name of the hash
		\return The name of the hash as a NString object
		*/
		NString getName(void) const;
		
		/**
		\brief Gets the value of the hash
		\return The value of the hash as a NString object
		*/
		NString getValue(void) const;
		
		/**
		\brief Copies one hash to another
		\param rhs Another hash object to be copied
		\return A reference to the current object
		*/
		NHash &operator=(const NHash &rhs);
		
		/**
		\brief Tests the equality of two hashes
		\param rhs Another hash object to be tested against
		\return true if it's equal or false otherwise
		*/
		bool operator==(const NHash &rhs);
		
	private:
		NString m_name;
		NString m_value;
};

#endif // NHASH_H
