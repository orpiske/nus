INCLUDE(NBase)
INCLUDE(NXml)


IF(WIN32)
	REMOVE_DEFINITIONS(/DNLIB_SHARED)
ELSE(WIN32)
	REMOVE_DEFINITIONS(-DNLIB_SHARED)
ENDIF(WIN32)

LINK_LIBRARIES(
	${NUS_XML_LIBRARY}
)

ADD_EXECUTABLE(
	ex_nxmlreader
	xmlreader/xmlreader.h
	xmlreader/xmlreader.cpp
	xmlreader/ex_nxmlreader.cpp
)

ADD_EXECUTABLE(
	ex_nxmlwriter
	xmlwriter/ex_nxmlwrite.cpp
)