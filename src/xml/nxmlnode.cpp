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
#include "nxmlnode.h"

/**
\file nxmlnode.cpp NXmlNode class implementation
*/

NXmlNode::NXmlNode(void)
	: NObject(),
	m_node(NULL)
{ 

}

NXmlNode::NXmlNode(const NString &name)
	: NObject(),
	m_node(NULL)
{
	init(name);
}


NXmlNode::NXmlNode(const NString &name, const NString &data)
	: NObject(),
	m_node(NULL)
{
	init(name);
}

NXmlNode::NXmlNode(const NXmlNode &other)
	: NObject(),
	m_node(NULL)
{
	m_node = other.getNode();
}


NXmlNode::NXmlNode(xmlNodePtr node)
	: NObject(),
	m_node(NULL)
{ 
	m_node = node;
}

NXmlNode::~NXmlNode(void) { 
	
	// Only the root node can release the memory used by the child nodes
	if (m_node && !m_node->parent) { 
		xmlFreeNode(m_node);
	}
}

void NXmlNode::init(const NString &name) { 
	m_node = xmlNewNode(NULL, 
			    reinterpret_cast<const xmlChar *>(name.toChar()));
}

const xmlNodePtr NXmlNode::getNode(void) const { 
	return m_node;
}

void NXmlNode::setName(const NString &name) { 
	if (!m_node) {
		init(name);
	}
	else {
		xmlNodeSetName(m_node, reinterpret_cast<const xmlChar *>(name.toChar()));
	}
}

NString NXmlNode::getName(void) const { 
	NString ret;

	if (m_node) {
		ret = reinterpret_cast<const char *>(m_node->name);
	}
	
	return ret;
}


void NXmlNode::setData(const NString &data) { 
	if (m_node) {
		xmlNodeSetContent(m_node, reinterpret_cast<const xmlChar *>(data.toChar()));
	}
}


NString NXmlNode::getData(void) const {
	NString ret;
	xmlChar *content = NULL;
	
	if (!m_node) {
		return ret;
	}
	
	content = xmlNodeGetContent(m_node);
	if (!content || isBlank()) { 

		NDebug::print() << "The node is blank or NULL";
		if (content) {
			NDebug::print() << "The node is blank" << content << ".";
		}
		return ret;
	}
	
	printf("Content = %s\n", content);
	NDebug::print() << "Value = " << (char *) content << " " << m_node->next;
	ret = reinterpret_cast<const char *>(content);
	xmlFree(content);
	
	return ret;
}

bool NXmlNode::isBlank(void) const { 
	if (xmlIsBlankNode(m_node) == 1) { 
		return true;
	}
	
	return false;
}


bool NXmlNode::isText(void) const {
	if (xmlNodeIsText(m_node) == 1) { 
		return true;
	}
	
	return false;
}


bool NXmlNode::isNull(void) const {
	if (!m_node) {
		return true;
	}
	
	return false;
}

xmlNodePtr NXmlNode::createNode(const NString &name) { 
	xmlNodePtr node;
	
	node = xmlNewNode(NULL, reinterpret_cast<const xmlChar *>(name.toChar()));
	if (!node) {
		throw NXmlError::getLastError(
				"Unable to create a new node to append");
	}
	
	return node;
}


xmlNodePtr NXmlNode::createNode(const NString &name, const NString &data) { 
	xmlNodePtr node;
	
	node = xmlNewNode(NULL, reinterpret_cast<const xmlChar *>(name.toChar()));
	if (!node) { 
		throw NXmlError::getLastError(
				"Unable to create a new node to append");
	}
	
	xmlNodeSetContent(node, reinterpret_cast<const xmlChar *>(data.toChar()));
	
	return node;
}


NXmlNode NXmlNode::addChild(const NString &name) {
	xmlNodePtr node;
	
	if (!m_node) {
		throw NXmlError::getLastError("There's no current node set");
	}
	
	node = createNode(name);
	if (!xmlAddChild(m_node, node)) {
		xmlFreeNode(node); 
		throw NXmlError::getLastError("Unable to add child node");
	}
	
	return NXmlNode(node);
}


