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
#include "nmysql.h"

/**
\file nmysql.cpp NMySql class implementation
*/

NMySql::NMySql(void)
	: NSql(),
	m_handle(NULL),
	m_resultSet(),
	m_pos(0),
	m_connected(false)
{ 
	init();
} 

NMySql::NMySql(const NString &user, const NString &pass, 
	const NHostAddress &host)
	: NSql(user, pass, host),
	m_handle(NULL),
	m_resultSet(),
	m_pos(0),
	m_connected(false)
{ 
	init();
}


NMySql::NMySql(const NString &user, const NString &pass, 
	const NHostAddress &host, nint16 port)
	: NSql(user, pass, host, port),
	m_handle(NULL),
	m_resultSet(),
	m_pos(0),
	m_connected(false)
{
	init();
}


NMySql::~NMySql(void) { 
	disconnectFromHost();
	mysql_library_end();
	m_handle = NULL;
}

void NMySql::init(void) { 
	m_handle = mysql_init(NULL);
	if (!m_handle) { 
		throw NMemException("Not enough memory to initialize MySql driver",
			NException::DBAL);
	}
}

NString NMySql::getError(void) const {
	nuint32 err_val = 0;
	NString ret = "";
	

	err_val = mysql_errno(m_handle);
	switch (err_val) { 
		case CR_SOCKET_CREATE_ERROR: { 
			ret = "Can't create socket";
			break;
		}
		case CR_CONNECTION_ERROR: { 
			ret = "Can't connect to local server at ";
			ret += m_host.toString();
			break;
		}
		case CR_CONN_HOST_ERROR: { 
			ret = "Can't connect to server at ";
			ret += m_host.toString();
			break;
		}
		case CR_IPSOCK_ERROR: { 
			ret = "Can't create TPC/IP socket";
			break;
		}
		case CR_UNKNOWN_HOST: { 
			ret = "Unknown host: ";
			ret += m_host.toString();
			break;
		}
		case CR_SERVER_GONE_ERROR: { 
			ret = "The server has gone away or quit";
			break;
		}
		case CR_VERSION_ERROR: { 
			ret = "Protocol mismatch between server and client";
			ret += getDetailedError();
			break;
		}
		case CR_OUT_OF_MEMORY: { 
			ret = "Client do not have enough memory to complete the request";
			break;
		}
		case CR_WRONG_HOST_INFO: { 
			ret = "Wrong host info";
			break;
		}
		case CR_LOCALHOST_CONNECTION: { 
			ret = "Localhost via unix socket";
			break;
		}
		case CR_TCP_CONNECTION: { 
			ret = "TCP connection error";
			ret += getDetailedError();
			break;
		}
		case CR_SERVER_HANDSHAKE_ERR: { 
			ret = "Connection handshake error";
			break;
		}
		case CR_SERVER_LOST: { 
			ret = "Lost connection with MySQL server during query";
			break;
		}
		case CR_COMMANDS_OUT_OF_SYNC: { 
			ret = "Commands out of sync. You can't run this command now";
			break;
		}
		case CR_NAMEDPIPE_CONNECTION: 
		case CR_NAMEDPIPEWAIT_ERROR: 
		case CR_NAMEDPIPEOPEN_ERROR:
		case CR_NAMEDPIPESETSTATE_ERROR: { 
			ret = "Unknown named pipe error: ";
			ret += getDetailedError();
			break;
		}
		
		case CR_CANT_READ_CHARSET: { 
			ret = "Can't initialize charset: ";
			ret += getDetailedError();
			break;
		}
		case CR_NET_PACKET_TOO_LARGE: { 
			ret = "Got packet bigger than 'max_allowed_bytes'";
			break;
		}
		case CR_EMBEDDED_CONNECTION: { 
			ret = "Embedded connection error";
			ret += getDetailedError();
			break;
		}
		case CR_PROBE_SLAVE_STATUS: { 
			ret = "Error on SHOW SLAVE STATUS";
			break;
		}
		case CR_PROBE_SLAVE_HOSTS: { 
			ret = "Error on SHOW SLAVE HOSTS";
			break;
		}
		case CR_PROBE_SLAVE_CONNECT: { 
			ret = "Error connecting to slave";
			break;
		}
		case CR_PROBE_MASTER_CONNECT: { 
			ret = "Error connecting to master";
			break;
		}
		case CR_SSL_CONNECTION_ERROR: { 
			ret = "SSL connection error";
			break;
		}
		case CR_MALFORMED_PACKET: { 
			ret = "Malformed packet";
			ret += getDetailedError();
			break;
		}
		case CR_WRONG_LICENSE: { 
			ret = "This client library is not licensed for use with";
			ret += " the current server";
			break;
		}
		case CR_NULL_POINTER: { 
			ret = "Invalid use of NULL pointer";
			break;
		}
		case CR_NO_PREPARE_STMT: { 
			ret = "Statement not prepared";
			break;
		}
		case CR_PARAMS_NOT_BOUND: { 
			ret = "No data supplied for parameters in prepared statement";
			break;
		}
		case CR_DATA_TRUNCATED: { 
			ret = "Data truncated";
			ret += getDetailedError();
			break;
		}
		case CR_NO_PARAMETERS_EXISTS: { 
			ret = "No parameters exist in statement";
			break;
		}
		case CR_INVALID_PARAMETER_NO: { 
			ret = "Invalid parameter number";
			break;
		}
		case CR_INVALID_BUFFER_USE: { 
			ret = "Can't send long data";
			ret += getDetailedError();
			break;
		}
		case CR_UNSUPPORTED_PARAM_TYPE: { 
			ret = "Unsupported param type";
			break;
		}
		case CR_SHARED_MEMORY_CONNECTION: 
		case CR_SHARED_MEMORY_CONNECT_REQUEST_ERROR: 
		case CR_SHARED_MEMORY_CONNECT_ANSWER_ERROR: 
		case CR_SHARED_MEMORY_CONNECT_FILE_MAP_ERROR: 
		case CR_SHARED_MEMORY_CONNECT_MAP_ERROR: 
		case CR_SHARED_MEMORY_FILE_MAP_ERROR: 
		case CR_SHARED_MEMORY_MAP_ERROR: 
		case CR_SHARED_MEMORY_EVENT_ERROR: 
		case CR_SHARED_MEMORY_CONNECT_ABANDONED_ERROR: 
		case CR_SHARED_MEMORY_CONNECT_SET_ERROR: { 
			ret = "Shared memory error: ";
			ret += getDetailedError();
			break;
		}
		case CR_CONN_UNKNOW_PROTOCOL: { 
			ret = "Wrong or unknown protocol";
			break;
		}
		case CR_INVALID_CONN_HANDLE: { 
			ret = "Invalid connection handle";
			break;
		}
		case CR_SECURE_AUTH: { 
			ret = "Connection using old (pre-4.1.1) authentication";
			ret += " protocol refused";
			break;
		}
		case CR_FETCH_CANCELED: { 
			ret = "Row retrieval was canceled";
			break;
		}
		case CR_NO_DATA: { 
			ret = "Attempt to read column without prior fetch";
			break;
		}
		case CR_NO_STMT_METADATA: { 
			ret = "Prepared statement contains no metadata";
			break;
		}
		case CR_NO_RESULT_SET: { 
			ret = "Attempt to read a row without an associated result set";
			break;
		}
		case CR_NOT_IMPLEMENTED: { 
			ret = "This feature is not implemented yet";
			break;
		}
		case CR_SERVER_LOST_EXTENDED: { 
			ret = "Lost connection with server at ";
			ret = ret + m_host.toString() + ". ";
			ret += getDetailedError();

			break;
		}
		case CR_UNKNOWN_ERROR: 
		default: { 
			ret = "Unknown error: ";
			ret += getDetailedError();
			break;
		}	
	}

	return ret;
}

