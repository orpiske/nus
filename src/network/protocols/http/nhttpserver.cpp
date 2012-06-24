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
#include "nhttpserver.h"

NHttpServer::NHttpServer(void)
	: NObject(),
	m_sock(),
	m_request(),
	m_response() 
{
	m_sock.setPort(80);
	m_response.setHttpVersion(1, 1);
	
	m_response.setServer("NUS/0.3.0");
	m_response.setCacheControl("no-cache");
	m_response.setPragma("no-cache");
	m_response.setVary("Accept-Encoding");
	m_response.setContentType("text/html; charset=iso8859-15");
}

void NHttpServer::setPort(nuint16 port) {
	m_sock.setPort(port);
}


void NHttpServer::setListenAddr(const NString &host) {
	m_sock.setHost(host);
}


void NHttpServer::run(void) {
	NMessage::print() << "Starting server";
	
	// Opens the socket
	m_sock.open();
	
	// Make it reuse the address if possible		
	m_sock.setSocketOptions(NAbstractSocket::REUSE_ADDRESS);
	
	// Listens 
	m_sock.execListen();
	
	NMessage::print() << "Server is up an running";		
	// Starts receiving connections
	while (true) {
		NTcpSocket *client = NULL;
		NMessage::print() << "Waiting for connection";
		client = m_sock.waitForConnected();
		if (client) { 
			NMessage::print() << "Someone connected";
			handleConnection(client);
		}
	}
}