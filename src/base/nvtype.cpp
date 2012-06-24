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
#include "nvtype.h"

/**
\file nvtype.cpp NVType class implementation
*/

NVtype::NVtype()
	: m_data(),
	m_type(NVtype::N_VOID)
{ 

}


NVtype::NVtype(const NVtype &other)
	: m_data(),
	m_type(NVtype::N_VOID)
{ 
	m_data = other.m_data;
	m_type = other.m_type;
}

NVtype::NVtype(char val)
	: m_data(),
	m_type(NVtype::N_CHAR)
{ 
	m_data.set(&val, 1);
}


NVtype::NVtype(nint32 val)
	: m_data(),
	m_type(NVtype::N_INT32)
{ 
	m_data.set(val);
}

NVtype::NVtype(nuint32 val)
	: m_data(),
	m_type(NVtype::N_UINT32)
{ 
	m_data.set(val);
}

NVtype::NVtype(nint64 val)
	: m_data(),
	m_type(NVtype::N_INT64)
{ 
	m_data.set(val);
}

NVtype::NVtype(nuint64 val)
	: m_data(),
	m_type(NVtype::N_UINT64)
{ 
	m_data.set(val);
}

NVtype::NVtype(const NString &str)
	: m_data(),
	m_type(NVtype::N_STRING)
{ 
	m_data.set(str);
}

NVtype::NVtype(const NDataStream &str)
	: m_data(),
	m_type(NVtype::N_DATASTREAM)
{ 
	m_data = str;
}

NVtype::Type NVtype::getType() const {
	return m_type;
}

char NVtype::toChar() const {
	return m_data.toChar();
}

nint32 NVtype::toInt32() const {
	return m_data.toInt32();
}

nuint32 NVtype::toUInt32() const {
	return m_data.toInt32();
}

nint64 NVtype::toInt64() const {
	return m_data.toInt64();
}

nuint64 NVtype::toUInt64() const {
	return m_data.toInt64();
}

NString NVtype::toString() const {
	return m_data.toString();
}

NDataStream NVtype::toStream() const {
	return m_data;
}


nuint32 NVtype::getSize() const {
	return m_data.size();
}


NVtype &NVtype::operator=(const NVtype &rhs) { 
	m_data = rhs.m_data;
	m_type = rhs.m_type;

	return *this;
}

bool NVtype::operator==(const NVtype &rhs) const { 
	if (m_type != rhs.m_type) { 
		return false;
	}

	return (m_data == rhs.m_data);
}


bool NVtype::operator!=(const NVtype &rhs) const { 
	if (m_type != rhs.m_type) { 
		return true;
	}

	return (m_data != rhs.m_data);
}

