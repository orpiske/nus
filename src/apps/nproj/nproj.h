// LICENSE: (Please see the file COPYING for details)
//
// NUS - Nemesis Utilities System: A C++ application development framework 
// Copyright (C) 2006, 2008 Otavio Rodolfo Piske
//
//  This file is part of NUS
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation version 2.1
//  of the License.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
#ifndef NPROJ_H_
#define NPROJ_H_

#include "ndefs.h"
#include "nobject.h"
#include "nopt.h"
#include "ngetopt.h"
#include "nstring.h"
#include "nfile.h"
#include "ndatastream.h"

#include "nfilecreator.h"
#include "nlicenses_list.h"

class NProj: public NObject {
	public:	
		NProj(void);
		~NProj(void);

		bool setModules(const NOpt<NProj> &opts);
		bool setExecutableFiles(const NOpt<NProj> &opts);
		bool setExecutableName(const NOpt<NProj> &opts);
		bool setLibraryFiles(const NOpt<NProj> &opts);
		bool setLibraryName(const NOpt<NProj> &opts);

		bool setLinkLibraries(const NOpt<NProj> &opts);
		bool version(const NOpt<NProj> &opts);
		bool setLicense(const NOpt<NProj> &opts);
		bool setForce(const NOpt<NProj> &opts);

		int run(void);
		
	private:
		NList<NString> m_modules;

		NString m_exe_name;
		NList<NString> m_exe_files;
		
		NString m_lib_name;
		NList<NString> m_lib_files;

		NList<NString> m_link_libraries;
		NFile m_output;

		bool m_license;
		bool m_force;

		NProj(const NProj &other);
		NProj &operator=(const NProj &rhs);

		void addOpt(NList<NString> *list, NString &str);

		void setupHeader(void);
		void addModules(void);
		void addExecutable(void);
		void addLibrary(void);

};

#endif // NPROJ_H_
