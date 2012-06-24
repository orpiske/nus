// LICENSE: (Please see the file COPYING for details)
//
// NUS - Nemesis Utilities System: A C++ application development framework 
// Copyright (C) 2006, 2007 Otavio Rodolfo Piske
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
#include "nbaseoutput.h"

/**
\file nbaseoutput.cpp Base class for output printing
*/

NBaseOutput::NBaseOutput(void)
		: m_base(DECIMAL)
{ 

}

NBaseOutput::~NBaseOutput(void) { 
	fflush(NULL);
}

NBaseOutput &NBaseOutput::setBase(Base base) {
	m_base = base;

	return *this;
}

void NBaseOutput::print(nint32 val) {
	switch (m_base) {
		case HEXADECIMAL: {
			printf("%x", val);
			break;
		}
		case OCTAL: {
			printf("%o", val);
			break;
		}
		case DECIMAL:
		default: {
			printf("%d", val);
			break;
		}
	}
}

void NBaseOutput::print(nuint32 val) {
	switch (m_base) {
		case HEXADECIMAL: {
			printf("%x",val);
			break;
		}
		case OCTAL: {
			printf("%o", val);
			break;
		}
		case DECIMAL:
		default: {
			printf("%u", val);
			break;
		}
	}
}


void NBaseOutput::print(nint64 val) {
	//switch (m_base
	printf("%lld", val);
}

void NBaseOutput::print(nuint64 val) {
	printf("%llu", val);
}


void NBaseOutput::print(double d) {
	printf("%f", d);
}


void NBaseOutput::print(char c) {
	printf("%c", c);
}


void NBaseOutput::print(const NString &str) {
	printf("%s", str.toChar());
}


void NBaseOutput::print(const void *ptr) { 
	printf("%p", ptr);
}


void NBaseOutput::print(const char *str) { 
	printf("%s", str);
}



void NBaseOutput::println(const NString &str) {
	printf("%s\n", str.toChar());
}
