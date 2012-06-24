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
#include "ndir.h"

/**
\file ndir.cpp NDir class implementation
\example ex_ndir.cpp
*/

NDir::NDir(const NString &name)
	: NObject(),
	m_contents(), 
	m_dir_name(name),
	m_dir_handle(0)
{

}

void NDir::init(const NString &name) {
#if defined(__WIN32) || defined (_MSC_VER)
	WIN32_FIND_DATA file_data;

	m_dir_handle = FindFirstFile(m_dir_name.toChar(), &file_data);
	if (m_dir_handle == INVALID_HANDLE_VALUE) {
		// No files were found
		return;
	}

	loadContents(&file_data);

#else 
	struct dirent *ent;

	m_dir_handle = opendir(m_dir_name.toChar());
	if (!m_dir_handle) {
		throw NIOException(nerror(errno), m_dir_name, 
				 NException::BASEIO,
				 NIOException::FILE,
				 errno);  
	}

	ent = readdir(m_dir_handle);
	if (!ent) {
		if (errno != 0) {
			throw NIOException(nerror(errno), m_dir_name, 
				 NException::BASEIO,
				 NIOException::FILE,
				 errno);  
		}
	}
	
	loadContents(ent);

#endif // defined(__WIN32) || defined (_MSC_VER)
}

NDir::~NDir(void) { 
#if defined(__WIN32) || defined (_MSC_VER)
	FindClose(m_dir_handle);
#else
	closedir(m_dir_handle);
#endif // defined(__WIN32) || defined (_MSC_VER)
}



#if defined(__WIN32) || defined (_MSC_VER)

void NDir::loadContents(WIN32_FIND_DATA *file_data) {
	while (true) { 
		m_contents.append(file_data->cFileName);
		if (!FindNextFile(m_dir_handle, file_data)) {
			if (GetLastError() != ERROR_NO_MORE_FILES) { 
				break;
			}
			else {
				NString msg = "Unhandled exception. OS error code: ";

				msg += GetLastError();
				throw NIOException(msg, m_dir_name, NException::BASEIO,
					NIOException::FILE,	0); 
			}
		}
	}	
}

#else 

void NDir::loadContents(struct dirent *ent) {
	NString tmp_name;

	while (ent) {
		NDebug::print() << "Entry name = " << ent->d_name;
		
		tmp_name = ent->d_name;
		m_contents.append(tmp_name);
		
#if !defined(__APPLE__)		
		seekdir(m_dir_handle, ent->d_off);
#endif // !defined(__APPLE__)

		ent = readdir(m_dir_handle);
		if (!ent) {
			if (errno != 0) {
				throw NIOException(nerror(errno), m_dir_name, 
					NException::BASEIO,
					NIOException::FILE,
					errno);  
			}
		}
	}

	NDebug::print() << "Added " << m_contents.size() << " entries";
}
#endif // defined(__WIN32) || defined (_MSC_VER)

NList<NString> NDir::getContents(void) const {
	return m_contents;
}


NString NDir::getName(void) const {
	return m_dir_name;
}
