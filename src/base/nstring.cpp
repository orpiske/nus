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
#include "nstring.h"

/**
\file nstring.cpp NString class implementation
*/

NString::NString(void)
	: m_string(new char[1]),
	m_used(0),
	m_allocated(1)
{
	set("");
}


NString::NString(const char *str)
	: m_string(new char[1]),
	m_used(0),
	m_allocated(1)
{
	set(str);	
}


NString::NString(const NString &str)
	: m_string(new char[1]),
	m_used(0),
	m_allocated(1)
{
	set(str);
}

NString::~NString(void) {
	delete[] m_string;
	
}

bool NString::needsMemory(nuint32 bytes) {
	if (bytes >= m_allocated) {
		return true;
	}

	if (bytes >= (m_allocated - m_used)) {
		return true;
	}

	return false;
}


nuint32 NString::calculateBlocks(nuint32 bytes) {
	nuint32 blocks = 0;
	nuint32 mod = 0;

	blocks = bytes / ALLOC_SIZE;
	mod = bytes % ALLOC_SIZE;
	if (blocks == 0) {
		blocks = 1;
	}

	if (mod > 0) {
		blocks++;
	}

	return blocks;
}


inline void NString::memcopy(char *dest) {
	assert(dest);

	if (m_string) {
		memcpy(dest, m_string, m_used);
		//printf("[DEBUG] Deallocated: %i bytes at %p (%s)\n", m_allocated, 
		//	m_string, m_string);
		delete[] m_string;
	}
	
	m_string = dest;
}


void NString::realloc(nuint32 bytes) {
	nuint32 blocks = 0;
	
	char *data_ptr = NULL;

	if (!needsMemory(bytes)) {
		return;
	}

	blocks = calculateBlocks(bytes + m_used);
	m_allocated = blocks * ALLOC_SIZE;
	
	data_ptr = new char[m_allocated];
	//printf("[DEBUG] Allocated: %i bytes in %i blocks at %p (%s)\n", 
	//	m_allocated, blocks, data_ptr, m_string);
	memset(data_ptr, 0, m_allocated);
	memcopy(data_ptr);
}

inline nuint32 NString::freeBytes(void) const {
	return m_allocated - m_used;
}


NString &NString::set(const char *str) {
	unsigned int len = 0;
		
	if (str) {
		len = strlen(str);
		//printf("[DEBUG] Input len is %i. Allocated is %i\n", len, m_allocated);
		if (len == 0) {
			memset(m_string, 0, m_allocated);
			m_used = 0;
		}
		else {
			if (m_allocated <= len) {
				realloc(len + 1);
			}
			
			memset(m_string, 0, m_allocated);
			memcpy(m_string, str, len);
			m_used = len;
		}
	}
	else {
		len = 1;
		if (m_allocated <= len) {
			realloc(len);
		}
		memset(m_string, 0, m_allocated);
		m_used = 0;
	}
	
	return *this;
}


NString &NString::set(const NString &str) {
	return set(str.toChar());
}

const char *NString::toChar() const {
	return m_string;
}


NString NString::number(int num) {
	char tmpBuff[1024];
	
	memset(tmpBuff, 0, sizeof(tmpBuff));
#ifdef _MSC_VER
	_snprintf_s(tmpBuff, sizeof(tmpBuff), "%i", num);
#else
	snprintf(tmpBuff, sizeof(tmpBuff), "%i", num);
#endif
	
	return NString(tmpBuff);
}


NString NString::number(nint64 num) {
	char tmpBuff[1024];
	
	memset(tmpBuff, 0, sizeof(tmpBuff));
#ifdef _MSC_VER
	_snprintf_s(tmpBuff, sizeof(tmpBuff), "%lli", num);
#else
	snprintf(tmpBuff, sizeof(tmpBuff), "%lli", num);
#endif // _MSC_VER
	
	return NString(tmpBuff);
}


unsigned int NString::length(void) const {
	return m_used;
}


bool NString::isNull() const {
	if (!m_string || this->length() == 0) {
		return true;
	}
	
	return false;
}


NString &NString::append(const char *str, nuint32 bytes) {
	assert(str);
	
	if (freeBytes() < bytes) {
		realloc(bytes);
	}

	strncat(m_string, str, bytes);
	m_used += bytes;
	m_string[m_used] = 0;
	return *this;
}

inline NString &NString::append(const char *str) {
	assert(str);
	return append(str, strlen(str));
}


