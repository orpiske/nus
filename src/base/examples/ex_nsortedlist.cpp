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
#include "nsortedlist.h"
#include "noutput.h"

#include <cstdlib>

// shows the content of the list using const iterators
void show_iterator_const(const NList<int> &list) {
	NMessage::print() << "Showing " << list.size() << " items (iterator)";
	for (NList<int>::const_iterator i = list.constBegin(); i != list.constEnd(); i++) {
		NMessage::print() << *i << ":";
	}
}


// shows the content of the list using iterators
void show_iterator(NList<int> &list) {
	NMessage::print() << "Showing " << list.size() << " items (iterator)";
	for (NList<int>::iterator i = list.begin(); i != list.end(); i++) {
		NMessage::print() << *i << ":";
	}
}


// Shows the list using acessor methods
void show(NSortedList<int> &list) {
	NMessage::print() << "Showing " << list.size() << " items";
	for (nuint32 i = 0; i < list.size(); i++) {
		NMessage::print() << list.at(i) << ":";
	}
}

int main(void) {
	NSortedList<int> list;
	int val = 0; 

	// Tries to show the list
	show(list);
	
	// Feeds the list with some random data
	NMessage::print() << "Feeding with random data";
	for (int i = 0; i < 32; i++) {
		val = rand();
		NMessage::print() << "Inserting: " << val;
		list.insert(val);
	}
	show(list);
	
	// Remove some data of the list:
	NMessage::print() << "Removing data";
	for (int i = (list.size() - 1); i > 0; i--) {
		if ((i % 2) == 0) {
			list.removeAt(i);
		}
	}
	show(list);
	
	// Take the first item
	NMessage::print() << "I'll take the first one for me: " << list.takeFirst();
	show_iterator(list);
	
	// Gets a reference to the last one
	NMessage::print() << "I'll show the last one: " << list.last();
	show_iterator_const(list);	
	
	// Unecessary. Memory will be free'd on destructor.	
	list.clear();
	
	return 0;
}
