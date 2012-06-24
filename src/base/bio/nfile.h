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
#ifndef NFILE_H
#define NFILE_H

#include <cstdio>
#include <sys/stat.h>

/**
\file nfile.h NFile class definition
\example ex_nfile.cpp
*/

#ifdef _MSC_VER
#include <io.h>
#endif

#include "ndefs.h"
#include "niodevice.h"
#include "nstring.h"


/**
\brief NFile class is used to abstract file manipulation
*/
class DllDeclSpec NFile: public NIODevice { 
	public:
		/**
		\brief Constructs a NFile object
		*/
		NFile(void);

		/**
		\brief Constructs a NFile object
		\param path The path of the file to open
		\param mode The mode to open the file as defined by
		the enum NIODevice::Mode
		*/
		NFile(const NString &path, 
		      NIODevice::Mode mode = NIODevice::ReadWrite);
		/**
		\brief Destroys a NFile object releasing used resources
		*/
		~NFile(void);
		
		/**
		\brief Tests whether the file is at the end
		\return true if it is at the end or false otherwise
		*/
		bool atEnd(void) const;

		/**
		\brief Tests whether the file exists
		\return true if it exists or false otherwise
		*/
		bool exists(void) const;

		/**
		\brief Tests whether the file exists
		\param filepath A filename with the path to it.
		\return true if it exists or false otherwise
		*/
		static bool exists(const NString &filepath);

		/**
		\brief Obtains the current file handle
		\return An signed integer representing the file handle
		\note Please note that you must not close the file handle or 
		you may break your program
		*/
		int handle(void) const;
		
		/**
		\brief Opens the file
		\param mode The mode to open the file as defined by
		the enum NIODevice::Mode
		\note Please note that this method may throw an exception of 
		type NException
		*/
		void open(NIODevice::Mode mode);

		/**
		\brief Closes the file
		*/
		void closeDevice(void);
		
		/**
		\brief Reads data from the file
		\param buffer A NDataStream buffer to store read data
		\return The amount of bytes read or -1 if there's any
		error with the handle
		*/
		nint32 read(NDataStream *buffer);

		/**
		\brief Reads at most 'bytes' of data from the file
		\param buffer A NDataStream buffer to store read data
		\param bytes Max number of bytes to read
		\return The amount of bytes read or -1 if there's any
		error with the handle
		*/
		nint32 read(NDataStream *buffer, nuint32 bytes);

		/**
		\brief Reads data from the file until find a newline
		\param buffer A NDataStream buffer to store read data
		\return The amount of bytes read or -1 if there's any
		error with the handle
		*/
		nint32 readLine(NDataStream *buffer);

		/**
		\brief Writes data to the file
		\param data Data to be written to the file
		\param bytes Max number of bytes to write
		\return The amount of bytes written or -1 if there's 
		any error with the handle
		*/
		nint32 write(const NDataStream &data, nuint32 bytes = 0);
	
		/**
		\brief Returns the size of the file
		\return The size, in bytes, of the file
		*/
		nint64 size(void) const;

		/**
		\brief Sets the name of the file to manipulate
		\param path The path of the file
		*/
		void setFileName(const NString &path);

		/**
		\brief Gets the name of the file to manipulate
		\return The full path to the file
		*/
		NString getFileName(void) const;
	
	
	private:
		FILE *m_handle;
		NString m_path;
		
		char *getMode(NIODevice::Mode mode) const;
		
		NFile(const NFile &file);
		NFile &operator=(const NFile &file);
};


#endif // NFILE_H

