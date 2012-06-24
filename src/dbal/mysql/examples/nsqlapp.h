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
#ifndef NSQLAPP_H_
#define NSQLAPP_H_

#include "ndefs.h"
#include "nobject.h"
#include "nstring.h"
#include "nsql.h"
#include "nmysql.h"
#include "nopt.h"
#include "ngetopt.h"

class NSqlApp: public NObject {
	public:
		NSqlApp(void);
		~NSqlApp(void);

		bool setPort(const NOpt<NSqlApp> &opt);
		bool setHost(const NOpt<NSqlApp> &opt);
		bool setUser(const NOpt<NSqlApp> &opt);
		bool setPassword(const NOpt<NSqlApp> &opt);
		bool setDatabase(const NOpt<NSqlApp> &opt);

		int run(void);

	private:
		nint16 m_port;
		NString m_host;
		NString m_user;
		NString m_password;
		NString m_database;
		NMySql m_db;

		void runQuery(void);
};

#endif // NSQLAPP_H_