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
#include "ndatastream.h"
#include "nstring.h"
#include "noutput.h"

int main(void) {
	NDataStream data;
	NDataStream num;
	nint16 val = 666; // 0x29a


	// Operators: you can use then to set or append to a NDataStream
	data = "teste";
	data += 0; // This one goes as a nint32, thus will use 4 bytes.
	data += "abc";
	data += val;
	data += "-end-";
	
	// The size() method displays the current size of the data 
	NMessage::print() << "Size: " << data.size();

	// You can use subscript operators to access data. 
	for (nuint32 i = 0; i < data.size(); i++) {
		NMessage::print() << NString().arg("%02x = %c", data[i], data[i]);
	}

	// Operators: they accept several data types, including short ints
	num = val;
	val = 0;
	NMessage::print() << NString().arg("%02x = %i", val, val);
	

	// And you can convert it back to its original type
	val = num.toInt16();
	NMessage::print() << NString().arg("%02x = %i\n", val, val);
	
	
	// You can convert it to a string, too
	NMessage::print() << "1) Data: " << data.toString();
	
	try {
		// You can also define the range ...
		NMessage::print() << "2) Data: " << data.toString(2, 10);
		
		// However, if you exceed the bounds of the stream it will
		// throw a NException exception. Be careful.
		NMessage::print() << "3) Data: " << data.toString(89, 1023);
	}
	catch (NException &e) {
		NWarning::print() << "Out of bounds: " << e.getDescription();
	}
		
	val = 0;

	// You may set the byte ordering:
	num.setByteOrder(NDataStream::N_LITTLE_ENDIAN);
	num = 666; // 0x29a
	
	// Again, be careful: it affects the order in which bytes are stored
	for (nuint32 i = 0; i < num.size(); i++) {
		NMessage::print() << NString().arg("%02x = %i", num[i], num[i]);
	}
	
	// ... but not how they are converted
	val = num.toInt16();
	NMessage::print() << NString().arg("%02x = %i", val, val);

	return 0;
}
