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
#include "nsqlrecord.h"

/**
\file nsqlrecord.cpp NSqlRecord class implementation
*/

NSqlRecord::NSqlRecord(void)
	: NObject(),
	m_record()
{

}


NSqlRecord::~NSqlRecord(void) {

}


NVtype NSqlRecord::getData(const NString &rowName) const { 
	if (!m_record.contains(rowName)) { 
		NString msg = "There's no row named ";

		msg += rowName;
		throw NException(msg, NException::DBAL);
	}

	return m_record.value(rowName);
}


void NSqlRecord::add(const NString &rowName, const NVtype &rowData) { 
	assert(rowName != "");
	
	if (m_record.contains(rowName, rowData)) { 
		NWarning::print() << "You're trying to add a value already in "
			<< "the record. Row name: " << rowName << " with value"
			<< rowData.toString();

		NWarning::print() << "Currently this is being ignored";

		return;
	}

	m_record.insert(rowName, rowData);
}
