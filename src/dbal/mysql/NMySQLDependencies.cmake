IF (COMPILING_NUS_LIBRARY)
	INCLUDE(contrib_mysql.cmake)
ELSE (COMPILING_NUS_LIBRARY)
	INCLUDE(contrib_mysql)
ENDIF(COMPILING_NUS_LIBRARY)