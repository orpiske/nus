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
#include "nsql.h"

/**
\file nsql.cpp NSql class implementation
*/

NSql::NSql(void)
	: NObject(),
	m_user(),
	m_password(),
	m_host(),
	m_port(0),
	m_database()
{

}


NSql::NSql(const NString &user, const NString &password, 
	const NHostAddress &host)
	: NObject(),
	m_user(user),
	m_password(password),
	m_host(host),
	m_port(0),
	m_database()
{

}


NSql::NSql(const NString &user, const NString &password, 
	const NHostAddress &host, nint16 port)
	: NObject(),
	m_user(user),
	m_password(password),
	m_host(host),
	m_port(port),
	m_database()
{

}


NSql::~NSql(void) {

}


void NSql::setUser(const NString &user) {
	m_user = user;
}


void NSql::setPassword(const NString &password) {
	m_password = password;
}


void NSql::setHost(const NHostAddress &host) {
	NDebug::print() << "Setting the host";
	m_host = host;
}


void NSql::setPort(nint16 port) { 
	if (port == 0) { 
		NString msg = "Port number ";

		msg = msg + port + " is not valid";

		throw NException(msg, NException::DBAL);
	}

	m_port = port;
	NDebug::print() << "Setting the port to " << m_port;
}


void NSql::setDatabase(const NString &database) { 
	m_database = database;
}


NString NSql::getUser(void) const {
	return m_user;
}

NString NSql::getPassword(void) const {
	return m_password;
}

NHostAddress NSql::getHost(void) const {
	return m_host;
}

nint16 NSql::getPort(void) const { 
	return m_port;
}

NString NSql::getDatabase(void) const { 
	return m_database;
}

void NSql::setRecordData(NSqlRecord *record, const NString &rowName, 
	const NVtype &rowData) 
{
	assert(record);

	record->add(rowName, rowData);
}



