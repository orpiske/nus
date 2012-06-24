INCLUDE(NEvents)

LINK_LIBRARIES(
	nbase-${N_VERSION}
)

ADD_EXECUTABLE(
	ex_events
	ex_raven.cpp
	ex_dispersion.cpp
	ex_main.cpp
)