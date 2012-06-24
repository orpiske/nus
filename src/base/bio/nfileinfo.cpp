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
#include "nfileinfo.h"

/**
\file nfileinfo.cpp NFileInfo class implementation
*/

NFileInfo::NFileInfo(const NString &path)
	: NObject(),
	m_path(path)
{

}

NFileInfo::~NFileInfo(void) {

}

bool NFileInfo::isFile(void) const {
	return NFileInfo::isFile(m_path);
}


bool NFileInfo::isDir(void) const {
	return NFileInfo::isDir(m_path);
}


bool NFileInfo::isDevice(void) const {
	return NFileInfo::isDevice(m_path);
}


bool NFileInfo::isFifo(void) const {
	return NFileInfo::isFifo(m_path);
}


bool NFileInfo::isLink(void) const {
	return NFileInfo::isLink(m_path);
}

bool NFileInfo::exists(void) const {
	return NFileInfo::exists(m_path);
}

bool NFileInfo::ownerRead(void) const {
	return NFileInfo::ownerRead(m_path);
}


bool NFileInfo::groupRead(void) const {
	return NFileInfo::groupRead(m_path);
}


bool NFileInfo::othersRead(void) const {
	return NFileInfo::othersRead(m_path);
}


bool NFileInfo::ownerWrite(void) const {
	return NFileInfo::ownerWrite(m_path);
}


bool NFileInfo::groupWrite(void) const {
	return NFileInfo::groupWrite(m_path);
}


bool NFileInfo::othersWrite(void) const {
	return NFileInfo::othersWrite(m_path);
} 


bool NFileInfo::ownerExecute(void) const {
	return NFileInfo::ownerExecute(m_path);
}


bool NFileInfo::groupExecute(void) const {
	return NFileInfo::groupExecute(m_path);
}


bool NFileInfo::othersExecute(void) const {
	return NFileInfo::othersExecute(m_path);
}

bool NFileInfo::isFile(const NString &path) {
	struct stat sb;
	
	if (stat(path.toChar(), &sb) == -1) {
		throw NIOException(nerror(errno), path, 
				 NException::BASEIO,
				 NIOException::FILE,
				 errno);  
	}
	
	if ((sb.st_mode & S_IFMT) == S_IFREG) { 
		return true;
	}
	
	return false;
}


bool NFileInfo::isDir(const NString &path) {
	struct stat sb;
	
	if (stat(path.toChar(), &sb) == -1) {
		throw NIOException(nerror(errno), path, 
				 NException::BASEIO,
				 NIOException::FILE,
				 errno);  
	}
	
	if ((sb.st_mode & S_IFMT) == S_IFDIR) { 
		return true;
	}
	
	return false;
}


bool NFileInfo::isDevice(const NString &path) {
	struct stat sb;
	
	if (stat(path.toChar(), &sb) == -1) {
		throw NIOException(nerror(errno), path, 
				 NException::BASEIO,
				 NIOException::FILE,
				 errno);  
	}
	
	if ((sb.st_mode & S_IFMT) == S_IFCHR) { 
		return true;
	}
	
	return false;
}


bool NFileInfo::isFifo(const NString &path) {
	struct stat sb;
	
	if (stat(path.toChar(), &sb) == -1) {
		throw NIOException(nerror(errno), path, 
				 NException::BASEIO,
				 NIOException::FILE,
				 errno);  
	}
	
#if !defined(__WIN32) && !defined(_MSC_VER) 
	if ((sb.st_mode & S_IFMT) == S_IFIFO) { 
		return true;
	}
#endif // !defined(__WIN32) && !defined(_MSC_VER) 
	
	return false;
}


bool NFileInfo::isLink(const NString &path) {
	struct stat sb;
	
	if (stat(path.toChar(), &sb) == -1) {
		throw NIOException(nerror(errno), path, 
				 NException::BASEIO,
				 NIOException::FILE,
				 errno);  
	}
#if !defined(__WIN32) && !defined(_MSC_VER) 
	if ((sb.st_mode & S_IFMT) == S_IFLNK) { 
		return true;
	}
#endif // !defined(__WIN32) && !defined(_MSC_VER) 
	
	return false;
}


bool NFileInfo::exists(const NString &path) {
	struct stat sb;
	
	if (stat(path.toChar(), &sb) == -1) {
		if (errno == ENOENT) {
			return false;
		}
		throw NIOException(nerror(errno), path, 
				 NException::BASEIO,
				 NIOException::FILE,
				 errno);  
	}
	
	return true;
}




