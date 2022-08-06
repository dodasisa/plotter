/*
 * Component.hpp
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

#ifndef __COMPONENT__
#define __COMPONENT__

#include "Constants.hpp"
#include <string>
#include <iostream>

using namespace std;

class Component
{
	private:
	string mName;
	ComponentType mType;
	int mPin;
	
	int Apply(string token, string value);
	int SetType(string type);
	int SetPin(string pin);
		
	public:
	Component(string name,string config);
	~Component();
	
	ComponentType GetType();
	string GetName();
	int GetPin();
};


#endif
