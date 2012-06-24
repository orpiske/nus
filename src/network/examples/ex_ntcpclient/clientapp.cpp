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
#include "clientapp.h"

ClientApp::ClientApp(void)
	: m_host(),
	m_port(0), 
	m_sock()
{

}

bool ClientApp::setHost(const NOpt<ClientApp> &opt) {
	m_host = opt.getValues().at(0);
	
	return true;
}

bool ClientApp::setPort(const NOpt<ClientApp> &opt) {
	NString optVal;
	
	optVal = opt.getValues().at(0);
	m_port = atoi(optVal.toChar());
	
	return true;
}

void ClientApp::run(void) {
	NDataStream data;
	int bytes;
	
	// Sets the host to connect to
	m_sock.setHost(m_host);
	
	// Sets the port to connect to
	m_sock.setPort(m_port);
	
	try { 
		// Open the socket
		m_sock.open();
		
		// Connect to the host
		m_sock.connectToHost();
		bytes = m_sock.readLine(&data);

		if (bytes < 0) {
			NMessage::print() << "Server disconnected";
			exit(1);
		}
		else {
			if (bytes == 0) {
				NMessage::print() << "Nothing to read";
			}
			else {
				NMessage::print() << "Read " << bytes << ":";
				NMessage::print() << data.toString();
			}
		}

		// Write something to the socket. Note that you don't need to append
		// a \r\n at the end of the data. It will be automagically appended to
		// you. If you don't want that behaviour, use write() instead.
		m_sock.writeLine("Hello network!");
		
		m_sock.disconnectFromHost();
	}
	catch (NNetworkException &e) {
		m_sock.disconnectFromHost();
		///NWarning::print() << "Error: " << e.getDescription();
		throw;
	}
}

