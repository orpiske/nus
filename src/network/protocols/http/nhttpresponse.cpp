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
#include "nhttpresponse.h"

NHttpResponse::NHttpResponse(): NHttp() {
	
}


NHttpResponse::~NHttpResponse() {
	
	
}


void NHttpResponse::setResponse(HttpStatus status, const NString &reason) {
	m_status = status,
	m_reason = reason;
}


void NHttpResponse::addResponseHeaderParam(ResponseHeaderParam param, 
		const NString &value)
{
	m_response_header.insert(param, value);
}

NString NHttpResponse::getResponseHeaderValue(ResponseHeaderParam param) const {
	m_response_header.value(param);
}

void NHttpResponse::protocolResponseHeader(NDataStream *stream) {
	for (NMap<ResponseHeaderParam, NString>::const_iterator i = m_response_header.constBegin();  
			i != m_response_header.constEnd(); i++)
	{
		if (i.key() == ACCEPT_RANGES) {
			formatParam(stream, "Accept-Ranges", i.value());
			continue;
		}	
		if (i.key() == AGE) {
			formatParam(stream, "Age", i.value());
			continue;
		}
		if (i.key() == ETAG) {
			formatParam(stream, "ETag", i.value());
			continue;
		}
		if (i.key() == LOCATION) {
			formatParam(stream, "Location", i.value());
			continue;
		}
		if (i.key() == PROXY_AUTH) {
			formatParam(stream, "Proxy-Authenthicate", i.value());
			continue;
		}
		if (i.key() == RETRY_AFTER) {
			formatParam(stream, "Retry-After", i.value());
			continue;
		}
		if (i.key() == SERVER) {
			formatParam(stream, "Server", i.value());
			continue;
		}
		if (i.key() == VARY) {
			formatParam(stream, "Vary", i.value());
			continue;
		}
		if (i.key() == WWW_AUTH) {
			formatParam(stream, "WWW-Authenticate", i.value());
			continue;
		}
	}
}



void NHttpResponse::setAcceptRanges(const NString &value) {
	addResponseHeaderParam(ACCEPT_RANGES, value);
}

void NHttpResponse::setAge(const NString &value) {
	addResponseHeaderParam(AGE, value);
}

void NHttpResponse::setEtag(const NString &value) {
	addResponseHeaderParam(ETAG, value);
}

void NHttpResponse::setLocation(const NString &value) {
	addResponseHeaderParam(LOCATION, value);
}

void NHttpResponse::setProxyAuth(const NString &value) {
	addResponseHeaderParam(PROXY_AUTH, value);
}

void NHttpResponse::setRetryAfter(nint32 value) {
	addResponseHeaderParam(RETRY_AFTER, NString::number(value));
}

void NHttpResponse::setServer(const NString &value) {
	addResponseHeaderParam(SERVER, value);
}

void NHttpResponse::setVary(const NString &value) {
	addResponseHeaderParam(VARY, value);
}

void NHttpResponse::setWWWAuth(const NString &value) {
	addResponseHeaderParam(WWW_AUTH, value);
}

NString NHttpResponse::getAcceptRanges(void) const {
	return getResponseHeaderValue(ACCEPT_RANGES);
}

NString NHttpResponse::getAge(void) const {
	return getResponseHeaderValue(AGE);
}

NString NHttpResponse::getEtag(void) const {
	return getResponseHeaderValue(ETAG);
}

NString NHttpResponse::getLocation(void) const {
	return getResponseHeaderValue(LOCATION);
}

NString NHttpResponse::getProxyAuth(void) const {
	return getResponseHeaderValue(PROXY_AUTH);
}

NString NHttpResponse::getRetryAfter(void) const {
	return getResponseHeaderValue(RETRY_AFTER);
}

NString NHttpResponse::getServer(void) const {
	return getResponseHeaderValue(SERVER);
}

NString NHttpResponse::getVary(void) const {
	return getResponseHeaderValue(VARY);
}

NString NHttpResponse::getWWWAuth(void) const {
	return getResponseHeaderValue(WWW_AUTH);	
}


NDataStream NHttpResponse::protocol() {
	NDataStream ret(""); 
	
	NDebug::print() << "Protocol version = " << protocolHTTPVersion().toString();
	
	ret = protocolHTTPVersion();
	ret += NHttp::protocolGeneralHeader();
	ret += NHttp::protocolEntityHeader();
	ret += "\r\n";
	ret += m_body.toString();
	ret += "\r\n";
	
	return ret;
}
