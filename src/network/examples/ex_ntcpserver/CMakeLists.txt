INCLUDE(NNetwork)

LINK_LIBRARIES(
	nbase-${N_VERSION}
)

ADD_EXECUTABLE(
	ex_ntcpserver
	ex_ntcpserver.cpp
	serverapp.h
	serverapp.cpp
)