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

#include "Config.hpp"
#include "Constants.hpp"

Config::Config(string fileName)
{
	mState = OK;
	std::cerr << "Config::Config" << endl;
	mFileName = fileName;
	std::cout << "Reading config file " << mFileName << std::endl;
	if (Read() == FALSE)
	{
		std::cout << "Error reading the config file " << mFileName << endl;
		mState = ERROR;
	}
}
Config::~Config()
{
	std::cerr << "Config::~Config" << endl;
	for (vector<Component*>::iterator componentIterator = components.begin(); componentIterator != components.end(); ++componentIterator)
	{
		Component* component = *componentIterator;
		delete(component);
	}
}

int Config::Read()
{
	std::cerr << "Config::Read" << endl;
	int ret = FALSE;
	string inputLine;
	string line;
	ifstream stream(mFileName);
	if (stream.is_open())
	{
		while (getline(stream, inputLine))
		{
			string line = Trim(inputLine);
			if (line.substr(0, 2) != "//" && line.substr(0, 1) != "#") { // skip the line; It is a comment
				size_t pos = 0;
				if ((pos = line.find("=")) != string::npos)
				{
					string token = Trim(line.substr(0, pos));
					line.erase(0, pos + 1);
					string value = Trim(line);
					data[token] = value;
					size_t pos2 = 0;
					string componentTag = "Component";
					if ((pos2 = value.find(componentTag)) != string::npos)
					{
						value.erase(0, componentTag.length());
						size_t pos3 = 0;
						if ((pos = line.find("(")) != string::npos) {
							Component* component = new Component(token, value);
							if (component->GetType() == unknown) {
								cerr << "Unknown component type" << endl;
								mState = ERROR;
							}
							else
								components.push_back(component);
						}
						else
						{
							cerr << "Missing details" << endl;
							mState = ERROR;
						}
					}
				}
				else
				{
					cerr << "Format error" << endl;
					mState = ERROR;
				}
			}
			ret = TRUE;
		}
		cerr << "Components added" << endl;
	}
	else
	{
		ret = FALSE;
	}

	stream.close();
	return ret;
}
string Config::GetValue(string key)
{
	map<string, string>::iterator it;
	it = data.find(key);
	if (it != data.end())
		return it->second;
	else
		return "Anonymous";
}
string Config::Trim(string text)
{
	if (text.empty())
		return text;
	size_t start = 0;
	size_t end = text.size() - 1;
	for (int i = 0; i <= end; i++)
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
int Config::IsValid()
{
	return mState;
}
