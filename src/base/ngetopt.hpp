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
#ifndef NGETOPT_HPP
#define NGETOPT_HPP

/**
\file ngetopt.hpp Template definition/implementation for NGetOpt class
\example ex_ngetopt.cpp
\include nopthandler.cpp
\include nopthandler.h
*/

/**
\class NGetOpt 
\brief class implements an easy to use command-line processing utility
\todo showUsage() is not working nicely on windows
*/
template <typename HandlerType>
class NGetOpt: public NObject {
	public:
		
		/**
		\brief Enumerates acceptable command-line styles
		*/
		enum Style {
			GNU_STYLE,		/*!< Use GNU style: (- and --). This is the default */
			BSD_STYLE,		/*!< Use BSD style: (- and -) */
			WINDOWS_STYLE,	/*!< Use Windows style: (/ and /) */
		};
		
		/**
		\brief Type definition for the command-line options list
		*/
		typedef NList< NOpt<HandlerType> > NOptList;
	
	
		/**
		\brief Constructs a NGetOpt object
		\param argc Number of arguments
		\param argv The command-line arguments 
		\param handler The handler object. The object to which one maps the 
		treatment of each option
		\param min_args Minimum number of arguments that must be provided 
		when calling the application
		\param style The style of command-line as defined by the enum Style
		*/
		NGetOpt(int argc, char **argv, HandlerType *handler, 
			nuint32 min_args = 0, Style style = GNU_STYLE);
		
		/**
		\brief Destroys a NGetOpt object
		*/
		~NGetOpt(void);
		
		/**
		\brief Sets the style used for the command line options
		\param style The style of command-line as defined by the enum Style
		*/
		void setStyle(Style style);
		
		/**
		\brief Gets the style used for the command line options
		\return The style used for the command line options as defined by
		the enum Style
		*/
		Style getStyle(void) const;
		
		/**
		\brief Adds a command-line option
		\param opt_short A letter identifying the option
		\param opt_long A long option name or "" in case it doesn't exist
		\param opt_opt A boolean value indicating whether the option is required 
		or not
		\param help A help text describing the option and its arguments
		\param handler The handler object. The object to which one maps the 
		treatment of each option
		\return A reference to the current object
		*/
		NGetOpt &add(const NString &opt_short, const NString &opt_long, 
				bool opt_opt, const NString &help, 
     				typename NOpt<HandlerType>::Handler handler);
		
		/**
		\brief Adds a command-line option
		\param opt An already set up NOpt object
		\return A reference to the current object
		*/
		NGetOpt &add(const NOpt<HandlerType> &opt);
		
		/**
		\brief Proccess the command-line options
		\return True in case of success or false otherwise
		*/
		bool proccess(void);
		
		/**
		\brief Shows the help text of each function in a fancy/formatted output
		*/
		void help(void);
		
	private:
		int m_argc;
		char **m_argv;
		HandlerType *m_handler;
		Style m_style;
		NOptList m_opts;
		NString m_style_str_short;
		NString m_style_str_long;
		NOptList m_passed;
		nint32 m_min_args;
		
		NOpt<HandlerType> getOptByName(const NString &str);
		bool isLongOpt(const NString &str) const;
		bool isShortOpt(const NString &str) const;
		
		NException valueErr(const NOpt<HandlerType> *opt);
		char **addValue(NOpt<HandlerType> *opt, nint32 pos, char **list);
		void checkRequired(void);
		
		
		void showUsage(void);
		void showHelp(void);
		
		NGetOpt(const NGetOpt &);
		NGetOpt &operator=(const NGetOpt &);
};


template <typename HandlerType>
NGetOpt<HandlerType>::NGetOpt(int argc, char **argv, HandlerType *handler, 
	nuint32 min_args, Style style)
			: NObject(),
			m_argc(argc - 1),
			m_argv(argv),
			m_handler(handler),
			m_style(style),
			m_opts(),
			m_style_str_short(),
			m_style_str_long(),
			m_passed(),
			m_min_args(min_args)
			
{
	assert(handler);
	
	if (m_style == GNU_STYLE) {
		m_style_str_short = "-";
		m_style_str_long = "--";
	}
	else {
		if (m_style == BSD_STYLE) {
			m_style_str_short = "-";
			m_style_str_long = "-";
		}
		else {
			m_style_str_short = "/";
			m_style_str_long = "/";
		}
	}
}


template <typename HandlerType>
NGetOpt<HandlerType>::~NGetOpt(void) {

}


template <typename HandlerType>
void NGetOpt<HandlerType>::setStyle(Style style) {
	m_style = style;
}


template <typename HandlerType>
typename NGetOpt<HandlerType>::Style NGetOpt<HandlerType>::getStyle(void) const {
	return m_style;
}


template <typename HandlerType>
NGetOpt<HandlerType> &NGetOpt<HandlerType>::add(const NString &opt_short, const NString &opt_long, 
						bool opt_opt, const NString &opt_help, 
						typename NOpt<HandlerType>::Handler handler)
{
	NOpt<HandlerType> opt(opt_short, opt_long, opt_opt, opt_help, handler);
	NDebug::print() << "Adding options";
	NDebug::print() << "Option: " << opt_short << ". Value: " << opt_long << 
		"(" << opt_help << ")";
	
	
	
	return add(opt);
}


template <typename HandlerType>
NGetOpt<HandlerType> &NGetOpt<HandlerType>::add(const NOpt<HandlerType> &opt) {
	if (!m_opts.contains(opt)) {
		m_opts.append(opt);
	}
	else {
		NWarning::print() << "Trying to insert a value '-" << opt.getShort() 
				<< "' [ --" << opt.getLong() << " ] already in the argument list";
	}
	return *this;
}


