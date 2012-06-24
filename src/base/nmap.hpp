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
#ifndef NMAP_HPP
#define NMAP_HPP

/**
\file nmap.hpp NMap implementation
\example ex_nmap.cpp
*/

/**
\brief NMap class provides a skip-list based dictionary.
\todo remove(const K &key) Could be optimized. Improve NSkipList's erase first, though
\todo Document NMap
*/
template <typename K, typename V>
class DllDeclSpec NMap {
	public:
		class iterator;	
		typedef const iterator const_iterator;	/*!< NMap iterator */
		
		/**
		\brief Constructs a NMap object
		*/
		NMap(void);
		
		/**
		\brief Destroys a NMap object
		*/
		~NMap(void);
		
		/**
		\brief Returns whether there is an item
		\param keyname The keyname of the item to search
		\return True if there is an item equal to val or false otherwise
		*/
		bool contains(const K &keyname) const;
		
		/**
		\brief Returns whether there is an item
		\param keyname The keyname of the item to search
		\param val The value of the item to search
		\return True if there is an item equal to val or false otherwise
		*/
		bool contains(const K &keyname, const V &val) const;
		
		/**
		\brief Gets the current number of itens in the map
		\return The current number of itens in the map
		\note See count()
		*/
		nuint64 size(void) const;
		
		/**
		\brief Gets the current number of itens in the map
		\return The current number of itens in the map
		*/
		nuint64 count(void) const;
		
		/**
		\brief Gets the count of itens in the list that are equal to a 
		given keyname
		\param keyname The name of the key
		\return The count of itens in the map that are equal to a given 
		key
		\note Note that the 'keyname' object must implement operator==
		*/
		nuint64 count(const K &keyname) const;
		
		/**
		\brief Returns an iterator pointing to the first item in
		the map
		\return An iterator pointing to the first item in the
		map
		*/
		iterator begin(void);
		
		/**
		\brief Returns a const_iterator pointing to the first item in
		the map
		\return A const_iterator pointing to the first item in the
		map
		*/
		const_iterator constBegin(void) const;
		
		/**
		\brief Returns an iterator pointing to the last item in
		the map
		\return An iterator pointing to the last item in the
		map
		*/
		iterator end(void);
		
		/**
		\brief Returns a const_iterator pointing to the last item in
		the map
		\return A const_iterator pointing to the last item in the
		map
		*/
		const_iterator constEnd(void) const;
		
		/**
		\brief Removes the item defined by key from the map. If it is 
		not found it will be silently ignored
		\param pos An iterator pointing to the item to be removed
		\return true if succeeded removing the item of false otherwise
		*/	
		bool erase(iterator pos);
		
		/**
		\brief Finds a node containing key
		\param keyname The key to be searched
		\return An iterator pointing to key or end() if not found
		*/
		iterator find(const K &keyname);
		
		/**
		\brief Finds a node containing key
		\param keyname The key to be searched
		\param val The value of the item to be searched
		\return A const iterator pointing to key or end() if not found
		*/
		iterator find(const K &keyname, const V &val);
		
		/**
		\brief Finds a node containing key
		\param keyname The key to be searched
		\return A const iterator pointing to key or end() if not found
		*/
		const_iterator constFind(const K &keyname) const;
		
		/**
		\brief Finds a node containing key
		\param keyname The key to be searched
		\param val The value of the item to be searched
		\return A const iterator pointing to key or end() if not found
		*/
		const_iterator constFind(const K &keyname, const V &val) const;
	
		/**
		\brief Inserts the data defined by key in the list and val. 
		\param keyname The key of the item to be added to the map
		\param val The value of the item to be added to the map
		\return An iterator pointing to key of end() if already exists 
		\note If it is already in the list it will be silently ignored
		*/
		iterator insert(const K &keyname, const V &val);
		
		/**
		\brief Checks whether the map is empty
		\return true if it is empty or false otherwise
		*/
		bool isEmpty(void) const;
		
		/**
		\brief Gets the first key containing a given value
		\param val The value of the item
		\return The found key or a default constructed value if not found
		*/
		const K key(const V val) const;
		
		/**
		\brief Gets a list of the keys in the map
		\return The list of the keys in the map
		*/
		NList<K> keys(void) const;
		
		/**
		\brief Gets a list of the keys in the map that contains a given 
		value
		\return The list of the keys in the map
		*/
		NList<K> keys(const V val);
		
