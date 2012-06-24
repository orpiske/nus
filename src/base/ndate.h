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
#ifndef NDATE_H
#define NDATE_H

/**
\file ndate.h Class definition for NDate class
*/
#include <ctime>

#include "nwarning.h"
#include "nstring.h"
#include "nlocaltime.h"

/**
\brief NDate class provides an easy to use date manipulation class.
*/
class DllDeclSpec NDate {
	public:
		/**
		\brief Constructs a NDate class without any particular date
		*/
		NDate(void);
		/**
		\brief Destroys a NDate class freeing any resource used
		*/
		~NDate(void);

		/**
		\brief Gets the current date
		\return The current date
		*/
		NString today(void) const;
		
		/**
		\brief Gets the current date in a given format
		\param format Date format as defined by strftime function
		\return The current date in the given format
		*/
		NString today(const NString &format) const;

	private:
		struct tm m_date;

		void init(void) const;

		NDate(const NDate &tm);
		NDate &operator=(const NDate &tm);
};

#endif // NDATE_H
