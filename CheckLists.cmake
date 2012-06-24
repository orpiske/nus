INCLUDE (CheckIncludeFiles)
INCLUDE (CheckIncludeFileCXX)

MACRO (FailIfNotSet VARIABLE name)
	IF (NOT ${VARIABLE}) 
		SET(MSG "** A required file, " ${name} ", was not found on your system **")
		MESSAGE(FATAL_ERROR ${MSG})
	ENDIF (NOT ${VARIABLE}) 
ENDMACRO(FailIfNotSet)

################
# Checking C headers
################
IF(UNIX)
	CHECK_INCLUDE_FILE_CXX(cstdio HAVE_CSTDIO)
	FailIfNotSet(HAVE_CSTDIO cstdio)

	CHECK_INCLUDE_FILE_CXX(cstdlib HAVE_STDLIB_H)
	FailIfNotSet(HAVE_STDLIB_H cstdlib)

	CHECK_INCLUDE_FILE_CXX(cstring HAVE_STRING_H)
	FailIfNotSet(HAVE_STRING_H cstring)

	CHECK_INCLUDE_FILE_CXX(cassert HAVE_ASSERT_H)
	FailIfNotSet(HAVE_ASSERT_H cassert)

	CHECK_INCLUDE_FILE_CXX(ctime HAVE_TIME_H)
	FailIfNotSet(HAVE_TIME_H ctime)
ENDIF(UNIX)

CHECK_INCLUDE_FILE_CXX(cstdarg HAVE_STDARG_H)
FailIfNotSet(HAVE_STDARG_H cstdarg)

CHECK_INCLUDE_FILE_CXX(exception HAVE_CXX_EXCEPTION)
FailIfNotSet(HAVE_CXX_EXCEPTION exception)

CHECK_INCLUDE_FILE_CXX(new HAVE_CXX_NEW)
FailIfNotSet(HAVE_CXX_NEW new)

CHECK_INCLUDE_FILE_CXX(ostream HAVE_CXX_OSTREAM)
FailIfNotSet(HAVE_CXX_OSTREAM ostream)

CHECK_INCLUDE_FILES(sys/types.h HAVE_SYS_TYPES_H)
FailIfNotSet(HAVE_SYS_TYPES_H sys/types.h)

CHECK_INCLUDE_FILES(sys/stat.h HAVE_SYS_STAT_H)
FailIfNotSet(HAVE_SYS_TYPES_H sys/stat.h)

IF (UNIX)
	CHECK_INCLUDE_FILES(unistd.h HAVE_UNISTD_H)
	FailIfNotSet(HAVE_UNISTD_H unistd.h)

	CHECK_INCLUDE_FILES(sys/stat.h HAVE_SYS_STAT_H)
	FailIfNotSet(HAVE_SYS_STAT_H sys/stat.h)

	CHECK_INCLUDE_FILES(netdb.h HAVE_NETDB_H)
	FailIfNotSet(HAVE_NETDB_H netdb.h)
	
	CHECK_INCLUDE_FILES(sys/socket.h HAVE_SYS_SOCKET_H)
	FailIfNotSet(HAVE_SYS_SOCKET_H netdb.h)
	
	CHECK_INCLUDE_FILES(netinet/in.h HAVE_NETINET_IN_H)
	FailIfNotSet(HAVE_NETINET_IN_H netinet/in.h)
	
	CHECK_INCLUDE_FILES(arpa/inet.h HAVE_ARPA_INET_H)
	FailIfNotSet(HAVE_ARPA_INET_H arpa/inet.h)
	
	CHECK_INCLUDE_FILES(dirent.h HAVE_DIRENT_H)
	FailIfNotSet(HAVE_DIRENT_H dirent.h)
ENDIF (UNIX)

