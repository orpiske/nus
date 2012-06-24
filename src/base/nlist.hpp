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
#ifndef NLIST_HPP
#define NLIST_HPP

/**
\file nlist.hpp Template class implementation for NList class
\example ex_nlist.cpp
*/


/**
\brief NList class implements a double-linked list
\note To add itens to a NList class, they must overload the operator=
*/
template<typename T>
class NList {
	public:
		class iterator;
		
		/**
		\brief Const iterator for NList objects
		*/
		typedef const iterator const_iterator;
		
		/**
		\brief Constructs an empty NList object
		*/
		NList(void);
		
		/**
		\brief Constructs a NList class with item val as its first item
		*/
		NList(const T &val);
		
		/**
		\brief Copy constructor
		*/
		NList(const NList<T> &other);
		
		/**
		\brief Destroys a NList object freeing the resources allocataded by
		this class
		*/
		virtual ~NList(void);

		/**
		\brief Gets the count of itens in the list
		\return The count of itens in the list
		*/
		nuint64 count(void) const;
		
		/**
		\brief Gets the count of itens in the list that are equal to a 
		given object
		\param obj An object to count against
		\return The count of itens in the list that are equal to a given 
		object
		\note Note that the object must implement operator==
		*/
		nuint64 count(const T &obj) const;
		
		
		/**
		\brief Gets the current number of itens in the class
		\return The current number of itens in the class
		\note See count()
		*/
		nuint64 size(void) const;
		/**
		\brief Checks if the list is empty
		\return True if the list is empty and false otherwise
		*/
		bool isEmpty(void) const;

		/**
		\brief Inserts an item at the end of the list
		\param val The item to be inserted
		\return A reference to this
	    	*/
		NList<T> &append(const T &val);
		
		/**
		\brief Inserts an item at a given position in the list
		\param val The item to be inserted
		\param pos Position where to insert the item
		\return A reference to this
		\note Pos must be valid in the list (pos >= 0 && pos <= size() -1)
		*/
		NList<T> &insert(const T &val, nuint64 pos);
		
		/**
		\brief Removes item at a given position
		\param pos Position of the item to be removed
		\return A reference to this
		\note Pos must be valid in the list (pos >= 0 && pos <= size() -1)
		*/
		NList<T> &removeAt(nuint64 pos);
		
		/**
		\brief Returns the item at a given position in the list
		\param pos Position of the item to get
		\return A reference to the item in the given pos. 
		\note Pos must be valid in the list (pos >= 0 && pos <= size() -1)
		*/
		const T &at(nuint64 pos) const;
		
		/**
		\brief Returns the value at a given position
		\param pos Position of the item to be removed
		\return The value at the position pos or a default constructed one 
		if pos is invalid (ie.: item does not exists)
		*/
		T value(nuint64 pos) const;
 
		/**
		\brief Returns the first item on the list
		\return A reference to the first item in the list
		*/
		T &first(void);
		
		/**
		\brief Returns the last item on the list
		\return A reference to the last item in the list
		*/
		T &last(void);
		
		/**
		\brief Removes the first item on the list and returns it
		\return The first item in the list or a default constructed value 
		if it does not exists
		*/
		T takeFirst(void);
		
		/**
		\brief Removes the last item on the list and returns it
		\return The last item in the list or a default constructed value 
		if it does not exists
		*/
		T takeLast(void);
		
		/**
		\brief Removes the a item with a given position on the list and
		returns it
		\return The item in the list or a default constructed value if
		it does not exists
		*/
		T takeAt(nuint64 pos);

		/**
		\brief Removes all the items on the list
		*/
		void clear(void);
		
		/**
		\brief Copies one list to another
		\param other A NList object with items to be coppied
		*/
		NList<T> &copy(const NList<T> &other);

		/**
		\brief Returns whether there is a next item in the list
		\return True if there is a next item or false otherwise
		*/
		bool hasNext(void) const;
		
		/**
		\brief Returns whether there is a previous item in the list
		\return True if there is a previous item or false otherwise
		*/
		bool hasPrevious(void) const;
		
		/**
		\brief Returns whether there is an item equal to val
		\return True if there is an item equal to val or false otherwise
		*/
		bool contains(const T &val) const;

		/**
		\brief Copies other list to this list
		\param rhs The list to be copied
		\return A reference to this
		*/
		NList<T> &operator=(const NList<T> &rhs);
		
		
		/**
		\brief Returns an iterator pointing to the first item in
		the list
		\return An iterator pointing to the first item in the
		list
		*/
		iterator begin(void);
		
		/**
		\brief Returns a const_iterator pointing to the first item in
		the list
		\return A const_iterator pointing to the first item in the
		list
		*/
		const_iterator constBegin(void) const;
		
		/**
		\brief Returns an iterator pointing to the last item in
		the list
		\return An iterator pointing to the last item in the
		list
		*/
		iterator end(void); 
		
