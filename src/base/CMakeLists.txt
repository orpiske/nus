IF (UNIX) 
	SET(N_REGEX_FILES nregex.h nregex.cpp)
ENDIF (UNIX) 

ADD_LIBRARY(
	nbase-${N_VERSION}
	errdefs.h
	errdefs.cpp
	nobject.h
	nobject.cpp
	nstring.h
	nstring.cpp
	ntime.h
	ntime.cpp
	ndate.h
	ndate.cpp
	ndatetime.h
	ndatetime.cpp
	ndatastream.h
	ndatastream.cpp
	ndefs.h
	nrand.h
	nrand.cpp
	nlistnode.h
	nlist.h
	nlist.hpp
	nsortedlist.h
	nsortedlist.hpp
	nskipnode.h
	nskipnode.hpp
	nskiplist.h
	nskiplist.hpp
	nmapitem.h
	nmapitem.hpp
	nmap.h
	nmap.hpp
	${N_REGEX_FILES}
	nvtype.h
	nvtype.cpp
	nkeypair.h
	nkeypair.hpp
	nlocaltime.h
	exceptions/nexception.h
	exceptions/nexception.cpp
	exceptions/nmemexception.h
	exceptions/nmemexception.cpp
	exceptions/nioexception.h
	exceptions/nioexception.cpp
	output/nbaseoutput.h
	output/nbaseoutput.cpp
	output/nmessage.h
	output/nmessage.cpp
	output/nwarning.h
	output/nwarning.cpp
	output/ndebug.h
	output/ndebug.cpp
	bio/niodevice.h
	bio/niodevice.cpp
	bio/nfile.h
	bio/nfile.cpp
	bio/nfileinfo.h
	bio/nfileinfo.cpp
	bio/ndir.h
	bio/ndir.cpp
    osal/${OS_CODE_DIR}/nthread.cpp
    osal/${OS_CODE_DIR}/nthread.h
)

INSTALL(TARGETS nbase-${N_VERSION}
	LIBRARY DESTINATION ${N_LIBRARY_DIR}
	RUNTIME DESTINATION ${N_LIBRARY_DIR}
    ARCHIVE DESTINATION ${N_LIBRARY_DIR}
)

InstallHeaders(src/base base)
InstallHeaders(src/base/bio base/bio)
InstallHeaders(src/base/exceptions base/exceptions)
InstallHeaders(src/base/output base/output)
InstallHeaders(src/base/osal base/osal)
InstallHeaders(src/base/osal/unix base/osal/unix)
InstallHeaders(src/base/osal/win32 base/osal/win32)
InstallCMakeModule(src/base NBase)
InstallExamples(src/base/examples base)