NString &NString::append(const NString &str) {
	append(str.toChar());
	return *this;
}


NString &NString::append(char c) {
	return append(&c, 2); // 2 -> for the char and the NULL terminator
}

NString &NString::insert(nuint32 pos, nuint32 size, const NString str) {
	nuint32 bytes = 0;
#if defined(_MSC_VER)
	char *tmp = new char[m_used + 1];

	memset(tmp, 0, m_used + 1);
#else
	char tmp[m_used];
#endif // defined(_MSC_VER)
	
	if (pos > m_used) {
		pos = m_used;
		
	}	
	strcpy(tmp, m_string);
	bytes = this->length() + size + 1;
	if (freeBytes() < bytes) {
		realloc(bytes);
	}
	
	memset(m_string, 0, sizeof(m_allocated));
	strncpy(m_string, tmp, pos);
	strncat(m_string, str.toChar(), size);
	strncat(m_string, tmp + pos, m_used);
	m_used = bytes;

#if defined(_MSC_VER)
	delete[] tmp; 
#endif // defined(_MSC_VER)
	
	return *this;
}


NString &NString::insert(nuint32 pos, const NString str) {
	return insert(pos, str.length(), str);	
}


bool NString::compare(nuint32 pos, nuint32 size, const NString &str) const {
	if (isNull() && str.isNull()) {
		return true;
	}
	else {
		if (isNull() && (str == "")) {
			return true;
		}
	}

	if (size == 0) {
		return false;
	}

	if (pos > this->length() || (pos + size) > this->length() 
		|| size > str.length()) 
	{
		return false;
	}
	
	if (strncmp(m_string + pos, str.toChar(), size) == 0) {
		return true;
	}
	
	return false;
}

bool NString::compare(nuint32 pos, const NString &str) const {
	return compare(pos, this->length(), str);
	
}

bool NString::compare(nuint32 pos, nuint32 size, const NString &str, 
				nuint32 str_pos) const
{
	if (pos > this->length() || (pos + size) > this->length() || 
			str_pos < str.length()) 
	{
		return false;
	}
	
	if (strncmp(m_string + pos, str.toChar() + str_pos, size) == 0) {
		return true;
	}
		
	return true;
}

NString NString::substr(nuint32 pos, nuint32 size) const { 
	NString ret;

#if defined(_MSC_VER)
	char *tmp = new char[m_used + 1];

	memset(tmp, 0, m_used + 1);
#else
	char tmp[m_used + 1];

	memset(tmp, 0, sizeof(tmp));
#endif // defined(_MSC_VER)
	
	if (pos > this->length() || (pos + size) > this->length() || size == 0) {
		return ret;
	}

	memcpy(tmp, m_string + pos, size);
	ret = tmp;
#if defined(_MSC_VER)
	delete[] tmp;
#endif // defined(_MSC_VER)
	
	return ret;
}


nint32 NString::find(const NString &str, nuint32 pos, nuint32 ocur) const { 
	nint32 ret = 0;
	for (nuint32 i = 0; i < ocur; i++) { 
		ret = find(str, pos);
		if (ret == NString::NOT_FOUND) { 
			return NString::NOT_FOUND;
		}
	}

	return ret;
}


nint32 NString::find(const NString &str, nuint32 pos) const { 
	for (nuint32 i = pos; i < m_used; i++) {
		if (this->operator[](i) == str[0]) {
			if (compare(i, str.length(), str)) { 
				return i;
			}
		}
	}

	return NString::NOT_FOUND;

}


nint32 NString::find(const NString &str) const { 
	return find(str, 0);
}


NString &NString::replace_first(const NString &src, const NString &dest) { 
	NString tmp;
	nint32 pos = NString::NOT_FOUND;

	pos = find(src);
	tmp = "";
	if (pos != NString::NOT_FOUND) {
		//printf("Found in = %i\n", pos);
		tmp += substr(0, pos);
		//printf("TMP = %s\n", tmp.toChar());
		tmp += dest;
		//printf("E) TMP = %s\n", tmp.toChar());
		tmp += substr(pos + src.length(), length() - (pos + src.length()));

		set(tmp);
	}
	
	//printf("F) TMP = %s\n", tmp.toChar());
	return *this;
}


