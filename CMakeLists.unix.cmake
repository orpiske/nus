MESSAGE(STATUS "Specs: ${CMAKE_SYSTEM_NAME} Version ${CMAKE_SYSTEM_VERSION} running on ${CMAKE_SYSTEM_PROCESSOR}")

SET(CMAKE_USE_CCACHE "OFF" CACHE BOOL "Sets whether to use ccache or not" FORCE)

IF (NOT CMAKE_USE_CCACHE) 
	IF(EXISTS /usr/lib/colorgcc/bin/g++) 
		SET(CMAKE_CXX_COMPILER "/usr/lib/colorgcc/bin/g++" CACHE STRING
			"C++ Compiler" FORCE)
	ENDIF(EXISTS /usr/lib/colorgcc/bin/g++)
ELSE (NOT CMAKE_USE_CCACHE) 
	SET(CMAKE_CXX_COMPILER "/usr/lib/ccache/bin/g++" CACHE STRING
			"C++ Compiler" FORCE)

ENDIF(NOT CMAKE_USE_CCACHE)



SET(OS_CODE_DIR unix)

AddCompilerDefinition(_GNU_SOURCE)
AddCompilerDefinition(REENTRANT)
AddCompilerDefinition(_REENTRANT)
LinkIfOs("SunOS" "pthread")
LinkIfOs("Linux" "pthread")

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build/lib)

SET(N_EXAMPLE_DIR src/nus-${N_VERSION}/examples)
SET(N_RUNTIME_DIR bin)
SET(N_LIBRARY_DIR lib)
SET(N_ARCHIVE_DIR lib)
SET(N_HEADER_DIR include/nus)
SET(N_SHARED_DIR share/nus/${N_VERSION})

SET(N_CMAKE_MODULE_DIR share/nus-${N_MAJOR_VERSION}.${N_MINOR_VERSION}/Modules/)