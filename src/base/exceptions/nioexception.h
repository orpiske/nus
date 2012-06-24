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
#ifndef NIOEXCEPTION_H
#define NIOEXCEPTION_H

/**
\file nioexception.h Class definition for NIOException object
*/

#include "ndefs.h"
#include "nexception.h"
#include "nstring.h"


/**
\brief NIOException is the exception object thrown in I/O related errors
*/
class DllDeclSpec NIOException: public NException {
		public:
			/**
			\brief Enumerates the set of resources in which a problem will 
			throw a NIOException exception
			*/
			enum Resource {
				UNKNOWN,	/*!< Unknown or unset resource */ 
				FILE,		/*!< File resource */
				DIRECTORY	/*!< Directory resource */
			};
			
			static const Flag IO_NOT_FOUND = 1;		/*!< Resource not found */
			static const Flag IO_ACCESS_DENIED = 2;		/*!< Access to the resource was denied */
			static const Flag IO_SYSTEM = 3;			/*!< Low-level system error */
			static const Flag IO_NO_SPACE = 4;		/*!< No space available on the device */
			static const Flag IO_IO_ERROR = 5;		/*!< Input/output error */
			
			/**
			\brief Constructs a NIOException object
			\param desc Exception description
			\param name The name of the resource
			\param module The module in which the exception occurred
			\param resource The resource that caused the exception
			\param flag A set of flags that may identify what occurred
			*/
			NIOException(const NString &desc, const NString &name, Module module, 
				Resource resource, Flag flag);

				
			/**
			\brief Gets the resource associated with the exception
			\return A resource value as enumerated by the enum Resource.
			*/
			Resource getResource(void) const;
			
			
			/**
			\brief Gets the name of the resource associated with the exception
			\return The name of the resource
			*/
			NString getResourceName(void) const;
			
			/**
			\brief Given a errno value, this function will return a corresponding
			flag value (as defined by the enum Flag)
			\param errno_val The value of the errno variable
			\return A flag value corresponding to the given errno value
			*/
			static Flag getFlagByErr(nuint32 errno_val);
			
		private:
			Resource m_resource;
			NString m_name;
};

#endif // NIOEXCEPTION_H
