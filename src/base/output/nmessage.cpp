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
#include "nmessage.h"

/**
\file nmessage.cpp NMessage class implementation
*/

NMessage::NMessage(void)
	: NBaseOutput()
{

}


NMessage::~NMessage(void) {
	printf("\n");
}


NMessage NMessage::print(void) { 
	NMessage ret;
	
	return ret;
}


NMessage &NMessage::operator<<(nint32 val) {
	NBaseOutput::print(val);
	return *this;
}


NMessage &NMessage::operator<<(nuint32 val) {
	NBaseOutput::print(val);
	return *this;
}


NMessage &NMessage::operator<<(nint64 val) {
	NBaseOutput::print(val);
	return *this;
}


NMessage &NMessage::operator<<(nuint64 val) {
	NBaseOutput::print(val);
	return *this;
}


NMessage &NMessage::operator<<(double d) {
	NBaseOutput::print(d);
	return *this;
}


NMessage &NMessage::operator<<(char c) {
	NBaseOutput::print(c);
	return *this;
}

NMessage &NMessage::operator<<(const NString &str) {
	NBaseOutput::print(str);
	return *this;
}


NMessage &NMessage::operator<<(const void *ptr) {
	NBaseOutput::print(ptr);
	return *this;
}


NMessage &NMessage::operator<<(const char *str) {
	NBaseOutput::print(str);
	return *this;
}
