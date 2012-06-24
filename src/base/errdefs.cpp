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
#include "errdefs.h"

/**
\file errdefs.cpp Error definitions implementation file
*/

const char *nerror(int code) {
	switch (code) {
		case EPERM:
		case EACCES: {
			return "Permission denied";
		}
		case ESRCH: {
			return "No such proccess";
		}
		case EINTR: {
			return "Interrupted function";
		}
		case EIO: {
			return "I/O Error";
		} 
		case ENXIO: {
			return "No such device or address";
		}
		case E2BIG: {
			return "Argument list too long";
		}
		case ENOEXEC: {
			return "Exec format error";
		}
		case EBADF: {
			return "Bad file number";
		}
		case ECHILD: {
			return "No spawned proccess";
		}
		// = EWOULDBLOCK
		case EAGAIN: {
			return "Resource temporarly unavailable";
		}
		case ENOMEM: {
			return "The system is out of memory";
		}
		case EFAULT: {
			return "The given buffer points to unaccessible memory";
		}
		case EBUSY: {
			return "Too busy to complete the request";
		}
		case EEXIST: {
			return "File exists";
		}
		case EXDEV: {
			return "Cross-device link";
		}
		case ENODEV: {
			return "No such device";
		}
		case ENOTDIR: {
			return "A directory component in one of the paths isn't a directory";
		}
		case EISDIR: {
			return "The given path is a directory";
		}
		case EINVAL: {
			return "Invalid argument";
		}
		case ENFILE: { 
			return "Too many open files";
		}
		case EMFILE: {
			return "Too many open files";
		}
		case ENOTTY: {
			return "Inappropriate I/O control operation";
		}
		case EFBIG: {
			return "File too big";
		}
		case ENOSPC: { 
			return "No space left on the device";
		}
		case ESPIPE: {
			return "Invalid seek";
		}
		case EROFS: {
			return "Read-only filesystem";
		}
		case EMLINK: {
			return "Too many links";
		}
		case EPIPE: {
			return "Broken pipe";
		}
		case EDOM: {
			return "Math argument";
		}
		case ERANGE: {
			return "Result too large";
		}
#if !defined(__APPLE__) && !defined(__FreeBSD__)
		case EDEADLOCK: {
			return "Resource deadlock would occur";
		}
#endif // !defined(__APPLE__) && !defined(__FreeBSD__)
		case ENAMETOOLONG: {
			return "Filename too long";
		}
		case ENOLCK: {
			return "No locks available";
		}
		case ENOSYS: {
			return "Function not supported";
		}
		case ENOTEMPTY: {
			return "Directory not empty";
		}
		case EILSEQ: {
			return "Illegal byte sequence";
		}
#if defined(__WIN32) && defined (_MSC_VER)
		case STRUNCATE: {
			return "String was truncated";
		}
#endif // defined(__WIN32) && defined (_MSC_VER)
		
#if !defined(__WIN32) && !defined (_MSC_VER)
		case ELOOP: {
			return "Too many symbolics links";
		}
		case EADDRINUSE: {
			return "Address already in use";
		}
		case EALREADY: {
			return "Connection already in progress";
		}
#if !defined(__APPLE__) && !defined(__FreeBSD__)
		case EBADE: {
			return "Invalid exchange";
		}
		case EBADFD: {
			return "File descriptor in bad state";
		}
		case EBADR: {
			return "Invalid request descriptor";
		}
		
		case EBADRQC: {
			return "Invalid request code";
		}
		case EBADSLT: {
			return "Invalid slot";
		}
		
		case ECHRNG: {
			return "Channel number out of range";
		}
		case ECOMM: {
			return "Communication error on send";
		}
#if !defined(__CYGWIN__) && !defined(__SVR4)
		case EISNAM: { 
			return "Is a named type file";
		}
		case EKEYEXPIRED: {
			return "Key has expired";
		}
		case EKEYREJECTED: {
			return "Key was rejected by service";
		}
		case EKEYREVOKED: {
			return "Key has been revoked";
		}
#endif // !defined(__CYGWIN__) && !defined(__SVR4)
		case EL2HLT: {
			return "Level 2 halted";
		}
		case EL2NSYNC: {
			return "Level 2 not synchronized";
		}
		case EL3HLT: {
			return "Level 3 halted";
		}
		case EL3RST: {
			return "Level 3 halted";
		}
		case ELIBACC: {
			return "Cannot access a needed shared library";
		}
		case ELIBBAD: {
			return "Accessing a corrupted shared library";
		}
		case ELIBMAX: { 
			return "Attempting to link in too many shared libraries";
		}
		case ELIBSCN: {
			return "lib section in a.out corrupted";
		}
		case ELIBEXEC: {
			return "Cannot exec a shared library directly";
		}
#if !defined(__CYGWIN__) && !defined(__SVR4)
		case EMEDIUMTYPE: {
			return "Wrong medium type";
		}
		case ENOKEY: { 
			return "Required key not available";
		}
#endif // !defined(__CYGWIN__) && !defined(__SVR4)
		case ENOTUNIQ: {
			return "Name not unique on network";
		}
		case EREMCHG: {
			return "Remote address changed";
		}
#if !defined(__CYGWIN__) && !defined(__SVR4)
		case EREMOTEIO: { 
			return "Remote I/O error";
		}
		case ERESTART: {
			return "Interrupted system call should be restarted";
		}
		case ESTRPIPE: {
			return "Streams pipe error";
		}
		case EUCLEAN: {
			return "Structure needs cleaning";
		}
#endif // !defined(__CYGWIN__) && !defined(__SVR4)
		case EUNATCH: {
			return "Protocol driver not attached";
		}
		case EXFULL: {
			return "Exchange full";
		}
#endif // !defined(__APPLE__) && !defined(__FreeBSD__)
		case EBADMSG: {
			return "Bad message";
		}
#if !defined(__CYGWIN__)
		case ECANCELED: {
			return "Operation canceled";
		}
#endif // !defined(__CYGWIN__)
		case ECONNABORTED: {
			return "connection aborted";
		}
		case ECONNREFUSED: {
			return "Connection refused";
		}
		case ECONNRESET: {
			return "Connection reset";
		}
		case EDESTADDRREQ: {
			return "Destination address required";
		}
		case EDQUOT: { 
			return "Disk quota exceeded";
		}
		case EHOSTDOWN: {
			return "Host is down:";
		}
		case EHOSTUNREACH: {
			return "Host is unreachable";
		}
		case EIDRM: {
			return "Identifier removed";
		}
		case EINPROGRESS: {
			return "Operation in progress";
		}
		case EISCONN: {
			return "Socket is connected";
		}
		case EMSGSIZE: {
			return "Message too long";
		}
		case EMULTIHOP: {
			return "Multihop attempted";
		}
		case ENETDOWN: {
			return "Network is down";
		}
		case ENETRESET: {
			return "Connection aborted by network";
		}
		case ENETUNREACH: {
			return "Network unreachable";
		}
		case ENOBUFS: {
			return "No buffer space available";
		}
		case ENODATA: {
			return "No message is available on the STREAM head read queue";
		}
//		case ENODEV: {
//			return "No such device";
//		}
		case ENOLINK: {
			return "Link has been severed";
		}
		case ENOPROTOOPT: {
			return "Protocol not available";
		}
		case ENOSR: {
			return "No STREAM resources";
		}
		case ENOSTR: {
			return "Not a STREAM";
		}
		case ENOTBLK: {
			return "Block device required";
		}
		case ENOTCONN: {
			return "The socket is not connected";
		}
		case ENOTSOCK: {
			return "Not a socket";
		}
		// From the errno man page: ENOTSUP  and  EOPNOTSUPP  have  the 
		// same value on Linux, but according to POSIX.1 these error 
		// values should be distinct. 
		case ENOTSUP: {
			return "Operation not supported";
		}
		case EOVERFLOW: {
			return "Value too large to be stored in data type";
		}
		case EPFNOSUPPORT: {
			return "Protocol family not supported";
		}
		case EPROTO: {
			return "Protocol error";
		}
		case EPROTONOSUPPORT: { 
			return "Protocol not supported";
		}
		case EPROTOTYPE: {
			return "Protocol wrong type for socket";
		}
		case EREMOTE: {
			return "Object is remote";
		}
		case ESHUTDOWN: { 
			return "Cannot send after transport endpoint shutdown";
		}
		case ESOCKTNOSUPPORT: {
			return "Socket type not supported";
		}
		case ESTALE: {
			// From the errno man page: this error can occur for 
			// NFS and for other file systems
			return "Stale file handle";
		}
		case ETIME: {
			return "Timer expired";
		}
		case ETIMEDOUT: {
			return "Connection timed out";
		}
		case ETXTBSY: { 
			return "Text file busy";
		}
		
		case EUSERS: { 
			return "Too many users";
		}
		case ENOENT: { 
			return "File does not exist";
		}
						
#endif // !defined(__WIN32) && !defined (_MSC_VER)

		default: {
			return "Unhandled error";
		}
	}
}
