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
	std::cerr << "Config::Config" << endl;
	mFileName=fileName;
	std::cout << "Reading config file " << mFileName << std::endl;
	if (Read()==FALSE)
	{
		std::cout << "Error reading the config file " << mFileName << endl;
	}
}
Config::~Config()
{
	std::cerr << "Config::~Config" << endl;
}

int Config::Read()
{
	std::cerr << "Config::Read" << endl;
	int ret=FALSE;
	string line;
	ifstream stream(mFileName);
	if (stream.is_open())
	{
		cerr << "Adding components" << endl;
		while (getline (stream,line))
		{
			size_t pos = 0;
			if ((pos= line.find("=")) != string::npos)
			{
				string token=Trim(line.substr(0,pos));
				line.erase(0,pos+1);
				string value=Trim(line);
				data[token] = value;
				size_t pos2 = 0;
				string componentTag="Component";
				if ((pos2= value.find(componentTag)) != string::npos)
				{
					value.erase(0,componentTag.length());
					components.push_back(Component(token,value));
				}
			}
			ret=TRUE;
		}
		cerr << "Components added" << endl;
	}
	else
	{
		ret=FALSE;
	}
	
	stream.close();
	return ret;
}
string Config::GetValue(string key)
{
	map<string,string>::iterator it;
	it=data.find(key);
	if (it != data.end())
		return it->second;
	else
		return "Anonymous";
}
string Config::Trim(string text) 
{
	if (text.empty())
		return text;
	int start=0;
	int end=text.size()-1;
	for (int i=0;i<=end;i++)
	{
		if (text[i] != ' ')
		{
			start=i;
			break;
		}
	}
	for (int i=end; i>=0;i--)
	{
		if (text[i] != ' ')
		{
			end=i;
			break;
		}		
	}
	string result;
	for (int i=start;i<=end;i++)
		result += text[i];
	return result;
}

