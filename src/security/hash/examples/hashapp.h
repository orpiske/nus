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
#ifndef HASHAPP_H
#define HASHAPP_H

#include "ndefs.h"
#include "nobject.h"
#include "nopt.h"
#include "nabstracthash.h"
#include "nmd5hash.h"
#include "nmd4hash.h"
#include "nmd2hash.h"
#include "nshahash.h"
#include "nsha1hash.h"

class HashApp: public NObject {
	enum Hashes {
		MD2,
		MD4,
		MD5,
		SHA,
		SHA1
	};
	
	enum Object {
		FILE_OBJ,
		STRING_OBJ
	};
		
	enum Actions {
		CALCULATE,
		COMPARE
	};
		
	public:
		HashApp(void);
		~HashApp(void);
		
		bool setHash(const NOpt<HashApp> &opt);
		bool compare(const NOpt<HashApp> &opt);
		bool calculate(const NOpt<HashApp> &opt);
		
		bool setFileObj(const NOpt<HashApp> &opt);
		bool setStringObj(const NOpt<HashApp> &opt);
		
		void run(void);
		
	private:
		NAbstractHash *m_hash_obj;
		Hashes m_hash_type;
		Actions m_action;
		Object m_object;
		NString m_object_name;
		NString m_object_hash;
		
		void execCompare(void);
		void execCalculate(void);
		
		HashApp(const HashApp &other);
		HashApp &operator=(const HashApp &rhs);
};

#endif // HASHAPP_H
