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
#ifndef NSIGNAL1_HPP
#define NSIGNAL1_HPP

/**
\file nsignal1.hpp Class definition for NSignal1
*/

/**
\class NSignal1
\brief NSignal1 class is used to create the concept of signals raised by classes
\see See the files in examples/raven for examples
*/
template <typename Param1>
class NSignal1: public NEvent1<Param1> {
	typedef NMap<int, NSlotBase1<Param1> *> SlotHandlersMap;
	
	public:
		/** 
		\brief Constructs a NSignal1 object
		*/
		NSignal1();
		
		/**
		\brief Destroys a NSignal1 object
		*/
		~NSignal1();

		/**
		\brief Connects slot to the object (signal)
		\return True in case of success false otherwise
		*/
		bool connect(NSlotBase1<Param1>* slot);

		/**
		\brief Emits a signal
		*/
		bool emit_sig(Param1 param) const;

	private:
		SlotHandlersMap m_slots;
};


template <typename Param1>
NSignal1<Param1>::NSignal1(void)
	: m_slots()
{
}


// disconnect all connected slots
template <typename Param1>
NSignal1<Param1>::~NSignal1(void) {
	for(typename SlotHandlersMap::iterator it = m_slots.begin(); 
		   it != m_slots.end(); 
		   it++)
	{
		if(isAttached(it.key())) {
			it.value()->disconnect();
		}
	}
}

// connect slot to the signal
template <typename Param1>
bool NSignal1<Param1>::connect(NSlotBase1<Param1>* slot) {
	int handle = -1;
	
	if (!slot) { 
		return false;
	}
	
	handle = slot->connect(this);
	m_slots.insert(handle, slot);
	
	return true;
}

	
template <typename Param1>
bool NSignal1<Param1>::emit_sig(Param1 param) const {
	notify(param);
	return true;
}

#endif // NSIGNAL1_HPP
