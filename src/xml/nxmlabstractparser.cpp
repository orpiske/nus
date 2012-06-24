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
#include "nxmlabstractparser.h"

/**
\file nxmlabstractparser.cpp NXmlAbstractParser class implementation
*/

NXmlAbstractParser::NXmlAbstractParser(void) 
	: NObject(), 
	m_encoding(),
	m_url()
{ 

}

NXmlAbstractParser::~NXmlAbstractParser(void) {

}


void NXmlAbstractParser::setEncoding(const NString &encoding) { 
	m_encoding = encoding;
}


NString NXmlAbstractParser::getEncoding(void) const { 
	return m_encoding;
}


void NXmlAbstractParser::setDefinitionUrl(const NString &url) {
	m_url = url;
}


NString NXmlAbstractParser::getDefinitionUrl(void) const {
	return m_url;
}

