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
#ifndef NDIR_H_
#define NDIR_H_

#if defined(__WIN32) || defined(_MSC_VER)
#include <windows.h>
#else 
#include <sys/types.h>
#include <dirent.h>
#endif // defined(__WIN32) || defined(_MSC_VER)

#include "nobject.h"
#include "nstring.h"
#include "nlist.h"
#include "nioexception.h"
#include "noutput.h"

/**
\file ndir.h NDir class definition
\example ex_ndir.cpp
*/


/**
\class NDir 
\brief NDir is utility class for directory navigation
*/
class DllDeclSpec NDir: public NObject {
	public:
		/**
		\brief Constructs a NDir object
		\param name Directory name (path)
		*/
		NDir(const NString &name);

		/**
		\brief Destroys a NDir object
		*/
		~NDir(void);

		/**
		\brief Get directory contents
		\return A NList<NString> object with the directory contents
		*/
		NList<NString> getContents(void) const;

		/**
		\brief Get directory name
		\return The directory name
		*/
		NString getName(void) const;

	private:
		NList<NString> m_contents;
		NString m_dir_name;

		void init(const NString &name); 

#if defined(__WIN32) || defined (_MSC_VER)
		HANDLE m_dir_handle;
		
		void loadContents(WIN32_FIND_DATA *file_data);
#else 
		DIR *m_dir_handle;

		void loadContents(struct dirent *ent);
#endif // defined(__WIN32) || defined (_MSC_VER)

		NDir(const NDir &other);
		NDir &operator=(const NDir &rhs);
	
};

#endif // NDIR_H_
