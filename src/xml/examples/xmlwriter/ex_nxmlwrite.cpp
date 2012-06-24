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
#include "ndefs.h"
#include "nstring.h"
#include "nxmldocument.h"
#include "nxmlnode.h"
#include "nxmlwriter.h"
#include "nmessage.h"
#include "nwarning.h"

int main(void) { 
	NXmlNode root;
	
	NXmlDocument *doc = NULL;
	NXmlWriter *writer = NULL;
	
	NString buffer;
	
	try { 
		// Creates a new XML document with root node "languages"
		doc = new NXmlDocument("languages");
		
		// Gets the root node
		root = doc->getRootNode();
		
		// Creates an NXmlWriter object used to dump the document
		writer = new NXmlWriter(doc);
		
		// Adds an elemente of name tupi-guarani without properties
		root.addChild("tupi-guarani");
		
		// Adds an element of name english with the property country
		// set to usa.
		root.addChild("english").addProperty("country", "usa");
		
		// Same as above, but now with portuguese and brazil
		root.addChild("portuguese").addProperty("country", "brazil");
		
		// Same as above, but now with spanish and argentina
		root.addChild("spanish").addProperty("country", "argentina");
		
		// Adds an element of name esperanto without properties with
		// data set to "International auxiliary language"
		root.addChild("esperanto", "International auxiliary language");
		
		// Dump the XML document to a string buffer
		writer->dump(&buffer, true);
		
		// Displays the XML Document
		NMessage::print() << "============= XML DOCUMENT =============";
		NMessage::print() << buffer;
		
		// Just to show that you can modify the document after you dump
		// it, as long as you dump it again
		root.addChild("japanese");
		writer->dump(&buffer, true);
		
		NMessage::print() << "============= XML DOCUMENT =============";
		NMessage::print() << buffer;
	}
	catch (NException &e) { 
		NWarning::print() << "Error: " << e.getDescription();
	}
	
	delete writer;
	delete doc;
}
