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
#include "nxmlschemaparser.h"

/**
\file nxmlschemaparser.cpp NXmlSchemaParser class implementation
*/

NXmlSchemaParser::NXmlSchemaParser(void)
	: NXmlAbstractParser(),
	m_parser_ctxt(NULL),
	m_schema_ptr(NULL),
	m_valid_ctxt(NULL)
{
	NDebug::print() << "Creating ... ";
	xmlInitParser();
}


NXmlSchemaParser::~NXmlSchemaParser(void) { 
	if (m_parser_ctxt) { 
		xmlSchemaFreeParserCtxt(m_parser_ctxt);
	}
	
	if (m_valid_ctxt) { 
		xmlSchemaFreeValidCtxt(m_valid_ctxt);
	}
	
	if (m_schema_ptr) { 
		xmlSchemaFree(m_schema_ptr);
	}
}

void NXmlSchemaParser::parseSchema(void) { 
	m_schema_ptr = xmlSchemaParse(m_parser_ctxt);
	
	xmlSchemaFreeParserCtxt(m_parser_ctxt);
	m_parser_ctxt = NULL;
	
	if (!m_schema_ptr) { 
		throw NXmlError::getLastError("XML schema parsing failed", 
				NXmlException::XML_PARSER_ERROR);
	}
	
	m_valid_ctxt = xmlSchemaNewValidCtxt(m_schema_ptr);
	if (!m_valid_ctxt) { 
		throw NXmlError::getLastError(
				"Unable to create a valid schema context", 
				NXmlException::XML_INIT_ERROR);
	}
	
}


xmlDocPtr NXmlSchemaParser::parse(const NString &filename) { 
	xmlDocPtr ret; 
	
	ret = xmlReadFile(filename.toChar(), NULL, 
				XML_PARSE_NOERROR | XML_PARSE_NOWARNING);
	
	//ret = xmlParseFile(filename.toChar());
	if (!ret) { 
		throw NXmlError::getLastError("XML document parsing failed");
	}
	
	// Create the parser context and do the commom parsing of 
	// xml schema structutures
	m_parser_ctxt = xmlSchemaNewParserCtxt(m_url.toChar());
	if (!m_parser_ctxt) { 
		throw NXmlError::getLastError(
				"Unable to create parser context", 
				NXmlException::XML_INIT_ERROR);
	}
	parseSchema();
	
	// Validate the doc against the schema
	if (xmlSchemaValidateDoc(m_valid_ctxt, ret)) { 
		throw NXmlError::getLastError("XML validation failed",
				NXmlException::XML_PARSER_ERROR);
	}
		
	return ret;
}


xmlDocPtr NXmlSchemaParser::parse(const NString &buffer, const NString &url) { 
	xmlDocPtr ret; 
	
	ret = xmlReadMemory(buffer.toChar(), buffer.length(), url.toChar(),
			    NULL, XML_PARSE_DTDVALID 
				| XML_PARSE_NOERROR 
			        | XML_PARSE_NOWARNING);
	if (!ret) { 
		throw NXmlError::getLastError("XML document parsing failed", 
				NXmlException::XML_PARSER_ERROR);
	}
	
	// Create the parser context and do the commom parsing of 
	// xml schema structutures
	m_parser_ctxt = xmlSchemaNewDocParserCtxt(ret);
	if (!m_parser_ctxt) { 
		throw NXmlError::getLastError("Unable to create parser context",
				NXmlException::XML_INIT_ERROR);
	}
	parseSchema();
	
	// Validate the doc against the schema
	if (xmlSchemaValidateDoc(m_valid_ctxt, ret)) { 
		throw NXmlError::getLastError("XML validation failed",
				NXmlException::XML_PARSER_ERROR);
	}
	
	return ret;
}


xmlDocPtr NXmlSchemaParser::parse(const NFile *file, const NString &url) { 
	xmlDocPtr ret; 
	
	if (!file) { 
		throw NXmlException("Invalid 'file' object: null object", 
				NException::XML, NXmlException::XML_INIT_ERROR);
	}
	
	ret = xmlReadFd(file->handle(), url.toChar(), NULL, 
				XML_PARSE_DTDVALID 
				| XML_PARSE_NOERROR 
			        | XML_PARSE_NOWARNING);
	if (!ret) { 
		throw NXmlError::getLastError("XML document parsing failed",
				NXmlException::XML_PARSER_ERROR);
	}
	
	// Create the parser context and do the commom parsing of 
	// xml schema structutures
	m_parser_ctxt = xmlSchemaNewDocParserCtxt(ret);
	if (!m_parser_ctxt) { 
		throw NXmlError::getLastError("Unable to create parser context",
				NXmlException::XML_INIT_ERROR);
	}
	parseSchema();
	
	// Validate the doc against the schema
	if (xmlSchemaValidateDoc(m_valid_ctxt, ret)) { 
		throw NXmlError::getLastError("XML validation failed", 
				NXmlException::XML_PARSER_ERROR);
	}
	
	return ret;
}
