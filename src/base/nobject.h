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
#ifndef NOBJECT_H
#define NOBJECT_H

/**
\file nobject.h Class definition for the NObject object
*/
#include "ndefs.h"
#include "nstring.h"

#include <cstdio>

/**
\brief NObject is the base object for various N.U.S objects
*/
class DllDeclSpec NObject {
	public:
		/**
		\brief NObject constructor
		*/
		NObject(void);
		/**
		\brief NObject destructor
		*/
		virtual ~NObject(void);
		
	private:

};

#endif
