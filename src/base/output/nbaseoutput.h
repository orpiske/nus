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
#ifndef NBASEOUTPUT_H
#define NBASEOUTPUT_H

/**
\file nbaseoutput.h Base class for output message handling
*/

#include "nstring.h"

/**
\brief NBaseOutput is the base class for output message handling
*/
class DllDeclSpec NBaseOutput {
	public:
		/**
		\brief Enumerates the numbering base for the output
		*/
		enum Base {
			HEXADECIMAL, 	/*!< Hexadecimal base */
			DECIMAL,		/*!< Decimal base */
			OCTAL			/*!< Octal base */
		};

		/**
		\brief Constructs a NBaseOutput object
		*/
		NBaseOutput(void);
		
		/**
		\brief Destructor
		*/
		virtual ~NBaseOutput(void);
		
		/**
		\brief Sets the numbering base for the output
		\param base The numbering base acording to the enum Base
		\return A reference to the current object
		*/
		NBaseOutput &setBase(Base base);
	
	protected:
		/**
		\brief Prints a signed integer
		\param val Value
		*/
		void print(nint32 val);
		
		/**
		\brief Prints an unsigned integer
		\param val Value
		*/
		void print(nuint32 val);
		
		
		/**
		\brief Prints a signed long integer
		\param val Value
		*/
		void print(nint64 val);
		
		/**
		\brief Prints an unsigned long integer
		\param val Value
		*/
		void print(nuint64 val);
		
		/**
		\brief Prints a double
		\param d Value
		*/
		static void print(double d);
		
		/**
		\brief Prints a char
		\param c Char
		*/
		static void print(char c);
		
		/**
		\brief Prints a string
		\param str String
		*/
		static void print(const NString &str);
		
		/**
		\brief Prints the address of a pointer
		\param ptr The address of the pointer
		*/
		static void print(const void *ptr);
		
		
		/**
		\brief Prints a char * string
		\param str A pointer to a null terminated string
		\note This avoid the compiler casting a regular, temporary, string
		to a const void pointer, which would cause the 
		print(const void *) method being called
		*/
		static void print(const char *str);
		
		/**
		\brief Prints a string appending a newline at the end of it
		\param str String
		*/
		static void println(const NString &str);
	
	private:
		Base m_base;
};

#endif // NBASEOUTPUT_H
