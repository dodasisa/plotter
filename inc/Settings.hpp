/*
 * settings.hpp
 * 
 * Copyright 2022 David <david.lopez.velazquez@gmail.com>
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


#ifndef SETTINGS_HPP
#define SETTINGS_HPP
#include <string>
#include <cstdio>
#include <cstring>
#include "../inc/rapidjson/document.h"
#include "../inc/rapidjson/filereadstream.h"
#include "log4cxx/logger.h"
#include "ComponentParameters.hpp"

using namespace std;
using namespace rapidjson;

class Settings
{
	public:
		Settings();
		/*!
		 * Defines the json file to parse
		 */
		void SetFile(string fileName);
		/*!
		 * Parses the Json file and fills the required properties with its content
		 */
		bool Parse(); 
		/*! 
		* Returns the error message, if any.
		*/
		string GetErrorMessage();
		/*!
		 * True if running tests; false if live mode
		 */ 
		bool GetTest();
		/*!
		 * True if no error has been detected
		 */
		bool GetValid();
		
		//vector<ComponentParameters*> GetComponents();
		//map<string, string> data;

		void SetTestMode(bool mode);

		string GetRootString(string name);
		
		string GetComponentString(char* componentName, char* property);
		int GetComponentInt(char* componentName, char *property);
		
	private:
		Document d;
		string FileName;
		string ErrorMessage;
		bool Test;
		bool Valid;
		static log4cxx::LoggerPtr logger;
};

#endif /* SETTINGS_HPP */ 
