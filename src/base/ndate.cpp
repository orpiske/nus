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
#include "ndate.h"

/**
\file ndate.cpp NDate implementation
*/

NDate::NDate(void)
	: m_date()
{

}


NDate::~NDate(void) {}


void NDate::init(void) const {
	time_t tmpDate;

	tmpDate = time(NULL);
	
	n_localtime(m_date, tmpDate);
}


NString NDate::today(void) const {
	return today("%d/%m/%y");
}


NString NDate::today(const NString &format) const {
	char strDate[10];
	NString ret;

	init();
	memset(strDate, 0, sizeof(strDate));
	strftime(strDate, sizeof(strDate), format.toChar(), &m_date);
	ret = strDate;

	return ret;
}
