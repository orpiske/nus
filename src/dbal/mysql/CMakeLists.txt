SET(COMPILING_NUS_LIBRARY ON)
INCLUDE(NMySQLDependencies.cmake)

ADD_LIBRARY(
	ndbal-mysql-${N_VERSION}
	nmysql.h
	nmysql.cpp
)


IF (WIN32) 
	IF (MSVC)
		SET_TARGET_PROPERTIES( 
			ndbal-mysql-${N_VERSION}
			PROPERTIES LINK_FLAGS /NODEFAULTLIB:msvcrtd.lib
		)
	ENDIF(MSVC)
ENDIF(WIN32)

INSTALL(TARGETS ndbal-mysql-${N_VERSION}
	LIBRARY DESTINATION ${N_LIBRARY_DIR}
	RUNTIME DESTINATION ${N_LIBRARY_DIR}
    ARCHIVE DESTINATION ${N_LIBRARY_DIR}
)

InstallHeaders(src/dbal/mysql dbal/mysql)
InstallCMakeModule(src/dbal/mysql NMySQL)
InstallCMakeModule(src/dbal/mysql NMySQLDependencies)
InstallCMakeModule(src/dbal/mysql contrib_mysql)
InstallExamples(src/dbal/mysql/examples dbal/mysql/examples)