NString &NString::replace(const NString &src, const NString &dest) {
	NString tmp = *this;
	NString last;
	
	do { 
		tmp.replace_first(src, dest); 
		// printf("1) TMP = %s\n", tmp.toChar());
		if (tmp == *this) { 
			break;
		}
		set(tmp);
	} while (true);
	
	return *this;
}


NString &NString::replace(const NString &src, const NString &dest, 
			nuint32 ocur) 
{
	NString tmp = *this;
	NString last;

	nuint32 count = 0;
	do { 
		tmp.replace_first(src, dest); 
		// printf("1) TMP = %s\n", tmp.toChar());
		if (tmp == *this) { 
			break;
		}
		
		count++; 
		set(tmp);
	} while (count < ocur);

	return *this;
}


NList<NString> NString::split(const NString &str) {
	nint32 pos = 0;
	nint32 last = 0;
	NString tmp;
	NList<NString> ret;
	
	do {
		last = find(str, pos);
		if (last > NString::NOT_FOUND) {
			tmp = substr(pos, last - pos);
			ret.append(tmp);
			//printf("[DEBUG] Adding %s (from %i:%i)\n", 
			//	tmp.toChar(), pos, last);
		}
		else {
			if (pos == 0 && last == NString::NOT_FOUND) { 
				tmp = substr(pos, length() - pos);
			}
			else {
				tmp = substr(pos, length() - pos);
			}
			ret.append(tmp);
			//printf("[DEBUG] Adding last %s (from %i:%i|%i)\n", 
			//	tmp.toChar(), pos, last, length());
			break;
		}
		pos = last + 1;
	} while (pos != NString::NOT_FOUND);

	return ret;
}


NString NString::rtrim() {
	nint32 i = 0;
	NString tmp(*this);

	// tmp.set(*this);

	for (i = length() - 1; i > 0; i--) {
		if (isspace(tmp[i]) || iscntrl(tmp[i])) {
			if (tmp[i] == '\0') {
				break;
			}

			printf("About to remove char %c(%i) at position %i\n", m_string[i], m_string[i], i);
		}
		else {

			break;
		}
	}

	return tmp.substr(0, (i + 1));
}


NString NString::ltrim() {
	nint32 position = 0;
	NString tmp;

	for (nuint32 i = 0; i < length() - 1; i++) {
		if (!isspace(m_string[i]) && !iscntrl(m_string[i])) {
			if (m_string[i] == 0) {
				break;
			}
			position = i;
			break;
		}
	}

	if (position > 0) {
		return substr(position, length() - position);
	}

	return *this;
}


NString NString::trim() {
	return ltrim().rtrim();
}


NString NString::operator+(const char *str) {
	return append(str);
}


NString NString::operator+(char c) {
	return append(c);
}


NString NString::operator+(const NString &str) {
	return append(str);
}


NString &NString::operator+=(const char *str) {
	return append(str);
}


NString &NString::operator+=(const NString &str) {
	return append(str);
}


NString &NString::operator+=(char c) {
	return append(c);
}


char NString::operator[](unsigned int index) const {
	return m_string[index];
}


bool NString::operator==(const NString &str) const {
	return compare(0, str);
}


bool NString::operator!=(const NString &str) const {
	return (!compare(0, str));
}



bool NString::operator>(const NString &str) const {
	int res = 0;
	
	res = strcmp(m_string, str.toChar()); 
	if (res <= 0) {
		return false;
	}
	
	return true;
}


bool NString::operator<(const NString &str) const {
	int res = 0;
		
	res = strcmp(m_string, str.toChar()); 
	if (res >= 0) {
		return false;
	}
	
	return true;
}


bool NString::operator>=(const NString &str) const {
	int res = 0;
		
	res = strcmp(m_string, str.toChar()); 
	if (res < 0) {
		return false;
	}
	
	return true;
}


bool NString::operator<=(const NString &str) const {
	int res = 0;
		
	res = strcmp(m_string, str.toChar()); 
	if (res > 0) {
		return false;
	}
	
	return true;
}


NString &NString::operator=(const NString &str) {
	set(str);
	
	return *this;
}


NString &NString::arg(const char *fmt, ...) {
	va_list ap;
	char *ret = NULL;
	
	assert(fmt);
	set(fmt);
	
	va_start(ap, fmt);
	free(ret);
	
	n_vasprintf(fmt, ap, ret);
	if (ret) {	
		set(ret);
		free(ret);
	}
	va_end(ap);
	
	return *this;
}
