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
#ifndef CLIENT_APP_H
#define CLIENT_APP_H

#include "ndefs.h"
#include "nobject.h"
#include "nopt.h"
#include "ntcpsocket.h"
#include "nstring.h"
#include "noutput.h"

class ClientApp: public NObject {
	public:
		ClientApp(void);
		
		bool setHost(const NOpt<ClientApp> &opt);
		bool setPort(const NOpt<ClientApp> &opt);
		
		void run(void);
		
	private:
		NString m_host;
		nuint16 m_port;
		NTcpSocket m_sock;
};

#endif // CLIENT_APP_H

