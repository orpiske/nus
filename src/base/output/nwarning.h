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
#ifndef NWARNING_H
#define NWARNING_H

/**
\file nwarning.h Class definition for NWarning
*/

#include "nbaseoutput.h"
#include "nstring.h"
#include "ncolordefs.h"

/**
\brief NWarning class is used for displaying warning messages
*/
class DllDeclSpec NWarning: public NBaseOutput {
	public:
		/**
		\brief Destroys a NWarning object
		*/
		~NWarning(void);
		
		/**
		\brief Starts the displaying of a warning message
		\returns An object to be used to display warning messages
		*/
		static NWarning print(void);
		
		/**
		\brief Prints a signed integer
		\param val Value
		\returns A reference to this
		*/
		NWarning &operator<<(nint32 val);
		
		/**
		\brief Prints an unsigned integer
		\param val Value
		\returns A reference to this
		*/
		NWarning &operator<<(nuint32 val);
		
		/**
		\brief Prints a signed long integer
		\param val Value
		\returns A reference to this
		*/
		NWarning &operator<<(nint64 val);
		
		/**
		\brief Prints an unsigned long integer
		\param val Value
		\returns A reference to this
		*/
		NWarning &operator<<(nuint64 val);
		
		/**
		\brief Prints a double
		\param d Value
		\returns A reference to this
		*/
		NWarning &operator<<(double d);
		
		/**
		\brief Prints a char
		\param c Char
		\returns A reference to this
		*/
		NWarning &operator<<(char c);
		
		/**
		\brief Prints a string
		\param str String
		\returns A reference to this
		*/
		NWarning &operator<<(const NString &str);
		
		/**
		\brief Prints the address of a pointer
		\param ptr The address of the pointer
		\returns A reference to this
		*/
		NWarning &operator<<(const void *ptr);
		
		/**
		\brief Prints a char * string
		\param str A pointer to a null terminated string
		\returns A reference to this
		\note This avoid the compiler casting a regular, temporary, string
		to a const void pointer, which would cause the operator for a 
		const void * being called
		*/
		NWarning &operator<<(const char *str);
	
	protected:
		/**
		\brief Creates a NMessage object
		*/
		NWarning(void);
		
		
		void print(int val);
		void print(double d);
		void print(char c);
		void print(const NString &str);
 		void println(const NString &str);

};

#endif // NWARNING_H
