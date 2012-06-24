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
#include "ngetopt.h"
#include "noutput.h"
#include "nnetworkexception.h"

#include "clientapp.h"

void setup_opts(NGetOpt<ClientApp> *opts) { 
	opts->add("h", "help", false, "Display the help for this program", NULL);
	opts->add("p", "port", true, "Sets the remote port to connect to", 
		    &ClientApp::setPort);
	opts->add("H", "host", true, "Sets the address of the remote host", 
		    &ClientApp::setHost);
}

int main(int argc, char **argv) {
	ClientApp app;
	NGetOpt<ClientApp> opts(argc, argv, &app, 1);
	
	setup_opts(&opts);
	
	try {
		if (opts.proccess()) {
			app.run();
		}
	}
	catch (NException &e) {
		NWarning::print() << "Error: " << e.getDescription();
		exit(1);
	}
	
	return 0;
}

