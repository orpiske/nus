// LICENSE: (Please see the file COPYING for details)
//
// NUS - Nemesis Utilities System: A C++ application development framework 
// Copyright (C) 2006, 2007 Otavio Rodolfo Piske
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
#ifndef NIODEVICE_H
#define NIODEVICE_H

/**
\file niodevice.h Basic IO device handling class
*/

#include "ndefs.h"
#include "nobject.h"
#include "ndatastream.h"


/**
\brief NIODevice class is the base class for working with IO devices
*/
class DllDeclSpec NIODevice: public NObject {
	public:
		/**
		\brief Enumerates file opening modes
		\todo Change to upper case
		*/
		enum Mode {
			NotOpen = 1,	/*!< Not open */
			ReadOnly = 2,	/*!< Read Only */
			ReadWrite = 4,	/*!< Read write */
			Append = 8,		/*!< Append */
			Truncate = 16,	/*!< Truncate */
		};
		
		/**
		\brief Constructs a NIODevice object
		*/
		NIODevice(void);
		
		/**
		\brief Destroys a NIODevice object
		*/
		virtual ~NIODevice();
		
		/**
		\brief Opens an associated device
		\param mode Open mode as defined by enum Mode
		*/
		virtual void open(Mode mode) = 0;
		
		/**
		\brief Closes an associated device
		*/
		virtual void closeDevice(void) = 0;
		
		/**
		\brief Sets the max size of the buffer used for reading data
		\param size The size, in bytes, for the buffer
		*/
		void setReadBufferSize(nuint32 size);
		
		/**
		\brief Gets the max size of the buffer used for reading data
		\return The buffer size
		*/
		nuint32 getReadBufferSize(void) const;
		
		
		/**
		\brief Reads data from the device
		\param buffer Output buffer for the bytes read
		\return The number of bytes read
		*/
		virtual nint32 read(NDataStream *buffer) = 0;
		
		/**
		\brief Reads data from the device
		\param buffer Output buffer for the bytes read
		\param bytes Number of bytes to be read from the device.
		\return The number of bytes read
		*/
		virtual nint32 read(NDataStream *buffer, nuint32 bytes) = 0;
		
		/**
		\brief Reads a line from the device
		\param buffer Output buffer for the bytes read
		\return The number of bytes read
		*/
		virtual nint32 readLine(NDataStream *buffer) = 0;
		
		/**
		\brief Writes data to the device
		\param data Data to be written to the device
		\param bytes Amount of bytes to be written to the device. 0 means that 
		all bytes of data will be written
		\return The number of bytes read
		*/
		virtual nint32 write(const NDataStream &data, nuint32 bytes = 0) = 0;
	
	protected:
		nuint32 m_readBufferSize;	/*!< Size of the read buffer */
};

#endif // NIODEVICE_H
