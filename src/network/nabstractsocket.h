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
#ifndef NABSTRACTSOCKET_H
#define NABSTRACTSOCKET_H

/**
\file nabstractsocket.h Class definition for NAbstractSocket
\example clientapp.cpp
\include clientapp.h
\include serverapp.cpp
\include serverapp.h
*/

#include "ndefs.h"
#include "nstring.h"
#include "ndatastream.h"
#include "nhostaddress.h"
#include "nsignal.h"
#include "niodevice.h"
#include "nexception.h"

#ifndef _MSC_VER
#include <sys/socket.h>
#endif // _MSC_VER


/**
\brief NAbstractSocket class provides an abstraction to manipulate sockets.
*/
class DllDeclSpec NAbstractSocket: public NIODevice {
	public:
		/**
		\brief Defines the socket type. Currently only TcpSockets are 
		supported.		
		*/
		enum SocketType {
			Unknown = -1,	/*!< Unknown socket type */
			TcpSocket,		/*!< TCP Socket Type */
			UdpSocket		/*!< UDP socket type (not implemented) */
		};

		/** \brief Default options */
		static const nint32 DEFAULT_SOCK_OPTS = 0;
		/** \brief Allow the reuse of local address */
		static const nint32 REUSE_ADDRESS = SO_REUSEADDR;
		/** \brief Enable sending of keep-alive messages */
		static const nint32 KEEPALIVE = SO_KEEPALIVE;
		
		/**
		\brief Constructs an abstract socket object
		*/
		NAbstractSocket(void);
		
		/**
		\brief Constructs an abstract socket object
		\param host Host to connect to/listen 
		*/
		NAbstractSocket(const NHostAddress &host);
		
		/**
		\brief Constructs an abstract socket object
		\param host Host to connect to/listen 
		\param port Port to connect to/listen 
		*/
		NAbstractSocket(const NHostAddress &host, nuint16 port);
		
		/**
		\brief Constructs an abstract socket object
		\param host Host to connect to/listen 
		\param port Port to connect to/listen 
		*/
		NAbstractSocket(const NString &host, nuint16 port);
		
		/**
		\brief Destroys an abstract socket object closing the related 
		connection
		*/
		virtual ~NAbstractSocket(void);
		
		
		/**
		\brief Sets the host to connect to/listen 
		\param host Hostname or IP to connect to/listen 
		*/
		virtual void setHost(const NHostAddress &host);
		
		/**
		\brief Sets the host to connect to/listen 
		\param host Hostname or IP to connect to/listen 
		*/
		virtual void setHost(const NString &host);
		
		/**
		\brief Gets the host to connect to/listen 
		\return The host to connect to/listen 
		*/
		NHostAddress getHost(void) const;

		/**
		\brief Sets the port to connect to/listen 
		\param port Port to connect to/listen 
		*/
		virtual void setPort(nuint16 port);
		
		/**
		\brief Gets the port to connect to/listen
		\return The port to connect to/listen 
		*/
		nuint16 getPort(void) const;
		
		
		/**
		\brief Sets the timeout for reading data
		\param timeout Max time, in seconds, that the object will wait for
		a response
		*/
		void setTimeout(nuint16 timeout);
		
		/**
		\brief Gets the timeout for reading data
		\return The max time, in seconds
		*/
		nuint16 getTimeout(void) const;

		/**
		\brief Sets the max number of pending connections 
		\param max The max number of pending connections
		\note By default uses 5
		*/
		void setMaxPendingConnections(nint32 max);
		
		/**
		\brief Gets the max number of pending connections
		\return The max number of pending connections
		*/
		nint32 getMaxPendingConnections(void) const;
		
		/**
		\brief Sets socket options
		*/
		virtual void setSocketOptions(nint32 opt);
		
		
		/**
		\brief Open the socket
		*/
		virtual void open(void) = 0;
		
		/**
		\brief Open the Socket
		\param mode Openning mode (ignored)
		\note For a socket 'mode' is ignored, so it's the same as 
		calling open()
		*/
		void open(Mode mode) { open(); };
		
		/**
		\brief Closes the socket
		*/
		virtual void closeDevice(void) = 0;
		
		/**
		\brief Disconnects from the remote host
		*/
		virtual void disconnectFromHost(void) = 0;
		
		/**
		\brief Starts listening
		*/
		virtual void execListen(void) = 0;
		
		/**
		\brief Connects to a host
		*/
		virtual void connectToHost(void) = 0;
		
		
		/**
		\brief Reads data from the socket
		\param buffer Buffer to save the received data
		\return The number of bytes read
		*/
		virtual nint32 read(NDataStream *buffer) = 0;
		
		/**
		\brief Reads data from the socket
		\param buffer Buffer to save the received data
		\param bytes Max number of bytes to read
		\return The number of bytes read
		*/
		virtual nint32 read(NDataStream *buffer, nuint32 bytes) = 0;
		
		/**
		\brief Reads a line from the socket
		\param buffer Buffer to save the received data
		\return The number of bytes read
		*/
		virtual nint32 readLine(NDataStream *buffer) = 0;
		
		/**
		\brief Writes data to the socket
		\param data Data to be written to the socket
		\param bytes Max number of bytes to write to the socket
		\return The amount of bytes written
		*/
		virtual nint32 write(const NDataStream &data, nuint32 bytes) = 0;


		/**
		\brief Writes a line of data to the socket
		\param data Data to be written to the socket
		\param bytes Max number of bytes to write to the socket
		\return The amount of bytes written
		\note It's not needed to append a carriage return/line feed at the end of the data. The
		object will do that for you. If you don't want this behaviour, use
		write() instead.
		*/
		virtual nint32 writeLine(const NDataStream &data, nuint32 bytes) = 0;
	
	protected:
		NHostAddress m_host; 		/*!< Hostname */
		nuint16 m_port;			/*!< Port */
		
		nuint16 m_timeout;		/*!< Time out, in seconds */
		nint32 m_opt;			/*!< Socket options */
		nint32 m_maxPendingConn;	/*!< Maximum number of pending connections */
};

#endif // NABSTRACTSOCKET_H
