/*
 * Config.cpp
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

#include "../inc/Config.hpp"
#include "../inc/Constants.hpp"
using namespace log4cxx;

LoggerPtr Config::logger(Logger::getLogger("plotter.config"));

Config::Config(string fileName,bool test)
{
	if (test) SetTestMode();
	if (IsOnTestMode()){
		logger->setLevel(Level::getOff());
	}
	mState = OK;
	LOG4CXX_TRACE(logger, "Config constructor");
	/// Stores the file name
	mFileName = fileName;
	LOG4CXX_INFO(logger, "Reading " << fileName);
	/// and calls the method Read()
	if (Read() == FALSE)
	{
		LOG4CXX_ERROR(logger, "Cannot read " << fileName);
		/// If Read() issues any error, the Config state is set to ERROR
		mState = ERROR;
	}
}

Config::~Config()
{
	LOG4CXX_TRACE(logger, "Config destructor");
	/// Loops through the Component's vector, component configuration detail, not the component itself,
	for (vector<ComponentParameters*>::iterator componentIterator = components.begin(); componentIterator != components.end(); ++componentIterator)
	{
		ComponentParameters* component = *componentIterator;
		/// and deletes them.
		delete(component);
	}
}
/**
 * The Read() method that actually reads the config file
 */ 
int Config::Read()
{
	LOG4CXX_TRACE(logger, "Config Read");
	int ret = FALSE;
	string inputLine;
	string line;
	ifstream stream(mFileName);
	int lineNumber = 0;
	/// Error if the file cannot be found.
	if (stream.is_open())
	{
		/// Reads line by line.
		while (getline(stream, inputLine))
		{
			lineNumber++;
			/// Removes the leading and trailing whitespaces
			string line = Trim(inputLine);
			/// Skips the comments, lines starting by // of by #
			if (line.substr(0, 2) != "//" && line.substr(0, 1) != "#") { // skip the line; It is a comment
				size_t pos = 0;
				/// A valid line must foolw the format key=value; the = is mandatory
				if ((pos = line.find("=")) != string::npos)
				{
					/// Removes leading and trailing whitespaces of the key
					string token = Trim(line.substr(0, pos));
					line.erase(0, pos + 1);
					/// Removes leading and trailing whitespaces of the value
					string value = Trim(line);
					data[token] = value;
					size_t pos2 = 0;
					string componentTag = "Component";
					/// if the value starts with the keyword Component, the rest of the value follows the format .variable(parameter)
					/// variable can be type, pin ...
					/// parameter can be a text or a number
					if ((pos2 = value.find(componentTag)) != string::npos)
					{
						value.erase(0, componentTag.length());
						size_t pos3 = 0;
						if ((pos3 = line.find("(")) != string::npos) {
							ComponentParameters* component = new ComponentParameters(token, value);
							/// An unknown or missing .variable means error.
							if (component->GetType() == unknown) {
								LOG4CXX_ERROR(logger, "Config line " << lineNumber << ". Unknown component type");
								mState = ERROR;
							}
							else
								components.push_back(component);
						}
						else
						{
							/// An variable without parameter means error.
							LOG4CXX_ERROR(logger, "Config line " << lineNumber << ". Missing details");
							mState = ERROR;
						}
					}
				}
				else
				{
					LOG4CXX_ERROR(logger, "Config line " << lineNumber << ". Format error");
					mState = ERROR;
				}
			}
			ret = TRUE;
		}
	}
	else
	{
		ret = FALSE;
	}

	stream.close();
	return ret;
}
/**
 * The GetValue() method returns the right part of the = using the left part as key.
 */ 
string Config::GetValue(string key)
{
	map<string, string>::iterator it;
	it = data.find(key);
	/// If not found returns anonymous. The default name of the robot comes from here.
	if (it != data.end())
		return it->second;
	else
		return "Anonymous";
}
/**
 * Removes leacing and trailing whitespaces of the given text
 */ 
string Config::Trim(string text)
{
	if (text.empty())
		return text;
	size_t start = 0;
	size_t end = text.size() - 1;
	for (size_t i = 0; i <= end; i++)
	{
		if (text[i] != ' ')
		{
			start = i;
			break;
		}
	}
	for (size_t i = end; i > 0; i--)
	{
		if (text[i] != ' ')
		{
			end = i;
			break;
		}
	}
	string result;
	for (size_t i = start; i <= end; i++)
		result += text[i];
	return result;
}
/**
 * Gives the status of the Config object
 * @return 0 if any error, 1 if success.
 */ 
int Config::IsValid()
{
	return mState;
}

/**
 * Writes nothing to the logs during the tests
 */ 
void Config::SetTestMode()
{
	mTest=true;
}

/**
 * Retrieves if on test mode
 * @return true if on est oin test mode
 */ 
bool Config::IsOnTestMode()
{
	return mTest;
}
