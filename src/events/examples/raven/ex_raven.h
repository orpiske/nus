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
#ifndef EX_RAVEN_H
#define EX_RAVEN_H

#include "nsignal.h"

/**
\brief Sample object that shows how the event based system used by nus works
*/
class Raven {
	public:
		NSignal1<bool> flySignal;
		NSignal1<int> riseSignal;
		
		Raven(void);
		~Raven(void);
		
		void fly(void);
		void land(void);
		
		void rise(int alt);
};

#endif // EX_RAVEN_H
