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
#ifndef NMAPITEM_HPP
#define NMAPITEM_HPP

/**
\file nmapitem.hpp NMapItem template class implementation
*/

/**
\brief NMapItem class abstracts a NMap item
\todo Document NMapItem class
*/
template <typename K, typename V>
class DllDeclSpec NMapItem {
	public:
		K key;	/*!< The key value/name */
		V value;	/*!< The value of the item */
		
		/**
		\brief Constructs a NMapItem object
		*/
		NMapItem(void)
			: key(),
			value()		
		{}

		/**
		\brief Test whether equals another NMapItem object
		\param rhs The object to be tested against
		\return true if it equals or false otherwise
		*/
		bool operator==(const NMapItem<K, V> &rhs) const {
			if (key == rhs.key && value == rhs.value) {
				return true;
			}
			
			return false;
		}

		/**
		\brief Test whether differs another NMapItem object
		\param rhs The object to be tested against
		\return true if it differs or false otherwise
		*/
		bool operator!=(const NMapItem<K, V> &rhs) const {
			if (key != rhs.key || value != rhs.value) {
				return false;
			}
			
			return true;
		}
		
		/**
		\brief Test whether is bigger than another NMapItem object
		\param rhs The object to be tested against
		\return true if it's bigger or false otherwise
		*/
		bool operator>(const NMapItem<K, V> &rhs) const {
			if (key > rhs.key) {
				return true;
			}
			
			return false;
		}
		
		
		/**
		\brief Test whether is smaller than another NMapItem object
		\param rhs The object to be tested against
		\return true if it's smaller or false otherwise
		*/
		bool operator<(const NMapItem<K, V> &rhs) const {
			if (key < rhs.key) {
				return true;
			}
			
			return false;
		}
		
		
		/**
		\brief Test whether is bigger than or equals another NMapItem object
		\param rhs The object to be tested against
		\return true if it's bigger than or equals another NMapItem object 
		or false otherwise
		*/
		bool operator>=(const NMapItem<K, V> &rhs) const {
			if (key > rhs.key) {
				return true;
			}
			
			if (key == rhs.key && value == rhs.value) {
				return true;
			}
			
			return false;
		}
		
		/**
		\brief Test whether is smaller than or equals another NMapItem object
		\param rhs The object to be tested against
		\return true if it's smaller than or equals another NMapItem object 
		or false otherwise
		*/
		bool operator<=(const NMapItem<K, V> &rhs) const {
			if (key < rhs.key) {
				return true;
			}
			
			if (key == rhs.key && value == rhs.value) {
				return true;
			}
			
			return false;
		}
};

#endif // NMAPITEM_HPP
