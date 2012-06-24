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
#include "nabstractsocket.h"

/**
\file nabstractsocket.cpp Base class for socket operations
*/

NAbstractSocket::NAbstractSocket(void)
	: m_host(),
	m_port(0),
	m_timeout(300),
	m_opt(DEFAULT_SOCK_OPTS),
	m_maxPendingConn(5)
{

}


NAbstractSocket::NAbstractSocket(const NHostAddress &host)
	: m_host(),
	m_port(0),
	m_timeout(300),
	m_opt(DEFAULT_SOCK_OPTS),
	m_maxPendingConn(5)
{
	m_host = host.toString();
}


NAbstractSocket::NAbstractSocket(const NHostAddress &host, nuint16 port)
	: m_host(),
	m_port(port),
	m_timeout(300),
	m_opt(DEFAULT_SOCK_OPTS),
	m_maxPendingConn(5)
{
	m_host = host.toString();
}

NAbstractSocket::NAbstractSocket(const NString &host, nuint16 port)
	: m_host(host),
	m_port(port),
	m_timeout(300),
	m_opt(DEFAULT_SOCK_OPTS),
	m_maxPendingConn(5)
{

}


NAbstractSocket::~NAbstractSocket(void) {

}

void NAbstractSocket::setHost(const NHostAddress &host) {
	m_host = host;
}


void NAbstractSocket::setHost(const NString &host) {
	m_host = host;
}


NHostAddress NAbstractSocket::getHost(void) const {
	return m_host;
}


void NAbstractSocket::setPort(nuint16 port) {
	m_port = port;
}


nuint16 NAbstractSocket::getPort(void) const {
	return m_port;
}


void NAbstractSocket::setTimeout(nuint16 timeout) {
	m_timeout = timeout;
}


nuint16 NAbstractSocket::getTimeout(void) const {
	return m_timeout;
}


void NAbstractSocket::setSocketOptions(nint32 opt) { 
	m_opt = opt;
}

void NAbstractSocket::setMaxPendingConnections(nint32 max) { 
	m_maxPendingConn = max;	
}


nint32 NAbstractSocket::getMaxPendingConnections(void) const { 
	return m_maxPendingConn;
}


/*
NAbstractSocket NAbstractSocket::waitForConnected(void) {
	return NAbstractSocket();
}
*/
