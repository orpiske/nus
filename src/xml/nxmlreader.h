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
#ifndef NXMLREADER_H
#define NXMLREADER_H

/**
\file nxmlreader.h NXmlReader class definition
\example xmlreader.cpp
\include ex_nxmlreader.cpp
\include xmlreader.h
*/

#include <libxml/xmlreader.h>

#include "ndefs.h"
#include "nstring.h"
#include "nfile.h"
#include "nxmldocument.h"
#include "nexception.h"
#include "nxmlerror.h"
#include "nxmlabstractparser.h"
#include "nxmlparser.h"
#include "nxmlschemaparser.h"

/**
\brief NXmlReader class is used to read xml documents
*/
class DllDeclSpec NXmlReader { 
	public:
		/**
		\brief Constructs a NXmlReader object
		*/
		NXmlReader(void);
		
		/**
		\brief Destroys a NXmlReader object
		*/
		~NXmlReader(void);
		
		
		/**
		\brief Sets the data definition schema used for parsing the 
		document
		*/		
		void setSchema(NXmlAbstractParser::XmlSchema schema);
		
		/**
		\brief Gets the data defintion schema used for parsing the
		document
		\return The data definition schema used for parsing the
		document
		*/
		NXmlAbstractParser::XmlSchema getSchema(void) const;
		
		/**
		\brief Sets the encoding of the document
		\param encoding The encoding of the document
		\note Param encoding is not used if file is parsed against a dtd or schema
		*/
		void setEncoding(const NString &encoding);
		
		/**
		\brief Gets the encoding of the document
		\return The name of the encoding of the document
		*/
		NString getEncoding(void) const;
		
		/**
		\brief Sets the path/url to the data definition schema
		\param url The path to the data definition schema
		*/
		void setDefinitionUrl(const NString &url);
		
		/**
		\brief Gets the path/url to the data definition schema
		\return The path/url to the data definition schema
		*/
		NString getDefinitionUrl(void) const;
		
		/**
		\brief Load a xml document
		\param path The path of a file containing a xml document
		*/
		void load(const NString &path);
		
		/**
		\brief Load a xml document
		\param buffer An in memory buffer containing a xml document
		\param size The size of the buffer
		*/
		void load(const NString &buffer, nint32 size);
		
		/**
		\brief Load a xml document
		\param file An open NFile object containing a xml document
		*/
		void load(const NFile *file);
		
		/**
		\brief Gets a NXmlDocument containing the parsed xml data
		\return A NXmlDocument object containing the parsed xml data
		*/
		NXmlDocument *getDocument(void);
		
	private:
		xmlTextReaderPtr m_reader;
		xmlDocPtr m_doc;
		NXmlDocument *m_xml_doc;
		NXmlAbstractParser::XmlSchema m_schema;
		NXmlAbstractParser *m_parser;
		NString m_url;
		NString m_encoding;
		
		const char *evalEncoding(const NString &encoding);
		void initDocument(void);
		void setupRootElement(void);
		
		void loadNoParse(const NString &path);
		void loadNoParse(const NString &buffer, nint32 size);
		void loadNoParse(const NFile *file);
		
		NXmlReader(const NXmlReader &other);
		NXmlReader &operator=(const NXmlReader &other);
		
		
};

#endif // NXMLREADER_H
