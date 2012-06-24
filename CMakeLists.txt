PROJECT(nus)

# Ugly hack to avoid newer versions from complaining. Needs to be fixed
cmake_policy(VERSION 2.4)

INCLUDE(CheckLists.cmake) 
CONFIGURE_FILE(
   "${CMAKE_CURRENT_BINARY_DIR}/deploy/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/deploy/cmake_uninstall.cmake")

CMAKE_MINIMUM_REQUIRED(VERSION 2.4.1 FATAL_ERROR)

# Our version. One must increase this number each time a release is made.
SET(N_MAJOR_VERSION 0)
SET(N_MINOR_VERSION 4)
SET(N_PATCH_VERSION 0)
SET(N_VERSION "${N_MAJOR_VERSION}.${N_MINOR_VERSION}.${N_PATCH_VERSION}")

SET(NT_MAJOR_VERSION 0)
SET(NT_MINOR_VERSION 1)
SET(NT_PATCH_VERSION 0)
SET(NT_TOOLS_VERSION "${NT_MAJOR_VERSION}.${NT_MINOR_VERSION}.${NT_PATCH_VERSION}")

IF(NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE Debug CACHE STRING
      	"Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      	FORCE
	)
ENDIF(NOT CMAKE_BUILD_TYPE)

SET(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "Verbose makefile")
SET(NLIB_DEBUG OFF CACHE BOOL "Adds extra debugging code.")
SET(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries")

# Base module must be always on because it's need by all other modules
SET(MODULE_BASE ON)
SET(MODULE_EVENTS ON CACHE BOOL "Compile events module")
SET(MODULE_NETWORK ON CACHE BOOL "Compile network module")
SET(MODULE_XML ON CACHE BOOL "Compile xml module")
SET(MODULE_SECURITY ON CACHE BOOL "Compile security related module")
SET(MODULE_DBAL ON CACHE BOOL "Compile the database access layer module")
SET(MODULE_EXAMPLE_SRC ON CACHE BOOL "Install example sources")
SET(MODULE_CMAKE_MODULES ON CACHE BOOL "Cmake modules")
SET(N_THREAD_SUPPORT ON CACHE BOOL "Basic thread support")
SET(INSTALL_CONTRIB_FILES OFF CACHE BOOL "Sets whether or not to install contrib files")

MARK_AS_ADVANCED(
	NLIB_DEBUG
	BUILD_SHARED_LIBS
	LIBRARY_OUTPUT_PATH
	EXECUTABLE_OUTPUT_PATH
	CMAKE_BACKWARDS_COMPATIBILITY
	N_THREAD_SUPPORT
)

# Adds commonly used macros and variables
INCLUDE(CMakeLists.default.cmake)

# Adds OS specif build rules
IF (UNIX) 
	MESSAGE(STATUS "Adding Unix related build rules")
	INCLUDE(CMakeLists.unix.cmake) 
ENDIF(UNIX)

IF (WIN32)
	MESSAGE(STATUS "Adding Windows related build rules")
	INCLUDE(CMakeLists.win32.cmake)
ENDIF(WIN32)



IF (NLIB_DEBUG) 
	AddCompilerDefinition(NLIB_DEBUG)
ENDIF (NLIB_DEBUG) 


# Setups internal linkage rules
IF (BUILD_SHARED_LIBS)
	AddCompilerDefinition(NLIB_SHARED)
	AddCompilerDefinition(N_VERSION ${N_VERSION})
	AddCompilerDefinition(N_TOOLS_VERSION ${N_TOOLS_VERSION})
ENDIF (BUILD_SHARED_LIBS)

# Setups compiler specific warnings
IF (CMAKE_COMPILER_IS_GNUCXX)
	SET(CMAKE_C_FLAGS "-Wall -Wshadow " CACHE STRING 
		"Flags used by the compiler during all build types." FORCE
	)

	SET(CMAKE_CXX_FLAGS "-Wall -Weffc++ -Wshadow -pipe" CACHE STRING 
		"Flags used by the compiler during all build types." FORCE
	)
ENDIF (CMAKE_COMPILER_IS_GNUCXX)

# Base input directories
INCLUDE_DIRECTORIES(
	src/base
	src/base/exceptions
	src/base/output
	src/base/bio
	src/base/osal/${OS_CODE_DIR}
)


INCLUDE(${CMAKE_BINARY_DIR}/deploy/CMakeInstall.txt)
ADD_SUBDIRECTORY(
	src/base
)

SET(CMAKE_MODULE_PATH 
	"${CMAKE_MODULE_PATH};${CMAKE_BINARY_DIR}/src/base/"
)

LINK_LIBRARIES(
	nbase-${N_VERSION}
)

EnableModule(MODULE_EVENTS "Events" src/events)
EnableModule(MODULE_NETWORK "network" src/network src/network/exceptions)
EnableModule(MODULE_XML "xml" src/xml)
EnableModule(MODULE_SECURITY "security" src/security src/security/hash)
CheckIfEnabled(MODULE_DBAL MODULE_NETWORK)
LinkIfEnabled(MODULE_DBAL nnetwork-${N_VERSION})
EnableModule(MODULE_DBAL "db access layer" src/dbal)

ADD_SUBDIRECTORY(src/apps/nproj)
