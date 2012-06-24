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
#ifndef NMYSQL_H_
#define NMYSQL_H_

#include "nobject.h"
#include "nstring.h"
#include "nhostaddress.h"
#include "nsql.h"
#include "nsqlquery.h"
#include "nsqlrecord.h"
#include "nsqlresultset.h"

#include <mysql.h>
#include <errmsg.h>


/**
\file nmysql.h NMySql class definition
\see NMySQL class documentation for examples 
\example nsqlapp.cpp
\include nsqlapp.h
\include ex_nmysql.cpp
*/

/**
\class NMySql 
\brief Base class for connecting to a MySQL database
\see NSql for documentation
*/
class DllDeclSpec NMySql: public NSql { 
	public:
		/**
		\brief Constructor
		*/
		NMySql(void);

		/**
		\brief Constructs a NMySql object
		\param user Database user
		\param pass Database password
		\param host Database host (i.e.: host where the database is running)
		*/
		NMySql(const NString &user, const NString &pass, 
			const NHostAddress &host);

		/**
		\brief Constructs a NMySql object
		\param user Database user
		\param pass Database password
		\param host Database host (i.e.: host where the database is running)
		\param port Database port
		*/
		NMySql(const NString &user, const NString &pass, 
			const NHostAddress &host, nint16 port);

		/**
		\brief Destroys a NMySql object
		*/
		~NMySql(void);

		
		void connectToHost(void);
		void disconnectFromHost(void);
		bool execSql(const NSqlQuery &query);
		
		NSqlRecord *getNext(void);
		NSqlRecord *getPrevious(void);
		NSqlRecord *getFirst(void);
		NSqlRecord *getLast(void);

		NString getError(void) const;

	private:	
		NMySql(const NMySql &other);
		NMySql &operator=(const NMySql &rhs);

		MYSQL *m_handle;
		NSqlResultSet m_resultSet;
		nuint64 m_pos;
		bool m_connected;

		void init(void);

		void clearResultSet(void);
		NSqlRecord *loadRow(MYSQL_RES *result, MYSQL_ROW row);
		void loadResultSet(void);

		NString getDetailedError(void) const;
		


}; 

#endif // NMYSQL_H_
