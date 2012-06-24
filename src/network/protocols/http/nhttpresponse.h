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
#ifndef NHTTPRESPONSE_H_
#define NHTTPRESPONSE_H_

#include "nhttp.h"

class NHttpResponse: public NHttp {
	public:
		enum ResponseHeaderParam {
			ACCEPT_RANGES,
			AGE,
			ETAG,
			LOCATION,
			PROXY_AUTH,
			RETRY_AFTER,
			SERVER,
			VARY,
			WWW_AUTH,
		};
		
		NHttpResponse();
		~NHttpResponse();
		
		void setAcceptRanges(const NString &value);
		void setAge(const NString &value);
		void setEtag(const NString &value);
		void setLocation(const NString &value);
		void setProxyAuth(const NString &value);
		void setRetryAfter(nint32 value);
		void setServer(const NString &value);
		void setVary(const NString &value);
		void setWWWAuth(const NString &value);
		
		NString getAcceptRanges(void) const;
		NString getAge(void) const;
		NString getEtag(void) const;
		NString getLocation(void) const;
		NString getProxyAuth(void) const;
		NString getRetryAfter(void) const;
		NString getServer(void) const;
		NString getVary(void) const;
		NString getWWWAuth(void) const;
		
		virtual NDataStream protocol(void);
		void setResponse(HttpStatus status, const NString &reason);
		
	protected: 
		void addResponseHeaderParam(ResponseHeaderParam param, 
									const NString &value);
		NString getResponseHeaderValue(ResponseHeaderParam param) const;
		void protocolResponseHeader(NDataStream *stream);
	
	private:
		NMap<ResponseHeaderParam, NString> m_response_header;
		
		// Response
		HttpStatus m_status;
		NString m_reason;
		
		
};

#endif /*NHTTPRESPONSE_H_*/
