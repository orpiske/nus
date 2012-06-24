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
#include "nhostopts.h"

NHostOpts::NHostOpts(void)
	: m_addr(),
	m_aliases(false),
	m_addresses(false)
{ 

}


// Sets the address to be resolved
bool NHostOpts::resolve(const NOpt<NHostOpts> &opt) { 
	m_addr = opt.getValues().at(0);
	
	return true;
}

// Sets the flag to show the alias of the host
bool NHostOpts::aliases(const NOpt<NHostOpts> &opt) { 
	m_aliases = true;
	
	return true;
}

// Sets the flag to show the alternative addresses to the host
bool NHostOpts::addresses(const NOpt<NHostOpts> &opt) { 
	m_addresses = true;
	
	return true;
}

// Run the application according to the flags set up
void NHostOpts::run(void) { 
	// Resolve the address of the host
	m_addr.resolve();

	// Shows aliases if requested
	if (!m_aliases) {
		NMessage::print() << "Host " << m_addr.address() << " is "
			<< m_addr.toString();
	}
	else { 
		NList<NString> tmp;
		
		tmp = m_addr.aliases();
		
		for (NList<NString>::const_iterator i = tmp.constBegin();
			i != tmp.constEnd();
			i++)
		{
			NMessage::print() << "Host " << m_addr.address() << " is " << *i;
		}
	}
	
	
	// Show addresses if requested
	if (m_addresses) { 
		NList<nuint32> tmp;
		
		tmp = m_addr.addresses();
		
		for (NList<nuint32>::const_iterator i = tmp.constBegin();
			i != tmp.constEnd();
			i++)
		{
			NMessage::print() << "Host " << m_addr.address() << " is also " 
				<< NHostAddress::toString(*i);
		}
	}
}

