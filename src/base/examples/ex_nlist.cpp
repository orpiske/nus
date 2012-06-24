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
#include "nlist.h"
#include "noutput.h"

// shows the content of the list using const iterators
void show_iterator_const(NList<nuint64> &list) {
	NList<nuint64>::iterator i = list.begin();
	
	NMessage::print() << "Showing " << list.size() << " items (const_iterator)";
	
	i = list.begin();
	while (i != list.end()) { 
		NMessage::print() << *i << ":";
		i++;
	}
}


// shows the content of the list using iterators
void show_iterator(NList<nuint64> &list) {
	NMessage::print() << "Showing " << list.size() << " items (iterator)";
	
	for (NList<nuint64>::iterator i = list.begin(); i != list.end(); i++) {
		NMessage::print() << *i << ":";
	}
	
}


// Shows the list using acessor methods
void show(NList<nuint64> &list) {
	NMessage::print() << "Showing " << list.size() << " items";
	
	for (nuint64 i = 0; i < list.size(); i++) {
		NMessage::print() << list.at(i) << ":";
	}
}

int main(void) {
	NList<nuint64> list;

	// Tries to show the list
	show(list);

	// Feed the list with some data:
	NMessage::print() << "Feeding with data";
	for (nuint64 i = 0; i < 10; i++) {
		list.append(i);
	}

	// Shows it again
	show(list);

	// Remove some data of the list:
	NMessage::print() << "Removing data";
	for (nuint64 i = (list.size() - 1); i > 0; i--) {
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
	
}
