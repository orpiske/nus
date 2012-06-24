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
#ifndef NHTTP_H_
#define NHTTP_H_

#include "ndefs.h"
#include "nobject.h"
#include "ndatastream.h"
#include "ndatetime.h"
#include "nmap.h"
#include "nresourcelocator.h"
#include "nhttpstatus.h"

class NHttp: public NObject {
	public:		
		enum GeneralHeaderParam {
			CACHE_CONTROL,
			CONNECTION,
			DATE,
			PRAGMA,
			TRAILER,
			TRANSFER_ENCODING,
			UPGRADE,
			VIA,
			WARNING,
		};
			
		enum Method {
			OPTIONS,
			GET,
			HEAD,
			POST,
			PUT,
			DELETE,
			TRACE,
			CONNECT
		};
		
		enum EntityHeaderParam {
			ALLOW,
			CONTENT_ENCODING,
			CONTENT_LANGUAGE,
			CONTENT_LENGTH,
			CONTENT_LOCATION,
			CONTENT_MD5,
			CONTENT_RANGE,
			CONTENT_TYPE,
			EXPIRES,
			LAST_MODIFIED
		};
		
		void setCacheControl(const NString &value);
		void setConnection(const NString &value);
		void setDate(const NDateTime &dateTime);
		void setPragma(const NString &value);
		void setTrailer(const NString &value);
		void setTransferEncoding(const NString &value);
		void setUpgrade(const NString &value);
		void setVia(const NString &value);
		void setWarning(const NString &value);

		NString getCacheControl(void) const;
		NString getConnection(void) const;
		NString getDate(void) const;
		NString getPragma(void) const;
		NString getTrailer(void) const;
		NString getTransferEncoding(void) const;
		NString getUpgrade(void) const;
		NString getVia(void) const;
		NString getWarning(void) const;
		
		void setAllow(const NString &value);
		void setContentEncoding(const NString &value);
		void setContentLanguage(const NString &value);
		void setContentLength(nint64 size);
		void setContentLocation(const NString &value);
		void setContentMD5(const NString &value);
		void setContentRange(const NString &value);
		void setContentType(const NString &value);
		void setExpires(const NDateTime &dateTime);
		void setLastModified(const NDateTime &dateTime);
		
		NString getAllow(void) const;
		NString getContentEncoding(void) const;
		NString getContentLanguage(void) const;
		NString getContentLength(void) const;
		NString getContentLocation(void) const;
		NString getContentMD5(void) const;
		NString getContentRange(void) const;
		NString getContentType(void) const;
		NString getExpires(void) const;
		NString getLastModified(void) const;
		
		void setHttpVersion(nuint16 major, nuint16 minor);
		nuint16 getMajorVersion(void) const;
		nuint16 getMinorVersio(void) const;
				
		void setEntityBody(const NDataStream &data);
		virtual NDataStream protocol(void) = 0;
		
	protected:
		nuint16 m_major;
		nuint16 m_minor; 
		
		NHttp(void);
		~NHttp(void);
			
		void addGeneralHeaderParam(GeneralHeaderParam param, 
				const NString &value);
		NString getGeneralHeaderValue(GeneralHeaderParam param) const;
		
		void addEntityHeaderParam(EntityHeaderParam param, 
				const NString &value);
		NString getEntityHeaderValue(EntityHeaderParam param) const;
			
		void formatParam(NDataStream *stream, const NString &name, 
				const NString &value);		
		
		NDataStream protocolGeneralHeader(void);
		NDataStream protocolEntityHeader(void);
		NDataStream protocolHTTPVersion(void);
		
		// Headers
		NMap<GeneralHeaderParam, NString> m_general_header;	
		NMap<EntityHeaderParam, NString> m_entity_header;	
		
		// Request
		Method m_method;
		NResourceLocator m_uri;
		
		// Message body (when applicable)
		NDataStream m_body;
};

#endif /*NHTTP_H_*/
