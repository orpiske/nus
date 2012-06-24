SET(COMPILING_NUS_LIBRARY ON)
INCLUDE(NSecurityDependencies.cmake)

ADD_LIBRARY(
	nsecurity-${N_VERSION}
	hash/nhash.h
	hash/nhash.cpp
	hash/nabstracthash.h
	hash/nabstracthash.cpp
	hash/nmd5hash.h
	hash/nmd5hash.cpp
	hash/nmd4hash.h
	hash/nmd4hash.cpp
	hash/nmd2hash.h
	hash/nmd2hash.cpp
	hash/nshahash.h
	hash/nshahash.cpp
	hash/nsha1hash.h
	hash/nsha1hash.cpp
)

TARGET_LINK_LIBRARIES(
	nsecurity-${N_VERSION}
	${OPENSS_LIBRARY}
	${CRYPTO_LIBRARY}
)

INSTALL(TARGETS nsecurity-${N_VERSION}
	LIBRARY DESTINATION ${N_LIBRARY_DIR}
	RUNTIME DESTINATION ${N_LIBRARY_DIR}
    ARCHIVE DESTINATION ${N_LIBRARY_DIR}
)

InstallHeaders(src/security security)
InstallHeaders(src/security/hash security/hash)

InstallCMakeModule(src/security NSecurity)
InstallCMakeModule(src/security NSecurityDependencies)
InstallCMakeModule(src/security contrib_openssl)

InstallExamples(src/security/hash/examples security/hash/examples)

IF (WIN32 AND INSTALL_CONTRIB_FILES)
	InstallFile(contrib/openssl-${OPENSSL_CONTRIB_VERSION}.win32/bin/libeay32.dll ${N_LIBRARY_DIR})
	InstallFile(contrib/openssl-${OPENSSL_CONTRIB_VERSION}.win32/bin/ssleay32.dll ${N_LIBRARY_DIR})
ENDIF (WIN32 AND INSTALL_CONTRIB_FILES)