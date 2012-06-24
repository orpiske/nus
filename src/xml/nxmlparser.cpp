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
#include "nxmlparser.h"

/**
\file nxmlparser.cpp NXmlParser class implementation
*/

NXmlParser::NXmlParser(void)
	: NXmlAbstractParser(),
	m_parser_ctxt(NULL)
{
	NDebug::print() << "Creating ... ";
	xmlInitParser();
	m_parser_ctxt = xmlNewParserCtxt();
	if (!m_parser_ctxt) { 
		throw NXmlError::getLastError("Unable to create parser context",
			NXmlException::XML_PARSER_ERROR);
	}
	NDebug::print() << "Done creating ... ";
}

NXmlParser::~NXmlParser(void) { 
	xmlFreeParserCtxt(m_parser_ctxt);
}

xmlDocPtr NXmlParser::parse(const NString &filename) { 
	xmlDocPtr ret = NULL;
	const char *enc = NULL;
	
	if (!m_encoding.isNull()) {
		enc = m_encoding.toChar();
	}
	
	NDebug::print() << "Parsing ... ";
	
	// XML_PARSE_NOERROR makes the libxml parser be silent about error
	// reporting ... after all, it's our job to report them upstream.
	ret = xmlCtxtReadFile(m_parser_ctxt, filename.toChar(), enc,
			      XML_PARSE_DTDVALID 
				| XML_PARSE_NOERROR 
				| XML_PARSE_NOWARNING);
	if (!ret || m_parser_ctxt->valid == 0) { 
		throw NXmlError::getLastError("XML validation failed", 
				NXmlException::XML_PARSER_ERROR);
	}
	
	return ret;
}


xmlDocPtr NXmlParser::parse(const NString &buffer, const NString &url) {
	xmlDocPtr ret = NULL;
	const char *enc = NULL;
	
	if (!m_encoding.isNull()) {
		enc = m_encoding.toChar();
	}
	
	ret = xmlCtxtReadMemory(m_parser_ctxt, buffer.toChar(), buffer.length(),
				url.toChar(), enc, 
				XML_PARSE_DTDVALID 
				| XML_PARSE_NOERROR 
			        | XML_PARSE_NOWARNING);
	return ret;
}


xmlDocPtr NXmlParser::parse(const NFile *file, const NString &url) { 
	xmlDocPtr ret = NULL;
	const char *enc = NULL;
	
	if (!file) { 
		throw NXmlException("Invalid 'file' object: null object", 
			NException::XML, NXmlException::XML_INIT_ERROR);
	}
	
	if (!m_encoding.isNull()) {
		enc = m_encoding.toChar();
	}
	
	ret = xmlCtxtReadFd(m_parser_ctxt, file->handle(), url.toChar(),
				enc, XML_PARSE_DTDVALID);
	return ret;
}
