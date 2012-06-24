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
#ifndef NTIME_H
#define NTIME_H

/**
\file ntime.h Class definition for NTime
*/

#include <ctime>

#include "errdefs.h"
#include "nwarning.h"
#include "nstring.h"
#include "nlocaltime.h"

/**
\brief NTime class provides an easy to use time manipulation class
*/
class DllDeclSpec NTime {
	public:
		/**
		\brief Constructs a NTime class without any particular time
		*/
		NTime(void);
	
		/**
		\brief Destroys a NTime class freeing any used resources
		*/
		~NTime(void);

		/**
		\brief Gets the current time
		\return The current time
		*/
		NString now(void) const;
		
		/**
		\brief Gets the current time in a given format
		\param format Time format as defined by strftime function
		\return The current time in the given format
		*/
		NString now(const NString &format) const;

	private:
		struct tm m_time;

		void init(void) const;

		NTime(const NTime &tm);
		NTime &operator=(const NTime &tm);	
};

#endif // NTIME_H
