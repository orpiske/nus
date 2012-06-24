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
#ifndef NTCPSOCKET_H
#define NTCPSOCKET_H

/**
\file linux/ntcpsocket.h NTcpSocket class definition for linux
\example clientapp.cpp
\include clientapp.h
\include serverapp.cpp
\include serverapp.h
*/

#include "ndefs.h"
#include "ndatastream.h"
#include "nstring.h"
#include "nabstractsocket.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#if defined(__CYGWIN__)
 #define MSG_DONTWAIT 0
#endif // defined(__CYGWIN__)

#if defined (__SVR4) && defined(__sun__) 
 #ifndef INADDR_NONE
  #define INADDR_NONE     ((unsigned long) -1)
 #endif // INADDR_NONE
#endif // defined (__SVR4) && defined(__sun__) 


/**
\brief NTcpSocket provides an easy interface to manipulate TCP Sockets
\note For details see NAbstractSocket
*/
class NTcpSocket: public NAbstractSocket {
	public:
		/**
		\brief Creates a NTcpSocket object
		*/
		NTcpSocket(void);
		
		/**
		\brief Creates a NTcpSocket object
		\param host Hostname/ip associated with the socket
		*/
		NTcpSocket(NHostAddress &host);
		
		/**
		\brief Creates a NTcpSocket object
		\param host Hostname/ip associated with the socket
		\param port Port associated with the socket
		*/
		NTcpSocket(const NString &host, nuint16 port);
		
		/**
		\brief Destroys a NTcpSocket object
		*/
		~NTcpSocket(void);

		/**
		\brief Sets the port associated with the socket
		\param port The port number associated with the socket
		*/
		void setPort(nint16 port);
		void setSocketOptions(nint32 opt);
		
		/**
		\brief Gets the address of the remote host
		\return The address of the remote host
		*/
		NHostAddress peerAddress(void) const;
		
		/**
		\brief Gets the name of the remote host
		\return The name of the remote host
		*/
		NString peerName(void) const;
		
		/**
		\brief Gets the port of the remote host
		\return The port of the remote host
		*/
		nuint16 peerPort(void) const;
		
		void open(void);
		void closeDevice(void);
		
		void disconnectFromHost(void);
		void connectToHost();
		void execListen(void);
		
		/**
		\brief Waits until a connection occurs
		\return A pointer to a NTcpSocket object associated with the newly
		created connection
		*/
		NTcpSocket *waitForConnected(void);
		
		nint32 read(NDataStream *buffer);
		nint32 read(NDataStream *buffer, nuint32 bytes);
		nint32 readLine(NDataStream *buffer);
		nint32 write(const NDataStream &data, nuint32 bytes = 0);
		nint32 writeLine(const NDataStream &data, nuint32 bytes = 0);

	private:
		struct sockaddr_in m_addr;
		int m_sock;
		
		NTcpSocket(nuint16 timeout, nint32 sock, struct sockaddr_in client);
		
		void init(void);
		void execBind(void);
		
		void setPeer(struct sockaddr_in addr);
		void setSock(int sock);
		void setupNewSocket(NTcpSocket *sock, struct sockaddr_in addr);
};

#endif // NTCPSOCKET_H
