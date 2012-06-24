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
#include "nhostopts.h"
#include "ngetopt.h"
#include "noutput.h"
#include "nnetworkexception.h"

void setup_opts(NGetOpt<NHostOpts> *opts) { 
	opts->add("h", "help", false, "Display the help for this program", NULL);
	opts->add("a", "aliases", false, "Display all the aliases for the host", 
		    &NHostOpts::aliases);
	opts->add("A", "addresses", false, "Display all the addresses for the host", 
		    &NHostOpts::addresses);
	opts->add("r", "resolve", true, "The host(s) to resolve", &NHostOpts::resolve);
}


int main(int argc, char **argv) {
	NHostOpts app;
	NGetOpt<NHostOpts> opts(argc, argv, &app);

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
	catch (NNetworkException &e) {
		NWarning::print() << e.getDescription() << ": " << e.getHost();
		exit(1);		
	}
	catch (NException &e) { 
		NWarning::print() << e.getDescription();
		exit(1);		
	}
	
	return 0;
}
