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

// Navigates through the skiplist using the iterators
void show_iterator(NSkipList<NString> &slist) {
	for (NSkipList<NString>::iterator i = slist.begin(); i != slist.end(); ++i) {
		NMessage::print() << "[ " << *i << "]:";
	}
}

// Displays a given time
void showTime(time_t start, time_t end, int size) {
	time_t length;

	length = end - start;
	NMessage::print() << size << " items added in " << static_cast<nuint64>(length) << " seconds. ";
	
	if (length > 0) {
		NMessage::print() << "With an average of " << static_cast<double>(size/length) 
				<< " items p/ sec.";
	}
	
}

// Add items to the skip list measuring the time to complete the operation
void addSkipList(NSkipList<NString> &slist, int size, int *data) {
	NString tmp;
	time_t start;
	time_t end;
	
	start = time(NULL);
	for (int i = 0; i < size; i++) {
		tmp = tmp.number(*data);
		slist.insert(tmp);
		data++;
	}
	end = time(NULL);
	showTime(start, end, size);
}


int main(void) {
	NSkipList<NString> slist(16);
	
	int size = 10;
	int *data = new int[size];
	
	// First, generates some random data
	NMessage::print() << "Loading random data ... ";
	
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		*data = rand();
		NMessage::print() << *data << " : ";
		data++;
	}
	
	
	// Rewind data pointer
	for (int i = size; i != 0; i--, data--) {}
	
	// Add data to the skip list
	NMessage::print() << "Adding " << size << " items to a SkipList";
	addSkipList(slist, size, data);
	show_iterator(slist);
	delete[] data;
} 
