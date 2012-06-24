MACRO (AddContrib ${PATH}) 
	IF (EXISTS ${PATH})
		SET (NUS_CONTRIB_OPENSSL ${PATH})
	ENDIF (EXISTS ${PATH})
ENDMACRO (AddContrib)

SET (OPENSSL_CONTRIB_VERSION 0.9.8a)

IF (WIN32) 
	SET(NUS_CONTRIB_OPENSSL
		${CMAKE_BINARY_DIR}/contrib/openssl-${OPENSSL_CONTRIB_VERSION}.win32/
	)
	SET(OPENSSL_LIBRARY_NAME libeay32)
ELSE(WIN32)
	IF (UNIX) 
		IF (${CMAKE_SYSTEM_NAME} STREQUAL "SunOS")
			SET (NUS_CONTRIB_OPENSSL /usr/sfw)
		ELSE (${CMAKE_SYSTEM_NAME} STREQUAL "SunOS")
			SET (NUS_CONTRIB_OPENSSL /usr)
		ENDIF (${CMAKE_SYSTEM_NAME} STREQUAL "SunOS")
	ENDIF (UNIX) 
	SET(OPENSSL_LIBRARY_NAME ssl)
ENDIF(WIN32)



################
# Checks for libxml2 C headers
################
FIND_PATH(OPENSSL_INCLUDE_DIR 
	openssl/ssl.h 
	PATHS
	${NUS_CONTRIB_OPENSSL}/include/openssl
	${NUS_CONTRIB_OPENSSL}/include
)

FIND_PATH(CRYPTO_INCLUDE_DIR 
	crypto.h 
	PATHS
	${NUS_CONTRIB_OPENSSL}/include/openssl
)
	
FIND_LIBRARY(OPENSSL_LIBRARY 
	NAMES ${OPENSSL_LIBRARY_NAME} 
	PATHS ${NUS_CONTRIB_OPENSSL}/lib
)

IF (UNIX)
	FIND_LIBRARY(CRYPTO_LIBRARY 
		NAMES crypto
		PATHS ${NUS_CONTRIB_OPENSSL}/lib
	)
ELSE (UNIX)
	SET (CRYPTO_LIBRARY "")
ENDIF (UNIX)
	
IF (NOT OPENSSL_INCLUDE_DIR) 
	MESSAGE(FATAL_ERROR "** Unable to find openssl include files and/or directories **")
ENDIF (NOT OPENSSL_INCLUDE_DIR)

IF (NOT OPENSSL_LIBRARY) 
	MESSAGE(FATAL_ERROR "** Unable to find openssl library files and/or directories **")
ENDIF (NOT OPENSSL_LIBRARY)


IF (NOT CRYPTO_INCLUDE_DIR) 
	MESSAGE(FATAL_ERROR "** Unable to find crypto include directories **")
ENDIF (NOT CRYPTO_INCLUDE_DIR)


INCLUDE_DIRECTORIES(
	${OPENSSL_INCLUDE_DIR}/
	${CRYPTO_INCLUDE_DIR}/
)

LINK_DIRECTORIES(
	${NUS_CONTRIB_OPENSSL}/lib
)

MARK_AS_ADVANCED(
	OPENSSL_LIBRARY
	OPENSSL_INCLUDE_DIR
	CRYPTO_LIBRARY
	CRYPTO_INCLUDE_DIR
)

LINK_LIBRARIES(
	${OPENSSL_LIBRARY}
)