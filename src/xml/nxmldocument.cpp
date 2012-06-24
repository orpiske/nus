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
#include "nxmldocument.h"

/**
\file nxmldocument.cpp NXmlDocument class implementation
*/

NXmlDocument::NXmlDocument(const NString &rootElement)
	: NObject(),
	m_doc(NULL),
	m_root(rootElement),
	m_namespace_list(),
	m_xpath_ctxt(NULL),
	m_xpath_obj(NULL),
	m_pos(-1)
{ 
	init();
}


NXmlDocument::NXmlDocument(void)
	: NObject(),
	m_doc(NULL),
	m_root(NULL),
	m_namespace_list(),
	m_xpath_ctxt(NULL),
	m_xpath_obj(NULL),
	m_pos(-1)
{ 
	
}


NXmlDocument::~NXmlDocument(void) { 
	freeSearchResources();
	if (m_doc) { 
		xmlFreeDoc(m_doc);
	}
	
	// xmlCleanupPaser();
}


void NXmlDocument::init(void) { 

	m_doc = xmlNewDoc(reinterpret_cast<const xmlChar *>("1.0"));
	if (!m_doc) { 
		throw NXmlError::getLastError(
				"Unable to create basic document structure", 
				NXmlException::XML_INIT_ERROR);
	}
	xmlDocSetRootElement(m_doc, m_root.getNode());
}


void NXmlDocument::setRootNode(const NXmlNode &root) { 
	m_root = root;
}


NXmlNode NXmlDocument::getRootNode(void) const {
	return m_root;
}




void NXmlDocument::freeSearchResources(void) const { 
	if (m_xpath_ctxt) { 
		xmlXPathFreeContext(m_xpath_ctxt);
		m_xpath_ctxt = NULL;
	}
	
	if (m_xpath_obj) { 
		xmlXPathFreeObject(m_xpath_obj);
		m_xpath_obj = NULL;
	}
	
	m_pos = -1;
}


void NXmlDocument::createSearchResources(const NString &expr) const { 
	freeSearchResources();
	
	m_xpath_ctxt = xmlXPathNewContext(m_doc);
	if (!m_xpath_ctxt) { 
		throw NXmlError::getLastError("Unable to create search context", 
			NXmlException::XML_INIT_ERROR);
	}
	
	for (nuint64 i = 0; i < m_namespace_list.count(); i++) {
		NXmlNameSpace ns = m_namespace_list.at(i);

		NDebug::print() << "Registering: " << ns.key << ":" << ns.value;
		registerNamespace(ns.key, ns.value);
	}

	m_xpath_obj = xmlXPathEvalExpression(
			reinterpret_cast<const xmlChar *>(expr.toChar()),
			m_xpath_ctxt);
	
	if (!m_xpath_obj) { 
		freeSearchResources();
		throw NXmlError::getLastError(
				"Unable to evaluate search expression", NXmlException::XML_PARSER_ERROR);
	}
	
	if (xmlXPathNodeSetIsEmpty(m_xpath_obj->nodesetval)) { 
		NDebug::print() << "NodeSet is empty";
	}
}

NXmlNode NXmlDocument::findNode(const NString &name) const {
	createSearchResources(name);
	if (!m_xpath_obj || !m_xpath_obj->nodesetval || m_xpath_obj->nodesetval->nodeNr == 0) {
		NDebug::print() << "Node " << name << " not found!";
		return NXmlNode();
	}

	m_pos = 0;
	return NXmlNode(m_xpath_obj->nodesetval->nodeTab[m_pos]);
}



NXmlNode NXmlDocument::find(const NString &expr) const {
	createSearchResources(expr);
	if (!m_xpath_obj || !m_xpath_obj->nodesetval || m_xpath_obj->nodesetval->nodeNr == 0) {
		NDebug::print() << "No node was found w/ expression " << expr
				<< " not found!";
		return NXmlNode();
	}

	m_pos = 0;
	return NXmlNode(m_xpath_obj->nodesetval->nodeTab[m_pos]);
}


NXmlNode NXmlDocument::next(void) const {
	m_pos++;
	
	if (m_pos <= m_xpath_obj->nodesetval->nodeNr) { 
		NDebug::print() << "Next node not found!";
		return NXmlNode(m_xpath_obj->nodesetval->nodeTab[m_pos]);
	}
	
	return NXmlNode();
}


NXmlNode NXmlDocument::previous(void) const {
	m_pos--;
	
	if (m_pos >= 0) { 
		NDebug::print() << "Previous node not found!";
		return NXmlNode(m_xpath_obj->nodesetval->nodeTab[m_pos]);
	}
	
	return NXmlNode();
}


void NXmlDocument::setXmlDoc(xmlDocPtr doc) { 
	m_doc = doc;
}



xmlDocPtr NXmlDocument::getXmlDoc(void) {
	return m_doc;
}


void NXmlDocument::registerNamespace(const NString &prefix, const NString &ns) const {
	int ret = xmlXPathRegisterNs(m_xpath_ctxt, BAD_CAST prefix.toChar(),
			BAD_CAST ns.toChar());

	if (ret != 0) {
		NString err = "Unable to register namespace ";

		err += ns;
		throw NXmlError::getLastError(err, NXmlException::XML_INIT_ERROR);
	}
}


void NXmlDocument::setNamespaces(const NXmlNameSpaceList &list) const {
	m_namespace_list.copy(list);
}
