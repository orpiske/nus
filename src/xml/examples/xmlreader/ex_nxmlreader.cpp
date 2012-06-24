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
#include "xmlreader.h"
#include "ngetopt.h"

void setup_opts(NGetOpt<XmlReader> *opts) { 
	opts->add("h", "help", false, "Display the help for this program", NULL);
	opts->add("f", "filename", true, "The xml file to read", 
		    &XmlReader::setFilename);
	opts->add("s", "schema", true, "The filename of the schema file to use", 
		    &XmlReader::setSchema);
	opts->add("d", "dtd", true, "The filename of the dtd file to use",
			&XmlReader::setDtd);
	opts->add("p", "print", false, "Print node info",
			&XmlReader::setPrint); 
	opts->add("S", "search", true, "Search for a node",
			&XmlReader::setSearch); 
}

int main(int argc, char **argv) { 
	XmlReader app;
	NGetOpt<XmlReader> opts(argc, argv, &app, 1);

	// Setup the command line flags (see NGetOpt documentation for details)
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

