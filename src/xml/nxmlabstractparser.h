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
#ifndef NXMLABSTRACTPARSER_H
#define NXMLABSTRACTPARSER_H

#include <libxml/parser.h>

/**
\file nxmlabstractparser.h Class definition for NXmlAbstractParser
*/

#include <ndefs.h>
#include <nstring.h>
#include <nfile.h>

/**
\brief NXmlAbstractParser class defines the basic operations for Xml data
definition parsers. 
\note Right now DTD and Xml Schema are the only 2 supported methods for
xml data definition
\note This class is used internally only. DO NOT used on applications
*/
class DllDeclSpec NXmlAbstractParser: public NObject { 
	public:
		/**
		\brief Enumerates the supported data defintion parsers
		*/
		enum XmlSchema {
			XMLNOPARSING,	/*!< Don't do any kind of schema parsing */
			XMLSCHEMA,		/*!< Xml Schema */ 
			XMLDTD		/*!< DTD */
		};
		
		/**
		\brief Constructs a NXmlAbstractParser object
		*/
		NXmlAbstractParser(void);
		
		/**
		\brief Destroys a NXmlAbstractParser object
		*/
		virtual ~NXmlAbstractParser(void);
		
		
		/**
		\brief Sets the encoding of the document to be parsed
		\param encoding The name of the encoding of the document
		\note The name of the encoding is, in fact, the acronymn that 
		identifies it. For example: UTF-8, ISO-8859-1, ISO-8859-15, etc.
		*/		
		void setEncoding(const NString &encoding);
		
		/**
		\brief Gets the encoding set for the document to be parsed
		\return The name of the encoding
		*/
		NString getEncoding(void) const;
		
		/**
		\brief Sets the path/url to the definition data
		\param url The url/path to the definition data
		*/
		virtual void setDefinitionUrl(const NString &url);
		
		/**
		\brief Gets the path/url to the defintion data
		\return The path/url to the definition data
		*/
		NString getDefinitionUrl(void) const;
		
		/**
		\brief Parse a Xml document
		\param filename Filename to the document to be parsed
		\return A xmlDocPtr pointing to the document
		*/
		virtual xmlDocPtr parse(const NString &filename) = 0;
		
		/**
		\brief Parse a Xml Document in memory
		\param buffer The Xml Document to be parsed
		\param url The path/url to the definition data
		\todo Removes the param URL. 
		\return A xmlDocPtr pointing to the document
		*/
		virtual xmlDocPtr parse(const NString &buffer, 
					const NString &url) = 0;
		
		/**
		\brief Parse a Xml Document pointed by a file object
		\param file An open NFile object containing xml data
		\param url The path/url to the definition data
		\todo Removes the param URL. 
		\return A xmlDocPtr pointing to the document
		*/
		virtual xmlDocPtr parse(const NFile *file, 
					const NString &url) = 0;
		
	protected:
		NString m_encoding;	/*!< Document encoding */
		NString m_url;		/*!< Document url */
};

#endif // NXMLABSTRACTPARSER_H