NXmlNode NXmlNode::addChild(const NString &name, const NString &data) {
	xmlNodePtr node;
	
	if (!m_node) {
		throw NXmlError::getLastError("There's no current node set");
	}
	
	node = createNode(name, data);
	if (!xmlAddChild(m_node, node)) { 
		xmlFreeNode(node);
		throw NXmlError::getLastError("Unable to add child node");
	}
	
	return NXmlNode(node);
}


NXmlNode NXmlNode::addNextSibling(const NString &name) { 
	xmlNodePtr node;
	
	if (!m_node) {
		throw NXmlError::getLastError("There's no current node set");
	}
	
	node = createNode(name);
	if (!xmlAddNextSibling(m_node, node)) {
		xmlFreeNode(node); 
		throw NXmlError::getLastError("Unable to add child node");
	}
	
	return NXmlNode(node);
}


NXmlNode NXmlNode::addNextSibling(const NString &name, const NString &data) { 
	xmlNodePtr node;
	
	if (!m_node) {
		throw NXmlError::getLastError("There's no current node set");
	}
	
	node = createNode(name, data);
	if (!xmlAddNextSibling(m_node, node)) {
		xmlFreeNode(node); 
		throw NXmlError::getLastError("Unable to add child node");
	}
	
	return NXmlNode(node);
}


NXmlNode NXmlNode::addPreviousSibling(const NString &name) { 
	xmlNodePtr node;
	
	if (!m_node) {
		throw NXmlError::getLastError("There's no current node set");
	}
	
	node = createNode(name);
	if (!xmlAddPrevSibling(m_node, node)) { 
		xmlFreeNode(node);
		throw NXmlError::getLastError("Unable to add child node");
	}
	
	return NXmlNode(node);
}


NXmlNode NXmlNode::addPreviousSibling(const NString &name, const NString &data) { 
	xmlNodePtr node;
	
	if (!m_node) {
		throw NXmlError::getLastError("There's no current node set");
	}
	
	node = createNode(name, data);
	if (!xmlAddPrevSibling(m_node, node)) {
		xmlFreeNode(node); 
		throw NXmlError::getLastError("Unable to add child node");
	}
	
	return NXmlNode(node);
}


bool NXmlNode::hasChild(void) const { 
	return m_node && m_node->children ? true : false;
}

bool NXmlNode::hasLast(void) const { 
	return m_node && m_node->last ? true : false;
}

bool NXmlNode::hasParent(void) const { 
	return m_node && m_node->parent ? true : false;
}

bool NXmlNode::hasNext(void) const { 
	return m_node && m_node->next ? true : false;
}

bool NXmlNode::hasPrevious(void) const { 
	return m_node && m_node->prev ? true : false;
}

NXmlNode NXmlNode::getChild(void) { 
	return NXmlNode(m_node->children);
}


NXmlNode NXmlNode::getLast(void) { 
	return NXmlNode(m_node->last);
}

NXmlNode NXmlNode::getParent(void) { 
	return NXmlNode(m_node->parent);
}


NXmlNode NXmlNode::getNext(void) { 
	return NXmlNode(m_node->next);
}


NXmlNode NXmlNode::getPrevious(void) { 
	return NXmlNode(m_node->prev);
}


const NXmlNode NXmlNode::getChild(void) const { 
	return NXmlNode(m_node->children);
}


const NXmlNode NXmlNode::getLast(void) const { 
	return NXmlNode(m_node->last);
}


const NXmlNode NXmlNode::getParent(void) const { 
	return NXmlNode(m_node->parent);
}


const NXmlNode NXmlNode::getNext(void) const { 
	return NXmlNode(m_node->next);
}


const NXmlNode NXmlNode::getPrevious(void) const { 
	return NXmlNode(m_node->prev);
}


NXmlNode &NXmlNode::addProperty(const NString &name, const NString &data) {
	xmlAttrPtr prop;
	
	if (!m_node) {
		throw NXmlError::getLastError("There's no current node set");
	}
	
	prop = xmlNewProp(m_node, 
			 reinterpret_cast<const xmlChar *>(name.toChar()),
			 reinterpret_cast<const xmlChar *>(data.toChar()));
	if (!prop) { 
		throw NXmlError::getLastError("Unable to add property");
	}
	
	return *this;
}


