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
#ifndef NEVENT1_HPP
#define NEVENT1_HPP

/**
\file nevent1.hpp Template class file for event definition
*/

/**
\class NEvent1 
\brief NEvent1 class abstracts the concept of an event, notifying the handlers whenever
an event happens.
\see See the files in examples/raven for examples
*/
template <typename Param1>
class NEvent1 {
	public:
		/**
		\brief Type definition for the event handlers map
		*/
		typedef NMap<nint32, NEventHandlerBase1<Param1> *> HandlersMap;
		
		/**
		\brief Creates a NEvent1 object
		*/
		NEvent1();
		
		/**
		\brief Destroys a NEvent1 object
		*/
		virtual ~NEvent1();

		/**
		\brief Attaches a handler to the event
		\param object Pointer to the object that will react to an event
		\param *member Member function pointer to be 
		executed on response of a event
		*/
		template <typename ListenerT>
		NEventId attach(ListenerT* object, 
				void (ListenerT::*member)(Param1));
		
		/**
		\brief Detaches a handler from the event
		\param id Handler id
		\return true is successfully detached or false otherwise
		*/
		bool detach(NEventId id);
		
		/**
		\brief Checks whether a handler is attached
		\param id Handler id to be checked against the event
		\return true if it's attached or false otherwise
		*/
		bool isAttached(NEventId id);
		
		/**
		\brief Notify all the attached handlers
		\param param Any given parameter to be passed to the handlers
		*/
		void notify(Param1 param) const;

	private:
		HandlersMap m_handlers;
		int m_count;
};

template <typename Param1>
NEvent1<Param1>::NEvent1()
	: m_handlers(),
	m_count(0)
{}
	
template <typename Param1>
NEvent1<Param1>::~NEvent1() {

	for(typename HandlersMap::iterator it = m_handlers.begin(); 
		   it != m_handlers.end();
		    ++it)
	{
		delete it.value();
	}
}


template <typename Param1>
template <typename ListenerT>
NEventId NEvent1<Param1>::attach(ListenerT* object, 
						void (ListenerT::*member)(Param1)) 
{
	typedef void (ListenerT::*PtrMember)(Param1);
	
	NEventHandler1<ListenerT, Param1> *handle = 
			new NEventHandler1<ListenerT, Param1>(object, member);
	
	m_handlers.insert(m_count, handle);
	m_count++;
	return m_count - 1;
}


// Finds the handler and, if it exists, remove it
template <typename Param1>
bool NEvent1<Param1>::detach(NEventId id) {
	typename HandlersMap::iterator it = m_handlers.find(id);

	if(it == m_handlers.end()) { 
		return false;
	}

	if (m_handlers.erase(it)) {
		delete it.value();
	}
	
	
	return true;
}

template <typename Param1>
bool NEvent1<Param1>::isAttached(NEventId id) {
	return m_handlers.find(id) != m_handlers.end();
}

template <typename Param1>
void NEvent1<Param1>::notify(Param1 param) const {
	
	for(typename HandlersMap::const_iterator it = m_handlers.constBegin();
		   it != m_handlers.constEnd(); it++)
	{
		it.value()->notify(param);
	}
}

#endif // NEVENT1_HPP
