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
#include "nexception.h"

/**
\file nexception.cpp NException class implementation
*/

NException::NException(void) : 
		m_description(),
		m_module(NOT_SET),
		m_flag(EX_NONE)
{ }


NException::NException(const NString &description, Module module, Flag flag)
	: m_description(description),
	m_module(module),
	m_flag(flag)
{ 
	
}


NException::~NException(void) { }


void NException::setDescription(const NString &desc) { 
	m_description = desc;
}


NString NException::getDescription(void) const { 
	return m_description;
}


void NException::setModule(NException::Module module) { 
	m_module = module;
}


NException::Module NException::getModule(void) const { 
	return m_module;
}


void NException::setFlag(Flag flag) { 
	m_flag = flag;
}


Flag NException::getFlag(void) const {
	return m_flag;
}


NException &NException::operator=(const NException &rhs) { 
	setDescription(rhs.getDescription());
	setModule(rhs.getModule());
	
	return *this;
}
