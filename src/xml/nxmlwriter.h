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
// Echoes wandering down an endless meadow, search for a thing... sublime...
#ifndef NXMLWRITER_H
#define NXMLWRITER_H

/**
\file nxmlwriter.h Class definition for NXmlWriter
\example ex_nxmlwrite.cpp
*/
#include <libxml/xmlwriter.h>

#include "ndefs.h"
#include "nxmlexception.h"
#include "nxmldocument.h"

class NString;
class NFile;


/**
\brief NXmlWriter class is used to output a NXmlDocument to a buffer or a file
*/
class DllDeclSpec NXmlWriter { 
	public:
		/**
		\brief Constructs a NXmlWriter object
		\param doc A NXmlDocument object to be saved
		*/
		NXmlWriter(NXmlDocument *doc);

		/**
		\brief Destroys a NXmlWriter object releasing used resources
		*/
		~NXmlWriter(void);
		
		/**
		\brief Save the XML document to a buffer
		\param buffer A pointer to a NString object to store the XML
		document
		\param indent Whether to indent (true) or not (false).
		\return The number of bytes written
		*/
		nint32 dump(NString *buffer, bool indent);

		/**
		\brief Save the XML document to a file
		\param file A pointer to an open NFile object where the XML
		document will be saved
		\param indent Whether to indent (true) or not (false)
		\return The number of bytes written
		*/
		nint32 dump(NFile *file, bool indent);
		
	private:
		NXmlDocument *m_doc;
		
		NXmlWriter(const NXmlWriter &other);
		NXmlWriter &operator=(const NXmlWriter &rhs);
		
};

#endif // NXMLWRITER_H
