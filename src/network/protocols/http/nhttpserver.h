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
#ifndef NHTTPSERVER_H_
#define NHTTPSERVER_H_

#include "nobject.h"
#include "ntcpsocket.h"
#include "nopt.h"
#include "nhttprequest.h"
#include "nhttpresponse.h"

class NHttpServer: public NObject {
	public:
		NHttpServer(void);
		
		virtual void setPort(nuint16 port);
		virtual void setListenAddr(const NString &host);
				
		void run(void);
	protected:
		virtual void handleConnection(NTcpSocket *client) = 0;
		NHttpRequest m_request;
		NHttpResponse m_response;
		
	private:
		NTcpSocket m_sock;
				
		
		
};

#endif /*NHTTPSERVER_H_*/
