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
#include "serverapp.h"

ServerApp::ServerApp(void)
	: m_port(0),
	m_host(),
	m_sock()
{

}

bool ServerApp::setPort(const NOpt<ServerApp> &opt) {
	NString optVal;
	
	optVal = opt.getValues().at(0);
	m_port = atoi(optVal.toChar());
	m_sock.setPort(m_port);
	
	return true;
}

bool ServerApp::setHost(const NOpt<ServerApp> &opt) {
	m_host = opt.getValues().at(0);
	
	m_sock.setHost(m_host);
	return true;
}

void ServerApp::handleConnection(NTcpSocket *client) {
	NDataStream data;
	nint32 bytes = 0;
	
	// Once a host connects, display a message
	client->writeLine("Hi there!"); 
	
	// Receives data from the host until receives a shutdown 
	// command or until client disconnect
	do {
		data = "";
		NMessage::print() << "Waiting for read ... ";
				
		// Reads data from the client
		bytes = client->readLine(&data);
		if (bytes < 0) {
			break;
		}
		else {
			if (bytes == 0) {
				continue;
			}
		}
				
		NWarning::print() << "Read (" << bytes << " bytes): " 
			<< data.toString();
				
		if (data.toString() == "shutdown") {

			// If I use write I should add a \r\n at the end
			client->write("Good bye!\r\n");
			client->disconnectFromHost();
			exit(0);
		}
	} while (bytes >= 0);
	
	// Just in case, disconnect from the host
	client->disconnectFromHost();
}

void ServerApp::run(void) {
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
		handleConnection(client);		
		
		NWarning::print() << "Client disconnected";
		// Release memory
		delete client;
	}
}

