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
#include "nfilecreator.h"

void create_if_not_exists(const NString &name, const NString &license, 
	bool force) 
{
	NFile outf; 
	NDataStream content;

	if (NFile::exists(name) && !force) { 
		NMessage::print() << "File " << name << " already exists.";

		return;
	}

	outf.setFileName(name);
	outf.open(NIODevice::Truncate);

	if (license != "") {
		content = content + license + "\n";
	}
	
	content = content + "// Source code file created by nproj " 
		+ N_TOOLS_VERSION + " with NUS version " 
		+ N_VERSION  + "\n";
	
	outf.write(content);
	outf.closeDevice();
}
