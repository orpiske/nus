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
#ifndef NDATETIME_H
#define NDATETIME_H

/**
\file ndatetime.h Class definition for NDateTime
*/

#include "ndate.h"
#include "ntime.h"
#include "nstring.h"

/**
\brief NDateTime class provides an easy to use date/time manipulation class.
*/
class DllDeclSpec NDateTime {
	public:
		/**
		\brief Gets the current time/date
		\return The current time/date
		*/	
		static NString now(void);
	    
		/**
		\brief Gets the current time/date
		\param dateFormat Date format as defined by strftime function
		\param timeFormat Time format as defined by strftime function
		\return The current time/date in the given format
		*/
		static NString now(const NString &dateFormat, const NString &timeFormat);
};

#endif // NDATETIME_H
