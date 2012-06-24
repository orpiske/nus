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
#include "nwarning.h"

/**
\file nwarning.cpp NWarning class implementation
*/

NWarning::NWarning(void)
	: NBaseOutput()
{}


NWarning::~NWarning(void) {
	NBaseOutput::print(" ***");
	NBaseOutput::print(RESET);
	NBaseOutput::print("\n");
}


NWarning NWarning::print(void) { 
	NWarning tmp;
	NBaseOutput::print(RED);
	NBaseOutput::print("*** ");
	return tmp;
}


NWarning &NWarning::operator<<(nint32 val) {
	NBaseOutput::print(val);
	return *this;
}

NWarning &NWarning::operator<<(nuint32 val) {
	NBaseOutput::print(val);
	return *this;
}


NWarning &NWarning::operator<<(nint64 val) {
	NBaseOutput::print(val);
	return *this;
}

NWarning &NWarning::operator<<(nuint64 val) {
	NBaseOutput::print(val);
	return *this;
}


NWarning &NWarning::operator<<(double d) {
	NBaseOutput::print(d);
	return *this;
}


NWarning &NWarning::operator<<(char c) {
	NBaseOutput::print(c);
	return *this;
}

NWarning &NWarning::operator<<(const NString &str) {
	NBaseOutput::print(str);
	return *this;
}


NWarning &NWarning::operator<<(const void *ptr) {
	NBaseOutput::print(ptr);
	return *this;
}


NWarning &NWarning::operator<<(const char *str) {
	NBaseOutput::print(str);
	return *this;
}