bool NFileInfo::ownerRead(const NString &path) {
#if !defined(__WIN32) && !defined(_MSC_VER) 
	struct stat sb;
	
	if (stat(path.toChar(), &sb) == -1) {
		throw NIOException(nerror(errno), path, 
				 NException::BASEIO,
				 NIOException::FILE,
				 errno);  
	}
	

	if (sb.st_mode & S_IRUSR) { 
		return true;
	}
	
	return false;
#else 
	return true;
#endif // !defined(__WIN32) && !defined(_MSC_VER) 
}


bool NFileInfo::groupRead(const NString &path) {
#if !defined(__WIN32) && !defined(_MSC_VER) 
	struct stat sb;
	
	if (stat(path.toChar(), &sb) == -1) {
		throw NIOException(nerror(errno), path, 
				 NException::BASEIO,
				 NIOException::FILE,
				 errno);  
	}
	
	if (sb.st_mode & S_IRGRP) { 
		return true;
	}
	
	return false;
#else
	return true;
#endif // !defined(__WIN32) && !defined(_MSC_VER) 
}


bool NFileInfo::othersRead(const NString &path) {
#if !defined(__WIN32) && !defined(_MSC_VER) 
	struct stat sb;
	
	if (stat(path.toChar(), &sb) == -1) {
		throw NIOException(nerror(errno), path, 
				 NException::BASEIO,
				 NIOException::FILE,
				 errno);  
	}
	
	if (sb.st_mode & S_IROTH) { 
		return true;
	}
	
	return false;
#else
	return true;
#endif // !defined(__WIN32) && !defined(_MSC_VER) 
}


bool NFileInfo::ownerWrite(const NString &path) {
#if !defined(__WIN32) && !defined(_MSC_VER) 
	struct stat sb;
	
	if (stat(path.toChar(), &sb) == -1) {
		throw NIOException(nerror(errno), path, 
				 NException::BASEIO,
				 NIOException::FILE,
				 errno);  
	}
	
	if (sb.st_mode & S_IWUSR) { 
		return true;
	}
	
	return false;
#else
	return true;
#endif // !defined(__WIN32) && !defined(_MSC_VER) 
}


bool NFileInfo::groupWrite(const NString &path) {
#if !defined(__WIN32) && !defined(_MSC_VER) 
	struct stat sb;
	
	if (stat(path.toChar(), &sb) == -1) {
		throw NIOException(nerror(errno), path, 
				 NException::BASEIO,
				 NIOException::FILE,
				 errno);  
	}
	
	if (sb.st_mode & S_IWGRP) { 
		return true;
	}
	
	return false;
#else
	return true;
#endif // !defined(__WIN32) && !defined(_MSC_VER) 
}


bool NFileInfo::othersWrite(const NString &path) {
#if !defined(__WIN32) && !defined(_MSC_VER) 
	struct stat sb;
	
	if (stat(path.toChar(), &sb) == -1) {
		throw NIOException(nerror(errno), path, 
				 NException::BASEIO,
				 NIOException::FILE,
				 errno);  
	}
	
	if (sb.st_mode & S_IWOTH) { 
		return true;
	}
	
	return false;
#else
	return true;
#endif // !defined(__WIN32) && !defined(_MSC_VER) 
}


bool NFileInfo::ownerExecute(const NString &path) {
#if !defined(__WIN32) && !defined(_MSC_VER) 
	struct stat sb;
	
	if (stat(path.toChar(), &sb) == -1) {
		throw NIOException(nerror(errno), path, 
				 NException::BASEIO,
				 NIOException::FILE,
				 errno);  
	}
	
	if ((sb.st_mode & S_IRWXU) == S_IXUSR) { 
		return true;
	}
	
	return false;
#else
	return true;
#endif // !defined(__WIN32) && !defined(_MSC_VER) 
}


bool NFileInfo::groupExecute(const NString &path) {
#if !defined(__WIN32) && !defined(_MSC_VER) 
	struct stat sb;
	
	if (stat(path.toChar(), &sb) == -1) {
		throw NIOException(nerror(errno), path, 
				 NException::BASEIO,
				 NIOException::FILE,
				 errno);  
	}
	
	if (sb.st_mode & S_IXGRP) { 
		return true;
	}
	
	return false;
#else
	return true;
#endif // !defined(__WIN32) && !defined(_MSC_VER) 
}


bool NFileInfo::othersExecute(const NString &path) {
#if !defined(__WIN32) && !defined(_MSC_VER) 
	struct stat sb;
	
	if (stat(path.toChar(), &sb) == -1) {
		throw NIOException(nerror(errno), path, 
				 NException::BASEIO,
				 NIOException::FILE,
				 errno);  
	}
	
	if (sb.st_mode & S_IXOTH) { 
		return true;
	}
	
	return false;
#else
	return true;
#endif // !defined(__WIN32) && !defined(_MSC_VER) 
}

