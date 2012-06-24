// LICENSE: (Please see the file COPYING for details)
//
// NUS - Nemesis Utilities System: A C++ application development framework 
// Copyright (C) 2006, 2007 Otavio Rodolfo Piske
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
#ifndef NXMLEXCEPTION_H
#define NXMLEXCEPTION_H

/**
\file nxmlexception.h Class definition for NXmlException object
*/

#include "ndefs.h"
#include "nexception.h"
#include "nstring.h"

/**
\brief NXmlException is the class for used for throwable xml exceptions
*/
class DllDeclSpec NXmlException: public NException {
	public:
		static const Flag XML_PARSER_ERROR = 1;		/*!< Parser Error */
		static const Flag XML_INIT_ERROR = 2;		/*!< Xml Initialization Error */
		
		/**
		\brief Creates a NXmlException object
		*/
		NXmlException(void);
		
		/**
		\brief Constructs a NXmlException object
		\param desc Exception description
		\param module The module in which the exception occurred
		\param flag An unique id that identifies the error that occurred
		*/
		NXmlException(const NString &desc, Module module, Flag flag);

};

#endif // NXMLEXCEPTION_H
