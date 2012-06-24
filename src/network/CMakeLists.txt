INCLUDE_DIRECTORIES(
	${OS_CODE_DIR}
	exceptions
)

# LinkIfOs("SunOS" "")
# LinkIfOs("SunOS" "")

ADD_LIBRARY(
	nnetwork-${N_VERSION}
	${OS_CODE_DIR}/nhostaddress.h
	${OS_CODE_DIR}/nhostaddress.cpp
	nabstractsocket.h
	nabstractsocket.cpp
	${OS_CODE_DIR}/ntcpsocket.h
	${OS_CODE_DIR}/ntcpsocket.cpp
	exceptions/nnetworkexception.h
	exceptions/nnetworkexception.cpp
	nresourcelocator.h
	nresourcelocator.cpp
	protocols/http/nhttp.h
	protocols/http/nhttp.cpp
	protocols/http/nhttprequest.h
	protocols/http/nhttprequest.cpp
	protocols/http/nhttpresponse.h
	protocols/http/nhttpresponse.cpp
	protocols/http/nhttpserver.h
	protocols/http/nhttpserver.cpp
	protocols/http/nhttpstatus.h
)


IF (UNIX OR CYGWIN)
	IF (${CMAKE_SYSTEM_NAME} STREQUAL "SunOS")
		TARGET_LINK_LIBRARIES(
			nnetwork-${N_VERSION}
			socket
			nsl
			resolv
		)
	ENDIF (${CMAKE_SYSTEM_NAME} STREQUAL "SunOS")
ELSE (UNIX OR CYGWIN)
	IF (WIN32) 
		TARGET_LINK_LIBRARIES(
			nnetwork-${N_VERSION}
			WS2_32
		)
	ENDIF(WIN32)
ENDIF(UNIX OR CYGWIN)



INSTALL(TARGETS nnetwork-${N_VERSION}
	LIBRARY DESTINATION ${N_LIBRARY_DIR}
	RUNTIME DESTINATION ${N_LIBRARY_DIR}
    ARCHIVE DESTINATION ${N_LIBRARY_DIR}
)

InstallHeaders(src/network network)
InstallHeaders(src/network/win32 network/win32)
InstallHeaders(src/network/unix network/unix)
InstallHeaders(src/network/exceptions network/exceptions)
InstallHeaders(src/network/protocols/http network/protocols/http)
InstallCMakeModule(src/network NNetwork)

InstallExamples(src/network/examples/ex_nhostaddress network/ex_nhostaddress)
InstallExamples(src/network/examples/ex_ntcpclient network/ex_ntcpclient)
InstallExamples(src/network/examples/ex_ntcpserver network/ex_ntcpserver)