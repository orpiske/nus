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
#ifndef NLOCALTIME_H
#define NLOCALTIME_H

/**
\file nlocaltime.h Internally used hack to deal with different datetime format
available in different operating systems
\note DO NOT USE out of NUS.
*/

// This is another hack to deal with different time/date functions among
// OSes and Compilers.

#undef n_localtime
#if defined (_MSC_VER)
#define n_localtime(m_time, tmpTime) \
{ \
	if (localtime_s(const_cast<tm *>(&m_time), &tmpTime) != 0) { \
		NString msg; \
		NWarning::print() << \
			msg.arg("Unable to obtain current date/time: %s", nerror(errno));\
	} \
 } /*!< Hack to lower level local time funtion */
#elif defined(__WIN32) && defined (__GNUC__)
#define n_localtime(m_time, tmpTime) \
{\
	struct tm *my_tmp = localtime(&tmpTime); \
	if (my_tmp) { \
		NString msg; \
		memcpy((void *)&m_time, my_tmp, sizeof(m_time)); \
		NWarning::print() << msg.arg("Unable to obtain current date/time: %s", nerror(errno));\
	} \
} /*!< Hack to lower level local time funtion */
#else
#define n_localtime(m_time, tmpTime) \
{ \
	if (!localtime_r(&tmpTime, const_cast<tm *>(&m_time))) { \
		NString msg; \
		NWarning::print() << \
			msg.arg("Unable to obtain current date/time: %s", nerror(errno));\
	} \
} /*!< Hack to lower level local time funtion */
#endif

#endif // NLOCALTIME_H_
