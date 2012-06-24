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
#include "nxmlwriter.h"

/**
\file nxmlwriter.cpp NXmlWriter class implementation
*/

NXmlWriter::NXmlWriter(NXmlDocument *doc)
	: m_doc(NULL)
{ 
	if (!doc) { 
		throw NXmlException("Invalid XML Document: NULL pointer",
				 NException::XML, NXmlException::XML_INIT_ERROR);
	}
	
	m_doc = doc;
}

NXmlWriter::~NXmlWriter(void) { 

}


nint32 NXmlWriter::dump(NString *buffer, bool indent) {
	int size = 0; 
	xmlTextWriterPtr writer;
	xmlChar *ret;

	if (!buffer) { 
		throw NXmlException("Invalid return buffer: NULL", 
				 NException::XML, NXmlException::XML_INIT_ERROR);
	}
	writer = xmlNewTextWriterTree(m_doc->getXmlDoc(),
					      m_doc->getRootNode().getNode(), 0);
	
	// 
	while (xmlTextWriterEndElement(writer) != -1) {

	}
	xmlTextWriterEndDocument(writer);
	xmlTextWriterFlush(writer);
	
	if (indent) { 
		xmlDocDumpFormatMemory(m_doc->getXmlDoc(), &ret, &size, 1);
	}
	else { 
		xmlDocDumpFormatMemory(m_doc->getXmlDoc(), &ret, &size, 0);
	}
	
	buffer->set(reinterpret_cast<const char *>(ret));
	
	return size;
}

