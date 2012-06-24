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
#include "nstring.h"
#include "noutput.h"

int main(void) {
	NString mystring;
	NString string2;
	
	NMessage::print() << "Starting!";

	mystring = "This is a test";

	NMessage::print() << mystring;
	if (mystring.isNull()) {
		NWarning::print() << "I am null";
	}
	else {
		NMessage::print() << "I am not null";
	}

	mystring += ". Ok, trying to append something";

	NMessage::print() << mystring;
	NMessage::print() << "Now I have " << mystring.length();
	NMessage::print() << "Inserting 'NUS' to position 2 " << mystring.insert(2, "NUS");
	string2 = "ABCD";
	mystring = "ABCD";
	
	if (mystring.compare(0, string2)) {
		NMessage::print() << "They are equal!\nChanging the string";
		
		string2 = "BCDE";
		if (!mystring.compare(0, string2)) {
				NMessage::print() << "They are not equal anymore!!";
		}
	}
	
	NMessage::print() << "Substr(0, 2) of " << mystring << " = " << mystring.substr(0, 2);
	NMessage::print() << "Substr(1, 2) of " << mystring << " = " << mystring.substr(1, 2);
	string2 = string2 + "123" + "AC/DC" + "2";
	NMessage::print() << string2;
	string2 = string2 + "\t" + LIGHT_GREEN + "abcdefgdhijklmnopqrstuvxwz";
	string2 = string2 + RESET;
	NMessage::print() << string2;
	
	NMessage::print() << "You can also put numbers on me: " << NString::number(1023);
	
	mystring.arg("Hi %s, you have %f money on your pocket and you are %x years old",
			 "otavio", 10.334, 25);
	
	NMessage::print() << mystring;

	NMessage::print() << "string 'otavio' found in position: " << 
		mystring.find("otavio");

	/* 
	NMessage::print() << mystring.replace("otavio", "user");

	NMessage::print() << mystring.replace("you", "you", 4);
	*/

	mystring = "Hey ho, let's go! Hey ho, let's go! Hey ho, let's go!";
	NMessage::print() << "Before replace_first(): " << mystring;
	mystring.replace_first("Hey", "Youpi");
	NMessage::print() << "After replace_first(): " << mystring;

	// Also note how replace is case sensitive
	mystring = "Hey ho, let's go! Hey ho, let's go! hey ho, let's go!";
	NMessage::print() << "Before replace(): " << mystring;
	mystring.replace("Hey", "Youpi");
	NMessage::print() << "After replace(): " << mystring;

	// Also note how replace is case sensitive
	mystring = "Hey ho, let's go! Hey ho, let's go! hey ho, let's go!";
	NMessage::print() << "Before replace(2): " << mystring;
	mystring.replace("ho", "joe", 2);
	NMessage::print() << "After replace(2): " << mystring;

	NString trimExample = "       I have spaces         ";

	NMessage::print() << "Before = " << trimExample << ". L = " << trimExample.length();

	NMessage::print() << "Rtrim = " << trimExample.rtrim() << ". L = " << trimExample.rtrim().length();
	NMessage::print() << "Ltrim = " << trimExample.ltrim() << ". L = " << trimExample.ltrim().length();
	NMessage::print() << "Trim = " << trimExample.trim() << ". L = " << trimExample.trim().length();

	return 0;
}
