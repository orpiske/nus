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
// This example shows how to use the NFile class to manipulate files
#include "ndir.h"
#include "nobject.h"
#include "nstring.h"
#include "ngetopt.h"
#include "noutput.h"
#include "nlist.h"

class DirInfo {
	public:
		DirInfo(void) {

		}

		bool setPath(const NOpt<DirInfo> &opt) {
			m_path = opt.getValues().at(0);
			return true;
		}


		int run(void) {
			NDir dir(m_path);
			NList<NString> contents;

			contents = dir.getContents();
			for (nuint64 i = 0; i < contents.size(); i++) {
				NMessage::print() << "Entry " << i << " = " << 
					contents.at(i);
			}
			
			return 0;
		}
	private:
		NString m_path;
};

void setup_opts(NGetOpt<DirInfo> *opts) { 
	opts->add("h", "help", false, "Display the help for this program", NULL);
	opts->add("p", "path", true, "The path to check", 
		    &DirInfo::setPath);
}

int main(int argc, char **argv) { 
	DirInfo app;
	NGetOpt<DirInfo> opts(argc, argv, &app, 1);

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