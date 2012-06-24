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
#include "ntime.h"

/**
\file ntime.cpp Ntime class implementation
*/

NTime::NTime(void)
	: m_time() 
{
	
}


NTime::~NTime(void) {
	
}


void NTime::init(void) const {
	time_t tmpTime;

	tmpTime = time(NULL);
	
	n_localtime(m_time, tmpTime);
}


NString NTime::now(void) const {
	return now("%H:%M:%S");
}


NString NTime::now(const NString &format) const {
	char strTime[10];
	NString ret;

	init();
	memset(strTime, 0, sizeof(strTime));
	strftime(strTime, sizeof(strTime), format.toChar(), &m_time);
	ret = strTime;

	return ret;
}
