INCLUDE(NBase)

ADD_EXECUTABLE(
	ex_nstring
	ex_nstring.cpp
)

ADD_EXECUTABLE(
	ex_ndatastream
	ex_ndatastream.cpp
)

ADD_EXECUTABLE(
	ex_nsortedlist
	ex_nsortedlist.cpp
)

ADD_EXECUTABLE(
	ex_nlist
	ex_nlist.cpp
)

ADD_EXECUTABLE(
	ex_nskiplist
	ex_nskiplist.cpp
)

ADD_EXECUTABLE(
	ex_skip_vs_sorted
	ex_skip_vs_sorted.cpp
)

ADD_EXECUTABLE(
	ex_nmap
	ex_nmap.cpp
)

ADD_EXECUTABLE(
	ex_nfile
	ex_nfile.cpp
)

ADD_EXECUTABLE(
	ex_ngetopt
	ex_ngetopt.cpp
	nopthandler.h
	nopthandler.cpp
)

IF (NOT WIN32) 
	ADD_EXECUTABLE(
		ex_nregex
		ex_nregex.cpp
	)
ELSE (NOT WIN32) 
	MESSAGE(STATUS "NRegex example won't be compiled as it's supported in Windows")
ENDIF (NOT WIN32)

ADD_EXECUTABLE(
	ex_nfileinfo
	ex_nfileinfo.cpp
)


ADD_EXECUTABLE(
	ex_ndir
	ex_ndir.cpp
)