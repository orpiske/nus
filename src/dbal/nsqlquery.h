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
#ifndef NSQLQUERY_H_
#define NSQLQUERY_H_

#include "nobject.h"
#include "nstring.h"
#include "nvtype.h"


/**
\file nsqlquery.h NSqlQuery class definition
*/

/**
\class NSqlQuery
\brief Base class for SQL Queries manipulation
*/
class DllDeclSpec NSqlQuery: public NObject {
	public: 
		/**
		\brief Constructs a NSqlQuery object
		*/
		NSqlQuery(void);

		/**
		\brief Constructs a NSqlQuery object
		\param query SQL query
		*/
		NSqlQuery(const NString &query);

		/**
		\brief Copy constructor
		\param other Object to be copied
		*/
		NSqlQuery(const NSqlQuery &other);

		/**
		\brief Destroys a NSqlQuery object
		*/
		~NSqlQuery(void);

		/**
		\brief Bind an identified mask name to a value
		\param name Mask name
		\param value Value to be bound.
		\return true in case of success or false otherwise
		*/
		bool bindValue(const NString &name, const NVtype &value);

		/**
		\brief Bind an predefined mask name to a value
		\param value Value to be bound.
		\return true in case of success or false otherwise
		*/
		bool addBindValue(const NVtype &value);


		/**
		\brief Sets the current query
		\param query SQL query
		*/ 
		void set(const NString &query);

		/**
		\brief Gets the current query
		\return The current query
		*/
		NString get(void) const;

	private:
		NString m_query;
};

#endif // NSQLQUERY_H_
