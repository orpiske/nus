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
#ifndef NSTRING_H
#define NSTRING_H

/**
\file nstring.h Class definition for NString class
\example ex_nstring.cpp
*/

#include "ndefs.h"
#include "nlist.h"

#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <cstdlib>
#include <cctype>

// Ok, I don't like this voodoo. But given the scenario I don't think there
// would be a better way to do this magic.
#undef n_vasprintf
#if defined (_MSC_VER)
#define n_vasprintf(fmt, ap, ret) \
{ \
	int len = (_vscprintf(fmt, ap)) + 1; \
	ret = static_cast<char *>(malloc(len * sizeof(char))); \
	vsprintf_s(ret, len, fmt, ap); \
} /*!< Hack to lower level libc formatting function */
#elif defined(__WIN32) && defined (__GNUC__) || defined (__SVR4)
#define n_vasprintf(fmt, ap, ret) \
{ \
	int max_size = 2048;\
	ret = static_cast<char *>(malloc(max_size));\
	vsnprintf(ret, max_size, fmt, ap); \
}
#else
#define n_vasprintf(fmt, ap, ret) vasprintf(&ret, fmt, ap); /*!< Hack to lower level libc formatting function */
#endif

/**
\brief NString class implements an easy to use, std::string based, string 
 manipulation class
*/
class DllDeclSpec NString {
	public:
		/**
		\brief Constructs an empty NString object
		*/
		NString(void);
	
		/**
		\brief Constructs a NString object setting it to str
		\param str A pointer to a NULL terminated C++ char string
		*/
		NString(const char *str);
		
		/**
		\brief Constructs a NString object setting it to str
		\param str A NString object with the string
		*/
		NString(const NString &str);
		
		/**
		\brief Destroys a NString object releasing the used memory
		*/
		~NString(void);
		
		/**
		\brief Converts a given number to a NString
		\param num A 32 bit integer to be converted
		\return A string with the converted number
		*/
		static NString number(int num);
		
		/**
		\brief Converts a given number to a NString
		\param num A 64 bit integer to be converted
		\return A string with the converted number
		*/
		static NString number(nint64 num);
		
		/**
		\brief Sets the string of the current object
		\param str A pointer to a NULL terminated C++ char string
		\return A reference to this
		*/
		NString &set(const char *str);
		
		/**
		\brief Sets the string of the current object
		\param str A NString object with the string
		\return A reference to this
		*/
		NString &set(const NString &str);
		
		/**
		\brief Converts the string stored by the current object to a 
		char pointer
		\return A pointer to a null terminated char string.
		*/
		const char *toChar() const;

		
		/**
		\brief The current lenght of the string
		\return The lenght of the string
		*/
		unsigned int length() const;
		
		/**
		\brief Checks whether the current string is null (empty)
		\return true if it is null or false otherwise
		*/
		bool isNull() const;
		
		/**
		\brief Appends a string to the current object
		\param str A pointer to a NULL terminated string to be appended
		\param bytes Number of bytes to append to the end of the string
		\return A reference to this
		*/
		NString &append(const char *str, nuint32 bytes);
		
		/**
		\brief Appends a string to the current object
		\param str A pointer to a NULL terminated string to be appended
		\return A reference to this
		*/
		NString &append(const char *str);
		
		/**
		\brief Appends a string to the current object
		\param str A NString object to be appended
		\return A reference to this
		*/
		NString &append(const NString &str);
		
		/**
		\brief Appends a char to the current object
		\param c An ASCII char
		\return A reference to this
		*/
		NString &append(char c);
		
		/**
		\brief Inserts a string at a given position in the string
		\param pos Position where to insert
		\param size Number of bytes, from str, to be inserted into the string
		\param str The string to be inserted
		\return A referece to this
		*/
		NString &insert(nuint32 pos, nuint32 size, const NString str);
		
		/**
		\brief Inserts a string at a given position in the string
		\param pos Position where to insert
		\param str The string to be inserted
		\return A referece to this
		*/
		NString &insert(nuint32 pos, const NString str);

		/**
		\brief Compare the string
		\param pos Initial position (start from 0)
		\param size Number of bytes to compare
		\param str The string to be compared
		\return true if it's equal or false otherwise
		\note If given incorrect values, the method will return false
		*/
		bool compare(nuint32 pos, nuint32 size, const NString &str) const;
		
		
		/**
		\brief Compare the string
		\param pos Initial position (start from 0)
		\param str The string to be compared
		\return true if it's equal or false otherwise
		\note If given incorrect values, the method will return false
		*/
		bool compare(nuint32 pos, const NString &str) const;
		
		/**
		\brief Compare the string
		\param pos Initial position (start from 0)
		\param size Number of bytes to compare
		\param str The string to be compared
		\param str_pos Initial position on string 'str'
		\return true if it's equal or false otherwise
		\note If given incorrect values, the method will return false
		*/
		bool compare(nuint32 pos, nuint32 size, const NString &str, 
				nuint32 str_pos) const;
		
		/**
		\brief Gets a substring
		\param pos Initial position (start from 0)
		\param size Number of bytes to get
		\note Returns a default constructed value if pos and size are not
		valid
		\return A NString object with the substring
		*/
		NString substr(nuint32 pos, nuint32 size) const;


