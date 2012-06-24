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
#ifndef NSQLRECORD_H_
#define NSQLRECORD_H_

#include "nobject.h"
#include "nstring.h"
#include "nvtype.h"
#include "nmap.h"

/**
\file nsqlrecord.h NSqlRecord class definition
*/

/**
\class NSqlRecord
\brief Base class for SQL Record manipulation
*/

class DllDeclSpec NSqlRecord: public NObject {
	friend class NSql;
	public:	
		/**
		\brief Constructs a NSqlRecord object 
		*/
		NSqlRecord(void);

		/**
		\brief Destroys a NSqlRecord object 
		*/
		~NSqlRecord(void);


		/**
		\brief Gets data from the current record
		\param rowName The name of the row containing the data
		*/
		NVtype getData(const NString &rowName) const;

	private:
		NMap<NString, NVtype> m_record;

		/**
		\brief Sets the data of the record
		\param rowName The name of the row
		\param rowData The data of the row
		\note This method is only used from NSql object
		*/
		void add(const NString &rowName, const NVtype &rowData);
};

#endif // NSQLRECORD_H_
