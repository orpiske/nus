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
#include "nobject.h"
#include "ngetopt.h"
#include "nopthandler.h"

#include <cstdlib>

void setup_options(NGetOpt<NOptHandler> *opts) {
	// First, we map the valid options for the program
	//
	// The first param is the short option, the second is the long option
	// the third is whether it's required, the fourth is the help text for the
	// option and the fifth, which is optional, is the max amount of times the
	// option may appear 
	opts->add("h", "help", false,
		    "Display the help for this program", 
		   NULL);
	
	opts->add("", "south-america", false,
		"Displays the name of (some) countries in South America.",
		&NOptHandler::south_america);
	
	opts->add("c", "central-america", false,
		"Displays the name of (some) countries in Central America.",
		&NOptHandler::central_america);
		
	opts->add("n", "north-america", false, 
		"Displays the name of (some) countries in North America.",
		&NOptHandler::north_america);
	
	// These parameters requires arguments, that's why the third argument is
	// true
	opts->add("l", "language", true,
		"Displays only countries that spoke 'language'. Acceptable values: "
		"english, portuguese, spanish, german, japanese.", 
		&NOptHandler::language);
		
	opts->add("m", "max", true, 
		"Max number of countries per continent to display.",
		&NOptHandler::max);
}

int main(int argc, char **argv) {
	NOptHandler handler;
	NGetOpt<NOptHandler> opts(argc, argv, &handler);
	
	try { 
		setup_options(&opts);
		if (argc > 1) { 
			if (opts.proccess()) { 
				handler.foo();
			}
		}
		else { 
			opts.help();
		}
	}
	catch (const NException &e) { 
		NWarning::print() << "Error: " << e.getDescription();
		exit(1);
	}
	return 0;
}

