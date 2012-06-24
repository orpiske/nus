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
#ifndef NSKIPLIST_HPP
#define NSKIPLIST_HPP

/**
\file nskiplist.hpp Template class implementation for NSkipList
\example ex_nskiplist.cpp
*/

/**
\brief NSkipList provides a skip-list based container class
\note Items used in the NSkipList class must implement the following operators:
=, ==, < and >.
\todo This class must not accept a max height bigger than 32 (ie. sizeof(int))
*/
template <typename T>
class DllDeclSpec NSkipList {
	public:
		class iterator;
		
		/**
		\brief Const iterator for NList objects
		*/
		typedef const iterator const_iterator;
		
		/**
		\brief Constructs a NSkipList object with a pre-defined max height 
		
		*/
		NSkipList(void);
		
		/**
		\brief Constructs a NSkipList object with a defined max height 
		\param max Max height of the skip list (between 16 and 32)
		\throw NException If given a value smaller than 16 or bigger than 32
		*/
		NSkipList(nint32 max);
	
		/**
		\brief Destroys a NSkipList object freeing resources used
		*/
		~NSkipList(void);
		
		/**
		\brief Checks whether the skip-list is empty
		\return true if it is empty or false otherwise
		*/
		bool isEmpty(void) const;
		
		/**
		\brief Gets the max height of the skip list
		\return The max height of the skip list
		*/
		nint32 getHeight(void) const;
		
		/**
		\brief Gets the current height of the skip list
		\return The current height of the skip list
		*/
		nint32 getCurrentHeight(void) const;
		
		/**
		\brief Removes the item defined by key from the list. If it is 
		not found it will be silently ignored
		\param key Item to be removed from the list
		\return true if succeeded removing the item of false otherwise
		*/		
		bool erase(const T &key);
		
		/**
		\brief Checks whether a item exists in the list
		\param key The item to be checked
		\return true if the item exists or false otherwise
		\note It returns true if key's operator==(const T &key) function
		returns true for any member already on the list
		*/
		bool contains(const T &key) const;
		
		/**
		\brief Gets the size of the list
		\return The size of the list
		*/
		nuint64 size(void) const;
		
		/**
		\brief Gets the size of the list
		\return The size of the list
		*/
		nuint64 count(void) const;
		
		/**
		\brief Returns an iterator pointing to the first item in
		the list
		\return An iterator pointing to the first item in the
		list
		*/
		iterator begin(void) ;
		
		/**
		\brief Returns an iterator pointing to the first item in
		the list
		\return A const iterator pointing to the first item in the
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
		\brief Returns an iterator pointing to the last item in
		the list
		\return A const iterator pointing to the last item in the
		list
		*/
		const_iterator constEnd(void) const;
		
		/**
		\brief Finds a node containing key
		\param key The key to be searched
		\return An iterator pointing to key or end() if not found
		*/
		iterator find(const T &key);
		
		/**
		\brief Finds a node containing key
		\param key The key to be searched
		\return A const iterator pointing to key or end() if not found
		*/
		const_iterator find_const(const T &key) const;
		
		/**
		\brief Inserts the data defined by key in the list. If it is 
		already in the list it will be silently ignored
		\param key Item to be added to the list
		\return An iterator pointing to key of end() if already exists 
		*/
		iterator insert(const T &key);
		
		/**
		\brief Removes all nodes from the list
		*/
		void clear(void);
		
	private:
		static const nint32 DEFAULT_HEIGHT;
		
		NSkipNode<T> *m_head; // Head node;
		NSkipNode<T> **m_fix; // Update array;
		NSkipNode<T> *m_curl; // Current link
		nint32 m_maxh; // Max height;
		nint32 m_curh; // Current height;
		nuint64 m_size; // Size at level 0;
		
		// For the PRNG
		nint32 m_reset;
		nint32 m_bits;
		
		NSkipNode<T> *locate(const T &key) const;
		nint32 rlevel(void);
		void reset(void);
		
		NSkipNode<T> *findPtr(const T &key);
		
		NSkipList(const NSkipList &);
		NSkipList &operator=(const NSkipList &);
	
};

template <typename T>
const nint32 NSkipList<T>::DEFAULT_HEIGHT = 24;


template <typename T>
NSkipList<T>::NSkipList(void) 
	: m_head(NULL),
	m_fix(NULL),
	m_curl(NULL),
	m_maxh(DEFAULT_HEIGHT),
	m_curh(0),
	m_size(0),
	m_reset(0),
	m_bits(0)
{
	
	m_head = new NSkipNode<T>(m_maxh + 1);
	m_fix = new NSkipNode<T>*[m_maxh];
}


