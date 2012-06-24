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
#ifndef NVTYPE_H_
#define NVTYPE_H_

#include "nobject.h"
#include "nstring.h"
#include "ndatastream.h"

class NDataStream;


/**
\file nvtype.h Class definition for NVtype object
*/


/**
\class NVtype 
\brief Abstracts variable data type elements
*/
class DllDeclSpec NVtype { 
	public:
		/**
		\brief Data type stored in the class
		*/
		enum Type { 
			N_VOID,		/*!< Void data type */
			N_CHAR,		/*!< Char data type */
			N_INT32,		/*!< 32 bits signed integer data type */
			N_UINT32,		/*!< 32 bits unsigned integer data type */
			N_INT64,		/*!< 64 bits signed integer data type */
			N_UINT64,		/*!< 64 bits unsigned integer data type */
			N_STRING,		/*!< string data type */
			N_DATASTREAM	/*!< stream data type */
		};
		

		/**
		\brief Constructs a NVtype object
		*/
		NVtype(void);

		/**
		\brief Copy constructor
		\param other Other NVtype object to be copied
		*/
		NVtype(const NVtype &other);

		/**
		\brief Constructs a NVtype object
		\param val Value to assign to the object
		*/
		explicit NVtype(char val);

		/**
		\brief Constructs a NVType object
		\param val Value to assign to the object
		*/
		explicit NVtype(nint32 val);

		/**
		\brief Constructs a NVType object
		\param val Value to assign to the object
		*/
		explicit NVtype(nuint32 val);

		/**
		\brief Constructs a NVType object
		\param val Value to assign to the object
		*/
		explicit NVtype(nint64 val);

		/**
		\brief Constructs a NVType object
		\param val Value to assign to the object
		*/
		explicit NVtype(nuint64 val);

		/**
		\brief Constructs a NVType object
		\param str Value (string) to assign to the object
		*/
		NVtype(const NString &str);


		/**
		\brief Constructs a NVType object
		\param str Value (stream) to assign to the object
		*/
		explicit NVtype(const NDataStream &str);


		/**
		\brief Current datatype of object
		*/
		Type getType() const;


		/**
		\brief Gets the current data as a char
		\return The data as a char
		*/
		char toChar() const;

		/**
		\brief Gets the current data as a signed 32 bit int
		\return The data as an int
		*/
		nint32 toInt32() const;

		/**
		\brief Gets the current data as an unsigned 32 bit int
		\return The data as an int
		*/
		nuint32 toUInt32() const;

		/**
		\brief Gets the current data as a signed 64 bit int
		\return The data as an int
		*/
		nint64 toInt64() const;

		/**
		\brief Gets the current data as an unsigned 64 bit int
		\return The data as an int
		*/
		nuint64 toUInt64() const;

		/**
		\brief Gets the current data as a string
		\return The data as an string
		*/		
		NString toString() const;

		/**
		\brief Gets the current data as a stream of bytes
		\return The data as a stream
		*/
		NDataStream toStream() const;


		/**
		\brief Gets the size of the current data
		\return The size of the current data
		*/
		nuint32 getSize() const;

		/**
		\brief Assignment operator
		\param rhs The object to be copied
		\return A reference to this
		*/
		NVtype &operator=(const NVtype &rhs);

		/**
		\brief Checks whether the current object is equals rhs
		\param rhs The object to be checked if it's equal
		\return True if it's equal or false otherwise
		*/
		bool operator==(const NVtype &rhs) const;
		
		/**
		\brief Checks whether the current object is different than rhs
		\param rhs The object to be checked if it's different
		\return True if it's different or false otherwise
		*/
		bool operator!=(const NVtype &rhs) const;

	private:
		NDataStream m_data;
		Type m_type;
};


#endif // NVTYPE_H_
