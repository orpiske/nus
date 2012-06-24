INCLUDE(NNetwork)

LINK_LIBRARIES(
	nbase-${N_VERSION}
)

ADD_EXECUTABLE(
	ex_nhostaddress
	ex_nhostaddress.cpp
	nhostopts.h
	nhostopts.cpp
)