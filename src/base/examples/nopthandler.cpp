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
#include "nopthandler.h"


NOptHandler::NOptHandler(void)
	: NObject(),
	m_south(false),
	m_central(false),
	m_north(false),
	m_languages(),
	m_max(2),
	m_countries()
{ 
	// Adds some data to the list of countries
	m_countries.append(Country("Brazil", "South America", "portuguese"));
	m_countries.append(Country("Argentina", "South America", "spanish"));
	m_countries.append(Country("Chile", "South America", "spanish"));
	m_countries.append(Country("Colombia", "South America", "spanish"));
	m_countries.append(Country("Venezuela", "South America", "spanish"));
	
	m_countries.append(Country("Panama", "Central America", "spanish"));
	m_countries.append(Country("Guatemala", "Central America", "spanish"));
	m_countries.append(Country("Honduras", "Central America", "spanish"));
	
	m_countries.append(Country("USA", "North America", "english"));
	m_countries.append(Country("Mexico", "North America", "spanish"));
	m_countries.append(Country("Canada", "Central America", "french"));
}

NOptHandler::~NOptHandler(void) { 

}

// This method is executed when --south-america is passed on the command line
bool NOptHandler::south_america(const NOpt<NOptHandler> &val) {
	m_south = true;
	return true;
}


// This method is executed when --central-america is passed on the command line
bool NOptHandler::central_america(const NOpt<NOptHandler> &val) {
	m_central = true;
	return true;
}


// This method is executed when --north-america is passed on the command line
bool NOptHandler::north_america(const NOpt<NOptHandler> &val) {
	m_north = true;
	return true;
}

// This method is executed when --language is passed on the command line
// Note that it will accept as many --language options as passed on the 
// command line
bool NOptHandler::language(const NOpt<NOptHandler> &val) {
	NList<NString> values;
	
	// Iterates through the list of values, processing all the options 
	// given
	values = val.getValues();
	for (NList<NString>::const_iterator i = values.constBegin();
		i != values.constEnd();
		i++)
	{
		NMessage::print() << "Language: " << *i;
		if (*i != "portuguese" && *i != "english" &&  *i != "spanish") { 
			NString msg = "Error: ";
			
			msg = msg + *i + " is not a valid language!";
			throw NException(msg, NException::BASE);	
		}
	
		m_languages.append(*i);
	}
	
	return true;
} 


// This method is executed when --max is passed on the command line
bool NOptHandler::max(const NOpt<NOptHandler> &val) {
	NString strValue;
	
	strValue = val.getValues().at(0);
	m_max = atoi(strValue.toChar());
	if (m_max < 2 || m_max > 5) { 
		m_max = 2;
	}
	
	return true;
}



bool NOptHandler::showCountry(const Country &country, const NString &continent) { 
	if (country.continent == continent && m_languages.contains(country.language)) { 
		NMessage::print() << "Country: " << country.name;
		NMessage::print() << "Continent: " << country.continent;
		NMessage::print() << "Language: " << country.language;
		
		return true;
	}
	else { 
		if (country.continent == continent && m_languages.size() == 0) { 
			NMessage::print() << "Country: " << country.name;
			NMessage::print() << "Continent: " << country.continent;
			NMessage::print() << "Language: " << country.language;
			
			return true;
		}
	}
	
	return false;
}

void NOptHandler::showContinent(const NString &continent) { 
	NOptHandler::Country country;
	nint32 count = 0;
	
	for (nuint32 i = 0; i < m_countries.size(); i++) { 
		country = m_countries.at(i);
		if (showCountry(country, continent)) { 
			count++;
			
			if (count >= m_max) { 
				break;
			}
		}
	}	
	NMessage::print();
}


// This method is used to execte the options passed on the command line
void NOptHandler::foo(void) { 
	if (m_south) { 
		showContinent("South America");
	}
	
	if (m_central) { 
		showContinent("Central America");
	}
	
	if (m_north) { 
		showContinent("North America");
	}
}
