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
#ifndef NSKIPNODE_HPP
#define NSKIPNODE_HPP

/**
\file nskipnode.hpp Template class implementation for NSkipNode
*/


/**
\brief NSkipNode abstracts the concept of a skip node and is used by NSkipList 
 class
\note This class is used internally and should not be used for other means
*/

template <typename T>
class DllDeclSpec NSkipNode {
	public:
		/**
		\brief Data container
		*/
		T data;
		/**
		\brief Node height
		*/
		nint32 height;
		/**
		\brief Next node pointer
		*/
		NSkipNode<T> **next;
		
		/**
		\brief Constructs a NSkipNode without setting any attribute
		*/
		NSkipNode(void);
		
		/**
		\brief Constructs a NSkipNode with the given height
		\param height The height of the node
		*/
		NSkipNode(nint32 height);
		
		/**
		\brief Constructs a NSkipNode with the given height and data
		\param height The height of the node
		\param val The value of the node
		*/
		NSkipNode(nint32 height, const T &val);
		
		/**
		\brief Destroys a NSkipNode freeing any resources used
		*/
		~NSkipNode(void);

	private:
		/**
		\brief Zero the "next" pointer of the node
		*/
		void nzero(void);
		
		NSkipNode(const NSkipNode &);
		NSkipNode &operator=(const NSkipNode &);
};

template <typename T>
NSkipNode<T>::NSkipNode(void)
	: data(),
	height(0),
	next(NULL)
{

}


template <typename T>
NSkipNode<T>::NSkipNode(nint32 h)
	: data(),
	height(h),
	next(NULL)
{
	next = new NSkipNode*[height];
	nzero();
}


template <typename T>
NSkipNode<T>::NSkipNode(nint32 h, const T &val)
	: data(),
	height(h),
	next(NULL)
{
	next = new NSkipNode*[height];
	nzero();
	data = val;
}

template <typename T>
NSkipNode<T>::~NSkipNode(void) {
	delete[] next;
}


template <typename T>
void NSkipNode<T>::nzero(void) {
	for (int i = 0; i < height; i++) {
		next[i] = NULL;
	}
}
#endif // NSKIPNODE_HPP
