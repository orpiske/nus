INCLUDE(NBase)
INCLUDE(NNetwork)
INCLUDE(NDBal)
INCLUDE(NMySQLDependencies)

FIND_LIBRARY(NUS_DBAL_MYSQL_LIBRARY
	NAMES ndbal-mysql-${N_VERSION}
	PATHS 
	${NUS_INSTALL_DIR}/lib 
)	

LINK_DIRECTORIES(
	${NUS_DBAL_MYSQL_LIBRARY_DIR}
)

INCLUDE_DIRECTORIES(
	${NUS_INCLUDE_DIR}/dbal/mysql
	${NUS_INCLUDE_DIR}/dbal/exceptions
)

LINK_LIBRARIES(
	${NUS_BASE_LIBRARY}
	${NUS_NETWORK_LIBRARY}
	${NUS_DBAL_LIBRARY}
	${NUS_DBAL_MYSQL_LIBRARY}
)