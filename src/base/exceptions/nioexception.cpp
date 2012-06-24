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
#include "nioexception.h"

/**
\file nioexception.cpp NIOException class implementation
*/

NIOException::NIOException(const NString &desc, const NString &name, Module module,
	Resource resource, Flag flag)
	: NException(desc, module, flag),
	m_resource(UNKNOWN),
	m_name(name)
{

}


NIOException::Resource NIOException::getResource(void) const {
	return m_resource;
}


NString NIOException::getResourceName(void) const {
	return m_name;
}

Flag NIOException::getFlagByErr(nuint32 errno_val) {
	Flag ret = 0;
	
	switch (errno_val) {
		case EPERM:
		case EACCES: {
			ret = IO_ACCESS_DENIED;
			break;
		}
		case ENOSPC: {
			ret = IO_NO_SPACE;
			break;
		}
		case EIO: {
			ret = IO_IO_ERROR;
			break;
		}
		case ENXIO: {
			ret = IO_NOT_FOUND;
			break;
		}
		default: {
			ret = IO_SYSTEM;
			break;
		}
	}
	
	return ret;
}
