MACRO (AddContrib ${PATH}) 
	IF (EXISTS ${PATH})
		SET (NUS_CONTRIB_MYSQL ${PATH})
	ENDIF (EXISTS ${PATH})
ENDMACRO (AddContrib)

SET (MYSQL_CONTRIB_VERSION 5.0.44)

IF (WIN32) 
	SET(NUS_CONTRIB_MYSQL $ENV{N_MYSQL_DIR})
ENDIF(WIN32)

IF (UNIX) 
	SET (NUS_CONTRIB_MYSQL /usr)
ENDIF (UNIX) 
	
IF (APPLE)
	SET (NUS_CONTRIB_MYSQL /sw)
ENDIF (APPLE)


################
# Checks for mysql C headers
################
FIND_PATH(MYSQL_INCLUDE_DIR 
	mysql.h 
	PATHS
	${NUS_CONTRIB_MYSQL}/include/mysql
	${NUS_CONTRIB_MYSQL}/include/
)

FIND_LIBRARY(MYSQL_LIBRARY 
	NAMES mysqlclient
	PATHS 
	${NUS_CONTRIB_MYSQL}/lib/mysql
	${NUS_CONTRIB_MYSQL}/lib/debug
)


IF (NOT MYSQL_INCLUDE_DIR) 
	MESSAGE(FATAL_ERROR "** Unable to find mysql include directories **")
ENDIF (NOT MYSQL_INCLUDE_DIR)


INCLUDE_DIRECTORIES(
	${MYSQL_INCLUDE_DIR}/
)

LINK_DIRECTORIES(
	${NUS_CONTRIB_MYSQL}/lib
)

MARK_AS_ADVANCED(
	MYSQL_LIBRARY
	MYSQL_INCLUDE_DIR
)

LINK_LIBRARIES(
	${MYSQL_LIBRARY}
)