		/**
		\brief Returns a const_iterator pointing to the last item in
		the list
		\return A const_iterator pointing to the last item in the
		list
		*/
		const_iterator constEnd(void) const;
	
	protected:
		mutable NListNode<T> *m_first;	/*!< The first node of the list */
		mutable NListNode<T> *m_node; 	/*!< The current node */

		nuint64 m_count;		/*!< The number of the itens in the list */

		/**
		\brief Goes to the first node
		*/
		void gotoFirst() const;
		
		/**
		\brief Goes to a position on the list
		\param pos A valid (pos < size) position
		*/
		void gotoPos(nuint64 pos) const;
};

template<typename T>
NList<T>::NList(void)
	: m_first(NULL),
	m_node(NULL),
	m_count(0)
{

}


template<typename T>
NList<T>::NList(const T &val)
	: m_first(NULL),
	m_node(NULL),
	m_count(0)
{
	append(val);
}


template<typename T>
NList<T>::NList(const NList<T> &other)
	: m_first(NULL),
	m_node(NULL),
	m_count(0)
{
	copy(other);
}


template<typename T>
NList<T>::~NList(void) {
	clear();
}


template<typename T>
bool NList<T>::isEmpty(void) const {
	if (m_count == 0) {
		return true;
	}

	return false;
}


template<typename T>
nuint64 NList<T>::count(void) const {
	return m_count;
}

template<typename T>
nuint64 NList<T>::count(const T &obj) const { 
	nuint64 ret = 0;
	
	gotoFirst();
	for (nint32 i = 0; i < size(); i++) {
		if (obj == at(i)) {
			ret++;
		}
	}
	
	return ret;
}


template<typename T>
nuint64 NList<T>::size(void) const {
	return count();
}


template<typename T>
NList<T> &NList<T>::append(const T &val) {
	NListNode<T> *node = NULL;

	node = new NListNode<T>;
	node->data = val;
	
	if (isEmpty()) {
		m_first = node;
	}
	else {
		m_node->next = node;
		node->previous = m_node;
	}
	m_node = node;
	m_count++;
	
	return *this;
}


template<typename T>
void NList<T>::gotoFirst(void) const {
	m_node = m_first;
}


template<typename T>
void NList<T>::gotoPos(nuint64 pos) const { 

#if !defined (_MSC_VER) 
	assert(pos < size());
#else
#if DNLIB_DEBUG
	if (pos < size()) { 
		printf("Assertion 'pos < size()' failed");
		exit(1);
	}
#endif // DNLIB_DEBUG
#endif // (_MSC_VER) 
	
	gotoFirst();
	for (nuint64 i = 0; i < pos; i++) {
		if (m_node && m_node->next) {
			m_node = m_node->next;
		}
	}
}


template<typename T>
NList<T> &NList<T>::insert(const T &val, nuint64 pos) {
	NListNode<T> *node = NULL;

	gotoPos(pos);
	node = new NListNode<T>;
	node->data = val;
	
	if (!isEmpty()) {
		node->previous = m_node->previous;
		m_node->previous = node;

		// Sets the 'next' pointer, only if it exists.
		if (node->previous) {
			node->previous->next = node;
		}
		node->next = m_node;
	}

	m_node = node;
	m_count++;
	
	return *this;
}


template<typename T>
NList<T> &NList<T>::removeAt(nuint64 pos) {
	NListNode<T> *previous = NULL;
	NListNode<T> *next = NULL;
	
	gotoPos(pos);
	
	previous = m_node->previous;
	next = m_node->next;
	
	delete m_node;
	m_node = NULL;
	
	if (previous) {
		previous->next = next;
		m_node = previous;
	}
	else {
		m_first = next;
		m_node = m_first;
	}

	if (next) {
		next->previous = previous;
		m_node = next;
	}

	m_count--;
	if (count() == 0) {
		m_first = NULL; 
		m_node = NULL;
	}
	
	return *this;
}


template<typename T>
const T &NList<T>::at(nuint64 pos) const {
	gotoPos(pos);

	return m_node->data;
}


template<typename T>
T NList<T>::value(nuint64 pos) const {
	T ret;

	this->gotoPos(pos);
	ret = m_node->data;

	return ret;
}


template<typename T>
T &NList<T>::first(void) {
	gotoPos(0);
	return m_node->data;
}


template<typename T>
T &NList<T>::last(void) {
	gotoPos(size() - 1);
	return m_node->data;
}


template<typename T>
void NList<T>::clear(void) {
	for (nint64 i = size() - 1; i >= 0; i--) {
		removeAt(i);
	}
	
}


template<typename T>
NList<T> &NList<T>::copy(const NList<T> &other) {
	clear();
	for (nuint64 i = 0; i < other.size(); i++) {
		append(other.value(i));
	}

	return *this;
}