		/**
		\brief Removes the itens containing a given key name
		\param keyname The value of the key
		\return The number of the itens removed
		*/
		nuint64 remove(const K &keyname);
		
		/**
		\brief Removes the a item with a given key value in the map and
		returns it
		\return The item in the map or a default constructed value if
		it does not exists
		*/
		V take(const K &keyname);
		
		/**
		\brief Gets the value of a given key
		\param keyname The value of the key
		\return The value or a default constructed value if not found
		*/
		V value(const K &keyname) const;
		
		/**
		\brief Gets the value of a given key
		\param keyname The value of the key
		\param defaultValue The default value for the return object, if 
		not found
		\return The value or a defaultValue if not found
		*/
		V value(const K &keyname, const V &defaultValue) const;
		
		/**
		\brief Gets a list of values in the map
		\return A NList object with the values in the map
		*/
		NList<V> values(void) const;
		
		/**
		\brief Gets a list of values in the map with a given keyname
		\param keyname The value of the key
		\return A NList object with the values in the map
		*/
		NList<V> values(const K &keyname) const;
		
		/**
		\brief Clears the map
		*/
		void clear(void);
		
		/**
		\brief Copies another map
		\param rhs The map to be copied
		*/
		void copy(const NMap<K, V> &rhs);
		
		/**
		\brief Copies another map
		\param rhs The map to be copied
		\return A reference to the current object
		*/
		NMap<K, V> &operator=(const NMap<K, V> &rhs);
		
		/**
		\brief Tests whether a map differs from another
		\param rhs The map to be tested
		\return true if it differs or false otherwise
		*/
		bool operator!=(const NMap<K, V> &rhs) const;
		
		/**
		\brief Tests whether a map equals another
		\param rhs The map to be tested
		\return true if it is equal or false otherwise
		*/
		bool operator==(const NMap<K, V> &rhs) const;
		
		/**
		\brief Gets the value of a given key
		\param keyname The value of the key
		\return The value or a default constructed value if not found
		*/
		V operator[](const K &keyname);
		
		/**
		\brief Gets the value of a given key
		\param keyname The value of the key
		\return The value or a default constructed value if not found
		*/
		const V &operator[](const K &keyname) const;
	
	private:
		typedef NSkipList<NMapItem<K, V> > NMapSkip;
		NMapSkip m_skip;
};


template <typename K, typename V>
NMap<K, V>::NMap(void)
	: m_skip()
{

}

template <typename K, typename V>
NMap<K, V>::~NMap(void) {

}


template <typename K, typename V>
nuint64 NMap<K, V>::size(void) const {
	return m_skip.count();
}


template <typename K, typename V>
nuint64 NMap<K, V>::count(void) const {
	return m_skip.count();
}


template <typename K, typename V>
nuint64 NMap<K, V>::count(const K &keyname) const {
	nuint64 items = 0;
	
	for (typename NMapSkip::iterator i = m_skip.begin(); 
		    i != m_skip.end();
		    i++)
	{
		if ((*i).key == keyname) {
			items++;
		}
	}
	
	return items;
}


/**
\brief NMap::iterator class provides an iterator to navigate through the map 
object
*/
template <typename K, typename V>
class NMap<K, V>::iterator { 
	public:
		/**
		\brief Constructs a NMap::iterator
		*/
		iterator(void): m_it(NULL) { }
		
		/**
		\brief Copy-constructs a NMap::iterator
		\param other The object to be copied
		*/
		iterator(const iterator &other): m_it(NULL) {
			m_it = other.m_it;
		}
		
		/**
		\brief Copy-constructs a NMap::iterator
		\param it A NMapSkip::iterator object to be copied
		*/
		iterator(const typename NMapSkip::iterator &it): m_it(it) {
		
		}
		
		/**
		\brief Gets the key value of the iterator's item
		\return The key value of the iteratorp's item
		*/
		K key(void) const {
			return (*m_it).key;
		}
		
		/**
		\brief Gets the value of the iterator's item
		\return The value of the iterator's item
		*/
		V value(void) const {
			return (*m_it).value;
		}
		
		/**
		\brief Copies an iterator
		\param rhs The iterator to be copied
		\return A reference to the current object
		*/
		iterator &operator=(const iterator &rhs) {
			m_it = rhs.m_it;
			
			return *this;
		}
		