template <typename T>
NSkipList<T>::NSkipList(nint32 max)
	: m_head(NULL),
	m_fix(NULL),
	m_curl(NULL),
	m_maxh(max),
	m_curh(0),
	m_size(0),
	m_reset(0),
	m_bits(0)
{
	
	if (m_maxh < 16 || m_maxh > 32 ) {
		throw NException("Skiplist value must be between 16 and 32", 
					NException::BASE,
					NException::EX_OUT_OF_BOUNDS);
	}
	m_head = new NSkipNode<T>(m_maxh + 1);
	m_fix = new NSkipNode<T>*[m_maxh];
}


template <typename T>
NSkipList<T>::~NSkipList(void) {
	clear();
	
	delete m_head;
	delete[] m_fix;
}


/**
\brief Selects a random height for a node.
\return Returns a random height for a node.
\note Please note that the generated random height will be between 
*/
template <typename T>
nint32 NSkipList<T>::rlevel(void) {
	nint32 h = 0; //random height;
	nint32 found = 0; 
	
	for (h = 0; found == 0; h++) {
		if (m_reset == 0) {
			m_bits = nrand();
			m_reset = sizeof(nint32) * CHAR_BIT - 1;
		}
		
		found = m_bits & 1;
		m_bits = m_bits >> 1;
		m_reset--;
	}
	
	if (h >= m_maxh) {
		h = m_maxh - 1;
	}
	
	return h;
}


template <typename T>
bool NSkipList<T>::isEmpty(void) const {
	if (!m_head) {
		return true;
	}
	
	return false;
}


template <typename T>
nint32 NSkipList<T>::getHeight(void) const {
	return m_curh;
}


/**
\brief Finds the immediatelly smaller node than 'key'.
\return A node that's smaller than key or m_head if not found
*/
template <typename T>
NSkipNode<T> *NSkipList<T>::locate(const T &key) const {
	NSkipNode<T> *node = m_head;
	T tmp;
	
	for (int i = m_curh; i >= 0; i--) {
		while (node->next[i] != NULL) {
			tmp = node->next[i]->data;
			if (key <= tmp) {
				break;
			}
			
			node = node->next[i];
		}
		m_fix[i] = node;
	} 
	
	return node;
}




template <typename T>
bool NSkipList<T>::contains(const T &key) const {
	NSkipNode<T> *node = m_head;
	T tmp;
	
	for (int i = m_curh; i >= 0; i--) {
		while (node->next[i] != NULL) {
			tmp = node->next[i]->data;
			if (key == tmp) {
				return true;
			}
			
			node = node->next[i];
		}
		m_fix[i] = node;
	} 
	
	return false;
}


template <typename T>
void NSkipList<T>::reset(void) {
	m_curl = m_head->next[0];
}


template <typename T>
bool NSkipList<T>::erase(const T &key) {
	NSkipNode<T> *node = NULL;
	 
	node = findPtr(key);
	if (!node) {
		return false;
	}
	
	// Navigate through the nodes updating the "next" pointer of the 
	// immediatelly smaller node.
	for (int i = 0; i < m_curh; i++) {
		if (m_fix[i]->next[i] != node) {
			break;
		}
		
		m_fix[i]->next[i] = node->next[i];
	}
	
	// Updates the current height
	while (m_curh > 0) {
		if (m_head && m_head->next && m_head->next[m_curh - 1] != NULL) {
			break;
		}
		
		m_curh--;
	}
	
	m_size--;
	
	// Resets the "current" node pointer to match the current height.
	reset();	
	delete node;

	return true;
}


template <typename T>
nuint64 NSkipList<T>::size(void) const {
	return count();
}


template <typename T>
nuint64 NSkipList<T>::count(void) const {
	return m_size;
}


/**
\brief NSkipList::iterator is the iterator object for NSkipList
*/
template <typename T>
class NSkipList<T>::iterator {
	public:
	 	/**
		\brief Constructs a NSkipList::iterator
		*/
		iterator(NSkipNode<T> *node)
			: m_node(node)
		{}
		
		/**
		\brief Copy-constructs a NSkipList::iterator
		\param other The object to be copied
		*/
		iterator(const iterator &other): m_node(NULL) {
			m_node = other.m_node;
		}
		
		/**
		\brief Copies an iterator
		\param rhs The iterator to be copied
		\return A reference to the current object
		*/
		iterator &operator=(const iterator &rhs) {
			m_node = rhs.m_node;
			
			return *this;
		}
		