bool NXmlNode::removeProperty(const NString &name) { 
	NString propName;
	xmlAttrPtr prop = NULL;
	
	
	if (!m_node) {
		return true;
	}
	
	prop = m_node->properties;
	while (prop) { 
		propName = reinterpret_cast<const char *>(prop->name);
		if (name == propName) { 
			xmlRemoveProp(prop);
			return true;
		}
		
		prop = prop->next;
	}
	
	return false;
}


NString NXmlNode::getProperty(const NString &name) const { 
	NString ret;
	const xmlChar *nameX = reinterpret_cast<const xmlChar *>(name.toChar());
	
	if (m_node) {
		ret = reinterpret_cast<const char *>(xmlGetProp(m_node, nameX));
	}
	
	return ret;
}


bool NXmlNode::hasProperty(const NString &name) const { 
	if (m_node && xmlHasProp(m_node, 
	    reinterpret_cast<const xmlChar *>(name.toChar()))) 
	{ 
		return true;
	}
	else { 
		return false;
	}
}

bool NXmlNode::removeChild(void) { 
	if (m_node && m_node->children) {
		xmlFreeNode(m_node->children);
		return true;
	}
	
	return false;
}


bool NXmlNode::removeChild(const NString &name) { 
	NString nodeName;
	xmlNodePtr node = NULL;

	if (!m_node) {
		return false;
	}

	node = m_node->children;
	while (node) { 
		nodeName = reinterpret_cast<const char *>(node->name);
		if (name == nodeName) {
			xmlUnlinkNode(node);
			xmlFreeNode(node);
			
			return true;
		}
		
		node = node->children;
	}

	return false;
}


bool NXmlNode::removeNextSibling(void) { 
	if (m_node && m_node->next) { 
		xmlFreeNode(m_node->next);
		return true;
	}
	
	return false;
}


bool NXmlNode::removeNextSibling(const NString &name) { 
	NString nodeName;
	xmlNodePtr node = NULL;
	
	if (!m_node) {
		return false;
	}
	
	node = m_node->next;
	while (node) { 
		nodeName = reinterpret_cast<const char *>(node->name);
		if (name == nodeName) {
			xmlUnlinkNode(node);
			xmlFreeNode(node);
			
			return true;
		}
		
		node = node->next;
	}

	return false;
}


bool NXmlNode::removePreviousSibling(void) {
	if (m_node && m_node->prev) { 
		xmlFreeNode(m_node->prev);
		return true;
	}
	
	return false;
}


bool NXmlNode::removePreviousSibling(const NString &name) { 
	NString nodeName;
	xmlNodePtr node = NULL;
	
	if (!m_node) {
		return false;
	}

	node = m_node->prev;
	while (node) { 
		nodeName = reinterpret_cast<const char *>(node->name);
		if (name == nodeName) {
			xmlUnlinkNode(node);
			xmlFreeNode(node);
			
			return true;
		}
		
		node = node->prev;
	}

	return false;
}


NXmlNode NXmlNode::find(const NString &name) { 
	NString nodeName;
	xmlNodePtr node = NULL;
	
	if (!m_node) {
		NXmlNode();
	}
	
	node = m_node->children;
	while (node) { 
		nodeName = reinterpret_cast<const char *>(node->name);
		if (name == nodeName) {
			return NXmlNode(node);
		}
		
		node = node->children;
	}

	return NXmlNode();
}


const NXmlNode NXmlNode::find(const NString &name) const { 
	return find(name);
}

NXmlNode NXmlNode::copy(const NXmlNode &other) const { 
	xmlNodePtr node = NULL;
	const int recursive = 1; // Do a recursive copy
	
	if (m_node) {
		node = xmlCopyNode(m_node, recursive);
	}
	
	return NXmlNode(node);
}


NXmlNode &NXmlNode::operator=(const NXmlNode &rhs) { 
	if (m_node && !m_node->parent) { 
		xmlFreeNode(m_node);
	}
	
	m_node = rhs.getNode();
	return *this;
}
