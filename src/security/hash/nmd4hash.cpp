// LICENSE: (Please see the file COPYING for details)
//
// NUS - Nemesis Utilities System: A C++ application development framework 
// Copyright (C) 2006, 2008 Otavio Rodolfo Piske
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
#include "nmd4hash.h"

/**
\file nmd4hash.cpp NMd4Hash class implementation
*/

NMd4Hash::NMd4Hash(void) {
	setHashBufferSize(48);
	init("md4");
}


NMd4Hash::~NMd4Hash(void) {
	
}


NHash NMd4Hash::calculate(const NString &str) {
	NString value;
	
	update(str.toChar(), str.length());
	value = cleanup();
	
	return NHash("md4", value);
}


NHash NMd4Hash::calculate(const NDataStream &data, nint32 size) {
	NString value;
	update(data.data(), size);
	
	value = cleanup();
	
	return NHash("md4", value);
}


NHash NMd4Hash::calculateFile(const NString &filename) {
	NFile file(filename, NIODevice::ReadOnly);
	
	return calculateFile(&file);
	
}


NHash NMd4Hash::calculateFile(NFile *file) {
	NDataStream buffer;
	
	while (!file->atEnd()) {
		file->read(&buffer, 48);
		update(buffer.data(), buffer.size());
	
	}
	
	return NHash("md4", cleanup());
}
