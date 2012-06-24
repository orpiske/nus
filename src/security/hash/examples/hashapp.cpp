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
#include "hashapp.h"

HashApp::HashApp(void)
	: m_hash_obj(NULL),
	m_hash_type(HashApp::MD5),
	m_action(HashApp::CALCULATE),
	m_object(HashApp::FILE_OBJ),
	m_object_name(),
	m_object_hash()
{

}


HashApp::~HashApp(void) {
	delete m_hash_obj;
}


bool HashApp::setHash(const NOpt<HashApp> &opt) {
	NString name;
	
	// Gets the hash type informed in the command line
	name = opt.getValues().at(0);
	if (name == "md2") {
		m_hash_type = HashApp::MD2;
		m_hash_obj = new NMd2Hash;
		return true;
	}
	
	if (name == "md4") {
		m_hash_type = HashApp::MD4;
		m_hash_obj = new NMd4Hash;
		return true;
	}
	
	if (name == "md5") {
		m_hash_type = HashApp::MD5;
		m_hash_obj = new NMd5Hash;
		return true;
	}
	
	if (name == "sha") {
		m_hash_type = HashApp::SHA;
		m_hash_obj = new NShaHash;
		return true;
	}
	
	if (name == "sha1") {
		m_hash_type = HashApp::SHA1;
		m_hash_obj = new NSha1Hash;
		return true;
	}
	
	NWarning::print() << name << " is not a valid hash name.";
	NMessage::print() << "Acceptable names: md2, md4, md5, sha, sha1, rmd160";
	return false;
}


bool HashApp::compare(const NOpt<HashApp> &opt) {
	m_action = HashApp::COMPARE;
	
	m_object_hash = opt.getValues().at(0);
	
	return true;
}


bool HashApp::calculate(const NOpt<HashApp> &) {
	m_action = HashApp::CALCULATE;
	
	return true;
}


bool HashApp::setFileObj(const NOpt<HashApp> &opt) {
	m_object = HashApp::FILE_OBJ;
	m_object_name = opt.getValues().at(0);
	
	return true;
}


bool HashApp::setStringObj(const NOpt<HashApp> &opt) {
	m_object = HashApp::STRING_OBJ;
	m_object_name = opt.getValues().at(0);
	
	return true;
}


void HashApp::execCalculate(void) {
	if (m_object == HashApp::FILE_OBJ) {
		// Calculates the hash for a file
		NMessage::print() << "Hash is " 
			<< m_hash_obj->calculateFile(m_object_name).getValue();
	}
	else {
		// Calculates the hash for a string
		NMessage::print() << "Hash is " 
			<<	m_hash_obj->calculate(m_object_name).getValue();
	}
}


// Compares the hash
void HashApp::execCompare(void) {
	if (m_object == HashApp::FILE_OBJ) {
		NMessage::print() << "Not implemented";
	}
	else {
		if (m_hash_obj->match(m_object_name, m_object_hash)) {
			NMessage::print() << "Matches!";
		}
		else {
			NMessage::print() << "Do not match";
		}
	}

}


void HashApp::run(void) {
	if (!m_hash_obj) {
		NWarning::print() << "You must provide a hash type";
		return;
	}
	
	if (m_object_name == "") {
		NWarning::print() << "You must provide an object name";
		return;
	}
	
	if (m_action == HashApp::COMPARE) {
		execCompare();
	}
	else {
		execCalculate();
	}
}
