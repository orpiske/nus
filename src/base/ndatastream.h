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
#ifndef NDATASTREAM_H
#define NDATASTREAM_H

/**
\file ndatastream.h Class definition for NDataStream object
\example ex_ndatastream.cpp
*/
#include "ndefs.h"
#include "nstring.h"
#include "nbaseexceptions.h"
#include "nmemutil.h"
#include "noutput.h"

/**
\brief NDataStream class provides serialization of raw, binary, data
*/
class DllDeclSpec NDataStream {
	public:
		/**
		\enum ByteOrder Byte ordering for manipulating data
		*/
		enum ByteOrder {
			N_BIG_ENDIAN, 		/*!< Big endian byte ordering */
			N_LITTLE_ENDIAN 	/*!< Little endian byte ordering */
		};

		/**
		\brief Constructs a NDataStream object with no Data
		*/
		NDataStream(void);
		/**
		\brief Copy constructor for NDataStream
		 */
		NDataStream(const NDataStream &stream);
		
		/**
		\brief Copy constructor for NDataStream
		\param str A pointer to a null terminated string
		*/
		NDataStream(const char *str);
		
		
		/**
		\brief Destroys the NDataStream object, freeing any resource allocated
		*/
		~NDataStream(void);

		/**
		\brief Sets the bytes in which data will be serialized
		\note By default it uses BIGENDIAN
		*/
		void setByteOrder(ByteOrder bo);
		
		/**
		\brief Get the current configured byte order
		\return The current configured byte order
		*/
		ByteOrder getByteOrder(void) const;

		/**
		\brief Sets the stream data
		\param src A pointer to a source of data
		\param bytes Size, in bytes, to be written
		\return A reference to the stream
		
		*/
		NDataStream &set(const void *src, nuint32 bytes) ;
		/**
		\brief Sets the stream data
		\param str A pointer to a null terminated string
		\return A reference to the stream
		
		*/
		NDataStream &set(const char *str) ;
		/**
		\brief Sets the stream data
		\param str A NString object
		\return A reference to the stream
		
		*/
		NDataStream &set(const NString &str) ;
		/**
		\brief Sets the stream data
		\param val A 16 bit integer
		\return A reference to the stream
		*/
		NDataStream &set(const nint16 val);
		/**
		\brief Sets the stream data
		\param val A 16 bit unsigned integer
		\return A reference to the stream
		*/
		NDataStream &set(const nuint16 val);
		/**
		\brief Sets the stream data
		\param val A 32 bit integer
		\return A reference to the stream
		*/
		NDataStream &set(const nint32 val);
		/**
		\brief Sets the stream data
		\param val A 32 bit unsigned integer
		\return A reference to the stream
		*/
		NDataStream &set(const nuint32 val);
		/**
		\brief Sets the stream data
		\param val A 64 bit integer
		\return A reference to the stream
		*/
		NDataStream &set(const nint64 val);
		/**
		\brief Sets the stream data
		\param val A 64 bit unsigned integer
		\return A reference to the stream
		*/
		NDataStream &set(const nuint64 val);

		/**
		\brief Appends data to the stream
		\param str A pointer to a null terminated string
		\return A reference to the stream
		
		*/
		NDataStream &append(const char *str) ;
		/**
		\brief Sets the stream data
		\param str A NString object
		\return A reference to the stream
		
		*/
		NDataStream &append(const NString &str) ;
		/**
		\brief Appends data to the stream
		\param src A pointer to a source of data
		\param bytes Size, in bytes, to be written
		\return A reference to the stream
		
		*/
		NDataStream &append(const void *src, nuint32 bytes) ;
		/**
		\brief Appends data to the stream
		\param val A 16 bit integer
		\return A reference to the stream
		*/
		NDataStream &append(const nint16 val);
		/**
		\brief Appends data to the stream
		\param val A 16 bit unsigned integer
		\return A reference to the stream
		*/
		NDataStream &append(const nuint16 val);
		/**
		\brief Appends data to the stream
		\param val A 32 bit integer
		\return A reference to the stream
		*/
		NDataStream &append(const nint32 val);
		/**
		\brief Appends data to the stream
		\param val A 32 bit unsigned integer
		\return A reference to the stream
		*/
		NDataStream &append(const nuint32 val);
		/**
		\brief Appends data to the stream
		\param val A 64 bit integer
		\return A reference to the stream
		*/
		NDataStream &append(const nint64 val);
		/**
		\brief Appends data to the stream
		\param val A 64 bit unsigned integer
		\return A reference to the stream
		*/
		NDataStream &append(const nuint64 val);

