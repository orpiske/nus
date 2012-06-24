IF (COMPILING_NUS_LIBRARY)
	INCLUDE(contrib_libxml.cmake)
	INCLUDE(contrib_zlib.cmake)
	INCLUDE(contrib_iconv.cmake)
ELSE (COMPILING_NUS_LIBRARY)
	INCLUDE(contrib_libxml)
	INCLUDE(contrib_zlib)
	INCLUDE(contrib_iconv)
ENDIF(COMPILING_NUS_LIBRARY)

IF (UNIX)
	FIND_LIBRARY(LIBM_LIBRARY NAMES 
		m 
		PATHS
		/usr/lib 
		/usr/local/lib
	)
ENDIF(UNIX)

MARK_AS_ADVANCED(
	LIBM_LIBRARY
)