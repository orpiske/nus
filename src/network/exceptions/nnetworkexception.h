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
#ifndef NNETWORK_EXCEPTION_H
#define NNETWORK_EXCEPTION_H

/**
\file nnetworkexception.h NNetworkException class definition
*/

#include "ndefs.h"
#include "nexception.h"
#include "nstring.h"

/**
\brief NNetworkException is the object used for network-related exceptions
*/
class DllDeclSpec NNetworkException: public NException {			
	public:
		static const Flag UNHANDLED_EXCEPTION = 1; 	/*!< Unhandled exception */
		static const Flag DNS_HOST_UNKNOWN = 2; 	/*!< Host not found */
		static const Flag DNS_TRY_AGAIN = 3; 		/*!< Try again */
		
		
		static const Flag DNS_NO_ADDRESS = 4;	/*!< Un-assigned ip to the address */
		static const Flag DNS_NO_RECOVERY = 5;	/*!< Unrecoverable error */
		
		static const Flag SOCKET_INIT_FAILED = 6; /*!< Socket initialization failed */
		static const Flag CONNECTION_FAILED = 7; /*!< Connection failed or refused */ 
		
		static const Flag SOCK_ERROR = 8; /*!< Internal socket error */ 
	
		/**
		\brief Constructs a NNetworkException object
		\param desc Exception description
		\param host An optional hostname associated to the exception
		\param module The module in which the exception occurred
		\param flag An unique id, as provided by the enum Flag, that identifies the
		error that occurred
		*/
		NNetworkException(const NString &desc, const NString &host, 
				Module module, Flag flag = UNHANDLED_EXCEPTION);
		
		/**
		\brief Gets the hostname associated with the exception
		\return The hostname associated with the exception
		*/
		NString getHost(void) const;
		
	protected:
		NString m_host;	/*!< The hostname */
		Flag m_flag;	/*!< The error flag */
};


#endif // NNETWORK_EXCEPTION_H
