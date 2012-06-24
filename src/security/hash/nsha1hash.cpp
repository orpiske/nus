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
#include "nsha1hash.h"

/**
\file nsha1hash.cpp NSha1Hash class implementation
*/

NSha1Hash::NSha1Hash(void) {
	setHashBufferSize(48);
	init("sha1");
}


NSha1Hash::~NSha1Hash(void) {
	
}


NHash NSha1Hash::calculate(const NString &str) {
	NString value;
	
	update(str.toChar(), str.length());
	value = cleanup();
	
	return NHash("sha1", value);
}


NHash NSha1Hash::calculate(const NDataStream &data, nint32 size) {
	NString value;
	update(data.data(), size);
	
	value = cleanup();
	
	return NHash("sha1", value);
}


NHash NSha1Hash::calculateFile(const NString &filename) {
	NFile file(filename, NIODevice::ReadOnly);
	
	return calculateFile(&file);
	
}


NHash NSha1Hash::calculateFile(NFile *file) {
	NDataStream buffer;
	
	while (!file->atEnd()) {
		file->read(&buffer, 48);
		update(buffer.data(), buffer.size());
	
	}
	
	return NHash("sha1", cleanup());
}
