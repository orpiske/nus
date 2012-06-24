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
#include "ndatastream.h"

/**
\file ndatastream.cpp NDataStream implementation
*/

NDataStream::NDataStream(void)
	: m_bo(N_BIG_ENDIAN),
	m_data(NULL),
	m_used(0),
	m_allocated(0)
{
	realloc(ALLOC_SIZE);
	set("");
}

NDataStream::NDataStream(const NDataStream &stream)
	: m_bo(N_BIG_ENDIAN),
	m_data(NULL),
	m_used(0),
	m_allocated(0)
{
	set(stream.toString());
}


NDataStream::NDataStream(const char *str)
	: m_bo(N_BIG_ENDIAN),
	m_data(NULL),
	m_used(0),
	m_allocated(0)
{
	set(str);
}

NDataStream::~NDataStream(void) {
	delete[] static_cast<char *>(m_data);
}

inline bool NDataStream::needsMemory(nuint32 bytes) {
	if (bytes > m_allocated) {
		return true;
	}

	if (bytes > (m_allocated - m_used)) {
		return true;
	}

	return false;
}

nuint32 NDataStream::calculateBlocks(nuint32 bytes) {
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


void NDataStream::memcopy(void *dest) {
	assert(dest);

	if (m_data) {
		memcpy(dest, m_data, m_used);
		delete[] static_cast<char *>(m_data);
	}

	m_data = dest;
}


void NDataStream::realloc(nuint32 bytes) {
	nuint32 blocks = 0;
	nuint32 streamSize = 0;
	void *data_ptr = NULL;

	if (!needsMemory(bytes)) {
		return;
	}

	blocks = calculateBlocks(bytes + m_used);
	streamSize = blocks * ALLOC_SIZE;

	data_ptr = new char[streamSize];
	memcopy(data_ptr);
	m_allocated = streamSize;
}


inline nuint32 NDataStream::freeBytes(void) const {
	return m_allocated - m_used;
}

void NDataStream::setByteOrder(NDataStream::ByteOrder bo) {
	m_bo = bo;
}

NDataStream::ByteOrder NDataStream::getByteOrder(void) const {
	return m_bo;
}


NDataStream &NDataStream::set(const char *str) {
	unsigned int len = 0;

	if (str) {
		len = strlen(str);

		//printf("Len = %i | Allocated = %i\n", len, m_allocated);
		if (m_allocated <= len) {
			realloc(len);
		}
		memcpy(m_data, str, len);
		m_used = len;
	}
	else {
		memset(m_data, 0, m_allocated);
		m_used = 0;
	}

	return *this;
}


NDataStream &NDataStream::set(const NString &str) {
	return set(str.toChar());
}


NDataStream &NDataStream::set(const void *src, nuint32 bytes) {
	assert(src);

	if (m_allocated < bytes) {
		realloc(bytes);
	}
	memcpy(m_data, src, bytes);
	m_used = bytes;

	return *this;
}

template<typename T>
NDataStream &NDataStream::set(T val) {
	unsigned char c[sizeof(T)];
	nuint32 i = 0;
	int shift = 0;
	const int num_bits = 8;

	if (getByteOrder() == N_LITTLE_ENDIAN) {
		do {
			c[i] = val >> shift;
			shift += num_bits;
			i++;
		} while (i < sizeof(T));
	}
	else {
		shift = (sizeof(T) * num_bits) - num_bits;
		do {
			c[i] = val >> shift;
			shift -= num_bits;
			i++;
		} while (i < sizeof(T));
	}

	memset(m_data, 0, m_allocated);
	memcpy(m_data, c, sizeof(c));
	m_used = sizeof(T);
	return *this;
}


NDataStream &NDataStream::set(const nint16 val) {
	return set<nint16>(val);
}


NDataStream &NDataStream::set(const nuint16 val) {
	return set<nuint16>(val);
}



NDataStream &NDataStream::set(const nint32 val) {
	return set<nint32>(val);
}


NDataStream &NDataStream::set(const nuint32 val) {
	return set<nuint32>(val);
}


NDataStream &NDataStream::set(const nint64 val) {
	nint32 lowerBase = 0;
	nint32 higherBase = 0;
	const int num_bits = 8;

	lowerBase |= val;
	higherBase |= val >> (sizeof(nint64) * num_bits) / 2;

	set<nint32>(lowerBase);
	return append<nint32>(higherBase);
}


NDataStream &NDataStream::set(const nuint64 val) {
	nuint32 lowerBase = 0;
	nuint32 higherBase = 0;
	const int num_bits = 8;

	lowerBase |= val;
	higherBase |= val >> (sizeof(nint64) * num_bits) / 2;

	set<nint32>(lowerBase);
	return append<nuint32>(higherBase);
}


NDataStream &NDataStream::append(const void *src, nuint32 bytes) {

	if (src) {
		if (freeBytes() < bytes) {
			realloc(bytes);
		}

		memcat(m_data, m_used, src, bytes);
		m_used += bytes;
	}

	return *this;
}


NDataStream &NDataStream::append(const char *str) {
	assert(str);

	return append(str, strlen(str));
}


NDataStream &NDataStream::append(const NString &str) {
	return append(str.toChar());
}


template<typename T>
NDataStream &NDataStream::append(T val) {
	unsigned char c[sizeof(T)];
	nuint32 i = 0;
	int shift = 0;
	const int num_bits = 8;

	if (getByteOrder() == N_LITTLE_ENDIAN) {
		do {
			c[i] = val >> shift;
			shift += num_bits;
			i++;
		} while (i < sizeof(T));
	}
	else {
		shift = (sizeof(T) * num_bits) - num_bits;
		do {
			c[i] = val >> shift;
			shift -= num_bits;
			i++;
		} while (i < sizeof(T));
	}

	memcat(m_data, m_used, c, sizeof(c));
	m_used += sizeof(T);

	return *this;
}

NDataStream &NDataStream::append(const nint16 val) {
	return append<nint16>(val);
}


NDataStream &NDataStream::append(const nuint16 val) {
	return append<nuint16>(val);
}


NDataStream &NDataStream::append(const nint32 val) {
	return append<nint32>(val);
}


NDataStream &NDataStream::append(const nuint32 val) {
	return append<nuint32>(val);
}


NDataStream &NDataStream::append(const nint64 val) {
	nint32 lowerBase = 0;
	nint32 higherBase = 0;
	const int num_bits = 8;

	lowerBase |= val;
	higherBase |= val >> (sizeof(nint64) * num_bits) / 2;

	append<nint32>(lowerBase);
	return append<nint32>(higherBase);
}


NDataStream &NDataStream::append(const nuint64 val) {
	nuint32 lowerBase = 0;
	nuint32 higherBase = 0;
	const int num_bits = 8;

	lowerBase |= val;
	higherBase |= val >> (sizeof(nint64) * num_bits) / 2;

	append<nuint32>(lowerBase);
	return append<nuint32>(higherBase);
}

bool NDataStream::withinLimits(nuint32 start, nuint32 bytes) const {
	if (start > m_used) {
		return false;
	}

	if (bytes > m_used) {
		return false;
	}

	if ((start + bytes) > m_used) {
		return false;
	}

	return true;
}


NString NDataStream::toString(nuint32 start, nuint32 bytes) const {
	NString ret;
	char *tmp = NULL;

	if (!withinLimits(start, bytes)) {
		throw NException(N_OUTOFBOUNDS, NException::BASE,
						NException::EX_OUT_OF_BOUNDS);
	}
	tmp = new char[bytes + 1];

	memset(tmp, 0, bytes + 1);
	memcpy(tmp, static_cast<char *>(m_data) + start, bytes);
	if (tmp[bytes] != '\0') {
		tmp[bytes] = '\0';
	}

	ret.set(tmp);
	delete[] tmp;

	return ret;
}


NString NDataStream::toString(nuint32 bytes) const {
	return toString(0, bytes);
}

NString NDataStream::toString(void) const {
	return toString(m_used);
}


unsigned char NDataStream::toChar(void) const {
	return toChar(0);
}

unsigned char NDataStream::toChar(nuint32 pos) const {
	return static_cast<char *>(m_data)[pos];
}

template<typename T>
T NDataStream::to(void) const {
	T ret = 0;
	int pos = 0;
	const int num_bits = 8;

	if (getByteOrder() == N_LITTLE_ENDIAN) {
		pos = (sizeof(T) - 1);
		do {
			ret |= toChar(pos);
			if (pos != 0) {
				ret <<= num_bits;
			}
			pos--;
		}
		while (pos >= 0);
	}
	else {
		pos = 0;
		do {
			ret |= toChar(pos);

			if (pos != (sizeof(T) - 1)) {
				ret <<= num_bits;
			}
			pos++;
		} while (pos != sizeof(T));
	}

	return ret;
}


nint16 NDataStream::toInt16(void) const {
	return to<nint16>();

}



nint32 NDataStream::toInt32(void) const {
	return to<nint32>();
}



nint64 NDataStream::toInt64(void) const {
	return to<nint32>();
}

bool NDataStream::isNull(void) const {
	if (m_used == 0) {
		return true;
	}

	return false;
}

nuint32 NDataStream::size(void) const {
	return m_used;
}


const void *NDataStream::data(void) const {
	return m_data;
}


bool NDataStream::operator==(const NDataStream &rhs) const {
	if (size() != rhs.size()) {
		return false;
	}

	if (memcmp(m_data, rhs.m_data, size()) == 0) {
		return true;
	}

	return false;
}

bool NDataStream::operator!=(const NDataStream &rhs) const {
	if (size() != rhs.size()) {
		return true;
	}

	if (memcmp(m_data, rhs.m_data, size()) == 0) {
		return false;
	}

	return true;
}

NDataStream &NDataStream::operator=(const char *str) {
	return set(str);
}

NDataStream &NDataStream::operator=(const NString &str) {
	return set(str);
}

NDataStream &NDataStream::operator=(const NDataStream &str) {
	return set(str.toString());
}

NDataStream &NDataStream::operator=(const nint16 val) {
	return set(val);
}

NDataStream &NDataStream::operator=(const nuint16 val) {
	return set(val);
}

NDataStream &NDataStream::operator=(const nint32 val) {
	return set(val);
}

NDataStream &NDataStream::operator=(const nuint32 val) {
	return set(val);
}

NDataStream &NDataStream::operator=(const nint64 val) {
	return set(val);
}

NDataStream &NDataStream::operator=(const nuint64 val) {
	return set(val);
}

NDataStream &NDataStream::operator+=(const char *str) {
	return append(str);
}

NDataStream &NDataStream::operator+=(const NString &str) {
	return append(str);
}

NDataStream &NDataStream::operator+=(const NDataStream &str) {
	return append(str.toString());
}

NDataStream &NDataStream::operator+=(const nint16 val) {
	return append(val);
}

NDataStream &NDataStream::operator+=(const nuint16 val) {
	return append(val);
}

NDataStream &NDataStream::operator+=(const nint32 val) {
	return append(val);
}

NDataStream &NDataStream::operator+=(const nuint32 val) {
	return append(val);
}

NDataStream &NDataStream::operator+=(const nint64 val) {
	return append(val);
}

NDataStream &NDataStream::operator+=(const nuint64 val) {
	return append(val);
}

NDataStream NDataStream::operator+(const char *str) {
	return append(str);
}

NDataStream NDataStream::operator+(const NString &str) {
	return append(str);
}

NDataStream NDataStream::operator+(const NDataStream &str) {
	return append(str.toString());
}

NDataStream NDataStream::operator+(const nint16 val) {
	return append(val);
}

NDataStream NDataStream::operator+(const nuint16 val) {
	return append(val);
}

NDataStream NDataStream::operator+(const nint32 val) {
	return append(val);
}

NDataStream NDataStream::operator+(const nuint32 val) {
	return append(val);
}

NDataStream NDataStream::operator+(const nint64 val) {
	return append(val);
}

NDataStream NDataStream::operator+(const nuint64 val) {
	return append(val);
}

unsigned char NDataStream::operator[](nuint32 pos) {
	if (pos >= m_used) {
		return 0;
	}

	return static_cast<char *>(m_data)[pos];
}