		/**
		\brief Test whether two iterator's items are equal
		\param rhs The iterator with the item to be tested
		\return true if equals or false otherwise
		*/
		bool operator==(const iterator &rhs) const {
			if (m_it == rhs.m_it) {
				return true;
			}
			
			return false;
		}
		
		
		/**
		\brief Test whether two iterator's items differs
		\param rhs The iterator with the item to be tested
		\return true if differs or false otherwise
		*/
		bool operator!=(const iterator &rhs) const {
			if (m_it != rhs.m_it) {
				return true;
			}
			
			return false;
		}
		
		/**
		\brief Gets the content of the iterator's item
		\return The content of the iterator's item
		*/
		NMapItem<K, V> operator*(void) const {
			return *m_it;
		}
		
		/**
		\brief Moves foward
		\return An iterator pointing to the next item
		*/
		iterator inc(void) {
			iterator tmp(*this);
			
			m_it++;
			return tmp;
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
			
			m_it++;
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
		
	private:
		typename NMapSkip::iterator m_it;
};

template <typename K, typename V>
typename NMap<K, V>::iterator NMap<K, V>::begin(void) {
	return typename NMap<K, V>::iterator(m_skip.begin());
}


template <typename K, typename V>
NMAPITERATOR_CONST NMap<K, V>::constBegin(void) const {
	return typename NMap<K, V>::const_iterator(m_skip.constBegin());
}	




template <typename K, typename V>
typename NMap<K, V>::iterator NMap<K, V>::end(void) {
	return typename NMap<K, V>::iterator(m_skip.end());
}


template <typename K, typename V>
NMAPITERATOR_CONST NMap<K, V>::constEnd(void) const {
	return typename NMap<K, V>::const_iterator(m_skip.constEnd());
}


template <typename K, typename V>
bool NMap<K, V>::erase(iterator pos) {
	return m_skip.erase(*pos);
}


template <typename K, typename V>
typename NMap<K, V>::iterator NMap<K, V>::find(const K &keyname) {
	for (typename NMapSkip::iterator i = m_skip.begin(); i != m_skip.end(); i++) {
		if ((*i).key == keyname) {
			return typename NMap<K, V>::iterator(i);
		}
		
	}
	
	return typename NMap<K, V>::iterator(m_skip.end());
}


template <typename K, typename V>
NMAPITERATOR_CONST NMap<K, V>::constFind(const K &keyname) const {
	for (typename NMapSkip::const_iterator i = m_skip.constBegin(); 
		    i != m_skip.constEnd(); i++) 
	{
		if ((*i).key == keyname) {
			return typename NMap<K, V>::const_iterator(i);
		}
		
	}
	
	return typename NMap<K, V>::const_iterator(m_skip.constEnd());
}


template <typename K, typename V>
typename NMap<K, V>::iterator NMap<K, V>::find(const K &keyname, const V &val) {
	for (typename NMapSkip::iterator i = m_skip.begin(); i != m_skip.end(); i++) {
		if ((*i).key == keyname && (*i).value == val) {
			return typename NMap<K, V>::iterator(i);
		}
	}
	
	return typename NMap<K, V>::iterator(m_skip.end());
}


template <typename K, typename V>
NMAPITERATOR_CONST NMap<K, V>::constFind(const K &keyname, const V &val) const {
	for (typename NMapSkip::const_iterator i = m_skip.constBegin(); 
		    i != m_skip.constEnd(); i++) 
	{
		if ((*i).key == keyname && (*i).value == val) {
			return typename NMap<K, V>::const_iterator(i);
		}
	}
	
	return typename NMap<K, V>::const_iterator(m_skip.constEnd());
}


template <typename K, typename V>
typename NMap<K, V>::iterator NMap<K, V>::insert(const K &keyname, const V &val) {
	NMapItem<K, V> item;
	
	item.key = keyname;
	item.value = val;
	
	return typename NMap<K, V>::iterator(m_skip.insert(item));
}

template <typename K, typename V>
bool NMap<K, V>::isEmpty(void) const {
	return m_skip.isEmpty();
}


template <typename K, typename V>
const K NMap<K, V>::key(const V val) const {
	K tmp;
	
	for (typename NMapSkip::iterator i = m_skip.begin(); i != m_skip.end(); i++) {
		if ((*i).value == val) {
			tmp = (*i).key;
			break;
		}
	}
	
	return tmp;
}


template <typename K, typename V>
NList<K> NMap<K, V>::keys(void) const {
	NList<K> ret;
	
	
	for (typename NMapSkip::const_iterator i = m_skip.constBegin(); 
		    i != m_skip.constEnd(); i++) 
	{
		ret.append((*i).key);
	}
	
	return ret;
}


template <typename K, typename V>
NList<K> NMap<K, V>::keys(const V val) {
	NList<K> ret;
	
	for (typename NMapSkip::iterator i = m_skip.begin(); i != m_skip.end(); i++) {
		if ((*i).value == val) {
			ret.append((*i).key);
			break;
		}
	}
	
	return ret;
}


template <typename K, typename V>
nuint64 NMap<K, V>::remove(const K &keyname) {
	nuint64 items = 0;
	
	for (typename NMapSkip::iterator i = m_skip.begin(); i != m_skip.end(); i++) {
		if ((*i).key == keyname) {
			if (m_skip.remove((*i))) {
				items++;
			}
		}
	}
	
	return items;
}

template <typename K, typename V>
V NMap<K, V>::take(const K &keyname) {
	V tmp;
	
	for (typename NMapSkip::iterator i = m_skip.begin(); i != m_skip.end(); i++) {
		if ((*i).key == keyname) {
			tmp = (*i).value;
			m_skip.remove((*i));
		}
	}
}


template <typename K, typename V>
V NMap<K, V>::value(const K &keyname) const {
	V tmp;
	
	for (typename NMapSkip::const_iterator i = m_skip.constBegin(); 
		    i != m_skip.constEnd(); i++) 
	{
		if ((*i).key == keyname) {
			tmp = (*i).value;
			break;
		}
	}
	
	return tmp;

}

template <typename K, typename V>
V NMap<K, V>::value(const K &keyname, const V &defaultValue) const {
	V tmp = defaultValue;
	
	for (typename NMapSkip::const_iterator i = m_skip.constBegin(); 
		    i != m_skip.constEnd(); i++) 
	{
		if ((*i).key == keyname) {
			tmp = (*i).value;
			break;
		}
	}
	
	return tmp;
}


template <typename K, typename V>
NList<V> NMap<K, V>::values(void) const {
	NList<V> ret;
	
	for (typename NMapSkip::const_iterator i = m_skip.constBegin(); 
		    i != m_skip.constEnd(); i++) 
	{
		ret.append((*i).value);
	}
	
	return ret;
}

template <typename K, typename V>
NList<V> NMap<K, V>::values(const K &keyname) const {
	NList<V> ret;
	
	for (typename NMapSkip::const_iterator i = m_skip.constBegin(); 
		    i != m_skip.constEnd(); i++) 
	{
		if ((*i).key == keyname) {
			ret.append((*i).value);
		}
	}
	
	return ret;
}


template <typename K, typename V>
void NMap<K, V>::copy(const NMap<K, V> &rhs) {
	m_skip.clear();
	
	for (typename NMap::iterator i = rhs.constBegin(); i != rhs.constEnd(); i++) {
		insert((*i).key, (*i).value);
	}
}


template <typename K, typename V>
bool NMap<K, V>::contains(const K &keyname) const {
	if (constFind(keyname) != constEnd()) {
		return true;
	}
	
	return false;
}


template <typename K, typename V>
bool NMap<K, V>::contains(const K &keyname, const V &val) const {
	if (constFind(keyname, val) != constEnd()) {
		return true;	
	}
	
	return false;
}



template <typename K, typename V>
NMap<K, V> &NMap<K, V>::operator=(const NMap<K, V> &rhs) {
	copy(rhs);
	
	return *this;
}


template <typename K, typename V>
bool NMap<K, V>::operator!=(const NMap<K, V> &rhs) const {
	for (typename NMapSkip::iterator i = rhs.begin(); i != rhs.end(); i++) {
		if (contains((*i).key, (*i).value)) {
			return false;
		}
	}
	
	return true;
}


template <typename K, typename V>
bool NMap<K, V>::operator==(const NMap<K, V> &rhs) const {
	for (typename NMapSkip::iterator i = rhs.begin(); i != rhs.end(); i++) {
		if (!contains((*i).key, (*i).value)) {
			return false;
		}
	}
	
	return true;
}


template <typename K, typename V>
V NMap<K, V>::operator[](const K &keyname) {
	return value(keyname);
}


template <typename K, typename V>
const V &NMap<K, V>::operator[](const K &keyname) const {
	return value(keyname);
}

#endif // NMAP_HPP
