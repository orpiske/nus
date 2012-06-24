INCLUDE(NNetwork)

LINK_LIBRARIES(
	nbase-${N_VERSION}
)

ADD_EXECUTABLE(
	ex_ntcpclient
	ex_ntcpclient.cpp
	clientapp.h
	clientapp.cpp
)