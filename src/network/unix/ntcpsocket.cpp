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
\file linux/ntcpsocket.cpp NTcpSocket class implementation
*/

NTcpSocket::NTcpSocket(void)
	: NAbstractSocket(),
	m_addr(),
	m_sock(-1)
{
	init();
}

NTcpSocket::NTcpSocket(NHostAddress &host)
	: NAbstractSocket(host),
	m_addr(),
	m_sock(-1)
{
	init();
}


NTcpSocket::NTcpSocket(const NString &host, nuint16 port)
	: NAbstractSocket(host, port),
	m_addr(),
	m_sock(-1)
{
	init();
}

NTcpSocket::NTcpSocket(nuint16 timeout, nint32 sock, struct sockaddr_in client)
	: NAbstractSocket(),
	m_addr(),
	m_sock(sock)
{
	init();
	setTimeout(timeout);
	m_addr = client;
	
	m_host.setAddress(reinterpret_cast<struct sockaddr *>(&m_addr));
	setPort(ntohs(m_addr.sin_port));
}

NTcpSocket::~NTcpSocket(void) {

}

void NTcpSocket::setPort(nint16 port) { 
	NAbstractSocket::setPort(port);
	
	m_addr.sin_port = htons(m_port); 
}

void NTcpSocket::setSocketOptions(nint32 opt) { 
	int val = 1;
	
	NAbstractSocket::setSocketOptions(opt);
	
	// Will force binding and won't fail unless there's really is an active
	// listening socket. I.E.: state == LISTENING. 
	if (m_opt & REUSE_ADDRESS) { 
		setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	}
	
	// Enables keep-alive messages on connection oriented protocols like, tcp ;)
	if (m_opt & KEEPALIVE) { 
		setsockopt(m_sock, SOL_SOCKET, SO_KEEPALIVE, &val, sizeof(val));
	}
}


void NTcpSocket::init(void) {
	memset(&m_addr, 0, sizeof(m_addr));
	
	m_addr.sin_family = AF_INET;
}

void NTcpSocket::open(void) { 
	m_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (!m_sock == -1) { 
		throw NNetworkException(nerror(errno), "", NException::NETWORK, 
				NNetworkException::SOCKET_INIT_FAILED);
	}
	
}

void NTcpSocket::closeDevice(void) { 
	disconnectFromHost();
}

void NTcpSocket::disconnectFromHost(void) { 
	close(m_sock);
	m_sock = 0;
}

void NTcpSocket::connectToHost() { 
	int ret = 0;
	
	m_host.resolve();
	inet_aton(m_host.toString().toChar(), &m_addr.sin_addr);
	if (m_addr.sin_addr.s_addr == INADDR_NONE) {
		throw NNetworkException("Bad Address", m_host.toString(),
			NException::NETWORK, NNetworkException::SOCKET_INIT_FAILED);
	}
	
	ret = connect(m_sock, reinterpret_cast<struct sockaddr *>(&m_addr),
		      sizeof(m_addr));
	if (ret == -1) { 
		NString msg = nerror(errno);
		
		msg += NSTR(": ") + m_host.toString() + NSTR(":") + NString::number(m_port);
		throw NNetworkException(msg, m_host.toString(), 
			NException::NETWORK, NNetworkException::CONNECTION_FAILED);
	}
}

void NTcpSocket::execBind(void) { 
	int ret = 0;
	
	if (m_host.isNull()) { 
		m_addr.sin_addr.s_addr = INADDR_ANY;
	}
	else {
		m_addr.sin_addr.s_addr = inet_addr(m_host.toString().toChar());
		if (m_addr.sin_addr.s_addr == INADDR_NONE) {
			throw NNetworkException("Bad Address", m_host.toString(),
				NException::NETWORK, NNetworkException::SOCKET_INIT_FAILED);
		}
	}
	
	ret = bind(m_sock, reinterpret_cast<const struct sockaddr *>(&m_addr),
		   sizeof(m_addr));
	if (ret == -1) { 
		NString msg = nerror(errno);
		
		msg += NSTR(": ") + m_host.toString() + NSTR(":") + NString::number(m_port);
		throw NNetworkException(msg, m_host.toString(), NException::NETWORK,
			NNetworkException::SOCKET_INIT_FAILED);
	}
}


void NTcpSocket::setPeer(struct sockaddr_in addr) {
	m_addr = addr;
}


