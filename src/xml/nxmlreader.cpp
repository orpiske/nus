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
#include "nxmlreader.h"

/**
\file nxmlreader.cpp NXmlReader class implementation
*/

NXmlReader::NXmlReader(void)
	: m_reader(NULL),
	m_doc(NULL),
	m_xml_doc(NULL),
	m_schema(NXmlAbstractParser::XMLNOPARSING),
	m_parser(NULL),
	m_url(),
	m_encoding()
{
	xmlInitParser();
	xmlInitMemory();
}


NXmlReader::~NXmlReader(void) {
	if (m_parser) { 
		delete m_parser;
	}
}

const char *NXmlReader::evalEncoding(const NString &encoding) { 
	if (encoding == "") { 
		return NULL;
	}
	
	return encoding.toChar();
}


void NXmlReader::setupRootElement(void) { 
	NXmlNode node(xmlDocGetRootElement(m_doc));
	
	m_xml_doc->setRootNode(node);
}


void NXmlReader::setSchema(NXmlAbstractParser::XmlSchema schema) {
	m_schema = schema;
}


NXmlAbstractParser::XmlSchema NXmlReader::getSchema(void) const {
	return m_schema;
}


void NXmlReader::setEncoding(const NString &encoding) { 
	m_encoding = encoding;
}


NString NXmlReader::getEncoding(void) const {
	return m_encoding;
}

void NXmlReader::setDefinitionUrl(const NString &url) {
	m_url = url;
}


NString NXmlReader::getDefinitionUrl(void) const {
	return m_url;
}


NXmlDocument *NXmlReader::getDocument(void) { 
	return m_xml_doc;
}


void NXmlReader::initDocument(void) { 
	m_xml_doc = new NXmlDocument;
	m_xml_doc->setXmlDoc(m_doc);
	
	setupRootElement();
}


void NXmlReader::load(const NString &path) {
	switch (m_schema) { 
		case NXmlAbstractParser::XMLDTD: { 
			m_parser = new NXmlParser;
			m_doc = m_parser->parse(path);
			
			break;
			
		}
		case NXmlAbstractParser::XMLSCHEMA: {
			m_parser = new NXmlSchemaParser;
			
			m_parser->setDefinitionUrl(m_url);
			m_doc = m_parser->parse(path);
			break;
		}
		
		case NXmlAbstractParser::XMLNOPARSING:
		default: { 
			loadNoParse(path);
			break;
		}
	}
		
	initDocument();
}


void NXmlReader::loadNoParse(const NString &path) { 
	m_reader = xmlReaderForFile(path.toChar(), 
				    evalEncoding(m_encoding), 0);
		
	if (!m_reader) { 
		throw NXmlError::getLastError(NSTR("Unable to read from file ")
				+ path, NXmlException::XML_INIT_ERROR);
	}
	
	xmlTextReaderRead(m_reader);
	m_doc = xmlTextReaderCurrentDoc(m_reader);
	
	if (!m_doc) { 
		throw NXmlError::getLastError("Unable to create a xml doc object",
			NXmlException::XML_INIT_ERROR);
	}
}


void NXmlReader::load(const NString &buffer, nint32 size) {
	switch (m_schema) { 
		case NXmlAbstractParser::XMLDTD: { 
			m_parser = new NXmlParser;
			m_doc = m_parser->parse(buffer, m_url);
			
			break;
		}
		case NXmlAbstractParser::XMLSCHEMA: {
			m_parser = new NXmlSchemaParser;
			
			m_parser->setDefinitionUrl(m_url);
			m_doc = m_parser->parse(buffer, m_url);
			
			break;
		}
		
		case NXmlAbstractParser::XMLNOPARSING:
		default: { 
			loadNoParse(buffer, size);
			break;
		}
	}
	
	initDocument();
}


void NXmlReader::loadNoParse(const NString &buffer, nint32 size) {
	if (buffer == "") { 
		NDebug::print() << "The buffer to parse is empty";
	}
	
	m_reader = xmlReaderForMemory(buffer.toChar(), size, m_url.toChar(),
				      evalEncoding(m_encoding), 0);
	
	xmlTextReaderRead(m_reader);
	
	m_doc = xmlTextReaderCurrentDoc(m_reader);
	
	if (!m_doc) { 
		throw NXmlError::getLastError("Unable to create a xml doc object",
				NXmlException::XML_INIT_ERROR);
	}
}


void NXmlReader::load(const NFile *file) {
	switch (m_schema) { 
		case NXmlAbstractParser::XMLDTD: { 
			m_parser = new NXmlParser;
			m_doc = m_parser->parse(file, m_url);
			break;
		}
		case NXmlAbstractParser::XMLSCHEMA: {
			m_parser = new NXmlSchemaParser;
			
			m_parser->setDefinitionUrl(m_url);
			m_doc = m_parser->parse(file, m_url);
			break;
		}
		
		case NXmlAbstractParser::XMLNOPARSING:
		default: { 
			loadNoParse(file);
			break;
		}
	}
	
	initDocument();
} 



void NXmlReader::loadNoParse(const NFile *file) { 
	if (!file) { 
		throw NXmlException("Invalid 'file' object: null object", 
				NException::XML, NXmlException::XML_INIT_ERROR);
	}
	
	m_reader = xmlReaderForFd(file->handle(), m_url.toChar(), 
				  evalEncoding(m_encoding), 0);
	
	if (!m_reader) { 
		throw NXmlError::getLastError("Unable to read from file handle",
			NXmlException::XML_INIT_ERROR);
	}
	
	xmlTextReaderRead(m_reader);
	
	m_doc = xmlTextReaderCurrentDoc(m_reader);
	
	if (!m_doc) { 
		throw NXmlError::getLastError("Unable to create a xml doc object", 
			NXmlException::XML_INIT_ERROR);
	}
}
