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
#ifndef XMLREADER_H
#define XMLREADER_H

#include "ndefs.h"
#include "nobject.h"
#include "nxmlnode.h"
#include "nstring.h"
#include "nxmlexception.h"
#include "nmessage.h"
#include "nopt.h"
#include "nxmlabstractparser.h"
#include "nxmlreader.h"

class NXmlDocument;

class XmlReader: public NObject {
	public:
		XmlReader(void);
		~XmlReader(void);
		
		bool setFilename(const NOpt<XmlReader> &opt);
		bool setSchema(const NOpt<XmlReader> &opt);
		bool setDtd(const NOpt<XmlReader> &opt);
		bool setPrint(const NOpt<XmlReader> &);
		bool setSearch(const NOpt<XmlReader> &opt);
		
		void run(void);
		
	private:
		NString m_filename;
		NString m_schema_dtd;
		NString m_search_str;
		bool m_print;
		NXmlReader *m_reader;
		NXmlDocument *m_doc;
		NXmlAbstractParser::XmlSchema m_parser_type;
		
		void load(void);
		void print(NXmlNode node);
		void search(void);
		
		XmlReader(const XmlReader &);
		XmlReader &operator=(const XmlReader &);
};

#endif // XMLREADER_H
