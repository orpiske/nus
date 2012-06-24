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
#include "nsqlquery.h"

/**
\file nsqlquery.cpp NSqlQuery class implementation
*/

NSqlQuery::NSqlQuery(void)
	: NObject(),
	m_query()
{

}


NSqlQuery::NSqlQuery(const NString &query)
	: NObject(),
	m_query(query)
{

}


NSqlQuery::NSqlQuery(const NSqlQuery &other)
	: NObject(),
	m_query(other.m_query)
{
	
}


NSqlQuery::~NSqlQuery(void) { 

}


bool NSqlQuery::bindValue(const NString &name, const NVtype &value) {
	if (m_query.find(name) != NString::NOT_FOUND) { 
		m_query.replace_first(name, value.toString());
		
		return true;
	}
	return false;
}


bool NSqlQuery::addBindValue(const NVtype &value) { 
	if (m_query.find("?") != NString::NOT_FOUND) { 
		m_query.replace_first("?", value.toString());
		
		return true;
	}

	return false;
}
 
void NSqlQuery::set(const NString &query) {
	m_query = query;
}


NString NSqlQuery::get(void) const {
	return m_query;
}
