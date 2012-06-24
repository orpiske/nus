SET(MODULE_DBAL_MYSQL OFF CACHE BOOL "Compile the MySQL Database sub-module")

LINK_LIBRARIES(
	ndbal-${N_VERSION}
)

IF (MODULE_DBAL_MYSQL)
	MESSAGE(STATUS "Enabling module db access layer: mysql driver")
	INCLUDE_DIRECTORIES(
		mysql/
	)
	
	ADD_SUBDIRECTORY(
		mysql
	)
ENDIF (MODULE_DBAL_MYSQL)

ADD_LIBRARY(
	ndbal-${N_VERSION}
	nsql.h
	nsql.cpp
	nsqlquery.h
	nsqlquery.cpp
	nsqlrecord.h
	nsqlrecord.cpp
)


INSTALL(TARGETS ndbal-${N_VERSION}
	LIBRARY DESTINATION ${N_LIBRARY_DIR}
	RUNTIME DESTINATION ${N_LIBRARY_DIR}
    ARCHIVE DESTINATION ${N_LIBRARY_DIR}
)

InstallHeaders(src/dbal dbal)
InstallCMakeModule(src/dbal NDBal)
# InstallExamples(src/base/examples base)
