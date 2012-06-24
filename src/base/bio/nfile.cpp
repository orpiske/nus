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
#include "nfile.h"

/**
\file nfile.cpp NFile class implementation
*/

NFile::NFile(void)
	: NIODevice(),
	m_handle(NULL),
	m_path()
{

}

NFile::NFile(const NString &path, NIODevice::Mode mode)
	: NIODevice(),
	m_handle(NULL),
	m_path()
{ 
	setFileName(path);
	open(mode);	
}


NFile::~NFile(void) { 
	closeDevice();
}


bool NFile::atEnd(void) const { 
	if (feof(m_handle)) { 
		return true;
	}
	
	return false;	
}


bool NFile::exists(void) const { 
	struct stat sb;
	
	if (stat(m_path.toChar(), &sb) == -1) {
		if (errno == ENOENT) {
			return false;
		}
		throw NIOException(nerror(errno), m_path, 
				 NException::BASEIO,
				 NIOException::FILE,
				 errno);  
	}
	
	return true;
}


bool NFile::exists(const NString &filepath) { 
	struct stat sb;
	
	if (stat(filepath.toChar(), &sb) == -1) {
		if (errno == ENOENT) {
			return false;
		}
		throw NIOException(nerror(errno), filepath, 
				 NException::BASEIO,
				 NIOException::FILE,
				 errno);  
	}
	
	return true;
}


int NFile::handle(void) const { 
#ifndef _MSC_VER
	return fileno(m_handle);
#else
	return _fileno(m_handle);
#endif
}

char *NFile::getMode(NIODevice::Mode mode) const {
	if ((mode & NIODevice::ReadWrite) && !(mode & NIODevice::Truncate)
	   || (mode & NIODevice::Append))
	{ 
		return "a+";
	}
	
	if ((mode & NIODevice::ReadWrite) && !(mode & NIODevice::Append)
	   || (mode & NIODevice::Truncate)) { 
		return "w+";
	}
	
	return "r";
}


void NFile::open(NIODevice::Mode mode) { 
	if (mode & NIODevice::ReadOnly) { 
		if (!exists()) { 
			throw NIOException("Not found", m_path, NException::BASEIO,
					NIOException::FILE, 
					errno);
		}
	}
	
	m_handle = fopen(m_path.toChar(), getMode(mode));
	if (!m_handle) {
		throw NIOException(nerror(errno), m_path,
				NException::BASEIO, 
				NIOException::FILE, 
				NIOException::getFlagByErr(errno));
	}
}


void NFile::closeDevice(void) { 
	if (m_handle) { 
		fclose(m_handle);
		m_handle = NULL;
	}

}


nint32 NFile::read(NDataStream *buffer) {
#ifndef _MSC_VER 
	char tmp[m_readBufferSize];
#else
	char tmp[2048];
#endif
	int bread = 0;
	
	memset(tmp, 0, sizeof(tmp));
	
	bread = fread(tmp, sizeof(tmp), 1, m_handle);
	if (bread == 0) {
		if (ferror(m_handle)) { 
			return -1;
		}
	}
	
	buffer->set(tmp, bread);
	return bread;	
}


nint32 NFile::read(NDataStream *buffer, nuint32 bytes) { 
	char tmp[1];
	int bread = 0;
	nuint32 btotal = 0;
	
	*buffer = "";
	do { 
		memset(tmp, 0, sizeof(tmp));
		
		bread = fread(tmp, sizeof(tmp), 1, m_handle);
		if (bread > 0) { 
			btotal += bread;
			buffer->append(tmp, bread);
		}
		else {
			if (ferror(m_handle)) {
				return -1;
			}
		}
	} while (!feof(m_handle) && btotal != bytes);

	return btotal;	
}


nint32 NFile::readLine(NDataStream *buffer) { 
	char tmp[1];
	int bread = 0;
	nuint32 btotal = 0;
	
	*buffer = "";
	do { 
		memset(tmp, 0, sizeof(tmp));
		
		bread = fread(tmp, sizeof(tmp), 1, m_handle);
		if (bread > 0) { 
			if (tmp[0] == '\n' || tmp[0] == '\0' || tmp[0] == '\r') { 
				break;
			}
			
			btotal += bread;
			buffer->append(tmp, bread);
		}
		else {
			break;
		}
	} while (!feof(m_handle));
	return btotal;	
}


nint32 NFile::write(const NDataStream &data, nuint32 bytes) { 
	int btotal = 0; 
	
	if (bytes != 0 && (data.size() >= bytes)) { 
		btotal = fwrite(data.data(), bytes, 1, m_handle);
		if (btotal == 0) { 
			return -1;
		}
	}
	else { 
		btotal = fwrite(data.data(), data.size(), 1, m_handle);
	}
	
	return btotal;	
}


nint64 NFile::size(void) const { 
	struct stat fdata;
	
	if (fstat(handle(), &fdata) < 0) {	  
		throw NIOException(nerror(errno), m_path, 
				 NException::BASEIO,
				 NIOException::FILE,
				 errno);
	}
	
	return fdata.st_size;
}


void NFile::setFileName(const NString &path) { 
	if (!m_path.isNull()) { 
		closeDevice();
	}
	
	m_path = path;
}


NString NFile::getFileName(void) const { 
	return m_path;
}

