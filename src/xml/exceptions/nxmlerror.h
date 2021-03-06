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
#ifndef NXMLERROR_H
#define NXMLERROR_H

/**
\file nxmlerror.h NXmlError class definition
*/

#include <libxml/xmlerror.h>

#include "ndefs.h"
#include "nstring.h"
#include "nexception.h"
#include "nxmlexception.h"


/**
\brief NXmlError class is used to abstract a xml error
\note This class is used only internally on the api an MUST NOT be used for
applications
*/
class DllDeclSpec NXmlError { 
	public:
		/**
		\brief Creates a NXmlError object
		*/
		NXmlError(void);
		
		/**
		\brief Gets the last error reported by the underlying library
		\param msg A message set by the api.
		\param flag An unique id that identifies the error that occurred
		\return A NXmlException object with the message and the details 
		given by the api
		*/
		static NXmlException getLastError(const NString &msg, 
						Flag flag = NXmlException::EX_NONE);
};

#endif // NXMLERROR_H