		/**
		\brief Test whether two iterator's items differs
		\param rhs The iterator with the item to be tested
		\return true if differs or false otherwise
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
		\brief Test whether two iterator's items are equal
		\param rhs The iterator with the item to be tested
		\return true if equals or false otherwise
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
		\brief Moves foward
		\return An iterator pointing to the next item
		*/
		iterator operator++(int) {
			iterator tmp(*this);
			
			inc();
			return tmp;
		}
		
		/**
		\brief Moves foward
		\return A const iterator pointing to the next item
		*/
		const iterator &operator++(void) const {
			iterator tmp(*this);
			
			m_node = m_node->next[0];
			return *this;
		}
		
		/**
		\brief Moves foward
		\return A const iterator pointing to the next item
		*/
		const iterator operator++(int) const {
			iterator tmp(*this);
			
			++(*this);
			return tmp;
		}
		
		/**
		\brief Gets the content of the iterator's item
		\return A reference to the content of the iterator's item
		*/	
		T& operator*(void) {
			return m_node->data;
		}
		
		/**
		\brief Gets the content of the iterator's item
		\return A const referecence to the content of the iterator's item
		*/
		const T& operator*(void) const {
			return m_node->data;
		}
		
		/**
		\brief Gets the address of the iterator's item
		\return A pointer to the address of the iterator's item
		*/
		T* operator->(void) {
			return &m_node->data;
		}
		
		/**
		\brief Gets the address of the iterator's item
		\return A const-pointer to the address of the iterator's item
		*/
		const T* operator->(void) const {
			return &m_node->data;
		}

	private:
		mutable NSkipNode<T> *m_node;
		
		iterator inc(void) {
			iterator tmp(*this);
			
			m_node = m_node->next[0];
			return tmp;
		}
};


template <typename T>
typename NSkipList<T>::iterator NSkipList<T>::begin(void) {
	if (m_head && m_head->next[0]) { 
		return typename NSkipList<T>::iterator(m_head->next[0]);
	}
	
	return typename NSkipList<T>::iterator(NULL);
}


template <typename T>
NSKIPLIST_CONST NSkipList<T>::constBegin(void) const {
	if (m_head && m_head->next[0]) { 
		return typename NSkipList<T>::const_iterator(m_head->next[0]);
	}
	
	return typename NSkipList<T>::const_iterator(NULL);
}


template <typename T>
typename NSkipList<T>::iterator NSkipList<T>::end(void) {
	return typename NSkipList<T>::iterator(NULL);
}


template <typename T>
NSKIPLIST_CONST NSkipList<T>::constEnd(void) const {
	return typename NSkipList<T>::const_iterator(NULL);
}


template <typename T>
NSkipNode<T> *NSkipList<T>::findPtr(const T &key) {
	NSkipNode<T> *node = m_head;
	T tmp;
		
	node = locate(key);
	if (!node) {
		return NULL;
	}
			
	node = node->next[0];
	if (node && key == node->data) {
		return node;	
	}
	
	return NULL;
}

template <typename T>
typename NSkipList<T>::iterator NSkipList<T>::find(const T &key) {
	return typename NSkipList<T>::iterator(find(key));
}


template <typename T>
NSKIPLIST_CONST NSkipList<T>::find_const(const T &key) const {
	return typename NSkipList<T>::const_iterator(find(key));
}


template <typename T>
typename NSkipList<T>::iterator NSkipList<T>::insert(const T &key) {
	nint32 height = 0;
	NSkipNode<T> *node = NULL;
		
	if (contains(key)) {
		return typename NSkipList<T>::iterator(NULL);
	}
	
	height = rlevel();
	node = new NSkipNode<T>(height, key);
	if (height > m_curh) {
		m_curh++;
		height = m_curh;
		m_fix[height] = m_head;
	}
	
	while (--height >= 0) {
		node->next[height] = m_fix[height]->next[height];
		m_fix[height]->next[height] = node;
	}
	
	m_size++;
	return typename NSkipList<T>::iterator(node);
}


template <typename T>
void NSkipList<T>::clear(void) {
	NSkipNode<T> *node = NULL;
	NSkipNode<T> *save = NULL;
	
	if (!m_head || !m_head->next) {
		return;
	}

	node = m_head->next[0];
	while (node) {
		save = node->next[0];
		delete node;
		node = save;
		
	}
}

#endif // NSKIPLIST_HPP
