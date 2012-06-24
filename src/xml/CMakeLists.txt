SET(COMPILING_NUS_LIBRARY ON)
INCLUDE(NXmlDependencies.cmake)

ADD_LIBRARY(
	nxml-${N_VERSION}
	nxmlnode.h
	nxmlnode.cpp
	nxmldocument.h
	nxmldocument.cpp
	nxmlreader.h
	nxmlreader.cpp
	nxmlwriter.h
	nxmlwriter.cpp
	nxmlabstractparser.h
	nxmlabstractparser.cpp
	nxmlparser.h
	nxmlparser.cpp
	nxmlschemaparser.h
	nxmlschemaparser.cpp
	exceptions/nxmlerror.h
	exceptions/nxmlerror.cpp
	exceptions/nxmlexception.h
	exceptions/nxmlexception.cpp
)

INCLUDE_DIRECTORIES(
	exceptions
)

IF (UNIX OR CYGWIN)
	TARGET_LINK_LIBRARIES(
		nxml-${N_VERSION}
		xml2
		m
		z
	)
ELSEIF (UNIX OR CYGWIN)
	IF (WIN32)
		TARGET_LINK_LIBRARIES(
			nxml-${N_VERSION}
			libxml2
			zlib
		)
	ENDIF(WIN32)
ENDIF(UNIX OR CYGWIN)

LINK_LIBRARIES(
	nxml-${N_VERSION}
)

INSTALL(TARGETS nxml-${N_VERSION}
	LIBRARY DESTINATION ${N_LIBRARY_DIR}
	RUNTIME DESTINATION ${N_LIBRARY_DIR}
    ARCHIVE DESTINATION ${N_LIBRARY_DIR}
)

InstallHeaders(src/xml xml)
InstallHeaders(src/xml/exceptions xml)

InstallCMakeModule(src/xml NXml)
InstallCMakeModule(src/xml NXmlDependencies)
InstallCMakeModule(src/xml contrib_libxml)
InstallCMakeModule(src/xml contrib_zlib)
InstallCMakeModule(src/xml contrib_iconv)

InstallExamples(src/xml/examples/xmlreader xml/xmlreader)
InstallExamples(src/xml/examples/xmlwriter xml/xmlwriter)

IF (MODULE_EXAMPLE_SRC)
	InstallFileMask(src/xml/examples *.xml ${N_EXAMPLE_DIR}/xml/data)
	InstallFile(src/xml/examples/nxmlreader-2.dtd ${N_EXAMPLE_DIR}/xml/data)
	InstallFile(src/xml/examples/nxmlreader-2_typo.xml ${N_EXAMPLE_DIR}/xml/data)
	InstallFile(src/xml/examples/nxmlreader-3.xml ${N_EXAMPLE_DIR}/xml/data)
	InstallFile(src/xml/examples/nxmlreader-3.xsd ${N_EXAMPLE_DIR}/xml/data)
ENDIF (MODULE_EXAMPLE_SRC)

IF (WIN32 AND INSTALL_CONTRIB_FILES)
	InstallFile(contrib/libxml${LIBXML2_CONTRIB_VERSION}.win32/bin/libxml2.dll ${N_LIBRARY_DIR})
	InstallFile(contrib/zlib-${ZLIB_CONTRIB_VERSION}.win32/bin/zlib1.dll ${N_LIBRARY_DIR})
	InstallFile(contrib/iconv-${ICONV_CONTRIB_VERSION}.win32/bin/iconv.dll ${N_LIBRARY_DIR})
ENDIF (WIN32 AND INSTALL_CONTRIB_FILES)
