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
// This example shows how to use the NFile class to manipulate files
#include "ndefs.h"
#include "nfile.h"
#include "nstring.h"
#include "noutput.h"

#include <cstdlib>

int main(void) { 
	NFile tmp;
	
	tmp.setFileName("testfile.tmp");
	if (tmp.exists()) { 
		NMessage::print() << "File " << tmp.getFileName() << " does not exist";
	}
	
	try {
		// Opening a file may throw a NIOException exception 
		// Put file in read-only mode to see it happening
		tmp.open(NIODevice::ReadWrite);
		
		// If the file was openned, write something to it
		tmp.write("test");
	} 
	catch (NIOException &e) { 
		NMessage::print() << "Error: " << e.getDescription();
		
		if (e.getResource() == NIOException::FILE) {
			NMessage::print() << "On file: " << e.getResourceName();
		}
		
		if (e.getFlag() == NIOException::IO_ACCESS_DENIED) {
			NWarning::print() << "Access Denied";
		}
	
		exit(1);
	}

	return 0;
}