template <typename HandlerType>
bool NGetOpt<HandlerType>::isLongOpt(const NString &str) const {
	NDebug::print() << " ---> "  << m_style_str_long << " & " << str;
	
	if (str.compare(0, m_style_str_long.length(), m_style_str_long)) {
		return true;	
	}
	
	return false;
}


template <typename HandlerType>
bool NGetOpt<HandlerType>::isShortOpt(const NString &str) const {
	if (str.compare(0, m_style_str_short.length(), m_style_str_short)) {
		if (!isLongOpt(str)) { 
			return true;
		}
	}
	
	return false;
}


template <typename HandlerType>
NOpt<HandlerType> NGetOpt<HandlerType>::getOptByName(const NString &str) {
	NString opt_str;
	NString cmd_str;
	typename NOptList::iterator i = m_opts.begin();
	NOpt<HandlerType> ret;
	
	bool is_short = false;
	nuint32 opt_length = m_style_str_long.length();

	NDebug::print() << "Looking for option: " << str;
	if (isShortOpt(str)) {
		NDebug::print() << "Given option is short";
		is_short = true;
		opt_length = m_style_str_short.length();
	}
	else {
		NDebug::print() << "Given option is not short, checking if it's long";
		if (!isLongOpt(str)) { 
			NString msg = "Option ";
			msg = msg + str + " is not valid";
			throw NException(msg, NException::BASE);
		}
	}

	cmd_str = str.substr(opt_length, str.length() - opt_length);
	for (i = m_opts.begin(); i != m_opts.end(); i++) {
		opt_str = is_short ? i->getShort() : i->getLong();
			
		NDebug::print() << "Comparing: " << cmd_str << "(" << cmd_str.length()
			<< ") with " << opt_str << "(" << opt_str.length() << ")";
		
		if (cmd_str == opt_str) {
			NDebug::print() << "Ok, found!";
			ret = *i;
			break;
		}
	}
	
	return ret;
}

template <typename HandlerType>
NException NGetOpt<HandlerType>::valueErr(const NOpt<HandlerType> *opt) { 
	NString msg = "The option ";
		
	if (opt->getShort() != "") { 
		msg = msg + "'" + opt->getShort() + "'";
	}

	if (opt->getLong() != "") {
		msg = msg + " [ " + opt->getLong() + " ] ";
	}

	msg += "requires an argument but it was not given";
	return NException(msg, NException::BASE);
}



template <typename HandlerType>
char **NGetOpt<HandlerType>::addValue(NOpt<HandlerType> *opt, nint32 pos, char **list) { 
	NString tmp;
	assert(opt);
	
	list++;
	if (!*list || isLongOpt(*list) || isShortOpt(*list)) { 
		throw valueErr(opt);
	}
	
	opt->addValue(*list);
	return list;
}


template <typename HandlerType>
void NGetOpt<HandlerType>::showUsage(void) { 
	NMessage::print() << LIGHT_WHITE << "Usage:";
	for (typename NOptList::iterator i = m_opts.begin(); 
		    i != m_opts.end(); 
			i++) 
	{
		NString msg = "\t";
		
		if (i->getShort() != "") { 
			msg = msg + LIGHT_GREEN + "-" + i->getShort();
			
			if (i->getLong() != "") {
				msg = msg + RESET + " [ " + LIGHT_GREEN + "--" + i->getLong() + RESET + " ] ";
			}
		}
		else { 
			if (i->getLong() != "") {
				msg = msg + LIGHT_GREEN + "--" + i->getLong() + RESET;
			}
		}

		if (i->hasOpt()) { 
			msg = msg + LIGHT_CYAN + "< value >";
		}
	
		NMessage::print() << msg;
	}
}


template <typename HandlerType>
void NGetOpt<HandlerType>::showHelp(void) { 
	NMessage::print() << LIGHT_WHITE << "Help:";
	for (typename NOptList::iterator i = m_opts.begin(); 
		    i != m_opts.end(); 
		    i++) 
	{
		NString msg = "\t"; 
		
		if (i->getLong() != "") {
			msg = msg + LIGHT_GREEN + " --" + i->getLong() + RESET + " ";
		}
		
		if (i->getShort() != "") { 
			msg = msg + "(" + LIGHT_GREEN "-" + i->getShort() + RESET + " short option)";
			
		}
		
		msg += "\n\t\t";
		msg += i->getHelp();
		//msg += "\n";

		NMessage::print() << msg;
	}
}

template <typename HandlerType>
void NGetOpt<HandlerType>::help(void) { 
	showUsage();
	NMessage::print();
	showHelp();
}


template <typename HandlerType>
bool NGetOpt<HandlerType>::proccess(void) {
	typename NOpt<HandlerType>::Handler method;
	NOpt<HandlerType> opt;
	NString tmp;
	char **local_argv = m_argv;
	
	if (m_argc <= m_min_args) {
		help();
		return false;
	}
	
	local_argv++;
	for (nint32 i = 1; i <= m_argc; i++, local_argv++) {
		tmp = *local_argv;
		
		opt = getOptByName(tmp);
		if (!opt.isNull()) {
			if (opt.hasOpt()) {
				local_argv = addValue(&opt, i, local_argv);
				i++;
			}
			
			m_passed.append(opt);
		}
		else { 
			NWarning::print() << "Invalid option " << tmp;
			help();
			
			return false;
			
		}
	}
	
	// Executes each given parameter
	for (typename NOptList::iterator i = m_passed.begin(); 
		    i != m_passed.end(); 
		    i++) 
	{
		method = i->getHandler();
		if (!method) { 
			help();
			return false;
		}
		else {
			if (!(m_handler->*method)(*i)) {
				return false;
			};
		}
	}
	
	return true;
	
}

#endif // NGETOPT_HPP
