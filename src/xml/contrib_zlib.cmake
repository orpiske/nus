SET (ZLIB_CONTRIB_VERSION 1.2.3)

IF (COMPILING_NUS_LIBRARY)
	IF (WIN32) 
		SET(NUS_CONTRIB_ZLIB
			${CMAKE_BINARY_DIR}/contrib/zlib-${ZLIB_CONTRIB_VERSION}.win32/
		)
	ENDIF(WIN32)
ENDIF (COMPILING_NUS_LIBRARY)

IF (UNIX OR CYGWIN) 
	SET (NUS_CONTRIB_ZLIB /usr)
ENDIF (UNIX OR CYGWIN) 

################
# Checks for zlib C headers
################
FIND_LIBRARY(ZLIB_LIBRARY NAMES 
	NAMES z zlib zlib1
	PATHS 
	${NUS_CONTRIB_ZLIB}/lib
	${NUS_CONTRIB_ZLIB}/bin
)

IF (NOT ZLIB_LIBRARY) 
	MESSAGE(FATAL_ERROR "Unable to find contrib library: zlib")
ENDIF (NOT ZLIB_LIBRARY)

LINK_DIRECTORIES(
	${NUS_CONTRIB_ZLIB}/lib
)

MARK_AS_ADVANCED(
	LIBZ_LIBRARY
	LIBZ_LIBRARY_DIR
)