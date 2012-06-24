MACRO (AddContrib ${PATH}) 
	IF (EXISTS ${PATH})
		SET (NUS_CONTRIB_LIBXML2 ${PATH})
	ENDIF (EXISTS ${PATH})
ENDMACRO (AddContrib)

SET (LIBXML2_CONTRIB_VERSION 2-2.6.32+)

# If compiling from inside the library use the contrib packages from the 
# framework if is a windows system. In *nix will use whatever is 
# provided by the distro.
IF (WIN32) 
	SET(NUS_CONTRIB_LIBXML2
		${CMAKE_BINARY_DIR}/contrib/libxml${LIBXML2_CONTRIB_VERSION}.win32/
	)
	SET(LIBXML2_LIBRARY_NAME libxml2)
ELSE(WIN32)
	IF (UNIX) 
		SET (NUS_CONTRIB_LIBXML2 /usr)
	ENDIF (UNIX) 
	SET(LIBXML2_LIBRARY_NAME xml2)
ENDIF(WIN32)

################
# Checks for libxml2 C headers
################
FIND_PATH(LIBXML2_INCLUDE_DIR 
	libxml/parser.h 
	PATHS
	${NUS_CONTRIB_LIBXML2}/include/libxml2/
	${NUS_CONTRIB_LIBXML2}/include/libxml/
	${NUS_CONTRIB_LIBXML2}/include/
)
	
FIND_LIBRARY(LIBXML2_LIBRARY 
	NAMES ${LIBXML2_LIBRARY_NAME} 
	PATHS ${NUS_CONTRIB_LIBXML2}/lib
)

IF (NOT LIBXML2_INCLUDE_DIR) 
	MESSAGE(STATUS "** Tried at: ${NUS_CONTRIB_LIBXML2} **")
	MESSAGE(FATAL_ERROR "** Unable to find libxml2 include files and/or directory **")
ENDIF (NOT LIBXML2_INCLUDE_DIR)


IF (NOT LIBXML2_LIBRARY) 
	MESSAGE(STATUS "** Tried at: ${NUS_CONTRIB_LIBXML2} **")
	MESSAGE(FATAL_ERROR "** Unable to find libxml2 library files and/or directory **")
ENDIF (NOT LIBXML2_LIBRARY)


INCLUDE_DIRECTORIES(
	${LIBXML2_INCLUDE_DIR}/
)

LINK_DIRECTORIES(
	${NUS_CONTRIB_LIBXML2}/lib
)

MARK_AS_ADVANCED(
	LIBXML2_LIBRARY
	LIBXML2_INCLUDE_DIR
)

LINK_LIBRARIES(
	${LIBXML2_LIBRARY}
)