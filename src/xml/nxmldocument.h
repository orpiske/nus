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
#ifndef NXMLDOCUMENT_H
#define NXMLDOCUMENT_H

/**
\file nxmldocument.h Class definition for NXmlDocument
\example ex_nxmlreader.cpp
\example xmlreader.h
\example xmlreader.cpp
\example ex_nxmlwrite.cpp
*/
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#include "ndefs.h"
#include "nobject.h"
#include "nexception.h"
#include "nxmlnode.h"
#include "ndebug.h"
#include "nxmlerror.h"
#include "nlist.h"
#include "nkeypair.h"

typedef NKeyPair<NString, NString> NXmlNameSpace;
typedef NList<NXmlNameSpace> NXmlNameSpaceList;

/**
\brief NXmlDocument class abstracts the concept of a XML Document
*/
class DllDeclSpec NXmlDocument: public NObject {
	friend class NXmlReader;
	friend class NXmlWriter;
	
	public:
		/**
		\brief Constructs a NXmlDocument
		\param rootElement The name of the root element
		*/
		NXmlDocument(const NString &rootElement);

		/**
		\brief Destroys a NXmlDocument object releasing any used
		resources
		*/
		~NXmlDocument(void);
		
		/**
		\brief Sets the root node 
		\param root The root node
		*/
		void setRootNode(const NXmlNode &root);
		/**
		\brief Returns a the root element
		\return The the root element or a NULL NXmlNode object if not set
		*/
		NXmlNode getRootNode(void) const;

		
		/**
		\brief Finds a node in the document
		\param name A XPath expression to match the name of the node
		\return The node or a NULL NXmlNode object if not set
		\note Deprecated. Use find();
		*/
		NXmlNode findNode(const NString &name) const;


		/**
		\brief Finds a node in the document
		\param expr A XPath expression to match the name of the node
		\return The node or a NULL NXmlNode object if not set
		\note Deprecated. Use find();
		*/
		NXmlNode find(const NString &expr) const;

		/**
		\brief Once a node is found using findNode, this method
		returns the next node matching the search pattern
		\return The node or a NULL NXmlNode object if not set
		*/
		NXmlNode next(void) const;

		
		/**
		\brief Once a node is found using findNode, this method
		returns the previous node matching the search pattern
		\return The node or a NULL NXmlNode object if not set
		*/
		NXmlNode previous(void) const;

		
		void setNamespaces(const NXmlNameSpaceList &list) const;


	private:
		xmlDocPtr m_doc;
		NXmlNode m_root;
		
		
		mutable NXmlNameSpaceList m_namespace_list;
		mutable xmlXPathContextPtr m_xpath_ctxt;
		mutable xmlXPathObjectPtr m_xpath_obj;
		mutable nint32 m_pos;
		
		void init(void);
		
		void freeSearchResources(void) const;
		void createSearchResources(const NString &expr) const;
		
		// This constructor is used by NXmlReader class which needs to
		// instantiate a NXmlDocument object without a particular 
		// rootElement thus making itself the initialization of the 
		// object
		NXmlDocument(void);
		
		// Methods used by NXmlReader to initialize this class
		void setXmlDoc(xmlDocPtr doc);
		
		
		// This method is used by friend classes to obtain the
		// xmlDocPtr structure that this class abstracts
		xmlDocPtr getXmlDoc(void);
		
		// This methods are not implemented
		NXmlDocument(const NXmlDocument &other);
		NXmlDocument &operator=(const NXmlDocument &other);
		
		/**
		\brief Register namespace
		\param ns Namespace to register
		*/
		void registerNamespace(const NString &prefix, const NString &ns) const;

};

#endif // NXMLDOCUMENT_H
