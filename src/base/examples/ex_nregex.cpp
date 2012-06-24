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

#include "nobject.h"
#include "nstring.h"
#include "nregex.h"
#include "ngetopt.h"
#include "nlist.h"

class RegexExample {
	public:
		RegexExample(void): m_reg(), m_string() { }
		
		bool setRegex(const NOpt<RegexExample> &opt) {
			m_reg = opt.getValues().at(0);
			return true;
		}

		bool setString(const NOpt<RegexExample> &opt) {
			m_string = opt.getValues().at(0);
			return true;
		}
		
		void run(void) {
			NRegex regex(m_reg, m_string);
			NList<NRegex::MatchOffset> off_list;

			if (regex.match()) {
				NMessage::print() << "Matched: " << m_reg 
					<< " with " << m_string;
			}
			else {
				NWarning::print() << "Not matched: " << m_reg 
					<< " with " << m_string;
			}
		}	

	private:
		NString m_reg;
		NString m_string;
		

};

void setup_opts(NGetOpt<RegexExample> *opts) { 
	opts->add("h", "help", false, "Display the help for this program", NULL);
	opts->add("r", "regex", true, "The regex to match", 
		    &RegexExample::setRegex);
	opts->add("s", "string", true, "The string to match", 
		    &RegexExample::setString);
}

int main(int argc, char **argv) { 
	RegexExample app;
	NGetOpt<RegexExample> opts(argc, argv, &app, 1);

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