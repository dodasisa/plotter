/*
 * basecomponent.hpp
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


#ifndef BASECOMPONENT_HPP
#define BASECOMPONENT_HPP
#include <string>
#include "Constants.hpp"
using namespace std;
class BaseComponent
{
	public:
		BaseComponent();
		BaseComponent(ComponentType type);
		virtual ~BaseComponent();
		int GetReady();
		void SetReady(int ready);
		string GetName();
		void SetName(string name);
		int GetState();
		void SetState(int state);
		ComponentType GetType();
		void SetType(ComponentType type);
	
	private:
		int mReady;
		int mState;
		string mName;
		ComponentType mType;
};

#endif /* BASECOMPONENT_HPP */ 
