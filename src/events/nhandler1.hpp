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
#ifndef NHANDLER1_HPP
#define NHANDLER1_HPP

/**
\file nhandler1.hpp Template class file for event handlers with 1 parameter
*/


/**
\class NEventHandlerBase1 
\brief Is the base class for handling events with 1 parameter
\see See the files in examples/raven for examples
*/
template <typename ParamT>
class NEventHandlerBase1 {
	public:
		/**
		\brief Destroys a NEventHandlerBase1 object
		*/
		virtual ~NEventHandlerBase1(void) { };
		
		/**
		\brief Executes the associated method.
		*/
		virtual void notify(ParamT param) = 0;

};


/**
\class NEventHandler1 
\brief Handles events with 1 parameter
\see See the files in examples/raven for examples
*/

template <typename ListenerT, typename ParamT>
class NEventHandler1: public NEventHandlerBase1<ParamT> {
	public:
		typedef void (ListenerT::*PtrMember)(ParamT);  /*!< Listener declaration to member function pointer */
	
		/**
		\brief Creates a new event handler
		\param object Pointer to an object that will react to an event
		\param member Member function pointer that will be executed on
		reaction to an event.
		*/
		NEventHandler1(ListenerT* object, PtrMember member);
		
		/**
		\brief Destroys a NEventHandlerBase1 object
		*/
		~NEventHandler1(void);
		
		/**
		\brief Executes the associated method.
		\param param Any given parameter to be passed to the method
		that will be executed on reaction to a given event
		*/
		void notify(ParamT param);
	
	private:
		ListenerT* m_object;
		PtrMember m_member;
		
		NEventHandler1(const NEventHandler1<ListenerT, ParamT> &other);
		NEventHandler1<ListenerT, ParamT> 
				&operator=(const NEventHandler1<ListenerT, ParamT> &rhs);

};


template <typename ListenerT, typename ParamT>
NEventHandler1<ListenerT, ParamT>::NEventHandler1(ListenerT* object, PtrMember member)
		: m_object(object),
		m_member(member)
{ 
	assert(member && member);
}


template <typename ListenerT, typename ParamT>
void NEventHandler1<ListenerT, ParamT>::notify(ParamT param) {
	(m_object->*m_member)(param);
}


template <typename ListenerT, typename ParamT>
NEventHandler1<ListenerT, ParamT>::~NEventHandler1(void) { }

#endif // NHANDLER1_HPP
