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
#include "nhash.h"

/**
\file nhash.cpp NHash class implementation
*/

NHash::NHash(const NString name, const NString &value)
	: m_name(name),
	m_value(value)
{

}


NHash::NHash(const NHash &other)
	: m_name(other.m_name),
	m_value(other.m_value)
{

}

NString NHash::getName(void) const {
	return m_name;
}


NString NHash::getValue(void) const {
	return m_value;
}


NHash &NHash::operator=(const NHash &rhs) {
	m_name = rhs.getName();
	m_value = rhs.getValue();
	
	return *this;
}


bool NHash::operator==(const NHash &rhs) {
	if (m_name != rhs.m_name) {
		return false;
	}
	
	if (m_value != rhs.m_value) {
		return false;
	}
	
	return true;
}

