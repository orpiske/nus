SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build/bin)

SET(CMAKE_INSTALL_PREFIX "c:/lib/nus-${N_VERSION}" CACHE STRING 
	"Sets the installation path of the library" 
	FORCE
)

IF (UNIX OR CYGWIN)
	SET(OS_CODE_DIR unix)
ELSE (UNIX OR CYGWIN)
	IF (WIN32) 
		SET(OS_CODE_DIR win32)
	ENDIF(WIN32)
ENDIF(UNIX OR CYGWIN)

MESSAGE(STATUS "Library is $ENV{LIB}")

LINK_DIRECTORIES($ENV{LIB})

SET(N_EXAMPLE_DIR src/nus-${N_VERSION}/examples)
SET(N_RUNTIME_DIR bin)
SET(N_LIBRARY_DIR lib)
SET(N_ARCHIVE_DIR lib)
SET(N_HEADER_DIR include/nus)
SET(N_SHARED_DIR share/nus/${N_VERSION})
SET(N_CMAKE_MODULE_DIR ${N_SHARED_DIR}/cmake_modules)