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
#ifndef NXMLNODE_H
#define NXMLNODE_H

#include <libxml/tree.h>

/**
\file nxmlnode.h Class definition for NXmlNode object
\example ex_nxmlreader.cpp
\example xmlreader.h
\example xmlreader.cpp
\example ex_nxmlwrite.cpp
*/

#include "ndefs.h"
#include "nobject.h"
#include "nexception.h"
#include "nstring.h"
#include "nexception.h"
#include "nxmlerror.h"
#include "ndebug.h"


/**
\brief NXmlNode class represents the concept of a xml node
\todo Support namespaces
\see http://www.xmlsoft.org/html/libxml-tree.html
*/
class DllDeclSpec NXmlNode: public NObject { 
	// Since I don't want to expose the interface (i.e.: by making the constructor
	// NXmlNode(xmlNodePtr node) public) I set NXmlDocument, NXmlReader and NXmlWriter
	//  our 'friend' classes. TODO: avoid using all this 'friendship'
	friend class NXmlDocument;
	friend class NXmlReader;
	friend class NXmlWriter;
	
	public:
		/**
		\brief Enumerates copy modes for xml nodes
		*/
		enum CopyMode { 
			RECURSIVE,		/*!< Recursively copy nodes */
			NONRECURSIVE	/*!< Non-Recursive copy of nodes */
		};
		
		/**
		\brief Constructs a NXmlNode object
		*/
		NXmlNode(void);
		
		/**
		\brief Constructs a NXmlNode object
		\param name The name of the node
		*/
		NXmlNode(const NString &name);
		
		/**
		\brief Constructs a NXmlNode object
		\param name The name of the node
		\param data The data of the node
		*/
		NXmlNode(const NString &name, const NString &data);
		
		/**
		\brief Constructs a NXmlNode object
		\param other A NXmlNode object which will be copied
		*/
		NXmlNode (const NXmlNode &other);
		
		
		/**
		\brief Destroys a NXmlNode object
		*/
		~NXmlNode(void);
		
		/**
		\brief Sets the name of the node
		\param name The name of the node
		*/
		void setName(const NString &name);	
		
		/**
		\brief Gets the name of the node
		\return The name of the node
		*/
		NString getName(void) const;
		
		/**
		\brief Sets the data of the node
		\param data The data of the node
		*/
		void setData(const NString &data);
		
		/**
		\brief Gets the data of the node
		\return The data of the node
		*/
		NString getData(void) const;
		
		/**
		\brief Returns whether the node is blank or not
		\return True if the node is blank. false otherwise
		*/
		bool isBlank(void) const;
		
		/**
		\brief Returns whether the node holds text data
		\return True if the node holds text data or false otherwise
		*/
		bool isText(void) const;
		
		/**
		\brief Returns whether the node is null or not
		\return True if the node is null. false otherwise
		\note Note that this is different from isBlank. A blank node is 
		a node with no name and (probably) no data. A null node simple 
		does not exist.
		*/
		bool isNull(void) const;
		
		/**
		\brief Adds a child node
		\param name The name of the child node
		\return The child node
		*/
		NXmlNode addChild(const NString &name);
		/**
		\brief Adds a child node
		\param name The name of the child node
		\param data The data of the child node
		\return The child node
		*/
		NXmlNode addChild(const NString &name, const NString &data);
		
		
		/**
		\brief Adds a sibling node
		\param name The name of the node
		\return The sibling node
		*/
		NXmlNode addNextSibling(const NString &name);
		
		/**
		\brief Adds a sibling node
		\param name The name of the sibling node
		\param data The data of the sibling node
		\return The sibling node
		*/
		NXmlNode addNextSibling(const NString &name, const NString &data);
		
		
		/**
		\brief Adds a sibling node
		\param name The name of the sibling node
		\return The sibling node
		*/
		NXmlNode addPreviousSibling(const NString &name);
		
		/**
		\brief Adds a sibling node
		\param name The name of the sibling node
		\param data The data of the sibling node
		\return The sibling node
		*/
		NXmlNode addPreviousSibling(const NString &name, const NString &data);
		
		
		/**
		\brief Gets the first child node
		\return The first child node or a null NXmlNode object if not 
		existant
		*/
		NXmlNode getChild(void);
		
		/**
		\brief Gets the last node
		\return The last node or a null NXmlNode object if not existant
		*/
		NXmlNode getLast(void);
		
		/**
		\brief Gets the parent node
		\return The parent node or a null NXmlNode object if not existant
		*/
		NXmlNode getParent(void);
		
		/**
		\brief Gets the next sibling node
		\return The next sibling node or a null NXmlNode object if not existant
		*/
		NXmlNode getNext(void);
		
