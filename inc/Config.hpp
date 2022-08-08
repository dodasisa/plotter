/*
 * Config.hpp
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
 
#ifndef __CONFIG__
#define __CONFIG__
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "Component.hpp"
#include "log4cxx/logger.h"

using namespace std;

/*! \class Config
 *  \brief Configuration class. Parses the config file
 *  \param fileName The configuration path and file name
 * 
 * The constructor gets the configurarion file name, by default robot.cfg
 */  
class Config
{
private:
	static log4cxx::LoggerPtr logger;
	string mFileName;
	int Read();
	string Trim(string text);
	int mState;
	map<string, string> data;

public:
	Config(string fileName); 			///< Config constructor. Calls Read() and returns its value.
	~Config();							///< Destructor. Calls the destructor of every Component configuration details.
	vector<Component*> components;		///< Vector of components configuration data found in the cfg file.
	string GetValue(string key);		///< cfg data is stored in a map<key,value>. This returns the value of one key.
	int IsValid();						///< Returns 0 if errors found, 1 if the config file is correct.
};

#endif
