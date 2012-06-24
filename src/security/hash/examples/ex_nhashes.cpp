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
#include "ndefs.h"
#include "nhash.h"
#include "nmd5hash.h"
#include "ngetopt.h"
#include "noutput.h"
#include "hashapp.h"

void setup_opts(NGetOpt<HashApp> *opts) { 
	opts->add("h", "help", false, "Display the help for this program", NULL);
	opts->add("n", "name", true, "The name of the hash to use", 
		    &HashApp::setHash);
	opts->add("c", "calculate", false, "Calculate the hash of a given object", 
		    &HashApp::calculate);
	opts->add("C", "compare", true, "Compare a hash with an object",
			&HashApp::compare);
	opts->add("f", "file", true, "Computes/compare the hash of a file",
			&HashApp::setFileObj); 
	opts->add("s", "string", true, "Computes/compare the hash of a string",
			&HashApp::setStringObj);
}



int main(int argc, char **argv) {
	HashApp app;
	NGetOpt<HashApp> opts(argc, argv, &app, 1);

	// Setup the command line flags (see NGetOpt documentation for details)
	setup_opts(&opts);
	try { 
		// Run the program, if given command line flags or show the help
		if (argc > 1) { 
			if (opts.proccess()) { 
				app.run();
			}
		}
		else { 
			opts.help();
		}
	}
	catch (NException &e) { 
		NWarning::print() << e.getDescription();
		exit(1);		
	}

	return 0;
}

