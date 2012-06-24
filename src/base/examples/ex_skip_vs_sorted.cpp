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
#include "nskiplist.h"
#include "nsortedlist.h"
#include "nstring.h"
#include "noutput.h"

#include <ctime>

void showTime(time_t start, time_t end, int size) {
	time_t length;

	length = end - start;
	NMessage::print() << size << " items added in " << 
			static_cast<nuint32>(length) << " seconds. ";
	
	if (length > 0) {
		NMessage::print() << "With an average of " << 
				static_cast<double>(size / length) << " items p/ sec.";
	}
	
}


void addList(int size, int *data) {
	NString tmp;	
	NSortedList<NString> list;
	time_t start;
	time_t end;
	
	// Starts the counter and inserts some items
	start = time(NULL);
	for (int i = 0; i < size; i++) {
		tmp = tmp.number(i);
		list.insert(tmp);
		data++;
	}
	end = time(NULL);
	
	// Show elapsed time
	showTime(start, end, size);
}

void addSkipList(int size, int *data) {
	NString tmp;
	time_t start;
	time_t end;
	
	// Creates a skiplist with max height = 16
	NSkipList<NString> slist(16);
	
	// Starts the counter and inserts some items
	start = time(NULL);
	for (int i = 0; i < size; i++) {
		tmp = tmp.number(*data);
		slist.insert(tmp);
		data++;
	}
	end = time(NULL);
	
	// Show elapsed time
	showTime(start, end, size);
}

int main(void) {
	int size = 2501;
	int *data = new int[size];
	
	// Generates some random data
	for (int i = 0; i < size; i++) {
		*data = rand();
		data++;
	}
	
	// Rewind (this is lame ... )
 	for (int i = size; i != 0; i--, data--) {}
	
	// Add to the skip list
	NMessage::print() << "Adding " << size << " items to a SkipList";
	addSkipList(size, data);
	
	
	NMessage::print() << "Adding " << size << " items to a List";
	addList(size, data);
	NMessage::print() << "Done.";
} 
