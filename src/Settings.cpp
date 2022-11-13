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
	ErrorMessage="";
	LOG4CXX_TRACE(logger, "Settings constructor end");
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
	ParseResult ok=d.ParseStream(is);
	fclose(fp);

	if (!ok)
	{
		LOG4CXX_ERROR(logger, "Settings: Error parsing ");// << FileName << ". " << GetParseError_En(ok.Code()) << "," <<  ok.Offset());
		ErrorMessage="Parse error";
		Valid=false;
		return false;
	}
	/*
	const Value& robotName= d["name"];
	if (!robotName.IsNull())
		RobotName=robotName.GetString();

	const Value& robotVersion= d["version"];
	if (!robotVersion.IsNull())
		RobotVersion=robotVersion.GetString();

	const Value& components = d["components"];
	LOG4CXX_DEBUG(logger, "Settings: components count=" << components.Size());
	for (int i=0; i<components.Size();i++)
	{		
		const Value& component=components[i].GetObject();
		LOG4CXX_DEBUG(logger, "Settings: component " << (i+1) << ". Name=" << component["name"].GetString() << "Type=" << component["type"].GetString());
				
		//LOG4CXX_DEBUG(logger, "Settings: component " << (i+1) << "name=" << components[i]["name"] << ", type=" << components[i]["type"]);
	}
	*/
	Valid=true;
	return Valid;
}
string Settings::GetRootString(string name)
{
	char char_array[name.length()+1];
	strcpy(char_array, name.c_str());
	const Value& text= d[char_array];
	if (!text.IsNull())
		return text.GetString();
	else
	{
		ErrorMessage="Setting " + name + " not found";
		return "ERROR";
	}
}
string Settings::GetErrorMessage()
{
	return ErrorMessage;
}
bool Settings::GetTest()
{
	return Test;
}
bool Settings::GetValid()
{
	return Valid;
}
void Settings::SetTestMode(bool mode)
{
	Test=mode;
}

string Settings::GetComponentString(char* componentName, char *property)
{
	const Value& components = d["components"];
	const Value& component=components[componentName].GetObject();
	
	const Value& value= component[property];
	if (!value.IsNull())
		return value.GetString();
	else
	{
//		ErrorMessage="Component setting " + index + ". " + name + " not found";
		return "ERROR";
	}	
}

int Settings::GetComponentInt(char* componentName, char *property)
{
	const Value& components = d["components"];
	const Value& component=components[componentName].GetObject();
	
	const Value& value= component[property];
	if (!value.IsNull())
		return value.GetInt();
	else
	{
//		ErrorMessage="Component setting " + index + ". " + name + " not found";
		return -1;
	}	
}

