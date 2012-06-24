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
#ifndef NREGEX_H
#define NREGEX_H

#include "nstring.h"
#include "noutput.h"
#include "nexception.h"
#include "nlist.h"

#include <sys/types.h>
#include <regex.h>

/**
\file nregex.h NRegex class definition
\example ex_nregex.cpp
*/

/**
\class NRegex 
\brief NRegex class implements a POSIX compatible regex matcher/compiler
\note This class is NOT PORTABLE. It works only on Linux and Mac OS X.
*/
class DllDeclSpec NRegex {
	public:
		/**
		\brief Regex matching offset
		*/
		typedef struct MatchOffset_t { 
			nint32 start;	/*!< Offset start */
			nint32 end;	/*!< Offset end */
		} MatchOffset; /*!< Defines a regex match offset */

		/**
		\brief Constructs a NRegex object
		\param reg The regex to match against
		\param str The string to be matched
		*/
		NRegex(const NString &reg, const NString &str);

		/**
		\brief Tests whether the string matches the regex
		\return true if matches or false otherwise
		*/
		bool match();
		//NList<MatchOffset> pos();
		
		static const nint32 NO_MATCH; /*!< Regex no match */
		static const nint32 MATCH_COUNT_MAX; /*!< Maximum match count */
	
	private:
		NRegex(const NRegex &);
		NRegex &operator=(const NRegex &);

		regex_t m_reg;
		NString m_str;
		NList<NRegex::MatchOffset> m_offsets;
		

		NString getError(int ret);
		NString getDetailedError(int ret);

};

#endif // NREGEX_H
