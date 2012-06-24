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
#ifndef NSHA1HASH_H
#define NSHA1HASH_H

/**
\file nsha1hash.h NSha1Hash class definition
\example hashapp.cpp 
\include hashapp.h
\include ex_nhashes.cpp 
*/

#include "ndefs.h"
#include "nabstracthash.h"
#include "nstring.h"
#include "ndatastream.h"
#include "nfile.h"

/**
\brief NSha1Hash class is the class definition for sha1 hash calculation 
algorithm.
\see NAbstractHash for inherited methods
*/
class DllDeclSpec NSha1Hash: public NAbstractHash {
	public:
	
		/**
		\brief Constructs a NSha1Hash object
		*/
		NSha1Hash(void);
		
		/**
		\brief Destroys a NSha1Hash object
		*/
		~NSha1Hash(void);
		
		NHash calculate(const NString &str);
		NHash calculate(const NDataStream &data, nint32 size);
		NHash calculateFile(const NString &filename);
		NHash calculateFile(NFile *file);	
};


#endif // NSHA1HASH_H
