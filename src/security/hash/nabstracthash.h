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
#ifndef NABSTRACTHASH_H
#define NABSTRACTHASH_H

/**
\file nabstracthash.h NAbstractHash class definition
\example hashapp.cpp 
\include hashapp.h
\include ex_nhashes.cpp 
*/

#include <exception>
#include <new>
#include <openssl/evp.h>

#include "ndefs.h"
#include "nobject.h"
#include "nhash.h"
#include "nstring.h"
#include "ndatastream.h"

class NFile;

/**
\brief NAbstractHash class is the base class definition for hash calculation 
classes
*/
class DllDeclSpec NAbstractHash: public NObject {
	public:
		/**
		\brief Constructs a NAbstractHash object
		*/
		NAbstractHash(void);
		
		/**
		\brief Destroys a NAbstractHash object
		*/
		virtual ~NAbstractHash(void);
		
		/**
		\brief Calculates the hash of a given string
		\param str The string to calculate the hash
		\return A NHash object with the value of the string
		*/ 
		virtual NHash calculate(const NString &str) = 0;
		
		/**
		\brief Calculates the hash of arbitrary data
		\param data The data to be calculated
		\param size Number of bytes to calculate the hash
		\return A NHash object with the value of the string
		*/
		virtual NHash calculate(const NDataStream &data, nint32 size) = 0;
		
		/**
		\brief Calculates the hash of a file
		\param filename The full path to the file to calculate
		\return A NHash object with the value of the string
		*/
		virtual NHash calculateFile(const NString &filename) = 0;
		
		/**
		\brief Calculates the hash of a file
		\param file A pointer to an open NFile object
		\return A NHash object with the value of the string
		*/ 
		virtual NHash calculateFile(NFile *file) = 0;
		
		/**
		\brief Tests whether a string matches a given hash
		\param str The string to be tested
		\param hash The hash to be tested in string format
		\return true if the string matches the hash or false otherwise
		*/
		bool match(const NString &str, const NString &hash);
	
		/**
		\brief Tests whether a string matches a given hash
		\param str The string to be tested
		\param hash The hash to be tested
		\return true if the string matches the hash or false otherwise
		*/	
		bool match(const NString &str, const NHash &hash);
		
		/**
		\brief Tests whether a file matches a given hash
		\param file A pointer to an open NFile object
		\param hash The hash to be tested in string format
		\return true if the string matches the hash or false otherwise
		*/
		bool match(NFile *file, const NString &hash);
		
		/**
		\brief Tests whether a file matches a given hash
		\param file A pointer to an open NFile object
		\param hash The hash to be tested
		\return true if the string matches the hash or false otherwise
		*/
		bool match(NFile *file, const NHash &hash);
		
	protected:
		/**
		\brief Initialiazes the hash structures
		\param hash_name The name of the hash
		\note Acceptable values for hash_name: md2, md4, md5, sha, sha1, 
		rmd160 (class not implemented)
		*/
		void init(const NString &hash_name);
		
		/**
		\brief Updates the hash structures by computing the hash of more data
		\param data The data to be computed
		\param bytes Number of bytes to compute
		\return The number of bytes computed
		*/
		int update(const void *data, int bytes);
		
		/**
		\brief Clear the hash structures and return the result
		\return The resulting hash as a pointer to a NULL terminated structure
		*/
		NString cleanup(void);
		
		/**
		\brief Sets the size of the internal buffer used to calculate the hash
		\param size The size of the internal buffer
		*/
		void setHashBufferSize(int size);
		
		/**
		\brief Gets the size of the internal buffer used to calculate the hash
		\return The size of the internal buffer
		*/
		int getHashBufferSize(void) const;
	
	private:
		EVP_MD_CTX m_digest_context;
		const EVP_MD *m_message_digest;
		int m_total;
		int m_hash_buffer_size;
		
		NAbstractHash(const NAbstractHash &other);
		NAbstractHash &operator=(const NAbstractHash &rhs);
		
		/**
		\brief Clear the hash structures and return the result
		\return The resulting hash as a pointer to a NULL terminated structure
		*/
		char *p_cleanup(void);
};

#endif // NABSTRACTHASH_H
