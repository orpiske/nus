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
#ifndef NSLOT1_HPP
#define NSLOT1_HPP

/**
\file nslot1.hpp Template class file for event definition
*/


/**
\class NSlotBase1 
\brief NSlotBase1 is the base class for slot definition
\see See the files in examples/raven for examples
*/
template <typename ParamT>
class NSlotBase1 {
	public:
		/**
		\brief Destroys a NSlotBase1 object
		*/
		virtual ~NSlotBase1(void) {};
		
		/**
		\brief Connects a event to the slot
		\param event Event/Signal to connect this slot to
		\return Handler id.
		*/
		virtual int connect(NEvent1<ParamT>* event) = 0;
		
		/**
		\brief Disconnects the slot from the event/signal
		*/
		virtual void disconnect() = 0;
};


/**
\class NSlot1 
\brief NSlot1 is the template class for slot implementation
\see See the files in examples/raven for examples
*/
template <typename ListenerT, typename ParamT>
class NSlot1: public NSlotBase1<ParamT> {
	public:
	
		typedef void (ListenerT::*PtrMember)(ParamT);  /*!< Listener type definition */

		/**
		\brief Constructs a NSlot1 object 
		\param object The object for which a event will be attached to
		\param member Method to be executed on reaction to a given signal/event
		*/
		NSlot1(ListenerT* object, PtrMember member);
		
		/**
		\brief Destroys a NSlot1 object
		*/
		~NSlot1();
	
		
		/**
		\brief Connects a event to the slot
		\param event Event/Signal to connect this slot to
		\return Handler id.
		*/
		int connect(NEvent1<ParamT>* event);
		
		/**
		\brief Disconnects the slot from the event/signal
		*/
		void disconnect();

	private:
		ListenerT* m_object;
		PtrMember m_member;

		NEventId m_handle;
		NEvent1<ParamT>* m_cpp_event;
	
		NSlot1(const NSlot1<ListenerT, ParamT> &other);
		NSlot1<ListenerT, ParamT> 
				operator=(const NSlot1<ListenerT, ParamT> &other);
};


template <typename ListenerT, typename ParamT>
NSlot1<ListenerT, ParamT>::NSlot1(ListenerT* object, PtrMember member)
		: m_object(object), 
		m_member(member),
		m_handle(0), 
		m_cpp_event(NULL)
{
	assert(object && member);
}


template <typename ListenerT, typename ParamT>
NSlot1<ListenerT, ParamT>::~NSlot1() {
	
	if(m_cpp_event != NULL) {
		m_cpp_event->detach(m_handle);
	}
}


template <typename ListenerT, typename ParamT>
int NSlot1<ListenerT, ParamT>::connect(NEvent1<ParamT>* event) {
	m_cpp_event = event;
	m_handle = event->attach(m_object, m_member);
		
	return m_handle;
}


template <typename ListenerT, typename ParamT>
void NSlot1<ListenerT, ParamT>::disconnect() {
	m_cpp_event = NULL;
}

#endif // NSLOT1_HPP
