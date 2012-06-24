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
#include "nabstracthash.h"

/**
\file nabstracthash.cpp NAbstractHash class implementation
*/

NAbstractHash::NAbstractHash(void)
		: m_digest_context(),
		m_message_digest(NULL),
		m_total(0),
		m_hash_buffer_size(0)
 {
 
 }

NAbstractHash::~NAbstractHash(void) {}

void NAbstractHash::init(const NString &hash_name) {
	OpenSSL_add_all_digests();
	
	assert(hash_name.toChar());
	
	m_message_digest = EVP_get_digestbyname(hash_name.toChar());
	if (!m_message_digest) {
		throw NException(NSTR("Unknown message digest: ") + hash_name, 
				     NException::SECURITY);
	}
	
	EVP_MD_CTX_init(&m_digest_context);
	EVP_DigestInit_ex(&m_digest_context, m_message_digest, NULL);	
}


int NAbstractHash::update(const void *data, int bytes) {
	EVP_DigestUpdate(&m_digest_context, data, bytes);
	m_total += bytes;
	
	return m_total;
}


NString NAbstractHash::cleanup(void) {
	char *tmp = p_cleanup();
	NString ret = tmp;
	
	delete[] tmp;
	return ret;
}

char *NAbstractHash::p_cleanup(void) {
	unsigned char md_value[EVP_MAX_MD_SIZE];
	unsigned int md_len;
	char *out_hash = NULL;
		
	assert(m_hash_buffer_size);
	
	memset(md_value, 0, sizeof(md_value));
	EVP_DigestFinal_ex(&m_digest_context, md_value, &md_len);
	EVP_MD_CTX_cleanup(&m_digest_context);
	
	try {
		out_hash = new char[m_hash_buffer_size];
		memset(out_hash, 0, m_hash_buffer_size);
	}
	catch (std::bad_alloc &) {
		throw NException(N_ENOMEM, NException::SECURITY);
	}
	
	
	for(unsigned int i = 0; i < md_len; i++) {
		char tmp[3];
		memset(tmp, 0, sizeof(tmp));

#if !defined(_MSC_VER)
		snprintf(tmp, sizeof(tmp), "%02x", (md_value[i] & 0x000000FF));
#else
		_snprintf_s(tmp, sizeof(tmp), "%02x", (md_value[i] & 0x000000FF));
#endif 
		strcat(out_hash, tmp);
	}
	
	return out_hash;
}


bool NAbstractHash::match(const NString &str, const NString &hash) {
	if (calculate(str).getValue() == hash) {
		return true;
	}
	
	return false;
}


bool NAbstractHash::match(const NString &str, const NHash &hash) {
	if (calculate(str) == hash) {
		return true;
	}
	
	return false;
}

bool NAbstractHash::match(NFile *file, const NString &hash) {
	assert(file);
	
	if (calculateFile(file).getValue() == hash) {
		return true;
	}
	
	return false;
}


bool NAbstractHash::match(NFile *file, const NHash &hash) {
	assert(file);
	
	if (calculateFile(file) == hash) {
		return true;
	}
	
	return false;
}


void NAbstractHash::setHashBufferSize(int size) {
	m_hash_buffer_size = size;
}


int NAbstractHash::getHashBufferSize(void) const {
	return m_hash_buffer_size;
}