		/**
		\brief Converts the stream data to a NString object
		\return A NString object
		*/
		NString toString(void) const;
		/**
		\brief Converts the stream data to a NString object
		\param size Size, in bytes, to be converted
		\return A NString object
		*/
		NString toString(nuint32 size) const;
		/**
		\brief Converts the stream data to a NString object
		\param start Position, to start the convertion
		\param bytes Size, in bytes, to be converted
		\return A NString object
		*/
		NString toString(nuint32 start, nuint32 bytes) const ;

		/**
		\brief Converts the first byte of the stream data to char
		\return The first byte as a char
		*/
		unsigned char toChar(void) const;
		/**
		\brief Converts a byte of the stream data to char
		\param pos Position of the byte to be converted
		\return A byte as a char
		*/
		unsigned char toChar(nuint32 pos) const;

		/**
		\brief Converts the stream to a 16 bit signed integer
		\return A 16 bit signed integer.
		*/
		nint16 toInt16(void) const;
		/**
		\brief Converts the stream to a 32 bit signed integer
		\return A 32 bit signed integer.
		*/
		nint32 toInt32(void) const;
		/**
		\brief Converts the stream to a 64 bit signed integer
		\return A 64 bit signed integer.
		*/
		nint64 toInt64(void) const;
		
		/**
		\brief Returns true if the stream is null
		\return True if the string is null. False otherwise
		*/
		bool isNull(void) const;
		/**
		\brief Returns the size of the stream
		\return The size of the stream
		*/
		nuint32 size(void) const;
		
		/**
		\brief Returns a pointer to the data associated with the stream
		\return Returns the data associated with the stream
		*/
		const void *data(void) const;


		/**
		\brief Equality test
		\param rhs A NDataStream object to compare to
		\return true if equals or false ortherwise
		*/
		bool operator==(const NDataStream &rhs) const;

		/**
		\brief Equality test
		\param rhs A NDataStream object to compare to
		\return false if equals or true ortherwise
		*/
		bool operator!=(const NDataStream &rhs) const;

		/**
		\brief Sets the stream data
		\param str A pointer to a null terminated string
		\return A reference to the stream
		*/
		NDataStream &operator=(const char *str) ;
		
		/**
		\brief Sets the stream data
		\param str A NString object
		\return A reference to the stream
		*/
		NDataStream &operator=(const NString &str) ;
		
		/**
		\brief Sets the stream data
		\param str A NDataStream object
		\return A reference to the stream
		
		*/
		NDataStream &operator=(const NDataStream &str) ;
		/**
		\brief Sets the stream data
		\param val A 16 bit integer
		\return A reference to the stream
		*/
		NDataStream &operator=(const nint16 val);
		/**
		\brief Sets the stream data
		\param val A 16 bit unsigned integer
		\return A reference to the stream
		*/
		NDataStream &operator=(const nuint16 val);
		/**
		\brief Sets the stream data
		\param val A 32 bit integer
		\return A reference to the stream
		*/
		NDataStream &operator=(const nint32 val);
		/**
		\brief Sets the stream data
		\param val A 32 bit unsigned integer
		\return A reference to the stream
		*/
		NDataStream &operator=(const nuint32 val);
		/**
		\brief Sets the stream data
		\param val A 64 bit integer
		\return A reference to the stream
		*/
		NDataStream &operator=(const nint64 val);
		/**
		\brief Sets the stream data
		\param val A 64 bit unsigned integer
		\return A reference to the stream
		*/
		NDataStream &operator=(const nuint64 val);

