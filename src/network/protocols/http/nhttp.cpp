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
#include "nhttp.h"

NHttp::NHttp(void)
	: NObject(),
	m_major(1),
	m_minor(1),
	m_general_header(),
	m_entity_header(),
	m_method(HEAD),
	m_uri(""),
	m_body()
	
{

}

NHttp::~NHttp(void) {
	
}

void NHttp::addGeneralHeaderParam(GeneralHeaderParam param, 
		const NString &value)
{
	m_general_header.insert(param, value);
}

NString NHttp::getGeneralHeaderValue(GeneralHeaderParam param) const {
	return m_general_header.value(param);
}


void NHttp::addEntityHeaderParam(EntityHeaderParam param, const NString &value) {
	m_entity_header.insert(param, value);
}

NString NHttp::getEntityHeaderValue(EntityHeaderParam param) const {
	return m_entity_header.value(param);
}

void NHttp::setEntityBody(const NDataStream &data) {
	m_body = data;
}

void NHttp::formatParam(NDataStream *stream, const NString &name, 
		const NString &value)
{
	NString tmp = name;
	
	tmp += ": ";
	tmp += value;
	tmp += "\r\n";
	
	stream->append(tmp);
}

NDataStream NHttp::protocolGeneralHeader(void) {
	NDataStream stream;
	
	for (NMap<GeneralHeaderParam, NString>::const_iterator i = m_general_header.constBegin();  
		i != m_general_header.constEnd(); i++)
	{
		if (i.key() == CACHE_CONTROL) {
			formatParam(&stream, "Cache-Control", i.value());
			continue;
		}
		if (i.key() == CONNECTION) {
			formatParam(&stream, "Connection", i.value());
			continue;
		}
		if (i.key() == DATE) {
			formatParam(&stream, "Connection", i.value());
			continue;
		}
		if (i.key() == PRAGMA) {
			formatParam(&stream, "Pragma", i.value());
			continue;
		}
		if (i.key() == TRAILER) {
			formatParam(&stream, "Trailer", i.value());
			continue;
		}
		if (i.key() == TRANSFER_ENCODING) {
			formatParam(&stream, "Transfer-Encoding", i.value());
			continue;
		}
		if (i.key() == UPGRADE) {
			formatParam(&stream, "Upgrade", i.value());
			continue;
		}
		if (i.key() == VIA) {
			formatParam(&stream, "Via", i.value());
			continue;
		}
		if (i.key() == WARNING) {
			formatParam(&stream, "Warning", i.value());
			continue;
		}
	}
	
	return stream;
}

NDataStream NHttp::protocolHTTPVersion(void) {
	NDataStream ret;
	NString tmp;
	
	tmp = "HTTP/";
	tmp += NString::number(m_major);
	tmp += ".";
	tmp += NString::number(m_minor);
	tmp += "\r\n";
	
	NDebug::print() << tmp;
	ret.set(tmp);
	
	return ret;
}

NDataStream NHttp::protocolEntityHeader(void) {
	NDataStream stream;
	
	for (NMap<EntityHeaderParam, NString>::const_iterator i = m_entity_header.constBegin();  
			i != m_entity_header.constEnd(); i++)
	{
		if (i.key() == ALLOW) {
			formatParam(&stream, "Allow", i.value());
			continue;
		}
		if (i.key() == CONTENT_ENCODING) {
			formatParam(&stream, "Content-Encoding", i.value());
			continue;
		}
		if (i.key() == CONTENT_LANGUAGE) {
			formatParam(&stream, "Content-Language", i.value());
			continue;
		}
		if (i.key() == CONTENT_LENGTH) {
			formatParam(&stream, "Content-Length", i.value());
			continue;
		}
		if (i.key() == CONTENT_LOCATION) {
			formatParam(&stream, "Content-Location", i.value());
			continue;
		}
		if (i.key() == CONTENT_MD5) {
			formatParam(&stream, "Content-MD5", i.value());
			continue;
		}
		if (i.key() == CONTENT_RANGE) {
			formatParam(&stream, "Content-Range", i.value());
			continue;
		}
		if (i.key() == CONTENT_TYPE) {
			formatParam(&stream, "Content-Type", i.value());
			continue;
		}
		if (i.key() == EXPIRES) {
			formatParam(&stream, "Expires", i.value());
			continue;
		}
		if (i.key() == LAST_MODIFIED) {
			formatParam(&stream, "Last-Modified", i.value());
			continue;
		}
	}
	
	return stream;
}

