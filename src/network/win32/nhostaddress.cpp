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
#include "nhostaddress.h"

/**
\file win32/nhostaddress.cpp NHostAddress class implementation
*/

NHostAddress::NHostAddress(void)
	: NObject(),
	m_addr("0.0.0.0"),
	m_host()
{
	WORD version; 
	WSADATA wsaData; 

	memset(&m_host, 0, sizeof(m_host));
	
	version = MAKEWORD(2 , 2);
	
	if (WSAStartup(version, &wsaData) != 0) {
		throw NNetworkException("Unable to initialize winsock", m_addr, NException::NETWORK);
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		WSACleanup();
		throw NNetworkException("Incorrect Winsock version", m_addr, NException::NETWORK);
	}
	
}



NHostAddress::NHostAddress(const NString &addr)
	: NObject(),
	m_addr(addr),
	m_host()
{

}


NHostAddress::NHostAddress(const NHostAddress &addr)
	: NObject(),
	m_addr("0.0.0.0"),
	m_host()
{
	m_host = addr.m_host;
	m_addr = addr.m_addr;
}

NHostAddress::NHostAddress(const sockaddr *addr)
	: NObject(),
	m_addr("0.0.0.0"),
	m_host()
{
	setAddress(addr);
}

void NHostAddress::clear(void) {
	m_addr = "0.0.0.0";
}


void NHostAddress::setAddress(nuint32 ip) {
	m_addr = NString::number(static_cast<int>(ip));
}


void NHostAddress::setAddress(const NString &addr) {
	m_addr = addr;
}

void NHostAddress::setAddress(const sockaddr *sock) {
	assert(sock);
	
	m_addr = sock->sa_data;
}


nuint32 NHostAddress::resolve(void) const {
	struct hostent *result = NULL;
	size_t bufflen = 1024;
	int ret = 0;
	nuint32 ret_addr = 0;

	// TODO: May not be thread safe. Verify
	if (isalpha(m_addr[0])) { 
		result = gethostbyname(m_addr.toChar());
	}
	else { 
		ret_addr = inet_addr(m_addr.toChar());
		result = gethostbyaddr((char *)&ret_addr, 4, AF_INET);
	}
	
	if (WSAGetLastError() != 0) {
  		throwErrorByCode(WSAGetLastError());
	}

	memcpy(&m_host, result, sizeof(struct hostent));
	ret_addr |= (unsigned char)(m_host.h_addr[0]);
	ret_addr <<= 8;
	ret_addr |= (unsigned char)(m_host.h_addr[1]);
	ret_addr <<= 8;
	ret_addr |= (unsigned char) m_host.h_addr[2];
	ret_addr <<= 8;
	ret_addr |= (unsigned char) m_host.h_addr[3];
	
	return ret_addr;
}

void NHostAddress::throwErrorByCode(int herr) const {
	NString msg = "Unable to resolve address ";
	
	msg += m_addr;
	msg += ": ";
	switch (herr) {
		case WSAHOST_NOT_FOUND: {
			throw NNetworkException("Host not found", m_addr,
				NException::NETWORK, NNetworkException::DNS_HOST_UNKNOWN);
		}
		case WSATRY_AGAIN: {
			throw NNetworkException("Try again", m_addr, 
				NException::NETWORK, NNetworkException::DNS_TRY_AGAIN);
		}
		case WSANO_RECOVERY: {
			throw NNetworkException("Non-recovarable name server error", m_addr, 
					NException::NETWORK, NNetworkException::DNS_NO_RECOVERY);

		}
		case WSANO_DATA: {
			throw NNetworkException("Address is valid, but there's no assigned ip address",
						m_addr, NException::NETWORK, NNetworkException::DNS_NO_ADDRESS);		} 
		default: {
			throw NNetworkException("Unknown error", m_addr, 
						NException::NETWORK, NNetworkException::UNHANDLED_EXCEPTION);
		}
	}
}


NString NHostAddress::toString(void) const {
	NString ret;
	char addr[16];
	
	if (!m_host.h_addr_list) {
		resolve();
	}
	
	memset(addr, 0, sizeof(addr));
#if defined(_MSC_VER)
	_snprintf_s(addr, sizeof(addr), "%s", inet_ntoa(*(struct in_addr *) m_host.h_addr));
#else
	snprintf(addr, sizeof(addr), "%s", inet_ntoa(*(struct in_addr *) m_host.h_addr));
#endif // defined(_MSC_VER)
	ret = addr;
	return ret;
}

NString NHostAddress::toString(nuint32 ip) {
// This is not nice but I'll fix in the future
#if defined(_MSC_VER) 
	NHostAddress tmp;
	
	tmp.setAddress(ip);
	
	return tmp.toString();
#else
	NString ret;
	char addr[32];
		
	memset(addr, 0, sizeof(addr));



	if (!inet_ntop(AF_INET, &ip, addr, sizeof(addr))) { 
		throw NNetworkException(nerror(errno), NString::number((int) ip), 
				NException::NETWORK);
	}
	
	ret = addr;
	return ret;
#endif // defined(_MSC_VER)
}



NString NHostAddress::address(void) const {
	return m_addr;
}


NList<NString> NHostAddress::aliases(void) {
	NList<NString> ret;
	NString tmp;
	
	for (int i = 0; m_host.h_addr_list[i]; i++) {
		tmp = m_host.h_aliases[i];
		ret.append(tmp);
	}
	
	return ret;
}


NList<nuint32> NHostAddress::addresses(void) {
	NList<nuint32> ret;
	
	for (int i = 0; m_host.h_addr_list[i]; i++) {
		ret.append(atoi(m_host.h_addr_list[i]));
	}
	
	return ret;

}


bool NHostAddress::isNull(void) const {
	if (m_addr == "0.0.0.0") {
		return true;
	}
	
	return false;
}


bool NHostAddress::isLocalhost(void) const {
	if (m_addr == "127.0.0.1") {
		return true;
	}
	
	return false;
}


NHostAddress &NHostAddress::operator=(const NHostAddress &rhs) {
	m_addr = rhs.m_addr;
	
	return *this;
}


NHostAddress &NHostAddress::operator=(const NString &rhs) {
	m_addr = rhs;
	
	return *this;
}
