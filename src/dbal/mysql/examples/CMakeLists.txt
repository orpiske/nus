# CMake project file for NUS
# Generated by NProj 0.1.0 with NUS version 0.3.0
INCLUDE(NBase)
INCLUDE(NDBal)
INCLUDE(NMySQL)

# Project executable
ADD_EXECUTABLE(
	ex_nmysql
	ex_nmysql.cpp
	nsqlapp.h
	nsqlapp.cpp
)