		/**
		\brief Finds a substring starting from a given position
		\param str Substring to find
		\param pos The initial position
		\param ocur The Nth occurrence of the substring to find
		\return The position of the substring or -1 if not found
		*/
		nint32 find(const NString &str, nuint32 pos, nuint32 ocur) const;

		/**
		\brief Finds a substring starting from a given position
		\param str Substring to find
		\param pos The initial position
		\return The position of the substring or -1 if not found
		*/
		nint32 find(const NString &str, nuint32 pos) const;


		/**
		\brief Finds a substring
		\param str Substring to find
		\return The position of the substring or -1 if not found
		*/
		nint32 find(const NString &str) const;


		/**
		\brief Replaces the first ocurrence of 'src' with 'dest'
		\param src String to find
		\param dest String to replace with
		\return A reference to this
		\note This method is case sensitive
		*/
		NString &replace_first(const NString &src, const NString &dest);

		/**
		\brief Replaces part of the string
		\param src String to find
		\param dest String to replace with
		\return A reference to this
		\note This method is case sensitive
		*/
		NString &replace(const NString &src, const NString &dest);

		/**
		\brief Replaces part of the string
		\param src String to find
		\param dest String to replace with
		\param ocur The Nth occurrence to replace
		\return A reference to this
		\note This method is case sensitive
		*/
		NString &replace(const NString &src, const NString &dest, 
			nuint32 ocur);


		/**
		\brief Splits the string
		\param substr The substring to split at
		@return A NList<NString> object containing the substrings
		splitted at substr
		*/
		NList<NString> split(const NString &substr);

		/**
		 \brief Removes all space characters from the right side of the string
		 \return A copy of this
		 */
		NString rtrim();

		/**
		 \brief Removes all space characters from the left side of the string
		 \return A copy of this
		 */
		NString ltrim();

		/**
		 \brief Removes all spaces from the left and right side of the string
		 \return A copy of this
		 */
		NString trim();

		/**
		\brief Appends a string to the current object
		\param str A pointer to a NULL terminated string to be appended
		\return A copy of this
		*/
		
		NString operator+(const char *str);
		/**
		\brief Appends a string to the current object
		\param str A NString object to be appended
		\return A copy of this
		*/
		NString operator+(const NString &str);
		
		/**
		\brief Appends a char to the current object
		\param c An ASCII char
		\return A reference to this
		*/
		NString operator+(char c);
		
		/**
		\brief Appends a string to the current object
		\param str A pointer to a NULL terminated string to be appended
		\return A reference to this
		*/
		NString &operator+=(const char *str);
		
		/**
		\brief Appends a string to the current object
		\param str A NString object to be appended
		\return A reference to this
		*/
		NString &operator+=(const NString &str);
		
		/**
		\brief Appends a char to the current object
		\param c An ASCII char
		\return A reference to this
		*/
		NString &operator+=(char c);
		
		/**
		\brief Access the char at position index
		\param index The position of the char in the string
		\return The char at position index
		*/
		char operator[](unsigned int index) const;
		
		/**
		\brief Checks whether the current object is equals str
		\param str String to be checked against
		\return true if it is equal or false otherwise
		*/
		bool operator==(const NString &str) const;
		
		/**
		\brief Checks whether the current object is not equal to str
		\param str String to be checked against
		\return true if it is not equal or false otherwise
		*/
		bool operator!=(const NString &str) const;
		
		/**
		\brief Checks whether the current object is lexically greater than
		str
		@param str String to be checked against
		\return true if it is lexically greater or false otherwise
		*/
		bool operator>(const NString &str) const;
		
		/**
		\brief Checks whether the current object is lexically less than
		str
		@param str String to be checked against
		\return true if it is lexically less or false otherwise
		*/
		bool operator<(const NString &str) const;
		
		/**
		\brief Checks whether the current object is lexically greater than
		or equals str
		@param str String to be checked against
		\return true if it is lexically greater than or equals str or
		 false otherwise
		*/
		bool operator>=(const NString &str) const;
		
		/**
		\brief Checks whether the current object is lexically less than
		or equals str
		@param str String to be checked against
		\return true if it is lexically less or equals str or false
		otherwise
		*/
		bool operator<=(const NString &str) const;
		
		
		/**
		\brief Sets the string of the current object
		@param str A NString object with the string
		\return A reference to this
		*/
		NString &operator=(const NString &str);

		
		/**
		\brief Provides formatted output to a NString object
		@param fmt Output format
		\note The acceptable format is that used by printf.
		*/
		NString &arg(const char *fmt, ...);

		static const nint32 NOT_FOUND = -1; /*!< Substring not found identified */
		
	private:
		char *m_string;
		nuint32 m_used;
		nuint32 m_allocated;
		static const nuint32 ALLOC_SIZE = 64;
		
		bool needsMemory(nuint32 bytes);
		nuint32 calculateBlocks(nuint32 bytes);
		void memcopy(char *dest);
		nuint32 freeBytes(void) const;
		void realloc(nuint32 bytes);
	
};

/**
\brief Returns a NString object from a char pointer
\param str A pointer to a null terminated char pointer
\return  A NString object
\note It's used, internally, as a shorter way to cast a char pointer to a
NString object
*/
inline NString NSTR(const char *str) { 
	return NString(str);	
}

#endif // NSTRING_H


