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
#include "ntcpsocket.h"

/**
\file win32/ntcpsocket.cpp NTcpSocket class implementation
*/

NTcpSocket::NTcpSocket(void)
	: NAbstractSocket(), 
	m_sock(INVALID_SOCKET)
{
	init();
}


NTcpSocket::NTcpSocket(NHostAddress &host)
	: NAbstractSocket(host), 
	m_sock(INVALID_SOCKET)
{
	init();
}


NTcpSocket::NTcpSocket(const NString &host, nuint16 port)
	: NAbstractSocket(host, port), 
	m_sock(INVALID_SOCKET)
{
	init();
}

NTcpSocket::NTcpSocket(nuint16 timeout, nint32 sock)
	: NAbstractSocket(),
	m_addr(),
	m_sock(sock)
{
	init();
	setTimeout(timeout);
	try {
		NDebug::print() << "Creating structures";
		m_addr = new struct addrinfo;
		NDebug::print() << "Zeroing";
		memset(m_addr, 0, sizeof(struct addrinfo));

		m_addr->ai_addr = new struct sockaddr;
		memset(m_addr->ai_addr, 0, sizeof(struct sockaddr));

		NDebug::print() << "Done zeroing";
	}
	catch (std::bad_alloc &) {
		if (m_addr && m_addr->ai_addr) {
			delete m_addr->ai_addr;
		}
		
		delete m_addr;
		throw;
	}

	NDebug::print() << "Setting peer address";
	m_host = peerAddress();
	setPort(peerPort());
}


NTcpSocket::~NTcpSocket(void) {
   WSACleanup();
}


void NTcpSocket::init(void) {
	WORD version; 
	WSADATA wsaData; 

	memset(&m_host, 0, sizeof(m_host));
	
	version = MAKEWORD(2 , 2);
	
	if (WSAStartup(version, &wsaData) != 0) {
		throw NNetworkException("Unable to initialize winsock", "",
			NException::NETWORK, NNetworkException::SOCKET_INIT_FAILED);
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		WSACleanup();
		throw NNetworkException("Incorrect Winsock version", "", 
			NException::NETWORK, NNetworkException::SOCKET_INIT_FAILED);
	}

	
}


void NTcpSocket::setPort(nint16 port) {
	NAbstractSocket::setPort(port);
}


void NTcpSocket::setSocketOptions(nint32 opt) {

}


void NTcpSocket::throwSocketError(int err) const {
	NString msg;
	
	switch (err) {
		case WSANOTINITIALISED: {
			msg = "Winsock was not initialized";
			break;
		}
		case WSAENETDOWN: {
			msg = "The network subsystem is down";
			break;
		}
		case WSAEAFNOSUPPORT: {
			msg = "Address family not supported";
			break;
		}
		case WSAEINPROGRESS: {
			msg = "A blocking winsock call is in progress";
			break;
		}
		case WSAEMFILE: {
			msg = "No more socket descriptors available";
			break;
		}
		case WSAENOBUFS: {
			msg = "No buffer space is available";
			break;
		}
		case WSAEPROTONOSUPPORT: {
			msg = "Protocol not supported";
			break;
		}
		case WSAEPROTOTYPE: {
			msg = "The specified protocol is incorrect";
			break;
		} 
		case WSAESOCKTNOSUPPORT: {
			msg = "The specified socket type is incorrect";
			break;
		}
		case WSATRY_AGAIN: {
			msg = "Temporary failure in name resolution";
			break;
		}
		case WSAEINVAL: {
			msg = "Invalid value";
			break;
		}
		case WSANO_RECOVERY: {
			msg = "Nonrecoverable error in name resolution";
			break;
		}
		case WSA_NOT_ENOUGH_MEMORY: {
			msg = "Not enough memory";
			break;
		}
		case WSAHOST_NOT_FOUND: {
			msg = "Host not found";
			break;
		}
		case WSATYPE_NOT_FOUND: {
			msg = "Unsupported service type";
			break;
		}
		default: {
			msg = "Unhandled exception";
			break;
		}
	}
	
	throw NNetworkException(msg, m_host.toString(), NException::NETWORK, 
		NNetworkException::SOCKET_INIT_FAILED);
}


