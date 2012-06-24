// LICENSE: (Please see the file COPYING for details)
//
// NUS - Nemesis Utilities System: A C++ application development framework 
// Copyright (C) 2006, 2007 Otavio Rodolfo Piske
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
#include "ndefs.h"
#include "nproj.h"
#include "nexception.h"

void setup_opts(NGetOpt<NProj> *opts) { 
	opts->add("h", "help", false, "Display the help for this program", NULL);
	opts->add("m", "modules", true, "Sets the NUS modules for the project", 
		&NProj::setModules);
	opts->add("e", "executable", true, 
		"Sets the executable name for the project", 
		&NProj::setExecutableName);
	opts->add("f", "exefiles", true, 
		"Sets the executable file names for the project", 
		&NProj::setExecutableFiles);

	opts->add("l", "library", true, "Sets the library name for the project", 
		&NProj::setLibraryName);
	opts->add("F", "lib-files", true, 
		"Sets the library file names for the project", 
		&NProj::setLibraryFiles);

	opts->add("L", "link-libraries", true, 
		"Sets the external libraries the project will link to", 
		&NProj::setExecutableFiles);

	opts->add("", "license", false, 
		"Sets the license for the project (currently only LGPL)", 
		&NProj::setLicense);
	opts->add("", "force", false, 
		"Force the overwriting of files", 
		&NProj::setForce);

	opts->add("v", "version", false, "Displays the program version", 
		&NProj::version);
}


int main(int argc, char **argv) {
	NProj app;
	NGetOpt<NProj> opts(argc, argv, &app);

	setup_opts(&opts);
	try { 
		if (opts.proccess()) { 
			app.run();
		}
	}
	catch (NException &e) { 
		NWarning::print() << e.getDescription();
		exit(1);		
	}
	
	return 0;
}