void NHttp::setHttpVersion(nuint16 major, nuint16 minor) {
	m_major = major;
	m_minor = minor;
}

void NHttp::setCacheControl(const NString &value) {
	addGeneralHeaderParam(CACHE_CONTROL, value);
}

void NHttp::setConnection(const NString &value) {
	addGeneralHeaderParam(CONNECTION, value);
}

void NHttp::setDate(const NDateTime &dateTime) {
	addGeneralHeaderParam(DATE, dateTime.now());
}

void NHttp::setPragma(const NString &value) {
	addGeneralHeaderParam(PRAGMA, value);
}

void NHttp::setTrailer(const NString &value) {
	addGeneralHeaderParam(TRAILER, value);
}

void NHttp::setTransferEncoding(const NString &value) {
	addGeneralHeaderParam(TRANSFER_ENCODING, value);
}

void NHttp::setUpgrade(const NString &value) {
	addGeneralHeaderParam(UPGRADE, value);
}

void NHttp::setVia(const NString &value) {
	addGeneralHeaderParam(VIA, value);
}

void NHttp::setWarning(const NString &value) {
	addGeneralHeaderParam(WARNING, value);
}

NString NHttp::getCacheControl(void) const {
	return getGeneralHeaderValue(CACHE_CONTROL);
}

NString NHttp::getConnection(void) const {
	return getGeneralHeaderValue(CONNECTION);
}

NString NHttp::getDate(void) const {
	return getGeneralHeaderValue(DATE);
}

NString NHttp::getPragma(void) const {
	return getGeneralHeaderValue(PRAGMA);
}

NString NHttp::getTrailer(void) const {
	return getGeneralHeaderValue(TRAILER);
}

NString NHttp::getTransferEncoding(void) const {
	return getGeneralHeaderValue(TRANSFER_ENCODING);
}

NString NHttp::getUpgrade(void) const {
	return getGeneralHeaderValue(UPGRADE);
}

NString NHttp::getVia(void) const {
	return getGeneralHeaderValue(VIA);
}

NString NHttp::getWarning(void) const {
	return getGeneralHeaderValue(WARNING);
}


void NHttp::setAllow(const NString &value) {
	addEntityHeaderParam(ALLOW, value);
}

void NHttp::setContentEncoding(const NString &value) {
	addEntityHeaderParam(CONTENT_ENCODING, value);
}

void NHttp::setContentLanguage(const NString &value) {
	addEntityHeaderParam(CONTENT_LANGUAGE, value);
}

void NHttp::setContentLength(nint64 size) {
	addEntityHeaderParam(CONTENT_LENGTH, NString::number(size));
}

void NHttp::setContentLocation(const NString &value) {
	addEntityHeaderParam(CONTENT_LOCATION, value);
}

void NHttp::setContentMD5(const NString &value) {
	addEntityHeaderParam(CONTENT_MD5, value);
}

void NHttp::setContentRange(const NString &value) {
	addEntityHeaderParam(CONTENT_RANGE, value);
}

void NHttp::setContentType(const NString &value) {
	addEntityHeaderParam(CONTENT_TYPE, value);
}

void NHttp::setExpires(const NDateTime &dateTime) {
	addEntityHeaderParam(EXPIRES, dateTime.now());
}

void NHttp::setLastModified(const NDateTime &dateTime) {
	addEntityHeaderParam(LAST_MODIFIED, dateTime.now());
}

NString NHttp::getAllow(void) const {
	return getEntityHeaderValue(ALLOW);
}

NString NHttp::getContentEncoding(void) const {
	return getEntityHeaderValue(CONTENT_ENCODING);
}

NString NHttp::getContentLanguage(void) const {
	return getEntityHeaderValue(CONTENT_LANGUAGE);
}

NString NHttp::getContentLength(void) const {
	return getEntityHeaderValue(CONTENT_LENGTH);
}

NString NHttp::getContentLocation(void) const {
	return getEntityHeaderValue(CONTENT_LOCATION);
}

NString NHttp::getContentMD5(void) const {
	return getEntityHeaderValue(CONTENT_MD5);
}

NString NHttp::getContentRange(void) const {
	return getEntityHeaderValue(CONTENT_RANGE);
}

NString NHttp::getContentType(void) const {
	return getEntityHeaderValue(CONTENT_TYPE);
}

NString NHttp::getExpires(void) const {
	return getEntityHeaderValue(EXPIRES);
}

NString NHttp::getLastModified(void) const {
	return getEntityHeaderValue(LAST_MODIFIED);
}