void NTcpSocket::open(void) {
	NString port;
	struct addrinfo hints;
	int ret = 0;
	
	if (m_sock != INVALID_SOCKET) {
		return;
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	port = NString::number(m_port);
	
	if (m_host.isNull()) {
		ret = getaddrinfo(NULL, port.toChar(), &hints, &m_addr);
	}
	else {
		ret = getaddrinfo(m_host.toString().toChar(), port.toChar(), &hints, &m_addr);
	}

	if (ret != 0) {
		NDebug::print() << "Getaddrinfo error!";
		throwSocketError(WSAGetLastError());
	}
	
	m_sock = socket(m_addr->ai_family, m_addr->ai_socktype, m_addr->ai_protocol);
	if (m_sock == INVALID_SOCKET) {
		NDebug::print() << "socket() error!";
		throwSocketError(WSAGetLastError());
	}
}


void NTcpSocket::closeDevice(void) {
	disconnectFromHost();
}


void NTcpSocket::disconnectFromHost(void) {
	if (m_sock > 0) {
		closesocket(m_sock);
		m_sock = 0;
	}
}



void NTcpSocket::connectToHost(void) {
	int ret = 0;

	ret = connect(m_sock, m_addr->ai_addr, (int) m_addr->ai_addrlen);
	if (ret == SOCKET_ERROR) {
		NString msg = "Unable to connect to ";
		disconnectFromHost();
		
		msg += m_host.toString() + NSTR(":") + NString::number(m_port);
		throw NNetworkException(msg, m_host.toString(), NException::NETWORK,
			NNetworkException::CONNECTION_FAILED);
	}
}


void NTcpSocket::execBind(void) {
	if (bind(m_sock, m_addr->ai_addr, (int)m_addr->ai_addrlen) == SOCKET_ERROR) {
		throwSocketError(WSAGetLastError());
	}
}


void NTcpSocket::execListen(void) {
	execBind();
	if (listen(m_sock, m_maxPendingConn) == SOCKET_ERROR) {
		disconnectFromHost();
		throw NNetworkException("Unable to listen", "",
			NException::NETWORK, NNetworkException::SOCKET_INIT_FAILED);
	}
}


NTcpSocket *NTcpSocket::waitForConnected(void) {
	SOCKET client = INVALID_SOCKET;
	NTcpSocket *ret = NULL;

	NDebug::print() << "Accepting ... ";
	client = accept(m_sock, NULL, NULL);
	if (client == INVALID_SOCKET) {
		NDebug::print() << "Unable to accept ...";
		throwSocketError(WSAGetLastError());
	}

	NDebug::print() << "Accepted";
	ret = new NTcpSocket(m_timeout, client);
	ret->setTimeout(m_timeout);
	
	return ret;
}

NHostAddress NTcpSocket::peerAddress(void) const {
	NHostAddress addr;
	int len = 0;

	getpeername(m_sock, m_addr->ai_addr, &len);		
	addr.setAddress(m_addr->ai_addr);

	return addr;
}


NString NTcpSocket::peerName(void) const {
	return peerAddress().toString();
}


nuint16 NTcpSocket::peerPort(void) const {
	struct sockaddr_in *tmp;

	tmp = reinterpret_cast<sockaddr_in *>(m_addr->ai_addr);
	return ntohs(tmp->sin_port);
}



nint32 NTcpSocket::read(NDataStream *buffer) {
	nint32 bread = 0;
	fd_set fd;
	timeval timeout;
	nint32 sel = 0;
	socklen_t len = 0;
	nint32 numRead = -1;
	char tmp[2048];

	FD_ZERO(&fd);
	FD_SET(m_sock, &fd);
	
	timeout.tv_sec = m_timeout;
	timeout.tv_usec = 0;
	
	sel = select(m_sock + 1, &fd, NULL, NULL, &timeout);
	if (sel < 0) {
		throw NNetworkException(nerror(errno), m_host.toString(), 
			NException::NETWORK, NNetworkException::SOCK_ERROR);
	}
	
	if (sel == 0) {
		// timedout
		return 0;
	}
	
	*buffer = "";
	do { 
		memset(tmp, 0, sizeof(tmp));

		numRead = recvfrom(m_sock, tmp, sizeof(tmp), 0, m_addr->ai_addr, 
			&len);

		if (numRead < 0) {
			NDebug::print() << "I did not received an orderly shutdown: "
					 << WSAGetLastError();;
			return -1;
		}
		else {
			// There's action in a file descriptor but no data to read
			// it's likely that the remote peer disconnected
			if (sel == 1 && numRead == 0 && bread == 0) {
				return -1;
			}
		}
		
		bread += numRead;
		buffer->append(tmp, numRead);
	} while (numRead > 0);
	
	return bread;
}


nint32 NTcpSocket::read(NDataStream *buffer, nuint32 bytes) {
	nuint32 bread = 0;
	fd_set fd;
	timeval timeout;
	nint32 sel = 0;
	socklen_t len = 0;
	nint32 numRead = -1;
	char tmp[1];

	FD_ZERO(&fd);
	FD_SET(m_sock, &fd);
	
	timeout.tv_sec = m_timeout;
	timeout.tv_usec = 0;
	
	sel = select(m_sock + 1, &fd, NULL, NULL, &timeout);
	if (sel < 0) {
		throw NNetworkException(nerror(errno), m_host.toString(), 
			NException::NETWORK, NNetworkException::SOCK_ERROR);
	}
	
	if (sel == 0) {
		// timedout
		return 0;
	}
	
	*buffer = "";
	do { 
		memset(tmp, 0, sizeof(tmp));

		numRead = recvfrom(m_sock, tmp, 1, 0, m_addr->ai_addr, &len);

		if (numRead < 0) {
			NDebug::print() << "I did not received an orderly shutdown: "
					 << WSAGetLastError();;
			return -1;
		}
		else {
			// There's action in a file descriptor but no data to read
			// it's likely that the remote peer disconnected
			if (sel == 1 && numRead == 0 && bread == 0) {
				return -1;
			}
		}
		
		bread += numRead;
		buffer->append(tmp, numRead);
	} while (numRead > 0 && bread < bytes);
	
	return bread;
}


nint32 NTcpSocket::readLine(NDataStream *buffer) {
	nint32 bread = 0;
	fd_set fd;
	timeval timeout;
	nint32 sel = 0;
	socklen_t len = 0;
	nint32 numRead = -1;
	char tmp[1];

	FD_ZERO(&fd);
	FD_SET(m_sock, &fd);
	
	timeout.tv_sec = m_timeout;
	timeout.tv_usec = 0;
	
	sel = select(m_sock + 1, &fd, NULL, NULL, &timeout);
	if (sel == SOCKET_ERROR) {
		throwSocketError(WSAGetLastError());
	}
	
	if (sel == 0) {
		// timedout
		return -1;
	}
	
	*buffer = "";
	do { 
		memset(tmp, 0, sizeof(tmp));

		numRead = recvfrom(m_sock, tmp, sizeof(tmp), 0, m_addr->ai_addr, &len);
		if (numRead < 0) {
			NDebug::print() << "I did not received an orderly shutdown: "
					 << WSAGetLastError();;
			return -1;
		}
		else {
			// There's action in a file descriptor but no data to read
			// it's likely that the remote peer disconnected
			if (sel == 1 && numRead == 0 && bread == 0) {
				return -1;
			}
		}
		
		bread += numRead;
		buffer->append(tmp, numRead);
		if (tmp[0] == '\n' || tmp[0] == '\0') {
			break;
		}
	} while (numRead > 0);
	
	return bread;
}


nint32 NTcpSocket::write(const NDataStream &data, nuint32 bytes) {
	if (bytes == 0) {
		return send(m_sock, static_cast<const char *>(data.data()), data.size(), 0);
	}
		
	return send(m_sock, static_cast<const char *>(data.data()), bytes, 0);
}


nint32 NTcpSocket::writeLine(const NDataStream &data, nuint32 bytes) {
	NDataStream tmp = data;

	tmp += "\r\n";

	if (bytes == 0) {
		return send(m_sock, static_cast<const char *>(tmp.data()), tmp.size() + 2, 0);
	}
		
	return send(m_sock, static_cast<const char *>(tmp.data()), bytes, 0);
}