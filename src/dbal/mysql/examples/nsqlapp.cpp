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

// Source code file created by nproj 0.1.0 with NUS version 0.3.0
#include "nsqlapp.h"

NSqlApp::NSqlApp(void)
	: NObject(),
	m_port(3306),
	m_host("localhost"),
	m_user(""),
	m_password(""),
	m_database(""),
	m_db()
{

}


NSqlApp::~NSqlApp(void) {
	
}

bool NSqlApp::setPort(const NOpt<NSqlApp> &opt) {
	NString optVal;
	
	optVal = opt.getValues().at(0);
	NDebug::print() << "Port val = " << optVal;
	m_port = atoi(optVal.toChar());

	if (m_port == 0) { 
		throw NException("Port number is not valid", NException::DBAL);
	}
	
	
	return true;
}


bool NSqlApp::setHost(const NOpt<NSqlApp> &opt) {
	m_host = opt.getValues().at(0);
	

	return true;
}


bool NSqlApp::setUser(const NOpt<NSqlApp> &opt) {
	m_user = opt.getValues().at(0);
	m_db.setUser(m_user);

	return true;
}


bool NSqlApp::setPassword(const NOpt<NSqlApp> &opt) {
	m_password = opt.getValues().at(0);

	return true;

}


bool NSqlApp::setDatabase(const NOpt<NSqlApp> &opt) {
	m_database = opt.getValues().at(0);
	
	return true;

}

void NSqlApp::runQuery(void) {
	NString query = "select * from proj";
	bool q_ret = false;

	// Runs a query. If the query is successfull, it'll return true.
	q_ret = m_db.execSql(query);
	if (q_ret) {
		// Gets the row from the query executed
		NSqlRecord *rec = m_db.getFirst();

		// If there's no more rows, rec will be NULL.
		while (rec) {
			NVtype id;
			NVtype name;
	
			// Gets the data using the row name
			id = rec->getData("id");
			name = rec->getData("name");

			NMessage::print() << "id: " << id.toString() 
				<< ". Name: " << name.toString();

			// Gets the next row in the result set
			rec = m_db.getNext();
		}
	}
	else {
		NMessage::print() << "Error";
	}

}

int NSqlApp::run(void) {
	// Sets the connection properties (port, host, etc)
	m_db.setPort(m_port);	
	m_db.setHost(m_host);
	m_db.setDatabase(m_database);
	m_db.setPassword(m_password);

	// Connects to the database and run a simple query
	m_db.connectToHost();
	runQuery();

	// Disconnects from the database
	m_db.disconnectFromHost();

	return 0;
}