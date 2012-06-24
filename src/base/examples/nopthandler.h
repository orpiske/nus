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
#ifndef NOPTHANDLER_H
#define NOPTHANDLER_H

#include "ndefs.h"
#include "nopt.h"
#include "noutput.h"
#include "nlist.h"
#include "nstring.h"

#include <cstdlib>

class NOptHandler: public NObject {
	public:
		struct Country { 
			NString name;
			NString continent;
			NString language;
			
			Country(): name(), continent(), language() {};
			Country(const NString n, const NString c, const NString l)
				: name(n), continent(c), language(l)
			{ 
			
			}
		};
		
		NOptHandler(void);
		~NOptHandler(void);
		
		bool south_america(const NOpt<NOptHandler> &val);
		bool central_america(const NOpt<NOptHandler> &val);
		bool north_america(const NOpt<NOptHandler> &val);
		
		bool language(const NOpt<NOptHandler> &val);
		bool max(const NOpt<NOptHandler> &val);
		
		void foo(void);
	
	private:
		bool m_south;
		bool m_central;
		bool m_north;
		NList<NString> m_languages;
		nint32 m_max;
		NList<Country> m_countries;
		
		void showContinent(const NString &continent);
		bool showCountry(const Country &country, const NString &continent);
};


#endif // NOPTHANDLER_H
