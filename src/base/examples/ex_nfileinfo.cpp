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
#include "nfileinfo.h"
#include "nobject.h"
#include "nstring.h"
#include "ngetopt.h"
#include "noutput.h"

class FileInfoApp {
	public:
		FileInfoApp(void) {

		}

		bool setFile(const NOpt<FileInfoApp> &opt) {
			m_filename = opt.getValues().at(0);
			return true;
		}


		int run(void) {
			NFileInfo info(m_filename);

			
			// Checks the file type 
			NMessage::print() << "The file " << m_filename << 
				(info.isFile() ? " is" : " is not") << " a file";
			NMessage::print() << "The file " << m_filename << 
				(info.isDir() ? " is" : " is not") << 
				" a directory";
			NMessage::print() << "The file " << m_filename << 
				(info.isDevice() ? " is" : " is not") << 
				" a device";
			NMessage::print() << "The file " << m_filename << 
				(info.isFifo() ? " is" : " is not") << " a fifo";
			NMessage::print() << "The file " << m_filename << 
				(info.isLink() ? " is" : " is not") << " a link";

			// Checks the file permissions for read
			NMessage::print() << "The file " << m_filename << 
				(info.ownerRead() ? " can" : " can not") << 
				" be read by the owner";
			NMessage::print() << "The file " << m_filename << 
				(info.groupRead() ? " can" : " can not") << 
				" be read by the group";
			NMessage::print() << "The file " << m_filename << 
				(info.othersRead() ? " can" : " can not") << 
				" be read by others";

			// Checks the file permissions for writing
			NMessage::print() << "The file " << m_filename << 
				(info.ownerWrite() ? " can" : " can not") << 
				" be written by the owner";
			NMessage::print() << "The file " << m_filename << 
				(info.groupWrite() ? " can" : " can not") << 
				" be written by the group";
			NMessage::print() << "The file " << m_filename << 
				(info.othersWrite() ? " can" : " can not") << 
				" be written by others";

			// Checks the file permissioning for executing
			NMessage::print() << "The file " << m_filename << 
				(info.ownerExecute() ? " can" : " can not") << 
				" be executed by the owner";
			NMessage::print() << "The file " << m_filename << 
				(info.groupExecute() ? " can" : " can not") << 
				" be executed by the group";
			NMessage::print() << "The file " << m_filename << 
				(info.othersExecute() ? " can" : " can not") << 
				" be executed by others";

			return 0;
		}
	private:
		NString m_filename;
};

void setup_opts(NGetOpt<FileInfoApp> *opts) { 
	opts->add("h", "help", false, "Display the help for this program", NULL);
	opts->add("f", "file", true, "The file/directory to check", 
		    &FileInfoApp::setFile);
}

int main(int argc, char **argv) { 
	FileInfoApp app;
	NGetOpt<FileInfoApp> opts(argc, argv, &app, 1);

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