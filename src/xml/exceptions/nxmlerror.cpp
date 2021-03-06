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
#include "nxmlerror.h"

/**
\file nxmlerror.cpp NXmlError class implementation
*/

NXmlError::NXmlError(void) { }


NXmlException NXmlError::getLastError(const NString &msg, Flag flag) { 
	NXmlException ret;
	NString description = msg;
	xmlErrorPtr err;
	
	err = xmlGetLastError();
	ret.setModule(NException::XML);
	if (!err) { 
		ret.setDescription(description);
		return ret;
	}
	
	description += ": ";
	description += err->message;
	if (err->file) { 
		description += NSTR("on file ") + err->file + NSTR(" ");
	}
	
	if (err->line > 0) { 
		description += NSTR("at line ") + NString::number(err->line);
	}
	
	ret.setDescription(description);
	ret.setFlag(flag);
	return ret;
}