NString NMySql::getDetailedError(void) const {
	NString ret; 
	const char *details = NULL; 
	
	details = mysql_error(m_handle);
	if (details) { 
		ret = "MySQL error message is: ";
		ret += details;
	}

	return ret;
}


void NMySql::connectToHost(void) { 
	MYSQL *ret = NULL;

	if (!m_handle) { 
		throw NException("You don't have setup a DB connection", 
			NException::DBAL);
	}

	m_host.resolve();
	NDebug::print() << "Connecting to: " << m_host.toString();
	NDebug::print() << "User: " << m_user;
	NDebug::print() << "Port: " << m_port;
	NDebug::print() << "Database: " << m_database;

	ret = mysql_real_connect(m_handle, m_host.toString().toChar(),
		m_user.toChar(), m_password.toChar(), m_database.toChar(), 
		m_port, NULL, 0);

	if (ret != m_handle) {
		throw NException(getError(), NException::DBAL);
	}

	m_connected = true;
	
}


void NMySql::disconnectFromHost(void) { 
	if (m_handle) { 
		mysql_close(m_handle);
	}

	
	m_connected = false;
}


bool NMySql::execSql(const NSqlQuery &query) { 
	nint32 ret = 0;
	NString statement;

	if (!m_connected) { 
		throw NException("You don't have setup a DB connection", 
			NException::DBAL);
	}

	statement = query.get();

	ret = mysql_query(m_handle, statement.toChar());
	if (ret != 0) {
		NDebug::print() << "Error executing last statement: " 
			<< getDetailedError();
		
		return false;
	}

	loadResultSet();
	return true;
}