		/**
		\brief Gets the previous sibling node
		\return The previous sibling node or a null NXmlNode object if not 
		existant
		*/
		NXmlNode getPrevious(void);
				
		/**
		\brief Returns whether the node has a child or not
		\return True if the node has a child or false otherwise
		*/
		bool hasChild(void) const;
		
		/**
		\brief Returns whether the node has a last node or not
		\return True if the node has a last node or false otherwise
		*/
		bool hasLast(void) const;
		
		/**
		\brief Returns whether the node has a parent node or not
		\return True if the node has a parent node or false otherwise
		\note In most cases will return true, except if the node is the 
		root node
		*/
		bool hasParent(void) const;
		
		/**
		\brief Returns whether the node has a next node or not
		\return True if the node has a next node or false otherwise
		*/
		bool hasNext(void) const;
		
		/**
		\brief Returns whether the node has a previous node or not
		\return True if the node has a previous node or false otherwise
		*/
		bool hasPrevious(void) const;
		
		
		/**
		\brief Gets the first child node
		\return The first child node or a null NXmlNode object if not 
		existant
		*/
		const NXmlNode getChild(void) const;
		
		/**
		\brief Gets the last node
		\return The last node or a null NXmlNode object if not existant
		*/
		const NXmlNode getLast(void) const;
		
		/**
		\brief Gets the parent node
		\return The parent node or a null NXmlNode object if not existant
		*/
		const NXmlNode getParent(void) const;
		
		/**
		\brief Gets the next sibling node
		\return The next sibling node or a null NXmlNode object if not existant
		*/
		const NXmlNode getNext(void) const;
		
		/**
		\brief Gets the previous sibling node
		\return The previous sibling node or a null NXmlNode object if not 
		existant
		*/
		const NXmlNode getPrevious(void) const;
		
		
		/**
		\brief Adds a property to the current object
		\param name The name of the property
		\param data The data of the property
		\return A reference to the current object
		*/
		NXmlNode &addProperty(const NString &name, const NString &data);
		
		/**
		\brief Removes a property of the current node
		\param name The name of the property to be removed
		\return True if the property was removed or false otherwise
		*/
		bool removeProperty(const NString &name);
		
		/**
		\brief Gets a property of the current object
		\param name The name of the property
		\return The data of the property
		*/
		NString getProperty(const NString &name) const;
		
		/**
		\brief Returns whether the current object has a property
		\param name The name of the property
		\return True if the object has the property or false otherwise
		*/
		bool hasProperty(const NString &name) const;
		
		/**
		\brief Removes a child node
		\return True if removed the child (ie. node was found and removed)
		or false otherwise
		*/
		bool removeChild(void);
		
		/**
		\brief Removes a child node
		\param name The name of the child node to be removed
		\return True if removed the child (ie. node  was found and removed)
		or false otherwise
		*/
		bool removeChild(const NString &name);
		
		/**
		\brief Removes a sibling node
		\return True if removed the sibling (ie. node was found and removed)
		or false otherwise
		*/
		bool removeNextSibling(void);
		
		/**
		\brief Removes a sibling node
		\param name The name of the sibling node to be removed
		\return True if removed the sibling (ie. node was found and removed)
		or false otherwise
		*/
		bool removeNextSibling(const NString &name);
		
		/**
		\brief Removes a sibling node
		\return True if removed the sibling (ie. node was found and removed)
		or false otherwise
		*/
		bool removePreviousSibling(void);
		
		/**
		\brief Removes a sibling node
		\param name The name of the sibling node to be removed
		\return True if removed the sibling (ie. node was found and removed)
		or false otherwise
		*/
		bool removePreviousSibling(const NString &name);
		
		
		/**
		\brief Finds a node
		\param name The name of the node
		\return The node or a null NXmlNode object if not found
		*/
		NXmlNode find(const NString &name);
		
		/**
		\brief Finds a node
		\param name The name of the node
		\return The node (const) or a null NXmlNode object if not found
		*/
		const NXmlNode find(const NString &name) const;
		
		
		/**
		\brief Recursively copy a node 
		\param other The node to be copied
		\return A new NXmlNode object with the same data, child, etc as 'other'
		*/
		NXmlNode copy(const NXmlNode &other) const;
		
		
		/**
		\brief Copy a node
		\param rhs The node to be copied
		\return A reference to the current object
		*/
		NXmlNode &operator=(const NXmlNode &rhs);
	private:
		xmlNodePtr m_node;
		
		void init(const NString &name);
		const xmlNodePtr getNode(void) const;
		
		xmlNodePtr createNode(const NString &name);
		xmlNodePtr createNode(const NString &name, const NString &data);
		
		// Used by NXmlDocument and NXmlReader
		NXmlNode(xmlNodePtr node);

};

#endif // NXMLNODE_H
