// LICENSE: (Please see the file COPYING for details)
//
// <APPLICATION_NAME>: <DESCRIPTION>
// Copyright (C) <DATE> <AUTHOR>
//
//  This file is part of <PROGRAM>
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

// Source code file created by nproj 0.1.0 with NUS version 0.3.0

#include "nsqlapp.h"

void setup_opts(NGetOpt<NSqlApp> *opts) { 
	opts->add("h", "help", false, "Display the help for this program", NULL);
	opts->add("p", "port", true, "Sets the port to connect to the Database", 
		&NSqlApp::setPort);
	opts->add("H", "host", true, 
		"Sets the hostname where the Database is running", 
		&NSqlApp::setHost);

	opts->add("u", "user", true, "Sets the user to connect to the Database", 
		&NSqlApp::setUser);
	opts->add("P", "password", true, 
		"Sets the password to connect to the Database", 
		&NSqlApp::setPassword);
	opts->add("d", "database", true, 
		"Sets the database to connect to", 
		&NSqlApp::setDatabase);
	
}


int main(int argc, char **argv) {
	NSqlApp app;
	NGetOpt<NSqlApp> opts(argc, argv, &app);
	int ret = 0;

	setup_opts(&opts);
	try { 
		if (opts.proccess()) { 
			ret = app.run();
		}
	}
	catch (NException &e) { 
		NWarning::print() << e.getDescription();
		exit(1);		
	}
	
	return ret;
}
