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
#ifndef NSQL_H_
#define NSQL_H_

#include "nobject.h"
#include "nstring.h"
#include "nhostaddress.h"
#include "nsqlquery.h"

#include "nsqlrecord.h"
#include "ndatastream.h"


/**
\file nsql.h NSql class definition
\see NMySQL class documentation for examples 
*/

/**
\class NSql 
\brief Base class for SQL manipulation
*/
class DllDeclSpec NSql: public NObject {
	public:
		/**
		\brief Constructs a NSql object
		*/
		NSql(void);


		/**
		\brief Constructs a NSql object
		\param user Database user
		\param pass Database password
		\param host Database host (i.e.: host where the database is running)
		*/
		NSql(const NString &user, const NString &pass, 
			const NHostAddress &host);
		

		/**
		\brief Constructs a NSql object
		\param user Database user
		\param pass Database password
		\param host Database host (i.e.: host where the database is running)
		\param port Database port
		*/
		NSql(const NString &user, const NString &pass, 
			const NHostAddress &host, nint16 port);


		/**
		\brief Destroys a NSql object
		*/
		virtual ~NSql(void);

		/**
		\brief Sets the database user 
		\param user Database user
		*/
		virtual void setUser(const NString &user);

		/**
		\brief Sets the database password
		\param pass Database password
		*/
		virtual void setPassword(const NString &pass);

		/**
		\brief Sets the database host
		\param host Database host (i.e.: host where the database is running)
		*/
		virtual void setHost(const NHostAddress &host);

		/**
		\brief Sets the database port
		\param port Database port
		*/
		virtual void setPort(nint16 port);

		/**
		\brief Sets the database name
		\param database Database name
		*/
		virtual void setDatabase(const NString &database);


		/**
		\brief Gets the database user
		\return Database user
		*/
		virtual NString getUser(void) const;

		/**
		\brief Gets the database password
		\return Database password
		*/
		virtual NString getPassword(void) const;

		/**
		\brief Gets the database host
		\return Database host (i.e.: host where the database is running)
		*/
		virtual NHostAddress getHost(void) const;

		/**
		\brief Gets the database port
		\return Database port
		*/
		virtual nint16 getPort(void) const;

		/**
		\brief Gets the database name
		\return The database name
		*/
		virtual NString getDatabase(void) const;


		/**
		\brief Connects to the database host
		*/
		virtual void connectToHost(void) = 0;

		/**
		\brief Disconnects from the database host
		*/
		virtual void disconnectFromHost(void) = 0;


		/**
		\brief Executes a SQL query identified by query
		\param query SQL query
		\return true in case of success or false otherwise
		*/
		virtual bool execSql(const NSqlQuery &query) = 0;
		

		/**
		\brief Gets the next record in the record set
		\return The next record in the record set or NULL if not existant
		*/
		virtual NSqlRecord *getNext(void) = 0;

		
		/**
		\brief Gets the previous record in the record set
		\return The previous record in the record set or NULL if not existant
		*/
		virtual NSqlRecord *getPrevious(void) = 0;

		/**
		\brief Gets the first record in the record set
		\return The first record in the record set or NULL if not existant
		*/
		virtual NSqlRecord *getFirst(void) = 0;

		/**
		\brief Gets the last record in the record set
		\return The last record in the record set or NULL if not existant
		*/
		virtual NSqlRecord *getLast(void) = 0;


		/**
		\brief Gets the last error from the database
		\return The last error from the database
		*/
		virtual NString getError(void) const = 0;
		
	protected:
		NString m_user;		/*!< Database user */
		NString m_password;	/*!< Database password */
		NHostAddress m_host;	/*!< Database host */
		nint16 m_port;		/*!< Database port */
		NString m_database;	/*!< Database name */

		/**
		\brief Sets the data of a record set
		\param record The record data to set feed up with data
		\param rowName The name of the row containing data
		\param rowData The data of the row
		*/
		void setRecordData(NSqlRecord *record, const NString &rowName, 
			const NVtype &rowData);


	private:	
		NSql(const NSql &other);
		NSql &operator=(const NSql &rhs);


};

#endif // NSQL_H_
