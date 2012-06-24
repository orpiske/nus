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
#ifndef NSORTEDLIST_HPP
#define NSORTEDLIST_HPP

/**
\file nsortedlist.hpp Template class implementation for NSortedList class
\example ex_nsortedlist.cpp
\example ex_skip_vs_sorted.cpp
*/


/**
\brief NSortedList class provides a sorted list class, it is implemented by 
subclassing NList class
\note Note that the item to be inserted must overload the operators = and <
\note You should not use this class to store a large amount of itens because 
this class is very slow (+/- 200 itens added p/ sec on a p4 2.2ghz). You should
use a NSkipList instead
*/
template <typename T>
class NSortedList: public NList<T> { 
	public:
		/**
		\brief Constructs an empty NSortedList object
		*/
		NSortedList(void);
	
		/**
		\brief Constructs a NSortedList object and inserts val
		\param val The first item to be inserted
		*/
		NSortedList(const T &val);
		
		/**
		\brief Copy constructor
		\param other A NSortedList object containing the items to be copied
		*/
		NSortedList(const NSortedList<T> &other);
		
		/**
		\brief Inserts a item on the list
		\param val Item to be inserted
		\return A reference to this
		*/
		NSortedList<T> &insert(const T &val);
	
	private:
		NSortedList<T> &append(const T &val);
	
		/**
		\brief Finds the most likely previous position of val (ie. the not that is 
		storing 'data' that's immediatelly smaller than 'val').
		\param val Value to be located.
		\return A pointer to a NListNode<T> object pointing to the most likely position
		or NULL if there's no such position (ie. the node must be inserted at the beginning
		of the list.
		*/
		NListNode<T> *locate(const T &val);
};


template <typename T>
NSortedList<T>::NSortedList(void)
	: NList<T>()
{

} 


template <typename T>
NSortedList<T>::NSortedList(const T &val)
	: NList<T>(val)
{

}


template <typename T>
NSortedList<T>::NSortedList(const NSortedList<T> &other)
	: NList<T>(other)
{
	copy(other);
}


template <typename T>
NListNode<T> *NSortedList<T>::locate(const T &val) { 
	NList<T>::gotoFirst();
	
	while (NList<T>::m_node && NList<T>::m_node->next 
			&& NList<T>::m_node->data < val) 
	{
		NList<T>::m_node = NList<T>::m_node->next;
	}
	
	if (NList<T>::m_node) { 
		return NList<T>::m_node->previous;
	}
	
	return NList<T>::m_node;
}


template <typename T>
NSortedList<T> &NSortedList<T>::insert(const T &val) {
	NListNode<T> *tmp = NULL;

	if (contains(val)) {
		return *this;
	}
	
	NList<T>::m_node = locate(val);
	if (NList<T>::m_node) { 
		tmp = new NListNode<T>;
		tmp->data = val;
		
		tmp->previous = NList<T>::m_node;
		tmp->next = NList<T>::m_node->next;
		
		if (NList<T>::m_node->next) {
			NList<T>::m_node->next->previous = tmp;
		}
		NList<T>::m_node->next = tmp;
		
	}
	else {
		// There's no smaller item than val.
		tmp = new NListNode<T>;
		tmp->data = val;
		tmp->next = NList<T>::m_first;
		
		// If there's something in the list, fix it.
		if (NList<T>::m_first) { 
			NList<T>::m_first->previous = tmp;
		}
		NList<T>::m_first = tmp;
		NList<T>::m_node = NList<T>::m_first;
	}
	
#ifdef NEXTRADEBUG
	std::cout << "Node: " << (void *) NList<T>::m_node << std::endl;
	std::cout << "Previous: " << (void *) NList<T>::m_node->previous << std::endl;
	std::cout << "Next: " << (void *) NList<T>::m_node->next << std::endl;
#endif

	NList<T>::m_count++;
	return *this;
}


#endif // NSORTEDLIST_HPP
