/*
 * Component.cpp
 * 
 * Copyright 2022  <david@raspberrypi>
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
 
#include "Component.hpp"

Component::Component(string name, string config)
{
	mType = unknown;
	mName = name;
	size_t pos = 0;
	if ((pos = config.find("(")) == string::npos) 
	{
		cerr << "Missing configuration info for Component " << name << endl;
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
					cerr << "Cannot handle token " << token << " and value " << value << endl;
				}
			}
			else
				cerr << "Wrong configuration info for Component. Missing ) ?" << endl;
		}
		else
			cerr << "Missing configuration info for Component" << endl;
	}
}

Component::~Component()
{
}

int Component::SetType(string type)
{
	mType = unknown;
	if (type == "led")
		mType = led;
	if (type == "servo")
		mType = servo;
	if (type == "camera")
		mType = camera;
	if (mType == unknown)
	{
		cerr << "Unknown type of component" << endl;
		return ERROR;
	}
	else
		return OK;
}

int Component::SetPin(string pin)
{
	mPin = atoi(pin.c_str());
	return OK;
}

int Component::Apply(string token, string value)
{
	if (token == "type")
		return SetType(value);
	if (token == "pin")
		return SetPin(value);
	return ERROR;
}

ComponentType Component::GetType()
{
	return mType;
}
string Component::GetName()
{
	return mName;
}

int Component::GetPin()
{
	return mPin;
}
