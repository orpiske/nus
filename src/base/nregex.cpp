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
#include "nregex.h"

/**
\file nregex.cpp NRegex class implementation
*/

const nint32 NRegex::NO_MATCH = -1;
const nint32 NRegex::MATCH_COUNT_MAX = 2048;

NRegex::NRegex(const NString &reg, const NString &str)
	: m_reg(),
	m_str(str),
	m_offsets()
{
	int reg_ret = 0;

	reg_ret = regcomp(&m_reg , reg.toChar(), REG_EXTENDED | REG_NOSUB);
	if (reg_ret != 0) {
		throw NException(getError(reg_ret), NException::BASE);
	}
}

NString NRegex::getError(int retval) {
	NString ret;	

	switch (retval) { 
		case REG_BADBR: 
			ret = "[REG_BADBR] Invalid use of back reference operator";
			break;
		case REG_BADPAT:
			ret = "[REG_BADPAT] Invalid use of pattern operators such as group or list";
			break;
		case REG_BADRPT:
              		ret = "Invalid  use  of  repetition operators such as "
			"using `*' as the first character.";
			break;
		case REG_EBRACE:
			ret = "[REG_EBRACE] Un-matched brace interval operators.";
			break;
		case REG_EBRACK:
			ret = "[REG_EBRACK] Un-matched bracket list operators.";
			break;
		case REG_ECOLLATE:
			ret = "[REG_ECOLLATE] Invalid collating element.";
			break;
		case REG_ECTYPE:
			ret = "[REG_ECTYPE] Unknown character class name.";
			break;
#if !defined(__APPLE__) && !defined(__SVR4)
		case REG_EEND:
			ret = "[REG_EEND] Non specific error. This is not "
			"defined by POSIX.2.";
			break;
#endif // !defined(__APPLE__) && !defined(__SVR4)
		case REG_EESCAPE:
			ret = "[REG_EESCAPE] Trailing backslash.";
			break;
		case REG_EPAREN:
			ret = "[REG_EPAREN] Un-matched parenthesis group operators.";
			break;
		case REG_ERANGE:
			ret = "[REG_ERANGE] Invalid use of the range operator, "
			"eg. the ending point  of  the range occurs prior to "
			"the starting point.";
			break;
#if !defined(__APPLE__) && !defined(__SVR4)
		case REG_ESIZE:
			ret = "[REG_ESIZE] Compiled  regular  expression  "
			"requires  a pattern buffer larger than 64Kb.  This is "
			"not defined by POSIX.2.";
			break;
#endif // !defined(__APPLE__) && !defined(__SVR4)
		case REG_ESPACE:
			ret = "[REG_ESPACE] The regex routines ran out of memory.";
			break;
		case REG_ESUBREG:
			ret = "[REG_ESUBREG] Invalid back reference to a subexpression";
			break;
	}

	
	ret = ret + ": " + getDetailedError(retval);
	return ret;
}

NString NRegex::getDetailedError(int retval) {
	size_t len;
	char *buffer = NULL;
	NString ret;

	len = regerror (retval, &m_reg, NULL, 0);
	buffer = (char *) malloc (len);	
	
	if (!buffer) {
		//NWarning::print() << "Not enough memory for detailed error";
		
		return ret;
	}

	memset(buffer, 0, len);
	regerror (retval, &m_reg, buffer, len);
	ret.set(buffer);	
	free(buffer);
	
	return ret;
}


bool NRegex::match() { 
	int ret = 0;
	
	ret = regexec(&m_reg, m_str.toChar(), 0, NULL, 0);

	if (ret == 0) {
		return true;
	}
	else { 
		if (ret == REG_NOMATCH) {
			return false;
		}
	}

	throw NException(getError(ret), NException::BASE);
}

// TODO: broken. fix it.
/*
NList<NRegex::MatchOffset> NRegex::pos() {
	int ret = 0;
	int i = 0;
	int start_pos = 0;
	regmatch_t match;
	MatchOffset off;
	const char *tmp_str = m_str.toChar();

	memset(&off, 0, sizeof(off));
	memset(&match, 0, sizeof(match));
	do {
		ret = regexec(&m_reg, tmp_str + off.start, 1, &match, REG_NOTBOL);
		
		if (ret != 0) { 
			if (ret = REG_NOMATCH) {
				break;
			}
		
			throw NException(getError(ret), NException::BASE);
		}

		printf("aaaaa %i | %i\n", match.rm_so, match.rm_eo);

	
		off.start += off.start + match.rm_so;
		off.end += off.start + match.rm_eo;

		m_offsets.append(off);
		i++;
	} while (ret == 0);
	
	return m_offsets;
}
*/
