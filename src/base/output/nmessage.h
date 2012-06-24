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
#ifndef NMESSAGE_H
#define NMESSAGE_H

/**
\file nmessage.h Class definition for NMessage
*/

#include "nbaseoutput.h"
#include "nstring.h"

/**
\brief NMessage class is used for displaying general purpouse messages
*/
class DllDeclSpec NMessage: public NBaseOutput {
	public:
		/**
		\brief Destroys a NMessage object
		*/
		~NMessage(void);
		
		/**
		\brief Starts the displaying of a warning message
		\returns An object to be used to display warning messages
		*/
		static NMessage print(void);
		
		
		/**
		\brief Prints a signed integer
		\param val Value
		\returns A reference to this
		*/
		NMessage &operator<<(nint32 val);
		
		/**
		\brief Prints an unsigned integer
		\param val Value
		\returns A reference to this
		*/
		NMessage &operator<<(nuint32 val);
		
		
		/**
		\brief Prints a signed long integer
		\param val Value
		\returns A reference to this
		*/
		NMessage &operator<<(nint64 val);
		
		/**
		\brief Prints an unsigned long integer
		\param val Value
		\returns A reference to this
		*/
		NMessage &operator<<(nuint64 val);
		
		/**
		\brief Prints a double
		\param d Value
		\returns A reference to this
		*/
		NMessage &operator<<(double d);
		
		/**
		\brief Prints a char
		\param c Char
		\returns A reference to this
		*/
		NMessage &operator<<(char c);
		
		/**
		\brief Prints a string
		\param str String
		\returns A reference to this
		*/
		NMessage &operator<<(const NString &str);
		
		/**
		\brief Prints the address of a pointer
		\param ptr The address of the pointer
		\returns A reference to this
		*/
		NMessage &operator<<(const void *ptr);
		
		/**
		\brief Prints a char * string
		\param str A pointer to a null terminated string
		\returns A reference to this
		\note This avoid the compiler casting a regular, temporary, string
		to a const void pointer, which would cause the operator for a 
		const void * being called
		*/
		NMessage &operator<<(const char *str);
		
	private:
		NMessage(void);
};

#endif // NMESSAGE_H