template<typename T>
bool NList<T>::hasNext(void) const {
	if (m_node && m_node->next) {
		return true;
	}

	return false;
}


template<typename T>
bool NList<T>::hasPrevious(void) const {
	if (m_node && m_node->previous) {
		return true;
	}

	return false;
}


template <typename T>
T NList<T>::takeFirst(void) { 
    return takeAt(0);
}


template <typename T>
T NList<T>::takeLast(void) { 
    return takeAt(size() - 1);
}


template<typename T>
T NList<T>::takeAt(nuint64 pos) {
	T ret;

	ret = value(pos);
	removeAt(pos);
	return ret;
}


template<typename T>
NList<T> &NList<T>::operator=(const NList<T> &rhs) { 
	return copy(rhs);
}


template <typename T>
bool NList<T>::contains(const T &val) const { 
	T tmp;
	
	for (nuint64 i = 0; i < size(); i++) { 
		tmp = at(i);
		if (val == tmp) { 
			return true;
		}
	}
	
	return false;
}


/**
\brief NList::iterator iterates through a NList object
*/
template <typename T>
class NList<T>::iterator {
	public:
	 	/**
		\brief Constructs a NList::iterator
		\param node The node attached to the iterator
		*/
		iterator(NListNode<T> *node)
			: m_node(node)
		{}
		
		/**
		\brief Copy constructs a NList::iterator
		\param other Another NList::iterator
		*/
		iterator(const iterator &other): m_node(NULL) {
			m_node = other.m_node;
		}
		
		/**
		\brief Destroys a NList::iterator object
		*/
		~iterator(void) {}

		/**
		\brief Copies another NList::iterator
		\param rhs Another NList::iterator
		\return A reference to the current object
		*/
		iterator &operator=(const iterator &rhs) {
			m_node = rhs.m_node;
			
			return *this;
		}
		
		
		/**
		\brief Tests whether whether the current object is different of another
		\param rhs The object to be tested against
		\return true in case of success or false otherwise
		*/
		bool operator!=(const iterator &rhs) const {
			if (!m_node || !rhs.m_node) { 
				if (!m_node && !rhs.m_node) {
					return false;
				}

				return true;
			}
			
			if (m_node->data != rhs.m_node->data) {
				return true;
			}

			return false;
		}

		
		/**
		\brief Tests whether whether the current object equals another
		\param rhs The object to be tested against
		\return true in case of success or false otherwise
		*/
		bool operator==(const iterator &rhs) const {
			if (!m_node || !rhs.m_node) { 
				if (!m_node && !rhs.m_node) {
					return true;
				}

				return false;
			}

			if (m_node->data == rhs.m_node->data) {
				return true;
			}
			
			return false;
		}
		
		/**
		\brief Moves forward on the list
		\return A reference to the current object
		*/
		iterator operator++(int) {
			iterator tmp(*this);
			
			inc();
			return tmp;
		}
		
		/**
		\brief Moves forward on the list
		\return A reference to the current object
		*/
		const iterator &operator++(void) const {
			iterator tmp(*this);
			
			m_node = m_node->next;
			return *this;
		}
		
		
		/**
		\brief Moves forward on the list
		\return A reference to the current object
		*/
		const iterator operator++(int) const {
			iterator tmp(*this);
			
			++(*this);
			return tmp;
		}
		
		/**
		\brief Gets the data of the iterator
		\return The data of the node
		*/
		T& operator*(void) {
			return m_node->data;
		}
		
		/**
		\brief Gets the data of the iterator
		\return A const reference to the data of the node
		*/
		const T& operator*(void) const {
			return m_node->data;
		}
		
		/**
		\brief Gets the address of the iterator's data
		\return The address of the iterator's data
		*/
		T* operator->(void) {
			return &m_node->data;
		}
		
		/**
		\brief Gets the address of the iterator's data
		\return A const pointer to the address of the iterator's data
		*/
		const T* operator->(void) const {
			return &m_node->data;
		}
		
		
	private:
		mutable NListNode<T> *m_node;
		
		iterator inc(void) {
			iterator tmp(*this);
			
			m_node = m_node->next;
			return tmp;
		}
};


template <typename T>
typename NList<T>::iterator NList<T>::begin(void) {
	typename NList<T>::iterator i(m_first);
	
	return i;
}


template <typename T>
NLISTITERATOR_CONST NList<T>::constBegin(void) const {
	typename NList<T>::const_iterator i(m_first);
	
	return i;
} 


template <typename T>
typename NList<T>::iterator NList<T>::end(void) {
	return typename NList<T>::iterator(NULL);
}



template <typename T>
NLISTITERATOR_CONST NList<T>::constEnd(void) const {
	return typename NList<T>::const_iterator(NULL);
}

#endif // NLIST_HPP
