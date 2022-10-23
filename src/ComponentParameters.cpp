/*
 * ComponentParameters.cpp
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
 
#include "../inc/ComponentParameters.hpp"
using namespace log4cxx;

LoggerPtr ComponentParameters::logger(Logger::getLogger("plotter.config.componentParameters"));

ComponentParameters::ComponentParameters(string name, string config)
{
	LOG4CXX_TRACE(logger, "ComponentParameters constructor: name=" << name << ", config=" << config);
	mType = unknown;
	mName = name;
	size_t pos = 0;
	if ((pos = config.find("(")) == string::npos) 
	{
		LOG4CXX_ERROR(logger, "Missing configuration info for Component " << name);
		return;
	}
	while ((pos = config.find(".")) != string::npos)
	{
		config.erase(0, pos + 1);
		size_t pos2 = 0;
		if ((pos2 = config.find("(")) != string::npos)
		{
			string token = config.substr(0, pos2);
			config.erase(0, pos2 + 1);
			size_t pos3 = 0;
			if ((pos3 = config.find(")")) != string::npos)
			{
				string value = config.substr(0, pos3);
				if (Apply(token, value) == ERROR)
				{
					LOG4CXX_ERROR(logger, "Cannot handle token " << token << " and value " << value);
				}
			}
			else
				LOG4CXX_ERROR(logger, "Wrong configuration info for Component. Missing ) ?");
		}
		else
			LOG4CXX_ERROR(logger, "Missing configuration info for Component");
	}
}

ComponentParameters::~ComponentParameters()
{
	LOG4CXX_TRACE(logger, "ComponentParameters destructor. " << mName);
}

int ComponentParameters::SetType(string type)
{
	LOG4CXX_TRACE(logger, "ComponentParameters SetType " << type);
	mType = unknown;
	if (type == "led")
		mType = led;
	if (type == "servo")
		mType = servo;
	if (type == "camera")
		mType = camera;
	if (type == "button")
		mType = button;
	if (type == "arm")
		mType=arm;
	if (type == "screen")
		mType = screen;
	if (mType == unknown)
	{
		LOG4CXX_ERROR(logger, "Unknown type of component");
		return ERROR;
	}
	else
		return OK;
}

int ComponentParameters::SetPin(string pin)
{
	LOG4CXX_TRACE(logger, "ComponentParameters SetPin " << pin);
	mPin = atoi(pin.c_str());
	return OK;
}

int ComponentParameters::Apply(string token, string value)
{
	LOG4CXX_TRACE(logger, "ComponentParameters Apply. Token=" << token << ", Value=" << value);
	if (token == "type")
		return SetType(value);
	if (token == "pin")
		return SetPin(value);
	return ERROR;
}

ComponentType ComponentParameters::GetType()
{
	LOG4CXX_TRACE(logger, "ComponentParameters GetType. " << mType);
	return mType;
}
string ComponentParameters::GetName()
{
	LOG4CXX_TRACE(logger, "ComponentParameters GetName. " << mName);
	return mName;
}

int ComponentParameters::GetPin()
{
	LOG4CXX_TRACE(logger, "ComponentParameters GetPin. " << mPin);
	return mPin;
}