void NTcpSocket::setSock(int sock) {
	m_sock = sock;
}

void NTcpSocket::setupNewSocket(NTcpSocket *sock, struct sockaddr_in addr) {
	assert(sock);
	
	sock->setTimeout(m_timeout);
	sock->setReadBufferSize(m_readBufferSize);
	sock->setHost(m_host);
}


void NTcpSocket::execListen(void) {
	int ret = 0;
	
	execBind();
	ret = listen(m_sock, m_maxPendingConn);
	if (ret == -1) { 
		NString msg = nerror(errno);
		
		msg += NSTR(": ") + m_host.toString() + NSTR(":") + NString::number(m_port);
		throw NException(msg , NException::NETWORK);
	}
	
}


NTcpSocket *NTcpSocket::waitForConnected(void) { 
	int client  = 0;
	NTcpSocket *ret = NULL;
	struct sockaddr_in cli_addr;
	socklen_t len_inet = 0;
	
	len_inet = sizeof(cli_addr);
	client = accept(m_sock, reinterpret_cast<struct sockaddr *>(&cli_addr), 
			 &len_inet);
	if (client == -1) {
		delete ret;
		NString msg = nerror(errno);
		
		msg += NSTR(": ") + m_host.toString() + NSTR(":") + NString::number(m_port);
		throw NNetworkException(msg , m_host.toString(), 
				NException::NETWORK, NNetworkException::SOCKET_INIT_FAILED);
	}
	
	ret = new NTcpSocket(m_timeout, client, cli_addr);
	return ret;
	
}


NHostAddress NTcpSocket::peerAddress(void) const { 
	NHostAddress ret;
	
	ret.setAddress(reinterpret_cast<const struct sockaddr *>(&m_addr));
	return ret;
}


NString NTcpSocket::peerName(void) const {
	return peerAddress().toString();
}


nuint16 NTcpSocket::peerPort(void) const {
	return ntohs(m_addr.sin_port);
}


nint32 NTcpSocket::read(NDataStream *buffer) { 
	nint32 bread = 0;
	fd_set fd;
	timeval timeout;
	nint32 sel = 0;
	socklen_t len = 0;
	nint32 numRead = -1;
	char tmp[m_readBufferSize];

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
		return 0;
	}
	
	*buffer = "";
	do { 
		memset(tmp, 0, sizeof(tmp));

		numRead = recvfrom(m_sock, &tmp, sizeof(tmp), MSG_DONTWAIT,
				    reinterpret_cast<struct sockaddr *>(&m_addr),
				    &len);
		if (numRead < 0) {
			break;
		}
		else {
			// There's action in a file descriptor but no data to read
			// so it's likely that the remote peer disconnected
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

		numRead = recvfrom(m_sock, &tmp, 1, MSG_DONTWAIT,
				    reinterpret_cast<struct sockaddr *>(&m_addr),
				    &len);
		if (numRead < 0) {
			break;
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

		numRead = recvfrom(m_sock, &tmp, sizeof(tmp), MSG_DONTWAIT,
				    reinterpret_cast<struct sockaddr *>(&m_addr),
				    &len);

		if (numRead < 0) {
			NDebug::print() << "I did not received an orderly shutdown: "
						<< nerror(errno);
			return -1;
		}
		else {
			// There's action in a file descriptor but no data to read
			// it's likely that the remote peer disconnected
			if (sel == 1 && numRead == 0 && bread == 0) {
				return -1;
			}

		}
		if (tmp[0] == '\n' || tmp[0] == '\0' || numRead < 0) {
			break;
		}
		
		bread += numRead;
		buffer->append(tmp, numRead);
	} while (numRead > 0);
	
	return bread;
}

nint32 NTcpSocket::write(const NDataStream &data, nuint32 bytes) { 
	if (bytes == 0) {
		return send(m_sock, data.data(), data.size(), MSG_DONTWAIT);
	}
		
	return send(m_sock, data.data(), bytes, MSG_DONTWAIT);
}


nint32 NTcpSocket::writeLine(const NDataStream &data, nuint32 bytes) {
	NDataStream tmp = data;

	tmp += "\r\n";

	if (bytes == 0) {
		return send(m_sock, tmp.data(), tmp.size(), MSG_DONTWAIT);
	}
		
	return send(m_sock, tmp.data(), bytes, MSG_DONTWAIT);
}
