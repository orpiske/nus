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
#ifndef NOPT_HPP
#define NOPT_HPP

#include "noutput.h"

/**
\file nopt.hpp Class template for NOpt
*/

/**
\class NOpt 
\brief NOpt class is used to store a command line option passed to the application
*/
template <typename HandlerType>
class NOpt: public NObject {
	public:
		/**
		\brief Option handler type definition
		*/
		typedef bool (HandlerType::*Handler)(const NOpt &);
	
		/**
		\brief Creates a NOpt object
		*/
		NOpt(void);
		
		
		/**
		\brief Creates a NOpt object
		\param opt_short A letter identifying the option
		\param opt_long A long option name or "" in case it doesn't exist
		\param opt_opt A boolean value indicating whether the option is required 
		or not
		\param help A help text describing the option and its arguments
		\param handler The handler method for the option
		*/
		NOpt(const NString &opt_short, const NString &opt_long, bool opt_opt, 
			const NString &help, Handler handler);
		
		/**
		\brief Destroys a NOpt object
		*/
		~NOpt();
		
		/**
		\brief Sets the identifier for the short option
		\param opt_short A letter identifying the option
		*/
		void setShort(const NString &opt_short);
		
		/**
		\brief Gets the identifier for the short option
		\return A letter identifying the option
		*/
		NString getShort(void) const;
		
		/**
		\brief Sets the long option name
		\param opt_long A long option name or "" in case it doesn't exist
		*/
		void setLong(const NString &opt_long);
		
		/**
		\brief Gets the long option name
		\return The long option name
		*/
		NString getLong(void) const;
		
		
		/**
		\brief Sets whether the option is required or not
		\param opt_opt A boolean value: true if it's required or false 
		otherwise
		*/
		void setOpt(bool opt_opt);
		
		/**
		\brief Gets whether the option is required or not
		\return A boolean value: true if it's required or false otherwise
		*/
		bool hasOpt(void) const;
		
		
		/**
		\brief Sets a help text for the option
		\param help A help text describing the option, its arguments, etc
		*/
		void setHelp(const NString &help);
		
		/**
		\brief Gets the help text for the option
		\return The help text for the option
		*/
		NString getHelp(void) const;
		
		/**
		\brief Adds a value to the values list
		\param value The value to be added
		*/
		void addValue(const NString &value);
		
		
		/**
		\brief Adds a set of values to the values list
		\param values A NList<NString> object containing a list of values
		*/
		void addValues(const NList<NString> &values);
		
		
		/**
		\brief Gets the list of values of the option
		\return A NList<NString> object with the values
		*/
		NList<NString> getValues(void) const;
		
		// uses NOpt<HandlerType>::Handler instead of Handler to avoid 
		// warnings when generating the documentation
		/**
		\brief Sets the handler for the option
		\param handle A method pointer of type 
		void (NObject::*Handler)(const NOpt &)
		*/
		void setHandler(typename NOpt<HandlerType>::Handler handle);
		
		/**
		\brief Gets the handler for te option
		\return A method pointer of type void (NObject::*Handler)(const NOpt &)
		*/
		Handler getHandler(void) const;
		
		/**
		\brief Tests whether the object is null or not
		\return true if it's null or false otherwise
		*/
		bool isNull(void) const;
		
		
		/**
		\brief Sets whether this option is required
		\param required True if it's required or false otherwise
		*/
		void setRequired(bool required);
		
		
		/**
		\brief Gets whether this options is required
		\return True if it's required or false otherwise
		*/
		bool getRequired(void) const;
	
		/**
		\brief Tests whether the object equals another object
		\param rhs The object to test against
		\return true if it is equal or false otherwise
		*/
		bool operator==(const NOpt &rhs) const;
		
		
		/**
		\brief Tests whether the object is different than another object
		\param rhs The object to test against
		\return true if it is different or false otherwise
		*/
		bool operator!=(const NOpt &rhs) const;
	private:
		NString m_short;
		NString m_long;
		bool m_opt;
		NString m_help;
		NList<NString> m_values;
		Handler m_handler;

		NException maxCountExceeded(void) const;
};


template <typename HandlerType>
NOpt<HandlerType>::NOpt(void)
		: NObject(),
		m_short(),
		m_long(),
		m_opt(),
		m_help(),
		m_values(),
		m_handler(NULL)
{

}


template <typename HandlerType>
NOpt<HandlerType>::NOpt(const NString &opt_short, const NString &opt_long, 
				bool opt_opt, const NString &help, Handler handler)
			: NObject(), 
			m_short(opt_short), 
			m_long(opt_long),
			m_opt(opt_opt),
			m_help(help),
			m_values(),
			m_handler(handler)
{

}


template <typename HandlerType>
NOpt<HandlerType>::~NOpt() {

}


template <typename HandlerType>
void NOpt<HandlerType>::setShort(const NString &opt_short) {
	m_short = opt_short;
}


template <typename HandlerType>
NString NOpt<HandlerType>::getShort(void) const {
	return m_short;
}


template <typename HandlerType>
void NOpt<HandlerType>::setLong(const NString &opt_long) {
	m_long = opt_long;
}


template <typename HandlerType>
NString NOpt<HandlerType>::getLong(void) const {
	return m_long;
}


template <typename HandlerType>
void NOpt<HandlerType>::setOpt(bool opt_opt) {
	m_opt = opt_opt;
}


template <typename HandlerType>
bool NOpt<HandlerType>::hasOpt(void) const {
	return m_opt;
}


template <typename HandlerType>
void NOpt<HandlerType>::setHelp(const NString &help) {
	m_help = help;
}


template <typename HandlerType>
NString NOpt<HandlerType>::getHelp(void) const {
	return m_help;
}



template <typename HandlerType>
void NOpt<HandlerType>::addValue(const NString &value) {
	m_values.append(value);	
}


template <typename HandlerType>
void NOpt<HandlerType>::addValues(const NList<NString> &values) {
	m_values.copy(values);
}


template <typename HandlerType>
NList<NString> NOpt<HandlerType>::getValues(void) const {
	return m_values;
}


template <typename HandlerType>
void NOpt<HandlerType>::setHandler(typename NOpt<HandlerType>::Handler handler) {
	m_handler = handler;
}


template <typename HandlerType>
typename NOpt<HandlerType>::Handler NOpt<HandlerType>::getHandler(void) const {
	return m_handler;
}


template <typename HandlerType>
bool NOpt<HandlerType>::isNull(void) const {
	if ((m_short == 0) && (m_long == "")) {
		return true;
	}
	
	return false;
}


template <typename HandlerType>
bool NOpt<HandlerType>::operator==(const NOpt &rhs) const {
	if (m_short == "") { 
		if (m_long == rhs.getLong()) {
			return true;
		}
		
		return false;
	}

	if (m_short == rhs.getShort()) {
		return true;
	}
	
	if (m_long == rhs.getLong()) {
		return true;
	}
	

	return false; 
}


template <typename HandlerType>
bool NOpt<HandlerType>::operator!=(const NOpt &rhs) const {
	if (m_short == "") { 
		if (m_long != rhs.getLong()) {
			return true;
		}

		return false;
	}


	if (m_short != rhs.getShort()) {
		if (m_long != rhs.getLong()) {
			return true;
		}
	}

	return false; 
}

#endif // NOPT_HPP
