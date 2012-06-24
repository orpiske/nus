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
#ifndef NEXCEPTION_H
#define NEXCEPTION_H

/**
\file nexception.h Class definition for NException object
*/

#include "nstring.h"

/**
\brief Error flag type definition
*/
typedef nint32 Flag;

/**
\brief NException is the base class for throwable exceptions
*/
class DllDeclSpec NException { 
	public:
		/**
		\brief Available modules 
		*/
		enum Module { 
			NOT_SET,  	/*!< Unknown/not set */
			OS,		/*!< Operating system */
			BASE,		/*!< Nus' base module */
			BASEIO,	/*!< Nus' base io module */
			OUTPUT,	/*!< Nus' output module */
			NETWORK,	/*!< Nus' network module */
			XML,		/*!< Nus' xml module */
			SECURITY, 	/*!< Nus' security module */
			DBAL, 		/*!< Nus' database access module */
			TOOLS, 		/*!< Nus' support tools */
			USERAPP,	/*!< User application */
			USERLIB		/*!< User library */
		};
	
/*
const Flag NException::EX_NONE = 0;
const Flag NException::EX_OUT_OF_BOUNDS = 1;
*/

		/**
		\brief Non-error flag for the exception: 
		*/
		static const Flag EX_NONE = 0;

		/**
		\brief Out of bounds erro flag for the exception: 
		*/
		static const Flag EX_OUT_OF_BOUNDS = 1;	

		/**
		\brief Constructs a NException object
		*/
		NException(void);

		/**
		\brief Constructs a NException object
		\param desc Exception description
		\param module The module in which the exception occurred
		\param flag An unique id that identifies the error that occurred
		*/
		NException(const NString &desc, Module module, Flag flag = EX_NONE);

		/**
		\brief Destroys a NException object
		*/
		virtual ~NException(void);
		
		
		/**
		\brief Sets the description of a NException object
		\param desc Exception description
		*/
		void setDescription(const NString &desc);
		
		/**
		\brief Gets the description of a NException object
		\return Returns the description of a NException object
		*/
		NString getDescription(void) const;
		
		/**
		\brief Sets the module in which the exception was thrown
		\param module The module in which the exception was thrown as defined 
		by the enum Module.
		*/
		void setModule(Module module);
		
		/**
		\brief Returns the module in which the exception was thrown
		\return The module as defined by enum Module
		*/
		NException::Module getModule(void) const;
		
		
		/**
		\brief Sets the description of a NException object
		\param other NException object to be copied
		*/
		NException &operator=(const NException &other);
		
		
		/**
		\brief Sets the error flag associated with the object
		\param flag The value of the flag associated with the object
		*/
		void setFlag(Flag flag);
		/**
		\brief Gets the error flag associated with the object
		\return The error flag of the object
		*/
		Flag getFlag(void) const;
		
	protected:
		/**
		\brief Sets the error identification for a given exception
		\param error_id The identification for the error.
		*/
		void setErrorId(nint16 error_id);
		
	private:
		NString m_description;
		Module m_module;
		Flag m_flag;
};



#endif // NEXCEPTION_H
