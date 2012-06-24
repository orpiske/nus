cmake_policy(VERSION 2.4)

# Adds a compiler definition
MACRO(AddCompilerDefinition NAME)
	IF (NOT ${ARGV1})
		IF (MSVC)
			ADD_DEFINITIONS(
				/D${NAME}=\\"${ARGV1}\\"
			)
		ELSE (MSVC)
			IF (CMAKE_COMPILER_IS_GNUCXX)
				ADD_DEFINITIONS(
					-D${NAME}='"${ARGV1}"'
				)
			ELSE (CMAKE_COMPILER_IS_GNUCXX)
				MESSAGE(FATAL "Unsupported compiler")
			ENDIF (CMAKE_COMPILER_IS_GNUCXX)

		ENDIF(MSVC)
	ELSE (NOT ${ARGV1})
		IF (MSVC)
			ADD_DEFINITIONS(
				/D${NAME}
			)
		ELSE (MSVC)
			IF (CMAKE_COMPILER_IS_GNUCXX)
				ADD_DEFINITIONS(
					-D${NAME}
				)
			ELSE (CMAKE_COMPILER_IS_GNUCXX)
				MESSAGE(FATAL "Unsupported compiler")
			ENDIF (CMAKE_COMPILER_IS_GNUCXX)

		ENDIF(MSVC)		
	
	ENDIF (NOT ${ARGV1})
ENDMACRO(AddCompilerDefinition NAME VALUE)

# Checks if a module is enabled
MACRO(CheckIfEnabled MODNAME)
	IF (${MODNAME})
		MESSAGE(STATUS "Dependency check for ${MODNAME}")
		FOREACH(dep_mod ${ARGN})
			MESSAGE(STATUS "Checking if ${dep_mod} is enabled")
			IF (NOT ${dep_mod})
				MESSAGE(FATAL_ERROR "** Module ${MODNAME} requires ${dep_mod} **")
			ENDIF (NOT ${dep_mod})
		ENDFOREACH(dep_mod)
	ENDIF (${MODNAME})
ENDMACRO(CheckIfEnabled MODNAME DEPNAME)

# Include a directory if path is existant
MACRO(IncludeIfPresent PATH)
	IF (EXISTS ${PATH})
		INCLUDE_DIRECTORIES(
			${PATH}
		)
	ENDIF (EXISTS ${PATH})
ENDMACRO(IncludeIfPresent PATH)

# Enable module
MACRO(EnableModule VAR MOD_NAME PATH)
	IF (${VAR})
		MESSAGE(STATUS "Enabling module ${MOD_NAME}")

		INCLUDE_DIRECTORIES(
			${PATH}
		)

		ADD_SUBDIRECTORY(
			${PATH}
		)
		
		FOREACH(inc_dir ${ARGN})
			ADD_SUBDIRECTORY(
				${inc_dir}
			)
		ENDFOREACH(inc_dir)

		IncludeIfPresent(${CMAKE_BINARY_DIR}/${PATH}/${OS_CODE_DIR})
		IncludeIfPresent(${CMAKE_BINARY_DIR}/${PATH}/exceptions)
	ENDIF(${VAR})
ENDMACRO(EnableModule)

# Link a library with a module if module is enabled
MACRO(LinkIfEnabled MODNAME LIBNAME)
	IF (${MODNAME})
		LINK_DIRECTORIES(
			${LIBRARY_OUTPUT_PATH}
		)

		LINK_LIBRARIES(
			${LIBNAME}
		)
	ENDIF (${MODNAME})
ENDMACRO(LinkIfEnabled MODNAME LIBNAME)

MACRO(LinkIfOs OSNAME LIBNAME)
	IF (${CMAKE_SYSTEM_NAME} STREQUAL ${OSNAME})
		LINK_LIBRARIES(
			${LIBNAME}
		)
	ENDIF (${CMAKE_SYSTEM_NAME} STREQUAL ${OSNAME})
ENDMACRO(LinkIfOs OSNAME LIBNAME)