		/**
		\brief Appends data to the stream
		\param str A pointer to a null terminated string
		\return A reference to the stream
		
		*/
		NDataStream &operator+=(const char *str) ;
		/**
		\brief Sets the stream data
		\param str A NString object
		\return A reference to the stream
		
		*/
		NDataStream &operator+=(const NString &str) ;
		/**
		\brief Appends data to the stream
		\param str A NDataStream object
		\return A reference to the stream
		
		*/
		NDataStream &operator+=(const NDataStream &str) ;
		/**
		\brief Appends data to the stream
		\param val A 16 bit integer
		\return A reference to the stream
		*/
		NDataStream &operator+=(const nint16 val);
		/**
		\brief Appends data to the stream
		\param val A 16 bit unsigned integer
		\return A reference to the stream
		*/
		NDataStream &operator+=(const nuint16 val);
		/**
		\brief Appends data to the stream
		\param val A 32 bit integer
		\return A reference to the stream
		*/
		NDataStream &operator+=(const nint32 val);
		/**
		\brief Appends data to the stream
		\param val A 32 bit unsigned integer
		\return A reference to the stream
		*/
		NDataStream &operator+=(const nuint32 val);
		/**
		\brief Appends data to the stream
		\param val A 64 bit integer
		\return A reference to the stream
		*/
		NDataStream &operator+=(const nint64 val);
		/**
		\brief Appends data to the stream
		\param val A 64 bit unsigned integer
		\return A reference to the stream
		*/
		NDataStream &operator+=(const nuint64 val);

		/**
		\brief Appends data to the stream
		\param str A pointer to a null terminated string
		\return A reference to the stream
		
		*/
		NDataStream operator+(const char *str) ;

		/**
		\brief Sets the stream data
		\param str A NString object
		\return A reference to the stream
		
		*/
		NDataStream operator+(const NString &str) ;
		/**
		\brief Appends data to the stream
		\param str A NDataStream object
		\return A reference to the stream
		
		*/
		NDataStream operator+(const NDataStream &str) ;
		/**
		\brief Appends data to the stream
		\param val A 16 bit integer
		\return A reference to the stream
		*/
		NDataStream operator+(const nint16 val);
		/**
		\brief Appends data to the stream
		\param val A 16 bit unsigned integer
		\return A reference to the stream
		*/
		NDataStream operator+(const nuint16 val);
		/**
		\brief Appends data to the stream
		\param val A 32 bit integer
		\return A reference to the stream
		*/
		NDataStream operator+(const nint32 val);

		/**
		\brief Appends data to the stream
		\param val A 32 bit unsigned integer
		\return A reference to the stream
		*/
		NDataStream operator+(const nuint32 val);
		/**
		\brief Appends data to the stream
		\param val A 64 bit integer
		\return A reference to the stream
		*/
		NDataStream operator+(const nint64 val);
		/**
		\brief Appends data to the stream
		\param val A 64 bit unsigned integer
		\return A reference to the stream
		*/
		NDataStream operator+(const nuint64 val);

		/**
		\brief Converts a byte of the stream data to char
		\param pos Position of the byte to be converted
		\return A byte as a char or 0 if not found or out of 
		bounds
		*/
		unsigned char operator[](nuint32 pos);
	
	private:
		ByteOrder m_bo;
		void *m_data;
		nuint32 m_used;
		nuint32 m_allocated;

		static const nuint32 ALLOC_SIZE = 512;

		void realloc(nuint32 bytes);

		bool needsMemory(nuint32 bytes);
		nuint32 calculateBlocks(nuint32 bytes);
		nuint32 freeBytes(void) const;
		bool withinLimits(nuint32 start, nuint32 bytes) const;
		void memcopy(void *dest);
		
		template<typename T>
		NDataStream &set(T val);

		template<typename T>
		NDataStream &append(T val);

		template<typename T>
		T to(void) const;
};

#endif // NDATASTREAM_H
