IF (NOT MODULE_EXAMPLE)	
	IF (NOT CMAKE_MODULE_PATH)
		MESSAGE(STATUS "CMAKE_MODULE_PATH is not set. Using default")
		SET(CMAKE_MODULE_PATH ${NUS_INSTALL_DIR}/share/nus/0.2/cmake_modules)	
	ENDIF(NOT CMAKE_MODULE_PATH)
	
	INCLUDE(NXml)
ENDIF (NOT MODULE_EXAMPLE)

ADD_EXECUTABLE(
	ex_nxmlreader
	xmlreader.h
	xmlreader.cpp
	ex_nxmlreader.cpp
)