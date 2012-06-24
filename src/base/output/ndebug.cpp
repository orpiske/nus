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
#include "ndebug.h"

/**
\file ndebug.cpp Class implementation for NDebug
*/

NDebug::NDebug(void)
	: NBaseOutput()
{}


NDebug::~NDebug(void) {
#ifdef NLIB_DEBUG
	printf("\n");
#endif // NLIB_DEBUG
}


NDebug NDebug::print(void) { 
	NDebug tmp;
	
#ifdef NLIB_DEBUG
	NBaseOutput::print("[DEBUG] ");

#endif // NLIB_DEBUG
	return tmp;

}


NDebug &NDebug::operator<<(nint32 val) {
#ifdef NLIB_DEBUG
	NBaseOutput::print(val);
#endif // NLIB_DEBUG
	
	return *this;
}

NDebug &NDebug::operator<<(nuint32 val) {
#ifdef NLIB_DEBUG
	NBaseOutput::print(val);
#endif // NLIB_DEBUG
	
	return *this;
}


NDebug &NDebug::operator<<(nint64 val) {
#ifdef NLIB_DEBUG
	NBaseOutput::print(val);
#endif // NLIB_DEBUG
	
	return *this;
}

NDebug &NDebug::operator<<(nuint64 val) {
#ifdef NLIB_DEBUG
	NBaseOutput::print(val);
#endif // NLIB_DEBUG
	
	return *this;
}


NDebug &NDebug::operator<<(double d) {
#ifdef NLIB_DEBUG
	NBaseOutput::print(d);
#endif // NLIB_DEBUG
	
	return *this;
}


NDebug &NDebug::operator<<(char c) {
#ifdef NLIB_DEBUG
	NBaseOutput::print(c);
#endif // NLIB_DEBUG
	
	return *this;
}

NDebug &NDebug::operator<<(const NString &str) {
#ifdef NLIB_DEBUG
	NBaseOutput::print(str);
#endif // NLIB_DEBUG
	
	return *this;
}


NDebug &NDebug::operator<<(const void *ptr) {
#ifdef NLIB_DEBUG
	NBaseOutput::print(ptr);
#endif // NLIB_DEBUG
	
	return *this;
}


NDebug &NDebug::operator<<(const char *str) {
#ifdef NLIB_DEBUG
	NBaseOutput::print(str);
#endif // NLIB_DEBUG
	
	return *this;
}
