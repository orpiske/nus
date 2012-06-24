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
#ifndef NHOSTADDRESS_H
#define NHOSTADDRESS_H

/**
\file linux/nhostaddress.h NHostAddress class definition
\example nhostopts.cpp
\include nhostopts.h
\include ex_nhostaddress.cpp
*/

#include "ndefs.h"
#include "nobject.h"
#include "nstring.h"
#include "nlist.h"
#include "nbaseexceptions.h"
#include "nnetworkexception.h"

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <climits>

/**
\brief NHostAddress class abstracts an ip address/hostname
*/
class NHostAddress: public NObject {
	public:
		/**
		\brief Constructs a NHostAddress object 
		*/
		NHostAddress(void);

		/**
		\brief Constructs a NHostAddress object
		\param addr The address (ip or hostname)
		*/
		NHostAddress(const NString &addr);

		/**
		\brief Constructs a NHostAddress object
		\param addr The object to be copied
		\note Copy constructor
		*/
		NHostAddress(const NHostAddress &addr);

		/**
		\brief Constructs a NHostAddress object
		\param addr A pointer to a sockaddr structure
		*/
		NHostAddress(const sockaddr *addr);

		/**
		\brief Resets the host address hold by the object
		*/
		void clear(void);

		/**
		\brief Sets the host address hold by the object to
		a given ip address
		\param ip The ip address of the host in network byte 
		order
		*/
		void setAddress(nuint32 ip);

		/**
		\brief Sets the host address hold by the object to
		a given host address
		\param addr The host address
		*/
		void setAddress(const NString &addr);

		/**
		\brief Sets the host address hold by the object to 
		a given address
		\param sock A pointer to a sockaddr structure containing the
		host address
		*/
		void setAddress(const sockaddr *sock);

		/**
		\brief Resolves the address of the host
		\return Returns the 32bit unsigned integer representing the
		host address
		\note The returned integer will be in network byte order
		\throw NMemException If runs out of memory
		\throw NResolveException If get a low level error
		\throw NHostTryAgainException If requested to try again
		\throw NHostNotFoundException If the host was not found
		*/
		nuint32 resolve(void) const;

		/**
		\brief Returns the resolved address in a NString format
		\return A NString object with the ip address of the host
		*/
		NString toString(void) const;
		
		/**
		\brief Returns a given ip addresss in a NString format
		\param ip The ip address in network byte order
		\return A NString object with the ip address of the host
		*/
		static NString toString(nuint32 ip);

		/**
		\brief Returns the host address as originally set
		\return The host address
		*/
		NString address(void) const;

		/**
		\brief Returns a list with all the aliases of the host
		\return A NList<NString> object with the aliases of the host
		*/
		NList<NString> aliases(void);

		/**
		\brief Returns a list with all the ip addresses of the host
		\return A NList<nuint32> object with all the ip addresses of 
		the host
		\note The ip addresses will be in network byte order
		*/
		NList<nuint32> addresses(void);
		
		/**
		\brief Tests whether the host is NULL (0.0.0.0)
		\return true if it is null or false otherwise
		*/
		bool isNull(void) const;

		/**
		\brief Tests wheter the host is localhost (127.0.0.1)
		\return true if it is localhost of false otherwise
		*/
		bool isLocalhost(void) const;

		/**
		\brief Assigns a NHostAddress to the object
		\param rhs The NHostAddress being copied
		\return A reference to the object
		*/
		NHostAddress &operator=(const NHostAddress &rhs);

		/**
		\brief Assigns an address to the object
		\param rhs The address of the host
		\return A reference to the object
		*/
		NHostAddress &operator=(const NString &rhs);

	private:
		NString m_addr;
		mutable struct hostent m_host;
		
		void throwErrorByCode(int herr) const;
		
};

#endif // NHOSTADDRESS_H
