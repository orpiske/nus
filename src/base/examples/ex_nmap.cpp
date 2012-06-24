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
#include "nmap.h"
#include "nstring.h"
#include "noutput.h"

void sites(void) {
	NMap<NString, NString> map;
	NList<NString> keys;
	
	// Inserts some data into the map
	map.insert("slashdot", "www.slashdot.org");
	map.insert("osnews", "www.osnews.com");
	map.insert("brlinux", "www.br-linux.org");
	map.insert("brlinux", "http://br-linux.org");
	map.insert("thedailywtf", "www.thedailywtf.com");
	map.insert("userfriendly", "www.userfriendly.org");
	
	// Navigates through the map, using its iterator. Also, shows the methods
	// key() and value() of the iterator, which return the key and the value of
	// the current iterator
	for (NMap<NString, NString>::iterator i = map.begin(); i != map.end(); ++i) {
		NMessage::print() << "Title: " << i.key() << ". URL: " << i.value();
	}
	
	// Obviosly you can search in the map using the key value
	if (map.contains("osnews")) {
		NMessage::print() << "I visit OS News too!";
	}
	else {
		NMessage::print() << "Don't you visit OS News?";
	}
	
	// You can address values using the keys. Note, however, that if you 
	// address an incorrect value you will receive a default constructed 
	// value ...
	NMessage::print() << "URL: " << map["thedailywtf"];
	
	// Find, on the otherside, will return map.end(), if you do address
	// an incorrect index.
	if (map.find("lala") == map.end()) {
		NMessage::print() << "Site lala not found";
	}
	
	// You may "download" all the keys values from the map using keys()
	// keys() will return a NList<K> and ...
	keys = map.keys();
	
	// ... then you can use everything provided by NList, to navigate :D
	for (NList<NString>::iterator i = keys.begin(); i != keys.end(); i++) {
		NMessage::print() << "Site: " << *i;
	}
	
	// You may, also, request only a particular key value:
	keys = map.keys("www.br-linux.org");
	for (NList<NString>::iterator i = keys.begin(); i != keys.end(); i++) {
		NMessage::print() << "Site (2): " << *i;
	}
}


// Let's learn some portuguese!
void portuguese(void) {
	NMap<int, NString> map;
	int r = 0;
	
	// Inserts some data on the Map
	map.insert(0, "zero");
	map.insert(1, "um");
	map.insert(2, "dois");
	map.insert(3, "treis");
	map.insert(4, "quatro");
	map.insert(5, "cinco");
	map.insert(6, "seis");
	map.insert(7, "sete");
	map.insert(8, "oito");
	map.insert(9, "nove");
	map.insert(10, "dez");
	
	// Choose some values to display
	NMessage::print() << "You just learned " << map.size() << " words in portuguese!";
	for (NMap<int, NString>::iterator i = map.begin(); i != map.end(); i++, r++) {
		if ((r % 2) == 0) {
			NMessage::print() << map.value(r); 
		} 
	}
	
	// Find will return an iterator. You can use value() to obtain it's value
	// and key() to obtain its key
	NMessage::print() << "Key: " << map.find(5).key() << " = " 
		<< map.find(5).value();
}

int main(void) {
	sites();
	portuguese();
}

