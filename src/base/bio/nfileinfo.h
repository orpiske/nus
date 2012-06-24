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
#ifndef NFILEINFO_H_
#define NFILEINFO_H_

#include <sys/types.h>
#include <sys/stat.h>

#if !defined(__WIN32) && !defined (_MSC_VER)
#include <unistd.h>
#endif // !defined(__WIN32) && !defined (_MSC_VER)

#include "ndefs.h"
#include "nobject.h"
#include "nstring.h"
#include "nioexception.h"


/**
\file nfileinfo.h NFileInfo class definition
\example ex_nfileinfo.cpp
*/


/**
\class NFileInfo
\brief NFileInfo is utility class for obtaining file information
\note This class still don't work well in Windows.
*/

class DllDeclSpec NFileInfo: public NObject { 
	public: 
		/**
		\brief Constructs a NFileInfo object
		*/
		NFileInfo(const NString &path);

		/**
		\brief Destroys a NFileInfo object
		*/
		~NFileInfo(void);


		/**
		\brief Tests whether the object is a file
		\return true in case of success or false otherwise
		*/
		bool isFile(void) const;

		/**
		\brief Tests whether the object is a directory
		\return true in case of success or false otherwise
		*/
		bool isDir(void) const;

		/**
		\brief Tests whether the object is a device
		\return true in case of success or false otherwise
		*/
		bool isDevice(void) const;

		/**
		\brief Tests whether the object is a fifo
		\return true in case of success or false otherwise
		\note Always false for windows
		*/
		bool isFifo(void) const;

		/**
		\brief Tests whether the object is a link
		\return true in case of success or false otherwise
		\note Always false for windows
		*/
		bool isLink(void) const;

		/**
		\brief Tests whether the object exists
		\return true in case of success or false otherwise
		*/
		bool exists(void) const;

		/**
		\brief Tests whether the object is readable by the owner
		\return true in case of success or false otherwise
		\note Always true for windows
		*/
		bool ownerRead(void) const;

		/**
		\brief Tests whether the object is readable by the group
		\return true in case of success or false otherwise
		\note Always true for windows
		*/
		bool groupRead(void) const;

		/**
		\brief Tests whether the object is readable by others
		\return true in case of success or false otherwise
		\note Always true for windows
		*/
		bool othersRead(void) const;

		/**
		\brief Tests whether the object is writable by the owner
		\return true in case of success or false otherwise
		\note Always true for windows
		*/
		bool ownerWrite(void) const;

		/**
		\brief Tests whether the object is writable by the group
		\return true in case of success or false otherwise
		\note Always true for windows
		*/
		bool groupWrite(void) const;

		/**
		\brief Tests whether the object is writable by others
		\return true in case of success or false otherwise
		\note Always true for windows
		*/
		bool othersWrite(void) const;

		/**
		\brief Tests whether the object is executable by the owner
		\return true in case of success or false otherwise
		\note Always true for windows
		*/
		bool ownerExecute(void) const;

		/**
		\brief Tests whether the object is executable by the group
		\return true in case of success or false otherwise
		\note Always true for windows
		*/
		bool groupExecute(void) const;

		/**
		\brief Tests whether the object is executable by others
		\return true in case of success or false otherwise
		\note Always true for windows
		*/
		bool othersExecute(void) const;

		/**
		\brief Tests whether the object is readable by the owner
		\param path Object (file, directory, etc) path
		\return true in case of success or false otherwise
		*/
		static bool isFile(const NString &path);

		/**
		\brief Tests whether the object is a directory
		\param path Object (file, directory, etc) path
		\return true in case of success or false otherwise
		*/
		static bool isDir(const NString &path);

		/**
		\brief Tests whether the object is a device
		\param path Object (file, directory, etc) path
		\return true in case of success or false otherwise
		*/
		static bool isDevice(const NString &path);

		/**
		\brief Tests whether the object is a fifo
		\param path Object (file, directory, etc) path
		\return true in case of success or false otherwise
		\note Always false for windows
		*/
		static bool isFifo(const NString &path);

		/**
		\brief Tests whether the object is a link
		\param path Object (file, directory, etc) path
		\return true in case of success or false otherwise
		\note Always false for windows
		*/
		static bool isLink(const NString &path);

		/**
		\brief Tests whether the object exists
		\param path Object (file, directory, etc) path
		\return true in case of success or false otherwise
		*/
		static bool exists(const NString &path);

		/**
		\brief Tests whether the object is readable by the owner
		\param path Object (file, directory, etc) path
		\return true in case of success or false otherwise
		\note Always true for windows
		*/
		static bool ownerRead(const NString &path);

		/**
		\brief Tests whether the object is readable by the group
		\param path Object (file, directory, etc) path
		\return true in case of success or false otherwise
		\note Always true for windows
		*/
		static bool groupRead(const NString &path);

		/**
		\brief Tests whether the object is readable by others
		\param path Object (file, directory, etc) path
		\return true in case of success or false otherwise
		\note Always true for windows
		*/
		static bool othersRead(const NString &path);

		/**
		\brief Tests whether the object is writable by the owner
		\param path Object (file, directory, etc) path
		\return true in case of success or false otherwise
		\note Always true for windows
		*/
		static bool ownerWrite(const NString &path);

		/**
		\brief Tests whether the object is writable by the group
		\param path Object (file, directory, etc) path
		\return true in case of success or false otherwise
		\note Always true for windows
		*/
		static bool groupWrite(const NString &path);

		/**
		\brief Tests whether the object is writable by others
		\param path Object (file, directory, etc) path
		\return true in case of success or false otherwise
		\note Always true for windows
		*/
		static bool othersWrite(const NString &path);

		/**
		\brief Tests whether the object is executable by the owner
		\param path Object (file, directory, etc) path
		\return true in case of success or false otherwise
		\note Always true for windows
		*/
		static bool ownerExecute(const NString &path);

		/**
		\brief Tests whether the object is executable by the group
		\param path Object (file, directory, etc) path
		\return true in case of success or false otherwise
		\note Always true for windows
		*/
		static bool groupExecute(const NString &path);

		/**
		\brief Tests whether the object is executable by others
		\param path Object (file, directory, etc) path
		\return true in case of success or false otherwise
		\note Always true for windows
		*/
		static bool othersExecute(const NString &path);

	private:
		NString m_path;
};

#endif // NFILEINFO_H_
