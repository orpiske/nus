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
#ifndef NXMLPARSER_H
#define NXMLPARSER_H

#include <libxml/parser.h>

/**
\file nxmlparser.h Class definition for NXmlParser
\example ex_nxmlreader.cpp
\example xmlreader.h
\example xmlreader.cpp
*/

#include "ndefs.h"
#include "nstring.h"
#include "nexception.h"
#include "nxmlabstractparser.h"
#include "nxmlerror.h"
#include "ndebug.h"

/**
\brief NXmlParser class defines the basic operations for DTD Xml data
definition parser
\note You must not use this class directly. It is used internally by the
api
\see NXmlAbstractParser class documentation for details
*/
class DllDeclSpec NXmlParser: public NXmlAbstractParser { 
	public:
		/**
		\brief Constructs a NXmlParser object
		*/
		NXmlParser(void);
		/**
		\brief Destroys a NXmlParser object
		*/
		~NXmlParser(void);
		
		xmlDocPtr parse(const NString &filename);
		xmlDocPtr parse(const NString &buffer, const NString &url);
		xmlDocPtr parse(const NFile *file, const NString &url);
	
	private:
		xmlParserCtxtPtr m_parser_ctxt;
		
		NXmlParser(const NXmlParser &other);
		NXmlParser &operator=(const NXmlParser &rhs);
};

#endif // NXMLPARSER_H