void NMySql::clearResultSet(void) {
	NSqlRecord *rec = NULL;

	// We use use m_resultSet.size() instead of (m_resultSet.size() - 2)
	// because the EOD terminators will be re-placed at the end of this 
	// method.
	for (nuint64 i = 0; i < m_resultSet.size(); i++) { 
		rec = m_resultSet.at(i);	
		delete rec;
	}

	m_resultSet.clear();
	m_resultSet.append(NULL);
}

NSqlRecord *NMySql::loadRow(MYSQL_RES *result, MYSQL_ROW row) {
	NSqlRecord *ret = NULL;
	MYSQL_FIELD *fields = NULL;
	nuint32 num_fields = 0;

	num_fields = mysql_num_fields(result);
	fields = mysql_fetch_fields(result);
	if (num_fields > 0) { 
		ret = new NSqlRecord;
	
		for (nuint32 i = 0; i < num_fields; i++) { 
			NString tmp = row[i];
			
	
			NString name(fields[i].name);
			NVtype rowData(tmp);
	
			NDebug::print() << "Pass " << i << " loaded field " << name 
				<< " with data " << rowData.toString();
	
			NSql::setRecordData(ret, name, rowData);
		}
	}
	
	
	return ret;
}

void NMySql::loadResultSet(void) { 
	MYSQL_RES *result = NULL;
	MYSQL_ROW row;

	my_ulonglong count = 0;
	
	count = mysql_affected_rows(m_handle);
	NDebug::print() << "Affected rows: " << count;
	
	result = mysql_store_result(m_handle);
	if (!result) { 
		if (mysql_field_count(m_handle) > 0) {
			throw NException(getError(), NException::DBAL);
		}
	}
	else {
		clearResultSet();
		while ((row = mysql_fetch_row(result))) { 
			m_resultSet.append(loadRow(result, row));
		};
		m_resultSet.append(NULL);
		mysql_free_result(result);
	}
}

NSqlRecord *NMySql::getNext(void) { 
	// It uses (m_resultSet.size() - 2) because the start of data and 
	// end of data place holders.
	NDebug::print() << "Recordset position: " << m_pos << " of " 
		<< (m_resultSet.size() - 2);

	if (m_resultSet.size() > 0 && m_pos < (m_resultSet.size() - 2)) {
		m_pos++;
		return m_resultSet.at(m_pos);
	}

	return NULL;
}


NSqlRecord *NMySql::getPrevious(void) { 
	if (m_pos != 0) {
		m_pos--;
		return m_resultSet.at(m_pos);
		
	}

	return NULL;
}


NSqlRecord *NMySql::getFirst(void) { 
	// It uses (m_resultSet.size() - 2) because the start of data and 
	// end of data place holders.
	if ((m_resultSet.size() - 2) > 0) {
		m_pos++;
		return m_resultSet.at(1);
	}

	return NULL;
}


NSqlRecord *NMySql::getLast(void) { 
	return m_resultSet.last();
}
