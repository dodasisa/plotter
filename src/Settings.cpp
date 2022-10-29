/*
 * settings.cpp
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


#include "../inc/Settings.hpp"
using namespace std;
using namespace log4cxx;

LoggerPtr Settings::logger(Logger::getLogger("plotter.settings"));

Settings::Settings()
{
	LOG4CXX_TRACE(logger, "Settings constructor");
	Message="";
}

void Settings::SetFile(string fileName)
{
	LOG4CXX_TRACE(logger, "Settings SetFile " << fileName);
	FileName=fileName;
}

bool Settings::Parse()
{
	LOG4CXX_TRACE(logger, "Settings Parse");
	FILE* fp = fopen(FileName.c_str(),"rb");
	char readBuffer[1000];
	FileReadStream is(fp,readBuffer,sizeof(readBuffer));
	Document d;
	d.ParseStream(is);
	fclose(fp);
	
	LOG4CXX_DEBUG(logger, "Settings: name=" << d["name"].GetString());
	LOG4CXX_DEBUG(logger, "Settings: version=" << d["version"].GetString());
	const Value& components = d["components"];
	LOG4CXX_DEBUG(logger, "Settings: components count=" << components.Size());
	for (int i=0; i<components.Size();i++)
	{		
		const Value& component=components[i].GetObject();
		LOG4CXX_DEBUG(logger, "Settings: component " << (i+1) << ". Name=" << component["name"].GetString());
				
		//LOG4CXX_DEBUG(logger, "Settings: component " << (i+1) << "name=" << components[i]["name"] << ", type=" << components[i]["type"]);
	}
	return true;
} 

