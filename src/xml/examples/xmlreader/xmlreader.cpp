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
#include "xmlreader.h"

XmlReader::XmlReader(void)
	: NObject(),
	m_filename(),
	m_schema_dtd(),
	m_search_str(),
	m_print(false),
	m_reader(NULL),
	m_doc(NULL),
	m_parser_type(NXmlAbstractParser::XMLNOPARSING)
{

}

XmlReader::~XmlReader(void) {

}


// Sets the filename of the xml file to be parsed
bool XmlReader::setFilename(const NOpt<XmlReader> &opt) { 
	m_filename = opt.getValues().at(0);
	

	return true;
}


// Sets the filename of the schema file to be parsed
bool XmlReader::setSchema(const NOpt<XmlReader> &opt) {
	m_schema_dtd = opt.getValues().at(0);
	m_parser_type = NXmlAbstractParser::XMLSCHEMA;

	return true;
}


// Sets the filename of the dtd file to be parsed
bool XmlReader::setDtd(const NOpt<XmlReader> &opt) { 
	m_schema_dtd = opt.getValues().at(0);
	m_parser_type = NXmlAbstractParser::XMLDTD;
	
	return true;
}


// Sets the flag to print the data of the loaded xml file
bool XmlReader::setPrint(const NOpt<XmlReader> &) {
	m_print = true;
	
	return true;
}


// Sets a search string to look for in the document. This 
// search string must be in the XPath language format. Ex.: //nodename to 
// search for a node.
bool XmlReader::setSearch(const NOpt<XmlReader> &opt) {
	m_search_str = opt.getValues().at(0);

	return true;
}


// Execute the search for the node using the string passed by the -s/--search 
// option. 
void XmlReader::search(void) {
	NXmlNode node;
	
	// If the search is sucessfull it will return a non-null node
	node = m_doc->findNode(m_search_str);
	if (!node.isNull()) {
		NMessage::print() << "You search for: " << m_search_str;
		print(node);
	}
	else { 
		NMessage::print() << "Node " << m_search_str << " not found!";
	}
}


// It's possible to navigate through a given node, descending to it's children
// siblings, etc. 
void XmlReader::print(NXmlNode node) { 
	NMessage::print() << "============= NODE INFORMATION =============";
	
	do { 
		// It's important to test whether the given node is a data node
		// or a text one. If it's a text node it doesn't hold any data 
		// we would want to play with now (ex.: properties, data, etc).
		if (node.isText()) { 
			node = node.getNext();
			continue;
		}

		// Checks whether node has property
		NMessage::print() << "Element: " << node.getName();
		if (node.hasProperty("name")) { 
				NMessage::print() << "\tProperty: " 
						<< node.getProperty("name");
		}

		if (!node.isBlank()) { 
			NMessage::print() << "Data: " << node.getData();
			
		}
		
		if (node.hasChild()) { 
			print(node.getChild());	
		}
		
		node = node.getNext();
	} while (!node.isNull());
}


// Loads the xml file, parsing it if requested.
void XmlReader::load(void) { 
	NMessage::print() << "Loading " << m_filename;

	m_reader = new NXmlReader;
	m_reader->setSchema(m_parser_type);

	// By default it does not parse the xml file against a dtd or a schema,
	// so if it's desired to parse against one of them, it's needed to 
	// inform the path to the dtd/schema file, which can be done using
	// setDefinitionUrl
	if (m_parser_type != NXmlAbstractParser::XMLNOPARSING) { 
		m_reader->setDefinitionUrl(m_schema_dtd);
	}

	// Load the file (and parses it, if it was requested)
	m_reader->load(m_filename);

	// Once loaded and parsed the reader will create a new NXmlDocument
	// which contains the xml document parsed. This document can be 
	// obtained using getDocument() method of the NXmlReader class. 
	// It the document was successfully loaded it will never return a 
	// NULL pointer.
	m_doc = m_reader->getDocument();
	NMessage::print() << "Document successfully loaded";
	
	
	// Do not forget to deallocate the memory used by the NXmlReader object
	delete m_reader;
	
	
}


// Program flow
void XmlReader::run(void) { 
	NXmlNode node;
	load();

	if (m_print) { 
		node = m_doc->getRootNode();
		print(node);
	}
	
	if (m_search_str != "") { 
		search();
	}
}
