/*
 * ComponentParameters.hpp
 * 
 * Copyright 2022  <david.lopez.velazquez@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#ifndef __COMPONENTPARAMETERS__
#define __COMPONENTPARAMETERS__

#include "Constants.hpp"
#include <string>
#include <iostream>
#include "log4cxx/logger.h"

using namespace std;

/*! \class ComponentParameters
 *  \brief Stores the configuration of any component
 *  \see BaseComponent
 *  Simply stores the parameters grabbed from the config file for one component
 *  This class is used by Robot to build the actual components
 */ 
class ComponentParameters
{
	private:
	static log4cxx::LoggerPtr logger;
	string mName;
	ComponentType mType;
	int mPin;
	
	int Apply(string token, string value);
	int SetType(string type);
	int SetPin(string pin);
		
	public:
	/*! 
	* Default constructor
	* \param name Name of the current component
	* \param config Text containing the parameters to be parsed
	* Parses the information coming in the config string, and stores under the given name
	*/ 
	ComponentParameters(string name,string config);
	
	/*! 
	* Destructor
	*/
	~ComponentParameters();
	
	/*! Returns the type of component.
	 * One of the values pof the enum ComponentType
	 */
	ComponentType GetType();
	
	/*! 
	 * Returns the name of component.
	 */
	string GetName();
	
	/*! 
	 * Returns the pin of the component, if any.
	 */
	int GetPin();
};


#endif
